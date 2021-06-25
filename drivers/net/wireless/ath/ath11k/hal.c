<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#समावेश <linux/dma-mapping.h>
#समावेश "hal_tx.h"
#समावेश "debug.h"
#समावेश "hal_desc.h"
#समावेश "hif.h"

अटल स्थिर काष्ठा hal_srng_config hw_srng_config_ढाँचा[] = अणु
	/* TODO: max_rings can populated by querying HW capabilities */
	अणु /* REO_DST */
		.start_ring_id = HAL_SRNG_RING_ID_REO2SW1,
		.max_rings = 4,
		.entry_size = माप(काष्ठा hal_reo_dest_ring) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_REO_REO2SW1_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* REO_EXCEPTION */
		/* Designating REO2TCL ring as exception ring. This ring is
		 * similar to other REO2SW rings though it is named as REO2TCL.
		 * Any of theREO2SW rings can be used as exception ring.
		 */
		.start_ring_id = HAL_SRNG_RING_ID_REO2TCL,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_reo_dest_ring) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_REO_REO2TCL_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* REO_REINJECT */
		.start_ring_id = HAL_SRNG_RING_ID_SW2REO,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_reo_entrance_ring) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_REO_SW2REO_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* REO_CMD */
		.start_ring_id = HAL_SRNG_RING_ID_REO_CMD,
		.max_rings = 1,
		.entry_size = (माप(काष्ठा hal_tlv_hdr) +
			माप(काष्ठा hal_reo_get_queue_stats)) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_REO_CMD_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* REO_STATUS */
		.start_ring_id = HAL_SRNG_RING_ID_REO_STATUS,
		.max_rings = 1,
		.entry_size = (माप(काष्ठा hal_tlv_hdr) +
			माप(काष्ठा hal_reo_get_queue_stats_status)) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_REO_STATUS_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* TCL_DATA */
		.start_ring_id = HAL_SRNG_RING_ID_SW2TCL1,
		.max_rings = 3,
		.entry_size = (माप(काष्ठा hal_tlv_hdr) +
			     माप(काष्ठा hal_tcl_data_cmd)) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_SW2TCL1_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* TCL_CMD */
		.start_ring_id = HAL_SRNG_RING_ID_SW2TCL_CMD,
		.max_rings = 1,
		.entry_size = (माप(काष्ठा hal_tlv_hdr) +
			     माप(काष्ठा hal_tcl_gse_cmd)) >> 2,
		.lmac_ring =  false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_SW2TCL1_CMD_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* TCL_STATUS */
		.start_ring_id = HAL_SRNG_RING_ID_TCL_STATUS,
		.max_rings = 1,
		.entry_size = (माप(काष्ठा hal_tlv_hdr) +
			     माप(काष्ठा hal_tcl_status_ring)) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_TCL_STATUS_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* CE_SRC */
		.start_ring_id = HAL_SRNG_RING_ID_CE0_SRC,
		.max_rings = 12,
		.entry_size = माप(काष्ठा hal_ce_srng_src_desc) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_CE_SRC_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* CE_DST */
		.start_ring_id = HAL_SRNG_RING_ID_CE0_DST,
		.max_rings = 12,
		.entry_size = माप(काष्ठा hal_ce_srng_dest_desc) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_CE_DST_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* CE_DST_STATUS */
		.start_ring_id = HAL_SRNG_RING_ID_CE0_DST_STATUS,
		.max_rings = 12,
		.entry_size = माप(काष्ठा hal_ce_srng_dst_status_desc) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_CE_DST_STATUS_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* WBM_IDLE_LINK */
		.start_ring_id = HAL_SRNG_RING_ID_WBM_IDLE_LINK,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_wbm_link_desc) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_WBM_IDLE_LINK_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* SW2WBM_RELEASE */
		.start_ring_id = HAL_SRNG_RING_ID_WBM_SW_RELEASE,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_wbm_release_ring) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_SW2WBM_RELEASE_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* WBM2SW_RELEASE */
		.start_ring_id = HAL_SRNG_RING_ID_WBM2SW0_RELEASE,
		.max_rings = 4,
		.entry_size = माप(काष्ठा hal_wbm_release_ring) >> 2,
		.lmac_ring = false,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_WBM2SW_RELEASE_RING_BASE_MSB_RING_SIZE,
	पूर्ण,
	अणु /* RXDMA_BUF */
		.start_ring_id = HAL_SRNG_RING_ID_WMAC1_SW2RXDMA0_BUF,
		.max_rings = 2,
		.entry_size = माप(काष्ठा hal_wbm_buffer_ring) >> 2,
		.lmac_ring = true,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_RXDMA_RING_MAX_SIZE,
	पूर्ण,
	अणु /* RXDMA_DST */
		.start_ring_id = HAL_SRNG_RING_ID_WMAC1_RXDMA2SW0,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_reo_entrance_ring) >> 2,
		.lmac_ring = true,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_RXDMA_RING_MAX_SIZE,
	पूर्ण,
	अणु /* RXDMA_MONITOR_BUF */
		.start_ring_id = HAL_SRNG_RING_ID_WMAC1_SW2RXDMA2_BUF,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_wbm_buffer_ring) >> 2,
		.lmac_ring = true,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_RXDMA_RING_MAX_SIZE,
	पूर्ण,
	अणु /* RXDMA_MONITOR_STATUS */
		.start_ring_id = HAL_SRNG_RING_ID_WMAC1_SW2RXDMA1_STATBUF,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_wbm_buffer_ring) >> 2,
		.lmac_ring = true,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_RXDMA_RING_MAX_SIZE,
	पूर्ण,
	अणु /* RXDMA_MONITOR_DST */
		.start_ring_id = HAL_SRNG_RING_ID_WMAC1_RXDMA2SW1,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_reo_entrance_ring) >> 2,
		.lmac_ring = true,
		.ring_dir = HAL_SRNG_सूची_DST,
		.max_size = HAL_RXDMA_RING_MAX_SIZE,
	पूर्ण,
	अणु /* RXDMA_MONITOR_DESC */
		.start_ring_id = HAL_SRNG_RING_ID_WMAC1_SW2RXDMA1_DESC,
		.max_rings = 1,
		.entry_size = माप(काष्ठा hal_wbm_buffer_ring) >> 2,
		.lmac_ring = true,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_RXDMA_RING_MAX_SIZE,
	पूर्ण,
	अणु /* RXDMA सूची BUF */
		.start_ring_id = HAL_SRNG_RING_ID_RXDMA_सूची_BUF,
		.max_rings = 1,
		.entry_size = 8 >> 2, /* TODO: Define the काष्ठा */
		.lmac_ring = true,
		.ring_dir = HAL_SRNG_सूची_SRC,
		.max_size = HAL_RXDMA_RING_MAX_SIZE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ath11k_hal_alloc_cont_rdp(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	माप_प्रकार size;

	size = माप(u32) * HAL_SRNG_RING_ID_MAX;
	hal->rdp.vaddr = dma_alloc_coherent(ab->dev, size, &hal->rdp.paddr,
					    GFP_KERNEL);
	अगर (!hal->rdp.vaddr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ath11k_hal_मुक्त_cont_rdp(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	माप_प्रकार size;

	अगर (!hal->rdp.vaddr)
		वापस;

	size = माप(u32) * HAL_SRNG_RING_ID_MAX;
	dma_मुक्त_coherent(ab->dev, size,
			  hal->rdp.vaddr, hal->rdp.paddr);
	hal->rdp.vaddr = शून्य;
पूर्ण

अटल पूर्णांक ath11k_hal_alloc_cont_wrp(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	माप_प्रकार size;

	size = माप(u32) * HAL_SRNG_NUM_LMAC_RINGS;
	hal->wrp.vaddr = dma_alloc_coherent(ab->dev, size, &hal->wrp.paddr,
					    GFP_KERNEL);
	अगर (!hal->wrp.vaddr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ath11k_hal_मुक्त_cont_wrp(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	माप_प्रकार size;

	अगर (!hal->wrp.vaddr)
		वापस;

	size = माप(u32) * HAL_SRNG_NUM_LMAC_RINGS;
	dma_मुक्त_coherent(ab->dev, size,
			  hal->wrp.vaddr, hal->wrp.paddr);
	hal->wrp.vaddr = शून्य;
पूर्ण

अटल व्योम ath11k_hal_ce_dst_setup(काष्ठा ath11k_base *ab,
				    काष्ठा hal_srng *srng, पूर्णांक ring_num)
अणु
	काष्ठा hal_srng_config *srng_config = &ab->hal.srng_config[HAL_CE_DST];
	u32 addr;
	u32 val;

	addr = HAL_CE_DST_RING_CTRL +
	       srng_config->reg_start[HAL_SRNG_REG_GRP_R0] +
	       ring_num * srng_config->reg_size[HAL_SRNG_REG_GRP_R0];

	val = ath11k_hअगर_पढ़ो32(ab, addr);
	val &= ~HAL_CE_DST_R0_DEST_CTRL_MAX_LEN;
	val |= FIELD_PREP(HAL_CE_DST_R0_DEST_CTRL_MAX_LEN,
			  srng->u.dst_ring.max_buffer_length);
	ath11k_hअगर_ग_लिखो32(ab, addr, val);
पूर्ण

अटल व्योम ath11k_hal_srng_dst_hw_init(काष्ठा ath11k_base *ab,
					काष्ठा hal_srng *srng)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	u32 val;
	u64 hp_addr;
	u32 reg_base;

	reg_base = srng->hwreg_base[HAL_SRNG_REG_GRP_R0];

	अगर (srng->flags & HAL_SRNG_FLAGS_MSI_INTR) अणु
		ath11k_hअगर_ग_लिखो32(ab, reg_base +
				   HAL_REO1_RING_MSI1_BASE_LSB_OFFSET(ab),
				   srng->msi_addr);

		val = FIELD_PREP(HAL_REO1_RING_MSI1_BASE_MSB_ADDR,
				 ((u64)srng->msi_addr >>
				  HAL_ADDR_MSB_REG_SHIFT)) |
		      HAL_REO1_RING_MSI1_BASE_MSB_MSI1_ENABLE;
		ath11k_hअगर_ग_लिखो32(ab, reg_base +
				       HAL_REO1_RING_MSI1_BASE_MSB_OFFSET(ab), val);

		ath11k_hअगर_ग_लिखो32(ab,
				   reg_base + HAL_REO1_RING_MSI1_DATA_OFFSET(ab),
				   srng->msi_data);
	पूर्ण

	ath11k_hअगर_ग_लिखो32(ab, reg_base, srng->ring_base_paddr);

	val = FIELD_PREP(HAL_REO1_RING_BASE_MSB_RING_BASE_ADDR_MSB,
			 ((u64)srng->ring_base_paddr >>
			  HAL_ADDR_MSB_REG_SHIFT)) |
	      FIELD_PREP(HAL_REO1_RING_BASE_MSB_RING_SIZE,
			 (srng->entry_size * srng->num_entries));
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_REO1_RING_BASE_MSB_OFFSET(ab), val);

	val = FIELD_PREP(HAL_REO1_RING_ID_RING_ID, srng->ring_id) |
	      FIELD_PREP(HAL_REO1_RING_ID_ENTRY_SIZE, srng->entry_size);
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_REO1_RING_ID_OFFSET(ab), val);

	/* पूर्णांकerrupt setup */
	val = FIELD_PREP(HAL_REO1_RING_PRDR_INT_SETUP_INTR_TMR_THOLD,
			 (srng->पूर्णांकr_समयr_thres_us >> 3));

	val |= FIELD_PREP(HAL_REO1_RING_PRDR_INT_SETUP_BATCH_COUNTER_THOLD,
			  (srng->पूर्णांकr_batch_cntr_thres_entries *
			   srng->entry_size));

	ath11k_hअगर_ग_लिखो32(ab,
			   reg_base + HAL_REO1_RING_PRODUCER_INT_SETUP_OFFSET(ab),
			   val);

	hp_addr = hal->rdp.paddr +
		  ((अचिन्हित दीर्घ)srng->u.dst_ring.hp_addr -
		   (अचिन्हित दीर्घ)hal->rdp.vaddr);
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_REO1_RING_HP_ADDR_LSB_OFFSET(ab),
			   hp_addr & HAL_ADDR_LSB_REG_MASK);
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_REO1_RING_HP_ADDR_MSB_OFFSET(ab),
			   hp_addr >> HAL_ADDR_MSB_REG_SHIFT);

	/* Initialize head and tail poपूर्णांकers to indicate ring is empty */
	reg_base = srng->hwreg_base[HAL_SRNG_REG_GRP_R2];
	ath11k_hअगर_ग_लिखो32(ab, reg_base, 0);
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_REO1_RING_TP_OFFSET(ab), 0);
	*srng->u.dst_ring.hp_addr = 0;

	reg_base = srng->hwreg_base[HAL_SRNG_REG_GRP_R0];
	val = 0;
	अगर (srng->flags & HAL_SRNG_FLAGS_DATA_TLV_SWAP)
		val |= HAL_REO1_RING_MISC_DATA_TLV_SWAP;
	अगर (srng->flags & HAL_SRNG_FLAGS_RING_PTR_SWAP)
		val |= HAL_REO1_RING_MISC_HOST_FW_SWAP;
	अगर (srng->flags & HAL_SRNG_FLAGS_MSI_SWAP)
		val |= HAL_REO1_RING_MISC_MSI_SWAP;
	val |= HAL_REO1_RING_MISC_SRNG_ENABLE;

	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_REO1_RING_MISC_OFFSET(ab), val);
