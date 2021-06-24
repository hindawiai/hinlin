<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम binding nvidia,tegra30-car.
 *
 * The first 130 घड़ीs are numbered to match the bits in the CAR's CLK_OUT_ENB
 * रेजिस्टरs. These IDs often match those in the CAR's RST_DEVICES रेजिस्टरs,
 * but not in all हालs. Some bits in CLK_OUT_ENB affect multiple घड़ीs. In
 * this हाल, those घड़ीs are asचिन्हित IDs above 160 in order to highlight
 * this issue. Implementations that पूर्णांकerpret these घड़ी IDs as bit values
 * within the CLK_OUT_ENB or RST_DEVICES रेजिस्टरs should be careful to
 * explicitly handle these special हालs.
 *
 * The balance of the घड़ीs controlled by the CAR are asचिन्हित IDs of 160 and
 * above.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_TEGRA30_CAR_H
#घोषणा _DT_BINDINGS_CLOCK_TEGRA30_CAR_H

#घोषणा TEGRA30_CLK_CPU 0
/* 1 */
/* 2 */
/* 3 */
#घोषणा TEGRA30_CLK_RTC 4
#घोषणा TEGRA30_CLK_TIMER 5
#घोषणा TEGRA30_CLK_UARTA 6
/* 7 (रेजिस्टर bit affects uartb and vfir) */
#घोषणा TEGRA30_CLK_GPIO 8
#घोषणा TEGRA30_CLK_SDMMC2 9
/* 10 (रेजिस्टर bit affects spdअगर_in and spdअगर_out) */
#घोषणा TEGRA30_CLK_I2S1 11
#घोषणा TEGRA30_CLK_I2C1 12
#घोषणा TEGRA30_CLK_NDFLASH 13
#घोषणा TEGRA30_CLK_SDMMC1 14
#घोषणा TEGRA30_CLK_SDMMC4 15
/* 16 */
#घोषणा TEGRA30_CLK_PWM 17
#घोषणा TEGRA30_CLK_I2S2 18
#घोषणा TEGRA30_CLK_EPP 19
/* 20 (रेजिस्टर bit affects vi and vi_sensor) */
#घोषणा TEGRA30_CLK_GR2D 21
#घोषणा TEGRA30_CLK_USBD 22
#घोषणा TEGRA30_CLK_ISP 23
#घोषणा TEGRA30_CLK_GR3D 24
/* 25 */
#घोषणा TEGRA30_CLK_DISP2 26
#घोषणा TEGRA30_CLK_DISP1 27
#घोषणा TEGRA30_CLK_HOST1X 28
#घोषणा TEGRA30_CLK_VCP 29
#घोषणा TEGRA30_CLK_I2S0 30
#घोषणा TEGRA30_CLK_COP_CACHE 31

#घोषणा TEGRA30_CLK_MC 32
#घोषणा TEGRA30_CLK_AHBDMA 33
#घोषणा TEGRA30_CLK_APBDMA 34
/* 35 */
#घोषणा TEGRA30_CLK_KBC 36
#घोषणा TEGRA30_CLK_STATMON 37
#घोषणा TEGRA30_CLK_PMC 38
/* 39 (रेजिस्टर bit affects fuse and fuse_burn) */
#घोषणा TEGRA30_CLK_KFUSE 40
#घोषणा TEGRA30_CLK_SBC1 41
#घोषणा TEGRA30_CLK_NOR 42
/* 43 */
#घोषणा TEGRA30_CLK_SBC2 44
/* 45 */
#घोषणा TEGRA30_CLK_SBC3 46
#घोषणा TEGRA30_CLK_I2C5 47
#घोषणा TEGRA30_CLK_DSIA 48
/* 49 (रेजिस्टर bit affects cve and tvo) */
#घोषणा TEGRA30_CLK_MIPI 50
#घोषणा TEGRA30_CLK_HDMI 51
#घोषणा TEGRA30_CLK_CSI 52
#घोषणा TEGRA30_CLK_TVDAC 53
#घोषणा TEGRA30_CLK_I2C2 54
#घोषणा TEGRA30_CLK_UARTC 55
/* 56 */
#घोषणा TEGRA30_CLK_EMC 57
#घोषणा TEGRA30_CLK_USB2 58
#घोषणा TEGRA30_CLK_USB3 59
#घोषणा TEGRA30_CLK_MPE 60
#घोषणा TEGRA30_CLK_VDE 61
#घोषणा TEGRA30_CLK_BSEA 62
#घोषणा TEGRA30_CLK_BSEV 63

