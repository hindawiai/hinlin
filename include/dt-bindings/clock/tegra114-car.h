<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम binding nvidia,tegra114-car.
 *
 * The first 160 घड़ीs are numbered to match the bits in the CAR's CLK_OUT_ENB
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

#अगर_अघोषित _DT_BINDINGS_CLOCK_TEGRA114_CAR_H
#घोषणा _DT_BINDINGS_CLOCK_TEGRA114_CAR_H

/* 0 */
/* 1 */
/* 2 */
/* 3 */
#घोषणा TEGRA114_CLK_RTC 4
#घोषणा TEGRA114_CLK_TIMER 5
#घोषणा TEGRA114_CLK_UARTA 6
/* 7 (रेजिस्टर bit affects uartb and vfir) */
/* 8 */
#घोषणा TEGRA114_CLK_SDMMC2 9
/* 10 (रेजिस्टर bit affects spdअगर_in and spdअगर_out) */
#घोषणा TEGRA114_CLK_I2S1 11
#घोषणा TEGRA114_CLK_I2C1 12
#घोषणा TEGRA114_CLK_NDFLASH 13
#घोषणा TEGRA114_CLK_SDMMC1 14
#घोषणा TEGRA114_CLK_SDMMC4 15
/* 16 */
#घोषणा TEGRA114_CLK_PWM 17
#घोषणा TEGRA114_CLK_I2S2 18
#घोषणा TEGRA114_CLK_EPP 19
/* 20 (रेजिस्टर bit affects vi and vi_sensor) */
#घोषणा TEGRA114_CLK_GR2D 21
#घोषणा TEGRA114_CLK_USBD 22
#घोषणा TEGRA114_CLK_ISP 23
#घोषणा TEGRA114_CLK_GR3D 24
/* 25 */
#घोषणा TEGRA114_CLK_DISP2 26
#घोषणा TEGRA114_CLK_DISP1 27
#घोषणा TEGRA114_CLK_HOST1X 28
#घोषणा TEGRA114_CLK_VCP 29
#घोषणा TEGRA114_CLK_I2S0 30
/* 31 */

#घोषणा TEGRA114_CLK_MC 32
/* 33 */
#घोषणा TEGRA114_CLK_APBDMA 34
/* 35 */
#घोषणा TEGRA114_CLK_KBC 36
/* 37 */
/* 38 */
/* 39 (रेजिस्टर bit affects fuse and fuse_burn) */
#घोषणा TEGRA114_CLK_KFUSE 40
#घोषणा TEGRA114_CLK_SBC1 41
#घोषणा TEGRA114_CLK_NOR 42
/* 43 */
#घोषणा TEGRA114_CLK_SBC2 44
/* 45 */
#घोषणा TEGRA114_CLK_SBC3 46
#घोषणा TEGRA114_CLK_I2C5 47
#घोषणा TEGRA114_CLK_DSIA 48
/* 49 */
#घोषणा TEGRA114_CLK_MIPI 50
#घोषणा TEGRA114_CLK_HDMI 51
#घोषणा TEGRA114_CLK_CSI 52
/* 53 */
#घोषणा TEGRA114_CLK_I2C2 54
#घोषणा TEGRA114_CLK_UARTC 55
#घोषणा TEGRA114_CLK_MIPI_CAL 56
#घोषणा TEGRA114_CLK_EMC 57
#घोषणा TEGRA114_CLK_USB2 58
#घोषणा TEGRA114_CLK_USB3 59
/* 60 */
#घोषणा TEGRA114_CLK_VDE 61
#घोषणा TEGRA114_CLK_BSEA 62
#घोषणा TEGRA114_CLK_BSEV 63

/* 64 */
#घोषणा TEGRA114_CLK_UARTD 65
/* 66 */
#घोषणा TEGRA114_CLK_I2C3 67
#घोषणा TEGRA114_CLK_SBC4 68
#घोषणा TEGRA114_CLK_SDMMC3 69
/* 70 */
#घोषणा TEGRA114_CLK_OWR 71
/* 72 */
#घोषणा TEGRA114_CLK_CSITE 73
/* 74 */
/* 75 */
#घोषणा TEGRA114_CLK_LA 76
#घोषणा TEGRA114_CLK_TRACE 77
#घोषणा TEGRA114_CLK_SOC_THERM 78
#घोषणा TEGRA114_CLK_DTV 79
#घोषणा TEGRA114_CLK_NDSPEED 80
#घोषणा TEGRA114_CLK_I2CSLOW 81
#घोषणा TEGRA114_CLK_DSIB 82
#घोषणा TEGRA114_CLK_TSEC 83
/* 84 */
/* 85 */
/* 86 */
/* 87 */
/* 88 */
#घोषणा TEGRA114_CLK_XUSB_HOST 89
/* 90 */
#घोषणा TEGRA114_CLK_MSENC 91
#घोषणा TEGRA114_CLK_CSUS 92
/* 93 */
/* 94 */
/* 95 (bit affects xusb_dev and xusb_dev_src) */

