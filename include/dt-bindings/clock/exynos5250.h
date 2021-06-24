<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Author: Andrzej Hajda <a.hajda@samsung.com>
 *
 * Device Tree binding स्थिरants क्रम Exynos5250 घड़ी controller.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_EXYNOS_5250_H
#घोषणा _DT_BINDINGS_CLOCK_EXYNOS_5250_H

/* core घड़ीs */
#घोषणा CLK_FIN_PLL		1
#घोषणा CLK_FOUT_APLL		2
#घोषणा CLK_FOUT_MPLL		3
#घोषणा CLK_FOUT_BPLL		4
#घोषणा CLK_FOUT_GPLL		5
#घोषणा CLK_FOUT_CPLL		6
#घोषणा CLK_FOUT_EPLL		7
#घोषणा CLK_FOUT_VPLL		8
#घोषणा CLK_ARM_CLK		9

/* gate क्रम special घड़ीs (sclk) */
#घोषणा CLK_SCLK_CAM_BAYER	128
#घोषणा CLK_SCLK_CAM0		129
#घोषणा CLK_SCLK_CAM1		130
#घोषणा CLK_SCLK_GSCL_WA	131
#घोषणा CLK_SCLK_GSCL_WB	132
#घोषणा CLK_SCLK_FIMD1		133
#घोषणा CLK_SCLK_MIPI1		134
#घोषणा CLK_SCLK_DP		135
#घोषणा CLK_SCLK_HDMI		136
#घोषणा CLK_SCLK_PIXEL		137
#घोषणा CLK_SCLK_AUDIO0		138
#घोषणा CLK_SCLK_MMC0		139
#घोषणा CLK_SCLK_MMC1		140
#घोषणा CLK_SCLK_MMC2		141
#घोषणा CLK_SCLK_MMC3		142
#घोषणा CLK_SCLK_SATA		143
#घोषणा CLK_SCLK_USB3		144
#घोषणा CLK_SCLK_JPEG		145
#घोषणा CLK_SCLK_UART0		146
#घोषणा CLK_SCLK_UART1		147
#घोषणा CLK_SCLK_UART2		148
#घोषणा CLK_SCLK_UART3		149
#घोषणा CLK_SCLK_PWM		150
#घोषणा CLK_SCLK_AUDIO1		151
#घोषणा CLK_SCLK_AUDIO2		152
#घोषणा CLK_SCLK_SPDIF		153
#घोषणा CLK_SCLK_SPI0		154
#घोषणा CLK_SCLK_SPI1		155
#घोषणा CLK_SCLK_SPI2		156
#घोषणा CLK_DIV_I2S1		157
#घोषणा CLK_DIV_I2S2		158
#घोषणा CLK_SCLK_HDMIPHY	159
#घोषणा CLK_DIV_PCM0		160

