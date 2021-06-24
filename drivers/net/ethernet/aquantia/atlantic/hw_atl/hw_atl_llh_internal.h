<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_llh_पूर्णांकernal.h: Preprocessor definitions
 * क्रम Atlantic रेजिस्टरs.
 */

#अगर_अघोषित HW_ATL_LLH_INTERNAL_H
#घोषणा HW_ATL_LLH_INTERNAL_H

/* COM Temperature Sense Reset Bitfield Definitions */
#घोषणा HW_ATL_TS_RESET_ADR 0x00003100
#घोषणा HW_ATL_TS_RESET_MSK 0x00000004
#घोषणा HW_ATL_TS_RESET_SHIFT 2
#घोषणा HW_ATL_TS_RESET_WIDTH 1

/* COM Temperature Sense Power Down Bitfield Definitions */
#घोषणा HW_ATL_TS_POWER_DOWN_ADR 0x00003100
#घोषणा HW_ATL_TS_POWER_DOWN_MSK 0x00000001
#घोषणा HW_ATL_TS_POWER_DOWN_SHIFT 0
#घोषणा HW_ATL_TS_POWER_DOWN_WIDTH 1

/* COM Temperature Sense Ready Bitfield Definitions */
#घोषणा HW_ATL_TS_READY_ADR 0x00003120
#घोषणा HW_ATL_TS_READY_MSK 0x80000000
#घोषणा HW_ATL_TS_READY_SHIFT 31
#घोषणा HW_ATL_TS_READY_WIDTH 1

/*  COM Temperature Sense Ready Latch High Bitfield Definitions */
#घोषणा HW_ATL_TS_READY_LATCH_HIGH_ADR 0x00003120
#घोषणा HW_ATL_TS_READY_LATCH_HIGH_MSK 0x40000000
#घोषणा HW_ATL_TS_READY_LATCH_HIGH_SHIFT 30
#घोषणा HW_ATL_TS_READY_LATCH_HIGH_WIDTH 1

/* COM Temperature Sense Data Out [B:0] Bitfield Definitions */
#घोषणा HW_ATL_TS_DATA_OUT_ADR 0x00003120
#घोषणा HW_ATL_TS_DATA_OUT_MSK 0x00000FFF
#घोषणा HW_ATL_TS_DATA_OUT_SHIFT 0
#घोषणा HW_ATL_TS_DATA_OUT_WIDTH 12

/* global microprocessor semaphore  definitions
 * base address: 0x000003a0
 * parameter: semaphore अणुsपूर्ण | stride size 0x4 | range [0, 15]
 */
#घोषणा HW_ATL_GLB_CPU_SEM_ADR(semaphore)  (0x000003a0u + (semaphore) * 0x4)
/* रेजिस्टर address क्रम bitfield rx dma good octet counter lsw [1f:0] */
#घोषणा HW_ATL_STATS_RX_DMA_GOOD_OCTET_COUNTERLSW 0x00006808
/* रेजिस्टर address क्रम bitfield rx dma good packet counter lsw [1f:0] */
#घोषणा HW_ATL_STATS_RX_DMA_GOOD_PKT_COUNTERLSW 0x00006800
/* रेजिस्टर address क्रम bitfield tx dma good octet counter lsw [1f:0] */
#घोषणा HW_ATL_STATS_TX_DMA_GOOD_OCTET_COUNTERLSW 0x00008808
/* रेजिस्टर address क्रम bitfield tx dma good packet counter lsw [1f:0] */
#घोषणा HW_ATL_STATS_TX_DMA_GOOD_PKT_COUNTERLSW 0x00008800

/* रेजिस्टर address क्रम bitfield rx dma good octet counter msw [3f:20] */
#घोषणा HW_ATL_STATS_RX_DMA_GOOD_OCTET_COUNTERMSW 0x0000680c
/* रेजिस्टर address क्रम bitfield rx dma good packet counter msw [3f:20] */
#घोषणा HW_ATL_STATS_RX_DMA_GOOD_PKT_COUNTERMSW 0x00006804
/* रेजिस्टर address क्रम bitfield tx dma good octet counter msw [3f:20] */
#घोषणा HW_ATL_STATS_TX_DMA_GOOD_OCTET_COUNTERMSW 0x0000880c
/* रेजिस्टर address क्रम bitfield tx dma good packet counter msw [3f:20] */
#घोषणा HW_ATL_STATS_TX_DMA_GOOD_PKT_COUNTERMSW 0x00008804

/* preprocessor definitions क्रम msm rx errors counter रेजिस्टर */
#घोषणा HW_ATL_MAC_MSM_RX_ERRS_CNT_ADR 0x00000120u

/* preprocessor definitions क्रम msm rx unicast frames counter रेजिस्टर */
#घोषणा HW_ATL_MAC_MSM_RX_UCST_FRM_CNT_ADR 0x000000e0u

/* preprocessor definitions क्रम msm rx multicast frames counter रेजिस्टर */
#घोषणा HW_ATL_MAC_MSM_RX_MCST_FRM_CNT_ADR 0x000000e8u

/* preprocessor definitions क्रम msm rx broadcast frames counter रेजिस्टर */
#घोषणा HW_ATL_MAC_MSM_RX_BCST_FRM_CNT_ADR 0x000000f0u

/* preprocessor definitions क्रम msm rx broadcast octets counter रेजिस्टर 1 */
#घोषणा HW_ATL_MAC_MSM_RX_BCST_OCTETS_COUNTER1_ADR 0x000001b0u

/* preprocessor definitions क्रम msm rx broadcast octets counter रेजिस्टर 2 */
#घोषणा HW_ATL_MAC_MSM_RX_BCST_OCTETS_COUNTER2_ADR 0x000001b4u

/* preprocessor definitions क्रम msm rx unicast octets counter रेजिस्टर 0 */
#घोषणा HW_ATL_MAC_MSM_RX_UCST_OCTETS_COUNTER0_ADR 0x000001b8u

/* preprocessor definitions क्रम msm tx unicast frames counter रेजिस्टर */
#घोषणा HW_ATL_MAC_MSM_TX_UCST_FRM_CNT_ADR 0x00000108u

/* preprocessor definitions क्रम msm tx multicast frames counter रेजिस्टर */
#घोषणा HW_ATL_MAC_MSM_TX_MCST_FRM_CNT_ADR 0x00000110u

/* preprocessor definitions क्रम global mअगर identअगरication */
#घोषणा HW_ATL_GLB_MIF_ID_ADR 0x0000001cu

/* रेजिस्टर address क्रम bitfield iamr_lsw[1f:0] */
#घोषणा HW_ATL_ITR_IAMRLSW_ADR 0x00002090
/* रेजिस्टर address क्रम bitfield rx dma drop packet counter [1f:0] */
#घोषणा HW_ATL_RPB_RX_DMA_DROP_PKT_CNT_ADR 0x00006818

/* रेजिस्टर address क्रम bitfield imcr_lsw[1f:0] */
#घोषणा HW_ATL_ITR_IMCRLSW_ADR 0x00002070
/* रेजिस्टर address क्रम bitfield imsr_lsw[1f:0] */
#घोषणा HW_ATL_ITR_IMSRLSW_ADR 0x00002060
/* रेजिस्टर address क्रम bitfield itr_reg_res_dsbl */
#घोषणा HW_ATL_ITR_REG_RES_DSBL_ADR 0x00002300
/* biपंचांगask क्रम bitfield itr_reg_res_dsbl */
#घोषणा HW_ATL_ITR_REG_RES_DSBL_MSK 0x20000000
/* lower bit position of bitfield itr_reg_res_dsbl */
#घोषणा HW_ATL_ITR_REG_RES_DSBL_SHIFT 29
/* रेजिस्टर address क्रम bitfield iscr_lsw[1f:0] */
#घोषणा HW_ATL_ITR_ISCRLSW_ADR 0x00002050
/* रेजिस्टर address क्रम bitfield isr_lsw[1f:0] */
#घोषणा HW_ATL_ITR_ISRLSW_ADR 0x00002000
/* रेजिस्टर address क्रम bitfield itr_reset */
#घोषणा HW_ATL_ITR_RES_ADR 0x00002300
/* biपंचांगask क्रम bitfield itr_reset */
#घोषणा HW_ATL_ITR_RES_MSK 0x80000000
/* lower bit position of bitfield itr_reset */
#घोषणा HW_ATL_ITR_RES_SHIFT 31

/* रेजिस्टर address क्रम bitfield  rsc_en */
#घोषणा HW_ATL_ITR_RSC_EN_ADR 0x00002200

/* रेजिस्टर address क्रम bitfield  rsc_delay */
#घोषणा HW_ATL_ITR_RSC_DELAY_ADR 0x00002204
/* biपंचांगask क्रम bitfield  rsc_delay */
#घोषणा HW_ATL_ITR_RSC_DELAY_MSK 0x0000000f
/* width of bitfield  rsc_delay */
#घोषणा HW_ATL_ITR_RSC_DELAY_WIDTH 4
/* lower bit position of bitfield  rsc_delay */
#घोषणा HW_ATL_ITR_RSC_DELAY_SHIFT 0

/* रेजिस्टर address क्रम bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_RDM_DCADCPUID_ADR(dca) (0x00006100 + (dca) * 0x4)
/* biपंचांगask क्रम bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_RDM_DCADCPUID_MSK 0x000000ff
/* lower bit position of bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_RDM_DCADCPUID_SHIFT 0
/* रेजिस्टर address क्रम bitfield dca_en */
#घोषणा HW_ATL_RDM_DCA_EN_ADR 0x00006180

/* rx dca_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca_en".
 * port="pif_rdm_dca_en_i"
 */

/* रेजिस्टर address क्रम bitfield dca_en */
#घोषणा HW_ATL_RDM_DCA_EN_ADR 0x00006180
/* biपंचांगask क्रम bitfield dca_en */
#घोषणा HW_ATL_RDM_DCA_EN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield dca_en */
#घोषणा HW_ATL_RDM_DCA_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dca_en */
#घोषणा HW_ATL_RDM_DCA_EN_SHIFT 31
/* width of bitfield dca_en */
#घोषणा HW_ATL_RDM_DCA_EN_WIDTH 1
/* शेष value of bitfield dca_en */
#घोषणा HW_ATL_RDM_DCA_EN_DEFAULT 0x1

/* rx dca_mode[3:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca_mode[3:0]".
 * port="pif_rdm_dca_mode_i[3:0]"
 */

/* रेजिस्टर address क्रम bitfield dca_mode[3:0] */
#घोषणा HW_ATL_RDM_DCA_MODE_ADR 0x00006180
/* biपंचांगask क्रम bitfield dca_mode[3:0] */
#घोषणा HW_ATL_RDM_DCA_MODE_MSK 0x0000000f
/* inverted biपंचांगask क्रम bitfield dca_mode[3:0] */
#घोषणा HW_ATL_RDM_DCA_MODE_MSKN 0xfffffff0
/* lower bit position of bitfield dca_mode[3:0] */
#घोषणा HW_ATL_RDM_DCA_MODE_SHIFT 0
/* width of bitfield dca_mode[3:0] */
#घोषणा HW_ATL_RDM_DCA_MODE_WIDTH 4
/* शेष value of bitfield dca_mode[3:0] */
#घोषणा HW_ATL_RDM_DCA_MODE_DEFAULT 0x0

/* rx descअणुdपूर्ण_data_size[4:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_data_size[4:0]".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc0_data_size_i[4:0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_data_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDDATA_SIZE_ADR(descriptor) \
	(0x00005b18 + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_data_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDDATA_SIZE_MSK 0x0000001f
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_data_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDDATA_SIZE_MSKN 0xffffffe0
/* lower bit position of bitfield descअणुdपूर्ण_data_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDDATA_SIZE_SHIFT 0
/* width of bitfield descअणुdपूर्ण_data_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDDATA_SIZE_WIDTH 5
/* शेष value of bitfield descअणुdपूर्ण_data_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDDATA_SIZE_DEFAULT 0x0

/* rx dcaअणुdपूर्ण_desc_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca{d}_desc_en".
 * parameter: dca अणुdपूर्ण | stride size 0x4 | range [0, 31]
 * port="pif_rdm_dca_desc_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_RDM_DCADDESC_EN_ADR(dca) (0x00006100 + (dca) * 0x4)
/* biपंचांगask क्रम bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_RDM_DCADDESC_EN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_RDM_DCADDESC_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_RDM_DCADDESC_EN_SHIFT 31
/* width of bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_RDM_DCADDESC_EN_WIDTH 1
/* शेष value of bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_RDM_DCADDESC_EN_DEFAULT 0x0

/* rx descअणुdपूर्ण_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_en".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_RDM_DESCDEN_ADR(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_RDM_DESCDEN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_RDM_DESCDEN_MSKN 0x7fffffff
/* lower bit position of bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_RDM_DESCDEN_SHIFT 31
/* width of bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_RDM_DESCDEN_WIDTH 1
/* शेष value of bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_RDM_DESCDEN_DEFAULT 0x0

/* rx descअणुdपूर्ण_hdr_size[4:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_hdr_size[4:0]".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc0_hdr_size_i[4:0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_hdr_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDHDR_SIZE_ADR(descriptor) \
	(0x00005b18 + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_hdr_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDHDR_SIZE_MSK 0x00001f00
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_hdr_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDHDR_SIZE_MSKN 0xffffe0ff
/* lower bit position of bitfield descअणुdपूर्ण_hdr_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDHDR_SIZE_SHIFT 8
/* width of bitfield descअणुdपूर्ण_hdr_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDHDR_SIZE_WIDTH 5
/* शेष value of bitfield descअणुdपूर्ण_hdr_size[4:0] */
#घोषणा HW_ATL_RDM_DESCDHDR_SIZE_DEFAULT 0x0