#घोषणा TEGRA30_CLK_SPEEDO 64
#घोषणा TEGRA30_CLK_UARTD 65
#घोषणा TEGRA30_CLK_UARTE 66
#घोषणा TEGRA30_CLK_I2C3 67
#घोषणा TEGRA30_CLK_SBC4 68
#घोषणा TEGRA30_CLK_SDMMC3 69
#घोषणा TEGRA30_CLK_PCIE 70
#घोषणा TEGRA30_CLK_OWR 71
#घोषणा TEGRA30_CLK_AFI 72
#घोषणा TEGRA30_CLK_CSITE 73
/* 74 */
#घोषणा TEGRA30_CLK_AVPUCQ 75
#घोषणा TEGRA30_CLK_LA 76
/* 77 */
/* 78 */
#घोषणा TEGRA30_CLK_DTV 79
#घोषणा TEGRA30_CLK_NDSPEED 80
#घोषणा TEGRA30_CLK_I2CSLOW 81
#घोषणा TEGRA30_CLK_DSIB 82
/* 83 */
#घोषणा TEGRA30_CLK_IRAMA 84
#घोषणा TEGRA30_CLK_IRAMB 85
#घोषणा TEGRA30_CLK_IRAMC 86
#घोषणा TEGRA30_CLK_IRAMD 87
#घोषणा TEGRA30_CLK_CRAM2 88
/* 89 */
#घोषणा TEGRA30_CLK_AUDIO_2X 90 /* a/k/a audio_2x_sync_clk */
/* 91 */
#घोषणा TEGRA30_CLK_CSUS 92
#घोषणा TEGRA30_CLK_CDEV2 93
#घोषणा TEGRA30_CLK_CDEV1 94
/* 95 */

#घोषणा TEGRA30_CLK_CPU_G 96
#घोषणा TEGRA30_CLK_CPU_LP 97
#घोषणा TEGRA30_CLK_GR3D2 98
#घोषणा TEGRA30_CLK_MSELECT 99
#घोषणा TEGRA30_CLK_TSENSOR 100
#घोषणा TEGRA30_CLK_I2S3 101
#घोषणा TEGRA30_CLK_I2S4 102
#घोषणा TEGRA30_CLK_I2C4 103
#घोषणा TEGRA30_CLK_SBC5 104
#घोषणा TEGRA30_CLK_SBC6 105
#घोषणा TEGRA30_CLK_D_AUDIO 106
#घोषणा TEGRA30_CLK_APBIF 107
#घोषणा TEGRA30_CLK_DAM0 108
#घोषणा TEGRA30_CLK_DAM1 109
#घोषणा TEGRA30_CLK_DAM2 110
#घोषणा TEGRA30_CLK_HDA2CODEC_2X 111
#घोषणा TEGRA30_CLK_ATOMICS 112
#घोषणा TEGRA30_CLK_AUDIO0_2X 113
#घोषणा TEGRA30_CLK_AUDIO1_2X 114
#घोषणा TEGRA30_CLK_AUDIO2_2X 115
#घोषणा TEGRA30_CLK_AUDIO3_2X 116
#घोषणा TEGRA30_CLK_AUDIO4_2X 117
#घोषणा TEGRA30_CLK_SPDIF_2X 118
#घोषणा TEGRA30_CLK_ACTMON 119
#घोषणा TEGRA30_CLK_EXTERN1 120
#घोषणा TEGRA30_CLK_EXTERN2 121
#घोषणा TEGRA30_CLK_EXTERN3 122
#घोषणा TEGRA30_CLK_SATA_OOB 123
#घोषणा TEGRA30_CLK_SATA 124
#घोषणा TEGRA30_CLK_HDA 125
/* 126 */
#घोषणा TEGRA30_CLK_SE 127

#घोषणा TEGRA30_CLK_HDA2HDMI 128
#घोषणा TEGRA30_CLK_SATA_COLD 129
/* 130 */
/* 131 */
/* 132 */
/* 133 */
/* 134 */
/* 135 */
#घोषणा TEGRA30_CLK_CEC 136
/* 137 */
/* 138 */
/* 139 */
/* 140 */
/* 141 */
/* 142 */
/* 143 */
/* 144 */
/* 145 */
/* 146 */
/* 147 */
/* 148 */
/* 149 */
/* 150 */
/* 151 */
/* 152 */
/* 153 */
/* 154 */
/* 155 */
/* 156 */
/* 157 */
/* 158 */
/* 159 */