पूर्ण

अटल व्योम ath11k_hal_srng_src_hw_init(काष्ठा ath11k_base *ab,
					काष्ठा hal_srng *srng)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	u32 val;
	u64 tp_addr;
	u32 reg_base;

	reg_base = srng->hwreg_base[HAL_SRNG_REG_GRP_R0];

	अगर (srng->flags & HAL_SRNG_FLAGS_MSI_INTR) अणु
		ath11k_hअगर_ग_लिखो32(ab, reg_base +
				   HAL_TCL1_RING_MSI1_BASE_LSB_OFFSET(ab),
				   srng->msi_addr);

		val = FIELD_PREP(HAL_TCL1_RING_MSI1_BASE_MSB_ADDR,
				 ((u64)srng->msi_addr >>
				  HAL_ADDR_MSB_REG_SHIFT)) |
		      HAL_TCL1_RING_MSI1_BASE_MSB_MSI1_ENABLE;
		ath11k_hअगर_ग_लिखो32(ab, reg_base +
				       HAL_TCL1_RING_MSI1_BASE_MSB_OFFSET(ab),
				   val);

		ath11k_hअगर_ग_लिखो32(ab, reg_base +
				       HAL_TCL1_RING_MSI1_DATA_OFFSET(ab),
				   srng->msi_data);
	पूर्ण

	ath11k_hअगर_ग_लिखो32(ab, reg_base, srng->ring_base_paddr);

	val = FIELD_PREP(HAL_TCL1_RING_BASE_MSB_RING_BASE_ADDR_MSB,
			 ((u64)srng->ring_base_paddr >>
			  HAL_ADDR_MSB_REG_SHIFT)) |
	      FIELD_PREP(HAL_TCL1_RING_BASE_MSB_RING_SIZE,
			 (srng->entry_size * srng->num_entries));
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_TCL1_RING_BASE_MSB_OFFSET(ab), val);

	val = FIELD_PREP(HAL_REO1_RING_ID_ENTRY_SIZE, srng->entry_size);
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_TCL1_RING_ID_OFFSET(ab), val);

	/* पूर्णांकerrupt setup */
	/* NOTE: IPQ8074 v2 requires the पूर्णांकerrupt समयr threshold in the
	 * unit of 8 usecs instead of 1 usec (as required by v1).
	 */
	val = FIELD_PREP(HAL_TCL1_RING_CONSR_INT_SETUP_IX0_INTR_TMR_THOLD,
			 srng->पूर्णांकr_समयr_thres_us);

	val |= FIELD_PREP(HAL_TCL1_RING_CONSR_INT_SETUP_IX0_BATCH_COUNTER_THOLD,
			  (srng->पूर्णांकr_batch_cntr_thres_entries *
			   srng->entry_size));

	ath11k_hअगर_ग_लिखो32(ab,
			   reg_base + HAL_TCL1_RING_CONSR_INT_SETUP_IX0_OFFSET(ab),
			   val);

	val = 0;
	अगर (srng->flags & HAL_SRNG_FLAGS_LOW_THRESH_INTR_EN) अणु
		val |= FIELD_PREP(HAL_TCL1_RING_CONSR_INT_SETUP_IX1_LOW_THOLD,
				  srng->u.src_ring.low_threshold);
	पूर्ण
	ath11k_hअगर_ग_लिखो32(ab,
			   reg_base + HAL_TCL1_RING_CONSR_INT_SETUP_IX1_OFFSET(ab),
			   val);

	अगर (srng->ring_id != HAL_SRNG_RING_ID_WBM_IDLE_LINK) अणु
		tp_addr = hal->rdp.paddr +
			  ((अचिन्हित दीर्घ)srng->u.src_ring.tp_addr -
			   (अचिन्हित दीर्घ)hal->rdp.vaddr);
		ath11k_hअगर_ग_लिखो32(ab,
				   reg_base + HAL_TCL1_RING_TP_ADDR_LSB_OFFSET(ab),
				   tp_addr & HAL_ADDR_LSB_REG_MASK);
		ath11k_hअगर_ग_लिखो32(ab,
				   reg_base + HAL_TCL1_RING_TP_ADDR_MSB_OFFSET(ab),
				   tp_addr >> HAL_ADDR_MSB_REG_SHIFT);
	पूर्ण

	/* Initialize head and tail poपूर्णांकers to indicate ring is empty */
	reg_base = srng->hwreg_base[HAL_SRNG_REG_GRP_R2];
	ath11k_hअगर_ग_लिखो32(ab, reg_base, 0);
	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_TCL1_RING_TP_OFFSET, 0);
	*srng->u.src_ring.tp_addr = 0;

	reg_base = srng->hwreg_base[HAL_SRNG_REG_GRP_R0];
	val = 0;
	अगर (srng->flags & HAL_SRNG_FLAGS_DATA_TLV_SWAP)
		val |= HAL_TCL1_RING_MISC_DATA_TLV_SWAP;
	अगर (srng->flags & HAL_SRNG_FLAGS_RING_PTR_SWAP)
		val |= HAL_TCL1_RING_MISC_HOST_FW_SWAP;
	अगर (srng->flags & HAL_SRNG_FLAGS_MSI_SWAP)
		val |= HAL_TCL1_RING_MISC_MSI_SWAP;

	/* Loop count is not used क्रम SRC rings */
	val |= HAL_TCL1_RING_MISC_MSI_LOOPCNT_DISABLE;

	val |= HAL_TCL1_RING_MISC_SRNG_ENABLE;

	ath11k_hअगर_ग_लिखो32(ab, reg_base + HAL_TCL1_RING_MISC_OFFSET(ab), val);