/* 96 */
/* 97 */
/* 98 */
#घोषणा TEGRA114_CLK_MSELECT 99
#घोषणा TEGRA114_CLK_TSENSOR 100
#घोषणा TEGRA114_CLK_I2S3 101
#घोषणा TEGRA114_CLK_I2S4 102
#घोषणा TEGRA114_CLK_I2C4 103
#घोषणा TEGRA114_CLK_SBC5 104
#घोषणा TEGRA114_CLK_SBC6 105
#घोषणा TEGRA114_CLK_D_AUDIO 106
#घोषणा TEGRA114_CLK_APBIF 107
#घोषणा TEGRA114_CLK_DAM0 108
#घोषणा TEGRA114_CLK_DAM1 109
#घोषणा TEGRA114_CLK_DAM2 110
#घोषणा TEGRA114_CLK_HDA2CODEC_2X 111
/* 112 */
#घोषणा TEGRA114_CLK_AUDIO0_2X 113
#घोषणा TEGRA114_CLK_AUDIO1_2X 114
#घोषणा TEGRA114_CLK_AUDIO2_2X 115
#घोषणा TEGRA114_CLK_AUDIO3_2X 116
#घोषणा TEGRA114_CLK_AUDIO4_2X 117
#घोषणा TEGRA114_CLK_SPDIF_2X 118
#घोषणा TEGRA114_CLK_ACTMON 119
#घोषणा TEGRA114_CLK_EXTERN1 120
#घोषणा TEGRA114_CLK_EXTERN2 121
#घोषणा TEGRA114_CLK_EXTERN3 122
/* 123 */
/* 124 */
#घोषणा TEGRA114_CLK_HDA 125
/* 126 */
#घोषणा TEGRA114_CLK_SE 127

#घोषणा TEGRA114_CLK_HDA2HDMI 128
/* 129 */
/* 130 */
/* 131 */
/* 132 */
/* 133 */
/* 134 */
/* 135 */
#घोषणा TEGRA114_CLK_CEC 136
/* 137 */
/* 138 */
/* 139 */
/* 140 */
/* 141 */
/* 142 */
/* 143 (bit affects xusb_falcon_src, xusb_fs_src, */
/*      xusb_host_src and xusb_ss_src) */
#घोषणा TEGRA114_CLK_CILAB 144
#घोषणा TEGRA114_CLK_CILCD 145
#घोषणा TEGRA114_CLK_CILE 146
#घोषणा TEGRA114_CLK_DSIALP 147
#घोषणा TEGRA114_CLK_DSIBLP 148
/* 149 */
#घोषणा TEGRA114_CLK_DDS 150
/* 151 */
#घोषणा TEGRA114_CLK_DP2 152
#घोषणा TEGRA114_CLK_AMX 153
#घोषणा TEGRA114_CLK_ADX 154
/* 155 (bit affects dfll_ref and dfll_soc) */
#घोषणा TEGRA114_CLK_XUSB_SS 156
/* 157 */
/* 158 */
/* 159 */

/* 160 */
/* 161 */
/* 162 */
/* 163 */
/* 164 */
/* 165 */
/* 166 */
/* 167 */
/* 168 */
/* 169 */
/* 170 */
/* 171 */
/* 172 */
/* 173 */
/* 174 */
/* 175 */
/* 176 */
/* 177 */
/* 178 */
/* 179 */
/* 180 */
/* 181 */
/* 182 */
/* 183 */
/* 184 */
/* 185 */
/* 186 */
/* 187 */
/* 188 */
/* 189 */
/* 190 */
/* 191 */

#घोषणा TEGRA114_CLK_UARTB 192
#घोषणा TEGRA114_CLK_VFIR 193
#घोषणा TEGRA114_CLK_SPDIF_IN 194
#घोषणा TEGRA114_CLK_SPDIF_OUT 195
#घोषणा TEGRA114_CLK_VI 196
#घोषणा TEGRA114_CLK_VI_SENSOR 197
#घोषणा TEGRA114_CLK_FUSE 198
#घोषणा TEGRA114_CLK_FUSE_BURN 199
#घोषणा TEGRA114_CLK_CLK_32K 200
#घोषणा TEGRA114_CLK_CLK_M 201
#घोषणा TEGRA114_CLK_CLK_M_DIV2 202
#घोषणा TEGRA114_CLK_CLK_M_DIV4 203
#घोषणा TEGRA114_CLK_OSC_DIV2 202
#घोषणा TEGRA114_CLK_OSC_DIV4 203
#घोषणा TEGRA114_CLK_PLL_REF 204
#घोषणा TEGRA114_CLK_PLL_C 205
#घोषणा TEGRA114_CLK_PLL_C_OUT1 206
#घोषणा TEGRA114_CLK_PLL_C2 207
#घोषणा TEGRA114_CLK_PLL_C3 208
#घोषणा TEGRA114_CLK_PLL_M 209
#घोषणा TEGRA114_CLK_PLL_M_OUT1 210
#घोषणा TEGRA114_CLK_PLL_P 211
#घोषणा TEGRA114_CLK_PLL_P_OUT1 212
#घोषणा TEGRA114_CLK_PLL_P_OUT2 213
#घोषणा TEGRA114_CLK_PLL_P_OUT3 214
#घोषणा TEGRA114_CLK_PLL_P_OUT4 215
#घोषणा TEGRA114_CLK_PLL_A 216
#घोषणा TEGRA114_CLK_PLL_A_OUT0 217
#घोषणा TEGRA114_CLK_PLL_D 218
#घोषणा TEGRA114_CLK_PLL_D_OUT0 219
#घोषणा TEGRA114_CLK_PLL_D2 220
#घोषणा TEGRA114_CLK_PLL_D2_OUT0 221
#घोषणा TEGRA114_CLK_PLL_U 222
#घोषणा TEGRA114_CLK_PLL_U_480M 223

