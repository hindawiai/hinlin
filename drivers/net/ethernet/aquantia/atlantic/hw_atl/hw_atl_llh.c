<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_llh.c: Definitions of bitfield and रेजिस्टर access functions क्रम
 * Atlantic रेजिस्टरs.
 */

#समावेश "hw_atl_llh.h"
#समावेश "hw_atl_llh_internal.h"
#समावेश "../aq_hw_utils.h"

व्योम hw_atl_ts_reset_set(काष्ठा aq_hw_s *aq_hw, u32 val)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TS_RESET_ADR,
			    HW_ATL_TS_RESET_MSK,
			    HW_ATL_TS_RESET_SHIFT,
			    val);
पूर्ण

व्योम hw_atl_ts_घातer_करोwn_set(काष्ठा aq_hw_s *aq_hw, u32 val)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TS_POWER_DOWN_ADR,
			    HW_ATL_TS_POWER_DOWN_MSK,
			    HW_ATL_TS_POWER_DOWN_SHIFT,
			    val);
पूर्ण

u32 hw_atl_ts_घातer_करोwn_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_TS_POWER_DOWN_ADR,
				  HW_ATL_TS_POWER_DOWN_MSK,
				  HW_ATL_TS_POWER_DOWN_SHIFT);
पूर्ण

u32 hw_atl_ts_पढ़ोy_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_TS_READY_ADR,
				  HW_ATL_TS_READY_MSK,
				  HW_ATL_TS_READY_SHIFT);
पूर्ण

u32 hw_atl_ts_पढ़ोy_latch_high_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_TS_READY_LATCH_HIGH_ADR,
				  HW_ATL_TS_READY_LATCH_HIGH_MSK,
				  HW_ATL_TS_READY_LATCH_HIGH_SHIFT);
पूर्ण

u32 hw_atl_ts_data_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_TS_DATA_OUT_ADR,
				  HW_ATL_TS_DATA_OUT_MSK,
				  HW_ATL_TS_DATA_OUT_SHIFT);
पूर्ण

/* global */
व्योम hw_atl_reg_glb_cpu_sem_set(काष्ठा aq_hw_s *aq_hw, u32 glb_cpu_sem,
				u32 semaphore)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GLB_CPU_SEM_ADR(semaphore), glb_cpu_sem);
पूर्ण

u32 hw_atl_reg_glb_cpu_sem_get(काष्ठा aq_hw_s *aq_hw, u32 semaphore)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GLB_CPU_SEM_ADR(semaphore));
पूर्ण

व्योम hw_atl_glb_glb_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 glb_reg_res_dis)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_GLB_REG_RES_DIS_ADR,
			    HW_ATL_GLB_REG_RES_DIS_MSK,
			    HW_ATL_GLB_REG_RES_DIS_SHIFT,
			    glb_reg_res_dis);
पूर्ण

व्योम hw_atl_glb_soft_res_set(काष्ठा aq_hw_s *aq_hw, u32 soft_res)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_GLB_SOFT_RES_ADR,
			    HW_ATL_GLB_SOFT_RES_MSK,
			    HW_ATL_GLB_SOFT_RES_SHIFT, soft_res);
पूर्ण

u32 hw_atl_glb_soft_res_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_GLB_SOFT_RES_ADR,
				  HW_ATL_GLB_SOFT_RES_MSK,
				  HW_ATL_GLB_SOFT_RES_SHIFT);
पूर्ण

u32 hw_atl_reg_glb_mअगर_id_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GLB_MIF_ID_ADR);
पूर्ण

/* stats */
u32 hw_atl_rpb_rx_dma_drop_pkt_cnt_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_RPB_RX_DMA_DROP_PKT_CNT_ADR);
पूर्ण

u64 hw_atl_stats_rx_dma_good_octet_counter_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg64(aq_hw, HW_ATL_STATS_RX_DMA_GOOD_OCTET_COUNTERLSW);
पूर्ण

u64 hw_atl_stats_rx_dma_good_pkt_counter_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg64(aq_hw, HW_ATL_STATS_RX_DMA_GOOD_PKT_COUNTERLSW);
पूर्ण

u64 hw_atl_stats_tx_dma_good_octet_counter_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg64(aq_hw, HW_ATL_STATS_TX_DMA_GOOD_OCTET_COUNTERLSW);
पूर्ण

u64 hw_atl_stats_tx_dma_good_pkt_counter_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg64(aq_hw, HW_ATL_STATS_TX_DMA_GOOD_PKT_COUNTERLSW);
पूर्ण

/* पूर्णांकerrupt */
व्योम hw_atl_itr_irq_स्वतः_masklsw_set(काष्ठा aq_hw_s *aq_hw,
				     u32 irq_स्वतः_masklsw)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_ITR_IAMRLSW_ADR, irq_स्वतः_masklsw);
पूर्ण

व्योम hw_atl_itr_irq_map_en_rx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_en_rx,
				  u32 rx)
अणु
/* रेजिस्टर address क्रम bitfield imr_rxअणुrपूर्ण_en */
	अटल u32 itr_imr_rxren_adr[32] = अणु
			0x00002100U, 0x00002100U, 0x00002104U, 0x00002104U,
			0x00002108U, 0x00002108U, 0x0000210CU, 0x0000210CU,
			0x00002110U, 0x00002110U, 0x00002114U, 0x00002114U,
			0x00002118U, 0x00002118U, 0x0000211CU, 0x0000211CU,
			0x00002120U, 0x00002120U, 0x00002124U, 0x00002124U,
			0x00002128U, 0x00002128U, 0x0000212CU, 0x0000212CU,
			0x00002130U, 0x00002130U, 0x00002134U, 0x00002134U,
			0x00002138U, 0x00002138U, 0x0000213CU, 0x0000213CU
		पूर्ण;

/* biपंचांगask क्रम bitfield imr_rxअणुrपूर्ण_en */
	अटल u32 itr_imr_rxren_msk[32] = अणु
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U,
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U,
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U,
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U,
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U,
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U,
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U,
			0x00008000U, 0x00000080U, 0x00008000U, 0x00000080U
		पूर्ण;

/* lower bit position of bitfield imr_rxअणुrपूर्ण_en */
	अटल u32 itr_imr_rxren_shअगरt[32] = अणु
			15U, 7U, 15U, 7U, 15U, 7U, 15U, 7U,
			15U, 7U, 15U, 7U, 15U, 7U, 15U, 7U,
			15U, 7U, 15U, 7U, 15U, 7U, 15U, 7U,
			15U, 7U, 15U, 7U, 15U, 7U, 15U, 7U
		पूर्ण;

	aq_hw_ग_लिखो_reg_bit(aq_hw, itr_imr_rxren_adr[rx],
			    itr_imr_rxren_msk[rx],
			    itr_imr_rxren_shअगरt[rx],
			    irq_map_en_rx);
पूर्ण

व्योम hw_atl_itr_irq_map_en_tx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_en_tx,
				  u32 tx)
अणु
/* रेजिस्टर address क्रम bitfield imr_txअणुtपूर्ण_en */
	अटल u32 itr_imr_txten_adr[32] = अणु
			0x00002100U, 0x00002100U, 0x00002104U, 0x00002104U,
			0x00002108U, 0x00002108U, 0x0000210CU, 0x0000210CU,
			0x00002110U, 0x00002110U, 0x00002114U, 0x00002114U,
			0x00002118U, 0x00002118U, 0x0000211CU, 0x0000211CU,
			0x00002120U, 0x00002120U, 0x00002124U, 0x00002124U,
			0x00002128U, 0x00002128U, 0x0000212CU, 0x0000212CU,
			0x00002130U, 0x00002130U, 0x00002134U, 0x00002134U,
			0x00002138U, 0x00002138U, 0x0000213CU, 0x0000213CU
		पूर्ण;

/* biपंचांगask क्रम bitfield imr_txअणुtपूर्ण_en */
	अटल u32 itr_imr_txten_msk[32] = अणु
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U,
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U,
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U,
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U,
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U,
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U,
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U,
			0x80000000U, 0x00800000U, 0x80000000U, 0x00800000U
		पूर्ण;

/* lower bit position of bitfield imr_txअणुtपूर्ण_en */
	अटल u32 itr_imr_txten_shअगरt[32] = अणु
			31U, 23U, 31U, 23U, 31U, 23U, 31U, 23U,
			31U, 23U, 31U, 23U, 31U, 23U, 31U, 23U,
			31U, 23U, 31U, 23U, 31U, 23U, 31U, 23U,
			31U, 23U, 31U, 23U, 31U, 23U, 31U, 23U
		पूर्ण;

	aq_hw_ग_लिखो_reg_bit(aq_hw, itr_imr_txten_adr[tx],
			    itr_imr_txten_msk[tx],
			    itr_imr_txten_shअगरt[tx],
			    irq_map_en_tx);
पूर्ण

व्योम hw_atl_itr_irq_map_rx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_rx, u32 rx)
अणु
/* रेजिस्टर address क्रम bitfield imr_rxअणुrपूर्ण[4:0] */
	अटल u32 itr_imr_rxr_adr[32] = अणु
			0x00002100U, 0x00002100U, 0x00002104U, 0x00002104U,
			0x00002108U, 0x00002108U, 0x0000210CU, 0x0000210CU,
			0x00002110U, 0x00002110U, 0x00002114U, 0x00002114U,
			0x00002118U, 0x00002118U, 0x0000211CU, 0x0000211CU,
			0x00002120U, 0x00002120U, 0x00002124U, 0x00002124U,
			0x00002128U, 0x00002128U, 0x0000212CU, 0x0000212CU,
			0x00002130U, 0x00002130U, 0x00002134U, 0x00002134U,
			0x00002138U, 0x00002138U, 0x0000213CU, 0x0000213CU
		पूर्ण;