पूर्ण

अटल व्योम ath11k_hal_srng_hw_init(काष्ठा ath11k_base *ab,
				    काष्ठा hal_srng *srng)
अणु
	अगर (srng->ring_dir == HAL_SRNG_सूची_SRC)
		ath11k_hal_srng_src_hw_init(ab, srng);
	अन्यथा
		ath11k_hal_srng_dst_hw_init(ab, srng);
पूर्ण

अटल पूर्णांक ath11k_hal_srng_get_ring_id(काष्ठा ath11k_base *ab,
				       क्रमागत hal_ring_type type,
				       पूर्णांक ring_num, पूर्णांक mac_id)
अणु
	काष्ठा hal_srng_config *srng_config = &ab->hal.srng_config[type];
	पूर्णांक ring_id;

	अगर (ring_num >= srng_config->max_rings) अणु
		ath11k_warn(ab, "invalid ring number :%d\n", ring_num);
		वापस -EINVAL;
	पूर्ण

	ring_id = srng_config->start_ring_id + ring_num;
	अगर (srng_config->lmac_ring)
		ring_id += mac_id * HAL_SRNG_RINGS_PER_LMAC;

	अगर (WARN_ON(ring_id >= HAL_SRNG_RING_ID_MAX))
		वापस -EINVAL;

	वापस ring_id;
पूर्ण

पूर्णांक ath11k_hal_srng_get_entrysize(काष्ठा ath11k_base *ab, u32 ring_type)
अणु
	काष्ठा hal_srng_config *srng_config;

	अगर (WARN_ON(ring_type >= HAL_MAX_RING_TYPES))
		वापस -EINVAL;

	srng_config = &ab->hal.srng_config[ring_type];

	वापस (srng_config->entry_size << 2);
पूर्ण

पूर्णांक ath11k_hal_srng_get_max_entries(काष्ठा ath11k_base *ab, u32 ring_type)
अणु
	काष्ठा hal_srng_config *srng_config;

	अगर (WARN_ON(ring_type >= HAL_MAX_RING_TYPES))
		वापस -EINVAL;

	srng_config = &ab->hal.srng_config[ring_type];

	वापस (srng_config->max_size / srng_config->entry_size);
पूर्ण

व्योम ath11k_hal_srng_get_params(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
				काष्ठा hal_srng_params *params)
