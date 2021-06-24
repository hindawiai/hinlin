<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम binding nvidia,tegra20-car.
 *
 * The first 96 घड़ीs are numbered to match the bits in the CAR's CLK_OUT_ENB
 * रेजिस्टरs. These IDs often match those in the CAR's RST_DEVICES रेजिस्टरs,
 * but not in all हालs. Some bits in CLK_OUT_ENB affect multiple घड़ीs. In
 * this हाल, those घड़ीs are asचिन्हित IDs above 95 in order to highlight
 * this issue. Implementations that पूर्णांकerpret these घड़ी IDs as bit values
 * within the CLK_OUT_ENB or RST_DEVICES रेजिस्टरs should be careful to
 * explicitly handle these special हालs.
 *
 * The balance of the घड़ीs controlled by the CAR are asचिन्हित IDs of 96 and
 * above.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_TEGRA20_CAR_H
#घोषणा _DT_BINDINGS_CLOCK_TEGRA20_CAR_H

#घोषणा TEGRA20_CLK_CPU 0
/* 1 */
/* 2 */
#घोषणा TEGRA20_CLK_AC97 3
#घोषणा TEGRA20_CLK_RTC 4
#घोषणा TEGRA20_CLK_TIMER 5
#घोषणा TEGRA20_CLK_UARTA 6
/* 7 (रेजिस्टर bit affects uart2 and vfir) */
#घोषणा TEGRA20_CLK_GPIO 8
#घोषणा TEGRA20_CLK_SDMMC2 9
/* 10 (रेजिस्टर bit affects spdअगर_in and spdअगर_out) */
#घोषणा TEGRA20_CLK_I2S1 11
#घोषणा TEGRA20_CLK_I2C1 12
#घोषणा TEGRA20_CLK_NDFLASH 13
#घोषणा TEGRA20_CLK_SDMMC1 14
#घोषणा TEGRA20_CLK_SDMMC4 15
#घोषणा TEGRA20_CLK_TWC 16
#घोषणा TEGRA20_CLK_PWM 17
#घोषणा TEGRA20_CLK_I2S2 18
#घोषणा TEGRA20_CLK_EPP 19
/* 20 (रेजिस्टर bit affects vi and vi_sensor) */
#घोषणा TEGRA20_CLK_GR2D 21
#घोषणा TEGRA20_CLK_USBD 22
#घोषणा TEGRA20_CLK_ISP 23
#घोषणा TEGRA20_CLK_GR3D 24
#घोषणा TEGRA20_CLK_IDE 25
#घोषणा TEGRA20_CLK_DISP2 26
#घोषणा TEGRA20_CLK_DISP1 27
#घोषणा TEGRA20_CLK_HOST1X 28
#घोषणा TEGRA20_CLK_VCP 29
/* 30 */
#घोषणा TEGRA20_CLK_CACHE2 31

#घोषणा TEGRA20_CLK_MC 32
#घोषणा TEGRA20_CLK_AHBDMA 33
#घोषणा TEGRA20_CLK_APBDMA 34
/* 35 */
#घोषणा TEGRA20_CLK_KBC 36
#घोषणा TEGRA20_CLK_STAT_MON 37
#घोषणा TEGRA20_CLK_PMC 38
#घोषणा TEGRA20_CLK_FUSE 39
#घोषणा TEGRA20_CLK_KFUSE 40
#घोषणा TEGRA20_CLK_SBC1 41
#घोषणा TEGRA20_CLK_NOR 42
#घोषणा TEGRA20_CLK_SPI 43
#घोषणा TEGRA20_CLK_SBC2 44
#घोषणा TEGRA20_CLK_XIO 45
#घोषणा TEGRA20_CLK_SBC3 46
#घोषणा TEGRA20_CLK_DVC 47
#घोषणा TEGRA20_CLK_DSI 48
/* 49 (रेजिस्टर bit affects tvo and cve) */
#घोषणा TEGRA20_CLK_MIPI 50
#घोषणा TEGRA20_CLK_HDMI 51
#घोषणा TEGRA20_CLK_CSI 52
#घोषणा TEGRA20_CLK_TVDAC 53
#घोषणा TEGRA20_CLK_I2C2 54
#घोषणा TEGRA20_CLK_UARTC 55
/* 56 */
#घोषणा TEGRA20_CLK_EMC 57
#घोषणा TEGRA20_CLK_USB2 58
#घोषणा TEGRA20_CLK_USB3 59
#घोषणा TEGRA20_CLK_MPE 60
#घोषणा TEGRA20_CLK_VDE 61
#घोषणा TEGRA20_CLK_BSEA 62
#घोषणा TEGRA20_CLK_BSEV 63