/* biपंचांगask क्रम bitfield imr_rxअणुrपूर्ण[4:0] */
	अटल u32 itr_imr_rxr_msk[32] = अणु
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU,
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU,
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU,
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU,
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU,
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU,
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU,
			0x00001f00U, 0x0000001FU, 0x00001F00U, 0x0000001FU
		पूर्ण;

/* lower bit position of bitfield imr_rxअणुrपूर्ण[4:0] */
	अटल u32 itr_imr_rxr_shअगरt[32] = अणु
			8U, 0U, 8U, 0U, 8U, 0U, 8U, 0U,
			8U, 0U, 8U, 0U, 8U, 0U, 8U, 0U,
			8U, 0U, 8U, 0U, 8U, 0U, 8U, 0U,
			8U, 0U, 8U, 0U, 8U, 0U, 8U, 0U
		पूर्ण;

	aq_hw_ग_लिखो_reg_bit(aq_hw, itr_imr_rxr_adr[rx],
			    itr_imr_rxr_msk[rx],
			    itr_imr_rxr_shअगरt[rx],
			    irq_map_rx);
पूर्ण

व्योम hw_atl_itr_irq_map_tx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_tx, u32 tx)
अणु
/* रेजिस्टर address क्रम bitfield imr_txअणुtपूर्ण[4:0] */
	अटल u32 itr_imr_txt_adr[32] = अणु
			0x00002100U, 0x00002100U, 0x00002104U, 0x00002104U,
			0x00002108U, 0x00002108U, 0x0000210CU, 0x0000210CU,
			0x00002110U, 0x00002110U, 0x00002114U, 0x00002114U,
			0x00002118U, 0x00002118U, 0x0000211CU, 0x0000211CU,
			0x00002120U, 0x00002120U, 0x00002124U, 0x00002124U,
			0x00002128U, 0x00002128U, 0x0000212CU, 0x0000212CU,
			0x00002130U, 0x00002130U, 0x00002134U, 0x00002134U,
			0x00002138U, 0x00002138U, 0x0000213CU, 0x0000213CU
		पूर्ण;

/* biपंचांगask क्रम bitfield imr_txअणुtपूर्ण[4:0] */
	अटल u32 itr_imr_txt_msk[32] = अणु
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U
		पूर्ण;

/* lower bit position of bitfield imr_txअणुtपूर्ण[4:0] */
	अटल u32 itr_imr_txt_shअगरt[32] = अणु
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U,
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U,
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U,
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U
		पूर्ण;

	aq_hw_ग_लिखो_reg_bit(aq_hw, itr_imr_txt_adr[tx],
			    itr_imr_txt_msk[tx],
			    itr_imr_txt_shअगरt[tx],
			    irq_map_tx);
पूर्ण

व्योम hw_atl_itr_irq_msk_clearlsw_set(काष्ठा aq_hw_s *aq_hw,
				     u32 irq_msk_clearlsw)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_ITR_IMCRLSW_ADR, irq_msk_clearlsw);
पूर्ण

व्योम hw_atl_itr_irq_msk_setlsw_set(काष्ठा aq_hw_s *aq_hw, u32 irq_msk_setlsw)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_ITR_IMSRLSW_ADR, irq_msk_setlsw);
पूर्ण

व्योम hw_atl_itr_irq_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 irq_reg_res_dis)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_ITR_REG_RES_DSBL_ADR,
			    HW_ATL_ITR_REG_RES_DSBL_MSK,
			    HW_ATL_ITR_REG_RES_DSBL_SHIFT, irq_reg_res_dis);
पूर्ण

व्योम hw_atl_itr_irq_status_clearlsw_set(काष्ठा aq_hw_s *aq_hw,
					u32 irq_status_clearlsw)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_ITR_ISCRLSW_ADR, irq_status_clearlsw);
पूर्ण

u32 hw_atl_itr_irq_statuslsw_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_ITR_ISRLSW_ADR);
पूर्ण

u32 hw_atl_itr_res_irq_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_ITR_RES_ADR, HW_ATL_ITR_RES_MSK,
				  HW_ATL_ITR_RES_SHIFT);
पूर्ण

व्योम hw_atl_itr_res_irq_set(काष्ठा aq_hw_s *aq_hw, u32 res_irq)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_ITR_RES_ADR, HW_ATL_ITR_RES_MSK,
			    HW_ATL_ITR_RES_SHIFT, res_irq);
पूर्ण

/* set RSC पूर्णांकerrupt */
व्योम hw_atl_itr_rsc_en_set(काष्ठा aq_hw_s *aq_hw, u32 enable)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_ITR_RSC_EN_ADR, enable);
पूर्ण

/* set RSC delay */
व्योम hw_atl_itr_rsc_delay_set(काष्ठा aq_hw_s *aq_hw, u32 delay)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_ITR_RSC_DELAY_ADR,
			    HW_ATL_ITR_RSC_DELAY_MSK,
			    HW_ATL_ITR_RSC_DELAY_SHIFT,
			    delay);
पूर्ण

/* rdm */
व्योम hw_atl_rdm_cpu_id_set(काष्ठा aq_hw_s *aq_hw, u32 cpuid, u32 dca)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DCADCPUID_ADR(dca),
			    HW_ATL_RDM_DCADCPUID_MSK,
			    HW_ATL_RDM_DCADCPUID_SHIFT, cpuid);
पूर्ण

व्योम hw_atl_rdm_rx_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_dca_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DCA_EN_ADR, HW_ATL_RDM_DCA_EN_MSK,
			    HW_ATL_RDM_DCA_EN_SHIFT, rx_dca_en);
पूर्ण

व्योम hw_atl_rdm_rx_dca_mode_set(काष्ठा aq_hw_s *aq_hw, u32 rx_dca_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DCA_MODE_ADR,
			    HW_ATL_RDM_DCA_MODE_MSK,
			    HW_ATL_RDM_DCA_MODE_SHIFT, rx_dca_mode);
पूर्ण

व्योम hw_atl_rdm_rx_desc_data_buff_size_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_data_buff_size,
					   u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DESCDDATA_SIZE_ADR(descriptor),
			    HW_ATL_RDM_DESCDDATA_SIZE_MSK,
			    HW_ATL_RDM_DESCDDATA_SIZE_SHIFT,
			    rx_desc_data_buff_size);
पूर्ण

व्योम hw_atl_rdm_rx_desc_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_dca_en,
				   u32 dca)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DCADDESC_EN_ADR(dca),
			    HW_ATL_RDM_DCADDESC_EN_MSK,
			    HW_ATL_RDM_DCADDESC_EN_SHIFT,
			    rx_desc_dca_en);
पूर्ण

व्योम hw_atl_rdm_rx_desc_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_en,
			       u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DESCDEN_ADR(descriptor),
			    HW_ATL_RDM_DESCDEN_MSK,
			    HW_ATL_RDM_DESCDEN_SHIFT,
			    rx_desc_en);
पूर्ण

व्योम hw_atl_rdm_rx_desc_head_buff_size_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_head_buff_size,
					   u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DESCDHDR_SIZE_ADR(descriptor),
			    HW_ATL_RDM_DESCDHDR_SIZE_MSK,
			    HW_ATL_RDM_DESCDHDR_SIZE_SHIFT,
			    rx_desc_head_buff_size);
पूर्ण

व्योम hw_atl_rdm_rx_desc_head_splitting_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_head_splitting,
					   u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DESCDHDR_SPLIT_ADR(descriptor),
			    HW_ATL_RDM_DESCDHDR_SPLIT_MSK,
			    HW_ATL_RDM_DESCDHDR_SPLIT_SHIFT,
			    rx_desc_head_splitting);
पूर्ण

u32 hw_atl_rdm_rx_desc_head_ptr_get(काष्ठा aq_hw_s *aq_hw, u32 descriptor)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_RDM_DESCDHD_ADR(descriptor),
				  HW_ATL_RDM_DESCDHD_MSK,
				  HW_ATL_RDM_DESCDHD_SHIFT);
पूर्ण

व्योम hw_atl_rdm_rx_desc_len_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_len,
				u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DESCDLEN_ADR(descriptor),
			    HW_ATL_RDM_DESCDLEN_MSK, HW_ATL_RDM_DESCDLEN_SHIFT,
			    rx_desc_len);
पूर्ण

व्योम hw_atl_rdm_rx_desc_res_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_res,
				u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DESCDRESET_ADR(descriptor),
			    HW_ATL_RDM_DESCDRESET_MSK,
			    HW_ATL_RDM_DESCDRESET_SHIFT,
			    rx_desc_res);
पूर्ण

व्योम hw_atl_rdm_rx_desc_wr_wb_irq_en_set(काष्ठा aq_hw_s *aq_hw,
					 u32 rx_desc_wr_wb_irq_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_INT_DESC_WRB_EN_ADR,
			    HW_ATL_RDM_INT_DESC_WRB_EN_MSK,
			    HW_ATL_RDM_INT_DESC_WRB_EN_SHIFT,
			    rx_desc_wr_wb_irq_en);
पूर्ण

व्योम hw_atl_rdm_rx_head_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_head_dca_en,
				   u32 dca)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DCADHDR_EN_ADR(dca),
			    HW_ATL_RDM_DCADHDR_EN_MSK,
			    HW_ATL_RDM_DCADHDR_EN_SHIFT,
			    rx_head_dca_en);
पूर्ण

व्योम hw_atl_rdm_rx_pld_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_pld_dca_en,
				  u32 dca)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_DCADPAY_EN_ADR(dca),
			    HW_ATL_RDM_DCADPAY_EN_MSK,
			    HW_ATL_RDM_DCADPAY_EN_SHIFT,
			    rx_pld_dca_en);
पूर्ण

