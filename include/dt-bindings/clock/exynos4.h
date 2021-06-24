<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Author: Andrzej Hajda <a.hajda@samsung.com>
 *
 * Device Tree binding स्थिरants क्रम Exynos4 घड़ी controller.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_EXYNOS_4_H
#घोषणा _DT_BINDINGS_CLOCK_EXYNOS_4_H

/* core घड़ीs */
#घोषणा CLK_XXTI		1
#घोषणा CLK_XUSBXTI		2
#घोषणा CLK_FIN_PLL		3
#घोषणा CLK_FOUT_APLL		4
#घोषणा CLK_FOUT_MPLL		5
#घोषणा CLK_FOUT_EPLL		6
#घोषणा CLK_FOUT_VPLL		7
#घोषणा CLK_SCLK_APLL		8
#घोषणा CLK_SCLK_MPLL		9
#घोषणा CLK_SCLK_EPLL		10
#घोषणा CLK_SCLK_VPLL		11
#घोषणा CLK_ARM_CLK		12
#घोषणा CLK_ACLK200		13
#घोषणा CLK_ACLK100		14
#घोषणा CLK_ACLK160		15
#घोषणा CLK_ACLK133		16
#घोषणा CLK_MOUT_MPLL_USER_T	17 /* Exynos4x12 only */
#घोषणा CLK_MOUT_MPLL_USER_C	18 /* Exynos4x12 only */
#घोषणा CLK_MOUT_CORE		19
#घोषणा CLK_MOUT_APLL		20
#घोषणा CLK_SCLK_HDMIPHY	22
#घोषणा CLK_OUT_DMC		23
#घोषणा CLK_OUT_TOP		24
#घोषणा CLK_OUT_LEFTBUS		25
#घोषणा CLK_OUT_RIGHTBUS	26
#घोषणा CLK_OUT_CPU		27

/* gate क्रम special घड़ीs (sclk) */
#घोषणा CLK_SCLK_FIMC0		128
#घोषणा CLK_SCLK_FIMC1		129
#घोषणा CLK_SCLK_FIMC2		130
#घोषणा CLK_SCLK_FIMC3		131
#घोषणा CLK_SCLK_CAM0		132
#घोषणा CLK_SCLK_CAM1		133
#घोषणा CLK_SCLK_CSIS0		134
#घोषणा CLK_SCLK_CSIS1		135
#घोषणा CLK_SCLK_HDMI		136
#घोषणा CLK_SCLK_MIXER		137
#घोषणा CLK_SCLK_DAC		138
#घोषणा CLK_SCLK_PIXEL		139
#घोषणा CLK_SCLK_FIMD0		140
#घोषणा CLK_SCLK_MDNIE0		141 /* Exynos4412 only */
#घोषणा CLK_SCLK_MDNIE_PWM0	142
#घोषणा CLK_SCLK_MIPI0		143
#घोषणा CLK_SCLK_AUDIO0		144
#घोषणा CLK_SCLK_MMC0		145
#घोषणा CLK_SCLK_MMC1		146
#घोषणा CLK_SCLK_MMC2		147
#घोषणा CLK_SCLK_MMC3		148
#घोषणा CLK_SCLK_MMC4		149
#घोषणा CLK_SCLK_SATA		150 /* Exynos4210 only */
#घोषणा CLK_SCLK_UART0		151
#घोषणा CLK_SCLK_UART1		152
#घोषणा CLK_SCLK_UART2		153
#घोषणा CLK_SCLK_UART3		154
#घोषणा CLK_SCLK_UART4		155
#घोषणा CLK_SCLK_AUDIO1		156
#घोषणा CLK_SCLK_AUDIO2		157
#घोषणा CLK_SCLK_SPDIF		158
#घोषणा CLK_SCLK_SPI0		159
#घोषणा CLK_SCLK_SPI1		160
#घोषणा CLK_SCLK_SPI2		161
#घोषणा CLK_SCLK_SLIMBUS	162
#घोषणा CLK_SCLK_FIMD1		163 /* Exynos4210 only */
#घोषणा CLK_SCLK_MIPI1		164 /* Exynos4210 only */
#घोषणा CLK_SCLK_PCM1		165
#घोषणा CLK_SCLK_PCM2		166
#घोषणा CLK_SCLK_I2S1		167
#घोषणा CLK_SCLK_I2S2		168
#घोषणा CLK_SCLK_MIPIHSI	169 /* Exynos4412 only */
#घोषणा CLK_SCLK_MFC		170
#घोषणा CLK_SCLK_PCM0		171
#घोषणा CLK_SCLK_G3D		172
#घोषणा CLK_SCLK_PWM_ISP	173 /* Exynos4x12 only */
#घोषणा CLK_SCLK_SPI0_ISP	174 /* Exynos4x12 only */
#घोषणा CLK_SCLK_SPI1_ISP	175 /* Exynos4x12 only */
#घोषणा CLK_SCLK_UART_ISP	176 /* Exynos4x12 only */
#घोषणा CLK_SCLK_FIMG2D		177