#घोषणा TEGRA20_CLK_SPEEDO 64
#घोषणा TEGRA20_CLK_UARTD 65
#घोषणा TEGRA20_CLK_UARTE 66
#घोषणा TEGRA20_CLK_I2C3 67
#घोषणा TEGRA20_CLK_SBC4 68
#घोषणा TEGRA20_CLK_SDMMC3 69
#घोषणा TEGRA20_CLK_PEX 70
#घोषणा TEGRA20_CLK_OWR 71
#घोषणा TEGRA20_CLK_AFI 72
#घोषणा TEGRA20_CLK_CSITE 73
/* 74 */
#घोषणा TEGRA20_CLK_AVPUCQ 75
#घोषणा TEGRA20_CLK_LA 76
/* 77 */
/* 78 */
/* 79 */
/* 80 */
/* 81 */
/* 82 */
/* 83 */
#घोषणा TEGRA20_CLK_IRAMA 84
#घोषणा TEGRA20_CLK_IRAMB 85
#घोषणा TEGRA20_CLK_IRAMC 86
#घोषणा TEGRA20_CLK_IRAMD 87
#घोषणा TEGRA20_CLK_CRAM2 88
#घोषणा TEGRA20_CLK_AUDIO_2X 89 /* a/k/a audio_2x_sync_clk */
#घोषणा TEGRA20_CLK_CLK_D 90
/* 91 */
#घोषणा TEGRA20_CLK_CSUS 92
#घोषणा TEGRA20_CLK_CDEV2 93
#घोषणा TEGRA20_CLK_CDEV1 94
/* 95 */

#घोषणा TEGRA20_CLK_UARTB 96
#घोषणा TEGRA20_CLK_VFIR 97
#घोषणा TEGRA20_CLK_SPDIF_IN 98
#घोषणा TEGRA20_CLK_SPDIF_OUT 99
#घोषणा TEGRA20_CLK_VI 100
#घोषणा TEGRA20_CLK_VI_SENSOR 101
#घोषणा TEGRA20_CLK_TVO 102
#घोषणा TEGRA20_CLK_CVE 103
#घोषणा TEGRA20_CLK_OSC 104
#घोषणा TEGRA20_CLK_CLK_32K 105 /* a/k/a clk_s */
#घोषणा TEGRA20_CLK_CLK_M 106
#घोषणा TEGRA20_CLK_SCLK 107
#घोषणा TEGRA20_CLK_CCLK 108
#घोषणा TEGRA20_CLK_HCLK 109
#घोषणा TEGRA20_CLK_PCLK 110
/* 111 */
#घोषणा TEGRA20_CLK_PLL_A 112
#घोषणा TEGRA20_CLK_PLL_A_OUT0 113
#घोषणा TEGRA20_CLK_PLL_C 114
#घोषणा TEGRA20_CLK_PLL_C_OUT1 115
#घोषणा TEGRA20_CLK_PLL_D 116
#घोषणा TEGRA20_CLK_PLL_D_OUT0 117
#घोषणा TEGRA20_CLK_PLL_E 118
#घोषणा TEGRA20_CLK_PLL_M 119
#घोषणा TEGRA20_CLK_PLL_M_OUT1 120
#घोषणा TEGRA20_CLK_PLL_P 121
#घोषणा TEGRA20_CLK_PLL_P_OUT1 122
#घोषणा TEGRA20_CLK_PLL_P_OUT2 123
#घोषणा TEGRA20_CLK_PLL_P_OUT3 124
#घोषणा TEGRA20_CLK_PLL_P_OUT4 125
#घोषणा TEGRA20_CLK_PLL_S 126
#घोषणा TEGRA20_CLK_PLL_U 127

#घोषणा TEGRA20_CLK_PLL_X 128
#घोषणा TEGRA20_CLK_COP 129 /* a/k/a avp */
#घोषणा TEGRA20_CLK_AUDIO 130 /* a/k/a audio_sync_clk */
#घोषणा TEGRA20_CLK_PLL_REF 131
#घोषणा TEGRA20_CLK_TWD 132
#घोषणा TEGRA20_CLK_CLK_MAX 133

#पूर्ण_अगर	/* _DT_BINDINGS_CLOCK_TEGRA20_CAR_H */