अणु
	params->ring_base_paddr = srng->ring_base_paddr;
	params->ring_base_vaddr = srng->ring_base_vaddr;
	params->num_entries = srng->num_entries;
	params->पूर्णांकr_समयr_thres_us = srng->पूर्णांकr_समयr_thres_us;
	params->पूर्णांकr_batch_cntr_thres_entries =
		srng->पूर्णांकr_batch_cntr_thres_entries;
	params->low_threshold = srng->u.src_ring.low_threshold;
	params->msi_addr = srng->msi_addr;
	params->msi_data = srng->msi_data;
	params->flags = srng->flags;
पूर्ण

dma_addr_t ath11k_hal_srng_get_hp_addr(काष्ठा ath11k_base *ab,
				       काष्ठा hal_srng *srng)
अणु
	अगर (!(srng->flags & HAL_SRNG_FLAGS_LMAC_RING))
		वापस 0;

	अगर (srng->ring_dir == HAL_SRNG_सूची_SRC)
		वापस ab->hal.wrp.paddr +
		       ((अचिन्हित दीर्घ)srng->u.src_ring.hp_addr -
			(अचिन्हित दीर्घ)ab->hal.wrp.vaddr);
	अन्यथा
		वापस ab->hal.rdp.paddr +
		       ((अचिन्हित दीर्घ)srng->u.dst_ring.hp_addr -
			 (अचिन्हित दीर्घ)ab->hal.rdp.vaddr);
पूर्ण

dma_addr_t ath11k_hal_srng_get_tp_addr(काष्ठा ath11k_base *ab,
				       काष्ठा hal_srng *srng)
अणु
	अगर (!(srng->flags & HAL_SRNG_FLAGS_LMAC_RING))
		वापस 0;

	अगर (srng->ring_dir == HAL_SRNG_सूची_SRC)
		वापस ab->hal.rdp.paddr +
		       ((अचिन्हित दीर्घ)srng->u.src_ring.tp_addr -
			(अचिन्हित दीर्घ)ab->hal.rdp.vaddr);
	अन्यथा
		वापस ab->hal.wrp.paddr +
		       ((अचिन्हित दीर्घ)srng->u.dst_ring.tp_addr -
			(अचिन्हित दीर्घ)ab->hal.wrp.vaddr);
पूर्ण

u32 ath11k_hal_ce_get_desc_size(क्रमागत hal_ce_desc type)
अणु
	चयन (type) अणु
	हाल HAL_CE_DESC_SRC:
		वापस माप(काष्ठा hal_ce_srng_src_desc);
	हाल HAL_CE_DESC_DST:
		वापस माप(काष्ठा hal_ce_srng_dest_desc);
	हाल HAL_CE_DESC_DST_STATUS:
		वापस माप(काष्ठा hal_ce_srng_dst_status_desc);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath11k_hal_ce_src_set_desc(व्योम *buf, dma_addr_t paddr, u32 len, u32 id,
				u8 byte_swap_data)
अणु
	काष्ठा hal_ce_srng_src_desc *desc = (काष्ठा hal_ce_srng_src_desc *)buf;

	desc->buffer_addr_low = paddr & HAL_ADDR_LSB_REG_MASK;
	desc->buffer_addr_info =
		FIELD_PREP(HAL_CE_SRC_DESC_ADDR_INFO_ADDR_HI,
			   ((u64)paddr >> HAL_ADDR_MSB_REG_SHIFT)) |
		FIELD_PREP(HAL_CE_SRC_DESC_ADDR_INFO_BYTE_SWAP,
			   byte_swap_data) |
		FIELD_PREP(HAL_CE_SRC_DESC_ADDR_INFO_GATHER, 0) |
		FIELD_PREP(HAL_CE_SRC_DESC_ADDR_INFO_LEN, len);
	desc->meta_info = FIELD_PREP(HAL_CE_SRC_DESC_META_INFO_DATA, id);
पूर्ण

व्योम ath11k_hal_ce_dst_set_desc(व्योम *buf, dma_addr_t paddr)
अणु
	काष्ठा hal_ce_srng_dest_desc *desc =
		(काष्ठा hal_ce_srng_dest_desc *)buf;

	desc->buffer_addr_low = paddr & HAL_ADDR_LSB_REG_MASK;
	desc->buffer_addr_info =
		FIELD_PREP(HAL_CE_DEST_DESC_ADDR_INFO_ADDR_HI,
			   ((u64)paddr >> HAL_ADDR_MSB_REG_SHIFT));
पूर्ण

u32 ath11k_hal_ce_dst_status_get_length(व्योम *buf)
अणु
	काष्ठा hal_ce_srng_dst_status_desc *desc =
		(काष्ठा hal_ce_srng_dst_status_desc *)buf;
	u32 len;

	len = FIELD_GET(HAL_CE_DST_STATUS_DESC_FLAGS_LEN, desc->flags);
	desc->flags &= ~HAL_CE_DST_STATUS_DESC_FLAGS_LEN;

	वापस len;
पूर्ण

व्योम ath11k_hal_set_link_desc_addr(काष्ठा hal_wbm_link_desc *desc, u32 cookie,
				   dma_addr_t paddr)
अणु
	desc->buf_addr_info.info0 = FIELD_PREP(BUFFER_ADDR_INFO0_ADDR,
					       (paddr & HAL_ADDR_LSB_REG_MASK));
	desc->buf_addr_info.info1 = FIELD_PREP(BUFFER_ADDR_INFO1_ADDR,
					       ((u64)paddr >> HAL_ADDR_MSB_REG_SHIFT)) |
				    FIELD_PREP(BUFFER_ADDR_INFO1_RET_BUF_MGR, 1) |
				    FIELD_PREP(BUFFER_ADDR_INFO1_SW_COOKIE, cookie);
पूर्ण

u32 *ath11k_hal_srng_dst_peek(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng)
अणु
	lockdep_निश्चित_held(&srng->lock);

	अगर (srng->u.dst_ring.tp != srng->u.dst_ring.cached_hp)
		वापस (srng->ring_base_vaddr + srng->u.dst_ring.tp);

	वापस शून्य;
पूर्ण

u32 *ath11k_hal_srng_dst_get_next_entry(काष्ठा ath11k_base *ab,
					काष्ठा hal_srng *srng)
अणु
	u32 *desc;

	lockdep_निश्चित_held(&srng->lock);

	अगर (srng->u.dst_ring.tp == srng->u.dst_ring.cached_hp)
		वापस शून्य;

	desc = srng->ring_base_vaddr + srng->u.dst_ring.tp;

	srng->u.dst_ring.tp = (srng->u.dst_ring.tp + srng->entry_size) %
			      srng->ring_size;

	वापस desc;
पूर्ण

पूर्णांक ath11k_hal_srng_dst_num_मुक्त(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
				 bool sync_hw_ptr)
अणु
	u32 tp, hp;

	lockdep_निश्चित_held(&srng->lock);

	tp = srng->u.dst_ring.tp;

	अगर (sync_hw_ptr) अणु
		hp = *srng->u.dst_ring.hp_addr;
		srng->u.dst_ring.cached_hp = hp;
	पूर्ण अन्यथा अणु
		hp = srng->u.dst_ring.cached_hp;
	पूर्ण

	अगर (hp >= tp)
		वापस (hp - tp) / srng->entry_size;
	अन्यथा
		वापस (srng->ring_size - tp + hp) / srng->entry_size;