/* gate घड़ीs */
#घोषणा CLK_SSS			255
#घोषणा CLK_FIMC0		256
#घोषणा CLK_FIMC1		257
#घोषणा CLK_FIMC2		258
#घोषणा CLK_FIMC3		259
#घोषणा CLK_CSIS0		260
#घोषणा CLK_CSIS1		261
#घोषणा CLK_JPEG		262
#घोषणा CLK_SMMU_FIMC0		263
#घोषणा CLK_SMMU_FIMC1		264
#घोषणा CLK_SMMU_FIMC2		265
#घोषणा CLK_SMMU_FIMC3		266
#घोषणा CLK_SMMU_JPEG		267
#घोषणा CLK_VP			268
#घोषणा CLK_MIXER		269
#घोषणा CLK_TVENC		270 /* Exynos4210 only */
#घोषणा CLK_HDMI		271
#घोषणा CLK_SMMU_TV		272
#घोषणा CLK_MFC			273
#घोषणा CLK_SMMU_MFCL		274
#घोषणा CLK_SMMU_MFCR		275
#घोषणा CLK_G3D			276
#घोषणा CLK_G2D			277
#घोषणा CLK_ROTATOR		278
#घोषणा CLK_MDMA		279
#घोषणा CLK_SMMU_G2D		280
#घोषणा CLK_SMMU_ROTATOR	281
#घोषणा CLK_SMMU_MDMA		282
#घोषणा CLK_FIMD0		283
#घोषणा CLK_MIE0		284
#घोषणा CLK_MDNIE0		285 /* Exynos4412 only */
#घोषणा CLK_DSIM0		286
#घोषणा CLK_SMMU_FIMD0		287
#घोषणा CLK_FIMD1		288 /* Exynos4210 only */
#घोषणा CLK_MIE1		289 /* Exynos4210 only */
#घोषणा CLK_DSIM1		290 /* Exynos4210 only */
#घोषणा CLK_SMMU_FIMD1		291 /* Exynos4210 only */
#घोषणा CLK_PDMA0		292
#घोषणा CLK_PDMA1		293
#घोषणा CLK_PCIE_PHY		294
#घोषणा CLK_SATA_PHY		295 /* Exynos4210 only */
#घोषणा CLK_TSI			296
#घोषणा CLK_SDMMC0		297
#घोषणा CLK_SDMMC1		298
#घोषणा CLK_SDMMC2		299
#घोषणा CLK_SDMMC3		300
#घोषणा CLK_SDMMC4		301
#घोषणा CLK_SATA		302 /* Exynos4210 only */
#घोषणा CLK_SROMC		303
#घोषणा CLK_USB_HOST		304
#घोषणा CLK_USB_DEVICE		305
#घोषणा CLK_PCIE		306
#घोषणा CLK_ONEन_अंकD		307
#घोषणा CLK_NFCON		308
#घोषणा CLK_SMMU_PCIE		309
#घोषणा CLK_GPS			310
#घोषणा CLK_SMMU_GPS		311
#घोषणा CLK_UART0		312
#घोषणा CLK_UART1		313
#घोषणा CLK_UART2		314
#घोषणा CLK_UART3		315
#घोषणा CLK_UART4		316
#घोषणा CLK_I2C0		317
#घोषणा CLK_I2C1		318
#घोषणा CLK_I2C2		319
#घोषणा CLK_I2C3		320
#घोषणा CLK_I2C4		321
#घोषणा CLK_I2C5		322
#घोषणा CLK_I2C6		323
#घोषणा CLK_I2C7		324
#घोषणा CLK_I2C_HDMI		325
#घोषणा CLK_TSADC		326
#घोषणा CLK_SPI0		327
#घोषणा CLK_SPI1		328
#घोषणा CLK_SPI2		329
#घोषणा CLK_I2S1		330
#घोषणा CLK_I2S2		331
#घोषणा CLK_PCM0		332
#घोषणा CLK_I2S0		333
#घोषणा CLK_PCM1		334
#घोषणा CLK_PCM2		335
#घोषणा CLK_PWM			336
#घोषणा CLK_SLIMBUS		337
#घोषणा CLK_SPDIF		338
#घोषणा CLK_AC97		339
#घोषणा CLK_MODEMIF		340
#घोषणा CLK_CHIPID		341
#घोषणा CLK_SYSREG		342
#घोषणा CLK_HDMI_CEC		343
#घोषणा CLK_MCT			344
#घोषणा CLK_WDT			345
#घोषणा CLK_RTC			346
#घोषणा CLK_KEYIF		347
#घोषणा CLK_AUDSS		348
#घोषणा CLK_MIPI_HSI		349 /* Exynos4210 only */
#घोषणा CLK_PIXELASYNCM0	351
#घोषणा CLK_PIXELASYNCM1	352
#घोषणा CLK_ASYNC_G3D		353 /* Exynos4x12 only */
#घोषणा CLK_PWM_ISP_SCLK	379 /* Exynos4x12 only */
#घोषणा CLK_SPI0_ISP_SCLK	380 /* Exynos4x12 only */
#घोषणा CLK_SPI1_ISP_SCLK	381 /* Exynos4x12 only */
#घोषणा CLK_UART_ISP_SCLK	382 /* Exynos4x12 only */
#घोषणा CLK_TMU_APBIF		383

