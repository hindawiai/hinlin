<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt2701-reg.h  --  Mediatek 2701 audio driver reg definition
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 */

#अगर_अघोषित _MT2701_REG_H_
#घोषणा _MT2701_REG_H_

#घोषणा AUDIO_TOP_CON0 0x0000
#घोषणा AUDIO_TOP_CON4 0x0010
#घोषणा AUDIO_TOP_CON5 0x0014
#घोषणा AFE_DAIBT_CON0 0x001c
#घोषणा AFE_MRGIF_CON 0x003c
#घोषणा ASMI_TIMING_CON1 0x0100
#घोषणा ASMO_TIMING_CON1 0x0104
#घोषणा PWR1_ASM_CON1 0x0108
#घोषणा ASYS_TOP_CON 0x0600
#घोषणा ASYS_I2SIN1_CON 0x0604
#घोषणा ASYS_I2SIN2_CON 0x0608
#घोषणा ASYS_I2SIN3_CON 0x060c
#घोषणा ASYS_I2SIN4_CON 0x0610
#घोषणा ASYS_I2SIN5_CON 0x0614
#घोषणा ASYS_I2SO1_CON 0x061C
#घोषणा ASYS_I2SO2_CON 0x0620
#घोषणा ASYS_I2SO3_CON 0x0624
#घोषणा ASYS_I2SO4_CON 0x0628
#घोषणा ASYS_I2SO5_CON 0x062c
#घोषणा PWR2_TOP_CON 0x0634
#घोषणा AFE_CONN0 0x06c0
#घोषणा AFE_CONN1 0x06c4
#घोषणा AFE_CONN2 0x06c8
#घोषणा AFE_CONN3 0x06cc
#घोषणा AFE_CONN14 0x06f8
#घोषणा AFE_CONN15 0x06fc
#घोषणा AFE_CONN16 0x0700
#घोषणा AFE_CONN17 0x0704
#घोषणा AFE_CONN18 0x0708
#घोषणा AFE_CONN19 0x070c
#घोषणा AFE_CONN20 0x0710
#घोषणा AFE_CONN21 0x0714
#घोषणा AFE_CONN22 0x0718
#घोषणा AFE_CONN23 0x071c
#घोषणा AFE_CONN24 0x0720
#घोषणा AFE_CONN41 0x0764
#घोषणा ASYS_IRQ1_CON 0x0780
#घोषणा ASYS_IRQ2_CON 0x0784
#घोषणा ASYS_IRQ3_CON 0x0788
#घोषणा ASYS_IRQ_CLR 0x07c0
#घोषणा ASYS_IRQ_STATUS 0x07c4
#घोषणा PWR2_ASM_CON1 0x1070
#घोषणा AFE_DAC_CON0 0x1200
#घोषणा AFE_DAC_CON1 0x1204
#घोषणा AFE_DAC_CON2 0x1208
#घोषणा AFE_DAC_CON3 0x120c
#घोषणा AFE_DAC_CON4 0x1210
#घोषणा AFE_MEMIF_HD_CON1 0x121c
#घोषणा AFE_MEMIF_PBUF_SIZE 0x1238
#घोषणा AFE_MEMIF_HD_CON0 0x123c
#घोषणा AFE_DL1_BASE 0x1240
#घोषणा AFE_DL1_CUR 0x1244
#घोषणा AFE_DL2_BASE 0x1250
#घोषणा AFE_DL2_CUR 0x1254
#घोषणा AFE_DL3_BASE 0x1260
#घोषणा AFE_DL3_CUR 0x1264
#घोषणा AFE_DL4_BASE 0x1270
#घोषणा AFE_DL4_CUR 0x1274
#घोषणा AFE_DL5_BASE 0x1280
#घोषणा AFE_DL5_CUR 0x1284
#घोषणा AFE_DLMCH_BASE 0x12a0
#घोषणा AFE_DLMCH_CUR 0x12a4
#घोषणा AFE_ARB1_BASE 0x12b0
#घोषणा AFE_ARB1_CUR 0x12b4
#घोषणा AFE_VUL_BASE 0x1300
#घोषणा AFE_VUL_CUR 0x130c
#घोषणा AFE_UL2_BASE 0x1310
#घोषणा AFE_UL2_END 0x1318
#घोषणा AFE_UL2_CUR 0x131c
#घोषणा AFE_UL3_BASE 0x1320
#घोषणा AFE_UL3_END 0x1328
#घोषणा AFE_UL3_CUR 0x132c
#घोषणा AFE_UL4_BASE 0x1330
#घोषणा AFE_UL4_END 0x1338
#घोषणा AFE_UL4_CUR 0x133c
#घोषणा AFE_UL5_BASE 0x1340
#घोषणा AFE_UL5_END 0x1348
#घोषणा AFE_UL5_CUR 0x134c
#घोषणा AFE_DAI_BASE 0x1370
#घोषणा AFE_DAI_CUR 0x137c

