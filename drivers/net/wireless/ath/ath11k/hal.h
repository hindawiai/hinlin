<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_HAL_H
#घोषणा ATH11K_HAL_H

#समावेश "hal_desc.h"
#समावेश "rx_desc.h"

काष्ठा ath11k_base;

#घोषणा HAL_LINK_DESC_SIZE			(32 << 2)
#घोषणा HAL_LINK_DESC_ALIGN			128
#घोषणा HAL_NUM_MPDUS_PER_LINK_DESC		6
#घोषणा HAL_NUM_TX_MSDUS_PER_LINK_DESC		7
#घोषणा HAL_NUM_RX_MSDUS_PER_LINK_DESC		6
#घोषणा HAL_NUM_MPDU_LINKS_PER_QUEUE_DESC	12
#घोषणा HAL_MAX_AVAIL_BLK_RES			3

#घोषणा HAL_RING_BASE_ALIGN	8

#घोषणा HAL_WBM_IDLE_SCATTER_BUF_SIZE_MAX	32704
/* TODO: Check with hw team on the supported scatter buf size */
#घोषणा HAL_WBM_IDLE_SCATTER_NEXT_PTR_SIZE	8
#घोषणा HAL_WBM_IDLE_SCATTER_BUF_SIZE (HAL_WBM_IDLE_SCATTER_BUF_SIZE_MAX - \
				       HAL_WBM_IDLE_SCATTER_NEXT_PTR_SIZE)

#घोषणा HAL_DSCP_TID_MAP_TBL_NUM_ENTRIES_MAX	48
#घोषणा HAL_DSCP_TID_TBL_SIZE			24

/* calculate the रेजिस्टर address from bar0 of shaकरोw रेजिस्टर x */
#घोषणा HAL_SHADOW_BASE_ADDR			0x000008fc
#घोषणा HAL_SHADOW_NUM_REGS			36
#घोषणा HAL_HP_OFFSET_IN_REG_START		1
#घोषणा HAL_OFFSET_FROM_HP_TO_TP		4

#घोषणा HAL_SHADOW_REG(x) (HAL_SHADOW_BASE_ADDR + (4 * (x)))

/* WCSS Relative address */
#घोषणा HAL_SEQ_WCSS_UMAC_OFFSET		0x00a00000
#घोषणा HAL_SEQ_WCSS_UMAC_REO_REG		0x00a38000
#घोषणा HAL_SEQ_WCSS_UMAC_TCL_REG		0x00a44000
#घोषणा HAL_SEQ_WCSS_UMAC_CE0_SRC_REG(x) \
		(ab->hw_params.regs->hal_seq_wcss_umac_ce0_src_reg)
#घोषणा HAL_SEQ_WCSS_UMAC_CE0_DST_REG(x) \
		(ab->hw_params.regs->hal_seq_wcss_umac_ce0_dst_reg)
#घोषणा HAL_SEQ_WCSS_UMAC_CE1_SRC_REG(x) \
		(ab->hw_params.regs->hal_seq_wcss_umac_ce1_src_reg)
#घोषणा HAL_SEQ_WCSS_UMAC_CE1_DST_REG(x) \
		(ab->hw_params.regs->hal_seq_wcss_umac_ce1_dst_reg)
#घोषणा HAL_SEQ_WCSS_UMAC_WBM_REG		0x00a34000

#घोषणा HAL_CE_WFSS_CE_REG_BASE			0x01b80000
#घोषणा HAL_WLAON_REG_BASE			0x01f80000

/* SW2TCL(x) R0 ring configuration address */
#घोषणा HAL_TCL1_RING_CMN_CTRL_REG		0x00000014
#घोषणा HAL_TCL1_RING_DSCP_TID_MAP		0x0000002c
#घोषणा HAL_TCL1_RING_BASE_LSB(ab)		ab->hw_params.regs->hal_tcl1_ring_base_lsb
#घोषणा HAL_TCL1_RING_BASE_MSB(ab)		ab->hw_params.regs->hal_tcl1_ring_base_msb
#घोषणा HAL_TCL1_RING_ID(ab)			ab->hw_params.regs->hal_tcl1_ring_id
#घोषणा HAL_TCL1_RING_MISC(ab)			ab->hw_params.regs->hal_tcl1_ring_misc
#घोषणा HAL_TCL1_RING_TP_ADDR_LSB(ab) \
	ab->hw_params.regs->hal_tcl1_ring_tp_addr_lsb
#घोषणा HAL_TCL1_RING_TP_ADDR_MSB(ab) \
	ab->hw_params.regs->hal_tcl1_ring_tp_addr_msb
#घोषणा HAL_TCL1_RING_CONSUMER_INT_SETUP_IX0(ab) \
	ab->hw_params.regs->hal_tcl1_ring_consumer_पूर्णांक_setup_ix0
#घोषणा HAL_TCL1_RING_CONSUMER_INT_SETUP_IX1(ab) \
	ab->hw_params.regs->hal_tcl1_ring_consumer_पूर्णांक_setup_ix1
#घोषणा HAL_TCL1_RING_MSI1_BASE_LSB(ab) \
	ab->hw_params.regs->hal_tcl1_ring_msi1_base_lsb
#घोषणा HAL_TCL1_RING_MSI1_BASE_MSB(ab) \
	ab->hw_params.regs->hal_tcl1_ring_msi1_base_msb
#घोषणा HAL_TCL1_RING_MSI1_DATA(ab) \
	ab->hw_params.regs->hal_tcl1_ring_msi1_data
#घोषणा HAL_TCL2_RING_BASE_LSB(ab)		ab->hw_params.regs->hal_tcl2_ring_base_lsb
#घोषणा HAL_TCL_RING_BASE_LSB(ab)		ab->hw_params.regs->hal_tcl_ring_base_lsb