/* mux घड़ीs */
#घोषणा CLK_MOUT_FIMC0		384
#घोषणा CLK_MOUT_FIMC1		385
#घोषणा CLK_MOUT_FIMC2		386
#घोषणा CLK_MOUT_FIMC3		387
#घोषणा CLK_MOUT_CAM0		388
#घोषणा CLK_MOUT_CAM1		389
#घोषणा CLK_MOUT_CSIS0		390
#घोषणा CLK_MOUT_CSIS1		391
#घोषणा CLK_MOUT_G3D0		392
#घोषणा CLK_MOUT_G3D1		393
#घोषणा CLK_MOUT_G3D		394
#घोषणा CLK_ACLK400_MCUISP	395 /* Exynos4x12 only */
#घोषणा CLK_MOUT_HDMI		396
#घोषणा CLK_MOUT_MIXER		397

/* gate घड़ीs - ppmu */
#घोषणा CLK_PPMULEFT		400
#घोषणा CLK_PPMURIGHT		401
#घोषणा CLK_PPMUCAMIF		402
#घोषणा CLK_PPMUTV		403
#घोषणा CLK_PPMUMFC_L		404
#घोषणा CLK_PPMUMFC_R		405
#घोषणा CLK_PPMUG3D		406
#घोषणा CLK_PPMUIMAGE		407
#घोषणा CLK_PPMULCD0		408
#घोषणा CLK_PPMULCD1		409 /* Exynos4210 only */
#घोषणा CLK_PPMUखाता		410
#घोषणा CLK_PPMUGPS		411
#घोषणा CLK_PPMUDMC0		412
#घोषणा CLK_PPMUDMC1		413
#घोषणा CLK_PPMUCPU		414
#घोषणा CLK_PPMUACP		415

/* भाग घड़ीs */
#घोषणा CLK_DIV_ACLK200		454 /* Exynos4x12 only */
#घोषणा CLK_DIV_ACLK400_MCUISP	455 /* Exynos4x12 only */
#घोषणा CLK_DIV_ACP		456
#घोषणा CLK_DIV_DMC		457
#घोषणा CLK_DIV_C2C		458 /* Exynos4x12 only */
#घोषणा CLK_DIV_GDL		459
#घोषणा CLK_DIV_GDR		460

/* must be greater than maximal घड़ी id */
#घोषणा CLK_NR_CLKS		461

/* Exynos4x12 ISP घड़ीs */
#घोषणा CLK_ISP_FIMC_ISP		 1
#घोषणा CLK_ISP_FIMC_DRC		 2
#घोषणा CLK_ISP_FIMC_FD			 3
#घोषणा CLK_ISP_FIMC_LITE0		 4
#घोषणा CLK_ISP_FIMC_LITE1		 5
#घोषणा CLK_ISP_MCUISP			 6
#घोषणा CLK_ISP_GICISP			 7
#घोषणा CLK_ISP_SMMU_ISP		 8
#घोषणा CLK_ISP_SMMU_DRC		 9
#घोषणा CLK_ISP_SMMU_FD			10
#घोषणा CLK_ISP_SMMU_LITE0		11
#घोषणा CLK_ISP_SMMU_LITE1		12
#घोषणा CLK_ISP_PPMUISPMX		13
#घोषणा CLK_ISP_PPMUISPX		14
#घोषणा CLK_ISP_MCUCTL_ISP		15
#घोषणा CLK_ISP_MPWM_ISP		16
#घोषणा CLK_ISP_I2C0_ISP		17
#घोषणा CLK_ISP_I2C1_ISP		18
#घोषणा CLK_ISP_MTCADC_ISP		19
#घोषणा CLK_ISP_PWM_ISP			20
#घोषणा CLK_ISP_WDT_ISP			21
#घोषणा CLK_ISP_UART_ISP		22
#घोषणा CLK_ISP_ASYNCAXIM		23
#घोषणा CLK_ISP_SMMU_ISPCX		24
#घोषणा CLK_ISP_SPI0_ISP		25
#घोषणा CLK_ISP_SPI1_ISP		26

#घोषणा CLK_ISP_DIV_ISP0		27
#घोषणा CLK_ISP_DIV_ISP1		28
#घोषणा CLK_ISP_DIV_MCUISP0		29
#घोषणा CLK_ISP_DIV_MCUISP1		30

#घोषणा CLK_NR_ISP_CLKS			31

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_EXYNOS_4_H */
