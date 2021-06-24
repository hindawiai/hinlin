<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/*
 * Copyright (C) 2020 Intel Corporation.
 * Lei Chuanhua <Chuanhua.lei@पूर्णांकel.com>
 * Zhu Yixin <Yixin.zhu@पूर्णांकel.com>
 */
#अगर_अघोषित __INTEL_LGM_CLK_H
#घोषणा __INTEL_LGM_CLK_H

/* PLL घड़ीs */
#घोषणा LGM_CLK_OSC		1
#घोषणा LGM_CLK_PLLPP		2
#घोषणा LGM_CLK_PLL2		3
#घोषणा LGM_CLK_PLL0CZ		4
#घोषणा LGM_CLK_PLL0B		5
#घोषणा LGM_CLK_PLL1		6
#घोषणा LGM_CLK_LJPLL3		7
#घोषणा LGM_CLK_LJPLL4		8
#घोषणा LGM_CLK_PLL0CM0		9
#घोषणा LGM_CLK_PLL0CM1		10

/* घड़ीs from PLLs */

/* ROPLL घड़ीs */
#घोषणा LGM_CLK_PP_HW		15
#घोषणा LGM_CLK_PP_UC		16
#घोषणा LGM_CLK_PP_FXD		17
#घोषणा LGM_CLK_PP_TBM		18

/* PLL2 घड़ीs */
#घोषणा LGM_CLK_DDR		20

/* PLL0CZ */
#घोषणा LGM_CLK_CM		25
#घोषणा LGM_CLK_IC		26
#घोषणा LGM_CLK_SDXC3		27

/* PLL0B */
#घोषणा LGM_CLK_NGI		30
#घोषणा LGM_CLK_NOC4		31
#घोषणा LGM_CLK_SW		32
#घोषणा LGM_CLK_QSPI		33
#घोषणा LGM_CLK_CQEM		LGM_CLK_SW
#घोषणा LGM_CLK_EMMC5		LGM_CLK_NOC4

/* PLL1 */
#घोषणा LGM_CLK_CT		35
#घोषणा LGM_CLK_DSP		36
#घोषणा LGM_CLK_VIF		37

/* LJPLL3 */
#घोषणा LGM_CLK_CML		40
#घोषणा LGM_CLK_SERDES		41
#घोषणा LGM_CLK_POOL		42
#घोषणा LGM_CLK_PTP		43

/* LJPLL4 */
#घोषणा LGM_CLK_PCIE		45
#घोषणा LGM_CLK_SATA		LGM_CLK_PCIE

/* PLL0CM0 */
#घोषणा LGM_CLK_CPU0		50

/* PLL0CM1 */
#घोषणा LGM_CLK_CPU1		55

/* Miscellaneous घड़ीs */
#घोषणा LGM_CLK_EMMC4		60
#घोषणा LGM_CLK_SDXC2		61
#घोषणा LGM_CLK_EMMC		62
#घोषणा LGM_CLK_SDXC		63
#घोषणा LGM_CLK_SLIC		64
#घोषणा LGM_CLK_DCL		65
#घोषणा LGM_CLK_DOCSIS		66
#घोषणा LGM_CLK_PCM		67
#घोषणा LGM_CLK_DDR_PHY		68
#घोषणा LGM_CLK_PONDEF		69
#घोषणा LGM_CLK_PL25M		70
#घोषणा LGM_CLK_PL10M		71
#घोषणा LGM_CLK_PL1544K		72
#घोषणा LGM_CLK_PL2048K		73
#घोषणा LGM_CLK_PL8K		74
#घोषणा LGM_CLK_PON_NTR		75
#घोषणा LGM_CLK_SYNC0		76
#घोषणा LGM_CLK_SYNC1		77
#घोषणा LGM_CLK_PROGDIV		78
#घोषणा LGM_CLK_OD0		79
#घोषणा LGM_CLK_OD1		80
#घोषणा LGM_CLK_CBPHY0		81
#घोषणा LGM_CLK_CBPHY1		82
#घोषणा LGM_CLK_CBPHY2		83
#घोषणा LGM_CLK_CBPHY3		84