व्योम hw_atl_rdm_rdm_पूर्णांकr_moder_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 rdm_पूर्णांकr_moder_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_INT_RIM_EN_ADR,
			    HW_ATL_RDM_INT_RIM_EN_MSK,
			    HW_ATL_RDM_INT_RIM_EN_SHIFT,
			    rdm_पूर्णांकr_moder_en);
पूर्ण

/* reg */
व्योम hw_atl_reg_gen_irq_map_set(काष्ठा aq_hw_s *aq_hw, u32 gen_पूर्णांकr_map,
				u32 regidx)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GEN_INTR_MAP_ADR(regidx), gen_पूर्णांकr_map);
पूर्ण

u32 hw_atl_reg_gen_irq_status_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GEN_INTR_STAT_ADR);
पूर्ण

व्योम hw_atl_reg_irq_glb_ctl_set(काष्ठा aq_hw_s *aq_hw, u32 पूर्णांकr_glb_ctl)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_INTR_GLB_CTL_ADR, पूर्णांकr_glb_ctl);
पूर्ण

व्योम hw_atl_reg_irq_thr_set(काष्ठा aq_hw_s *aq_hw, u32 पूर्णांकr_thr, u32 throttle)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_INTR_THR_ADR(throttle), पूर्णांकr_thr);
पूर्ण

व्योम hw_atl_reg_rx_dma_desc_base_addresslswset(काष्ठा aq_hw_s *aq_hw,
					       u32 rx_dma_desc_base_addrlsw,
					       u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_DMA_DESC_BASE_ADDRLSW_ADR(descriptor),
			rx_dma_desc_base_addrlsw);
पूर्ण

व्योम hw_atl_reg_rx_dma_desc_base_addressmswset(काष्ठा aq_hw_s *aq_hw,
					       u32 rx_dma_desc_base_addrmsw,
					       u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_DMA_DESC_BASE_ADDRMSW_ADR(descriptor),
			rx_dma_desc_base_addrmsw);
पूर्ण

u32 hw_atl_reg_rx_dma_desc_status_get(काष्ठा aq_hw_s *aq_hw, u32 descriptor)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_RX_DMA_DESC_STAT_ADR(descriptor));
पूर्ण

व्योम hw_atl_reg_rx_dma_desc_tail_ptr_set(काष्ठा aq_hw_s *aq_hw,
					 u32 rx_dma_desc_tail_ptr,
					 u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_DMA_DESC_TAIL_PTR_ADR(descriptor),
			rx_dma_desc_tail_ptr);
पूर्ण

व्योम hw_atl_reg_rx_flr_mcst_flr_msk_set(काष्ठा aq_hw_s *aq_hw,
					u32 rx_flr_mcst_flr_msk)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_FLR_MCST_FLR_MSK_ADR,
			rx_flr_mcst_flr_msk);
पूर्ण

व्योम hw_atl_reg_rx_flr_mcst_flr_set(काष्ठा aq_hw_s *aq_hw, u32 rx_flr_mcst_flr,
				    u32 filter)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_FLR_MCST_FLR_ADR(filter),
			rx_flr_mcst_flr);
पूर्ण

व्योम hw_atl_reg_rx_flr_rss_control1set(काष्ठा aq_hw_s *aq_hw,
				       u32 rx_flr_rss_control1)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_FLR_RSS_CONTROL1_ADR,
			rx_flr_rss_control1);
पूर्ण

व्योम hw_atl_reg_rx_flr_control2_set(काष्ठा aq_hw_s *aq_hw,
				    u32 rx_filter_control2)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_FLR_CONTROL2_ADR, rx_filter_control2);
पूर्ण

व्योम hw_atl_reg_rx_पूर्णांकr_moder_ctrl_set(काष्ठा aq_hw_s *aq_hw,
				       u32 rx_पूर्णांकr_moderation_ctl,
				       u32 queue)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RX_INTR_MODERATION_CTL_ADR(queue),
			rx_पूर्णांकr_moderation_ctl);
पूर्ण

व्योम hw_atl_reg_tx_dma_debug_ctl_set(काष्ठा aq_hw_s *aq_hw,
				     u32 tx_dma_debug_ctl)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_TX_DMA_DEBUG_CTL_ADR, tx_dma_debug_ctl);
पूर्ण

व्योम hw_atl_reg_tx_dma_desc_base_addresslswset(काष्ठा aq_hw_s *aq_hw,
					       u32 tx_dma_desc_base_addrlsw,
					       u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_TX_DMA_DESC_BASE_ADDRLSW_ADR(descriptor),
			tx_dma_desc_base_addrlsw);
पूर्ण

व्योम hw_atl_reg_tx_dma_desc_base_addressmswset(काष्ठा aq_hw_s *aq_hw,
					       u32 tx_dma_desc_base_addrmsw,
					       u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_TX_DMA_DESC_BASE_ADDRMSW_ADR(descriptor),
			tx_dma_desc_base_addrmsw);
पूर्ण

व्योम hw_atl_reg_tx_dma_desc_tail_ptr_set(काष्ठा aq_hw_s *aq_hw,
					 u32 tx_dma_desc_tail_ptr,
					 u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_TX_DMA_DESC_TAIL_PTR_ADR(descriptor),
			tx_dma_desc_tail_ptr);
पूर्ण

व्योम hw_atl_reg_tx_पूर्णांकr_moder_ctrl_set(काष्ठा aq_hw_s *aq_hw,
				       u32 tx_पूर्णांकr_moderation_ctl,
				       u32 queue)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_TX_INTR_MODERATION_CTL_ADR(queue),
			tx_पूर्णांकr_moderation_ctl);
पूर्ण

/* RPB: rx packet buffer */
व्योम hw_atl_rpb_dma_sys_lbk_set(काष्ठा aq_hw_s *aq_hw, u32 dma_sys_lbk)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_DMA_SYS_LBK_ADR,
			    HW_ATL_RPB_DMA_SYS_LBK_MSK,
			    HW_ATL_RPB_DMA_SYS_LBK_SHIFT, dma_sys_lbk);
पूर्ण

व्योम hw_atl_rpb_dma_net_lbk_set(काष्ठा aq_hw_s *aq_hw, u32 dma_net_lbk)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_DMA_NET_LBK_ADR,
			    HW_ATL_RPB_DMA_NET_LBK_MSK,
			    HW_ATL_RPB_DMA_NET_LBK_SHIFT, dma_net_lbk);
पूर्ण

व्योम hw_atl_rpb_rpf_rx_traf_class_mode_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_traf_class_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_RPF_RX_TC_MODE_ADR,
			    HW_ATL_RPB_RPF_RX_TC_MODE_MSK,
			    HW_ATL_RPB_RPF_RX_TC_MODE_SHIFT,
			    rx_traf_class_mode);
पूर्ण

u32 hw_atl_rpb_rpf_rx_traf_class_mode_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_RPB_RPF_RX_TC_MODE_ADR,
			HW_ATL_RPB_RPF_RX_TC_MODE_MSK,
			HW_ATL_RPB_RPF_RX_TC_MODE_SHIFT);
पूर्ण

व्योम hw_atl_rpb_rx_buff_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_buff_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_RX_BUF_EN_ADR,
			    HW_ATL_RPB_RX_BUF_EN_MSK,
			    HW_ATL_RPB_RX_BUF_EN_SHIFT, rx_buff_en);
पूर्ण

व्योम hw_atl_rpb_rx_buff_hi_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 rx_buff_hi_threshold_per_tc,
						u32 buffer)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_RXBHI_THRESH_ADR(buffer),
			    HW_ATL_RPB_RXBHI_THRESH_MSK,
			    HW_ATL_RPB_RXBHI_THRESH_SHIFT,
			    rx_buff_hi_threshold_per_tc);
पूर्ण

व्योम hw_atl_rpb_rx_buff_lo_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 rx_buff_lo_threshold_per_tc,
						u32 buffer)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_RXBLO_THRESH_ADR(buffer),
			    HW_ATL_RPB_RXBLO_THRESH_MSK,
			    HW_ATL_RPB_RXBLO_THRESH_SHIFT,
			    rx_buff_lo_threshold_per_tc);
पूर्ण

व्योम hw_atl_rpb_rx_flow_ctl_mode_set(काष्ठा aq_hw_s *aq_hw, u32 rx_flow_ctl_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_RX_FC_MODE_ADR,
			    HW_ATL_RPB_RX_FC_MODE_MSK,
			    HW_ATL_RPB_RX_FC_MODE_SHIFT, rx_flow_ctl_mode);
पूर्ण

व्योम hw_atl_rdm_rx_dma_desc_cache_init_tgl(काष्ठा aq_hw_s *aq_hw)
अणु
	u32 val;

	val = aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_ADR,
				 HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSK,
				 HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_SHIFT);

	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_ADR,
			    HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSK,
			    HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_SHIFT,
			    val ^ 1);
पूर्ण

u32 hw_atl_rdm_rx_dma_desc_cache_init_करोne_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, RDM_RX_DMA_DESC_CACHE_INIT_DONE_ADR,
				  RDM_RX_DMA_DESC_CACHE_INIT_DONE_MSK,
				  RDM_RX_DMA_DESC_CACHE_INIT_DONE_SHIFT);
पूर्ण

व्योम hw_atl_rpb_rx_pkt_buff_size_per_tc_set(काष्ठा aq_hw_s *aq_hw,
					    u32 rx_pkt_buff_size_per_tc, u32 buffer)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_RXBBUF_SIZE_ADR(buffer),
			    HW_ATL_RPB_RXBBUF_SIZE_MSK,
			    HW_ATL_RPB_RXBBUF_SIZE_SHIFT,
			    rx_pkt_buff_size_per_tc);
पूर्ण