/* AFE_DAIBT_CON0 (0x001c) */
#घोषणा AFE_DAIBT_CON0_DAIBT_EN		(0x1 << 0)
#घोषणा AFE_DAIBT_CON0_BT_FUNC_EN	(0x1 << 1)
#घोषणा AFE_DAIBT_CON0_BT_FUNC_RDY	(0x1 << 3)
#घोषणा AFE_DAIBT_CON0_BT_WIDE_MODE_EN	(0x1 << 9)
#घोषणा AFE_DAIBT_CON0_MRG_USE		(0x1 << 12)

/* PWR1_ASM_CON1 (0x0108) */
#घोषणा PWR1_ASM_CON1_INIT_VAL		(0x492)

/* AFE_MRGIF_CON (0x003c) */
#घोषणा AFE_MRGIF_CON_MRG_EN		(0x1 << 0)
#घोषणा AFE_MRGIF_CON_MRG_I2S_EN	(0x1 << 16)
#घोषणा AFE_MRGIF_CON_I2S_MODE_MASK	(0xf << 20)
#घोषणा AFE_MRGIF_CON_I2S_MODE_32K	(0x4 << 20)

/* ASYS_TOP_CON (0x0600) */
#घोषणा ASYS_TOP_CON_ASYS_TIMING_ON		(0x3 << 0)

/* PWR2_ASM_CON1 (0x1070) */
#घोषणा PWR2_ASM_CON1_INIT_VAL		(0x492492)

/* AFE_DAC_CON0 (0x1200) */
#घोषणा AFE_DAC_CON0_AFE_ON		(0x1 << 0)

/* AFE_MEMIF_PBUF_SIZE (0x1238) */
#घोषणा AFE_MEMIF_PBUF_SIZE_DLM_MASK		(0x1 << 29)
#घोषणा AFE_MEMIF_PBUF_SIZE_PAIR_INTERLEAVE	(0x0 << 29)
#घोषणा AFE_MEMIF_PBUF_SIZE_FULL_INTERLEAVE	(0x1 << 29)
#घोषणा DLMCH_BIT_WIDTH_MASK			(0x1 << 28)
#घोषणा AFE_MEMIF_PBUF_SIZE_DLM_CH_MASK		(0xf << 24)
#घोषणा AFE_MEMIF_PBUF_SIZE_DLM_CH(x)		((x) << 24)
#घोषणा AFE_MEMIF_PBUF_SIZE_DLM_BYTE_MASK	(0x3 << 12)
#घोषणा AFE_MEMIF_PBUF_SIZE_DLM_32BYTES		(0x1 << 12)

/* I2S in/out रेजिस्टर bit control */
#घोषणा ASYS_I2S_CON_FS			(0x1f << 8)
#घोषणा ASYS_I2S_CON_FS_SET(x)		((x) << 8)
#घोषणा ASYS_I2S_CON_RESET		(0x1 << 30)
#घोषणा ASYS_I2S_CON_I2S_EN		(0x1 << 0)
#घोषणा ASYS_I2S_CON_ONE_HEART_MODE	(0x1 << 16)
#घोषणा ASYS_I2S_CON_I2S_COUPLE_MODE	(0x1 << 17)
/* 0:EIAJ 1:I2S */
#घोषणा ASYS_I2S_CON_I2S_MODE		(0x1 << 3)
#घोषणा ASYS_I2S_CON_WIDE_MODE		(0x1 << 1)
#घोषणा ASYS_I2S_CON_WIDE_MODE_SET(x)	((x) << 1)
#घोषणा ASYS_I2S_IN_PHASE_FIX		(0x1 << 31)

#पूर्ण_अगर