पूर्ण

/* Returns number of available entries in src ring */
पूर्णांक ath11k_hal_srng_src_num_मुक्त(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
				 bool sync_hw_ptr)
अणु
	u32 tp, hp;

	lockdep_निश्चित_held(&srng->lock);

	hp = srng->u.src_ring.hp;

	अगर (sync_hw_ptr) अणु
		tp = *srng->u.src_ring.tp_addr;
		srng->u.src_ring.cached_tp = tp;
	पूर्ण अन्यथा अणु
		tp = srng->u.src_ring.cached_tp;
	पूर्ण

	अगर (tp > hp)
		वापस ((tp - hp) / srng->entry_size) - 1;
	अन्यथा
		वापस ((srng->ring_size - hp + tp) / srng->entry_size) - 1;
पूर्ण

u32 *ath11k_hal_srng_src_get_next_entry(काष्ठा ath11k_base *ab,
					काष्ठा hal_srng *srng)
अणु
	u32 *desc;
	u32 next_hp;

	lockdep_निश्चित_held(&srng->lock);

	/* TODO: Using % is expensive, but we have to करो this since size of some
	 * SRNG rings is not घातer of 2 (due to descriptor sizes). Need to see
	 * अगर separate function is defined क्रम rings having घातer of 2 ring size
	 * (TCL2SW, REO2SW, SW2RXDMA and CE rings) so that we can aव्योम the
	 * overhead of % by using mask (with &).
	 */
	next_hp = (srng->u.src_ring.hp + srng->entry_size) % srng->ring_size;

	अगर (next_hp == srng->u.src_ring.cached_tp)
		वापस शून्य;

	desc = srng->ring_base_vaddr + srng->u.src_ring.hp;
	srng->u.src_ring.hp = next_hp;

	/* TODO: Reap functionality is not used by all rings. If particular
	 * ring करोes not use reap functionality, we need not update reap_hp
	 * with next_hp poपूर्णांकer. Need to make sure a separate function is used
	 * beक्रमe करोing any optimization by removing below code updating
	 * reap_hp.
	 */
	srng->u.src_ring.reap_hp = next_hp;

	वापस desc;
पूर्ण

u32 *ath11k_hal_srng_src_reap_next(काष्ठा ath11k_base *ab,
				   काष्ठा hal_srng *srng)
अणु
	u32 *desc;
	u32 next_reap_hp;

	lockdep_निश्चित_held(&srng->lock);

	next_reap_hp = (srng->u.src_ring.reap_hp + srng->entry_size) %
		       srng->ring_size;

	अगर (next_reap_hp == srng->u.src_ring.cached_tp)
		वापस शून्य;

	desc = srng->ring_base_vaddr + next_reap_hp;
	srng->u.src_ring.reap_hp = next_reap_hp;

	वापस desc;
पूर्ण

u32 *ath11k_hal_srng_src_get_next_reaped(काष्ठा ath11k_base *ab,
					 काष्ठा hal_srng *srng)
अणु
	u32 *desc;

	lockdep_निश्चित_held(&srng->lock);

	अगर (srng->u.src_ring.hp == srng->u.src_ring.reap_hp)
		वापस शून्य;

	desc = srng->ring_base_vaddr + srng->u.src_ring.hp;
	srng->u.src_ring.hp = (srng->u.src_ring.hp + srng->entry_size) %
			      srng->ring_size;

	वापस desc;
पूर्ण

u32 *ath11k_hal_srng_src_peek(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng)
अणु
	lockdep_निश्चित_held(&srng->lock);

	अगर (((srng->u.src_ring.hp + srng->entry_size) % srng->ring_size) ==
	    srng->u.src_ring.cached_tp)
		वापस शून्य;

	वापस srng->ring_base_vaddr + srng->u.src_ring.hp;
पूर्ण

व्योम ath11k_hal_srng_access_begin(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng)
अणु
	lockdep_निश्चित_held(&srng->lock);

	अगर (srng->ring_dir == HAL_SRNG_सूची_SRC)
		srng->u.src_ring.cached_tp =
			*(अस्थिर u32 *)srng->u.src_ring.tp_addr;
	अन्यथा
		srng->u.dst_ring.cached_hp = *srng->u.dst_ring.hp_addr;
पूर्ण

/* Update cached ring head/tail poपूर्णांकers to HW. ath11k_hal_srng_access_begin()
 * should have been called beक्रमe this.
 */
व्योम ath11k_hal_srng_access_end(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng)
अणु
	lockdep_निश्चित_held(&srng->lock);

	/* TODO: See अगर we need a ग_लिखो memory barrier here */
	अगर (srng->flags & HAL_SRNG_FLAGS_LMAC_RING) अणु
		/* For LMAC rings, ring poपूर्णांकer updates are करोne through FW and
		 * hence written to a shared memory location that is पढ़ो by FW
		 */
		अगर (srng->ring_dir == HAL_SRNG_सूची_SRC) अणु
			srng->u.src_ring.last_tp =
				*(अस्थिर u32 *)srng->u.src_ring.tp_addr;
			*srng->u.src_ring.hp_addr = srng->u.src_ring.hp;
		पूर्ण अन्यथा अणु
			srng->u.dst_ring.last_hp = *srng->u.dst_ring.hp_addr;
			*srng->u.dst_ring.tp_addr = srng->u.dst_ring.tp;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (srng->ring_dir == HAL_SRNG_सूची_SRC) अणु
			srng->u.src_ring.last_tp =
				*(अस्थिर u32 *)srng->u.src_ring.tp_addr;
			ath11k_hअगर_ग_लिखो32(ab,
					   (अचिन्हित दीर्घ)srng->u.src_ring.hp_addr -
					   (अचिन्हित दीर्घ)ab->mem,
					   srng->u.src_ring.hp);
		पूर्ण अन्यथा अणु
			srng->u.dst_ring.last_hp = *srng->u.dst_ring.hp_addr;
			ath11k_hअगर_ग_लिखो32(ab,
					   (अचिन्हित दीर्घ)srng->u.dst_ring.tp_addr -
					   (अचिन्हित दीर्घ)ab->mem,
					   srng->u.dst_ring.tp);
		पूर्ण
	पूर्ण

	srng->बारtamp = jअगरfies;
पूर्ण

व्योम ath11k_hal_setup_link_idle_list(काष्ठा ath11k_base *ab,
				     काष्ठा hal_wbm_idle_scatter_list *sbuf,
				     u32 nsbufs, u32 tot_link_desc,
				     u32 end_offset)