व्योम hw_atl_rpb_rx_xoff_en_per_tc_set(काष्ठा aq_hw_s *aq_hw,
				      u32 rx_xoff_en_per_tc, u32 buffer)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPB_RXBXOFF_EN_ADR(buffer),
			    HW_ATL_RPB_RXBXOFF_EN_MSK,
			    HW_ATL_RPB_RXBXOFF_EN_SHIFT,
			    rx_xoff_en_per_tc);
पूर्ण

/* rpf */

व्योम hw_atl_rpfl2broadcast_count_threshold_set(काष्ठा aq_hw_s *aq_hw,
					       u32 l2broadcast_count_threshold)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2BC_THRESH_ADR,
			    HW_ATL_RPFL2BC_THRESH_MSK,
			    HW_ATL_RPFL2BC_THRESH_SHIFT,
			    l2broadcast_count_threshold);
पूर्ण

व्योम hw_atl_rpfl2broadcast_en_set(काष्ठा aq_hw_s *aq_hw, u32 l2broadcast_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2BC_EN_ADR, HW_ATL_RPFL2BC_EN_MSK,
			    HW_ATL_RPFL2BC_EN_SHIFT, l2broadcast_en);
पूर्ण

व्योम hw_atl_rpfl2broadcast_flr_act_set(काष्ठा aq_hw_s *aq_hw,
				       u32 l2broadcast_flr_act)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2BC_ACT_ADR,
			    HW_ATL_RPFL2BC_ACT_MSK,
			    HW_ATL_RPFL2BC_ACT_SHIFT, l2broadcast_flr_act);
पूर्ण

व्योम hw_atl_rpfl2multicast_flr_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 l2multicast_flr_en,
				      u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2MC_ENF_ADR(filter),
			    HW_ATL_RPFL2MC_ENF_MSK,
			    HW_ATL_RPFL2MC_ENF_SHIFT, l2multicast_flr_en);
पूर्ण

u32 hw_atl_rpfl2promiscuous_mode_en_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_RPFL2PROMIS_MODE_ADR,
				  HW_ATL_RPFL2PROMIS_MODE_MSK,
				  HW_ATL_RPFL2PROMIS_MODE_SHIFT);
पूर्ण

व्योम hw_atl_rpfl2promiscuous_mode_en_set(काष्ठा aq_hw_s *aq_hw,
					 u32 l2promiscuous_mode_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2PROMIS_MODE_ADR,
			    HW_ATL_RPFL2PROMIS_MODE_MSK,
			    HW_ATL_RPFL2PROMIS_MODE_SHIFT,
			    l2promiscuous_mode_en);
पूर्ण

व्योम hw_atl_rpfl2unicast_flr_act_set(काष्ठा aq_hw_s *aq_hw,
				     u32 l2unicast_flr_act,
				     u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2UC_ACTF_ADR(filter),
			    HW_ATL_RPFL2UC_ACTF_MSK, HW_ATL_RPFL2UC_ACTF_SHIFT,
			    l2unicast_flr_act);
पूर्ण

व्योम hw_atl_rpfl2_uc_flr_en_set(काष्ठा aq_hw_s *aq_hw, u32 l2unicast_flr_en,
				u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2UC_ENF_ADR(filter),
			    HW_ATL_RPFL2UC_ENF_MSK,
			    HW_ATL_RPFL2UC_ENF_SHIFT, l2unicast_flr_en);
पूर्ण

व्योम hw_atl_rpfl2unicast_dest_addresslsw_set(काष्ठा aq_hw_s *aq_hw,
					     u32 l2unicast_dest_addresslsw,
					     u32 filter)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPFL2UC_DAFLSW_ADR(filter),
			l2unicast_dest_addresslsw);
पूर्ण

व्योम hw_atl_rpfl2unicast_dest_addressmsw_set(काष्ठा aq_hw_s *aq_hw,
					     u32 l2unicast_dest_addressmsw,
					     u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2UC_DAFMSW_ADR(filter),
			    HW_ATL_RPFL2UC_DAFMSW_MSK,
			    HW_ATL_RPFL2UC_DAFMSW_SHIFT,
			    l2unicast_dest_addressmsw);
पूर्ण

व्योम hw_atl_rpfl2_accept_all_mc_packets_set(काष्ठा aq_hw_s *aq_hw,
					    u32 l2_accept_all_mc_packets)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPFL2MC_ACCEPT_ALL_ADR,
			    HW_ATL_RPFL2MC_ACCEPT_ALL_MSK,
			    HW_ATL_RPFL2MC_ACCEPT_ALL_SHIFT,
			    l2_accept_all_mc_packets);
पूर्ण

व्योम hw_atl_rpf_rpb_user_priority_tc_map_set(काष्ठा aq_hw_s *aq_hw,
					     u32 user_priority, u32 tc)
अणु
/* रेजिस्टर address क्रम bitfield rx_tc_upअणुtपूर्ण[2:0] */
	अटल u32 rpf_rpb_rx_tc_upt_adr[8] = अणु
			0x000054c4U, 0x000054C4U, 0x000054C4U, 0x000054C4U,
			0x000054c4U, 0x000054C4U, 0x000054C4U, 0x000054C4U
		पूर्ण;

/* biपंचांगask क्रम bitfield rx_tc_upअणुtपूर्ण[2:0] */
	अटल u32 rpf_rpb_rx_tc_upt_msk[8] = अणु
			0x00000007U, 0x00000070U, 0x00000700U, 0x00007000U,
			0x00070000U, 0x00700000U, 0x07000000U, 0x70000000U
		पूर्ण;

/* lower bit position of bitfield rx_tc_upअणुtपूर्ण[2:0] */
	अटल u32 rpf_rpb_rx_tc_upt_shft[8] = अणु
			0U, 4U, 8U, 12U, 16U, 20U, 24U, 28U
		पूर्ण;

	aq_hw_ग_लिखो_reg_bit(aq_hw, rpf_rpb_rx_tc_upt_adr[user_priority],
			    rpf_rpb_rx_tc_upt_msk[user_priority],
			    rpf_rpb_rx_tc_upt_shft[user_priority], tc);
पूर्ण

व्योम hw_atl_rpf_rss_key_addr_set(काष्ठा aq_hw_s *aq_hw, u32 rss_key_addr)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_RSS_KEY_ADDR_ADR,
			    HW_ATL_RPF_RSS_KEY_ADDR_MSK,
			    HW_ATL_RPF_RSS_KEY_ADDR_SHIFT,
			    rss_key_addr);
पूर्ण

व्योम hw_atl_rpf_rss_key_wr_data_set(काष्ठा aq_hw_s *aq_hw, u32 rss_key_wr_data)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPF_RSS_KEY_WR_DATA_ADR,
			rss_key_wr_data);
पूर्ण

u32 hw_atl_rpf_rss_key_wr_en_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_RPF_RSS_KEY_WR_ENI_ADR,
				  HW_ATL_RPF_RSS_KEY_WR_ENI_MSK,
				  HW_ATL_RPF_RSS_KEY_WR_ENI_SHIFT);
पूर्ण

व्योम hw_atl_rpf_rss_key_wr_en_set(काष्ठा aq_hw_s *aq_hw, u32 rss_key_wr_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_RSS_KEY_WR_ENI_ADR,
			    HW_ATL_RPF_RSS_KEY_WR_ENI_MSK,
			    HW_ATL_RPF_RSS_KEY_WR_ENI_SHIFT,
			    rss_key_wr_en);
पूर्ण

व्योम hw_atl_rpf_rss_redir_tbl_addr_set(काष्ठा aq_hw_s *aq_hw,
				       u32 rss_redir_tbl_addr)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_RSS_REसूची_ADDR_ADR,
			    HW_ATL_RPF_RSS_REसूची_ADDR_MSK,
			    HW_ATL_RPF_RSS_REसूची_ADDR_SHIFT,
			    rss_redir_tbl_addr);
पूर्ण

व्योम hw_atl_rpf_rss_redir_tbl_wr_data_set(काष्ठा aq_hw_s *aq_hw,
					  u32 rss_redir_tbl_wr_data)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_RSS_REसूची_WR_DATA_ADR,
			    HW_ATL_RPF_RSS_REसूची_WR_DATA_MSK,
			    HW_ATL_RPF_RSS_REसूची_WR_DATA_SHIFT,
			    rss_redir_tbl_wr_data);
पूर्ण

u32 hw_atl_rpf_rss_redir_wr_en_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_RPF_RSS_REसूची_WR_ENI_ADR,
				  HW_ATL_RPF_RSS_REसूची_WR_ENI_MSK,
				  HW_ATL_RPF_RSS_REसूची_WR_ENI_SHIFT);
पूर्ण

व्योम hw_atl_rpf_rss_redir_wr_en_set(काष्ठा aq_hw_s *aq_hw, u32 rss_redir_wr_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_RSS_REसूची_WR_ENI_ADR,
			    HW_ATL_RPF_RSS_REसूची_WR_ENI_MSK,
			    HW_ATL_RPF_RSS_REसूची_WR_ENI_SHIFT, rss_redir_wr_en);
पूर्ण

व्योम hw_atl_rpf_tpo_to_rpf_sys_lbk_set(काष्ठा aq_hw_s *aq_hw,
				       u32 tpo_to_rpf_sys_lbk)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_TPO_RPF_SYS_LBK_ADR,
			    HW_ATL_RPF_TPO_RPF_SYS_LBK_MSK,
			    HW_ATL_RPF_TPO_RPF_SYS_LBK_SHIFT,
			    tpo_to_rpf_sys_lbk);
पूर्ण

व्योम hw_atl_rpf_vlan_inner_etht_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_inner_etht)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_INNER_TPID_ADR,
			    HW_ATL_RPF_VL_INNER_TPID_MSK,
			    HW_ATL_RPF_VL_INNER_TPID_SHIFT,
			    vlan_inner_etht);
पूर्ण