/* Gate घड़ीs */
/* Gate CLK0 */
#घोषणा LGM_GCLK_C55		100
#घोषणा LGM_GCLK_QSPI		101
#घोषणा LGM_GCLK_EIP197		102
#घोषणा LGM_GCLK_VAULT		103
#घोषणा LGM_GCLK_TOE		104
#घोषणा LGM_GCLK_SDXC		105
#घोषणा LGM_GCLK_EMMC		106
#घोषणा LGM_GCLK_SPI_DBG	107
#घोषणा LGM_GCLK_DMA3		108

/* Gate CLK1 */
#घोषणा LGM_GCLK_DMA0		120
#घोषणा LGM_GCLK_LEDC0		121
#घोषणा LGM_GCLK_LEDC1		122
#घोषणा LGM_GCLK_I2S0		123
#घोषणा LGM_GCLK_I2S1		124
#घोषणा LGM_GCLK_EBU		125
#घोषणा LGM_GCLK_PWM		126
#घोषणा LGM_GCLK_I2C0		127
#घोषणा LGM_GCLK_I2C1		128
#घोषणा LGM_GCLK_I2C2		129
#घोषणा LGM_GCLK_I2C3		130
#घोषणा LGM_GCLK_SSC0		131
#घोषणा LGM_GCLK_SSC1		132
#घोषणा LGM_GCLK_SSC2		133
#घोषणा LGM_GCLK_SSC3		134
#घोषणा LGM_GCLK_GPTC0		135
#घोषणा LGM_GCLK_GPTC1		136
#घोषणा LGM_GCLK_GPTC2		137
#घोषणा LGM_GCLK_GPTC3		138
#घोषणा LGM_GCLK_ASC0		139
#घोषणा LGM_GCLK_ASC1		140
#घोषणा LGM_GCLK_ASC2		141
#घोषणा LGM_GCLK_ASC3		142
#घोषणा LGM_GCLK_PCM0		143
#घोषणा LGM_GCLK_PCM1		144
#घोषणा LGM_GCLK_PCM2		145

/* Gate CLK2 */
#घोषणा LGM_GCLK_PCIE10		150
#घोषणा LGM_GCLK_PCIE11		151
#घोषणा LGM_GCLK_PCIE30		152
#घोषणा LGM_GCLK_PCIE31		153
#घोषणा LGM_GCLK_PCIE20		154
#घोषणा LGM_GCLK_PCIE21		155
#घोषणा LGM_GCLK_PCIE40		156
#घोषणा LGM_GCLK_PCIE41		157
#घोषणा LGM_GCLK_XPCS0		158
#घोषणा LGM_GCLK_XPCS1		159
#घोषणा LGM_GCLK_XPCS2		160
#घोषणा LGM_GCLK_XPCS3		161
#घोषणा LGM_GCLK_SATA0		162
#घोषणा LGM_GCLK_SATA1		163
#घोषणा LGM_GCLK_SATA2		164
#घोषणा LGM_GCLK_SATA3		165

/* Gate CLK3 */
#घोषणा LGM_GCLK_ARCEM4		170
#घोषणा LGM_GCLK_IDMAR1		171
#घोषणा LGM_GCLK_IDMAT0		172
#घोषणा LGM_GCLK_IDMAT1		173
#घोषणा LGM_GCLK_IDMAT2		174
#घोषणा LGM_GCLK_PPV4		175
#घोषणा LGM_GCLK_GSWIPO		176
#घोषणा LGM_GCLK_CQEM		177
#घोषणा LGM_GCLK_XPCS5		178
#घोषणा LGM_GCLK_USB1		179
#घोषणा LGM_GCLK_USB2		180

#पूर्ण_अगर /* __INTEL_LGM_CLK_H */