अणु
	काष्ठा ath11k_buffer_addr *link_addr;
	पूर्णांक i;
	u32 reg_scatter_buf_sz = HAL_WBM_IDLE_SCATTER_BUF_SIZE / 64;

	link_addr = (व्योम *)sbuf[0].vaddr + HAL_WBM_IDLE_SCATTER_BUF_SIZE;

	क्रम (i = 1; i < nsbufs; i++) अणु
		link_addr->info0 = sbuf[i].paddr & HAL_ADDR_LSB_REG_MASK;
		link_addr->info1 = FIELD_PREP(
				HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_39_32,
				(u64)sbuf[i].paddr >> HAL_ADDR_MSB_REG_SHIFT) |
				FIELD_PREP(
				HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_MATCH_TAG,
				BASE_ADDR_MATCH_TAG_VAL);

		link_addr = (व्योम *)sbuf[i].vaddr +
			     HAL_WBM_IDLE_SCATTER_BUF_SIZE;
	पूर्ण

	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM_R0_IDLE_LIST_CONTROL_ADDR,
			   FIELD_PREP(HAL_WBM_SCATTER_BUFFER_SIZE, reg_scatter_buf_sz) |
			   FIELD_PREP(HAL_WBM_LINK_DESC_IDLE_LIST_MODE, 0x1));
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM_R0_IDLE_LIST_SIZE_ADDR,
			   FIELD_PREP(HAL_WBM_SCATTER_RING_SIZE_OF_IDLE_LINK_DESC_LIST,
				      reg_scatter_buf_sz * nsbufs));
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_RING_BASE_LSB,
			   FIELD_PREP(BUFFER_ADDR_INFO0_ADDR,
				      sbuf[0].paddr & HAL_ADDR_LSB_REG_MASK));
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_RING_BASE_MSB,
			   FIELD_PREP(
				HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_39_32,
				(u64)sbuf[0].paddr >> HAL_ADDR_MSB_REG_SHIFT) |
				FIELD_PREP(
				HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_MATCH_TAG,
				BASE_ADDR_MATCH_TAG_VAL));

	/* Setup head and tail poपूर्णांकers क्रम the idle list */
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_DESC_PTR_HEAD_INFO_IX0,
			   FIELD_PREP(BUFFER_ADDR_INFO0_ADDR,
				      sbuf[nsbufs - 1].paddr));
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_DESC_PTR_HEAD_INFO_IX1,
			   FIELD_PREP(
				HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_39_32,
				((u64)sbuf[nsbufs - 1].paddr >>
				 HAL_ADDR_MSB_REG_SHIFT)) |
			   FIELD_PREP(HAL_WBM_SCATTERED_DESC_HEAD_P_OFFSET_IX1,
				      (end_offset >> 2)));
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_DESC_PTR_HEAD_INFO_IX0,
			   FIELD_PREP(BUFFER_ADDR_INFO0_ADDR,
				      sbuf[0].paddr));

	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_DESC_PTR_TAIL_INFO_IX0,
			   FIELD_PREP(BUFFER_ADDR_INFO0_ADDR,
				      sbuf[0].paddr));
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_DESC_PTR_TAIL_INFO_IX1,
			   FIELD_PREP(
				HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_39_32,
				((u64)sbuf[0].paddr >> HAL_ADDR_MSB_REG_SHIFT)) |
			   FIELD_PREP(HAL_WBM_SCATTERED_DESC_TAIL_P_OFFSET_IX1,
				      0));
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_SCATTERED_DESC_PTR_HP_ADDR,
			   2 * tot_link_desc);

	/* Enable the SRNG */
	ath11k_hअगर_ग_लिखो32(ab,
			   HAL_SEQ_WCSS_UMAC_WBM_REG +
			   HAL_WBM_IDLE_LINK_RING_MISC_ADDR(ab), 0x40);
पूर्ण

पूर्णांक ath11k_hal_srng_setup(काष्ठा ath11k_base *ab, क्रमागत hal_ring_type type,
			  पूर्णांक ring_num, पूर्णांक mac_id,
			  काष्ठा hal_srng_params *params)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	काष्ठा hal_srng_config *srng_config = &ab->hal.srng_config[type];
	काष्ठा hal_srng *srng;
	पूर्णांक ring_id;
	u32 lmac_idx;
	पूर्णांक i;
	u32 reg_base;

	ring_id = ath11k_hal_srng_get_ring_id(ab, type, ring_num, mac_id);
	अगर (ring_id < 0)
		वापस ring_id;

	srng = &hal->srng_list[ring_id];

	srng->ring_id = ring_id;
	srng->ring_dir = srng_config->ring_dir;
	srng->ring_base_paddr = params->ring_base_paddr;
	srng->ring_base_vaddr = params->ring_base_vaddr;
	srng->entry_size = srng_config->entry_size;
	srng->num_entries = params->num_entries;
	srng->ring_size = srng->entry_size * srng->num_entries;
	srng->पूर्णांकr_batch_cntr_thres_entries =
				params->पूर्णांकr_batch_cntr_thres_entries;
	srng->पूर्णांकr_समयr_thres_us = params->पूर्णांकr_समयr_thres_us;
	srng->flags = params->flags;
	srng->msi_addr = params->msi_addr;
	srng->msi_data = params->msi_data;
	srng->initialized = 1;
	spin_lock_init(&srng->lock);

	क्रम (i = 0; i < HAL_SRNG_NUM_REG_GRP; i++) अणु
		srng->hwreg_base[i] = srng_config->reg_start[i] +
				      (ring_num * srng_config->reg_size[i]);
	पूर्ण

	स_रखो(srng->ring_base_vaddr, 0,
	       (srng->entry_size * srng->num_entries) << 2);

	/* TODO: Add comments on these swap configurations */
	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		srng->flags |= HAL_SRNG_FLAGS_MSI_SWAP | HAL_SRNG_FLAGS_DATA_TLV_SWAP |
			       HAL_SRNG_FLAGS_RING_PTR_SWAP;

	reg_base = srng->hwreg_base[HAL_SRNG_REG_GRP_R2];

	अगर (srng->ring_dir == HAL_SRNG_सूची_SRC) अणु
		srng->u.src_ring.hp = 0;
		srng->u.src_ring.cached_tp = 0;
		srng->u.src_ring.reap_hp = srng->ring_size - srng->entry_size;
		srng->u.src_ring.tp_addr = (व्योम *)(hal->rdp.vaddr + ring_id);
		srng->u.src_ring.low_threshold = params->low_threshold *
						 srng->entry_size;
		अगर (srng_config->lmac_ring) अणु
			lmac_idx = ring_id - HAL_SRNG_RING_ID_LMAC1_ID_START;
			srng->u.src_ring.hp_addr = (व्योम *)(hal->wrp.vaddr +
						   lmac_idx);
			srng->flags |= HAL_SRNG_FLAGS_LMAC_RING;
		पूर्ण अन्यथा अणु
			अगर (!ab->hw_params.supports_shaकरोw_regs)
				srng->u.src_ring.hp_addr =
				(u32 *)((अचिन्हित दीर्घ)ab->mem + reg_base);
			अन्यथा
				ath11k_dbg(ab, ATH11k_DBG_HAL,
					   "hal type %d ring_num %d reg_base 0x%x shadow 0x%lx\n",
					   type, ring_num,
					   reg_base,
					   (अचिन्हित दीर्घ)srng->u.src_ring.hp_addr -
					   (अचिन्हित दीर्घ)ab->mem);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* During initialization loop count in all the descriptors
		 * will be set to zero, and HW will set it to 1 on completing
		 * descriptor update in first loop, and increments it by 1 on
		 * subsequent loops (loop count wraps around after reaching
		 * 0xffff). The 'loop_cnt' in SW ring state is the expected
		 * loop count in descriptors updated by HW (to be processed
		 * by SW).
		 */
		srng->u.dst_ring.loop_cnt = 1;
		srng->u.dst_ring.tp = 0;
		srng->u.dst_ring.cached_hp = 0;
		srng->u.dst_ring.hp_addr = (व्योम *)(hal->rdp.vaddr + ring_id);
		अगर (srng_config->lmac_ring) अणु
			/* For LMAC rings, tail poपूर्णांकer updates will be करोne
			 * through FW by writing to a shared memory location
			 */
			lmac_idx = ring_id - HAL_SRNG_RING_ID_LMAC1_ID_START;
			srng->u.dst_ring.tp_addr = (व्योम *)(hal->wrp.vaddr +
						   lmac_idx);
			srng->flags |= HAL_SRNG_FLAGS_LMAC_RING;
		पूर्ण अन्यथा अणु
			अगर (!ab->hw_params.supports_shaकरोw_regs)
				srng->u.dst_ring.tp_addr =
				(u32 *)((अचिन्हित दीर्घ)ab->mem + reg_base +
					(HAL_REO1_RING_TP(ab) - HAL_REO1_RING_HP(ab)));
			अन्यथा
				ath11k_dbg(ab, ATH11k_DBG_HAL,
					   "type %d ring_num %d target_reg 0x%x shadow 0x%lx\n",
					   type, ring_num,
					   reg_base + (HAL_REO1_RING_TP(ab) -
						       HAL_REO1_RING_HP(ab)),
					   (अचिन्हित दीर्घ)srng->u.dst_ring.tp_addr -
					   (अचिन्हित दीर्घ)ab->mem);
		पूर्ण
	पूर्ण

	अगर (srng_config->lmac_ring)
		वापस ring_id;

	ath11k_hal_srng_hw_init(ab, srng);

	अगर (type == HAL_CE_DST) अणु
		srng->u.dst_ring.max_buffer_length = params->max_buffer_len;
		ath11k_hal_ce_dst_setup(ab, srng, ring_num);
	पूर्ण

	वापस ring_id;