व्योम hw_atl_rpf_vlan_outer_etht_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_outer_etht)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_OUTER_TPID_ADR,
			    HW_ATL_RPF_VL_OUTER_TPID_MSK,
			    HW_ATL_RPF_VL_OUTER_TPID_SHIFT,
			    vlan_outer_etht);
पूर्ण

व्योम hw_atl_rpf_vlan_prom_mode_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 vlan_prom_mode_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_PROMIS_MODE_ADR,
			    HW_ATL_RPF_VL_PROMIS_MODE_MSK,
			    HW_ATL_RPF_VL_PROMIS_MODE_SHIFT,
			    vlan_prom_mode_en);
पूर्ण

u32 hw_atl_rpf_vlan_prom_mode_en_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_RPF_VL_PROMIS_MODE_ADR,
				  HW_ATL_RPF_VL_PROMIS_MODE_MSK,
				  HW_ATL_RPF_VL_PROMIS_MODE_SHIFT);
पूर्ण

व्योम hw_atl_rpf_vlan_accept_untagged_packets_set(काष्ठा aq_hw_s *aq_hw,
						 u32 vlan_acc_untagged_packets)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_ADR,
			    HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_MSK,
			    HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_SHIFT,
			    vlan_acc_untagged_packets);
पूर्ण

व्योम hw_atl_rpf_vlan_untagged_act_set(काष्ठा aq_hw_s *aq_hw,
				      u32 vlan_untagged_act)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_UNTAGGED_ACT_ADR,
			    HW_ATL_RPF_VL_UNTAGGED_ACT_MSK,
			    HW_ATL_RPF_VL_UNTAGGED_ACT_SHIFT,
			    vlan_untagged_act);
पूर्ण

व्योम hw_atl_rpf_vlan_flr_en_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_flr_en,
				u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_EN_F_ADR(filter),
			    HW_ATL_RPF_VL_EN_F_MSK,
			    HW_ATL_RPF_VL_EN_F_SHIFT,
			    vlan_flr_en);
पूर्ण

व्योम hw_atl_rpf_vlan_flr_act_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_flr_act,
				 u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_ACT_F_ADR(filter),
			    HW_ATL_RPF_VL_ACT_F_MSK,
			    HW_ATL_RPF_VL_ACT_F_SHIFT,
			    vlan_flr_act);
पूर्ण

व्योम hw_atl_rpf_vlan_id_flr_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_id_flr,
				u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_ID_F_ADR(filter),
			    HW_ATL_RPF_VL_ID_F_MSK,
			    HW_ATL_RPF_VL_ID_F_SHIFT,
			    vlan_id_flr);
पूर्ण

व्योम hw_atl_rpf_vlan_rxq_en_flr_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_rxq_en,
				    u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_RXQ_EN_F_ADR(filter),
			    HW_ATL_RPF_VL_RXQ_EN_F_MSK,
			    HW_ATL_RPF_VL_RXQ_EN_F_SHIFT,
			    vlan_rxq_en);
पूर्ण

व्योम hw_atl_rpf_vlan_rxq_flr_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_rxq,
				 u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_VL_RXQ_F_ADR(filter),
			    HW_ATL_RPF_VL_RXQ_F_MSK,
			    HW_ATL_RPF_VL_RXQ_F_SHIFT,
			    vlan_rxq);
पूर्ण;

व्योम hw_atl_rpf_etht_flr_en_set(काष्ठा aq_hw_s *aq_hw, u32 etht_flr_en,
				u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_ENF_ADR(filter),
			    HW_ATL_RPF_ET_ENF_MSK,
			    HW_ATL_RPF_ET_ENF_SHIFT, etht_flr_en);
पूर्ण

व्योम hw_atl_rpf_etht_user_priority_en_set(काष्ठा aq_hw_s *aq_hw,
					  u32 etht_user_priority_en, u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_UPFEN_ADR(filter),
			    HW_ATL_RPF_ET_UPFEN_MSK, HW_ATL_RPF_ET_UPFEN_SHIFT,
			    etht_user_priority_en);
पूर्ण

व्योम hw_atl_rpf_etht_rx_queue_en_set(काष्ठा aq_hw_s *aq_hw,
				     u32 etht_rx_queue_en,
				     u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_RXQFEN_ADR(filter),
			    HW_ATL_RPF_ET_RXQFEN_MSK,
			    HW_ATL_RPF_ET_RXQFEN_SHIFT,
			    etht_rx_queue_en);
पूर्ण

व्योम hw_atl_rpf_etht_user_priority_set(काष्ठा aq_hw_s *aq_hw,
				       u32 etht_user_priority,
				       u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_UPF_ADR(filter),
			    HW_ATL_RPF_ET_UPF_MSK,
			    HW_ATL_RPF_ET_UPF_SHIFT, etht_user_priority);
पूर्ण

व्योम hw_atl_rpf_etht_rx_queue_set(काष्ठा aq_hw_s *aq_hw, u32 etht_rx_queue,
				  u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_RXQF_ADR(filter),
			    HW_ATL_RPF_ET_RXQF_MSK,
			    HW_ATL_RPF_ET_RXQF_SHIFT, etht_rx_queue);
पूर्ण

व्योम hw_atl_rpf_etht_mgt_queue_set(काष्ठा aq_hw_s *aq_hw, u32 etht_mgt_queue,
				   u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_MNG_RXQF_ADR(filter),
			    HW_ATL_RPF_ET_MNG_RXQF_MSK,
			    HW_ATL_RPF_ET_MNG_RXQF_SHIFT,
			    etht_mgt_queue);
पूर्ण

व्योम hw_atl_rpf_etht_flr_act_set(काष्ठा aq_hw_s *aq_hw, u32 etht_flr_act,
				 u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_ACTF_ADR(filter),
			    HW_ATL_RPF_ET_ACTF_MSK,
			    HW_ATL_RPF_ET_ACTF_SHIFT, etht_flr_act);
पूर्ण

व्योम hw_atl_rpf_etht_flr_set(काष्ठा aq_hw_s *aq_hw, u32 etht_flr, u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_ET_VALF_ADR(filter),
			    HW_ATL_RPF_ET_VALF_MSK,
			    HW_ATL_RPF_ET_VALF_SHIFT, etht_flr);
पूर्ण

व्योम hw_atl_rpf_l4_spd_set(काष्ठा aq_hw_s *aq_hw, u32 val, u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_L4_SPD_ADR(filter),
			    HW_ATL_RPF_L4_SPD_MSK,
			    HW_ATL_RPF_L4_SPD_SHIFT, val);
पूर्ण

व्योम hw_atl_rpf_l4_dpd_set(काष्ठा aq_hw_s *aq_hw, u32 val, u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPF_L4_DPD_ADR(filter),
			    HW_ATL_RPF_L4_DPD_MSK,
			    HW_ATL_RPF_L4_DPD_SHIFT, val);
पूर्ण

/* RPO: rx packet offload */
व्योम hw_atl_rpo_ipv4header_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					      u32 ipv4header_crc_offload_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_IPV4CHK_EN_ADR,
			    HW_ATL_RPO_IPV4CHK_EN_MSK,
			    HW_ATL_RPO_IPV4CHK_EN_SHIFT,
			    ipv4header_crc_offload_en);
पूर्ण

व्योम hw_atl_rpo_rx_desc_vlan_stripping_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_vlan_stripping,
					   u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_DESCDVL_STRIP_ADR(descriptor),
			    HW_ATL_RPO_DESCDVL_STRIP_MSK,
			    HW_ATL_RPO_DESCDVL_STRIP_SHIFT,
			    rx_desc_vlan_stripping);
पूर्ण

व्योम hw_atl_rpo_outer_vlan_tag_mode_set(व्योम *context,
					u32 outervlantagmode)
अणु
	aq_hw_ग_लिखो_reg_bit(context, HW_ATL_RPO_OUTER_VL_INS_MODE_ADR,
			    HW_ATL_RPO_OUTER_VL_INS_MODE_MSK,
			    HW_ATL_RPO_OUTER_VL_INS_MODE_SHIFT,
			    outervlantagmode);
पूर्ण

u32 hw_atl_rpo_outer_vlan_tag_mode_get(व्योम *context)
अणु
	वापस aq_hw_पढ़ो_reg_bit(context, HW_ATL_RPO_OUTER_VL_INS_MODE_ADR,
				  HW_ATL_RPO_OUTER_VL_INS_MODE_MSK,
				  HW_ATL_RPO_OUTER_VL_INS_MODE_SHIFT);
पूर्ण

व्योम hw_atl_rpo_tcp_udp_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					   u32 tcp_udp_crc_offload_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPOL4CHK_EN_ADR,
			    HW_ATL_RPOL4CHK_EN_MSK,
			    HW_ATL_RPOL4CHK_EN_SHIFT, tcp_udp_crc_offload_en);
पूर्ण

व्योम hw_atl_rpo_lro_en_set(काष्ठा aq_hw_s *aq_hw, u32 lro_en)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPO_LRO_EN_ADR, lro_en);
पूर्ण

व्योम hw_atl_rpo_lro_patch_optimization_en_set(काष्ठा aq_hw_s *aq_hw,
					      u32 lro_patch_optimization_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_LRO_PTOPT_EN_ADR,
			    HW_ATL_RPO_LRO_PTOPT_EN_MSK,
			    HW_ATL_RPO_LRO_PTOPT_EN_SHIFT,
			    lro_patch_optimization_en);
पूर्ण

व्योम hw_atl_rpo_lro_qsessions_lim_set(काष्ठा aq_hw_s *aq_hw,
				      u32 lro_qsessions_lim)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_LRO_QSES_LMT_ADR,
			    HW_ATL_RPO_LRO_QSES_LMT_MSK,
			    HW_ATL_RPO_LRO_QSES_LMT_SHIFT,
			    lro_qsessions_lim);
पूर्ण

