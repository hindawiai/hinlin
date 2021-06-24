<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * 	Author: Tomasz Figa <t.figa@samsung.com>
 *
 * Device Tree binding स्थिरants क्रम Samsung Exynos3250 घड़ी controllers.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_SAMSUNG_EXYNOS3250_CLOCK_H
#घोषणा _DT_BINDINGS_CLOCK_SAMSUNG_EXYNOS3250_CLOCK_H

/*
 * Let each exported घड़ी get a unique index, which is used on DT-enabled
 * platक्रमms to lookup the घड़ी from a घड़ी specअगरier. These indices are
 * thereक्रमe considered an ABI and so must not be changed. This implies
 * that new घड़ीs should be added either in मुक्त spaces between घड़ी groups
 * or at the end.
 */


/*
 * Main CMU
 */

#घोषणा CLK_OSCSEL			1
#घोषणा CLK_FIN_PLL			2
#घोषणा CLK_FOUT_APLL			3
#घोषणा CLK_FOUT_VPLL			4
#घोषणा CLK_FOUT_UPLL			5
#घोषणा CLK_FOUT_MPLL			6
#घोषणा CLK_ARM_CLK			7

/* Muxes */
#घोषणा CLK_MOUT_MPLL_USER_L		16
#घोषणा CLK_MOUT_GDL			17
#घोषणा CLK_MOUT_MPLL_USER_R		18
#घोषणा CLK_MOUT_GDR			19
#घोषणा CLK_MOUT_EBI			20
#घोषणा CLK_MOUT_ACLK_200		21
#घोषणा CLK_MOUT_ACLK_160		22
#घोषणा CLK_MOUT_ACLK_100		23
#घोषणा CLK_MOUT_ACLK_266_1		24
#घोषणा CLK_MOUT_ACLK_266_0		25
#घोषणा CLK_MOUT_ACLK_266		26
#घोषणा CLK_MOUT_VPLL			27
#घोषणा CLK_MOUT_EPLL_USER		28
#घोषणा CLK_MOUT_EBI_1			29
#घोषणा CLK_MOUT_UPLL			30
#घोषणा CLK_MOUT_ACLK_400_MCUISP_SUB	31
#घोषणा CLK_MOUT_MPLL			32
#घोषणा CLK_MOUT_ACLK_400_MCUISP	33
#घोषणा CLK_MOUT_VPLLSRC		34
#घोषणा CLK_MOUT_CAM1			35
#घोषणा CLK_MOUT_CAM_BLK		36
#घोषणा CLK_MOUT_MFC			37
#घोषणा CLK_MOUT_MFC_1			38
#घोषणा CLK_MOUT_MFC_0			39
#घोषणा CLK_MOUT_G3D			40
#घोषणा CLK_MOUT_G3D_1			41
#घोषणा CLK_MOUT_G3D_0			42
#घोषणा CLK_MOUT_MIPI0			43
#घोषणा CLK_MOUT_FIMD0			44
#घोषणा CLK_MOUT_UART_ISP		45
#घोषणा CLK_MOUT_SPI1_ISP		46
#घोषणा CLK_MOUT_SPI0_ISP		47
#घोषणा CLK_MOUT_TSADC			48
#घोषणा CLK_MOUT_MMC1			49
#घोषणा CLK_MOUT_MMC0			50
#घोषणा CLK_MOUT_UART1			51
#घोषणा CLK_MOUT_UART0			52
#घोषणा CLK_MOUT_SPI1			53
#घोषणा CLK_MOUT_SPI0			54
#घोषणा CLK_MOUT_AUDIO			55
#घोषणा CLK_MOUT_MPLL_USER_C		56
#घोषणा CLK_MOUT_HPM			57
#घोषणा CLK_MOUT_CORE			58
#घोषणा CLK_MOUT_APLL			59
#घोषणा CLK_MOUT_ACLK_266_SUB		60
#घोषणा CLK_MOUT_UART2			61
#घोषणा CLK_MOUT_MMC2			62