पूर्ण

अटल व्योम ath11k_hal_srng_update_hp_tp_addr(काष्ठा ath11k_base *ab,
					      पूर्णांक shaकरोw_cfg_idx,
					  क्रमागत hal_ring_type ring_type,
					  पूर्णांक ring_num)
अणु
	काष्ठा hal_srng *srng;
	काष्ठा ath11k_hal *hal = &ab->hal;
	पूर्णांक ring_id;
	काष्ठा hal_srng_config *srng_config = &hal->srng_config[ring_type];

	ring_id = ath11k_hal_srng_get_ring_id(ab, ring_type, ring_num, 0);
	अगर (ring_id < 0)
		वापस;

	srng = &hal->srng_list[ring_id];

	अगर (srng_config->ring_dir == HAL_SRNG_सूची_DST)
		srng->u.dst_ring.tp_addr = (u32 *)(HAL_SHADOW_REG(shaकरोw_cfg_idx) +
						   (अचिन्हित दीर्घ)ab->mem);
	अन्यथा
		srng->u.src_ring.hp_addr = (u32 *)(HAL_SHADOW_REG(shaकरोw_cfg_idx) +
						   (अचिन्हित दीर्घ)ab->mem);
पूर्ण

पूर्णांक ath11k_hal_srng_update_shaकरोw_config(काष्ठा ath11k_base *ab,
					 क्रमागत hal_ring_type ring_type,
					 पूर्णांक ring_num)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	काष्ठा hal_srng_config *srng_config = &hal->srng_config[ring_type];
	पूर्णांक shaकरोw_cfg_idx = hal->num_shaकरोw_reg_configured;
	u32 target_reg;

	अगर (shaकरोw_cfg_idx >= HAL_SHADOW_NUM_REGS)
		वापस -EINVAL;

	hal->num_shaकरोw_reg_configured++;

	target_reg = srng_config->reg_start[HAL_HP_OFFSET_IN_REG_START];
	target_reg += srng_config->reg_size[HAL_HP_OFFSET_IN_REG_START] *
		ring_num;

	/* For destination ring, shaकरोw the TP */
	अगर (srng_config->ring_dir == HAL_SRNG_सूची_DST)
		target_reg += HAL_OFFSET_FROM_HP_TO_TP;

	hal->shaकरोw_reg_addr[shaकरोw_cfg_idx] = target_reg;

	/* update hp/tp addr to hal काष्ठाure*/
	ath11k_hal_srng_update_hp_tp_addr(ab, shaकरोw_cfg_idx, ring_type,
					  ring_num);

	ath11k_dbg(ab, ATH11k_DBG_HAL,
		   "target_reg %x, shadow reg 0x%x shadow_idx 0x%x, ring_type %d, ring num %d",
		  target_reg,
		  HAL_SHADOW_REG(shaकरोw_cfg_idx),
		  shaकरोw_cfg_idx,
		  ring_type, ring_num);

	वापस 0;
पूर्ण