व्योम hw_atl_rpo_lro_total_desc_lim_set(काष्ठा aq_hw_s *aq_hw,
				       u32 lro_total_desc_lim)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_LRO_TOT_DSC_LMT_ADR,
			    HW_ATL_RPO_LRO_TOT_DSC_LMT_MSK,
			    HW_ATL_RPO_LRO_TOT_DSC_LMT_SHIFT,
			    lro_total_desc_lim);
पूर्ण

व्योम hw_atl_rpo_lro_min_pay_of_first_pkt_set(काष्ठा aq_hw_s *aq_hw,
					     u32 lro_min_pld_of_first_pkt)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_LRO_PKT_MIN_ADR,
			    HW_ATL_RPO_LRO_PKT_MIN_MSK,
			    HW_ATL_RPO_LRO_PKT_MIN_SHIFT,
			    lro_min_pld_of_first_pkt);
पूर्ण

व्योम hw_atl_rpo_lro_pkt_lim_set(काष्ठा aq_hw_s *aq_hw, u32 lro_pkt_lim)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPO_LRO_RSC_MAX_ADR, lro_pkt_lim);
पूर्ण

व्योम hw_atl_rpo_lro_max_num_of_descriptors_set(काष्ठा aq_hw_s *aq_hw,
					       u32 lro_max_number_of_descriptors,
					       u32 lro)
अणु
/* Register address क्रम bitfield lroअणुLपूर्ण_des_max[1:0] */
	अटल u32 rpo_lro_ldes_max_adr[32] = अणु
			0x000055A0U, 0x000055A0U, 0x000055A0U, 0x000055A0U,
			0x000055A0U, 0x000055A0U, 0x000055A0U, 0x000055A0U,
			0x000055A4U, 0x000055A4U, 0x000055A4U, 0x000055A4U,
			0x000055A4U, 0x000055A4U, 0x000055A4U, 0x000055A4U,
			0x000055A8U, 0x000055A8U, 0x000055A8U, 0x000055A8U,
			0x000055A8U, 0x000055A8U, 0x000055A8U, 0x000055A8U,
			0x000055ACU, 0x000055ACU, 0x000055ACU, 0x000055ACU,
			0x000055ACU, 0x000055ACU, 0x000055ACU, 0x000055ACU
		पूर्ण;

/* Biपंचांगask क्रम bitfield lroअणुLपूर्ण_des_max[1:0] */
	अटल u32 rpo_lro_ldes_max_msk[32] = अणु
			0x00000003U, 0x00000030U, 0x00000300U, 0x00003000U,
			0x00030000U, 0x00300000U, 0x03000000U, 0x30000000U,
			0x00000003U, 0x00000030U, 0x00000300U, 0x00003000U,
			0x00030000U, 0x00300000U, 0x03000000U, 0x30000000U,
			0x00000003U, 0x00000030U, 0x00000300U, 0x00003000U,
			0x00030000U, 0x00300000U, 0x03000000U, 0x30000000U,
			0x00000003U, 0x00000030U, 0x00000300U, 0x00003000U,
			0x00030000U, 0x00300000U, 0x03000000U, 0x30000000U
		पूर्ण;

/* Lower bit position of bitfield lroअणुLपूर्ण_des_max[1:0] */
	अटल u32 rpo_lro_ldes_max_shअगरt[32] = अणु
			0U, 4U, 8U, 12U, 16U, 20U, 24U, 28U,
			0U, 4U, 8U, 12U, 16U, 20U, 24U, 28U,
			0U, 4U, 8U, 12U, 16U, 20U, 24U, 28U,
			0U, 4U, 8U, 12U, 16U, 20U, 24U, 28U
		पूर्ण;

	aq_hw_ग_लिखो_reg_bit(aq_hw, rpo_lro_ldes_max_adr[lro],
			    rpo_lro_ldes_max_msk[lro],
			    rpo_lro_ldes_max_shअगरt[lro],
			    lro_max_number_of_descriptors);
पूर्ण

व्योम hw_atl_rpo_lro_समय_base_भागider_set(काष्ठा aq_hw_s *aq_hw,
					  u32 lro_समय_base_भागider)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_LRO_TB_DIV_ADR,
			    HW_ATL_RPO_LRO_TB_DIV_MSK,
			    HW_ATL_RPO_LRO_TB_DIV_SHIFT,
			    lro_समय_base_भागider);
पूर्ण

व्योम hw_atl_rpo_lro_inactive_पूर्णांकerval_set(काष्ठा aq_hw_s *aq_hw,
					  u32 lro_inactive_पूर्णांकerval)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_LRO_INA_IVAL_ADR,
			    HW_ATL_RPO_LRO_INA_IVAL_MSK,
			    HW_ATL_RPO_LRO_INA_IVAL_SHIFT,
			    lro_inactive_पूर्णांकerval);
पूर्ण

व्योम hw_atl_rpo_lro_max_coalescing_पूर्णांकerval_set(काष्ठा aq_hw_s *aq_hw,
						u32 lro_max_coal_पूर्णांकerval)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RPO_LRO_MAX_IVAL_ADR,
			    HW_ATL_RPO_LRO_MAX_IVAL_MSK,
			    HW_ATL_RPO_LRO_MAX_IVAL_SHIFT,
			    lro_max_coal_पूर्णांकerval);
पूर्ण

/* rx */
व्योम hw_atl_rx_rx_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 rx_reg_res_dis)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_RX_REG_RES_DSBL_ADR,
			    HW_ATL_RX_REG_RES_DSBL_MSK,
			    HW_ATL_RX_REG_RES_DSBL_SHIFT,
			    rx_reg_res_dis);
पूर्ण

/* tdm */
व्योम hw_atl_tdm_cpu_id_set(काष्ठा aq_hw_s *aq_hw, u32 cpuid, u32 dca)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_DCADCPUID_ADR(dca),
			    HW_ATL_TDM_DCADCPUID_MSK,
			    HW_ATL_TDM_DCADCPUID_SHIFT, cpuid);
पूर्ण

व्योम hw_atl_tdm_large_send_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					  u32 large_send_offload_en)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_TDM_LSO_EN_ADR, large_send_offload_en);
पूर्ण

व्योम hw_atl_tdm_tx_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_dca_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_DCA_EN_ADR, HW_ATL_TDM_DCA_EN_MSK,
			    HW_ATL_TDM_DCA_EN_SHIFT, tx_dca_en);
पूर्ण

व्योम hw_atl_tdm_tx_dca_mode_set(काष्ठा aq_hw_s *aq_hw, u32 tx_dca_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_DCA_MODE_ADR,
			    HW_ATL_TDM_DCA_MODE_MSK,
			    HW_ATL_TDM_DCA_MODE_SHIFT, tx_dca_mode);
पूर्ण

व्योम hw_atl_tdm_tx_desc_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_desc_dca_en,
				   u32 dca)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_DCADDESC_EN_ADR(dca),
			    HW_ATL_TDM_DCADDESC_EN_MSK,
			    HW_ATL_TDM_DCADDESC_EN_SHIFT,
			    tx_desc_dca_en);
पूर्ण

व्योम hw_atl_tdm_tx_desc_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_desc_en,
			       u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_DESCDEN_ADR(descriptor),
			    HW_ATL_TDM_DESCDEN_MSK,
			    HW_ATL_TDM_DESCDEN_SHIFT,
			    tx_desc_en);
पूर्ण

u32 hw_atl_tdm_tx_desc_head_ptr_get(काष्ठा aq_hw_s *aq_hw, u32 descriptor)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_TDM_DESCDHD_ADR(descriptor),
				  HW_ATL_TDM_DESCDHD_MSK,
				  HW_ATL_TDM_DESCDHD_SHIFT);
पूर्ण

व्योम hw_atl_tdm_tx_desc_len_set(काष्ठा aq_hw_s *aq_hw, u32 tx_desc_len,
				u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_DESCDLEN_ADR(descriptor),
			    HW_ATL_TDM_DESCDLEN_MSK,
			    HW_ATL_TDM_DESCDLEN_SHIFT,
			    tx_desc_len);
पूर्ण

व्योम hw_atl_tdm_tx_desc_wr_wb_irq_en_set(काष्ठा aq_hw_s *aq_hw,
					 u32 tx_desc_wr_wb_irq_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_INT_DESC_WRB_EN_ADR,
			    HW_ATL_TDM_INT_DESC_WRB_EN_MSK,
			    HW_ATL_TDM_INT_DESC_WRB_EN_SHIFT,
			    tx_desc_wr_wb_irq_en);
पूर्ण

व्योम hw_atl_tdm_tx_desc_wr_wb_threshold_set(काष्ठा aq_hw_s *aq_hw,
					    u32 tx_desc_wr_wb_threshold,
					    u32 descriptor)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_DESCDWRB_THRESH_ADR(descriptor),
			    HW_ATL_TDM_DESCDWRB_THRESH_MSK,
			    HW_ATL_TDM_DESCDWRB_THRESH_SHIFT,
			    tx_desc_wr_wb_threshold);
पूर्ण

व्योम hw_atl_tdm_tdm_पूर्णांकr_moder_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tdm_irq_moderation_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TDM_INT_MOD_EN_ADR,
			    HW_ATL_TDM_INT_MOD_EN_MSK,
			    HW_ATL_TDM_INT_MOD_EN_SHIFT,
			    tdm_irq_moderation_en);
पूर्ण

/* thm */
व्योम hw_atl_thm_lso_tcp_flag_of_first_pkt_set(काष्ठा aq_hw_s *aq_hw,
					      u32 lso_tcp_flag_of_first_pkt)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_THM_LSO_TCP_FLAG_FIRST_ADR,
			    HW_ATL_THM_LSO_TCP_FLAG_FIRST_MSK,
			    HW_ATL_THM_LSO_TCP_FLAG_FIRST_SHIFT,
			    lso_tcp_flag_of_first_pkt);