/* Dividers */
#घोषणा CLK_DIV_GPL			64
#घोषणा CLK_DIV_GDL			65
#घोषणा CLK_DIV_GPR			66
#घोषणा CLK_DIV_GDR			67
#घोषणा CLK_DIV_MPLL_PRE		68
#घोषणा CLK_DIV_ACLK_400_MCUISP		69
#घोषणा CLK_DIV_EBI			70
#घोषणा CLK_DIV_ACLK_200		71
#घोषणा CLK_DIV_ACLK_160		72
#घोषणा CLK_DIV_ACLK_100		73
#घोषणा CLK_DIV_ACLK_266		74
#घोषणा CLK_DIV_CAM1			75
#घोषणा CLK_DIV_CAM_BLK			76
#घोषणा CLK_DIV_MFC			77
#घोषणा CLK_DIV_G3D			78
#घोषणा CLK_DIV_MIPI0_PRE		79
#घोषणा CLK_DIV_MIPI0			80
#घोषणा CLK_DIV_FIMD0			81
#घोषणा CLK_DIV_UART_ISP		82
#घोषणा CLK_DIV_SPI1_ISP_PRE		83
#घोषणा CLK_DIV_SPI1_ISP		84
#घोषणा CLK_DIV_SPI0_ISP_PRE		85
#घोषणा CLK_DIV_SPI0_ISP		86
#घोषणा CLK_DIV_TSADC_PRE		87
#घोषणा CLK_DIV_TSADC			88
#घोषणा CLK_DIV_MMC1_PRE		89
#घोषणा CLK_DIV_MMC1			90
#घोषणा CLK_DIV_MMC0_PRE		91
#घोषणा CLK_DIV_MMC0			92
#घोषणा CLK_DIV_UART1			93
#घोषणा CLK_DIV_UART0			94
#घोषणा CLK_DIV_SPI1_PRE		95
#घोषणा CLK_DIV_SPI1			96
#घोषणा CLK_DIV_SPI0_PRE		97
#घोषणा CLK_DIV_SPI0			98
#घोषणा CLK_DIV_PCM			99
#घोषणा CLK_DIV_AUDIO			100
#घोषणा CLK_DIV_I2S			101
#घोषणा CLK_DIV_CORE2			102
#घोषणा CLK_DIV_APLL			103
#घोषणा CLK_DIV_PCLK_DBG		104
#घोषणा CLK_DIV_ATB			105
#घोषणा CLK_DIV_COREM			106
#घोषणा CLK_DIV_CORE			107
#घोषणा CLK_DIV_HPM			108
#घोषणा CLK_DIV_COPY			109
#घोषणा CLK_DIV_UART2			110
#घोषणा CLK_DIV_MMC2_PRE		111
#घोषणा CLK_DIV_MMC2			112

