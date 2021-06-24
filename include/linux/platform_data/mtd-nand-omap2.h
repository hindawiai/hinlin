<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2006 Micron Technology Inc.
 */

#अगर_अघोषित	_MTD_न_अंकD_OMAP2_H
#घोषणा	_MTD_न_अंकD_OMAP2_H

#समावेश <linux/mtd/partitions.h>

#घोषणा	GPMC_BCH_NUM_REMAINDER	8

क्रमागत nand_io अणु
	न_अंकD_OMAP_PREFETCH_POLLED = 0,	/* prefetch polled mode, शेष */
	न_अंकD_OMAP_POLLED,		/* polled mode, without prefetch */
	न_अंकD_OMAP_PREFETCH_DMA,		/* prefetch enabled sDMA mode */
	न_अंकD_OMAP_PREFETCH_IRQ		/* prefetch enabled irq mode */
पूर्ण;

क्रमागत omap_ecc अणु
	/*
	 * 1-bit ECC: calculation and correction by SW
	 * ECC stored at end of spare area
	 */
	OMAP_ECC_HAM1_CODE_SW = 0,

	/*
	 * 1-bit ECC: calculation by GPMC, Error detection by Software
	 * ECC layout compatible with ROM code layout
	 */
	OMAP_ECC_HAM1_CODE_HW,
	/* 4-bit  ECC calculation by GPMC, Error detection by Software */
	OMAP_ECC_BCH4_CODE_HW_DETECTION_SW,
	/* 4-bit  ECC calculation by GPMC, Error detection by ELM */
	OMAP_ECC_BCH4_CODE_HW,
	/* 8-bit  ECC calculation by GPMC, Error detection by Software */
	OMAP_ECC_BCH8_CODE_HW_DETECTION_SW,
	/* 8-bit  ECC calculation by GPMC, Error detection by ELM */
	OMAP_ECC_BCH8_CODE_HW,
	/* 16-bit ECC calculation by GPMC, Error detection by ELM */
	OMAP_ECC_BCH16_CODE_HW,
पूर्ण;

काष्ठा gpmc_nand_regs अणु
	व्योम __iomem	*gpmc_nand_command;
	व्योम __iomem	*gpmc_nand_address;
	व्योम __iomem	*gpmc_nand_data;
	व्योम __iomem	*gpmc_prefetch_config1;
	व्योम __iomem	*gpmc_prefetch_config2;
	व्योम __iomem	*gpmc_prefetch_control;
	व्योम __iomem	*gpmc_prefetch_status;
	व्योम __iomem	*gpmc_ecc_config;
	व्योम __iomem	*gpmc_ecc_control;
	व्योम __iomem	*gpmc_ecc_size_config;
	व्योम __iomem	*gpmc_ecc1_result;
	व्योम __iomem	*gpmc_bch_result0[GPMC_BCH_NUM_REMAINDER];
	व्योम __iomem	*gpmc_bch_result1[GPMC_BCH_NUM_REMAINDER];
	व्योम __iomem	*gpmc_bch_result2[GPMC_BCH_NUM_REMAINDER];
	व्योम __iomem	*gpmc_bch_result3[GPMC_BCH_NUM_REMAINDER];
	व्योम __iomem	*gpmc_bch_result4[GPMC_BCH_NUM_REMAINDER];
	व्योम __iomem	*gpmc_bch_result5[GPMC_BCH_NUM_REMAINDER];
	व्योम __iomem	*gpmc_bch_result6[GPMC_BCH_NUM_REMAINDER];
पूर्ण;
#पूर्ण_अगर