पूर्ण

व्योम hw_atl_thm_lso_tcp_flag_of_last_pkt_set(काष्ठा aq_hw_s *aq_hw,
					     u32 lso_tcp_flag_of_last_pkt)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_THM_LSO_TCP_FLAG_LAST_ADR,
			    HW_ATL_THM_LSO_TCP_FLAG_LAST_MSK,
			    HW_ATL_THM_LSO_TCP_FLAG_LAST_SHIFT,
			    lso_tcp_flag_of_last_pkt);
पूर्ण

व्योम hw_atl_thm_lso_tcp_flag_of_middle_pkt_set(काष्ठा aq_hw_s *aq_hw,
					       u32 lso_tcp_flag_of_middle_pkt)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_THM_LSO_TCP_FLAG_MID_ADR,
			    HW_ATL_THM_LSO_TCP_FLAG_MID_MSK,
			    HW_ATL_THM_LSO_TCP_FLAG_MID_SHIFT,
			    lso_tcp_flag_of_middle_pkt);
पूर्ण

/* TPB: tx packet buffer */
व्योम hw_atl_tpb_tx_buff_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_buff_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_TX_BUF_EN_ADR,
			    HW_ATL_TPB_TX_BUF_EN_MSK,
			    HW_ATL_TPB_TX_BUF_EN_SHIFT, tx_buff_en);
पूर्ण

u32 hw_atl_tpb_tps_tx_tc_mode_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_TPB_TX_TC_MODE_ADDR,
			HW_ATL_TPB_TX_TC_MODE_MSK,
			HW_ATL_TPB_TX_TC_MODE_SHIFT);
पूर्ण

व्योम hw_atl_tpb_tps_tx_tc_mode_set(काष्ठा aq_hw_s *aq_hw,
				   u32 tx_traf_class_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_TX_TC_MODE_ADDR,
			HW_ATL_TPB_TX_TC_MODE_MSK,
			HW_ATL_TPB_TX_TC_MODE_SHIFT,
			tx_traf_class_mode);
पूर्ण

व्योम hw_atl_tpb_tx_buff_hi_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 tx_buff_hi_threshold_per_tc,
					 u32 buffer)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_TXBHI_THRESH_ADR(buffer),
			    HW_ATL_TPB_TXBHI_THRESH_MSK,
			    HW_ATL_TPB_TXBHI_THRESH_SHIFT,
			    tx_buff_hi_threshold_per_tc);
पूर्ण

व्योम hw_atl_tpb_tx_buff_lo_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 tx_buff_lo_threshold_per_tc,
					 u32 buffer)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_TXBLO_THRESH_ADR(buffer),
			    HW_ATL_TPB_TXBLO_THRESH_MSK,
			    HW_ATL_TPB_TXBLO_THRESH_SHIFT,
			    tx_buff_lo_threshold_per_tc);
पूर्ण

व्योम hw_atl_tpb_tx_dma_sys_lbk_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_dma_sys_lbk_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_DMA_SYS_LBK_ADR,
			    HW_ATL_TPB_DMA_SYS_LBK_MSK,
			    HW_ATL_TPB_DMA_SYS_LBK_SHIFT,
			    tx_dma_sys_lbk_en);
पूर्ण

व्योम hw_atl_tpb_tx_dma_net_lbk_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tx_dma_net_lbk_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_DMA_NET_LBK_ADR,
			    HW_ATL_TPB_DMA_NET_LBK_MSK,
			    HW_ATL_TPB_DMA_NET_LBK_SHIFT,
			    tx_dma_net_lbk_en);
पूर्ण

व्योम hw_atl_tpb_tx_tx_clk_gate_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tx_clk_gate_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_TX_CLK_GATE_EN_ADR,
			    HW_ATL_TPB_TX_CLK_GATE_EN_MSK,
			    HW_ATL_TPB_TX_CLK_GATE_EN_SHIFT,
			    tx_clk_gate_en);
पूर्ण

व्योम hw_atl_tpb_tx_pkt_buff_size_per_tc_set(काष्ठा aq_hw_s *aq_hw,

					    u32 tx_pkt_buff_size_per_tc, u32 buffer)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_TXBBUF_SIZE_ADR(buffer),
			    HW_ATL_TPB_TXBBUF_SIZE_MSK,
			    HW_ATL_TPB_TXBBUF_SIZE_SHIFT,
			    tx_pkt_buff_size_per_tc);
पूर्ण

व्योम hw_atl_tpb_tx_path_scp_ins_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_path_scp_ins_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPB_TX_SCP_INS_EN_ADR,
			    HW_ATL_TPB_TX_SCP_INS_EN_MSK,
			    HW_ATL_TPB_TX_SCP_INS_EN_SHIFT,
			    tx_path_scp_ins_en);
पूर्ण

/* TPO: tx packet offload */
व्योम hw_atl_tpo_ipv4header_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					      u32 ipv4header_crc_offload_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPO_IPV4CHK_EN_ADR,
			    HW_ATL_TPO_IPV4CHK_EN_MSK,
			    HW_ATL_TPO_IPV4CHK_EN_SHIFT,
			    ipv4header_crc_offload_en);
पूर्ण

व्योम hw_atl_tpo_tcp_udp_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					   u32 tcp_udp_crc_offload_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPOL4CHK_EN_ADR,
			    HW_ATL_TPOL4CHK_EN_MSK,
			    HW_ATL_TPOL4CHK_EN_SHIFT,
			    tcp_udp_crc_offload_en);
पूर्ण

व्योम hw_atl_tpo_tx_pkt_sys_lbk_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tx_pkt_sys_lbk_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPO_PKT_SYS_LBK_ADR,
			    HW_ATL_TPO_PKT_SYS_LBK_MSK,
			    HW_ATL_TPO_PKT_SYS_LBK_SHIFT,
			    tx_pkt_sys_lbk_en);
पूर्ण

/* TPS: tx packet scheduler */
व्योम hw_atl_tps_tx_pkt_shed_data_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
					      u32 tx_pkt_shed_data_arb_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DATA_TC_ARB_MODE_ADR,
			    HW_ATL_TPS_DATA_TC_ARB_MODE_MSK,
			    HW_ATL_TPS_DATA_TC_ARB_MODE_SHIFT,
			    tx_pkt_shed_data_arb_mode);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_desc_rate_curr_समय_res_set(काष्ठा aq_hw_s *aq_hw,
							u32 curr_समय_res)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_RATE_TA_RST_ADR,
			    HW_ATL_TPS_DESC_RATE_TA_RST_MSK,
			    HW_ATL_TPS_DESC_RATE_TA_RST_SHIFT,
			    curr_समय_res);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_desc_rate_lim_set(काष्ठा aq_hw_s *aq_hw,
					      u32 tx_pkt_shed_desc_rate_lim)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_RATE_LIM_ADR,
			    HW_ATL_TPS_DESC_RATE_LIM_MSK,
			    HW_ATL_TPS_DESC_RATE_LIM_SHIFT,
			    tx_pkt_shed_desc_rate_lim);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_desc_tc_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
						 u32 arb_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_TC_ARB_MODE_ADR,
			    HW_ATL_TPS_DESC_TC_ARB_MODE_MSK,
			    HW_ATL_TPS_DESC_TC_ARB_MODE_SHIFT,
			    arb_mode);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_desc_tc_max_credit_set(काष्ठा aq_hw_s *aq_hw,
						   स्थिर u32 tc,
						   स्थिर u32 max_credit)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_TCTCREDIT_MAX_ADR(tc),
			    HW_ATL_TPS_DESC_TCTCREDIT_MAX_MSK,
			    HW_ATL_TPS_DESC_TCTCREDIT_MAX_SHIFT,
			    max_credit);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_desc_tc_weight_set(काष्ठा aq_hw_s *aq_hw,
					       स्थिर u32 tc,
					       स्थिर u32 weight)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_TCTWEIGHT_ADR(tc),
			    HW_ATL_TPS_DESC_TCTWEIGHT_MSK,
			    HW_ATL_TPS_DESC_TCTWEIGHT_SHIFT,
			    weight);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_desc_vm_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
						 u32 arb_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_VM_ARB_MODE_ADR,
			    HW_ATL_TPS_DESC_VM_ARB_MODE_MSK,
			    HW_ATL_TPS_DESC_VM_ARB_MODE_SHIFT,
			    arb_mode);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_tc_data_max_credit_set(काष्ठा aq_hw_s *aq_hw,
						   स्थिर u32 tc,
						   स्थिर u32 max_credit)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DATA_TCTCREDIT_MAX_ADR(tc),
			    HW_ATL_TPS_DATA_TCTCREDIT_MAX_MSK,
			    HW_ATL_TPS_DATA_TCTCREDIT_MAX_SHIFT,
			    max_credit);
पूर्ण

व्योम hw_atl_tps_tx_pkt_shed_tc_data_weight_set(काष्ठा aq_hw_s *aq_hw,
					       स्थिर u32 tc,
					       स्थिर u32 weight)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DATA_TCTWEIGHT_ADR(tc),
			    HW_ATL_TPS_DATA_TCTWEIGHT_MSK,
			    HW_ATL_TPS_DATA_TCTWEIGHT_SHIFT,
			    weight);
पूर्ण

व्योम hw_atl_tps_tx_desc_rate_mode_set(काष्ठा aq_hw_s *aq_hw,
				      स्थिर u32 rate_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_TX_DESC_RATE_MODE_ADR,
			    HW_ATL_TPS_TX_DESC_RATE_MODE_MSK,
			    HW_ATL_TPS_TX_DESC_RATE_MODE_SHIFT,
			    rate_mode);
पूर्ण