/* Gates */
#घोषणा CLK_ASYNC_G3D			128
#घोषणा CLK_ASYNC_MFCL			129
#घोषणा CLK_PPMULEFT			130
#घोषणा CLK_GPIO_LEFT			131
#घोषणा CLK_ASYNC_ISPMX			132
#घोषणा CLK_ASYNC_FSYSD			133
#घोषणा CLK_ASYNC_LCD0X			134
#घोषणा CLK_ASYNC_CAMX			135
#घोषणा CLK_PPMURIGHT			136
#घोषणा CLK_GPIO_RIGHT			137
#घोषणा CLK_MONOCNT			138
#घोषणा CLK_TZPC6			139
#घोषणा CLK_PROVISIONKEY1		140
#घोषणा CLK_PROVISIONKEY0		141
#घोषणा CLK_CMU_ISPPART			142
#घोषणा CLK_TMU_APBIF			143
#घोषणा CLK_KEYIF			144
#घोषणा CLK_RTC				145
#घोषणा CLK_WDT				146
#घोषणा CLK_MCT				147
#घोषणा CLK_SECKEY			148
#घोषणा CLK_TZPC5			149
#घोषणा CLK_TZPC4			150
#घोषणा CLK_TZPC3			151
#घोषणा CLK_TZPC2			152
#घोषणा CLK_TZPC1			153
#घोषणा CLK_TZPC0			154
#घोषणा CLK_CMU_COREPART		155
#घोषणा CLK_CMU_TOPPART			156
#घोषणा CLK_PMU_APBIF			157
#घोषणा CLK_SYSREG			158
#घोषणा CLK_CHIP_ID			159
#घोषणा CLK_QEJPEG			160
#घोषणा CLK_PIXELASYNCM1		161
#घोषणा CLK_PIXELASYNCM0		162
#घोषणा CLK_PPMUCAMIF			163
#घोषणा CLK_QEM2MSCALER			164
#घोषणा CLK_QEGSCALER1			165
#घोषणा CLK_QEGSCALER0			166
#घोषणा CLK_SMMUJPEG			167
#घोषणा CLK_SMMUM2M2SCALER		168
#घोषणा CLK_SMMUGSCALER1		169
#घोषणा CLK_SMMUGSCALER0		170
#घोषणा CLK_JPEG			171
#घोषणा CLK_M2MSCALER			172
#घोषणा CLK_GSCALER1			173
#घोषणा CLK_GSCALER0			174
#घोषणा CLK_QEMFC			175
#घोषणा CLK_PPMUMFC_L			176
#घोषणा CLK_SMMUMFC_L			177
#घोषणा CLK_MFC				178
#घोषणा CLK_SMMUG3D			179
#घोषणा CLK_QEG3D			180
#घोषणा CLK_PPMUG3D			181
#घोषणा CLK_G3D				182
#घोषणा CLK_QE_CH1_LCD			183
#घोषणा CLK_QE_CH0_LCD			184
#घोषणा CLK_PPMULCD0			185
#घोषणा CLK_SMMUFIMD0			186
#घोषणा CLK_DSIM0			187
#घोषणा CLK_FIMD0			188
#घोषणा CLK_CAM1			189
#घोषणा CLK_UART_ISP_TOP		190
#घोषणा CLK_SPI1_ISP_TOP		191
#घोषणा CLK_SPI0_ISP_TOP		192
#घोषणा CLK_TSADC			193
#घोषणा CLK_PPMUखाता			194
#घोषणा CLK_USBOTG			195
#घोषणा CLK_USBHOST			196
#घोषणा CLK_SROMC			197
#घोषणा CLK_SDMMC1			198
#घोषणा CLK_SDMMC0			199
#घोषणा CLK_PDMA1			200
#घोषणा CLK_PDMA0			201
#घोषणा CLK_PWM				202
#घोषणा CLK_PCM				203
#घोषणा CLK_I2S				204
#घोषणा CLK_SPI1			205
#घोषणा CLK_SPI0			206
#घोषणा CLK_I2C7			207
#घोषणा CLK_I2C6			208
#घोषणा CLK_I2C5			209
#घोषणा CLK_I2C4			210
#घोषणा CLK_I2C3			211
#घोषणा CLK_I2C2			212
#घोषणा CLK_I2C1			213
#घोषणा CLK_I2C0			214
#घोषणा CLK_UART1			215
#घोषणा CLK_UART0			216
#घोषणा CLK_BLOCK_LCD			217
#घोषणा CLK_BLOCK_G3D			218
#घोषणा CLK_BLOCK_MFC			219
#घोषणा CLK_BLOCK_CAM			220
#घोषणा CLK_SMIES			221
#घोषणा CLK_UART2			222
#घोषणा CLK_SDMMC2			223

/* Special घड़ीs */
#घोषणा CLK_SCLK_JPEG			224
#घोषणा CLK_SCLK_M2MSCALER		225
#घोषणा CLK_SCLK_GSCALER1		226
#घोषणा CLK_SCLK_GSCALER0		227
#घोषणा CLK_SCLK_MFC			228
#घोषणा CLK_SCLK_G3D			229
#घोषणा CLK_SCLK_MIPIDPHY2L		230
#घोषणा CLK_SCLK_MIPI0			231
#घोषणा CLK_SCLK_FIMD0			232
#घोषणा CLK_SCLK_CAM1			233
#घोषणा CLK_SCLK_UART_ISP		234
#घोषणा CLK_SCLK_SPI1_ISP		235
#घोषणा CLK_SCLK_SPI0_ISP		236
#घोषणा CLK_SCLK_UPLL			237
#घोषणा CLK_SCLK_TSADC			238
#घोषणा CLK_SCLK_EBI			239
#घोषणा CLK_SCLK_MMC1			240
#घोषणा CLK_SCLK_MMC0			241
#घोषणा CLK_SCLK_I2S			242
#घोषणा CLK_SCLK_PCM			243
#घोषणा CLK_SCLK_SPI1			244
#घोषणा CLK_SCLK_SPI0			245
#घोषणा CLK_SCLK_UART1			246
#घोषणा CLK_SCLK_UART0			247
#घोषणा CLK_SCLK_UART2			248
#घोषणा CLK_SCLK_MMC2			249