#घोषणा TEGRA114_CLK_PLL_U_60M 224
#घोषणा TEGRA114_CLK_PLL_U_48M 225
#घोषणा TEGRA114_CLK_PLL_U_12M 226
#घोषणा TEGRA114_CLK_PLL_X 227
#घोषणा TEGRA114_CLK_PLL_X_OUT0 228
#घोषणा TEGRA114_CLK_PLL_RE_VCO 229
#घोषणा TEGRA114_CLK_PLL_RE_OUT 230
#घोषणा TEGRA114_CLK_PLL_E_OUT0 231
#घोषणा TEGRA114_CLK_SPDIF_IN_SYNC 232
#घोषणा TEGRA114_CLK_I2S0_SYNC 233
#घोषणा TEGRA114_CLK_I2S1_SYNC 234
#घोषणा TEGRA114_CLK_I2S2_SYNC 235
#घोषणा TEGRA114_CLK_I2S3_SYNC 236
#घोषणा TEGRA114_CLK_I2S4_SYNC 237
#घोषणा TEGRA114_CLK_VIMCLK_SYNC 238
#घोषणा TEGRA114_CLK_AUDIO0 239
#घोषणा TEGRA114_CLK_AUDIO1 240
#घोषणा TEGRA114_CLK_AUDIO2 241
#घोषणा TEGRA114_CLK_AUDIO3 242
#घोषणा TEGRA114_CLK_AUDIO4 243
#घोषणा TEGRA114_CLK_SPDIF 244
/* 245 */
/* 246 */
/* 247 */
/* 248 */
#घोषणा TEGRA114_CLK_OSC 249
/* 250 */
/* 251 */
#घोषणा TEGRA114_CLK_XUSB_HOST_SRC 252
#घोषणा TEGRA114_CLK_XUSB_FALCON_SRC 253
#घोषणा TEGRA114_CLK_XUSB_FS_SRC 254
#घोषणा TEGRA114_CLK_XUSB_SS_SRC 255

#घोषणा TEGRA114_CLK_XUSB_DEV_SRC 256
#घोषणा TEGRA114_CLK_XUSB_DEV 257
#घोषणा TEGRA114_CLK_XUSB_HS_SRC 258
#घोषणा TEGRA114_CLK_SCLK 259
#घोषणा TEGRA114_CLK_HCLK 260
#घोषणा TEGRA114_CLK_PCLK 261
#घोषणा TEGRA114_CLK_CCLK_G 262
#घोषणा TEGRA114_CLK_CCLK_LP 263
#घोषणा TEGRA114_CLK_DFLL_REF 264
#घोषणा TEGRA114_CLK_DFLL_SOC 265
/* 266 */
/* 267 */
/* 268 */
/* 269 */
/* 270 */
/* 271 */
/* 272 */
/* 273 */
/* 274 */
/* 275 */
/* 276 */
/* 277 */
/* 278 */
/* 279 */
/* 280 */
/* 281 */
/* 282 */
/* 283 */
/* 284 */
/* 285 */
/* 286 */
/* 287 */

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
#घोषणा TEGRA114_CLK_AUDIO0_MUX 300
#घोषणा TEGRA114_CLK_AUDIO1_MUX 301
#घोषणा TEGRA114_CLK_AUDIO2_MUX 302
#घोषणा TEGRA114_CLK_AUDIO3_MUX 303
#घोषणा TEGRA114_CLK_AUDIO4_MUX 304
#घोषणा TEGRA114_CLK_SPDIF_MUX 305
/* 306 */
/* 307 */
/* 308 */
#घोषणा TEGRA114_CLK_DSIA_MUX 309
#घोषणा TEGRA114_CLK_DSIB_MUX 310
#घोषणा TEGRA114_CLK_XUSB_SS_DIV2 311
#घोषणा TEGRA114_CLK_CLK_MAX 312

#पूर्ण_अगर	/* _DT_BINDINGS_CLOCK_TEGRA114_CAR_H */