#घोषणा HAL_TCL1_RING_MSI1_BASE_LSB_OFFSET(ab)				\
	(HAL_TCL1_RING_MSI1_BASE_LSB(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_MSI1_BASE_MSB_OFFSET(ab)				\
	(HAL_TCL1_RING_MSI1_BASE_MSB(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_MSI1_DATA_OFFSET(ab)				\
	(HAL_TCL1_RING_MSI1_DATA(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_BASE_MSB_OFFSET(ab)				\
	(HAL_TCL1_RING_BASE_MSB(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_ID_OFFSET(ab)				\
	(HAL_TCL1_RING_ID(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_CONSR_INT_SETUP_IX0_OFFSET(ab)			\
	(HAL_TCL1_RING_CONSUMER_INT_SETUP_IX0(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_CONSR_INT_SETUP_IX1_OFFSET(ab) \
		(HAL_TCL1_RING_CONSUMER_INT_SETUP_IX1(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_TP_ADDR_LSB_OFFSET(ab) \
		(HAL_TCL1_RING_TP_ADDR_LSB(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_TP_ADDR_MSB_OFFSET(ab) \
		(HAL_TCL1_RING_TP_ADDR_MSB(ab) - HAL_TCL1_RING_BASE_LSB(ab))
#घोषणा HAL_TCL1_RING_MISC_OFFSET(ab) \
		(HAL_TCL1_RING_MISC(ab) - HAL_TCL1_RING_BASE_LSB(ab))

/* SW2TCL(x) R2 ring poपूर्णांकers (head/tail) address */
#घोषणा HAL_TCL1_RING_HP			0x00002000
#घोषणा HAL_TCL1_RING_TP			0x00002004
#घोषणा HAL_TCL2_RING_HP			0x00002008
#घोषणा HAL_TCL_RING_HP				0x00002018

#घोषणा HAL_TCL1_RING_TP_OFFSET \
		(HAL_TCL1_RING_TP - HAL_TCL1_RING_HP)

/* TCL STATUS ring address */
#घोषणा HAL_TCL_STATUS_RING_BASE_LSB(ab) \
	ab->hw_params.regs->hal_tcl_status_ring_base_lsb
#घोषणा HAL_TCL_STATUS_RING_HP			0x00002030

/* REO2SW(x) R0 ring configuration address */
#घोषणा HAL_REO1_GEN_ENABLE			0x00000000
#घोषणा HAL_REO1_DEST_RING_CTRL_IX_0		0x00000004
#घोषणा HAL_REO1_DEST_RING_CTRL_IX_1		0x00000008
#घोषणा HAL_REO1_DEST_RING_CTRL_IX_2		0x0000000c
#घोषणा HAL_REO1_DEST_RING_CTRL_IX_3		0x00000010
#घोषणा HAL_REO1_RING_BASE_LSB(ab)		ab->hw_params.regs->hal_reo1_ring_base_lsb
#घोषणा HAL_REO1_RING_BASE_MSB(ab)		ab->hw_params.regs->hal_reo1_ring_base_msb
#घोषणा HAL_REO1_RING_ID(ab)			ab->hw_params.regs->hal_reo1_ring_id
#घोषणा HAL_REO1_RING_MISC(ab)			ab->hw_params.regs->hal_reo1_ring_misc
#घोषणा HAL_REO1_RING_HP_ADDR_LSB(ab) \
	ab->hw_params.regs->hal_reo1_ring_hp_addr_lsb
#घोषणा HAL_REO1_RING_HP_ADDR_MSB(ab) \
	ab->hw_params.regs->hal_reo1_ring_hp_addr_msb
#घोषणा HAL_REO1_RING_PRODUCER_INT_SETUP(ab) \
	ab->hw_params.regs->hal_reo1_ring_producer_पूर्णांक_setup
#घोषणा HAL_REO1_RING_MSI1_BASE_LSB(ab) \
	ab->hw_params.regs->hal_reo1_ring_msi1_base_lsb
#घोषणा HAL_REO1_RING_MSI1_BASE_MSB(ab) \
	ab->hw_params.regs->hal_reo1_ring_msi1_base_msb
#घोषणा HAL_REO1_RING_MSI1_DATA(ab) \
	ab->hw_params.regs->hal_reo1_ring_msi1_data
#घोषणा HAL_REO2_RING_BASE_LSB(ab)		ab->hw_params.regs->hal_reo2_ring_base_lsb
#घोषणा HAL_REO1_AGING_THRESH_IX_0(ab) \
	ab->hw_params.regs->hal_reo1_aging_thresh_ix_0
#घोषणा HAL_REO1_AGING_THRESH_IX_1(ab) \
	ab->hw_params.regs->hal_reo1_aging_thresh_ix_1
#घोषणा HAL_REO1_AGING_THRESH_IX_2(ab) \
	ab->hw_params.regs->hal_reo1_aging_thresh_ix_2
#घोषणा HAL_REO1_AGING_THRESH_IX_3(ab) \
	ab->hw_params.regs->hal_reo1_aging_thresh_ix_3

#घोषणा HAL_REO1_RING_MSI1_BASE_LSB_OFFSET(ab) \
		(HAL_REO1_RING_MSI1_BASE_LSB(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_MSI1_BASE_MSB_OFFSET(ab) \
		(HAL_REO1_RING_MSI1_BASE_MSB(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_MSI1_DATA_OFFSET(ab) \
		(HAL_REO1_RING_MSI1_DATA(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_BASE_MSB_OFFSET(ab) \
		(HAL_REO1_RING_BASE_MSB(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_ID_OFFSET(ab) (HAL_REO1_RING_ID(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_PRODUCER_INT_SETUP_OFFSET(ab) \
		(HAL_REO1_RING_PRODUCER_INT_SETUP(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_HP_ADDR_LSB_OFFSET(ab) \
		(HAL_REO1_RING_HP_ADDR_LSB(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_HP_ADDR_MSB_OFFSET(ab) \
		(HAL_REO1_RING_HP_ADDR_MSB(ab) - HAL_REO1_RING_BASE_LSB(ab))
#घोषणा HAL_REO1_RING_MISC_OFFSET(ab) \
	(HAL_REO1_RING_MISC(ab) - HAL_REO1_RING_BASE_LSB(ab))

/* REO2SW(x) R2 ring poपूर्णांकers (head/tail) address */
#घोषणा HAL_REO1_RING_HP(ab)			ab->hw_params.regs->hal_reo1_ring_hp
#घोषणा HAL_REO1_RING_TP(ab)			ab->hw_params.regs->hal_reo1_ring_tp
#घोषणा HAL_REO2_RING_HP(ab)			ab->hw_params.regs->hal_reo2_ring_hp

#घोषणा HAL_REO1_RING_TP_OFFSET(ab)	(HAL_REO1_RING_TP(ab) - HAL_REO1_RING_HP(ab))

/* REO2TCL R0 ring configuration address */
#घोषणा HAL_REO_TCL_RING_BASE_LSB(ab) \
	ab->hw_params.regs->hal_reo_tcl_ring_base_lsb

/* REO2TCL R2 ring poपूर्णांकer (head/tail) address */
#घोषणा HAL_REO_TCL_RING_HP(ab)			ab->hw_params.regs->hal_reo_tcl_ring_hp

/* REO CMD R0 address */
#घोषणा HAL_REO_CMD_RING_BASE_LSB		0x00000194

/* REO CMD R2 address */
#घोषणा HAL_REO_CMD_HP				0x00003020

/* SW2REO R0 address */
#घोषणा HAL_SW2REO_RING_BASE_LSB		0x000001ec

/* SW2REO R2 address */
#घोषणा HAL_SW2REO_RING_HP			0x00003028

/* CE ring R0 address */
#घोषणा HAL_CE_DST_RING_BASE_LSB		0x00000000
#घोषणा HAL_CE_DST_STATUS_RING_BASE_LSB		0x00000058
#घोषणा HAL_CE_DST_RING_CTRL			0x000000b0

/* CE ring R2 address */
#घोषणा HAL_CE_DST_RING_HP			0x00000400
#घोषणा HAL_CE_DST_STATUS_RING_HP		0x00000408

/* REO status address */
#घोषणा HAL_REO_STATUS_RING_BASE_LSB(ab) \
	ab->hw_params.regs->hal_reo_status_ring_base_lsb
#घोषणा HAL_REO_STATUS_HP(ab)			ab->hw_params.regs->hal_reo_status_hp

/* WBM Idle R0 address */
#घोषणा HAL_WBM_IDLE_LINK_RING_BASE_LSB(x) \
		(ab->hw_params.regs->hal_wbm_idle_link_ring_base_lsb)
#घोषणा HAL_WBM_IDLE_LINK_RING_MISC_ADDR(x) \
		(ab->hw_params.regs->hal_wbm_idle_link_ring_misc)
#घोषणा HAL_WBM_R0_IDLE_LIST_CONTROL_ADDR	0x00000048
#घोषणा HAL_WBM_R0_IDLE_LIST_SIZE_ADDR		0x0000004c
#घोषणा HAL_WBM_SCATTERED_RING_BASE_LSB		0x00000058
#घोषणा HAL_WBM_SCATTERED_RING_BASE_MSB		0x0000005c
#घोषणा HAL_WBM_SCATTERED_DESC_PTR_HEAD_INFO_IX0 0x00000068
#घोषणा HAL_WBM_SCATTERED_DESC_PTR_HEAD_INFO_IX1 0x0000006c
#घोषणा HAL_WBM_SCATTERED_DESC_PTR_TAIL_INFO_IX0 0x00000078
#घोषणा HAL_WBM_SCATTERED_DESC_PTR_TAIL_INFO_IX1 0x0000007c
#घोषणा HAL_WBM_SCATTERED_DESC_PTR_HP_ADDR	 0x00000084

/* WBM Idle R2 address */
#घोषणा HAL_WBM_IDLE_LINK_RING_HP		0x000030b0

/* SW2WBM R0 release address */
#घोषणा HAL_WBM_RELEASE_RING_BASE_LSB(x) \
		(ab->hw_params.regs->hal_wbm_release_ring_base_lsb)

/* SW2WBM R2 release address */
#घोषणा HAL_WBM_RELEASE_RING_HP			0x00003018

/* WBM2SW R0 release address */
#घोषणा HAL_WBM0_RELEASE_RING_BASE_LSB(x) \
		(ab->hw_params.regs->hal_wbm0_release_ring_base_lsb)
#घोषणा HAL_WBM1_RELEASE_RING_BASE_LSB(x) \
		(ab->hw_params.regs->hal_wbm1_release_ring_base_lsb)

/* WBM2SW R2 release address */
#घोषणा HAL_WBM0_RELEASE_RING_HP		0x000030c0
#घोषणा HAL_WBM1_RELEASE_RING_HP		0x000030c8

/* TCL ring feild mask and offset */
#घोषणा HAL_TCL1_RING_BASE_MSB_RING_SIZE		GENMASK(27, 8)
#घोषणा HAL_TCL1_RING_BASE_MSB_RING_BASE_ADDR_MSB	GENMASK(7, 0)
#घोषणा HAL_TCL1_RING_ID_ENTRY_SIZE			GENMASK(7, 0)
#घोषणा HAL_TCL1_RING_MISC_MSI_LOOPCNT_DISABLE		BIT(1)
#घोषणा HAL_TCL1_RING_MISC_MSI_SWAP			BIT(3)
#घोषणा HAL_TCL1_RING_MISC_HOST_FW_SWAP			BIT(4)
#घोषणा HAL_TCL1_RING_MISC_DATA_TLV_SWAP		BIT(5)
#घोषणा HAL_TCL1_RING_MISC_SRNG_ENABLE			BIT(6)
#घोषणा HAL_TCL1_RING_CONSR_INT_SETUP_IX0_INTR_TMR_THOLD   GENMASK(31, 16)
#घोषणा HAL_TCL1_RING_CONSR_INT_SETUP_IX0_BATCH_COUNTER_THOLD GENMASK(14, 0)
#घोषणा HAL_TCL1_RING_CONSR_INT_SETUP_IX1_LOW_THOLD	GENMASK(15, 0)
#घोषणा HAL_TCL1_RING_MSI1_BASE_MSB_MSI1_ENABLE		BIT(8)
#घोषणा HAL_TCL1_RING_MSI1_BASE_MSB_ADDR		GENMASK(7, 0)
#घोषणा HAL_TCL1_RING_CMN_CTRL_DSCP_TID_MAP_PROG_EN	BIT(17)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP		GENMASK(31, 0)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP0		GENMASK(2, 0)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP1		GENMASK(5, 3)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP2		GENMASK(8, 6)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP3		GENMASK(11, 9)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP4		GENMASK(14, 12)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP5		GENMASK(17, 15)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP6		GENMASK(20, 18)
#घोषणा HAL_TCL1_RING_FIELD_DSCP_TID_MAP7		GENMASK(23, 21)

/* REO ring feild mask and offset */
#घोषणा HAL_REO1_RING_BASE_MSB_RING_SIZE		GENMASK(27, 8)
#घोषणा HAL_REO1_RING_BASE_MSB_RING_BASE_ADDR_MSB	GENMASK(7, 0)
#घोषणा HAL_REO1_RING_ID_RING_ID			GENMASK(15, 8)
#घोषणा HAL_REO1_RING_ID_ENTRY_SIZE			GENMASK(7, 0)
#घोषणा HAL_REO1_RING_MISC_MSI_SWAP			BIT(3)
#घोषणा HAL_REO1_RING_MISC_HOST_FW_SWAP			BIT(4)
#घोषणा HAL_REO1_RING_MISC_DATA_TLV_SWAP		BIT(5)
#घोषणा HAL_REO1_RING_MISC_SRNG_ENABLE			BIT(6)
#घोषणा HAL_REO1_RING_PRDR_INT_SETUP_INTR_TMR_THOLD	GENMASK(31, 16)
#घोषणा HAL_REO1_RING_PRDR_INT_SETUP_BATCH_COUNTER_THOLD GENMASK(14, 0)
#घोषणा HAL_REO1_RING_MSI1_BASE_MSB_MSI1_ENABLE		BIT(8)
#घोषणा HAL_REO1_RING_MSI1_BASE_MSB_ADDR		GENMASK(7, 0)
#घोषणा HAL_REO1_GEN_ENABLE_FRAG_DST_RING		GENMASK(25, 23)
#घोषणा HAL_REO1_GEN_ENABLE_AGING_LIST_ENABLE		BIT(2)
#घोषणा HAL_REO1_GEN_ENABLE_AGING_FLUSH_ENABLE		BIT(3)

/* CE ring bit field mask and shअगरt */
#घोषणा HAL_CE_DST_R0_DEST_CTRL_MAX_LEN			GENMASK(15, 0)

#घोषणा HAL_ADDR_LSB_REG_MASK				0xffffffff

#घोषणा HAL_ADDR_MSB_REG_SHIFT				32

/* WBM ring bit field mask and shअगरt */
#घोषणा HAL_WBM_LINK_DESC_IDLE_LIST_MODE		BIT(1)
#घोषणा HAL_WBM_SCATTER_BUFFER_SIZE			GENMASK(10, 2)
#घोषणा HAL_WBM_SCATTER_RING_SIZE_OF_IDLE_LINK_DESC_LIST GENMASK(31, 16)
#घोषणा HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_39_32	GENMASK(7, 0)
#घोषणा HAL_WBM_SCATTERED_DESC_MSB_BASE_ADDR_MATCH_TAG	GENMASK(31, 8)

#घोषणा HAL_WBM_SCATTERED_DESC_HEAD_P_OFFSET_IX1	GENMASK(20, 8)
#घोषणा HAL_WBM_SCATTERED_DESC_TAIL_P_OFFSET_IX1	GENMASK(20, 8)

#घोषणा BASE_ADDR_MATCH_TAG_VAL 0x5

#घोषणा HAL_REO_REO2SW1_RING_BASE_MSB_RING_SIZE		0x000fffff
#घोषणा HAL_REO_REO2TCL_RING_BASE_MSB_RING_SIZE		0x000fffff
#घोषणा HAL_REO_SW2REO_RING_BASE_MSB_RING_SIZE		0x0000ffff
#घोषणा HAL_REO_CMD_RING_BASE_MSB_RING_SIZE		0x0000ffff
#घोषणा HAL_REO_STATUS_RING_BASE_MSB_RING_SIZE		0x0000ffff
#घोषणा HAL_SW2TCL1_RING_BASE_MSB_RING_SIZE		0x000fffff
#घोषणा HAL_SW2TCL1_CMD_RING_BASE_MSB_RING_SIZE		0x000fffff
#घोषणा HAL_TCL_STATUS_RING_BASE_MSB_RING_SIZE		0x0000ffff
#घोषणा HAL_CE_SRC_RING_BASE_MSB_RING_SIZE		0x0000ffff
#घोषणा HAL_CE_DST_RING_BASE_MSB_RING_SIZE		0x0000ffff
#घोषणा HAL_CE_DST_STATUS_RING_BASE_MSB_RING_SIZE	0x0000ffff
#घोषणा HAL_WBM_IDLE_LINK_RING_BASE_MSB_RING_SIZE	0x0000ffff
#घोषणा HAL_SW2WBM_RELEASE_RING_BASE_MSB_RING_SIZE	0x0000ffff
#घोषणा HAL_WBM2SW_RELEASE_RING_BASE_MSB_RING_SIZE	0x000fffff
#घोषणा HAL_RXDMA_RING_MAX_SIZE				0x0000ffff

/* Add any other errors here and वापस them in
 * ath11k_hal_rx_desc_get_err().
 */

क्रमागत hal_srng_ring_id अणु
	HAL_SRNG_RING_ID_REO2SW1 = 0,
	HAL_SRNG_RING_ID_REO2SW2,
	HAL_SRNG_RING_ID_REO2SW3,
	HAL_SRNG_RING_ID_REO2SW4,
	HAL_SRNG_RING_ID_REO2TCL,
	HAL_SRNG_RING_ID_SW2REO,

	HAL_SRNG_RING_ID_REO_CMD = 8,
	HAL_SRNG_RING_ID_REO_STATUS,

	HAL_SRNG_RING_ID_SW2TCL1 = 16,
	HAL_SRNG_RING_ID_SW2TCL2,
	HAL_SRNG_RING_ID_SW2TCL3,
	HAL_SRNG_RING_ID_SW2TCL4,

	HAL_SRNG_RING_ID_SW2TCL_CMD = 24,
	HAL_SRNG_RING_ID_TCL_STATUS,

	HAL_SRNG_RING_ID_CE0_SRC = 32,
	HAL_SRNG_RING_ID_CE1_SRC,
	HAL_SRNG_RING_ID_CE2_SRC,
	HAL_SRNG_RING_ID_CE3_SRC,
	HAL_SRNG_RING_ID_CE4_SRC,
	HAL_SRNG_RING_ID_CE5_SRC,
	HAL_SRNG_RING_ID_CE6_SRC,
	HAL_SRNG_RING_ID_CE7_SRC,
	HAL_SRNG_RING_ID_CE8_SRC,
	HAL_SRNG_RING_ID_CE9_SRC,
	HAL_SRNG_RING_ID_CE10_SRC,
	HAL_SRNG_RING_ID_CE11_SRC,

	HAL_SRNG_RING_ID_CE0_DST = 56,
	HAL_SRNG_RING_ID_CE1_DST,
	HAL_SRNG_RING_ID_CE2_DST,
	HAL_SRNG_RING_ID_CE3_DST,
	HAL_SRNG_RING_ID_CE4_DST,
	HAL_SRNG_RING_ID_CE5_DST,
	HAL_SRNG_RING_ID_CE6_DST,
	HAL_SRNG_RING_ID_CE7_DST,
	HAL_SRNG_RING_ID_CE8_DST,
	HAL_SRNG_RING_ID_CE9_DST,
	HAL_SRNG_RING_ID_CE10_DST,
	HAL_SRNG_RING_ID_CE11_DST,

	HAL_SRNG_RING_ID_CE0_DST_STATUS = 80,
	HAL_SRNG_RING_ID_CE1_DST_STATUS,
	HAL_SRNG_RING_ID_CE2_DST_STATUS,
	HAL_SRNG_RING_ID_CE3_DST_STATUS,
	HAL_SRNG_RING_ID_CE4_DST_STATUS,
	HAL_SRNG_RING_ID_CE5_DST_STATUS,
	HAL_SRNG_RING_ID_CE6_DST_STATUS,
	HAL_SRNG_RING_ID_CE7_DST_STATUS,
	HAL_SRNG_RING_ID_CE8_DST_STATUS,
	HAL_SRNG_RING_ID_CE9_DST_STATUS,
	HAL_SRNG_RING_ID_CE10_DST_STATUS,
	HAL_SRNG_RING_ID_CE11_DST_STATUS,

	HAL_SRNG_RING_ID_WBM_IDLE_LINK = 104,
	HAL_SRNG_RING_ID_WBM_SW_RELEASE,
	HAL_SRNG_RING_ID_WBM2SW0_RELEASE,
	HAL_SRNG_RING_ID_WBM2SW1_RELEASE,
	HAL_SRNG_RING_ID_WBM2SW2_RELEASE,
	HAL_SRNG_RING_ID_WBM2SW3_RELEASE,

	HAL_SRNG_RING_ID_UMAC_ID_END = 127,
	HAL_SRNG_RING_ID_LMAC1_ID_START,

	HAL_SRNG_RING_ID_WMAC1_SW2RXDMA0_BUF = HAL_SRNG_RING_ID_LMAC1_ID_START,
	HAL_SRNG_RING_ID_WMAC1_SW2RXDMA1_BUF,
	HAL_SRNG_RING_ID_WMAC1_SW2RXDMA2_BUF,
	HAL_SRNG_RING_ID_WMAC1_SW2RXDMA0_STATBUF,
	HAL_SRNG_RING_ID_WMAC1_SW2RXDMA1_STATBUF,
	HAL_SRNG_RING_ID_WMAC1_RXDMA2SW0,
	HAL_SRNG_RING_ID_WMAC1_RXDMA2SW1,
	HAL_SRNG_RING_ID_WMAC1_SW2RXDMA1_DESC,
	HAL_SRNG_RING_ID_RXDMA_सूची_BUF,

	HAL_SRNG_RING_ID_LMAC1_ID_END = 143
पूर्ण;

/* SRNG रेजिस्टरs are split पूर्णांकo two groups R0 and R2 */
#घोषणा HAL_SRNG_REG_GRP_R0	0
#घोषणा HAL_SRNG_REG_GRP_R2	1
#घोषणा HAL_SRNG_NUM_REG_GRP    2

#घोषणा HAL_SRNG_NUM_LMACS      3
#घोषणा HAL_SRNG_REO_EXCEPTION  HAL_SRNG_RING_ID_REO2SW1
#घोषणा HAL_SRNG_RINGS_PER_LMAC (HAL_SRNG_RING_ID_LMAC1_ID_END - \
				 HAL_SRNG_RING_ID_LMAC1_ID_START)
#घोषणा HAL_SRNG_NUM_LMAC_RINGS (HAL_SRNG_NUM_LMACS * HAL_SRNG_RINGS_PER_LMAC)
#घोषणा HAL_SRNG_RING_ID_MAX    (HAL_SRNG_RING_ID_UMAC_ID_END + \
				 HAL_SRNG_NUM_LMAC_RINGS)

क्रमागत hal_ring_type अणु
	HAL_REO_DST,
	HAL_REO_EXCEPTION,
	HAL_REO_REINJECT,
	HAL_REO_CMD,
	HAL_REO_STATUS,
	HAL_TCL_DATA,
	HAL_TCL_CMD,
	HAL_TCL_STATUS,
	HAL_CE_SRC,
	HAL_CE_DST,
	HAL_CE_DST_STATUS,
	HAL_WBM_IDLE_LINK,
	HAL_SW2WBM_RELEASE,
	HAL_WBM2SW_RELEASE,
	HAL_RXDMA_BUF,
	HAL_RXDMA_DST,
	HAL_RXDMA_MONITOR_BUF,
	HAL_RXDMA_MONITOR_STATUS,
	HAL_RXDMA_MONITOR_DST,
	HAL_RXDMA_MONITOR_DESC,
	HAL_RXDMA_सूची_BUF,
	HAL_MAX_RING_TYPES,
पूर्ण;

#घोषणा HAL_RX_MAX_BA_WINDOW	256

#घोषणा HAL_DEFAULT_REO_TIMEOUT_USEC		(40 * 1000)

/**
 * क्रमागत hal_reo_cmd_type: Enum क्रम REO command type
 * @CMD_GET_QUEUE_STATS: Get REO queue status/stats
 * @CMD_FLUSH_QUEUE: Flush all frames in REO queue
 * @CMD_FLUSH_CACHE: Flush descriptor entries in the cache
 * @CMD_UNBLOCK_CACHE: Unblock a descriptor's address that was blocked
 *      earlier with a 'REO_FLUSH_CACHE' command
 * @CMD_FLUSH_TIMEOUT_LIST: Flush buffers/descriptors from समयout list
 * @CMD_UPDATE_RX_REO_QUEUE: Update REO queue settings
 */
क्रमागत hal_reo_cmd_type अणु
	HAL_REO_CMD_GET_QUEUE_STATS     = 0,
	HAL_REO_CMD_FLUSH_QUEUE         = 1,
	HAL_REO_CMD_FLUSH_CACHE         = 2,
	HAL_REO_CMD_UNBLOCK_CACHE       = 3,
	HAL_REO_CMD_FLUSH_TIMEOUT_LIST  = 4,
	HAL_REO_CMD_UPDATE_RX_QUEUE     = 5,
पूर्ण;

/**
 * क्रमागत hal_reo_cmd_status: Enum क्रम execution status of REO command
 * @HAL_REO_CMD_SUCCESS: Command has successfully executed
 * @HAL_REO_CMD_BLOCKED: Command could not be executed as the queue
 *			 or cache was blocked
 * @HAL_REO_CMD_FAILED: Command execution failed, could be due to
 *			invalid queue desc
 * @HAL_REO_CMD_RESOURCE_BLOCKED:
 * @HAL_REO_CMD_DRAIN:
 */
क्रमागत hal_reo_cmd_status अणु
	HAL_REO_CMD_SUCCESS		= 0,
	HAL_REO_CMD_BLOCKED		= 1,
	HAL_REO_CMD_FAILED		= 2,
	HAL_REO_CMD_RESOURCE_BLOCKED	= 3,
	HAL_REO_CMD_DRAIN		= 0xff,
पूर्ण;

काष्ठा hal_wbm_idle_scatter_list अणु
	dma_addr_t paddr;
	काष्ठा hal_wbm_link_desc *vaddr;
पूर्ण;

काष्ठा hal_srng_params अणु
	dma_addr_t ring_base_paddr;
	u32 *ring_base_vaddr;
	पूर्णांक num_entries;
	u32 पूर्णांकr_batch_cntr_thres_entries;
	u32 पूर्णांकr_समयr_thres_us;
	u32 flags;
	u32 max_buffer_len;
	u32 low_threshold;
	dma_addr_t msi_addr;
	u32 msi_data;

	/* Add more params as needed */
पूर्ण;

क्रमागत hal_srng_dir अणु
	HAL_SRNG_सूची_SRC,
	HAL_SRNG_सूची_DST
पूर्ण;

/* srng flags */
#घोषणा HAL_SRNG_FLAGS_MSI_SWAP			0x00000008
#घोषणा HAL_SRNG_FLAGS_RING_PTR_SWAP		0x00000010
#घोषणा HAL_SRNG_FLAGS_DATA_TLV_SWAP		0x00000020
#घोषणा HAL_SRNG_FLAGS_LOW_THRESH_INTR_EN	0x00010000
#घोषणा HAL_SRNG_FLAGS_MSI_INTR			0x00020000
#घोषणा HAL_SRNG_FLAGS_LMAC_RING		0x80000000

#घोषणा HAL_SRNG_TLV_HDR_TAG		GENMASK(9, 1)
#घोषणा HAL_SRNG_TLV_HDR_LEN		GENMASK(25, 10)

/* Common SRNG ring काष्ठाure क्रम source and destination rings */
काष्ठा hal_srng अणु
	/* Unique SRNG ring ID */
	u8 ring_id;

	/* Ring initialization करोne */
	u8 initialized;

	/* Interrupt/MSI value asचिन्हित to this ring */
	पूर्णांक irq;

	/* Physical base address of the ring */
	dma_addr_t ring_base_paddr;

	/* Virtual base address of the ring */
	u32 *ring_base_vaddr;

	/* Number of entries in ring */
	u32 num_entries;

	/* Ring size */
	u32 ring_size;

	/* Ring size mask */
	u32 ring_size_mask;

	/* Size of ring entry */
	u32 entry_size;

	/* Interrupt समयr threshold - in micro seconds */
	u32 पूर्णांकr_समयr_thres_us;

	/* Interrupt batch counter threshold - in number of ring entries */
	u32 पूर्णांकr_batch_cntr_thres_entries;

	/* MSI Address */
	dma_addr_t msi_addr;

	/* MSI data */
	u32 msi_data;

	/* Misc flags */
	u32 flags;

	/* Lock क्रम serializing ring index updates */
	spinlock_t lock;

	/* Start offset of SRNG रेजिस्टर groups क्रम this ring
	 * TBD: See अगर this is required - रेजिस्टर address can be derived
	 * from ring ID
	 */
	u32 hwreg_base[HAL_SRNG_NUM_REG_GRP];

	u64 बारtamp;

	/* Source or Destination ring */
	क्रमागत hal_srng_dir ring_dir;

	जोड़ अणु
		काष्ठा अणु
			/* SW tail poपूर्णांकer */
			u32 tp;

			/* Shaकरोw head poपूर्णांकer location to be updated by HW */
			अस्थिर u32 *hp_addr;

			/* Cached head poपूर्णांकer */
			u32 cached_hp;

			/* Tail poपूर्णांकer location to be updated by SW - This
			 * will be a रेजिस्टर address and need not be
			 * accessed through SW काष्ठाure
			 */
			u32 *tp_addr;

			/* Current SW loop cnt */
			u32 loop_cnt;

			/* max transfer size */
			u16 max_buffer_length;

			/* head poपूर्णांकer at access end */
			u32 last_hp;
		पूर्ण dst_ring;

		काष्ठा अणु
			/* SW head poपूर्णांकer */
			u32 hp;

			/* SW reap head poपूर्णांकer */
			u32 reap_hp;

			/* Shaकरोw tail poपूर्णांकer location to be updated by HW */
			u32 *tp_addr;

			/* Cached tail poपूर्णांकer */
			u32 cached_tp;

			/* Head poपूर्णांकer location to be updated by SW - This
			 * will be a रेजिस्टर address and need not be accessed
			 * through SW काष्ठाure
			 */
			u32 *hp_addr;

			/* Low threshold - in number of ring entries */
			u32 low_threshold;

			/* tail poपूर्णांकer at access end */
			u32 last_tp;
		पूर्ण src_ring;
	पूर्ण u;
पूर्ण;

/* Interrupt mitigation - Batch threshold in terms of numer of frames */
#घोषणा HAL_SRNG_INT_BATCH_THRESHOLD_TX 256
#घोषणा HAL_SRNG_INT_BATCH_THRESHOLD_RX 128
#घोषणा HAL_SRNG_INT_BATCH_THRESHOLD_OTHER 1

/* Interrupt mitigation - समयr threshold in us */
#घोषणा HAL_SRNG_INT_TIMER_THRESHOLD_TX 1000
#घोषणा HAL_SRNG_INT_TIMER_THRESHOLD_RX 500
#घोषणा HAL_SRNG_INT_TIMER_THRESHOLD_OTHER 256

/* HW SRNG configuration table */
काष्ठा hal_srng_config अणु
	पूर्णांक start_ring_id;
	u16 max_rings;
	u16 entry_size;
	u32 reg_start[HAL_SRNG_NUM_REG_GRP];
	u16 reg_size[HAL_SRNG_NUM_REG_GRP];
	u8 lmac_ring;
	क्रमागत hal_srng_dir ring_dir;
	u32 max_size;
पूर्ण;

/**
 * क्रमागत hal_rx_buf_वापस_buf_manager
 *
 * @HAL_RX_BUF_RBM_WBM_IDLE_BUF_LIST: Buffer वापसed to WBM idle buffer list
 * @HAL_RX_BUF_RBM_WBM_IDLE_DESC_LIST: Descriptor वापसed to WBM idle
 *	descriptor list.
 * @HAL_RX_BUF_RBM_FW_BM: Buffer वापसed to FW
 * @HAL_RX_BUF_RBM_SW0_BM: For Tx completion -- वापसed to host
 * @HAL_RX_BUF_RBM_SW1_BM: For Tx completion -- वापसed to host
 * @HAL_RX_BUF_RBM_SW2_BM: For Tx completion -- वापसed to host
 * @HAL_RX_BUF_RBM_SW3_BM: For Rx release -- वापसed to host
 */

क्रमागत hal_rx_buf_वापस_buf_manager अणु
	HAL_RX_BUF_RBM_WBM_IDLE_BUF_LIST,
	HAL_RX_BUF_RBM_WBM_IDLE_DESC_LIST,
	HAL_RX_BUF_RBM_FW_BM,
	HAL_RX_BUF_RBM_SW0_BM,
	HAL_RX_BUF_RBM_SW1_BM,
	HAL_RX_BUF_RBM_SW2_BM,
	HAL_RX_BUF_RBM_SW3_BM,
पूर्ण;

#घोषणा HAL_SRNG_DESC_LOOP_CNT		0xf0000000

#घोषणा HAL_REO_CMD_FLG_NEED_STATUS		BIT(0)
#घोषणा HAL_REO_CMD_FLG_STATS_CLEAR		BIT(1)
#घोषणा HAL_REO_CMD_FLG_FLUSH_BLOCK_LATER	BIT(2)
#घोषणा HAL_REO_CMD_FLG_FLUSH_RELEASE_BLOCKING	BIT(3)
#घोषणा HAL_REO_CMD_FLG_FLUSH_NO_INVAL		BIT(4)
#घोषणा HAL_REO_CMD_FLG_FLUSH_FWD_ALL_MPDUS	BIT(5)
#घोषणा HAL_REO_CMD_FLG_FLUSH_ALL		BIT(6)
#घोषणा HAL_REO_CMD_FLG_UNBLK_RESOURCE		BIT(7)
#घोषणा HAL_REO_CMD_FLG_UNBLK_CACHE		BIT(8)

/* Should be matching with HAL_REO_UPD_RX_QUEUE_INFO0_UPD_* feilds */
#घोषणा HAL_REO_CMD_UPD0_RX_QUEUE_NUM		BIT(8)
#घोषणा HAL_REO_CMD_UPD0_VLD			BIT(9)
#घोषणा HAL_REO_CMD_UPD0_ALDC			BIT(10)
#घोषणा HAL_REO_CMD_UPD0_DIS_DUP_DETECTION	BIT(11)
#घोषणा HAL_REO_CMD_UPD0_SOFT_REORDER_EN	BIT(12)
#घोषणा HAL_REO_CMD_UPD0_AC			BIT(13)
#घोषणा HAL_REO_CMD_UPD0_BAR			BIT(14)
#घोषणा HAL_REO_CMD_UPD0_RETRY			BIT(15)
#घोषणा HAL_REO_CMD_UPD0_CHECK_2K_MODE		BIT(16)
#घोषणा HAL_REO_CMD_UPD0_OOR_MODE		BIT(17)
#घोषणा HAL_REO_CMD_UPD0_BA_WINDOW_SIZE		BIT(18)
#घोषणा HAL_REO_CMD_UPD0_PN_CHECK		BIT(19)
#घोषणा HAL_REO_CMD_UPD0_EVEN_PN		BIT(20)
#घोषणा HAL_REO_CMD_UPD0_UNEVEN_PN		BIT(21)
#घोषणा HAL_REO_CMD_UPD0_PN_HANDLE_ENABLE	BIT(22)
#घोषणा HAL_REO_CMD_UPD0_PN_SIZE		BIT(23)
#घोषणा HAL_REO_CMD_UPD0_IGNORE_AMPDU_FLG	BIT(24)
#घोषणा HAL_REO_CMD_UPD0_SVLD			BIT(25)
#घोषणा HAL_REO_CMD_UPD0_SSN			BIT(26)
#घोषणा HAL_REO_CMD_UPD0_SEQ_2K_ERR		BIT(27)
#घोषणा HAL_REO_CMD_UPD0_PN_ERR			BIT(28)
#घोषणा HAL_REO_CMD_UPD0_PN_VALID		BIT(29)
#घोषणा HAL_REO_CMD_UPD0_PN			BIT(30)

/* Should be matching with HAL_REO_UPD_RX_QUEUE_INFO1_* feilds */
#घोषणा HAL_REO_CMD_UPD1_VLD			BIT(16)
#घोषणा HAL_REO_CMD_UPD1_ALDC			GENMASK(18, 17)
#घोषणा HAL_REO_CMD_UPD1_DIS_DUP_DETECTION	BIT(19)
#घोषणा HAL_REO_CMD_UPD1_SOFT_REORDER_EN	BIT(20)
#घोषणा HAL_REO_CMD_UPD1_AC			GENMASK(22, 21)
#घोषणा HAL_REO_CMD_UPD1_BAR			BIT(23)
#घोषणा HAL_REO_CMD_UPD1_RETRY			BIT(24)
#घोषणा HAL_REO_CMD_UPD1_CHECK_2K_MODE		BIT(25)
#घोषणा HAL_REO_CMD_UPD1_OOR_MODE		BIT(26)
#घोषणा HAL_REO_CMD_UPD1_PN_CHECK		BIT(27)
#घोषणा HAL_REO_CMD_UPD1_EVEN_PN		BIT(28)
#घोषणा HAL_REO_CMD_UPD1_UNEVEN_PN		BIT(29)
#घोषणा HAL_REO_CMD_UPD1_PN_HANDLE_ENABLE	BIT(30)
#घोषणा HAL_REO_CMD_UPD1_IGNORE_AMPDU_FLG	BIT(31)

/* Should be matching with HAL_REO_UPD_RX_QUEUE_INFO2_* feilds */
#घोषणा HAL_REO_CMD_UPD2_SVLD			BIT(10)
#घोषणा HAL_REO_CMD_UPD2_SSN			GENMASK(22, 11)
#घोषणा HAL_REO_CMD_UPD2_SEQ_2K_ERR		BIT(23)
#घोषणा HAL_REO_CMD_UPD2_PN_ERR			BIT(24)

#घोषणा HAL_REO_DEST_RING_CTRL_HASH_RING_MAP	GENMASK(31, 8)

काष्ठा ath11k_hal_reo_cmd अणु
	u32 addr_lo;
	u32 flag;
	u32 upd0;
	u32 upd1;
	u32 upd2;
	u32 pn[4];
	u16 rx_queue_num;
	u16 min_rel;
	u16 min_fwd;
	u8 addr_hi;
	u8 ac_list;
	u8 blocking_idx;
	u16 ba_winकरोw_size;
	u8 pn_size;
पूर्ण;

क्रमागत hal_pn_type अणु
	HAL_PN_TYPE_NONE,
	HAL_PN_TYPE_WPA,
	HAL_PN_TYPE_WAPI_EVEN,
	HAL_PN_TYPE_WAPI_UNEVEN,
पूर्ण;

क्रमागत hal_ce_desc अणु
	HAL_CE_DESC_SRC,
	HAL_CE_DESC_DST,
	HAL_CE_DESC_DST_STATUS,
पूर्ण;

#घोषणा HAL_HASH_ROUTING_RING_TCL 0
#घोषणा HAL_HASH_ROUTING_RING_SW1 1
#घोषणा HAL_HASH_ROUTING_RING_SW2 2
#घोषणा HAL_HASH_ROUTING_RING_SW3 3
#घोषणा HAL_HASH_ROUTING_RING_SW4 4
#घोषणा HAL_HASH_ROUTING_RING_REL 5
#घोषणा HAL_HASH_ROUTING_RING_FW  6

काष्ठा hal_reo_status_header अणु
	u16 cmd_num;
	क्रमागत hal_reo_cmd_status cmd_status;
	u16 cmd_exe_समय;
	u32 बारtamp;
पूर्ण;

काष्ठा hal_reo_status_queue_stats अणु
	u16 ssn;
	u16 curr_idx;
	u32 pn[4];
	u32 last_rx_queue_ts;
	u32 last_rx_dequeue_ts;
	u32 rx_biपंचांगap[8]; /* Biपंचांगap from 0-255 */
	u32 curr_mpdu_cnt;
	u32 curr_msdu_cnt;
	u16 fwd_due_to_bar_cnt;
	u16 dup_cnt;
	u32 frames_in_order_cnt;
	u32 num_mpdu_processed_cnt;
	u32 num_msdu_processed_cnt;
	u32 total_num_processed_byte_cnt;
	u32 late_rx_mpdu_cnt;
	u32 reorder_hole_cnt;
	u8 समयout_cnt;
	u8 bar_rx_cnt;
	u8 num_winकरोw_2k_jump_cnt;
पूर्ण;

काष्ठा hal_reo_status_flush_queue अणु
	bool err_detected;
पूर्ण;

क्रमागत hal_reo_status_flush_cache_err_code अणु
	HAL_REO_STATUS_FLUSH_CACHE_ERR_CODE_SUCCESS,
	HAL_REO_STATUS_FLUSH_CACHE_ERR_CODE_IN_USE,
	HAL_REO_STATUS_FLUSH_CACHE_ERR_CODE_NOT_FOUND,
पूर्ण;

काष्ठा hal_reo_status_flush_cache अणु
	bool err_detected;
	क्रमागत hal_reo_status_flush_cache_err_code err_code;
	bool cache_controller_flush_status_hit;
	u8 cache_controller_flush_status_desc_type;
	u8 cache_controller_flush_status_client_id;
	u8 cache_controller_flush_status_err;
	u8 cache_controller_flush_status_cnt;
पूर्ण;

क्रमागत hal_reo_status_unblock_cache_type अणु
	HAL_REO_STATUS_UNBLOCK_BLOCKING_RESOURCE,
	HAL_REO_STATUS_UNBLOCK_ENTIRE_CACHE_USAGE,
पूर्ण;

काष्ठा hal_reo_status_unblock_cache अणु
	bool err_detected;
	क्रमागत hal_reo_status_unblock_cache_type unblock_type;
पूर्ण;

काष्ठा hal_reo_status_flush_समयout_list अणु
	bool err_detected;
	bool list_empty;
	u16 release_desc_cnt;
	u16 fwd_buf_cnt;
पूर्ण;

क्रमागत hal_reo_threshold_idx अणु
	HAL_REO_THRESHOLD_IDX_DESC_COUNTER0,
	HAL_REO_THRESHOLD_IDX_DESC_COUNTER1,
	HAL_REO_THRESHOLD_IDX_DESC_COUNTER2,
	HAL_REO_THRESHOLD_IDX_DESC_COUNTER_SUM,
पूर्ण;

काष्ठा hal_reo_status_desc_thresh_reached अणु
	क्रमागत hal_reo_threshold_idx threshold_idx;
	u32 link_desc_counter0;
	u32 link_desc_counter1;
	u32 link_desc_counter2;
	u32 link_desc_counter_sum;
पूर्ण;

काष्ठा hal_reo_status अणु
	काष्ठा hal_reo_status_header unअगरorm_hdr;
	u8 loop_cnt;
	जोड़ अणु
		काष्ठा hal_reo_status_queue_stats queue_stats;
		काष्ठा hal_reo_status_flush_queue flush_queue;
		काष्ठा hal_reo_status_flush_cache flush_cache;
		काष्ठा hal_reo_status_unblock_cache unblock_cache;
		काष्ठा hal_reo_status_flush_समयout_list समयout_list;
		काष्ठा hal_reo_status_desc_thresh_reached desc_thresh_reached;
	पूर्ण u;
पूर्ण;

/**
 * HAL context to be used to access SRNG APIs (currently used by data path
 * and transport (CE) modules)
 */
काष्ठा ath11k_hal अणु
	/* HAL पूर्णांकernal state क्रम all SRNG rings.
	 */
	काष्ठा hal_srng srng_list[HAL_SRNG_RING_ID_MAX];

	/* SRNG configuration table */
	काष्ठा hal_srng_config *srng_config;

	/* Remote poपूर्णांकer memory क्रम HW/FW updates */
	काष्ठा अणु
		u32 *vaddr;
		dma_addr_t paddr;
	पूर्ण rdp;

	/* Shared memory क्रम ring poपूर्णांकer updates from host to FW */
	काष्ठा अणु
		u32 *vaddr;
		dma_addr_t paddr;
	पूर्ण wrp;

	/* Available REO blocking resources biपंचांगap */
	u8 avail_blk_resource;

	u8 current_blk_index;

	/* shaकरोw रेजिस्टर configuration */
	u32 shaकरोw_reg_addr[HAL_SHADOW_NUM_REGS];
	पूर्णांक num_shaकरोw_reg_configured;
पूर्ण;

u32 ath11k_hal_reo_qdesc_size(u32 ba_winकरोw_size, u8 tid);
व्योम ath11k_hal_reo_qdesc_setup(व्योम *vaddr, पूर्णांक tid, u32 ba_winकरोw_size,
				u32 start_seq, क्रमागत hal_pn_type type);
व्योम ath11k_hal_reo_init_cmd_ring(काष्ठा ath11k_base *ab,
				  काष्ठा hal_srng *srng);
व्योम ath11k_hal_reo_hw_setup(काष्ठा ath11k_base *ab, u32 ring_hash_map);
व्योम ath11k_hal_setup_link_idle_list(काष्ठा ath11k_base *ab,
				     काष्ठा hal_wbm_idle_scatter_list *sbuf,
				     u32 nsbufs, u32 tot_link_desc,
				     u32 end_offset);

dma_addr_t ath11k_hal_srng_get_tp_addr(काष्ठा ath11k_base *ab,
				       काष्ठा hal_srng *srng);
dma_addr_t ath11k_hal_srng_get_hp_addr(काष्ठा ath11k_base *ab,
				       काष्ठा hal_srng *srng);
व्योम ath11k_hal_set_link_desc_addr(काष्ठा hal_wbm_link_desc *desc, u32 cookie,
				   dma_addr_t paddr);
u32 ath11k_hal_ce_get_desc_size(क्रमागत hal_ce_desc type);
व्योम ath11k_hal_ce_src_set_desc(व्योम *buf, dma_addr_t paddr, u32 len, u32 id,
				u8 byte_swap_data);
व्योम ath11k_hal_ce_dst_set_desc(व्योम *buf, dma_addr_t paddr);
u32 ath11k_hal_ce_dst_status_get_length(व्योम *buf);
पूर्णांक ath11k_hal_srng_get_entrysize(काष्ठा ath11k_base *ab, u32 ring_type);
पूर्णांक ath11k_hal_srng_get_max_entries(काष्ठा ath11k_base *ab, u32 ring_type);
व्योम ath11k_hal_srng_get_params(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
				काष्ठा hal_srng_params *params);
u32 *ath11k_hal_srng_dst_get_next_entry(काष्ठा ath11k_base *ab,
					काष्ठा hal_srng *srng);
u32 *ath11k_hal_srng_dst_peek(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng);
पूर्णांक ath11k_hal_srng_dst_num_मुक्त(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
				 bool sync_hw_ptr);
u32 *ath11k_hal_srng_src_peek(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng);
u32 *ath11k_hal_srng_src_get_next_reaped(काष्ठा ath11k_base *ab,
					 काष्ठा hal_srng *srng);
u32 *ath11k_hal_srng_src_reap_next(काष्ठा ath11k_base *ab,
				   काष्ठा hal_srng *srng);
u32 *ath11k_hal_srng_src_get_next_entry(काष्ठा ath11k_base *ab,
					काष्ठा hal_srng *srng);
पूर्णांक ath11k_hal_srng_src_num_मुक्त(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
				 bool sync_hw_ptr);
व्योम ath11k_hal_srng_access_begin(काष्ठा ath11k_base *ab,
				  काष्ठा hal_srng *srng);
व्योम ath11k_hal_srng_access_end(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng);
पूर्णांक ath11k_hal_srng_setup(काष्ठा ath11k_base *ab, क्रमागत hal_ring_type type,
			  पूर्णांक ring_num, पूर्णांक mac_id,
			  काष्ठा hal_srng_params *params);
पूर्णांक ath11k_hal_srng_init(काष्ठा ath11k_base *ath11k);
व्योम ath11k_hal_srng_deinit(काष्ठा ath11k_base *ath11k);
व्योम ath11k_hal_dump_srng_stats(काष्ठा ath11k_base *ab);
व्योम ath11k_hal_srng_get_shaकरोw_config(काष्ठा ath11k_base *ab,
				       u32 **cfg, u32 *len);
पूर्णांक ath11k_hal_srng_update_shaकरोw_config(काष्ठा ath11k_base *ab,
					 क्रमागत hal_ring_type ring_type,
					पूर्णांक ring_num);
व्योम ath11k_hal_srng_shaकरोw_config(काष्ठा ath11k_base *ab);
व्योम ath11k_hal_srng_shaकरोw_update_hp_tp(काष्ठा ath11k_base *ab,
					 काष्ठा hal_srng *srng);
#पूर्ण_अगर