/* gate घड़ीs */
#घोषणा CLK_GSCL0		256
#घोषणा CLK_GSCL1		257
#घोषणा CLK_GSCL2		258
#घोषणा CLK_GSCL3		259
#घोषणा CLK_GSCL_WA		260
#घोषणा CLK_GSCL_WB		261
#घोषणा CLK_SMMU_GSCL0		262
#घोषणा CLK_SMMU_GSCL1		263
#घोषणा CLK_SMMU_GSCL2		264
#घोषणा CLK_SMMU_GSCL3		265
#घोषणा CLK_MFC			266
#घोषणा CLK_SMMU_MFCL		267
#घोषणा CLK_SMMU_MFCR		268
#घोषणा CLK_ROTATOR		269
#घोषणा CLK_JPEG		270
#घोषणा CLK_MDMA1		271
#घोषणा CLK_SMMU_ROTATOR	272
#घोषणा CLK_SMMU_JPEG		273
#घोषणा CLK_SMMU_MDMA1		274
#घोषणा CLK_PDMA0		275
#घोषणा CLK_PDMA1		276
#घोषणा CLK_SATA		277
#घोषणा CLK_USBOTG		278
#घोषणा CLK_MIPI_HSI		279
#घोषणा CLK_SDMMC0		280
#घोषणा CLK_SDMMC1		281
#घोषणा CLK_SDMMC2		282
#घोषणा CLK_SDMMC3		283
#घोषणा CLK_SROMC		284
#घोषणा CLK_USB2		285
#घोषणा CLK_USB3		286
#घोषणा CLK_SATA_PHYCTRL	287
#घोषणा CLK_SATA_PHYI2C		288
#घोषणा CLK_UART0		289
#घोषणा CLK_UART1		290
#घोषणा CLK_UART2		291
#घोषणा CLK_UART3		292
#घोषणा CLK_UART4		293
#घोषणा CLK_I2C0		294
#घोषणा CLK_I2C1		295
#घोषणा CLK_I2C2		296
#घोषणा CLK_I2C3		297
#घोषणा CLK_I2C4		298
#घोषणा CLK_I2C5		299
#घोषणा CLK_I2C6		300
#घोषणा CLK_I2C7		301
#घोषणा CLK_I2C_HDMI		302
#घोषणा CLK_ADC			303
#घोषणा CLK_SPI0		304
#घोषणा CLK_SPI1		305
#घोषणा CLK_SPI2		306
#घोषणा CLK_I2S1		307
#घोषणा CLK_I2S2		308
#घोषणा CLK_PCM1		309
#घोषणा CLK_PCM2		310
#घोषणा CLK_PWM			311
#घोषणा CLK_SPDIF		312
#घोषणा CLK_AC97		313
#घोषणा CLK_HSI2C0		314
#घोषणा CLK_HSI2C1		315
#घोषणा CLK_HSI2C2		316
#घोषणा CLK_HSI2C3		317
#घोषणा CLK_CHIPID		318
#घोषणा CLK_SYSREG		319
#घोषणा CLK_PMU			320
#घोषणा CLK_CMU_TOP		321
#घोषणा CLK_CMU_CORE		322
#घोषणा CLK_CMU_MEM		323
#घोषणा CLK_TZPC0		324
#घोषणा CLK_TZPC1		325
#घोषणा CLK_TZPC2		326
#घोषणा CLK_TZPC3		327
#घोषणा CLK_TZPC4		328
#घोषणा CLK_TZPC5		329
#घोषणा CLK_TZPC6		330
#घोषणा CLK_TZPC7		331
#घोषणा CLK_TZPC8		332
#घोषणा CLK_TZPC9		333
#घोषणा CLK_HDMI_CEC		334
#घोषणा CLK_MCT			335
#घोषणा CLK_WDT			336
#घोषणा CLK_RTC			337
#घोषणा CLK_TMU			338
#घोषणा CLK_FIMD1		339
#घोषणा CLK_MIE1		340
#घोषणा CLK_DSIM0		341
#घोषणा CLK_DP			342
#घोषणा CLK_MIXER		343
#घोषणा CLK_HDMI		344
#घोषणा CLK_G2D			345
#घोषणा CLK_MDMA0		346
#घोषणा CLK_SMMU_MDMA0		347
#घोषणा CLK_SSS			348
#घोषणा CLK_G3D			349
#घोषणा CLK_SMMU_TV		350
#घोषणा CLK_SMMU_FIMD1		351
#घोषणा CLK_SMMU_2D		352
#घोषणा CLK_SMMU_FIMC_ISP	353
#घोषणा CLK_SMMU_FIMC_DRC	354
#घोषणा CLK_SMMU_FIMC_SCC	355
#घोषणा CLK_SMMU_FIMC_SCP	356
#घोषणा CLK_SMMU_FIMC_FD	357
#घोषणा CLK_SMMU_FIMC_MCU	358
#घोषणा CLK_SMMU_FIMC_ODC	359
#घोषणा CLK_SMMU_FIMC_DIS0	360
#घोषणा CLK_SMMU_FIMC_DIS1	361
#घोषणा CLK_SMMU_FIMC_3DNR	362
#घोषणा CLK_SMMU_FIMC_LITE0	363
#घोषणा CLK_SMMU_FIMC_LITE1	364
#घोषणा CLK_CAMIF_TOP		365

/* mux घड़ीs */
#घोषणा CLK_MOUT_HDMI		1024
#घोषणा CLK_MOUT_GPLL		1025
#घोषणा CLK_MOUT_ACLK200_DISP1_SUB	1026
#घोषणा CLK_MOUT_ACLK300_DISP1_SUB	1027
#घोषणा CLK_MOUT_APLL		1028
#घोषणा CLK_MOUT_MPLL		1029

/* must be greater than maximal घड़ी id */
#घोषणा CLK_NR_CLKS		1030

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_EXYNOS_5250_H */