व्योम ath11k_hal_srng_shaकरोw_config(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	पूर्णांक ring_type, ring_num;

	/* update all the non-CE srngs. */
	क्रम (ring_type = 0; ring_type < HAL_MAX_RING_TYPES; ring_type++) अणु
		काष्ठा hal_srng_config *srng_config = &hal->srng_config[ring_type];

		अगर (ring_type == HAL_CE_SRC ||
		    ring_type == HAL_CE_DST ||
			ring_type == HAL_CE_DST_STATUS)
			जारी;

		अगर (srng_config->lmac_ring)
			जारी;

		क्रम (ring_num = 0; ring_num < srng_config->max_rings; ring_num++)
			ath11k_hal_srng_update_shaकरोw_config(ab, ring_type, ring_num);
	पूर्ण
पूर्ण

व्योम ath11k_hal_srng_get_shaकरोw_config(काष्ठा ath11k_base *ab,
				       u32 **cfg, u32 *len)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;

	*len = hal->num_shaकरोw_reg_configured;
	*cfg = hal->shaकरोw_reg_addr;
पूर्ण

व्योम ath11k_hal_srng_shaकरोw_update_hp_tp(काष्ठा ath11k_base *ab,
					 काष्ठा hal_srng *srng)
अणु
	lockdep_निश्चित_held(&srng->lock);

	/* check whether the ring is emptry. Update the shaकरोw
	 * HP only when then ring isn't' empty.
	 */
	अगर (srng->ring_dir == HAL_SRNG_सूची_SRC &&
	    *srng->u.src_ring.tp_addr != srng->u.src_ring.hp)
		ath11k_hal_srng_access_end(ab, srng);
पूर्ण

अटल पूर्णांक ath11k_hal_srng_create_config(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	काष्ठा hal_srng_config *s;

	hal->srng_config = kmemdup(hw_srng_config_ढाँचा,
				   माप(hw_srng_config_ढाँचा),
				   GFP_KERNEL);
	अगर (!hal->srng_config)
		वापस -ENOMEM;

	s = &hal->srng_config[HAL_REO_DST];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO1_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO1_RING_HP(ab);
	s->reg_size[0] = HAL_REO2_RING_BASE_LSB(ab) - HAL_REO1_RING_BASE_LSB(ab);
	s->reg_size[1] = HAL_REO2_RING_HP(ab) - HAL_REO1_RING_HP(ab);

	s = &hal->srng_config[HAL_REO_EXCEPTION];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO_TCL_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO_TCL_RING_HP(ab);

	s = &hal->srng_config[HAL_REO_REINJECT];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_SW2REO_RING_BASE_LSB;
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_SW2REO_RING_HP;

	s = &hal->srng_config[HAL_REO_CMD];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO_CMD_RING_BASE_LSB;
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO_CMD_HP;

	s = &hal->srng_config[HAL_REO_STATUS];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO_STATUS_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_REO_REG + HAL_REO_STATUS_HP(ab);

	s = &hal->srng_config[HAL_TCL_DATA];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_TCL_REG + HAL_TCL1_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_TCL_REG + HAL_TCL1_RING_HP;
	s->reg_size[0] = HAL_TCL2_RING_BASE_LSB(ab) - HAL_TCL1_RING_BASE_LSB(ab);
	s->reg_size[1] = HAL_TCL2_RING_HP - HAL_TCL1_RING_HP;

	s = &hal->srng_config[HAL_TCL_CMD];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_TCL_REG + HAL_TCL_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_TCL_REG + HAL_TCL_RING_HP;

	s = &hal->srng_config[HAL_TCL_STATUS];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_TCL_REG + HAL_TCL_STATUS_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_TCL_REG + HAL_TCL_STATUS_RING_HP;

	s = &hal->srng_config[HAL_CE_SRC];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_CE0_SRC_REG(ab) + HAL_CE_DST_RING_BASE_LSB;
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_CE0_SRC_REG(ab) + HAL_CE_DST_RING_HP;
	s->reg_size[0] = HAL_SEQ_WCSS_UMAC_CE1_SRC_REG(ab) -
		HAL_SEQ_WCSS_UMAC_CE0_SRC_REG(ab);
	s->reg_size[1] = HAL_SEQ_WCSS_UMAC_CE1_SRC_REG(ab) -
		HAL_SEQ_WCSS_UMAC_CE0_SRC_REG(ab);

	s = &hal->srng_config[HAL_CE_DST];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab) + HAL_CE_DST_RING_BASE_LSB;
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab) + HAL_CE_DST_RING_HP;
	s->reg_size[0] = HAL_SEQ_WCSS_UMAC_CE1_DST_REG(ab) -
		HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab);
	s->reg_size[1] = HAL_SEQ_WCSS_UMAC_CE1_DST_REG(ab) -
		HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab);

	s = &hal->srng_config[HAL_CE_DST_STATUS];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab) +
		HAL_CE_DST_STATUS_RING_BASE_LSB;
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab) + HAL_CE_DST_STATUS_RING_HP;
	s->reg_size[0] = HAL_SEQ_WCSS_UMAC_CE1_DST_REG(ab) -
		HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab);
	s->reg_size[1] = HAL_SEQ_WCSS_UMAC_CE1_DST_REG(ab) -
		HAL_SEQ_WCSS_UMAC_CE0_DST_REG(ab);

	s = &hal->srng_config[HAL_WBM_IDLE_LINK];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM_IDLE_LINK_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM_IDLE_LINK_RING_HP;

	s = &hal->srng_config[HAL_SW2WBM_RELEASE];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM_RELEASE_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM_RELEASE_RING_HP;

	s = &hal->srng_config[HAL_WBM2SW_RELEASE];
	s->reg_start[0] = HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM0_RELEASE_RING_BASE_LSB(ab);
	s->reg_start[1] = HAL_SEQ_WCSS_UMAC_WBM_REG + HAL_WBM0_RELEASE_RING_HP;
	s->reg_size[0] = HAL_WBM1_RELEASE_RING_BASE_LSB(ab) -
		HAL_WBM0_RELEASE_RING_BASE_LSB(ab);
	s->reg_size[1] = HAL_WBM1_RELEASE_RING_HP - HAL_WBM0_RELEASE_RING_HP;

	वापस 0;
पूर्ण

पूर्णांक ath11k_hal_srng_init(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	पूर्णांक ret;

	स_रखो(hal, 0, माप(*hal));

	ret = ath11k_hal_srng_create_config(ab);
	अगर (ret)
		जाओ err_hal;

	ret = ath11k_hal_alloc_cont_rdp(ab);
	अगर (ret)
		जाओ err_hal;

	ret = ath11k_hal_alloc_cont_wrp(ab);
	अगर (ret)
		जाओ err_मुक्त_cont_rdp;

	वापस 0;

err_मुक्त_cont_rdp:
	ath11k_hal_मुक्त_cont_rdp(ab);

err_hal:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ath11k_hal_srng_init);

व्योम ath11k_hal_srng_deinit(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;

	ath11k_hal_मुक्त_cont_rdp(ab);
	ath11k_hal_मुक्त_cont_wrp(ab);
	kमुक्त(hal->srng_config);
पूर्ण
EXPORT_SYMBOL(ath11k_hal_srng_deinit);

व्योम ath11k_hal_dump_srng_stats(काष्ठा ath11k_base *ab)
अणु
	काष्ठा hal_srng *srng;
	काष्ठा ath11k_ext_irq_grp *irq_grp;
	काष्ठा ath11k_ce_pipe *ce_pipe;
	पूर्णांक i;

	ath11k_err(ab, "Last interrupt received for each CE:\n");
	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		ce_pipe = &ab->ce.ce_pipe[i];

		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		ath11k_err(ab, "CE_id %d pipe_num %d %ums before\n",
			   i, ce_pipe->pipe_num,
			   jअगरfies_to_msecs(jअगरfies - ce_pipe->बारtamp));
	पूर्ण

	ath11k_err(ab, "\nLast interrupt received for each group:\n");
	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		irq_grp = &ab->ext_irq_grp[i];
		ath11k_err(ab, "group_id %d %ums before\n",
			   irq_grp->grp_id,
			   jअगरfies_to_msecs(jअगरfies - irq_grp->बारtamp));
	पूर्ण

	क्रम (i = 0; i < HAL_SRNG_RING_ID_MAX; i++) अणु
		srng = &ab->hal.srng_list[i];

		अगर (!srng->initialized)
			जारी;

		अगर (srng->ring_dir == HAL_SRNG_सूची_SRC)
			ath11k_err(ab,
				   "src srng id %u hp %u, reap_hp %u, cur tp %u, cached tp %u last tp %u napi processed before %ums\n",
				   srng->ring_id, srng->u.src_ring.hp,
				   srng->u.src_ring.reap_hp,
				   *srng->u.src_ring.tp_addr, srng->u.src_ring.cached_tp,
				   srng->u.src_ring.last_tp,
				   jअगरfies_to_msecs(jअगरfies - srng->बारtamp));
		अन्यथा अगर (srng->ring_dir == HAL_SRNG_सूची_DST)
			ath11k_err(ab,
				   "dst srng id %u tp %u, cur hp %u, cached hp %u last hp %u napi processed before %ums\n",
				   srng->ring_id, srng->u.dst_ring.tp,
				   *srng->u.dst_ring.hp_addr,
				   srng->u.dst_ring.cached_hp,
				   srng->u.dst_ring.last_hp,
				   jअगरfies_to_msecs(jअगरfies - srng->बारtamp));
	पूर्ण
पूर्ण
