<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * aQuantia Corporation Network Driver
 * Copyright (C) 2014-2019 aQuantia Corporation. All rights reserved
 */

/* File aq_cfg.h: Definition of configuration parameters and स्थिरants. */

#अगर_अघोषित AQ_CFG_H
#घोषणा AQ_CFG_H

#घोषणा AQ_CFG_VECS_DEF   8U
#घोषणा AQ_CFG_TCS_DEF    1U

#घोषणा AQ_CFG_TXDS_DEF    4096U
#घोषणा AQ_CFG_RXDS_DEF    2048U

#घोषणा AQ_CFG_IS_POLLING_DEF 0U

#घोषणा AQ_CFG_FORCE_LEGACY_INT 0U

#घोषणा AQ_CFG_INTERRUPT_MODERATION_OFF		0
#घोषणा AQ_CFG_INTERRUPT_MODERATION_ON		1
#घोषणा AQ_CFG_INTERRUPT_MODERATION_AUTO	0xFFFFU

#घोषणा AQ_CFG_INTERRUPT_MODERATION_USEC_MAX (0x1FF * 2)

#घोषणा AQ_CFG_IRQ_MASK                      0x3FFU

#घोषणा AQ_CFG_VECS_MAX   8U
#घोषणा AQ_CFG_TCS_MAX    8U

#घोषणा AQ_CFG_TX_FRAME_MAX  (16U * 1024U)
#घोषणा AQ_CFG_RX_FRAME_MAX  (2U * 1024U)

#घोषणा AQ_CFG_TX_CLEAN_BUDGET 256U

#घोषणा AQ_CFG_RX_REFILL_THRES 32U

#घोषणा AQ_CFG_RX_HDR_SIZE 256U

#घोषणा AQ_CFG_RX_PAGEORDER 0U

/* LRO */
#घोषणा AQ_CFG_IS_LRO_DEF           1U

/* RSS */
#घोषणा AQ_CFG_RSS_INसूचीECTION_TABLE_MAX  64U
#घोषणा AQ_CFG_RSS_HASHKEY_SIZE           40U

#घोषणा AQ_CFG_IS_RSS_DEF           1U
#घोषणा AQ_CFG_NUM_RSS_QUEUES_DEF   AQ_CFG_VECS_DEF
#घोषणा AQ_CFG_RSS_BASE_CPU_NUM_DEF 0U

#घोषणा AQ_CFG_PCI_FUNC_MSIX_IRQS   9U
#घोषणा AQ_CFG_PCI_FUNC_PORTS       2U

#घोषणा AQ_CFG_SERVICE_TIMER_INTERVAL    (1 * HZ)
#घोषणा AQ_CFG_POLLING_TIMER_INTERVAL   ((अचिन्हित पूर्णांक)(2 * HZ))

#घोषणा AQ_CFG_SKB_FRAGS_MAX   32U

/* Number of descriptors available in one ring to resume this ring queue
 */
#घोषणा AQ_CFG_RESTART_DESC_THRES   (AQ_CFG_SKB_FRAGS_MAX * 2)

#घोषणा AQ_CFG_NAPI_WEIGHT     64U

/*#घोषणा AQ_CFG_MAC_ADDR_PERMANENT अणु0x30, 0x0E, 0xE3, 0x12, 0x34, 0x56पूर्ण*/

#घोषणा AQ_CFG_FC_MODE AQ_NIC_FC_FULL

/* Default WOL modes used on initialization */
#घोषणा AQ_CFG_WOL_MODES WAKE_MAGIC

#घोषणा AQ_CFG_SPEED_MSK  0xFFFFU	/* 0xFFFFU==स्वतः_neg */

#घोषणा AQ_CFG_IS_AUTONEG_DEF       1U
#घोषणा AQ_CFG_MTU_DEF              1514U

#घोषणा AQ_CFG_LOCK_TRYS   100U

#घोषणा AQ_CFG_DRV_AUTHOR      "Marvell"
#घोषणा AQ_CFG_DRV_DESC        "Marvell (Aquantia) Corporation(R) Network Driver"
#घोषणा AQ_CFG_DRV_NAME        "atlantic"

#पूर्ण_अगर /* AQ_CFG_H */