व्योम hw_atl_tps_tx_desc_rate_en_set(काष्ठा aq_hw_s *aq_hw, स्थिर u32 desc,
				    स्थिर u32 enable)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_RATE_EN_ADR(desc),
			    HW_ATL_TPS_DESC_RATE_EN_MSK,
			    HW_ATL_TPS_DESC_RATE_EN_SHIFT,
			    enable);
पूर्ण

व्योम hw_atl_tps_tx_desc_rate_x_set(काष्ठा aq_hw_s *aq_hw, स्थिर u32 desc,
				   स्थिर u32 rate_पूर्णांक)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_RATE_X_ADR(desc),
			    HW_ATL_TPS_DESC_RATE_X_MSK,
			    HW_ATL_TPS_DESC_RATE_X_SHIFT,
			    rate_पूर्णांक);
पूर्ण

व्योम hw_atl_tps_tx_desc_rate_y_set(काष्ठा aq_hw_s *aq_hw, स्थिर u32 desc,
				   स्थिर u32 rate_frac)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TPS_DESC_RATE_Y_ADR(desc),
			    HW_ATL_TPS_DESC_RATE_Y_MSK,
			    HW_ATL_TPS_DESC_RATE_Y_SHIFT,
			    rate_frac);
पूर्ण

/* tx */
व्योम hw_atl_tx_tx_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 tx_reg_res_dis)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_TX_REG_RES_DSBL_ADR,
			    HW_ATL_TX_REG_RES_DSBL_MSK,
			    HW_ATL_TX_REG_RES_DSBL_SHIFT, tx_reg_res_dis);
पूर्ण

/* msm */
u32 hw_atl_msm_reg_access_status_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_MSM_REG_ACCESS_BUSY_ADR,
				  HW_ATL_MSM_REG_ACCESS_BUSY_MSK,
				  HW_ATL_MSM_REG_ACCESS_BUSY_SHIFT);
पूर्ण

व्योम hw_atl_msm_reg_addr_क्रम_indirect_addr_set(काष्ठा aq_hw_s *aq_hw,
					       u32 reg_addr_क्रम_indirect_addr)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_MSM_REG_ADDR_ADR,
			    HW_ATL_MSM_REG_ADDR_MSK,
			    HW_ATL_MSM_REG_ADDR_SHIFT,
			    reg_addr_क्रम_indirect_addr);
पूर्ण

व्योम hw_atl_msm_reg_rd_strobe_set(काष्ठा aq_hw_s *aq_hw, u32 reg_rd_strobe)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_MSM_REG_RD_STROBE_ADR,
			    HW_ATL_MSM_REG_RD_STROBE_MSK,
			    HW_ATL_MSM_REG_RD_STROBE_SHIFT,
			    reg_rd_strobe);
पूर्ण

u32 hw_atl_msm_reg_rd_data_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_MSM_REG_RD_DATA_ADR);
पूर्ण

व्योम hw_atl_msm_reg_wr_data_set(काष्ठा aq_hw_s *aq_hw, u32 reg_wr_data)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_MSM_REG_WR_DATA_ADR, reg_wr_data);
पूर्ण

व्योम hw_atl_msm_reg_wr_strobe_set(काष्ठा aq_hw_s *aq_hw, u32 reg_wr_strobe)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_MSM_REG_WR_STROBE_ADR,
			    HW_ATL_MSM_REG_WR_STROBE_MSK,
			    HW_ATL_MSM_REG_WR_STROBE_SHIFT,
			    reg_wr_strobe);
पूर्ण

/* pci */
व्योम hw_atl_pci_pci_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 pci_reg_res_dis)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_PCI_REG_RES_DSBL_ADR,
			    HW_ATL_PCI_REG_RES_DSBL_MSK,
			    HW_ATL_PCI_REG_RES_DSBL_SHIFT,
			    pci_reg_res_dis);
पूर्ण

व्योम hw_atl_reg_glb_cpu_scratch_scp_set(काष्ठा aq_hw_s *aq_hw,
					u32 glb_cpu_scratch_scp,
					u32 scratch_scp)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GLB_CPU_SCRATCH_SCP_ADR(scratch_scp),
			glb_cpu_scratch_scp);
पूर्ण

व्योम hw_atl_pcs_ptp_घड़ी_पढ़ो_enable(काष्ठा aq_hw_s *aq_hw,
				      u32 ptp_घड़ी_पढ़ो_enable)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_ADR,
			    HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_MSK,
			    HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_SHIFT,
			    ptp_घड़ी_पढ़ो_enable);
पूर्ण

u32 hw_atl_pcs_ptp_घड़ी_get(काष्ठा aq_hw_s *aq_hw, u32 index)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_PCS_PTP_TS_VAL_ADDR(index));
पूर्ण

व्योम hw_atl_mcp_up_क्रमce_पूर्णांकr_set(काष्ठा aq_hw_s *aq_hw, u32 up_क्रमce_पूर्णांकr)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL_MCP_UP_FORCE_INTERRUPT_ADR,
			    HW_ATL_MCP_UP_FORCE_INTERRUPT_MSK,
			    HW_ATL_MCP_UP_FORCE_INTERRUPT_SHIFT,
			    up_क्रमce_पूर्णांकr);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv4_dest_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPF_L3_DSTA_ADR(location), 0U);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv4_src_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPF_L3_SRCA_ADR(location), 0U);
पूर्ण

व्योम hw_atl_rpfl3l4_cmd_clear(काष्ठा aq_hw_s *aq_hw, u8 location)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPF_L3_REG_CTRL_ADR(location), 0U);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv6_dest_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i)
		aq_hw_ग_लिखो_reg(aq_hw,
				HW_ATL_RPF_L3_DSTA_ADR(location + i),
				0U);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv6_src_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i)
		aq_hw_ग_लिखो_reg(aq_hw,
				HW_ATL_RPF_L3_SRCA_ADR(location + i),
				0U);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv4_dest_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				       u32 ipv4_dest)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPF_L3_DSTA_ADR(location),
			ipv4_dest);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv4_src_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				      u32 ipv4_src)
अणु
	aq_hw_ग_लिखो_reg(aq_hw,
			HW_ATL_RPF_L3_SRCA_ADR(location),
			ipv4_src);
पूर्ण

व्योम hw_atl_rpfl3l4_cmd_set(काष्ठा aq_hw_s *aq_hw, u8 location, u32 cmd)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_RPF_L3_REG_CTRL_ADR(location), cmd);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv6_src_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				      u32 *ipv6_src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i)
		aq_hw_ग_लिखो_reg(aq_hw,
				HW_ATL_RPF_L3_SRCA_ADR(location + i),
				ipv6_src[3 - i]);
पूर्ण

व्योम hw_atl_rpfl3l4_ipv6_dest_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				       u32 *ipv6_dest)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i)
		aq_hw_ग_लिखो_reg(aq_hw,
				HW_ATL_RPF_L3_DSTA_ADR(location + i),
				ipv6_dest[3 - i]);
पूर्ण

u32 hw_atl_sem_ram_get(काष्ठा aq_hw_s *self)
अणु
	वापस hw_atl_reg_glb_cpu_sem_get(self, HW_ATL_FW_SM_RAM);
पूर्ण

u32 hw_atl_sem_mdio_get(काष्ठा aq_hw_s *self)
अणु
	वापस hw_atl_reg_glb_cpu_sem_get(self, HW_ATL_FW_SM_MDIO);
पूर्ण

u32 hw_atl_sem_reset1_get(काष्ठा aq_hw_s *self)
अणु
	वापस hw_atl_reg_glb_cpu_sem_get(self, HW_ATL_FW_SM_RESET1);
पूर्ण

u32 hw_atl_sem_reset2_get(काष्ठा aq_hw_s *self)
अणु
	वापस hw_atl_reg_glb_cpu_sem_get(self, HW_ATL_FW_SM_RESET2);
पूर्ण

u32 hw_atl_scrpad_get(काष्ठा aq_hw_s *aq_hw, u32 scratch_scp)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw,
			      HW_ATL_GLB_CPU_SCRATCH_SCP_ADR(scratch_scp));
पूर्ण

u32 hw_atl_scrpad12_get(काष्ठा aq_hw_s *self)
अणु
	वापस  hw_atl_scrpad_get(self, 0xB);
पूर्ण

u32 hw_atl_scrpad25_get(काष्ठा aq_hw_s *self)
अणु
	वापस hw_atl_scrpad_get(self, 0x18);
पूर्ण

व्योम hw_atl_glb_mdio_अगरace1_set(काष्ठा aq_hw_s *aq_hw, u32 value)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(1), value);
पूर्ण

u32 hw_atl_glb_mdio_अगरace1_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(1));
पूर्ण

व्योम hw_atl_glb_mdio_अगरace2_set(काष्ठा aq_hw_s *aq_hw, u32 value)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(2), value);
पूर्ण

u32 hw_atl_glb_mdio_अगरace2_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(2));
पूर्ण

व्योम hw_atl_glb_mdio_अगरace3_set(काष्ठा aq_hw_s *aq_hw, u32 value)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(3), value);
पूर्ण

u32 hw_atl_glb_mdio_अगरace3_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(3));
पूर्ण

व्योम hw_atl_glb_mdio_अगरace4_set(काष्ठा aq_hw_s *aq_hw, u32 value)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(4), value);
पूर्ण

u32 hw_atl_glb_mdio_अगरace4_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(4));
पूर्ण

व्योम hw_atl_glb_mdio_अगरace5_set(काष्ठा aq_hw_s *aq_hw, u32 value)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(5), value);
पूर्ण

u32 hw_atl_glb_mdio_अगरace5_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL_GLB_MDIO_IFACE_N_ADR(5));
पूर्ण

u32 hw_atl_mdio_busy_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL_MDIO_BUSY_ADR,
				  HW_ATL_MDIO_BUSY_MSK,
				  HW_ATL_MDIO_BUSY_SHIFT);
पूर्ण