#घोषणा TEGRA30_CLK_UARTB 160
#घोषणा TEGRA30_CLK_VFIR 161
#घोषणा TEGRA30_CLK_SPDIF_IN 162
#घोषणा TEGRA30_CLK_SPDIF_OUT 163
#घोषणा TEGRA30_CLK_VI 164
#घोषणा TEGRA30_CLK_VI_SENSOR 165
#घोषणा TEGRA30_CLK_FUSE 166
#घोषणा TEGRA30_CLK_FUSE_BURN 167
#घोषणा TEGRA30_CLK_CVE 168
#घोषणा TEGRA30_CLK_TVO 169
#घोषणा TEGRA30_CLK_CLK_32K 170
#घोषणा TEGRA30_CLK_CLK_M 171
#घोषणा TEGRA30_CLK_CLK_M_DIV2 172
#घोषणा TEGRA30_CLK_CLK_M_DIV4 173
#घोषणा TEGRA30_CLK_OSC_DIV2 172
#घोषणा TEGRA30_CLK_OSC_DIV4 173
#घोषणा TEGRA30_CLK_PLL_REF 174
#घोषणा TEGRA30_CLK_PLL_C 175
#घोषणा TEGRA30_CLK_PLL_C_OUT1 176
#घोषणा TEGRA30_CLK_PLL_M 177
#घोषणा TEGRA30_CLK_PLL_M_OUT1 178
#घोषणा TEGRA30_CLK_PLL_P 179
#घोषणा TEGRA30_CLK_PLL_P_OUT1 180
#घोषणा TEGRA30_CLK_PLL_P_OUT2 181
#घोषणा TEGRA30_CLK_PLL_P_OUT3 182
#घोषणा TEGRA30_CLK_PLL_P_OUT4 183
#घोषणा TEGRA30_CLK_PLL_A 184
#घोषणा TEGRA30_CLK_PLL_A_OUT0 185
#घोषणा TEGRA30_CLK_PLL_D 186
#घोषणा TEGRA30_CLK_PLL_D_OUT0 187
#घोषणा TEGRA30_CLK_PLL_D2 188
#घोषणा TEGRA30_CLK_PLL_D2_OUT0 189
#घोषणा TEGRA30_CLK_PLL_U 190
#घोषणा TEGRA30_CLK_PLL_X 191

#घोषणा TEGRA30_CLK_PLL_X_OUT0 192
#घोषणा TEGRA30_CLK_PLL_E 193
#घोषणा TEGRA30_CLK_SPDIF_IN_SYNC 194
#घोषणा TEGRA30_CLK_I2S0_SYNC 195
#घोषणा TEGRA30_CLK_I2S1_SYNC 196
#घोषणा TEGRA30_CLK_I2S2_SYNC 197
#घोषणा TEGRA30_CLK_I2S3_SYNC 198
#घोषणा TEGRA30_CLK_I2S4_SYNC 199
#घोषणा TEGRA30_CLK_VIMCLK_SYNC 200
#घोषणा TEGRA30_CLK_AUDIO0 201
#घोषणा TEGRA30_CLK_AUDIO1 202
#घोषणा TEGRA30_CLK_AUDIO2 203
#घोषणा TEGRA30_CLK_AUDIO3 204
#घोषणा TEGRA30_CLK_AUDIO4 205
#घोषणा TEGRA30_CLK_SPDIF 206
/* 207 */
/* 208 */
/* 209 */
#घोषणा TEGRA30_CLK_SCLK 210
/* 211 */
#घोषणा TEGRA30_CLK_CCLK_G 212
#घोषणा TEGRA30_CLK_CCLK_LP 213
#घोषणा TEGRA30_CLK_TWD 214
#घोषणा TEGRA30_CLK_CML0 215
#घोषणा TEGRA30_CLK_CML1 216
#घोषणा TEGRA30_CLK_HCLK 217
#घोषणा TEGRA30_CLK_PCLK 218
/* 219 */
#घोषणा TEGRA30_CLK_OSC 220
/* 221 */
/* 222 */
/* 223 */

/* 288 */
/* 289 */
/* 290 */
/* 291 */
/* 292 */
/* 293 */
/* 294 */
/* 295 */
/* 296 */
/* 297 */
/* 298 */
/* 299 */
/* 300 */
/* 301 */
/* 302 */
#घोषणा TEGRA30_CLK_AUDIO0_MUX 303
#घोषणा TEGRA30_CLK_AUDIO1_MUX 304
#घोषणा TEGRA30_CLK_AUDIO2_MUX 305
#घोषणा TEGRA30_CLK_AUDIO3_MUX 306
#घोषणा TEGRA30_CLK_AUDIO4_MUX 307
#घोषणा TEGRA30_CLK_SPDIF_MUX 308
#घोषणा TEGRA30_CLK_CLK_MAX 309

#पूर्ण_अगर	/* _DT_BINDINGS_CLOCK_TEGRA30_CAR_H */