/*
 * Total number of घड़ीs of मुख्य CMU.
 * NOTE: Must be equal to last घड़ी ID increased by one.
 */
#घोषणा CLK_NR_CLKS			250

/*
 * CMU DMC
 */

#घोषणा CLK_FOUT_BPLL			1
#घोषणा CLK_FOUT_EPLL			2

/* Muxes */
#घोषणा CLK_MOUT_MPLL_MIF		8
#घोषणा CLK_MOUT_BPLL			9
#घोषणा CLK_MOUT_DPHY			10
#घोषणा CLK_MOUT_DMC_BUS		11
#घोषणा CLK_MOUT_EPLL			12

/* Dividers */
#घोषणा CLK_DIV_DMC			16
#घोषणा CLK_DIV_DPHY			17
#घोषणा CLK_DIV_DMC_PRE			18
#घोषणा CLK_DIV_DMCP			19
#घोषणा CLK_DIV_DMCD			20

/*
 * Total number of घड़ीs of मुख्य CMU.
 * NOTE: Must be equal to last घड़ी ID increased by one.
 */
#घोषणा NR_CLKS_DMC			21

/*
 * CMU ISP
 */

/* Dividers */

#घोषणा CLK_DIV_ISP1			1
#घोषणा CLK_DIV_ISP0			2
#घोषणा CLK_DIV_MCUISP1			3
#घोषणा CLK_DIV_MCUISP0			4
#घोषणा CLK_DIV_MPWM			5

/* Gates */

#घोषणा CLK_UART_ISP			8
#घोषणा CLK_WDT_ISP			9
#घोषणा CLK_PWM_ISP			10
#घोषणा CLK_I2C1_ISP			11
#घोषणा CLK_I2C0_ISP			12
#घोषणा CLK_MPWM_ISP			13
#घोषणा CLK_MCUCTL_ISP			14
#घोषणा CLK_PPMUISPX			15
#घोषणा CLK_PPMUISPMX			16
#घोषणा CLK_QE_LITE1			17
#घोषणा CLK_QE_LITE0			18
#घोषणा CLK_QE_FD			19
#घोषणा CLK_QE_DRC			20
#घोषणा CLK_QE_ISP			21
#घोषणा CLK_CSIS1			22
#घोषणा CLK_SMMU_LITE1			23
#घोषणा CLK_SMMU_LITE0			24
#घोषणा CLK_SMMU_FD			25
#घोषणा CLK_SMMU_DRC			26
#घोषणा CLK_SMMU_ISP			27
#घोषणा CLK_GICISP			28
#घोषणा CLK_CSIS0			29
#घोषणा CLK_MCUISP			30
#घोषणा CLK_LITE1			31
#घोषणा CLK_LITE0			32
#घोषणा CLK_FD				33
#घोषणा CLK_DRC				34
#घोषणा CLK_ISP				35
#घोषणा CLK_QE_ISPCX			36
#घोषणा CLK_QE_SCALERP			37
#घोषणा CLK_QE_SCALERC			38
#घोषणा CLK_SMMU_SCALERP		39
#घोषणा CLK_SMMU_SCALERC		40
#घोषणा CLK_SCALERP			41
#घोषणा CLK_SCALERC			42
#घोषणा CLK_SPI1_ISP			43
#घोषणा CLK_SPI0_ISP			44
#घोषणा CLK_SMMU_ISPCX			45
#घोषणा CLK_ASYNCAXIM			46
#घोषणा CLK_SCLK_MPWM_ISP		47

/*
 * Total number of घड़ीs of CMU_ISP.
 * NOTE: Must be equal to last घड़ी ID increased by one.
 */
#घोषणा NR_CLKS_ISP			48

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_SAMSUNG_EXYNOS3250_CLOCK_H */