/* rx descअणुdपूर्ण_hdr_split bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_hdr_split".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc_hdr_split_i[0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_hdr_split */
#घोषणा HW_ATL_RDM_DESCDHDR_SPLIT_ADR(descriptor) \
	(0x00005b08 + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_hdr_split */
#घोषणा HW_ATL_RDM_DESCDHDR_SPLIT_MSK 0x10000000
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_hdr_split */
#घोषणा HW_ATL_RDM_DESCDHDR_SPLIT_MSKN 0xefffffff
/* lower bit position of bitfield descअणुdपूर्ण_hdr_split */
#घोषणा HW_ATL_RDM_DESCDHDR_SPLIT_SHIFT 28
/* width of bitfield descअणुdपूर्ण_hdr_split */
#घोषणा HW_ATL_RDM_DESCDHDR_SPLIT_WIDTH 1
/* शेष value of bitfield descअणुdपूर्ण_hdr_split */
#घोषणा HW_ATL_RDM_DESCDHDR_SPLIT_DEFAULT 0x0

/* rx descअणुdपूर्ण_hd[c:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_hd[c:0]".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="rdm_pif_desc0_hd_o[12:0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_RDM_DESCDHD_ADR(descriptor) (0x00005b0c + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_RDM_DESCDHD_MSK 0x00001fff
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_RDM_DESCDHD_MSKN 0xffffe000
/* lower bit position of bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_RDM_DESCDHD_SHIFT 0
/* width of bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_RDM_DESCDHD_WIDTH 13

/* rx descअणुdपूर्ण_len[9:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_len[9:0]".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc0_len_i[9:0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_RDM_DESCDLEN_ADR(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_RDM_DESCDLEN_MSK 0x00001ff8
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_RDM_DESCDLEN_MSKN 0xffffe007
/* lower bit position of bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_RDM_DESCDLEN_SHIFT 3
/* width of bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_RDM_DESCDLEN_WIDTH 10
/* शेष value of bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_RDM_DESCDLEN_DEFAULT 0x0

/* rx descअणुdपूर्ण_reset bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_reset".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="pif_rdm_q_pf_res_i[0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_reset */
#घोषणा HW_ATL_RDM_DESCDRESET_ADR(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_reset */
#घोषणा HW_ATL_RDM_DESCDRESET_MSK 0x02000000
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_reset */
#घोषणा HW_ATL_RDM_DESCDRESET_MSKN 0xfdffffff
/* lower bit position of bitfield descअणुdपूर्ण_reset */
#घोषणा HW_ATL_RDM_DESCDRESET_SHIFT 25
/* width of bitfield descअणुdपूर्ण_reset */
#घोषणा HW_ATL_RDM_DESCDRESET_WIDTH 1
/* शेष value of bitfield descअणुdपूर्ण_reset */
#घोषणा HW_ATL_RDM_DESCDRESET_DEFAULT 0x0

/* rdm_desc_init_i bitfield definitions
 * preprocessor definitions क्रम the bitfield rdm_desc_init_i.
 * port="pif_rdm_desc_init_i"
 */

/* रेजिस्टर address क्रम bitfield rdm_desc_init_i */
#घोषणा HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_ADR 0x00005a00
/* biपंचांगask क्रम bitfield rdm_desc_init_i */
#घोषणा HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSK 0xffffffff
/* inverted biपंचांगask क्रम bitfield rdm_desc_init_i */
#घोषणा HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSKN 0x00000000
/* lower bit position of bitfield  rdm_desc_init_i */
#घोषणा HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_SHIFT 0
/* width of bitfield rdm_desc_init_i */
#घोषणा HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_WIDTH 32
/* शेष value of bitfield rdm_desc_init_i */
#घोषणा HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_DEFAULT 0x0

/* rdm_desc_init_करोne_i bitfield definitions
 * preprocessor definitions क्रम the bitfield rdm_desc_init_करोne_i.
 * port="pif_rdm_desc_init_done_i"
 */

/* रेजिस्टर address क्रम bitfield rdm_desc_init_करोne_i */
#घोषणा RDM_RX_DMA_DESC_CACHE_INIT_DONE_ADR 0x00005a10
/* biपंचांगask क्रम bitfield rdm_desc_init_करोne_i */
#घोषणा RDM_RX_DMA_DESC_CACHE_INIT_DONE_MSK 0x00000001U
/* inverted biपंचांगask क्रम bitfield rdm_desc_init_करोne_i */
#घोषणा RDM_RX_DMA_DESC_CACHE_INIT_DONE_MSKN 0xfffffffe
/* lower bit position of bitfield  rdm_desc_init_करोne_i */
#घोषणा RDM_RX_DMA_DESC_CACHE_INIT_DONE_SHIFT 0U
/* width of bitfield rdm_desc_init_करोne_i */
#घोषणा RDM_RX_DMA_DESC_CACHE_INIT_DONE_WIDTH 1
/* शेष value of bitfield rdm_desc_init_करोne_i */
#घोषणा RDM_RX_DMA_DESC_CACHE_INIT_DONE_DEFAULT 0x0


/* rx पूर्णांक_desc_wrb_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "int_desc_wrb_en".
 * port="pif_rdm_int_desc_wrb_en_i"
 */

/* रेजिस्टर address क्रम bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_RDM_INT_DESC_WRB_EN_ADR 0x00005a30
/* biपंचांगask क्रम bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_RDM_INT_DESC_WRB_EN_MSK 0x00000004
/* inverted biपंचांगask क्रम bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_RDM_INT_DESC_WRB_EN_MSKN 0xfffffffb
/* lower bit position of bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_RDM_INT_DESC_WRB_EN_SHIFT 2
/* width of bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_RDM_INT_DESC_WRB_EN_WIDTH 1
/* शेष value of bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_RDM_INT_DESC_WRB_EN_DEFAULT 0x0

/* rx dcaअणुdपूर्ण_hdr_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca{d}_hdr_en".
 * parameter: dca अणुdपूर्ण | stride size 0x4 | range [0, 31]
 * port="pif_rdm_dca_hdr_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield dcaअणुdपूर्ण_hdr_en */
#घोषणा HW_ATL_RDM_DCADHDR_EN_ADR(dca) (0x00006100 + (dca) * 0x4)
/* biपंचांगask क्रम bitfield dcaअणुdपूर्ण_hdr_en */
#घोषणा HW_ATL_RDM_DCADHDR_EN_MSK 0x40000000
/* inverted biपंचांगask क्रम bitfield dcaअणुdपूर्ण_hdr_en */
#घोषणा HW_ATL_RDM_DCADHDR_EN_MSKN 0xbfffffff
/* lower bit position of bitfield dcaअणुdपूर्ण_hdr_en */
#घोषणा HW_ATL_RDM_DCADHDR_EN_SHIFT 30
/* width of bitfield dcaअणुdपूर्ण_hdr_en */
#घोषणा HW_ATL_RDM_DCADHDR_EN_WIDTH 1
/* शेष value of bitfield dcaअणुdपूर्ण_hdr_en */
#घोषणा HW_ATL_RDM_DCADHDR_EN_DEFAULT 0x0

/* rx dcaअणुdपूर्ण_pay_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca{d}_pay_en".
 * parameter: dca अणुdपूर्ण | stride size 0x4 | range [0, 31]
 * port="pif_rdm_dca_pay_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield dcaअणुdपूर्ण_pay_en */
#घोषणा HW_ATL_RDM_DCADPAY_EN_ADR(dca) (0x00006100 + (dca) * 0x4)
/* biपंचांगask क्रम bitfield dcaअणुdपूर्ण_pay_en */
#घोषणा HW_ATL_RDM_DCADPAY_EN_MSK 0x20000000
/* inverted biपंचांगask क्रम bitfield dcaअणुdपूर्ण_pay_en */
#घोषणा HW_ATL_RDM_DCADPAY_EN_MSKN 0xdfffffff
/* lower bit position of bitfield dcaअणुdपूर्ण_pay_en */
#घोषणा HW_ATL_RDM_DCADPAY_EN_SHIFT 29
/* width of bitfield dcaअणुdपूर्ण_pay_en */
#घोषणा HW_ATL_RDM_DCADPAY_EN_WIDTH 1
/* शेष value of bitfield dcaअणुdपूर्ण_pay_en */
#घोषणा HW_ATL_RDM_DCADPAY_EN_DEFAULT 0x0

/* RX rdm_पूर्णांक_rim_en Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "rdm_int_rim_en".
 * PORT="pif_rdm_int_rim_en_i"
 */

/* Register address क्रम bitfield rdm_पूर्णांक_rim_en */
#घोषणा HW_ATL_RDM_INT_RIM_EN_ADR 0x00005A30
/* Biपंचांगask क्रम bitfield rdm_पूर्णांक_rim_en */
#घोषणा HW_ATL_RDM_INT_RIM_EN_MSK 0x00000008
/* Inverted biपंचांगask क्रम bitfield rdm_पूर्णांक_rim_en */
#घोषणा HW_ATL_RDM_INT_RIM_EN_MSKN 0xFFFFFFF7
/* Lower bit position of bitfield rdm_पूर्णांक_rim_en */
#घोषणा HW_ATL_RDM_INT_RIM_EN_SHIFT 3
/* Width of bitfield rdm_पूर्णांक_rim_en */
#घोषणा HW_ATL_RDM_INT_RIM_EN_WIDTH 1
/* Default value of bitfield rdm_पूर्णांक_rim_en */
#घोषणा HW_ATL_RDM_INT_RIM_EN_DEFAULT 0x0

/* general पूर्णांकerrupt mapping रेजिस्टर definitions
 * preprocessor definitions क्रम general पूर्णांकerrupt mapping रेजिस्टर
 * base address: 0x00002180
 * parameter: regidx अणुfपूर्ण | stride size 0x4 | range [0, 3]
 */
#घोषणा HW_ATL_GEN_INTR_MAP_ADR(regidx) (0x00002180u + (regidx) * 0x4)

/* general पूर्णांकerrupt status रेजिस्टर definitions
 * preprocessor definitions क्रम general पूर्णांकerrupt status रेजिस्टर
 * address: 0x000021A0
 */

#घोषणा HW_ATL_GEN_INTR_STAT_ADR 0x000021A4U

/* पूर्णांकerrupt global control रेजिस्टर  definitions
 * preprocessor definitions क्रम पूर्णांकerrupt global control रेजिस्टर
 * address: 0x00002300
 */
#घोषणा HW_ATL_INTR_GLB_CTL_ADR 0x00002300u

/* पूर्णांकerrupt throttle रेजिस्टर definitions
 * preprocessor definitions क्रम पूर्णांकerrupt throttle रेजिस्टर
 * base address: 0x00002800
 * parameter: throttle अणुtपूर्ण | stride size 0x4 | range [0, 31]
 */
#घोषणा HW_ATL_INTR_THR_ADR(throttle) (0x00002800u + (throttle) * 0x4)

/* rx dma descriptor base address lsw definitions
 * preprocessor definitions क्रम rx dma descriptor base address lsw
 * base address: 0x00005b00
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 */
#घोषणा HW_ATL_RX_DMA_DESC_BASE_ADDRLSW_ADR(descriptor) \
(0x00005b00u + (descriptor) * 0x20)

/* rx dma descriptor base address msw definitions
 * preprocessor definitions क्रम rx dma descriptor base address msw
 * base address: 0x00005b04
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 */
#घोषणा HW_ATL_RX_DMA_DESC_BASE_ADDRMSW_ADR(descriptor) \
(0x00005b04u + (descriptor) * 0x20)

/* rx dma descriptor status रेजिस्टर definitions
 * preprocessor definitions क्रम rx dma descriptor status रेजिस्टर
 * base address: 0x00005b14
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 */
#घोषणा HW_ATL_RX_DMA_DESC_STAT_ADR(descriptor) \
	(0x00005b14u + (descriptor) * 0x20)

/* rx dma descriptor tail poपूर्णांकer रेजिस्टर definitions
 * preprocessor definitions क्रम rx dma descriptor tail poपूर्णांकer रेजिस्टर
 * base address: 0x00005b10
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 */
#घोषणा HW_ATL_RX_DMA_DESC_TAIL_PTR_ADR(descriptor) \
	(0x00005b10u + (descriptor) * 0x20)

/* rx पूर्णांकerrupt moderation control रेजिस्टर definitions
 * Preprocessor definitions क्रम RX Interrupt Moderation Control Register
 * Base Address: 0x00005A40
 * Parameter: RIM अणुRपूर्ण | stride size 0x4 | range [0, 31]
 */
#घोषणा HW_ATL_RX_INTR_MODERATION_CTL_ADR(rim) (0x00005A40u + (rim) * 0x4)

/* rx filter multicast filter mask रेजिस्टर definitions
 * preprocessor definitions क्रम rx filter multicast filter mask रेजिस्टर
 * address: 0x00005270
 */
#घोषणा HW_ATL_RX_FLR_MCST_FLR_MSK_ADR 0x00005270u

/* rx filter multicast filter रेजिस्टर definitions
 * preprocessor definitions क्रम rx filter multicast filter रेजिस्टर
 * base address: 0x00005250
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 7]
 */
#घोषणा HW_ATL_RX_FLR_MCST_FLR_ADR(filter) (0x00005250u + (filter) * 0x4)

/* RX Filter RSS Control Register 1 Definitions
 * Preprocessor definitions क्रम RX Filter RSS Control Register 1
 * Address: 0x000054C0
 */
#घोषणा HW_ATL_RX_FLR_RSS_CONTROL1_ADR 0x000054C0u

/* RX Filter Control Register 2 Definitions
 * Preprocessor definitions क्रम RX Filter Control Register 2
 * Address: 0x00005104
 */
#घोषणा HW_ATL_RX_FLR_CONTROL2_ADR 0x00005104u

/* tx tx dma debug control [1f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx dma debug control [1f:0]".
 * port="pif_tdm_debug_cntl_i[31:0]"
 */

/* रेजिस्टर address क्रम bitfield tx dma debug control [1f:0] */
#घोषणा HW_ATL_TDM_TX_DMA_DEBUG_CTL_ADR 0x00008920
/* biपंचांगask क्रम bitfield tx dma debug control [1f:0] */
#घोषणा HW_ATL_TDM_TX_DMA_DEBUG_CTL_MSK 0xffffffff
/* inverted biपंचांगask क्रम bitfield tx dma debug control [1f:0] */
#घोषणा HW_ATL_TDM_TX_DMA_DEBUG_CTL_MSKN 0x00000000
/* lower bit position of bitfield tx dma debug control [1f:0] */
#घोषणा HW_ATL_TDM_TX_DMA_DEBUG_CTL_SHIFT 0
/* width of bitfield tx dma debug control [1f:0] */
#घोषणा HW_ATL_TDM_TX_DMA_DEBUG_CTL_WIDTH 32
/* शेष value of bitfield tx dma debug control [1f:0] */
#घोषणा HW_ATL_TDM_TX_DMA_DEBUG_CTL_DEFAULT 0x0

/* tx dma descriptor base address lsw definitions
 * preprocessor definitions क्रम tx dma descriptor base address lsw
 * base address: 0x00007c00
 * parameter: descriptor अणुdपूर्ण | stride size 0x40 | range [0, 31]
 */
#घोषणा HW_ATL_TX_DMA_DESC_BASE_ADDRLSW_ADR(descriptor) \
	(0x00007c00u + (descriptor) * 0x40)

/* tx dma descriptor tail poपूर्णांकer रेजिस्टर definitions
 * preprocessor definitions क्रम tx dma descriptor tail poपूर्णांकer रेजिस्टर
 * base address: 0x00007c10
 *  parameter: descriptor अणुdपूर्ण | stride size 0x40 | range [0, 31]
 */
#घोषणा HW_ATL_TX_DMA_DESC_TAIL_PTR_ADR(descriptor) \
	(0x00007c10u + (descriptor) * 0x40)

/* rx dma_sys_loopback bitfield definitions
 * preprocessor definitions क्रम the bitfield "dma_sys_loopback".
 * port="pif_rpb_dma_sys_lbk_i"
 */

/* रेजिस्टर address क्रम bitfield dma_sys_loopback */
#घोषणा HW_ATL_RPB_DMA_SYS_LBK_ADR 0x00005000
/* biपंचांगask क्रम bitfield dma_sys_loopback */
#घोषणा HW_ATL_RPB_DMA_SYS_LBK_MSK 0x00000040
/* inverted biपंचांगask क्रम bitfield dma_sys_loopback */
#घोषणा HW_ATL_RPB_DMA_SYS_LBK_MSKN 0xffffffbf
/* lower bit position of bitfield dma_sys_loopback */
#घोषणा HW_ATL_RPB_DMA_SYS_LBK_SHIFT 6
/* width of bitfield dma_sys_loopback */
#घोषणा HW_ATL_RPB_DMA_SYS_LBK_WIDTH 1
/* शेष value of bitfield dma_sys_loopback */
#घोषणा HW_ATL_RPB_DMA_SYS_LBK_DEFAULT 0x0

/* rx dma_net_loopback bitfield definitions
 * preprocessor definitions क्रम the bitfield "dma_net_loopback".
 * port="pif_rpb_dma_net_lbk_i"
 */

/* रेजिस्टर address क्रम bitfield dma_net_loopback */
#घोषणा HW_ATL_RPB_DMA_NET_LBK_ADR 0x00005000
/* biपंचांगask क्रम bitfield dma_net_loopback */
#घोषणा HW_ATL_RPB_DMA_NET_LBK_MSK 0x00000010
/* inverted biपंचांगask क्रम bitfield dma_net_loopback */
#घोषणा HW_ATL_RPB_DMA_NET_LBK_MSKN 0xffffffef
/* lower bit position of bitfield dma_net_loopback */
#घोषणा HW_ATL_RPB_DMA_NET_LBK_SHIFT 4
/* width of bitfield dma_net_loopback */
#घोषणा HW_ATL_RPB_DMA_NET_LBK_WIDTH 1
/* शेष value of bitfield dma_net_loopback */
#घोषणा HW_ATL_RPB_DMA_NET_LBK_DEFAULT 0x0

/* rx rx_tc_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "rx_tc_mode".
 * port="pif_rpb_rx_tc_mode_i,pif_rpf_rx_tc_mode_i"
 */

/* रेजिस्टर address क्रम bitfield rx_tc_mode */
#घोषणा HW_ATL_RPB_RPF_RX_TC_MODE_ADR 0x00005700
/* biपंचांगask क्रम bitfield rx_tc_mode */
#घोषणा HW_ATL_RPB_RPF_RX_TC_MODE_MSK 0x00000100
/* inverted biपंचांगask क्रम bitfield rx_tc_mode */
#घोषणा HW_ATL_RPB_RPF_RX_TC_MODE_MSKN 0xfffffeff
/* lower bit position of bitfield rx_tc_mode */
#घोषणा HW_ATL_RPB_RPF_RX_TC_MODE_SHIFT 8
/* width of bitfield rx_tc_mode */
#घोषणा HW_ATL_RPB_RPF_RX_TC_MODE_WIDTH 1
/* शेष value of bitfield rx_tc_mode */
#घोषणा HW_ATL_RPB_RPF_RX_TC_MODE_DEFAULT 0x0

/* rx rx_buf_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "rx_buf_en".
 * port="pif_rpb_rx_buf_en_i"
 */

/* रेजिस्टर address क्रम bitfield rx_buf_en */
#घोषणा HW_ATL_RPB_RX_BUF_EN_ADR 0x00005700
/* biपंचांगask क्रम bitfield rx_buf_en */
#घोषणा HW_ATL_RPB_RX_BUF_EN_MSK 0x00000001
/* inverted biपंचांगask क्रम bitfield rx_buf_en */
#घोषणा HW_ATL_RPB_RX_BUF_EN_MSKN 0xfffffffe
/* lower bit position of bitfield rx_buf_en */
#घोषणा HW_ATL_RPB_RX_BUF_EN_SHIFT 0
/* width of bitfield rx_buf_en */
#घोषणा HW_ATL_RPB_RX_BUF_EN_WIDTH 1
/* शेष value of bitfield rx_buf_en */
#घोषणा HW_ATL_RPB_RX_BUF_EN_DEFAULT 0x0

/* rx rxअणुbपूर्ण_hi_thresh[d:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rx{b}_hi_thresh[d:0]".
 * parameter: buffer अणुbपूर्ण | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx0_hi_thresh_i[13:0]"
 */

/* रेजिस्टर address क्रम bitfield rxअणुbपूर्ण_hi_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBHI_THRESH_ADR(buffer) (0x00005714 + (buffer) * 0x10)
/* biपंचांगask क्रम bitfield rxअणुbपूर्ण_hi_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBHI_THRESH_MSK 0x3fff0000
/* inverted biपंचांगask क्रम bitfield rxअणुbपूर्ण_hi_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBHI_THRESH_MSKN 0xc000ffff
/* lower bit position of bitfield rxअणुbपूर्ण_hi_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBHI_THRESH_SHIFT 16
/* width of bitfield rxअणुbपूर्ण_hi_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBHI_THRESH_WIDTH 14
/* शेष value of bitfield rxअणुbपूर्ण_hi_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBHI_THRESH_DEFAULT 0x0

/* rx rxअणुbपूर्ण_lo_thresh[d:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rx{b}_lo_thresh[d:0]".
 * parameter: buffer अणुbपूर्ण | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx0_lo_thresh_i[13:0]"
 */

/* रेजिस्टर address क्रम bitfield rxअणुbपूर्ण_lo_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBLO_THRESH_ADR(buffer) (0x00005714 + (buffer) * 0x10)
/* biपंचांगask क्रम bitfield rxअणुbपूर्ण_lo_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBLO_THRESH_MSK 0x00003fff
/* inverted biपंचांगask क्रम bitfield rxअणुbपूर्ण_lo_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBLO_THRESH_MSKN 0xffffc000
/* lower bit position of bitfield rxअणुbपूर्ण_lo_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBLO_THRESH_SHIFT 0
/* width of bitfield rxअणुbपूर्ण_lo_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBLO_THRESH_WIDTH 14
/* शेष value of bitfield rxअणुbपूर्ण_lo_thresh[d:0] */
#घोषणा HW_ATL_RPB_RXBLO_THRESH_DEFAULT 0x0

/* rx rx_fc_mode[1:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rx_fc_mode[1:0]".
 * port="pif_rpb_rx_fc_mode_i[1:0]"
 */

/* रेजिस्टर address क्रम bitfield rx_fc_mode[1:0] */
#घोषणा HW_ATL_RPB_RX_FC_MODE_ADR 0x00005700
/* biपंचांगask क्रम bitfield rx_fc_mode[1:0] */
#घोषणा HW_ATL_RPB_RX_FC_MODE_MSK 0x00000030
/* inverted biपंचांगask क्रम bitfield rx_fc_mode[1:0] */
#घोषणा HW_ATL_RPB_RX_FC_MODE_MSKN 0xffffffcf
/* lower bit position of bitfield rx_fc_mode[1:0] */
#घोषणा HW_ATL_RPB_RX_FC_MODE_SHIFT 4
/* width of bitfield rx_fc_mode[1:0] */
#घोषणा HW_ATL_RPB_RX_FC_MODE_WIDTH 2
/* शेष value of bitfield rx_fc_mode[1:0] */
#घोषणा HW_ATL_RPB_RX_FC_MODE_DEFAULT 0x0

/* rx rxअणुbपूर्ण_buf_size[8:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rx{b}_buf_size[8:0]".
 * parameter: buffer अणुbपूर्ण | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx0_buf_size_i[8:0]"
 */

/* रेजिस्टर address क्रम bitfield rxअणुbपूर्ण_buf_size[8:0] */
#घोषणा HW_ATL_RPB_RXBBUF_SIZE_ADR(buffer) (0x00005710 + (buffer) * 0x10)
/* biपंचांगask क्रम bitfield rxअणुbपूर्ण_buf_size[8:0] */
#घोषणा HW_ATL_RPB_RXBBUF_SIZE_MSK 0x000001ff
/* inverted biपंचांगask क्रम bitfield rxअणुbपूर्ण_buf_size[8:0] */
#घोषणा HW_ATL_RPB_RXBBUF_SIZE_MSKN 0xfffffe00
/* lower bit position of bitfield rxअणुbपूर्ण_buf_size[8:0] */
#घोषणा HW_ATL_RPB_RXBBUF_SIZE_SHIFT 0
/* width of bitfield rxअणुbपूर्ण_buf_size[8:0] */
#घोषणा HW_ATL_RPB_RXBBUF_SIZE_WIDTH 9
/* शेष value of bitfield rxअणुbपूर्ण_buf_size[8:0] */
#घोषणा HW_ATL_RPB_RXBBUF_SIZE_DEFAULT 0x0

/* rx rxअणुbपूर्ण_xoff_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "rx{b}_xoff_en".
 * parameter: buffer अणुbपूर्ण | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx_xoff_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield rxअणुbपूर्ण_xoff_en */
#घोषणा HW_ATL_RPB_RXBXOFF_EN_ADR(buffer) (0x00005714 + (buffer) * 0x10)
/* biपंचांगask क्रम bitfield rxअणुbपूर्ण_xoff_en */
#घोषणा HW_ATL_RPB_RXBXOFF_EN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield rxअणुbपूर्ण_xoff_en */
#घोषणा HW_ATL_RPB_RXBXOFF_EN_MSKN 0x7fffffff
/* lower bit position of bitfield rxअणुbपूर्ण_xoff_en */
#घोषणा HW_ATL_RPB_RXBXOFF_EN_SHIFT 31
/* width of bitfield rxअणुbपूर्ण_xoff_en */
#घोषणा HW_ATL_RPB_RXBXOFF_EN_WIDTH 1
/* शेष value of bitfield rxअणुbपूर्ण_xoff_en */
#घोषणा HW_ATL_RPB_RXBXOFF_EN_DEFAULT 0x0

/* rx l2_bc_thresh[f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_bc_thresh[f:0]".
 * port="pif_rpf_l2_bc_thresh_i[15:0]"
 */

/* रेजिस्टर address क्रम bitfield l2_bc_thresh[f:0] */
#घोषणा HW_ATL_RPFL2BC_THRESH_ADR 0x00005100
/* biपंचांगask क्रम bitfield l2_bc_thresh[f:0] */
#घोषणा HW_ATL_RPFL2BC_THRESH_MSK 0xffff0000
/* inverted biपंचांगask क्रम bitfield l2_bc_thresh[f:0] */
#घोषणा HW_ATL_RPFL2BC_THRESH_MSKN 0x0000ffff
/* lower bit position of bitfield l2_bc_thresh[f:0] */
#घोषणा HW_ATL_RPFL2BC_THRESH_SHIFT 16
/* width of bitfield l2_bc_thresh[f:0] */
#घोषणा HW_ATL_RPFL2BC_THRESH_WIDTH 16
/* शेष value of bitfield l2_bc_thresh[f:0] */
#घोषणा HW_ATL_RPFL2BC_THRESH_DEFAULT 0x0

/* rx l2_bc_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_bc_en".
 * port="pif_rpf_l2_bc_en_i"
 */

/* रेजिस्टर address क्रम bitfield l2_bc_en */
#घोषणा HW_ATL_RPFL2BC_EN_ADR 0x00005100
/* biपंचांगask क्रम bitfield l2_bc_en */
#घोषणा HW_ATL_RPFL2BC_EN_MSK 0x00000001
/* inverted biपंचांगask क्रम bitfield l2_bc_en */
#घोषणा HW_ATL_RPFL2BC_EN_MSKN 0xfffffffe
/* lower bit position of bitfield l2_bc_en */
#घोषणा HW_ATL_RPFL2BC_EN_SHIFT 0
/* width of bitfield l2_bc_en */
#घोषणा HW_ATL_RPFL2BC_EN_WIDTH 1
/* शेष value of bitfield l2_bc_en */
#घोषणा HW_ATL_RPFL2BC_EN_DEFAULT 0x0

/* rx l2_bc_act[2:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_bc_act[2:0]".
 * port="pif_rpf_l2_bc_act_i[2:0]"
 */

/* रेजिस्टर address क्रम bitfield l2_bc_act[2:0] */
#घोषणा HW_ATL_RPFL2BC_ACT_ADR 0x00005100
/* biपंचांगask क्रम bitfield l2_bc_act[2:0] */
#घोषणा HW_ATL_RPFL2BC_ACT_MSK 0x00007000
/* inverted biपंचांगask क्रम bitfield l2_bc_act[2:0] */
#घोषणा HW_ATL_RPFL2BC_ACT_MSKN 0xffff8fff
/* lower bit position of bitfield l2_bc_act[2:0] */
#घोषणा HW_ATL_RPFL2BC_ACT_SHIFT 12
/* width of bitfield l2_bc_act[2:0] */
#घोषणा HW_ATL_RPFL2BC_ACT_WIDTH 3
/* शेष value of bitfield l2_bc_act[2:0] */
#घोषणा HW_ATL_RPFL2BC_ACT_DEFAULT 0x0

/* rx l2_mc_enअणुfपूर्ण bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_mc_en{f}".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 7]
 * port="pif_rpf_l2_mc_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield l2_mc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2MC_ENF_ADR(filter) (0x00005250 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield l2_mc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2MC_ENF_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield l2_mc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2MC_ENF_MSKN 0x7fffffff
/* lower bit position of bitfield l2_mc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2MC_ENF_SHIFT 31
/* width of bitfield l2_mc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2MC_ENF_WIDTH 1
/* शेष value of bitfield l2_mc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2MC_ENF_DEFAULT 0x0

/* rx l2_promis_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_promis_mode".
 * port="pif_rpf_l2_promis_mode_i"
 */

/* रेजिस्टर address क्रम bitfield l2_promis_mode */
#घोषणा HW_ATL_RPFL2PROMIS_MODE_ADR 0x00005100
/* biपंचांगask क्रम bitfield l2_promis_mode */
#घोषणा HW_ATL_RPFL2PROMIS_MODE_MSK 0x00000008
/* inverted biपंचांगask क्रम bitfield l2_promis_mode */
#घोषणा HW_ATL_RPFL2PROMIS_MODE_MSKN 0xfffffff7
/* lower bit position of bitfield l2_promis_mode */
#घोषणा HW_ATL_RPFL2PROMIS_MODE_SHIFT 3
/* width of bitfield l2_promis_mode */
#घोषणा HW_ATL_RPFL2PROMIS_MODE_WIDTH 1
/* शेष value of bitfield l2_promis_mode */
#घोषणा HW_ATL_RPFL2PROMIS_MODE_DEFAULT 0x0

/* rx l2_uc_actअणुfपूर्ण[2:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_uc_act{f}[2:0]".
 * parameter: filter अणुfपूर्ण | stride size 0x8 | range [0, 37]
 * port="pif_rpf_l2_uc_act0_i[2:0]"
 */

/* रेजिस्टर address क्रम bitfield l2_uc_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPFL2UC_ACTF_ADR(filter) (0x00005114 + (filter) * 0x8)
/* biपंचांगask क्रम bitfield l2_uc_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPFL2UC_ACTF_MSK 0x00070000
/* inverted biपंचांगask क्रम bitfield l2_uc_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPFL2UC_ACTF_MSKN 0xfff8ffff
/* lower bit position of bitfield l2_uc_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPFL2UC_ACTF_SHIFT 16
/* width of bitfield l2_uc_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPFL2UC_ACTF_WIDTH 3
/* शेष value of bitfield l2_uc_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPFL2UC_ACTF_DEFAULT 0x0

/* rx l2_uc_enअणुfपूर्ण bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_uc_en{f}".
 * parameter: filter अणुfपूर्ण | stride size 0x8 | range [0, 37]
 * port="pif_rpf_l2_uc_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield l2_uc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2UC_ENF_ADR(filter) (0x00005114 + (filter) * 0x8)
/* biपंचांगask क्रम bitfield l2_uc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2UC_ENF_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield l2_uc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2UC_ENF_MSKN 0x7fffffff
/* lower bit position of bitfield l2_uc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2UC_ENF_SHIFT 31
/* width of bitfield l2_uc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2UC_ENF_WIDTH 1
/* शेष value of bitfield l2_uc_enअणुfपूर्ण */
#घोषणा HW_ATL_RPFL2UC_ENF_DEFAULT 0x0

/* रेजिस्टर address क्रम bitfield l2_uc_daअणुfपूर्ण_lsw[1f:0] */
#घोषणा HW_ATL_RPFL2UC_DAFLSW_ADR(filter) (0x00005110 + (filter) * 0x8)
/* रेजिस्टर address क्रम bitfield l2_uc_daअणुfपूर्ण_msw[f:0] */
#घोषणा HW_ATL_RPFL2UC_DAFMSW_ADR(filter) (0x00005114 + (filter) * 0x8)
/* biपंचांगask क्रम bitfield l2_uc_daअणुfपूर्ण_msw[f:0] */
#घोषणा HW_ATL_RPFL2UC_DAFMSW_MSK 0x0000ffff
/* lower bit position of bitfield l2_uc_daअणुfपूर्ण_msw[f:0] */
#घोषणा HW_ATL_RPFL2UC_DAFMSW_SHIFT 0

/* rx l2_mc_accept_all bitfield definitions
 * Preprocessor definitions क्रम the bitfield "l2_mc_accept_all".
 * PORT="pif_rpf_l2_mc_all_accept_i"
 */

/* Register address क्रम bitfield l2_mc_accept_all */
#घोषणा HW_ATL_RPFL2MC_ACCEPT_ALL_ADR 0x00005270
/* Biपंचांगask क्रम bitfield l2_mc_accept_all */
#घोषणा HW_ATL_RPFL2MC_ACCEPT_ALL_MSK 0x00004000
/* Inverted biपंचांगask क्रम bitfield l2_mc_accept_all */
#घोषणा HW_ATL_RPFL2MC_ACCEPT_ALL_MSKN 0xFFFFBFFF
/* Lower bit position of bitfield l2_mc_accept_all */
#घोषणा HW_ATL_RPFL2MC_ACCEPT_ALL_SHIFT 14
/* Width of bitfield l2_mc_accept_all */
#घोषणा HW_ATL_RPFL2MC_ACCEPT_ALL_WIDTH 1
/* Default value of bitfield l2_mc_accept_all */
#घोषणा HW_ATL_RPFL2MC_ACCEPT_ALL_DEFAULT 0x0

/* width of bitfield rx_tc_upअणुtपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_RPB_RX_TC_UPT_WIDTH 3
/* शेष value of bitfield rx_tc_upअणुtपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_RPB_RX_TC_UPT_DEFAULT 0x0

/* rx rss_key_addr[4:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rss_key_addr[4:0]".
 * port="pif_rpf_rss_key_addr_i[4:0]"
 */

/* रेजिस्टर address क्रम bitfield rss_key_addr[4:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_ADDR_ADR 0x000054d0
/* biपंचांगask क्रम bitfield rss_key_addr[4:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_ADDR_MSK 0x0000001f
/* inverted biपंचांगask क्रम bitfield rss_key_addr[4:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_ADDR_MSKN 0xffffffe0
/* lower bit position of bitfield rss_key_addr[4:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_ADDR_SHIFT 0
/* width of bitfield rss_key_addr[4:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_ADDR_WIDTH 5
/* शेष value of bitfield rss_key_addr[4:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_ADDR_DEFAULT 0x0

/* rx rss_key_wr_data[1f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rss_key_wr_data[1f:0]".
 * port="pif_rpf_rss_key_wr_data_i[31:0]"
 */

/* रेजिस्टर address क्रम bitfield rss_key_wr_data[1f:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_DATA_ADR 0x000054d4
/* biपंचांगask क्रम bitfield rss_key_wr_data[1f:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_DATA_MSK 0xffffffff
/* inverted biपंचांगask क्रम bitfield rss_key_wr_data[1f:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_DATA_MSKN 0x00000000
/* lower bit position of bitfield rss_key_wr_data[1f:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_DATA_SHIFT 0
/* width of bitfield rss_key_wr_data[1f:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_DATA_WIDTH 32
/* शेष value of bitfield rss_key_wr_data[1f:0] */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_DATA_DEFAULT 0x0

/* rx rss_key_wr_en_i bitfield definitions
 * preprocessor definitions क्रम the bitfield "rss_key_wr_en_i".
 * port="pif_rpf_rss_key_wr_en_i"
 */

/* रेजिस्टर address क्रम bitfield rss_key_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_ENI_ADR 0x000054d0
/* biपंचांगask क्रम bitfield rss_key_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_ENI_MSK 0x00000020
/* inverted biपंचांगask क्रम bitfield rss_key_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_ENI_MSKN 0xffffffdf
/* lower bit position of bitfield rss_key_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_ENI_SHIFT 5
/* width of bitfield rss_key_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_ENI_WIDTH 1
/* शेष value of bitfield rss_key_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_KEY_WR_ENI_DEFAULT 0x0

/* rx rss_redir_addr[3:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rss_redir_addr[3:0]".
 * port="pif_rpf_rss_redir_addr_i[3:0]"
 */

/* रेजिस्टर address क्रम bitfield rss_redir_addr[3:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_ADDR_ADR 0x000054e0
/* biपंचांगask क्रम bitfield rss_redir_addr[3:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_ADDR_MSK 0x0000000f
/* inverted biपंचांगask क्रम bitfield rss_redir_addr[3:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_ADDR_MSKN 0xfffffff0
/* lower bit position of bitfield rss_redir_addr[3:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_ADDR_SHIFT 0
/* width of bitfield rss_redir_addr[3:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_ADDR_WIDTH 4
/* शेष value of bitfield rss_redir_addr[3:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_ADDR_DEFAULT 0x0

/* rx rss_redir_wr_data[f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rss_redir_wr_data[f:0]".
 * port="pif_rpf_rss_redir_wr_data_i[15:0]"
 */

/* रेजिस्टर address क्रम bitfield rss_redir_wr_data[f:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_DATA_ADR 0x000054e4
/* biपंचांगask क्रम bitfield rss_redir_wr_data[f:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_DATA_MSK 0x0000ffff
/* inverted biपंचांगask क्रम bitfield rss_redir_wr_data[f:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_DATA_MSKN 0xffff0000
/* lower bit position of bitfield rss_redir_wr_data[f:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_DATA_SHIFT 0
/* width of bitfield rss_redir_wr_data[f:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_DATA_WIDTH 16
/* शेष value of bitfield rss_redir_wr_data[f:0] */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_DATA_DEFAULT 0x0

/* rx rss_redir_wr_en_i bitfield definitions
 * preprocessor definitions क्रम the bitfield "rss_redir_wr_en_i".
 * port="pif_rpf_rss_redir_wr_en_i"
 */

/* रेजिस्टर address क्रम bitfield rss_redir_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_ENI_ADR 0x000054e0
/* biपंचांगask क्रम bitfield rss_redir_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_ENI_MSK 0x00000010
/* inverted biपंचांगask क्रम bitfield rss_redir_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_ENI_MSKN 0xffffffef
/* lower bit position of bitfield rss_redir_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_ENI_SHIFT 4
/* width of bitfield rss_redir_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_ENI_WIDTH 1
/* शेष value of bitfield rss_redir_wr_en_i */
#घोषणा HW_ATL_RPF_RSS_REसूची_WR_ENI_DEFAULT 0x0

/* rx tpo_rpf_sys_loopback bitfield definitions
 * preprocessor definitions क्रम the bitfield "tpo_rpf_sys_loopback".
 * port="pif_rpf_tpo_pkt_sys_lbk_i"
 */

/* रेजिस्टर address क्रम bitfield tpo_rpf_sys_loopback */
#घोषणा HW_ATL_RPF_TPO_RPF_SYS_LBK_ADR 0x00005000
/* biपंचांगask क्रम bitfield tpo_rpf_sys_loopback */
#घोषणा HW_ATL_RPF_TPO_RPF_SYS_LBK_MSK 0x00000100
/* inverted biपंचांगask क्रम bitfield tpo_rpf_sys_loopback */
#घोषणा HW_ATL_RPF_TPO_RPF_SYS_LBK_MSKN 0xfffffeff
/* lower bit position of bitfield tpo_rpf_sys_loopback */
#घोषणा HW_ATL_RPF_TPO_RPF_SYS_LBK_SHIFT 8
/* width of bitfield tpo_rpf_sys_loopback */
#घोषणा HW_ATL_RPF_TPO_RPF_SYS_LBK_WIDTH 1
/* शेष value of bitfield tpo_rpf_sys_loopback */
#घोषणा HW_ATL_RPF_TPO_RPF_SYS_LBK_DEFAULT 0x0

/* rx vl_inner_tpid[f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "vl_inner_tpid[f:0]".
 * port="pif_rpf_vl_inner_tpid_i[15:0]"
 */

/* रेजिस्टर address क्रम bitfield vl_inner_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_INNER_TPID_ADR 0x00005284
/* biपंचांगask क्रम bitfield vl_inner_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_INNER_TPID_MSK 0x0000ffff
/* inverted biपंचांगask क्रम bitfield vl_inner_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_INNER_TPID_MSKN 0xffff0000
/* lower bit position of bitfield vl_inner_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_INNER_TPID_SHIFT 0
/* width of bitfield vl_inner_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_INNER_TPID_WIDTH 16
/* शेष value of bitfield vl_inner_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_INNER_TPID_DEFAULT 0x8100

/* rx vl_outer_tpid[f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "vl_outer_tpid[f:0]".
 * port="pif_rpf_vl_outer_tpid_i[15:0]"
 */

/* रेजिस्टर address क्रम bitfield vl_outer_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_OUTER_TPID_ADR 0x00005284
/* biपंचांगask क्रम bitfield vl_outer_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_OUTER_TPID_MSK 0xffff0000
/* inverted biपंचांगask क्रम bitfield vl_outer_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_OUTER_TPID_MSKN 0x0000ffff
/* lower bit position of bitfield vl_outer_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_OUTER_TPID_SHIFT 16
/* width of bitfield vl_outer_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_OUTER_TPID_WIDTH 16
/* शेष value of bitfield vl_outer_tpid[f:0] */
#घोषणा HW_ATL_RPF_VL_OUTER_TPID_DEFAULT 0x88a8

/* rx vl_promis_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "vl_promis_mode".
 * port="pif_rpf_vl_promis_mode_i"
 */

/* रेजिस्टर address क्रम bitfield vl_promis_mode */
#घोषणा HW_ATL_RPF_VL_PROMIS_MODE_ADR 0x00005280
/* biपंचांगask क्रम bitfield vl_promis_mode */
#घोषणा HW_ATL_RPF_VL_PROMIS_MODE_MSK 0x00000002
/* inverted biपंचांगask क्रम bitfield vl_promis_mode */
#घोषणा HW_ATL_RPF_VL_PROMIS_MODE_MSKN 0xfffffffd
/* lower bit position of bitfield vl_promis_mode */
#घोषणा HW_ATL_RPF_VL_PROMIS_MODE_SHIFT 1
/* width of bitfield vl_promis_mode */
#घोषणा HW_ATL_RPF_VL_PROMIS_MODE_WIDTH 1
/* शेष value of bitfield vl_promis_mode */
#घोषणा HW_ATL_RPF_VL_PROMIS_MODE_DEFAULT 0x0

/* RX vl_accept_untagged_mode Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "vl_accept_untagged_mode".
 * PORT="pif_rpf_vl_accept_untagged_i"
 */

/* Register address क्रम bitfield vl_accept_untagged_mode */
#घोषणा HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_ADR 0x00005280
/* Biपंचांगask क्रम bitfield vl_accept_untagged_mode */
#घोषणा HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_MSK 0x00000004
/* Inverted biपंचांगask क्रम bitfield vl_accept_untagged_mode */
#घोषणा HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_MSKN 0xFFFFFFFB
/* Lower bit position of bitfield vl_accept_untagged_mode */
#घोषणा HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_SHIFT 2
/* Width of bitfield vl_accept_untagged_mode */
#घोषणा HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_WIDTH 1
/* Default value of bitfield vl_accept_untagged_mode */
#घोषणा HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_DEFAULT 0x0

/* rX vl_untagged_act[2:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "vl_untagged_act[2:0]".
 * PORT="pif_rpf_vl_untagged_act_i[2:0]"
 */

/* Register address क्रम bitfield vl_untagged_act[2:0] */
#घोषणा HW_ATL_RPF_VL_UNTAGGED_ACT_ADR 0x00005280
/* Biपंचांगask क्रम bitfield vl_untagged_act[2:0] */
#घोषणा HW_ATL_RPF_VL_UNTAGGED_ACT_MSK 0x00000038
/* Inverted biपंचांगask क्रम bitfield vl_untagged_act[2:0] */
#घोषणा HW_ATL_RPF_VL_UNTAGGED_ACT_MSKN 0xFFFFFFC7
/* Lower bit position of bitfield vl_untagged_act[2:0] */
#घोषणा HW_ATL_RPF_VL_UNTAGGED_ACT_SHIFT 3
/* Width of bitfield vl_untagged_act[2:0] */
#घोषणा HW_ATL_RPF_VL_UNTAGGED_ACT_WIDTH 3
/* Default value of bitfield vl_untagged_act[2:0] */
#घोषणा HW_ATL_RPF_VL_UNTAGGED_ACT_DEFAULT 0x0

/* RX vl_enअणुFपूर्ण Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "vl_en{F}".
 * Parameter: filter अणुFपूर्ण | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_en_i[0]"
 */

/* Register address क्रम bitfield vl_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_EN_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Biपंचांगask क्रम bitfield vl_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_EN_F_MSK 0x80000000
/* Inverted biपंचांगask क्रम bitfield vl_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_EN_F_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield vl_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_EN_F_SHIFT 31
/* Width of bitfield vl_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_EN_F_WIDTH 1
/* Default value of bitfield vl_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_EN_F_DEFAULT 0x0

/* RX vl_actअणुFपूर्ण[2:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "vl_act{F}[2:0]".
 * Parameter: filter अणुFपूर्ण | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_act0_i[2:0]"
 */

/* Register address क्रम bitfield vl_actअणुFपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_VL_ACT_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Biपंचांगask क्रम bitfield vl_actअणुFपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_VL_ACT_F_MSK 0x00070000
/* Inverted biपंचांगask क्रम bitfield vl_actअणुFपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_VL_ACT_F_MSKN 0xFFF8FFFF
/* Lower bit position of bitfield vl_actअणुFपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_VL_ACT_F_SHIFT 16
/* Width of bitfield vl_actअणुFपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_VL_ACT_F_WIDTH 3
/* Default value of bitfield vl_actअणुFपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_VL_ACT_F_DEFAULT 0x0

/* RX vl_idअणुFपूर्ण[B:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "vl_id{F}[B:0]".
 * Parameter: filter अणुFपूर्ण | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_id0_i[11:0]"
 */

/* Register address क्रम bitfield vl_idअणुFपूर्ण[B:0] */
#घोषणा HW_ATL_RPF_VL_ID_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Biपंचांगask क्रम bitfield vl_idअणुFपूर्ण[B:0] */
#घोषणा HW_ATL_RPF_VL_ID_F_MSK 0x00000FFF
/* Inverted biपंचांगask क्रम bitfield vl_idअणुFपूर्ण[B:0] */
#घोषणा HW_ATL_RPF_VL_ID_F_MSKN 0xFFFFF000
/* Lower bit position of bitfield vl_idअणुFपूर्ण[B:0] */
#घोषणा HW_ATL_RPF_VL_ID_F_SHIFT 0
/* Width of bitfield vl_idअणुFपूर्ण[B:0] */
#घोषणा HW_ATL_RPF_VL_ID_F_WIDTH 12
/* Default value of bitfield vl_idअणुFपूर्ण[B:0] */
#घोषणा HW_ATL_RPF_VL_ID_F_DEFAULT 0x0

/* RX vl_rxq_enअणुFपूर्ण Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "vl_rxq{F}".
 * Parameter: filter अणुFपूर्ण | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_rxq_en_i"
 */

/* Register address क्रम bitfield vl_rxq_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_RXQ_EN_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Biपंचांगask क्रम bitfield vl_rxq_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_RXQ_EN_F_MSK 0x10000000
/* Inverted biपंचांगask क्रम bitfield vl_rxq_enअणुFपूर्ण[ */
#घोषणा HW_ATL_RPF_VL_RXQ_EN_F_MSKN 0xEFFFFFFF
/* Lower bit position of bitfield vl_rxq_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_RXQ_EN_F_SHIFT 28
/* Width of bitfield vl_rxq_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_RXQ_EN_F_WIDTH 1
/* Default value of bitfield vl_rxq_enअणुFपूर्ण */
#घोषणा HW_ATL_RPF_VL_RXQ_EN_F_DEFAULT 0x0

/* RX vl_rxqअणुFपूर्ण[4:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "vl_rxq{F}[4:0]".
 * Parameter: filter अणुFपूर्ण | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_rxq0_i[4:0]"
 */

/* Register address क्रम bitfield vl_rxqअणुFपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_VL_RXQ_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Biपंचांगask क्रम bitfield vl_rxqअणुFपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_VL_RXQ_F_MSK 0x01F00000
/* Inverted biपंचांगask क्रम bitfield vl_rxqअणुFपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_VL_RXQ_F_MSKN 0xFE0FFFFF
/* Lower bit position of bitfield vl_rxqअणुFपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_VL_RXQ_F_SHIFT 20
/* Width of bitfield vl_rxwअणुFपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_VL_RXQ_F_WIDTH 5
/* Default value of bitfield vl_rxqअणुFपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_VL_RXQ_F_DEFAULT 0x0

/* rx et_enअणुfपूर्ण bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_en{f}".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield et_enअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_ENF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_enअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_ENF_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield et_enअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_ENF_MSKN 0x7fffffff
/* lower bit position of bitfield et_enअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_ENF_SHIFT 31
/* width of bitfield et_enअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_ENF_WIDTH 1
/* शेष value of bitfield et_enअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_ENF_DEFAULT 0x0

/* rx et_upअणुfपूर्ण_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_up{f}_en".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_up_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield et_upअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_UPFEN_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_upअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_UPFEN_MSK 0x40000000
/* inverted biपंचांगask क्रम bitfield et_upअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_UPFEN_MSKN 0xbfffffff
/* lower bit position of bitfield et_upअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_UPFEN_SHIFT 30
/* width of bitfield et_upअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_UPFEN_WIDTH 1
/* शेष value of bitfield et_upअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_UPFEN_DEFAULT 0x0

/* rx et_rxqअणुfपूर्ण_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_rxq{f}_en".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_rxq_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield et_rxqअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_RXQFEN_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_rxqअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_RXQFEN_MSK 0x20000000
/* inverted biपंचांगask क्रम bitfield et_rxqअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_RXQFEN_MSKN 0xdfffffff
/* lower bit position of bitfield et_rxqअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_RXQFEN_SHIFT 29
/* width of bitfield et_rxqअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_RXQFEN_WIDTH 1
/* शेष value of bitfield et_rxqअणुfपूर्ण_en */
#घोषणा HW_ATL_RPF_ET_RXQFEN_DEFAULT 0x0

/* rx et_upअणुfपूर्ण[2:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_up{f}[2:0]".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_up0_i[2:0]"
 */

/* रेजिस्टर address क्रम bitfield et_upअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_UPF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_upअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_UPF_MSK 0x1c000000
/* inverted biपंचांगask क्रम bitfield et_upअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_UPF_MSKN 0xe3ffffff
/* lower bit position of bitfield et_upअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_UPF_SHIFT 26
/* width of bitfield et_upअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_UPF_WIDTH 3
/* शेष value of bitfield et_upअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_UPF_DEFAULT 0x0

/* rx et_rxqअणुfपूर्ण[4:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_rxq{f}[4:0]".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_rxq0_i[4:0]"
 */

/* रेजिस्टर address क्रम bitfield et_rxqअणुfपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_ET_RXQF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_rxqअणुfपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_ET_RXQF_MSK 0x01f00000
/* inverted biपंचांगask क्रम bitfield et_rxqअणुfपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_ET_RXQF_MSKN 0xfe0fffff
/* lower bit position of bitfield et_rxqअणुfपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_ET_RXQF_SHIFT 20
/* width of bitfield et_rxqअणुfपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_ET_RXQF_WIDTH 5
/* शेष value of bitfield et_rxqअणुfपूर्ण[4:0] */
#घोषणा HW_ATL_RPF_ET_RXQF_DEFAULT 0x0

/* rx et_mng_rxqअणुfपूर्ण bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_mng_rxq{f}".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_mng_rxq_i[0]"
 */

/* रेजिस्टर address क्रम bitfield et_mng_rxqअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_MNG_RXQF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_mng_rxqअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_MNG_RXQF_MSK 0x00080000
/* inverted biपंचांगask क्रम bitfield et_mng_rxqअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_MNG_RXQF_MSKN 0xfff7ffff
/* lower bit position of bitfield et_mng_rxqअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_MNG_RXQF_SHIFT 19
/* width of bitfield et_mng_rxqअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_MNG_RXQF_WIDTH 1
/* शेष value of bitfield et_mng_rxqअणुfपूर्ण */
#घोषणा HW_ATL_RPF_ET_MNG_RXQF_DEFAULT 0x0

/* rx et_actअणुfपूर्ण[2:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_act{f}[2:0]".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_act0_i[2:0]"
 */

/* रेजिस्टर address क्रम bitfield et_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_ACTF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_ACTF_MSK 0x00070000
/* inverted biपंचांगask क्रम bitfield et_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_ACTF_MSKN 0xfff8ffff
/* lower bit position of bitfield et_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_ACTF_SHIFT 16
/* width of bitfield et_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_ACTF_WIDTH 3
/* शेष value of bitfield et_actअणुfपूर्ण[2:0] */
#घोषणा HW_ATL_RPF_ET_ACTF_DEFAULT 0x0

/* rx et_valअणुfपूर्ण[f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "et_val{f}[f:0]".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_val0_i[15:0]"
 */

/* रेजिस्टर address क्रम bitfield et_valअणुfपूर्ण[f:0] */
#घोषणा HW_ATL_RPF_ET_VALF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield et_valअणुfपूर्ण[f:0] */
#घोषणा HW_ATL_RPF_ET_VALF_MSK 0x0000ffff
/* inverted biपंचांगask क्रम bitfield et_valअणुfपूर्ण[f:0] */
#घोषणा HW_ATL_RPF_ET_VALF_MSKN 0xffff0000
/* lower bit position of bitfield et_valअणुfपूर्ण[f:0] */
#घोषणा HW_ATL_RPF_ET_VALF_SHIFT 0
/* width of bitfield et_valअणुfपूर्ण[f:0] */
#घोषणा HW_ATL_RPF_ET_VALF_WIDTH 16
/* शेष value of bitfield et_valअणुfपूर्ण[f:0] */
#घोषणा HW_ATL_RPF_ET_VALF_DEFAULT 0x0

/* RX l3_l4_enअणुFपूर्ण Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "l3_l4_en{F}".
 * Parameter: filter अणुFपूर्ण | stride size 0x4 | range [0, 7]
 * PORT="pif_rpf_l3_l4_en_i[0]"
 */

#घोषणा HW_ATL_RPF_L3_REG_CTRL_ADR(filter) (0x00005380 + (filter) * 0x4)

/* RX rpf_l3_saअणुDपूर्ण[1F:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "l3_sa{D}[1F:0]".
 * Parameter: location अणुDपूर्ण | stride size 0x4 | range [0, 7]
 * PORT="pif_rpf_l3_sa0_i[31:0]"
 */

/* Register address क्रम bitfield pअगर_rpf_l3_sa0_i[31:0] */
#घोषणा HW_ATL_RPF_L3_SRCA_ADR(filter) (0x000053B0 + (filter) * 0x4)
/* Biपंचांगask क्रम bitfield l3_sa0[1F:0] */
#घोषणा HW_ATL_RPF_L3_SRCA_MSK 0xFFFFFFFFu
/* Inverted biपंचांगask क्रम bitfield l3_sa0[1F:0] */
#घोषणा HW_ATL_RPF_L3_SRCA_MSKN 0xFFFFFFFFu
/* Lower bit position of bitfield l3_sa0[1F:0] */
#घोषणा HW_ATL_RPF_L3_SRCA_SHIFT 0
/* Width of bitfield l3_sa0[1F:0] */
#घोषणा HW_ATL_RPF_L3_SRCA_WIDTH 32
/* Default value of bitfield l3_sa0[1F:0] */
#घोषणा HW_ATL_RPF_L3_SRCA_DEFAULT 0x0

/* RX rpf_l3_daअणुDपूर्ण[1F:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "l3_da{D}[1F:0]".
 * Parameter: location अणुDपूर्ण | stride size 0x4 | range [0, 7]
 * PORT="pif_rpf_l3_da0_i[31:0]"
 */

 /* Register address क्रम bitfield pअगर_rpf_l3_da0_i[31:0] */
#घोषणा HW_ATL_RPF_L3_DSTA_ADR(filter) (0x000053D0 + (filter) * 0x4)
/* Biपंचांगask क्रम bitfield l3_da0[1F:0] */
#घोषणा HW_ATL_RPF_L3_DSTA_MSK 0xFFFFFFFFu
/* Inverted biपंचांगask क्रम bitfield l3_da0[1F:0] */
#घोषणा HW_ATL_RPF_L3_DSTA_MSKN 0xFFFFFFFFu
/* Lower bit position of bitfield l3_da0[1F:0] */
#घोषणा HW_ATL_RPF_L3_DSTA_SHIFT 0
/* Width of bitfield l3_da0[1F:0] */
#घोषणा HW_ATL_RPF_L3_DSTA_WIDTH 32
/* Default value of bitfield l3_da0[1F:0] */
#घोषणा HW_ATL_RPF_L3_DSTA_DEFAULT 0x0

/* RX l4_spअणुDपूर्ण[F:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "l4_sp{D}[F:0]".
 * Parameter: srcport अणुDपूर्ण | stride size 0x4 | range [0, 7]
 * PORT="pif_rpf_l4_sp0_i[15:0]"
 */

/* Register address क्रम bitfield l4_spअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_SPD_ADR(srcport) (0x00005400u + (srcport) * 0x4)
/* Biपंचांगask क्रम bitfield l4_spअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_SPD_MSK 0x0000FFFFu
/* Inverted biपंचांगask क्रम bitfield l4_spअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_SPD_MSKN 0xFFFF0000u
/* Lower bit position of bitfield l4_spअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_SPD_SHIFT 0
/* Width of bitfield l4_spअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_SPD_WIDTH 16
/* Default value of bitfield l4_spअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_SPD_DEFAULT 0x0

/* RX l4_dpअणुDपूर्ण[F:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "l4_dp{D}[F:0]".
 * Parameter: destport अणुDपूर्ण | stride size 0x4 | range [0, 7]
 * PORT="pif_rpf_l4_dp0_i[15:0]"
 */

/* Register address क्रम bitfield l4_dpअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_DPD_ADR(destport) (0x00005420u + (destport) * 0x4)
/* Biपंचांगask क्रम bitfield l4_dpअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_DPD_MSK 0x0000FFFFu
/* Inverted biपंचांगask क्रम bitfield l4_dpअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_DPD_MSKN 0xFFFF0000u
/* Lower bit position of bitfield l4_dpअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_DPD_SHIFT 0
/* Width of bitfield l4_dpअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_DPD_WIDTH 16
/* Default value of bitfield l4_dpअणुDपूर्ण[F:0] */
#घोषणा HW_ATL_RPF_L4_DPD_DEFAULT 0x0

/* rx ipv4_chk_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "ipv4_chk_en".
 * port="pif_rpo_ipv4_chk_en_i"
 */

/* रेजिस्टर address क्रम bitfield ipv4_chk_en */
#घोषणा HW_ATL_RPO_IPV4CHK_EN_ADR 0x00005580
/* biपंचांगask क्रम bitfield ipv4_chk_en */
#घोषणा HW_ATL_RPO_IPV4CHK_EN_MSK 0x00000002
/* inverted biपंचांगask क्रम bitfield ipv4_chk_en */
#घोषणा HW_ATL_RPO_IPV4CHK_EN_MSKN 0xfffffffd
/* lower bit position of bitfield ipv4_chk_en */
#घोषणा HW_ATL_RPO_IPV4CHK_EN_SHIFT 1
/* width of bitfield ipv4_chk_en */
#घोषणा HW_ATL_RPO_IPV4CHK_EN_WIDTH 1
/* शेष value of bitfield ipv4_chk_en */
#घोषणा HW_ATL_RPO_IPV4CHK_EN_DEFAULT 0x0

/* rx descअणुdपूर्ण_vl_strip bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_vl_strip".
 * parameter: descriptor अणुdपूर्ण | stride size 0x20 | range [0, 31]
 * port="pif_rpo_desc_vl_strip_i[0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_vl_strip */
#घोषणा HW_ATL_RPO_DESCDVL_STRIP_ADR(descriptor) \
	(0x00005b08 + (descriptor) * 0x20)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_vl_strip */
#घोषणा HW_ATL_RPO_DESCDVL_STRIP_MSK 0x20000000
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_vl_strip */
#घोषणा HW_ATL_RPO_DESCDVL_STRIP_MSKN 0xdfffffff
/* lower bit position of bitfield descअणुdपूर्ण_vl_strip */
#घोषणा HW_ATL_RPO_DESCDVL_STRIP_SHIFT 29
/* width of bitfield descअणुdपूर्ण_vl_strip */
#घोषणा HW_ATL_RPO_DESCDVL_STRIP_WIDTH 1
/* शेष value of bitfield descअणुdपूर्ण_vl_strip */
#घोषणा HW_ATL_RPO_DESCDVL_STRIP_DEFAULT 0x0

/* rx l4_chk_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "l4_chk_en".
 * port="pif_rpo_l4_chk_en_i"
 */

/* रेजिस्टर address क्रम bitfield l4_chk_en */
#घोषणा HW_ATL_RPOL4CHK_EN_ADR 0x00005580
/* biपंचांगask क्रम bitfield l4_chk_en */
#घोषणा HW_ATL_RPOL4CHK_EN_MSK 0x00000001
/* inverted biपंचांगask क्रम bitfield l4_chk_en */
#घोषणा HW_ATL_RPOL4CHK_EN_MSKN 0xfffffffe
/* lower bit position of bitfield l4_chk_en */
#घोषणा HW_ATL_RPOL4CHK_EN_SHIFT 0
/* width of bitfield l4_chk_en */
#घोषणा HW_ATL_RPOL4CHK_EN_WIDTH 1
/* शेष value of bitfield l4_chk_en */
#घोषणा HW_ATL_RPOL4CHK_EN_DEFAULT 0x0

/* RX outer_vl_ins_mode Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "outer_vl_ins_mode".
 * PORT="pif_rpo_outer_vl_mode_i"
 */

/* Register address क्रम bitfield outer_vl_ins_mode */
#घोषणा HW_ATL_RPO_OUTER_VL_INS_MODE_ADR 0x00005580
/* Biपंचांगask क्रम bitfield outer_vl_ins_mode */
#घोषणा HW_ATL_RPO_OUTER_VL_INS_MODE_MSK 0x00000004
/* Inverted biपंचांगask क्रम bitfield outer_vl_ins_mode */
#घोषणा HW_ATL_RPO_OUTER_VL_INS_MODE_MSKN 0xFFFFFFFB
/* Lower bit position of bitfield outer_vl_ins_mode */
#घोषणा HW_ATL_RPO_OUTER_VL_INS_MODE_SHIFT 2
/* Width of bitfield outer_vl_ins_mode */
#घोषणा HW_ATL_RPO_OUTER_VL_INS_MODE_WIDTH 1
/* Default value of bitfield outer_vl_ins_mode */
#घोषणा HW_ATL_RPO_OUTER_VL_INS_MODE_DEFAULT 0x0

/* rx reg_res_dsbl bitfield definitions
 * preprocessor definitions क्रम the bitfield "reg_res_dsbl".
 * port="pif_rx_reg_res_dsbl_i"
 */

/* रेजिस्टर address क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_RX_REG_RES_DSBL_ADR 0x00005000
/* biपंचांगask क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_RX_REG_RES_DSBL_MSK 0x20000000
/* inverted biपंचांगask क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_RX_REG_RES_DSBL_MSKN 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#घोषणा HW_ATL_RX_REG_RES_DSBL_SHIFT 29
/* width of bitfield reg_res_dsbl */
#घोषणा HW_ATL_RX_REG_RES_DSBL_WIDTH 1
/* शेष value of bitfield reg_res_dsbl */
#घोषणा HW_ATL_RX_REG_RES_DSBL_DEFAULT 0x1

/* tx dcaअणुdपूर्ण_cpuid[7:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca{d}_cpuid[7:0]".
 * parameter: dca अणुdपूर्ण | stride size 0x4 | range [0, 31]
 * port="pif_tdm_dca0_cpuid_i[7:0]"
 */

/* रेजिस्टर address क्रम bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCADCPUID_ADR(dca) (0x00008400 + (dca) * 0x4)
/* biपंचांगask क्रम bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCADCPUID_MSK 0x000000ff
/* inverted biपंचांगask क्रम bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCADCPUID_MSKN 0xffffff00
/* lower bit position of bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCADCPUID_SHIFT 0
/* width of bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCADCPUID_WIDTH 8
/* शेष value of bitfield dcaअणुdपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCADCPUID_DEFAULT 0x0

/* tx lso_en[1f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "lso_en[1f:0]".
 * port="pif_tdm_lso_en_i[31:0]"
 */

/* रेजिस्टर address क्रम bitfield lso_en[1f:0] */
#घोषणा HW_ATL_TDM_LSO_EN_ADR 0x00007810
/* biपंचांगask क्रम bitfield lso_en[1f:0] */
#घोषणा HW_ATL_TDM_LSO_EN_MSK 0xffffffff
/* inverted biपंचांगask क्रम bitfield lso_en[1f:0] */
#घोषणा HW_ATL_TDM_LSO_EN_MSKN 0x00000000
/* lower bit position of bitfield lso_en[1f:0] */
#घोषणा HW_ATL_TDM_LSO_EN_SHIFT 0
/* width of bitfield lso_en[1f:0] */
#घोषणा HW_ATL_TDM_LSO_EN_WIDTH 32
/* शेष value of bitfield lso_en[1f:0] */
#घोषणा HW_ATL_TDM_LSO_EN_DEFAULT 0x0

/* tx dca_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca_en".
 * port="pif_tdm_dca_en_i"
 */

/* रेजिस्टर address क्रम bitfield dca_en */
#घोषणा HW_ATL_TDM_DCA_EN_ADR 0x00008480
/* biपंचांगask क्रम bitfield dca_en */
#घोषणा HW_ATL_TDM_DCA_EN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield dca_en */
#घोषणा HW_ATL_TDM_DCA_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dca_en */
#घोषणा HW_ATL_TDM_DCA_EN_SHIFT 31
/* width of bitfield dca_en */
#घोषणा HW_ATL_TDM_DCA_EN_WIDTH 1
/* शेष value of bitfield dca_en */
#घोषणा HW_ATL_TDM_DCA_EN_DEFAULT 0x1

/* tx dca_mode[3:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca_mode[3:0]".
 * port="pif_tdm_dca_mode_i[3:0]"
 */

/* रेजिस्टर address क्रम bitfield dca_mode[3:0] */
#घोषणा HW_ATL_TDM_DCA_MODE_ADR 0x00008480
/* biपंचांगask क्रम bitfield dca_mode[3:0] */
#घोषणा HW_ATL_TDM_DCA_MODE_MSK 0x0000000f
/* inverted biपंचांगask क्रम bitfield dca_mode[3:0] */
#घोषणा HW_ATL_TDM_DCA_MODE_MSKN 0xfffffff0
/* lower bit position of bitfield dca_mode[3:0] */
#घोषणा HW_ATL_TDM_DCA_MODE_SHIFT 0
/* width of bitfield dca_mode[3:0] */
#घोषणा HW_ATL_TDM_DCA_MODE_WIDTH 4
/* शेष value of bitfield dca_mode[3:0] */
#घोषणा HW_ATL_TDM_DCA_MODE_DEFAULT 0x0

/* tx dcaअणुdपूर्ण_desc_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "dca{d}_desc_en".
 * parameter: dca अणुdपूर्ण | stride size 0x4 | range [0, 31]
 * port="pif_tdm_dca_desc_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCADDESC_EN_ADR(dca) (0x00008400 + (dca) * 0x4)
/* biपंचांगask क्रम bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCADDESC_EN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCADDESC_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCADDESC_EN_SHIFT 31
/* width of bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCADDESC_EN_WIDTH 1
/* शेष value of bitfield dcaअणुdपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCADDESC_EN_DEFAULT 0x0

/* tx descअणुdपूर्ण_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_en".
 * parameter: descriptor अणुdपूर्ण | stride size 0x40 | range [0, 31]
 * port="pif_tdm_desc_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_TDM_DESCDEN_ADR(descriptor) (0x00007c08 + (descriptor) * 0x40)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_TDM_DESCDEN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_TDM_DESCDEN_MSKN 0x7fffffff
/* lower bit position of bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_TDM_DESCDEN_SHIFT 31
/* width of bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_TDM_DESCDEN_WIDTH 1
/* शेष value of bitfield descअणुdपूर्ण_en */
#घोषणा HW_ATL_TDM_DESCDEN_DEFAULT 0x0

/* tx descअणुdपूर्ण_hd[c:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_hd[c:0]".
 * parameter: descriptor अणुdपूर्ण | stride size 0x40 | range [0, 31]
 * port="tdm_pif_desc0_hd_o[12:0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_TDM_DESCDHD_ADR(descriptor) (0x00007c0c + (descriptor) * 0x40)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_TDM_DESCDHD_MSK 0x00001fff
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_TDM_DESCDHD_MSKN 0xffffe000
/* lower bit position of bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_TDM_DESCDHD_SHIFT 0
/* width of bitfield descअणुdपूर्ण_hd[c:0] */
#घोषणा HW_ATL_TDM_DESCDHD_WIDTH 13

/* tx descअणुdपूर्ण_len[9:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_len[9:0]".
 * parameter: descriptor अणुdपूर्ण | stride size 0x40 | range [0, 31]
 * port="pif_tdm_desc0_len_i[9:0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESCDLEN_ADR(descriptor) (0x00007c08 + (descriptor) * 0x40)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESCDLEN_MSK 0x00001ff8
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESCDLEN_MSKN 0xffffe007
/* lower bit position of bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESCDLEN_SHIFT 3
/* width of bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESCDLEN_WIDTH 10
/* शेष value of bitfield descअणुdपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESCDLEN_DEFAULT 0x0

/* tx पूर्णांक_desc_wrb_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "int_desc_wrb_en".
 * port="pif_tdm_int_desc_wrb_en_i"
 */

/* रेजिस्टर address क्रम bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_TDM_INT_DESC_WRB_EN_ADR 0x00007b40
/* biपंचांगask क्रम bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_TDM_INT_DESC_WRB_EN_MSK 0x00000002
/* inverted biपंचांगask क्रम bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_TDM_INT_DESC_WRB_EN_MSKN 0xfffffffd
/* lower bit position of bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_TDM_INT_DESC_WRB_EN_SHIFT 1
/* width of bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_TDM_INT_DESC_WRB_EN_WIDTH 1
/* शेष value of bitfield पूर्णांक_desc_wrb_en */
#घोषणा HW_ATL_TDM_INT_DESC_WRB_EN_DEFAULT 0x0

/* tx descअणुdपूर्ण_wrb_thresh[6:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{d}_wrb_thresh[6:0]".
 * parameter: descriptor अणुdपूर्ण | stride size 0x40 | range [0, 31]
 * port="pif_tdm_desc0_wrb_thresh_i[6:0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुdपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESCDWRB_THRESH_ADR(descriptor) \
	(0x00007c18 + (descriptor) * 0x40)
/* biपंचांगask क्रम bitfield descअणुdपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESCDWRB_THRESH_MSK 0x00007f00
/* inverted biपंचांगask क्रम bitfield descअणुdपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESCDWRB_THRESH_MSKN 0xffff80ff
/* lower bit position of bitfield descअणुdपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESCDWRB_THRESH_SHIFT 8
/* width of bitfield descअणुdपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESCDWRB_THRESH_WIDTH 7
/* शेष value of bitfield descअणुdपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESCDWRB_THRESH_DEFAULT 0x0

/* tx lso_tcp_flag_first[b:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "lso_tcp_flag_first[b:0]".
 * port="pif_thm_lso_tcp_flag_first_i[11:0]"
 */

/* रेजिस्टर address क्रम bitfield lso_tcp_flag_first[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_FIRST_ADR 0x00007820
/* biपंचांगask क्रम bitfield lso_tcp_flag_first[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_FIRST_MSK 0x00000fff
/* inverted biपंचांगask क्रम bitfield lso_tcp_flag_first[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_FIRST_MSKN 0xfffff000
/* lower bit position of bitfield lso_tcp_flag_first[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_FIRST_SHIFT 0
/* width of bitfield lso_tcp_flag_first[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_FIRST_WIDTH 12
/* शेष value of bitfield lso_tcp_flag_first[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_FIRST_DEFAULT 0x0

/* tx lso_tcp_flag_last[b:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "lso_tcp_flag_last[b:0]".
 * port="pif_thm_lso_tcp_flag_last_i[11:0]"
 */

/* रेजिस्टर address क्रम bitfield lso_tcp_flag_last[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_LAST_ADR 0x00007824
/* biपंचांगask क्रम bitfield lso_tcp_flag_last[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_LAST_MSK 0x00000fff
/* inverted biपंचांगask क्रम bitfield lso_tcp_flag_last[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_LAST_MSKN 0xfffff000
/* lower bit position of bitfield lso_tcp_flag_last[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_LAST_SHIFT 0
/* width of bitfield lso_tcp_flag_last[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_LAST_WIDTH 12
/* शेष value of bitfield lso_tcp_flag_last[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_LAST_DEFAULT 0x0

/* tx lso_tcp_flag_mid[b:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "lso_tcp_flag_mid[b:0]".
 * port="pif_thm_lso_tcp_flag_mid_i[11:0]"
 */

/* Register address क्रम bitfield lro_rsc_max[1F:0] */
#घोषणा HW_ATL_RPO_LRO_RSC_MAX_ADR 0x00005598
/* Biपंचांगask क्रम bitfield lro_rsc_max[1F:0] */
#घोषणा HW_ATL_RPO_LRO_RSC_MAX_MSK 0xFFFFFFFF
/* Inverted biपंचांगask क्रम bitfield lro_rsc_max[1F:0] */
#घोषणा HW_ATL_RPO_LRO_RSC_MAX_MSKN 0x00000000
/* Lower bit position of bitfield lro_rsc_max[1F:0] */
#घोषणा HW_ATL_RPO_LRO_RSC_MAX_SHIFT 0
/* Width of bitfield lro_rsc_max[1F:0] */
#घोषणा HW_ATL_RPO_LRO_RSC_MAX_WIDTH 32
/* Default value of bitfield lro_rsc_max[1F:0] */
#घोषणा HW_ATL_RPO_LRO_RSC_MAX_DEFAULT 0x0

/* RX lro_en[1F:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lro_en[1F:0]".
 * PORT="pif_rpo_lro_en_i[31:0]"
 */

/* Register address क्रम bitfield lro_en[1F:0] */
#घोषणा HW_ATL_RPO_LRO_EN_ADR 0x00005590
/* Biपंचांगask क्रम bitfield lro_en[1F:0] */
#घोषणा HW_ATL_RPO_LRO_EN_MSK 0xFFFFFFFF
/* Inverted biपंचांगask क्रम bitfield lro_en[1F:0] */
#घोषणा HW_ATL_RPO_LRO_EN_MSKN 0x00000000
/* Lower bit position of bitfield lro_en[1F:0] */
#घोषणा HW_ATL_RPO_LRO_EN_SHIFT 0
/* Width of bitfield lro_en[1F:0] */
#घोषणा HW_ATL_RPO_LRO_EN_WIDTH 32
/* Default value of bitfield lro_en[1F:0] */
#घोषणा HW_ATL_RPO_LRO_EN_DEFAULT 0x0

/* RX lro_ptopt_en Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lro_ptopt_en".
 * PORT="pif_rpo_lro_ptopt_en_i"
 */

/* Register address क्रम bitfield lro_ptopt_en */
#घोषणा HW_ATL_RPO_LRO_PTOPT_EN_ADR 0x00005594
/* Biपंचांगask क्रम bitfield lro_ptopt_en */
#घोषणा HW_ATL_RPO_LRO_PTOPT_EN_MSK 0x00008000
/* Inverted biपंचांगask क्रम bitfield lro_ptopt_en */
#घोषणा HW_ATL_RPO_LRO_PTOPT_EN_MSKN 0xFFFF7FFF
/* Lower bit position of bitfield lro_ptopt_en */
#घोषणा HW_ATL_RPO_LRO_PTOPT_EN_SHIFT 15
/* Width of bitfield lro_ptopt_en */
#घोषणा HW_ATL_RPO_LRO_PTOPT_EN_WIDTH 1
/* Default value of bitfield lro_ptopt_en */
#घोषणा HW_ATL_RPO_LRO_PTOPT_EN_DEFALT 0x1

/* RX lro_q_ses_lmt Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lro_q_ses_lmt".
 * PORT="pif_rpo_lro_q_ses_lmt_i[1:0]"
 */

/* Register address क्रम bitfield lro_q_ses_lmt */
#घोषणा HW_ATL_RPO_LRO_QSES_LMT_ADR 0x00005594
/* Biपंचांगask क्रम bitfield lro_q_ses_lmt */
#घोषणा HW_ATL_RPO_LRO_QSES_LMT_MSK 0x00003000
/* Inverted biपंचांगask क्रम bitfield lro_q_ses_lmt */
#घोषणा HW_ATL_RPO_LRO_QSES_LMT_MSKN 0xFFFFCFFF
/* Lower bit position of bitfield lro_q_ses_lmt */
#घोषणा HW_ATL_RPO_LRO_QSES_LMT_SHIFT 12
/* Width of bitfield lro_q_ses_lmt */
#घोषणा HW_ATL_RPO_LRO_QSES_LMT_WIDTH 2
/* Default value of bitfield lro_q_ses_lmt */
#घोषणा HW_ATL_RPO_LRO_QSES_LMT_DEFAULT 0x1

/* RX lro_tot_dsc_lmt[1:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lro_tot_dsc_lmt[1:0]".
 * PORT="pif_rpo_lro_tot_dsc_lmt_i[1:0]"
 */

/* Register address क्रम bitfield lro_tot_dsc_lmt[1:0] */
#घोषणा HW_ATL_RPO_LRO_TOT_DSC_LMT_ADR 0x00005594
/* Biपंचांगask क्रम bitfield lro_tot_dsc_lmt[1:0] */
#घोषणा HW_ATL_RPO_LRO_TOT_DSC_LMT_MSK 0x00000060
/* Inverted biपंचांगask क्रम bitfield lro_tot_dsc_lmt[1:0] */
#घोषणा HW_ATL_RPO_LRO_TOT_DSC_LMT_MSKN 0xFFFFFF9F
/* Lower bit position of bitfield lro_tot_dsc_lmt[1:0] */
#घोषणा HW_ATL_RPO_LRO_TOT_DSC_LMT_SHIFT 5
/* Width of bitfield lro_tot_dsc_lmt[1:0] */
#घोषणा HW_ATL_RPO_LRO_TOT_DSC_LMT_WIDTH 2
/* Default value of bitfield lro_tot_dsc_lmt[1:0] */
#घोषणा HW_ATL_RPO_LRO_TOT_DSC_LMT_DEFALT 0x1

/* RX lro_pkt_min[4:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lro_pkt_min[4:0]".
 * PORT="pif_rpo_lro_pkt_min_i[4:0]"
 */

/* Register address क्रम bitfield lro_pkt_min[4:0] */
#घोषणा HW_ATL_RPO_LRO_PKT_MIN_ADR 0x00005594
/* Biपंचांगask क्रम bitfield lro_pkt_min[4:0] */
#घोषणा HW_ATL_RPO_LRO_PKT_MIN_MSK 0x0000001F
/* Inverted biपंचांगask क्रम bitfield lro_pkt_min[4:0] */
#घोषणा HW_ATL_RPO_LRO_PKT_MIN_MSKN 0xFFFFFFE0
/* Lower bit position of bitfield lro_pkt_min[4:0] */
#घोषणा HW_ATL_RPO_LRO_PKT_MIN_SHIFT 0
/* Width of bitfield lro_pkt_min[4:0] */
#घोषणा HW_ATL_RPO_LRO_PKT_MIN_WIDTH 5
/* Default value of bitfield lro_pkt_min[4:0] */
#घोषणा HW_ATL_RPO_LRO_PKT_MIN_DEFAULT 0x8

/* Width of bitfield lroअणुLपूर्ण_des_max[1:0] */
#घोषणा HW_ATL_RPO_LRO_LDES_MAX_WIDTH 2
/* Default value of bitfield lroअणुLपूर्ण_des_max[1:0] */
#घोषणा HW_ATL_RPO_LRO_LDES_MAX_DEFAULT 0x0

/* RX lro_tb_भाग[11:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lro_tb_div[11:0]".
 * PORT="pif_rpo_lro_tb_div_i[11:0]"
 */

/* Register address क्रम bitfield lro_tb_भाग[11:0] */
#घोषणा HW_ATL_RPO_LRO_TB_DIV_ADR 0x00005620
/* Biपंचांगask क्रम bitfield lro_tb_भाग[11:0] */
#घोषणा HW_ATL_RPO_LRO_TB_DIV_MSK 0xFFF00000
/* Inverted biपंचांगask क्रम bitfield lro_tb_भाग[11:0] */
#घोषणा HW_ATL_RPO_LRO_TB_DIV_MSKN 0x000FFFFF
/* Lower bit position of bitfield lro_tb_भाग[11:0] */
#घोषणा HW_ATL_RPO_LRO_TB_DIV_SHIFT 20
/* Width of bitfield lro_tb_भाग[11:0] */
#घोषणा HW_ATL_RPO_LRO_TB_DIV_WIDTH 12
/* Default value of bitfield lro_tb_भाग[11:0] */
#घोषणा HW_ATL_RPO_LRO_TB_DIV_DEFAULT 0xC35

/* RX lro_ina_ival[9:0] Bitfield Definitions
 *   Preprocessor definitions क्रम the bitfield "lro_ina_ival[9:0]".
 *   PORT="pif_rpo_lro_ina_ival_i[9:0]"
 */

/* Register address क्रम bitfield lro_ina_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_INA_IVAL_ADR 0x00005620
/* Biपंचांगask क्रम bitfield lro_ina_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_INA_IVAL_MSK 0x000FFC00
/* Inverted biपंचांगask क्रम bitfield lro_ina_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_INA_IVAL_MSKN 0xFFF003FF
/* Lower bit position of bitfield lro_ina_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_INA_IVAL_SHIFT 10
/* Width of bitfield lro_ina_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_INA_IVAL_WIDTH 10
/* Default value of bitfield lro_ina_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_INA_IVAL_DEFAULT 0xA

/* RX lro_max_ival[9:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lro_max_ival[9:0]".
 * PORT="pif_rpo_lro_max_ival_i[9:0]"
 */

/* Register address क्रम bitfield lro_max_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_MAX_IVAL_ADR 0x00005620
/* Biपंचांगask क्रम bitfield lro_max_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_MAX_IVAL_MSK 0x000003FF
/* Inverted biपंचांगask क्रम bitfield lro_max_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_MAX_IVAL_MSKN 0xFFFFFC00
/* Lower bit position of bitfield lro_max_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_MAX_IVAL_SHIFT 0
/* Width of bitfield lro_max_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_MAX_IVAL_WIDTH 10
/* Default value of bitfield lro_max_ival[9:0] */
#घोषणा HW_ATL_RPO_LRO_MAX_IVAL_DEFAULT 0x19

/* TX dcaअणुDपूर्ण_cpuid[7:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "dca{D}_cpuid[7:0]".
 * Parameter: DCA अणुDपूर्ण | stride size 0x4 | range [0, 31]
 * PORT="pif_tdm_dca0_cpuid_i[7:0]"
 */

/* Register address क्रम bitfield dcaअणुDपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCA_DCPUID_ADR(dca) (0x00008400 + (dca) * 0x4)
/* Biपंचांगask क्रम bitfield dcaअणुDपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCA_DCPUID_MSK 0x000000FF
/* Inverted biपंचांगask क्रम bitfield dcaअणुDपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCA_DCPUID_MSKN 0xFFFFFF00
/* Lower bit position of bitfield dcaअणुDपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCA_DCPUID_SHIFT 0
/* Width of bitfield dcaअणुDपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCA_DCPUID_WIDTH 8
/* Default value of bitfield dcaअणुDपूर्ण_cpuid[7:0] */
#घोषणा HW_ATL_TDM_DCA_DCPUID_DEFAULT 0x0

/* TX dcaअणुDपूर्ण_desc_en Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "dca{D}_desc_en".
 * Parameter: DCA अणुDपूर्ण | stride size 0x4 | range [0, 31]
 * PORT="pif_tdm_dca_desc_en_i[0]"
 */

/* Register address क्रम bitfield dcaअणुDपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCA_DDESC_EN_ADR(dca) (0x00008400 + (dca) * 0x4)
/* Biपंचांगask क्रम bitfield dcaअणुDपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCA_DDESC_EN_MSK 0x80000000
/* Inverted biपंचांगask क्रम bitfield dcaअणुDपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCA_DDESC_EN_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield dcaअणुDपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCA_DDESC_EN_SHIFT 31
/* Width of bitfield dcaअणुDपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCA_DDESC_EN_WIDTH 1
/* Default value of bitfield dcaअणुDपूर्ण_desc_en */
#घोषणा HW_ATL_TDM_DCA_DDESC_EN_DEFAULT 0x0

/* TX descअणुDपूर्ण_en Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "desc{D}_en".
 * Parameter: descriptor अणुDपूर्ण | stride size 0x40 | range [0, 31]
 * PORT="pif_tdm_desc_en_i[0]"
 */

/* Register address क्रम bitfield descअणुDपूर्ण_en */
#घोषणा HW_ATL_TDM_DESC_DEN_ADR(descriptor) (0x00007C08 + (descriptor) * 0x40)
/* Biपंचांगask क्रम bitfield descअणुDपूर्ण_en */
#घोषणा HW_ATL_TDM_DESC_DEN_MSK 0x80000000
/* Inverted biपंचांगask क्रम bitfield descअणुDपूर्ण_en */
#घोषणा HW_ATL_TDM_DESC_DEN_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield descअणुDपूर्ण_en */
#घोषणा HW_ATL_TDM_DESC_DEN_SHIFT 31
/* Width of bitfield descअणुDपूर्ण_en */
#घोषणा HW_ATL_TDM_DESC_DEN_WIDTH 1
/* Default value of bitfield descअणुDपूर्ण_en */
#घोषणा HW_ATL_TDM_DESC_DEN_DEFAULT 0x0

/* TX descअणुDपूर्ण_hd[C:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "desc{D}_hd[C:0]".
 * Parameter: descriptor अणुDपूर्ण | stride size 0x40 | range [0, 31]
 * PORT="tdm_pif_desc0_hd_o[12:0]"
 */

/* Register address क्रम bitfield descअणुDपूर्ण_hd[C:0] */
#घोषणा HW_ATL_TDM_DESC_DHD_ADR(descriptor) (0x00007C0C + (descriptor) * 0x40)
/* Biपंचांगask क्रम bitfield descअणुDपूर्ण_hd[C:0] */
#घोषणा HW_ATL_TDM_DESC_DHD_MSK 0x00001FFF
/* Inverted biपंचांगask क्रम bitfield descअणुDपूर्ण_hd[C:0] */
#घोषणा HW_ATL_TDM_DESC_DHD_MSKN 0xFFFFE000
/* Lower bit position of bitfield descअणुDपूर्ण_hd[C:0] */
#घोषणा HW_ATL_TDM_DESC_DHD_SHIFT 0
/* Width of bitfield descअणुDपूर्ण_hd[C:0] */
#घोषणा HW_ATL_TDM_DESC_DHD_WIDTH 13

/* TX descअणुDपूर्ण_len[9:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "desc{D}_len[9:0]".
 * Parameter: descriptor अणुDपूर्ण | stride size 0x40 | range [0, 31]
 * PORT="pif_tdm_desc0_len_i[9:0]"
 */

/* Register address क्रम bitfield descअणुDपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESC_DLEN_ADR(descriptor) (0x00007C08 + (descriptor) * 0x40)
/* Biपंचांगask क्रम bitfield descअणुDपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESC_DLEN_MSK 0x00001FF8
/* Inverted biपंचांगask क्रम bitfield descअणुDपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESC_DLEN_MSKN 0xFFFFE007
/* Lower bit position of bitfield descअणुDपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESC_DLEN_SHIFT 3
/* Width of bitfield descअणुDपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESC_DLEN_WIDTH 10
/* Default value of bitfield descअणुDपूर्ण_len[9:0] */
#घोषणा HW_ATL_TDM_DESC_DLEN_DEFAULT 0x0

/* TX descअणुDपूर्ण_wrb_thresh[6:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "desc{D}_wrb_thresh[6:0]".
 * Parameter: descriptor अणुDपूर्ण | stride size 0x40 | range [0, 31]
 * PORT="pif_tdm_desc0_wrb_thresh_i[6:0]"
 */

/* Register address क्रम bitfield descअणुDपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESC_DWRB_THRESH_ADR(descriptor) \
	(0x00007C18 + (descriptor) * 0x40)
/* Biपंचांगask क्रम bitfield descअणुDपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESC_DWRB_THRESH_MSK 0x00007F00
/* Inverted biपंचांगask क्रम bitfield descअणुDपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESC_DWRB_THRESH_MSKN 0xFFFF80FF
/* Lower bit position of bitfield descअणुDपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESC_DWRB_THRESH_SHIFT 8
/* Width of bitfield descअणुDपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESC_DWRB_THRESH_WIDTH 7
/* Default value of bitfield descअणुDपूर्ण_wrb_thresh[6:0] */
#घोषणा HW_ATL_TDM_DESC_DWRB_THRESH_DEFAULT 0x0

/* TX tdm_पूर्णांक_mod_en Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "tdm_int_mod_en".
 * PORT="pif_tdm_int_mod_en_i"
 */

/* Register address क्रम bitfield tdm_पूर्णांक_mod_en */
#घोषणा HW_ATL_TDM_INT_MOD_EN_ADR 0x00007B40
/* Biपंचांगask क्रम bitfield tdm_पूर्णांक_mod_en */
#घोषणा HW_ATL_TDM_INT_MOD_EN_MSK 0x00000010
/* Inverted biपंचांगask क्रम bitfield tdm_पूर्णांक_mod_en */
#घोषणा HW_ATL_TDM_INT_MOD_EN_MSKN 0xFFFFFFEF
/* Lower bit position of bitfield tdm_पूर्णांक_mod_en */
#घोषणा HW_ATL_TDM_INT_MOD_EN_SHIFT 4
/* Width of bitfield tdm_पूर्णांक_mod_en */
#घोषणा HW_ATL_TDM_INT_MOD_EN_WIDTH 1
/* Default value of bitfield tdm_पूर्णांक_mod_en */
#घोषणा HW_ATL_TDM_INT_MOD_EN_DEFAULT 0x0

/* TX lso_tcp_flag_mid[B:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "lso_tcp_flag_mid[B:0]".
 * PORT="pif_thm_lso_tcp_flag_mid_i[11:0]"
 */
/* रेजिस्टर address क्रम bitfield lso_tcp_flag_mid[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_MID_ADR 0x00007820
/* biपंचांगask क्रम bitfield lso_tcp_flag_mid[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_MID_MSK 0x0fff0000
/* inverted biपंचांगask क्रम bitfield lso_tcp_flag_mid[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_MID_MSKN 0xf000ffff
/* lower bit position of bitfield lso_tcp_flag_mid[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_MID_SHIFT 16
/* width of bitfield lso_tcp_flag_mid[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_MID_WIDTH 12
/* शेष value of bitfield lso_tcp_flag_mid[b:0] */
#घोषणा HW_ATL_THM_LSO_TCP_FLAG_MID_DEFAULT 0x0

/* tx tx_tc_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_tc_mode".
 * port="pif_tpb_tx_tc_mode_i,pif_tps_tx_tc_mode_i"
 */

/* रेजिस्टर address क्रम bitfield tx_tc_mode */
#घोषणा HW_ATL_TPB_TX_TC_MODE_ADDR 0x00007900
/* biपंचांगask क्रम bitfield tx_tc_mode */
#घोषणा HW_ATL_TPB_TX_TC_MODE_MSK 0x00000100
/* inverted biपंचांगask क्रम bitfield tx_tc_mode */
#घोषणा HW_ATL_TPB_TX_TC_MODE_MSKN 0xFFFFFEFF
/* lower bit position of bitfield tx_tc_mode */
#घोषणा HW_ATL_TPB_TX_TC_MODE_SHIFT 8
/* width of bitfield tx_tc_mode */
#घोषणा HW_ATL_TPB_TX_TC_MODE_WIDTH 1
/* शेष value of bitfield tx_tc_mode */
#घोषणा HW_ATL_TPB_TX_TC_MODE_DEFAULT 0x0

/* tx tx_desc_rate_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_desc_rate_mode".
 * port="pif_tps_desc_rate_mode_i"
 */

/* रेजिस्टर address क्रम bitfield tx_desc_rate_mode */
#घोषणा HW_ATL_TPS_TX_DESC_RATE_MODE_ADR 0x00007900
/* biपंचांगask क्रम bitfield tx_desc_rate_mode */
#घोषणा HW_ATL_TPS_TX_DESC_RATE_MODE_MSK 0x00000080
/* inverted biपंचांगask क्रम bitfield tx_desc_rate_mode */
#घोषणा HW_ATL_TPS_TX_DESC_RATE_MODE_MSKN 0xFFFFFF7F
/* lower bit position of bitfield tx_desc_rate_mode */
#घोषणा HW_ATL_TPS_TX_DESC_RATE_MODE_SHIFT 7
/* width of bitfield tx_desc_rate_mode */
#घोषणा HW_ATL_TPS_TX_DESC_RATE_MODE_WIDTH 1
/* शेष value of bitfield tx_desc_rate_mode */
#घोषणा HW_ATL_TPS_TX_DESC_RATE_MODE_DEFAULT 0x0

/* tx tx_buf_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_buf_en".
 * port="pif_tpb_tx_buf_en_i"
 */

/* रेजिस्टर address क्रम bitfield tx_buf_en */
#घोषणा HW_ATL_TPB_TX_BUF_EN_ADR 0x00007900
/* biपंचांगask क्रम bitfield tx_buf_en */
#घोषणा HW_ATL_TPB_TX_BUF_EN_MSK 0x00000001
/* inverted biपंचांगask क्रम bitfield tx_buf_en */
#घोषणा HW_ATL_TPB_TX_BUF_EN_MSKN 0xfffffffe
/* lower bit position of bitfield tx_buf_en */
#घोषणा HW_ATL_TPB_TX_BUF_EN_SHIFT 0
/* width of bitfield tx_buf_en */
#घोषणा HW_ATL_TPB_TX_BUF_EN_WIDTH 1
/* शेष value of bitfield tx_buf_en */
#घोषणा HW_ATL_TPB_TX_BUF_EN_DEFAULT 0x0

/* tx txअणुbपूर्ण_hi_thresh[c:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx{b}_hi_thresh[c:0]".
 * parameter: buffer अणुbपूर्ण | stride size 0x10 | range [0, 7]
 * port="pif_tpb_tx0_hi_thresh_i[12:0]"
 */

/* रेजिस्टर address क्रम bitfield txअणुbपूर्ण_hi_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBHI_THRESH_ADR(buffer) (0x00007914 + (buffer) * 0x10)
/* biपंचांगask क्रम bitfield txअणुbपूर्ण_hi_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBHI_THRESH_MSK 0x1fff0000
/* inverted biपंचांगask क्रम bitfield txअणुbपूर्ण_hi_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBHI_THRESH_MSKN 0xe000ffff
/* lower bit position of bitfield txअणुbपूर्ण_hi_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBHI_THRESH_SHIFT 16
/* width of bitfield txअणुbपूर्ण_hi_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBHI_THRESH_WIDTH 13
/* शेष value of bitfield txअणुbपूर्ण_hi_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBHI_THRESH_DEFAULT 0x0

/* tx txअणुbपूर्ण_lo_thresh[c:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx{b}_lo_thresh[c:0]".
 * parameter: buffer अणुbपूर्ण | stride size 0x10 | range [0, 7]
 * port="pif_tpb_tx0_lo_thresh_i[12:0]"
 */

/* रेजिस्टर address क्रम bitfield txअणुbपूर्ण_lo_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBLO_THRESH_ADR(buffer) (0x00007914 + (buffer) * 0x10)
/* biपंचांगask क्रम bitfield txअणुbपूर्ण_lo_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBLO_THRESH_MSK 0x00001fff
/* inverted biपंचांगask क्रम bitfield txअणुbपूर्ण_lo_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBLO_THRESH_MSKN 0xffffe000
/* lower bit position of bitfield txअणुbपूर्ण_lo_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBLO_THRESH_SHIFT 0
/* width of bitfield txअणुbपूर्ण_lo_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBLO_THRESH_WIDTH 13
/* शेष value of bitfield txअणुbपूर्ण_lo_thresh[c:0] */
#घोषणा HW_ATL_TPB_TXBLO_THRESH_DEFAULT 0x0

/* tx dma_sys_loopback bitfield definitions
 * preprocessor definitions क्रम the bitfield "dma_sys_loopback".
 * port="pif_tpb_dma_sys_lbk_i"
 */

/* रेजिस्टर address क्रम bitfield dma_sys_loopback */
#घोषणा HW_ATL_TPB_DMA_SYS_LBK_ADR 0x00007000
/* biपंचांगask क्रम bitfield dma_sys_loopback */
#घोषणा HW_ATL_TPB_DMA_SYS_LBK_MSK 0x00000040
/* inverted biपंचांगask क्रम bitfield dma_sys_loopback */
#घोषणा HW_ATL_TPB_DMA_SYS_LBK_MSKN 0xffffffbf
/* lower bit position of bitfield dma_sys_loopback */
#घोषणा HW_ATL_TPB_DMA_SYS_LBK_SHIFT 6
/* width of bitfield dma_sys_loopback */
#घोषणा HW_ATL_TPB_DMA_SYS_LBK_WIDTH 1
/* शेष value of bitfield dma_sys_loopback */
#घोषणा HW_ATL_TPB_DMA_SYS_LBK_DEFAULT 0x0

/* tx dma_net_loopback bitfield definitions
 * preprocessor definitions क्रम the bitfield "dma_net_loopback".
 * port="pif_tpb_dma_net_lbk_i"
 */

/* रेजिस्टर address क्रम bitfield dma_net_loopback */
#घोषणा HW_ATL_TPB_DMA_NET_LBK_ADR 0x00007000
/* biपंचांगask क्रम bitfield dma_net_loopback */
#घोषणा HW_ATL_TPB_DMA_NET_LBK_MSK 0x00000010
/* inverted biपंचांगask क्रम bitfield dma_net_loopback */
#घोषणा HW_ATL_TPB_DMA_NET_LBK_MSKN 0xffffffef
/* lower bit position of bitfield dma_net_loopback */
#घोषणा HW_ATL_TPB_DMA_NET_LBK_SHIFT 4
/* width of bitfield dma_net_loopback */
#घोषणा HW_ATL_TPB_DMA_NET_LBK_WIDTH 1
/* शेष value of bitfield dma_net_loopback */
#घोषणा HW_ATL_TPB_DMA_NET_LBK_DEFAULT 0x0

/* tx txअणुbपूर्ण_buf_size[7:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx{b}_buf_size[7:0]".
 * parameter: buffer अणुbपूर्ण | stride size 0x10 | range [0, 7]
 * port="pif_tpb_tx0_buf_size_i[7:0]"
 */

/* रेजिस्टर address क्रम bitfield txअणुbपूर्ण_buf_size[7:0] */
#घोषणा HW_ATL_TPB_TXBBUF_SIZE_ADR(buffer) (0x00007910 + (buffer) * 0x10)
/* biपंचांगask क्रम bitfield txअणुbपूर्ण_buf_size[7:0] */
#घोषणा HW_ATL_TPB_TXBBUF_SIZE_MSK 0x000000ff
/* inverted biपंचांगask क्रम bitfield txअणुbपूर्ण_buf_size[7:0] */
#घोषणा HW_ATL_TPB_TXBBUF_SIZE_MSKN 0xffffff00
/* lower bit position of bitfield txअणुbपूर्ण_buf_size[7:0] */
#घोषणा HW_ATL_TPB_TXBBUF_SIZE_SHIFT 0
/* width of bitfield txअणुbपूर्ण_buf_size[7:0] */
#घोषणा HW_ATL_TPB_TXBBUF_SIZE_WIDTH 8
/* शेष value of bitfield txअणुbपूर्ण_buf_size[7:0] */
#घोषणा HW_ATL_TPB_TXBBUF_SIZE_DEFAULT 0x0

/* tx tx_scp_ins_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_scp_ins_en".
 * port="pif_tpb_scp_ins_en_i"
 */

/* रेजिस्टर address क्रम bitfield tx_scp_ins_en */
#घोषणा HW_ATL_TPB_TX_SCP_INS_EN_ADR 0x00007900
/* biपंचांगask क्रम bitfield tx_scp_ins_en */
#घोषणा HW_ATL_TPB_TX_SCP_INS_EN_MSK 0x00000004
/* inverted biपंचांगask क्रम bitfield tx_scp_ins_en */
#घोषणा HW_ATL_TPB_TX_SCP_INS_EN_MSKN 0xfffffffb
/* lower bit position of bitfield tx_scp_ins_en */
#घोषणा HW_ATL_TPB_TX_SCP_INS_EN_SHIFT 2
/* width of bitfield tx_scp_ins_en */
#घोषणा HW_ATL_TPB_TX_SCP_INS_EN_WIDTH 1
/* शेष value of bitfield tx_scp_ins_en */
#घोषणा HW_ATL_TPB_TX_SCP_INS_EN_DEFAULT 0x0

/* tx tx_clk_gate_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_clk_gate_en".
 * port="pif_tpb_clk_gate_en_i"
 */

/* रेजिस्टर address क्रम bitfield tx_clk_gate_en */
#घोषणा HW_ATL_TPB_TX_CLK_GATE_EN_ADR 0x00007900
/* biपंचांगask क्रम bitfield tx_clk_gate_en */
#घोषणा HW_ATL_TPB_TX_CLK_GATE_EN_MSK 0x00000010
/* inverted biपंचांगask क्रम bitfield tx_clk_gate_en */
#घोषणा HW_ATL_TPB_TX_CLK_GATE_EN_MSKN 0xffffffef
/* lower bit position of bitfield tx_clk_gate_en */
#घोषणा HW_ATL_TPB_TX_CLK_GATE_EN_SHIFT 4
/* width of bitfield tx_clk_gate_en */
#घोषणा HW_ATL_TPB_TX_CLK_GATE_EN_WIDTH 1
/* शेष value of bitfield tx_clk_gate_en */
#घोषणा HW_ATL_TPB_TX_CLK_GATE_EN_DEFAULT 0x1

/* tx ipv4_chk_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "ipv4_chk_en".
 * port="pif_tpo_ipv4_chk_en_i"
 */

/* रेजिस्टर address क्रम bitfield ipv4_chk_en */
#घोषणा HW_ATL_TPO_IPV4CHK_EN_ADR 0x00007800
/* biपंचांगask क्रम bitfield ipv4_chk_en */
#घोषणा HW_ATL_TPO_IPV4CHK_EN_MSK 0x00000002
/* inverted biपंचांगask क्रम bitfield ipv4_chk_en */
#घोषणा HW_ATL_TPO_IPV4CHK_EN_MSKN 0xfffffffd
/* lower bit position of bitfield ipv4_chk_en */
#घोषणा HW_ATL_TPO_IPV4CHK_EN_SHIFT 1
/* width of bitfield ipv4_chk_en */
#घोषणा HW_ATL_TPO_IPV4CHK_EN_WIDTH 1
/* शेष value of bitfield ipv4_chk_en */
#घोषणा HW_ATL_TPO_IPV4CHK_EN_DEFAULT 0x0

/* tx l4_chk_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "l4_chk_en".
 * port="pif_tpo_l4_chk_en_i"
 */

/* रेजिस्टर address क्रम bitfield l4_chk_en */
#घोषणा HW_ATL_TPOL4CHK_EN_ADR 0x00007800
/* biपंचांगask क्रम bitfield l4_chk_en */
#घोषणा HW_ATL_TPOL4CHK_EN_MSK 0x00000001
/* inverted biपंचांगask क्रम bitfield l4_chk_en */
#घोषणा HW_ATL_TPOL4CHK_EN_MSKN 0xfffffffe
/* lower bit position of bitfield l4_chk_en */
#घोषणा HW_ATL_TPOL4CHK_EN_SHIFT 0
/* width of bitfield l4_chk_en */
#घोषणा HW_ATL_TPOL4CHK_EN_WIDTH 1
/* शेष value of bitfield l4_chk_en */
#घोषणा HW_ATL_TPOL4CHK_EN_DEFAULT 0x0

/* tx pkt_sys_loopback bitfield definitions
 * preprocessor definitions क्रम the bitfield "pkt_sys_loopback".
 * port="pif_tpo_pkt_sys_lbk_i"
 */

/* रेजिस्टर address क्रम bitfield pkt_sys_loopback */
#घोषणा HW_ATL_TPO_PKT_SYS_LBK_ADR 0x00007000
/* biपंचांगask क्रम bitfield pkt_sys_loopback */
#घोषणा HW_ATL_TPO_PKT_SYS_LBK_MSK 0x00000080
/* inverted biपंचांगask क्रम bitfield pkt_sys_loopback */
#घोषणा HW_ATL_TPO_PKT_SYS_LBK_MSKN 0xffffff7f
/* lower bit position of bitfield pkt_sys_loopback */
#घोषणा HW_ATL_TPO_PKT_SYS_LBK_SHIFT 7
/* width of bitfield pkt_sys_loopback */
#घोषणा HW_ATL_TPO_PKT_SYS_LBK_WIDTH 1
/* शेष value of bitfield pkt_sys_loopback */
#घोषणा HW_ATL_TPO_PKT_SYS_LBK_DEFAULT 0x0

/* tx data_tc_arb_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "data_tc_arb_mode".
 * port="pif_tps_data_tc_arb_mode_i"
 */

/* रेजिस्टर address क्रम bitfield data_tc_arb_mode */
#घोषणा HW_ATL_TPS_DATA_TC_ARB_MODE_ADR 0x00007100
/* biपंचांगask क्रम bitfield data_tc_arb_mode */
#घोषणा HW_ATL_TPS_DATA_TC_ARB_MODE_MSK 0x00000001
/* inverted biपंचांगask क्रम bitfield data_tc_arb_mode */
#घोषणा HW_ATL_TPS_DATA_TC_ARB_MODE_MSKN 0xfffffffe
/* lower bit position of bitfield data_tc_arb_mode */
#घोषणा HW_ATL_TPS_DATA_TC_ARB_MODE_SHIFT 0
/* width of bitfield data_tc_arb_mode */
#घोषणा HW_ATL_TPS_DATA_TC_ARB_MODE_WIDTH 1
/* शेष value of bitfield data_tc_arb_mode */
#घोषणा HW_ATL_TPS_DATA_TC_ARB_MODE_DEFAULT 0x0

/* tx descअणुrपूर्ण_rate_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{r}_rate_en".
 * port="pif_tps_desc_rate_en_i[0]"
 */

/* रेजिस्टर address क्रम bitfield descअणुrपूर्ण_rate_en */
#घोषणा HW_ATL_TPS_DESC_RATE_EN_ADR(desc) (0x00007408 + (desc) * 0x10)
/* biपंचांगask क्रम bitfield descअणुrपूर्ण_rate_en */
#घोषणा HW_ATL_TPS_DESC_RATE_EN_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield descअणुrपूर्ण_rate_en */
#घोषणा HW_ATL_TPS_DESC_RATE_EN_MSKN 0x7FFFFFFF
/* lower bit position of bitfield descअणुrपूर्ण_rate_en */
#घोषणा HW_ATL_TPS_DESC_RATE_EN_SHIFT 31
/* width of bitfield descअणुrपूर्ण_rate_en */
#घोषणा HW_ATL_TPS_DESC_RATE_EN_WIDTH 1
/* शेष value of bitfield descअणुrपूर्ण_rate_en */
#घोषणा HW_ATL_TPS_DESC_RATE_EN_DEFAULT 0x0

/* tx descअणुrपूर्ण_rate_x bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{r}_rate_x".
 * port="pif_tps_desc0_rate_x"
 */
/* रेजिस्टर address क्रम bitfield descअणुrपूर्ण_rate_x */
#घोषणा HW_ATL_TPS_DESC_RATE_X_ADR(desc) (0x00007408 + (desc) * 0x10)
/* biपंचांगask क्रम bitfield descअणुrपूर्ण_rate_x */
#घोषणा HW_ATL_TPS_DESC_RATE_X_MSK 0x03FF0000
/* inverted biपंचांगask क्रम bitfield descअणुrपूर्ण_rate_x */
#घोषणा HW_ATL_TPS_DESC_RATE_X_MSKN 0xFC00FFFF
/* lower bit position of bitfield descअणुrपूर्ण_rate_x */
#घोषणा HW_ATL_TPS_DESC_RATE_X_SHIFT 16
/* width of bitfield descअणुrपूर्ण_rate_x */
#घोषणा HW_ATL_TPS_DESC_RATE_X_WIDTH 10
/* शेष value of bitfield descअणुrपूर्ण_rate_x */
#घोषणा HW_ATL_TPS_DESC_RATE_X_DEFAULT 0x0

/* tx descअणुrपूर्ण_rate_y bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc{r}_rate_y".
 * port="pif_tps_desc0_rate_y"
 */
/* रेजिस्टर address क्रम bitfield descअणुrपूर्ण_rate_y */
#घोषणा HW_ATL_TPS_DESC_RATE_Y_ADR(desc) (0x00007408 + (desc) * 0x10)
/* biपंचांगask क्रम bitfield descअणुrपूर्ण_rate_y */
#घोषणा HW_ATL_TPS_DESC_RATE_Y_MSK 0x00003FFF
/* inverted biपंचांगask क्रम bitfield descअणुrपूर्ण_rate_y */
#घोषणा HW_ATL_TPS_DESC_RATE_Y_MSKN 0xFFFFC000
/* lower bit position of bitfield descअणुrपूर्ण_rate_y */
#घोषणा HW_ATL_TPS_DESC_RATE_Y_SHIFT 0
/* width of bitfield descअणुrपूर्ण_rate_y */
#घोषणा HW_ATL_TPS_DESC_RATE_Y_WIDTH 14
/* शेष value of bitfield descअणुrपूर्ण_rate_y */
#घोषणा HW_ATL_TPS_DESC_RATE_Y_DEFAULT 0x0

/* tx desc_rate_ta_rst bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc_rate_ta_rst".
 * port="pif_tps_desc_rate_ta_rst_i"
 */

/* रेजिस्टर address क्रम bitfield desc_rate_ta_rst */
#घोषणा HW_ATL_TPS_DESC_RATE_TA_RST_ADR 0x00007310
/* biपंचांगask क्रम bitfield desc_rate_ta_rst */
#घोषणा HW_ATL_TPS_DESC_RATE_TA_RST_MSK 0x80000000
/* inverted biपंचांगask क्रम bitfield desc_rate_ta_rst */
#घोषणा HW_ATL_TPS_DESC_RATE_TA_RST_MSKN 0x7fffffff
/* lower bit position of bitfield desc_rate_ta_rst */
#घोषणा HW_ATL_TPS_DESC_RATE_TA_RST_SHIFT 31
/* width of bitfield desc_rate_ta_rst */
#घोषणा HW_ATL_TPS_DESC_RATE_TA_RST_WIDTH 1
/* शेष value of bitfield desc_rate_ta_rst */
#घोषणा HW_ATL_TPS_DESC_RATE_TA_RST_DEFAULT 0x0

/* tx desc_rate_limit[a:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc_rate_limit[a:0]".
 * port="pif_tps_desc_rate_lim_i[10:0]"
 */

/* रेजिस्टर address क्रम bitfield desc_rate_limit[a:0] */
#घोषणा HW_ATL_TPS_DESC_RATE_LIM_ADR 0x00007310
/* biपंचांगask क्रम bitfield desc_rate_limit[a:0] */
#घोषणा HW_ATL_TPS_DESC_RATE_LIM_MSK 0x000007ff
/* inverted biपंचांगask क्रम bitfield desc_rate_limit[a:0] */
#घोषणा HW_ATL_TPS_DESC_RATE_LIM_MSKN 0xfffff800
/* lower bit position of bitfield desc_rate_limit[a:0] */
#घोषणा HW_ATL_TPS_DESC_RATE_LIM_SHIFT 0
/* width of bitfield desc_rate_limit[a:0] */
#घोषणा HW_ATL_TPS_DESC_RATE_LIM_WIDTH 11
/* शेष value of bitfield desc_rate_limit[a:0] */
#घोषणा HW_ATL_TPS_DESC_RATE_LIM_DEFAULT 0x0

/* tx desc_tc_arb_mode[1:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc_tc_arb_mode[1:0]".
 * port="pif_tps_desc_tc_arb_mode_i[1:0]"
 */

/* रेजिस्टर address क्रम bitfield desc_tc_arb_mode[1:0] */
#घोषणा HW_ATL_TPS_DESC_TC_ARB_MODE_ADR 0x00007200
/* biपंचांगask क्रम bitfield desc_tc_arb_mode[1:0] */
#घोषणा HW_ATL_TPS_DESC_TC_ARB_MODE_MSK 0x00000003
/* inverted biपंचांगask क्रम bitfield desc_tc_arb_mode[1:0] */
#घोषणा HW_ATL_TPS_DESC_TC_ARB_MODE_MSKN 0xfffffffc
/* lower bit position of bitfield desc_tc_arb_mode[1:0] */
#घोषणा HW_ATL_TPS_DESC_TC_ARB_MODE_SHIFT 0
/* width of bitfield desc_tc_arb_mode[1:0] */
#घोषणा HW_ATL_TPS_DESC_TC_ARB_MODE_WIDTH 2
/* शेष value of bitfield desc_tc_arb_mode[1:0] */
#घोषणा HW_ATL_TPS_DESC_TC_ARB_MODE_DEFAULT 0x0

/* tx desc_tcअणुtपूर्ण_credit_max[b:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc_tc{t}_credit_max[b:0]".
 * parameter: tc अणुtपूर्ण | stride size 0x4 | range [0, 7]
 * port="pif_tps_desc_tc0_credit_max_i[11:0]"
 */

/* रेजिस्टर address क्रम bitfield desc_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DESC_TCTCREDIT_MAX_ADR(tc) (0x00007210 + (tc) * 0x4)
/* biपंचांगask क्रम bitfield desc_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DESC_TCTCREDIT_MAX_MSK 0x0fff0000
/* inverted biपंचांगask क्रम bitfield desc_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DESC_TCTCREDIT_MAX_MSKN 0xf000ffff
/* lower bit position of bitfield desc_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DESC_TCTCREDIT_MAX_SHIFT 16
/* width of bitfield desc_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DESC_TCTCREDIT_MAX_WIDTH 12
/* शेष value of bitfield desc_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DESC_TCTCREDIT_MAX_DEFAULT 0x0

/* tx desc_tcअणुtपूर्ण_weight[8:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc_tc{t}_weight[8:0]".
 * parameter: tc अणुtपूर्ण | stride size 0x4 | range [0, 7]
 * port="pif_tps_desc_tc0_weight_i[8:0]"
 */

/* रेजिस्टर address क्रम bitfield desc_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DESC_TCTWEIGHT_ADR(tc) (0x00007210 + (tc) * 0x4)
/* biपंचांगask क्रम bitfield desc_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DESC_TCTWEIGHT_MSK 0x000001ff
/* inverted biपंचांगask क्रम bitfield desc_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DESC_TCTWEIGHT_MSKN 0xfffffe00
/* lower bit position of bitfield desc_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DESC_TCTWEIGHT_SHIFT 0
/* width of bitfield desc_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DESC_TCTWEIGHT_WIDTH 9
/* शेष value of bitfield desc_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DESC_TCTWEIGHT_DEFAULT 0x0

/* tx desc_vm_arb_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "desc_vm_arb_mode".
 * port="pif_tps_desc_vm_arb_mode_i"
 */

/* रेजिस्टर address क्रम bitfield desc_vm_arb_mode */
#घोषणा HW_ATL_TPS_DESC_VM_ARB_MODE_ADR 0x00007300
/* biपंचांगask क्रम bitfield desc_vm_arb_mode */
#घोषणा HW_ATL_TPS_DESC_VM_ARB_MODE_MSK 0x00000001
/* inverted biपंचांगask क्रम bitfield desc_vm_arb_mode */
#घोषणा HW_ATL_TPS_DESC_VM_ARB_MODE_MSKN 0xfffffffe
/* lower bit position of bitfield desc_vm_arb_mode */
#घोषणा HW_ATL_TPS_DESC_VM_ARB_MODE_SHIFT 0
/* width of bitfield desc_vm_arb_mode */
#घोषणा HW_ATL_TPS_DESC_VM_ARB_MODE_WIDTH 1
/* शेष value of bitfield desc_vm_arb_mode */
#घोषणा HW_ATL_TPS_DESC_VM_ARB_MODE_DEFAULT 0x0

/* tx data_tcअणुtपूर्ण_credit_max[b:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "data_tc{t}_credit_max[b:0]".
 * parameter: tc अणुtपूर्ण | stride size 0x4 | range [0, 7]
 * port="pif_tps_data_tc0_credit_max_i[11:0]"
 */

/* रेजिस्टर address क्रम bitfield data_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DATA_TCTCREDIT_MAX_ADR(tc) (0x00007110 + (tc) * 0x4)
/* biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DATA_TCTCREDIT_MAX_MSK 0x0fff0000
/* inverted biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DATA_TCTCREDIT_MAX_MSKN 0xf000ffff
/* lower bit position of bitfield data_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DATA_TCTCREDIT_MAX_SHIFT 16
/* width of bitfield data_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DATA_TCTCREDIT_MAX_WIDTH 12
/* शेष value of bitfield data_tcअणुtपूर्ण_credit_max[b:0] */
#घोषणा HW_ATL_TPS_DATA_TCTCREDIT_MAX_DEFAULT 0x0

/* tx data_tcअणुtपूर्ण_weight[8:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "data_tc{t}_weight[8:0]".
 * parameter: tc अणुtपूर्ण | stride size 0x4 | range [0, 7]
 * port="pif_tps_data_tc0_weight_i[8:0]"
 */

/* रेजिस्टर address क्रम bitfield data_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DATA_TCTWEIGHT_ADR(tc) (0x00007110 + (tc) * 0x4)
/* biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DATA_TCTWEIGHT_MSK 0x000001ff
/* inverted biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DATA_TCTWEIGHT_MSKN 0xfffffe00
/* lower bit position of bitfield data_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DATA_TCTWEIGHT_SHIFT 0
/* width of bitfield data_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DATA_TCTWEIGHT_WIDTH 9
/* शेष value of bitfield data_tcअणुtपूर्ण_weight[8:0] */
#घोषणा HW_ATL_TPS_DATA_TCTWEIGHT_DEFAULT 0x0

/* tx reg_res_dsbl bitfield definitions
 * preprocessor definitions क्रम the bitfield "reg_res_dsbl".
 * port="pif_tx_reg_res_dsbl_i"
 */

/* रेजिस्टर address क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_TX_REG_RES_DSBL_ADR 0x00007000
/* biपंचांगask क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_TX_REG_RES_DSBL_MSK 0x20000000
/* inverted biपंचांगask क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_TX_REG_RES_DSBL_MSKN 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#घोषणा HW_ATL_TX_REG_RES_DSBL_SHIFT 29
/* width of bitfield reg_res_dsbl */
#घोषणा HW_ATL_TX_REG_RES_DSBL_WIDTH 1
/* शेष value of bitfield reg_res_dsbl */
#घोषणा HW_ATL_TX_REG_RES_DSBL_DEFAULT 0x1

/* mac_phy रेजिस्टर access busy bitfield definitions
 * preprocessor definitions क्रम the bitfield "register access busy".
 * port="msm_pif_reg_busy_o"
 */

/* रेजिस्टर address क्रम bitfield रेजिस्टर access busy */
#घोषणा HW_ATL_MSM_REG_ACCESS_BUSY_ADR 0x00004400
/* biपंचांगask क्रम bitfield रेजिस्टर access busy */
#घोषणा HW_ATL_MSM_REG_ACCESS_BUSY_MSK 0x00001000
/* inverted biपंचांगask क्रम bitfield रेजिस्टर access busy */
#घोषणा HW_ATL_MSM_REG_ACCESS_BUSY_MSKN 0xffffefff
/* lower bit position of bitfield रेजिस्टर access busy */
#घोषणा HW_ATL_MSM_REG_ACCESS_BUSY_SHIFT 12
/* width of bitfield रेजिस्टर access busy */
#घोषणा HW_ATL_MSM_REG_ACCESS_BUSY_WIDTH 1

/* mac_phy msm रेजिस्टर address[7:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "msm register address[7:0]".
 * port="pif_msm_reg_addr_i[7:0]"
 */

/* रेजिस्टर address क्रम bitfield msm रेजिस्टर address[7:0] */
#घोषणा HW_ATL_MSM_REG_ADDR_ADR 0x00004400
/* biपंचांगask क्रम bitfield msm रेजिस्टर address[7:0] */
#घोषणा HW_ATL_MSM_REG_ADDR_MSK 0x000000ff
/* inverted biपंचांगask क्रम bitfield msm रेजिस्टर address[7:0] */
#घोषणा HW_ATL_MSM_REG_ADDR_MSKN 0xffffff00
/* lower bit position of bitfield msm रेजिस्टर address[7:0] */
#घोषणा HW_ATL_MSM_REG_ADDR_SHIFT 0
/* width of bitfield msm रेजिस्टर address[7:0] */
#घोषणा HW_ATL_MSM_REG_ADDR_WIDTH 8
/* शेष value of bitfield msm रेजिस्टर address[7:0] */
#घोषणा HW_ATL_MSM_REG_ADDR_DEFAULT 0x0

/* mac_phy रेजिस्टर पढ़ो strobe bitfield definitions
 * preprocessor definitions क्रम the bitfield "register read strobe".
 * port="pif_msm_reg_rden_i"
 */

/* रेजिस्टर address क्रम bitfield रेजिस्टर पढ़ो strobe */
#घोषणा HW_ATL_MSM_REG_RD_STROBE_ADR 0x00004400
/* biपंचांगask क्रम bitfield रेजिस्टर पढ़ो strobe */
#घोषणा HW_ATL_MSM_REG_RD_STROBE_MSK 0x00000200
/* inverted biपंचांगask क्रम bitfield रेजिस्टर पढ़ो strobe */
#घोषणा HW_ATL_MSM_REG_RD_STROBE_MSKN 0xfffffdff
/* lower bit position of bitfield रेजिस्टर पढ़ो strobe */
#घोषणा HW_ATL_MSM_REG_RD_STROBE_SHIFT 9
/* width of bitfield रेजिस्टर पढ़ो strobe */
#घोषणा HW_ATL_MSM_REG_RD_STROBE_WIDTH 1
/* शेष value of bitfield रेजिस्टर पढ़ो strobe */
#घोषणा HW_ATL_MSM_REG_RD_STROBE_DEFAULT 0x0

/* mac_phy msm रेजिस्टर पढ़ो data[31:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "msm register read data[31:0]".
 * port="msm_pif_reg_rd_data_o[31:0]"
 */

/* रेजिस्टर address क्रम bitfield msm रेजिस्टर पढ़ो data[31:0] */
#घोषणा HW_ATL_MSM_REG_RD_DATA_ADR 0x00004408
/* biपंचांगask क्रम bitfield msm रेजिस्टर पढ़ो data[31:0] */
#घोषणा HW_ATL_MSM_REG_RD_DATA_MSK 0xffffffff
/* inverted biपंचांगask क्रम bitfield msm रेजिस्टर पढ़ो data[31:0] */
#घोषणा HW_ATL_MSM_REG_RD_DATA_MSKN 0x00000000
/* lower bit position of bitfield msm रेजिस्टर पढ़ो data[31:0] */
#घोषणा HW_ATL_MSM_REG_RD_DATA_SHIFT 0
/* width of bitfield msm रेजिस्टर पढ़ो data[31:0] */
#घोषणा HW_ATL_MSM_REG_RD_DATA_WIDTH 32

/* mac_phy msm रेजिस्टर ग_लिखो data[31:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "msm register write data[31:0]".
 * port="pif_msm_reg_wr_data_i[31:0]"
 */

/* रेजिस्टर address क्रम bitfield msm रेजिस्टर ग_लिखो data[31:0] */
#घोषणा HW_ATL_MSM_REG_WR_DATA_ADR 0x00004404
/* biपंचांगask क्रम bitfield msm रेजिस्टर ग_लिखो data[31:0] */
#घोषणा HW_ATL_MSM_REG_WR_DATA_MSK 0xffffffff
/* inverted biपंचांगask क्रम bitfield msm रेजिस्टर ग_लिखो data[31:0] */
#घोषणा HW_ATL_MSM_REG_WR_DATA_MSKN 0x00000000
/* lower bit position of bitfield msm रेजिस्टर ग_लिखो data[31:0] */
#घोषणा HW_ATL_MSM_REG_WR_DATA_SHIFT 0
/* width of bitfield msm रेजिस्टर ग_लिखो data[31:0] */
#घोषणा HW_ATL_MSM_REG_WR_DATA_WIDTH 32
/* शेष value of bitfield msm रेजिस्टर ग_लिखो data[31:0] */
#घोषणा HW_ATL_MSM_REG_WR_DATA_DEFAULT 0x0

/* mac_phy रेजिस्टर ग_लिखो strobe bitfield definitions
 * preprocessor definitions क्रम the bitfield "register write strobe".
 * port="pif_msm_reg_wren_i"
 */

/* रेजिस्टर address क्रम bitfield रेजिस्टर ग_लिखो strobe */
#घोषणा HW_ATL_MSM_REG_WR_STROBE_ADR 0x00004400
/* biपंचांगask क्रम bitfield रेजिस्टर ग_लिखो strobe */
#घोषणा HW_ATL_MSM_REG_WR_STROBE_MSK 0x00000100
/* inverted biपंचांगask क्रम bitfield रेजिस्टर ग_लिखो strobe */
#घोषणा HW_ATL_MSM_REG_WR_STROBE_MSKN 0xfffffeff
/* lower bit position of bitfield रेजिस्टर ग_लिखो strobe */
#घोषणा HW_ATL_MSM_REG_WR_STROBE_SHIFT 8
/* width of bitfield रेजिस्टर ग_लिखो strobe */
#घोषणा HW_ATL_MSM_REG_WR_STROBE_WIDTH 1
/* शेष value of bitfield रेजिस्टर ग_लिखो strobe */
#घोषणा HW_ATL_MSM_REG_WR_STROBE_DEFAULT 0x0

/* रेजिस्टर address क्रम bitfield PTP Digital Clock Read Enable */
#घोषणा HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_ADR 0x00004628
/* biपंचांगask क्रम bitfield PTP Digital Clock Read Enable */
#घोषणा HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_MSK 0x00000010
/* inverted biपंचांगask क्रम bitfield PTP Digital Clock Read Enable */
#घोषणा HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_MSKN 0xFFFFFFEF
/* lower bit position of bitfield PTP Digital Clock Read Enable */
#घोषणा HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_SHIFT 4
/* width of bitfield PTP Digital Clock Read Enable */
#घोषणा HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_WIDTH 1
/* शेष value of bitfield PTP Digital Clock Read Enable */
#घोषणा HW_ATL_PCS_PTP_CLOCK_READ_ENABLE_DEFAULT 0x0

/* रेजिस्टर address क्रम ptp counter पढ़ोing */
#घोषणा HW_ATL_PCS_PTP_TS_VAL_ADDR(index) (0x00004900 + (index) * 0x4)

/* mअगर soft reset bitfield definitions
 * preprocessor definitions क्रम the bitfield "soft reset".
 * port="pif_glb_res_i"
 */

/* रेजिस्टर address क्रम bitfield soft reset */
#घोषणा HW_ATL_GLB_SOFT_RES_ADR 0x00000000
/* biपंचांगask क्रम bitfield soft reset */
#घोषणा HW_ATL_GLB_SOFT_RES_MSK 0x00008000
/* inverted biपंचांगask क्रम bitfield soft reset */
#घोषणा HW_ATL_GLB_SOFT_RES_MSKN 0xffff7fff
/* lower bit position of bitfield soft reset */
#घोषणा HW_ATL_GLB_SOFT_RES_SHIFT 15
/* width of bitfield soft reset */
#घोषणा HW_ATL_GLB_SOFT_RES_WIDTH 1
/* शेष value of bitfield soft reset */
#घोषणा HW_ATL_GLB_SOFT_RES_DEFAULT 0x0

/* mअगर रेजिस्टर reset disable bitfield definitions
 * preprocessor definitions क्रम the bitfield "register reset disable".
 * port="pif_glb_reg_res_dsbl_i"
 */

/* रेजिस्टर address क्रम bitfield रेजिस्टर reset disable */
#घोषणा HW_ATL_GLB_REG_RES_DIS_ADR 0x00000000
/* biपंचांगask क्रम bitfield रेजिस्टर reset disable */
#घोषणा HW_ATL_GLB_REG_RES_DIS_MSK 0x00004000
/* inverted biपंचांगask क्रम bitfield रेजिस्टर reset disable */
#घोषणा HW_ATL_GLB_REG_RES_DIS_MSKN 0xffffbfff
/* lower bit position of bitfield रेजिस्टर reset disable */
#घोषणा HW_ATL_GLB_REG_RES_DIS_SHIFT 14
/* width of bitfield रेजिस्टर reset disable */
#घोषणा HW_ATL_GLB_REG_RES_DIS_WIDTH 1
/* शेष value of bitfield रेजिस्टर reset disable */
#घोषणा HW_ATL_GLB_REG_RES_DIS_DEFAULT 0x1

/* tx dma debug control definitions */
#घोषणा HW_ATL_TX_DMA_DEBUG_CTL_ADR 0x00008920u

/* tx dma descriptor base address msw definitions */
#घोषणा HW_ATL_TX_DMA_DESC_BASE_ADDRMSW_ADR(descriptor) \
			(0x00007c04u + (descriptor) * 0x40)

/* tx dma total request limit */
#घोषणा HW_ATL_TX_DMA_TOTAL_REQ_LIMIT_ADR 0x00007b20u

/* tx पूर्णांकerrupt moderation control रेजिस्टर definitions
 * Preprocessor definitions क्रम TX Interrupt Moderation Control Register
 * Base Address: 0x00008980
 * Parameter: queue अणुQपूर्ण | stride size 0x4 | range [0, 31]
 */

#घोषणा HW_ATL_TX_INTR_MODERATION_CTL_ADR(queue) (0x00008980u + (queue) * 0x4)

/* pcie reg_res_dsbl bitfield definitions
 * preprocessor definitions क्रम the bitfield "reg_res_dsbl".
 * port="pif_pci_reg_res_dsbl_i"
 */

/* रेजिस्टर address क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_PCI_REG_RES_DSBL_ADR 0x00001000
/* biपंचांगask क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_PCI_REG_RES_DSBL_MSK 0x20000000
/* inverted biपंचांगask क्रम bitfield reg_res_dsbl */
#घोषणा HW_ATL_PCI_REG_RES_DSBL_MSKN 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#घोषणा HW_ATL_PCI_REG_RES_DSBL_SHIFT 29
/* width of bitfield reg_res_dsbl */
#घोषणा HW_ATL_PCI_REG_RES_DSBL_WIDTH 1
/* शेष value of bitfield reg_res_dsbl */
#घोषणा HW_ATL_PCI_REG_RES_DSBL_DEFAULT 0x1

/* PCI core control रेजिस्टर */
#घोषणा HW_ATL_PCI_REG_CONTROL6_ADR 0x1014u

/* global microprocessor scratch pad definitions */
#घोषणा HW_ATL_GLB_CPU_SCRATCH_SCP_ADR(scratch_scp) \
	(0x00000300u + (scratch_scp) * 0x4)

/* रेजिस्टर address क्रम bitfield uP Force Interrupt */
#घोषणा HW_ATL_MCP_UP_FORCE_INTERRUPT_ADR 0x00000404
/* biपंचांगask क्रम bitfield uP Force Interrupt */
#घोषणा HW_ATL_MCP_UP_FORCE_INTERRUPT_MSK 0x00000002
/* inverted biपंचांगask क्रम bitfield uP Force Interrupt */
#घोषणा HW_ATL_MCP_UP_FORCE_INTERRUPT_MSKN 0xFFFFFFFD
/* lower bit position of bitfield uP Force Interrupt */
#घोषणा HW_ATL_MCP_UP_FORCE_INTERRUPT_SHIFT 1
/* width of bitfield uP Force Interrupt */
#घोषणा HW_ATL_MCP_UP_FORCE_INTERRUPT_WIDTH 1
/* शेष value of bitfield uP Force Interrupt */
#घोषणा HW_ATL_MCP_UP_FORCE_INTERRUPT_DEFAULT 0x0

/* Preprocessor definitions क्रम Global MDIO Interfaces
 * Address: 0x00000280 + 0x4 * Number of पूर्णांकerface
 */
#घोषणा HW_ATL_GLB_MDIO_IFACE_ADDR_BEGIN   0x00000280u

#घोषणा HW_ATL_GLB_MDIO_IFACE_N_ADR(number) \
	(HW_ATL_GLB_MDIO_IFACE_ADDR_BEGIN + (((number) - 1) * 0x4))

/* MIF MDIO Busy Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "MDIO Busy".
 * PORT="mdio_pif_busy_o"
 */

/* Register address क्रम bitfield MDIO Busy */
#घोषणा HW_ATL_MDIO_BUSY_ADR 0x00000284
/* Biपंचांगask क्रम bitfield MDIO Busy */
#घोषणा HW_ATL_MDIO_BUSY_MSK 0x80000000
/* Inverted biपंचांगask क्रम bitfield MDIO Busy */
#घोषणा HW_ATL_MDIO_BUSY_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield MDIO Busy */
#घोषणा HW_ATL_MDIO_BUSY_SHIFT 31
/* Width of bitfield MDIO Busy */
#घोषणा HW_ATL_MDIO_BUSY_WIDTH 1

/* MIF MDIO Execute Operation Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "MDIO Execute Operation".
 * PORT="pif_mdio_op_start_i"
 */

/* Register address क्रम bitfield MDIO Execute Operation */
#घोषणा HW_ATL_MDIO_EXECUTE_OPERATION_ADR 0x00000284
/* Biपंचांगask क्रम bitfield MDIO Execute Operation */
#घोषणा HW_ATL_MDIO_EXECUTE_OPERATION_MSK 0x00008000
/* Inverted biपंचांगask क्रम bitfield MDIO Execute Operation */
#घोषणा HW_ATL_MDIO_EXECUTE_OPERATION_MSKN 0xFFFF7FFF
/* Lower bit position of bitfield MDIO Execute Operation */
#घोषणा HW_ATL_MDIO_EXECUTE_OPERATION_SHIFT 15
/* Width of bitfield MDIO Execute Operation */
#घोषणा HW_ATL_MDIO_EXECUTE_OPERATION_WIDTH 1
/* Default value of bitfield MDIO Execute Operation */
#घोषणा HW_ATL_MDIO_EXECUTE_OPERATION_DEFAULT 0x0

/* MIF Op Mode [1:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "Op Mode [1:0]".
 * PORT="pif_mdio_mode_i[1:0]"
 */

/* Register address क्रम bitfield Op Mode [1:0] */
#घोषणा HW_ATL_MDIO_OP_MODE_ADR 0x00000284
/* Biपंचांगask क्रम bitfield Op Mode [1:0] */
#घोषणा HW_ATL_MDIO_OP_MODE_MSK 0x00003000
/* Inverted biपंचांगask क्रम bitfield Op Mode [1:0] */
#घोषणा HW_ATL_MDIO_OP_MODE_MSKN 0xFFFFCFFF
/* Lower bit position of bitfield Op Mode [1:0] */
#घोषणा HW_ATL_MDIO_OP_MODE_SHIFT 12
/* Width of bitfield Op Mode [1:0] */
#घोषणा HW_ATL_MDIO_OP_MODE_WIDTH 2
/* Default value of bitfield Op Mode [1:0] */
#घोषणा HW_ATL_MDIO_OP_MODE_DEFAULT 0x0

/* MIF PHY address Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "PHY address".
 * PORT="pif_mdio_phy_addr_i[9:0]"
 */

/* Register address क्रम bitfield PHY address */
#घोषणा HW_ATL_MDIO_PHY_ADDRESS_ADR 0x00000284
/* Biपंचांगask क्रम bitfield PHY address */
#घोषणा HW_ATL_MDIO_PHY_ADDRESS_MSK 0x000003FF
/* Inverted biपंचांगask क्रम bitfield PHY address */
#घोषणा HW_ATL_MDIO_PHY_ADDRESS_MSKN 0xFFFFFC00
/* Lower bit position of bitfield PHY address */
#घोषणा HW_ATL_MDIO_PHY_ADDRESS_SHIFT 0
/* Width of bitfield PHY address */
#घोषणा HW_ATL_MDIO_PHY_ADDRESS_WIDTH 10
/* Default value of bitfield PHY address */
#घोषणा HW_ATL_MDIO_PHY_ADDRESS_DEFAULT 0x0

/* MIF MDIO WriteData [F:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "MDIO WriteData [F:0]".
 * PORT="pif_mdio_wdata_i[15:0]"
 */

/* Register address क्रम bitfield MDIO WriteData [F:0] */
#घोषणा HW_ATL_MDIO_WRITE_DATA_ADR 0x00000288
/* Biपंचांगask क्रम bitfield MDIO WriteData [F:0] */
#घोषणा HW_ATL_MDIO_WRITE_DATA_MSK 0x0000FFFF
/* Inverted biपंचांगask क्रम bitfield MDIO WriteData [F:0] */
#घोषणा HW_ATL_MDIO_WRITE_DATA_MSKN 0xFFFF0000
/* Lower bit position of bitfield MDIO WriteData [F:0] */
#घोषणा HW_ATL_MDIO_WRITE_DATA_SHIFT 0
/* Width of bitfield MDIO WriteData [F:0] */
#घोषणा HW_ATL_MDIO_WRITE_DATA_WIDTH 16
/* Default value of bitfield MDIO WriteData [F:0] */
#घोषणा HW_ATL_MDIO_WRITE_DATA_DEFAULT 0x0

/* MIF MDIO Address [F:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "MDIO Address [F:0]".
 * PORT="pif_mdio_addr_i[15:0]"
 */

/* Register address क्रम bitfield MDIO Address [F:0] */
#घोषणा HW_ATL_MDIO_ADDRESS_ADR 0x0000028C
/* Biपंचांगask क्रम bitfield MDIO Address [F:0] */
#घोषणा HW_ATL_MDIO_ADDRESS_MSK 0x0000FFFF
/* Inverted biपंचांगask क्रम bitfield MDIO Address [F:0] */
#घोषणा HW_ATL_MDIO_ADDRESS_MSKN 0xFFFF0000
/* Lower bit position of bitfield MDIO Address [F:0] */
#घोषणा HW_ATL_MDIO_ADDRESS_SHIFT 0
/* Width of bitfield MDIO Address [F:0] */
#घोषणा HW_ATL_MDIO_ADDRESS_WIDTH 16
/* Default value of bitfield MDIO Address [F:0] */
#घोषणा HW_ATL_MDIO_ADDRESS_DEFAULT 0x0

#घोषणा HW_ATL_MIF_RESET_TIMEOUT_ADR 0x00000348

#घोषणा HW_ATL_FW_SM_MDIO       0x0U
#घोषणा HW_ATL_FW_SM_RAM        0x2U
#घोषणा HW_ATL_FW_SM_RESET1     0x3U
#घोषणा HW_ATL_FW_SM_RESET2     0x4U

#पूर्ण_अगर /* HW_ATL_LLH_INTERNAL_H */
