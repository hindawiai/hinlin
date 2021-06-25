<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम binding nvidia,tegra210-car.
 *
 * The first 224 घड़ीs are numbered to match the bits in the CAR's CLK_OUT_ENB
 * रेजिस्टरs. These IDs often match those in the CAR's RST_DEVICES रेजिस्टरs,
 * but not in all हालs. Some bits in CLK_OUT_ENB affect multiple घड़ीs. In
 * this हाल, those घड़ीs are asचिन्हित IDs above 224 in order to highlight
 * this issue. Implementations that पूर्णांकerpret these घड़ी IDs as bit values
 * within the CLK_OUT_ENB or RST_DEVICES रेजिस्टरs should be careful to
 * explicitly handle these special हालs.
 *
 * The balance of the घड़ीs controlled by the CAR are asचिन्हित IDs of 224 and
 * above.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_TEGRA210_CAR_H
#घोषणा _DT_BINDINGS_CLOCK_TEGRA210_CAR_H

/* 0 */
/* 1 */
/* 2 */
#घोषणा TEGRA210_CLK_ISPB 3
#घोषणा TEGRA210_CLK_RTC 4
#घोषणा TEGRA210_CLK_TIMER 5
#घोषणा TEGRA210_CLK_UARTA 6
/* 7 (रेजिस्टर bit affects uartb and vfir) */
#घोषणा TEGRA210_CLK_GPIO 8
#घोषणा TEGRA210_CLK_SDMMC2 9
/* 10 (रेजिस्टर bit affects spdअगर_in and spdअगर_out) */
#घोषणा TEGRA210_CLK_I2S1 11
#घोषणा TEGRA210_CLK_I2C1 12
/* 13 */
#घोषणा TEGRA210_CLK_SDMMC1 14
#घोषणा TEGRA210_CLK_SDMMC4 15
/* 16 */
#घोषणा TEGRA210_CLK_PWM 17
#घोषणा TEGRA210_CLK_I2S2 18
/* 19 */
/* 20 (रेजिस्टर bit affects vi and vi_sensor) */
/* 21 */
#घोषणा TEGRA210_CLK_USBD 22
#घोषणा TEGRA210_CLK_ISPA 23
/* 24 */
/* 25 */
#घोषणा TEGRA210_CLK_DISP2 26
#घोषणा TEGRA210_CLK_DISP1 27
#घोषणा TEGRA210_CLK_HOST1X 28
/* 29 */
#घोषणा TEGRA210_CLK_I2S0 30
/* 31 */

#घोषणा TEGRA210_CLK_MC 32
#घोषणा TEGRA210_CLK_AHBDMA 33
#घोषणा TEGRA210_CLK_APBDMA 34
/* 35 */
/* 36 */
/* 37 */
#घोषणा TEGRA210_CLK_PMC 38
/* 39 (रेजिस्टर bit affects fuse and fuse_burn) */
#घोषणा TEGRA210_CLK_KFUSE 40
#घोषणा TEGRA210_CLK_SBC1 41
/* 42 */
/* 43 */
#घोषणा TEGRA210_CLK_SBC2 44
/* 45 */
#घोषणा TEGRA210_CLK_SBC3 46
#घोषणा TEGRA210_CLK_I2C5 47
#घोषणा TEGRA210_CLK_DSIA 48
/* 49 */
/* 50 */
/* 51 */
#घोषणा TEGRA210_CLK_CSI 52
/* 53 */
#घोषणा TEGRA210_CLK_I2C2 54
#घोषणा TEGRA210_CLK_UARTC 55
#घोषणा TEGRA210_CLK_MIPI_CAL 56
#घोषणा TEGRA210_CLK_EMC 57
#घोषणा TEGRA210_CLK_USB2 58
/* 59 */
/* 60 */
/* 61 */
/* 62 */
#घोषणा TEGRA210_CLK_BSEV 63

/* 64 */
#घोषणा TEGRA210_CLK_UARTD 65
/* 66 */
#घोषणा TEGRA210_CLK_I2C3 67
#घोषणा TEGRA210_CLK_SBC4 68
#घोषणा TEGRA210_CLK_SDMMC3 69
#घोषणा TEGRA210_CLK_PCIE 70
#घोषणा TEGRA210_CLK_OWR 71
#घोषणा TEGRA210_CLK_AFI 72
#घोषणा TEGRA210_CLK_CSITE 73
/* 74 */
/* 75 */
#घोषणा TEGRA210_CLK_LA 76
/* 77 */
#घोषणा TEGRA210_CLK_SOC_THERM 78
#घोषणा TEGRA210_CLK_DTV 79
/* 80 */
#घोषणा TEGRA210_CLK_I2CSLOW 81
#घोषणा TEGRA210_CLK_DSIB 82
#घोषणा TEGRA210_CLK_TSEC 83
/* 84 */
/* 85 */
/* 86 */
/* 87 */
/* 88 */
#घोषणा TEGRA210_CLK_XUSB_HOST 89
/* 90 */
/* 91 */
#घोषणा TEGRA210_CLK_CSUS 92
/* 93 */
/* 94 */
/* 95 (bit affects xusb_dev and xusb_dev_src) */

/* 96 */
/* 97 */
/* 98 */
#घोषणा TEGRA210_CLK_MSELECT 99
#घोषणा TEGRA210_CLK_TSENSOR 100
#घोषणा TEGRA210_CLK_I2S3 101
#घोषणा TEGRA210_CLK_I2S4 102
#घोषणा TEGRA210_CLK_I2C4 103
/* 104 */
/* 105 */
#घोषणा TEGRA210_CLK_D_AUDIO 106
#घोषणा TEGRA210_CLK_APB2APE 107
/* 108 */
/* 109 */
/* 110 */
#घोषणा TEGRA210_CLK_HDA2CODEC_2X 111
/* 112 */
/* 113 */
/* 114 */
/* 115 */
/* 116 */
/* 117 */
#घोषणा TEGRA210_CLK_SPDIF_2X 118
#घोषणा TEGRA210_CLK_ACTMON 119
#घोषणा TEGRA210_CLK_EXTERN1 120
#घोषणा TEGRA210_CLK_EXTERN2 121
#घोषणा TEGRA210_CLK_EXTERN3 122
#घोषणा TEGRA210_CLK_SATA_OOB 123
#घोषणा TEGRA210_CLK_SATA 124
#घोषणा TEGRA210_CLK_HDA 125
/* 126 */
/* 127 */

#घोषणा TEGRA210_CLK_HDA2HDMI 128
/* 129 */
/* 130 */
/* 131 */
/* 132 */
/* 133 */
/* 134 */
/* 135 */
#घोषणा TEGRA210_CLK_CEC 136
/* 137 */
/* 138 */
/* 139 */
/* 140 */
/* 141 */
/* 142 */
/* (bit affects xusb_falcon_src, xusb_fs_src, xusb_host_src and xusb_ss_src) */
#घोषणा TEGRA210_CLK_XUSB_GATE 143
#घोषणा TEGRA210_CLK_CILAB 144
#घोषणा TEGRA210_CLK_CILCD 145
#घोषणा TEGRA210_CLK_CILE 146
#घोषणा TEGRA210_CLK_DSIALP 147
#घोषणा TEGRA210_CLK_DSIBLP 148
#घोषणा TEGRA210_CLK_ENTROPY 149
/* 150 */
/* 151 */
#घोषणा TEGRA210_CLK_DP2 152
/* 153 */
/* 154 */
/* 155 (bit affects dfll_ref and dfll_soc) */
#घोषणा TEGRA210_CLK_XUSB_SS 156
/* 157 */
/* 158 */
/* 159 */

/* 160 */
#घोषणा TEGRA210_CLK_DMIC1 161
#घोषणा TEGRA210_CLK_DMIC2 162
/* 163 */
/* 164 */
/* 165 */
#घोषणा TEGRA210_CLK_I2C6 166
/* 167 */
/* 168 */
/* 169 */
/* 170 */
#घोषणा TEGRA210_CLK_VIM2_CLK 171
/* 172 */
#घोषणा TEGRA210_CLK_MIPIBIF 173
/* 174 */
/* 175 */
/* 176 */
#घोषणा TEGRA210_CLK_CLK72MHZ 177
#घोषणा TEGRA210_CLK_VIC03 178
/* 179 */
/* 180 */
#घोषणा TEGRA210_CLK_DPAUX 181
#घोषणा TEGRA210_CLK_SOR0 182
#घोषणा TEGRA210_CLK_SOR1 183
#घोषणा TEGRA210_CLK_GPU 184
#घोषणा TEGRA210_CLK_DBGAPB 185
/* 186 */
#घोषणा TEGRA210_CLK_PLL_P_OUT_ADSP 187
/* 188 ((bit affects pll_a_out_adsp and pll_a_out0_out_adsp)*/
#घोषणा TEGRA210_CLK_PLL_G_REF 189
/* 190 */
/* 191 */

/* 192 */
#घोषणा TEGRA210_CLK_SDMMC_LEGACY 193
#घोषणा TEGRA210_CLK_NVDEC 194
#घोषणा TEGRA210_CLK_NVJPG 195
/* 196 */
#घोषणा TEGRA210_CLK_DMIC3 197
#घोषणा TEGRA210_CLK_APE 198
#घोषणा TEGRA210_CLK_ADSP 199
/* 200 */
/* 201 */
#घोषणा TEGRA210_CLK_MAUD 202
/* 203 */
/* 204 */
/* 205 */
#घोषणा TEGRA210_CLK_TSECB 206
#घोषणा TEGRA210_CLK_DPAUX1 207
#घोषणा TEGRA210_CLK_VI_I2C 208
#घोषणा TEGRA210_CLK_HSIC_TRK 209
#घोषणा TEGRA210_CLK_USB2_TRK 210
#घोषणा TEGRA210_CLK_QSPI 211
#घोषणा TEGRA210_CLK_UARTAPE 212
/* 213 */
/* 214 */
/* 215 */
/* 216 */
/* 217 */
#घोषणा TEGRA210_CLK_ADSP_NEON 218
#घोषणा TEGRA210_CLK_NVENC 219
#घोषणा TEGRA210_CLK_IQC2 220
#घोषणा TEGRA210_CLK_IQC1 221
#घोषणा TEGRA210_CLK_SOR_SAFE 222
#घोषणा TEGRA210_CLK_PLL_P_OUT_CPU 223


#घोषणा TEGRA210_CLK_UARTB 224
#घोषणा TEGRA210_CLK_VFIR 225
#घोषणा TEGRA210_CLK_SPDIF_IN 226
#घोषणा TEGRA210_CLK_SPDIF_OUT 227
#घोषणा TEGRA210_CLK_VI 228
#घोषणा TEGRA210_CLK_VI_SENSOR 229
#घोषणा TEGRA210_CLK_FUSE 230
#घोषणा TEGRA210_CLK_FUSE_BURN 231
#घोषणा TEGRA210_CLK_CLK_32K 232
#घोषणा TEGRA210_CLK_CLK_M 233
#घोषणा TEGRA210_CLK_CLK_M_DIV2 234
#घोषणा TEGRA210_CLK_CLK_M_DIV4 235
#घोषणा TEGRA210_CLK_OSC_DIV2 234
#घोषणा TEGRA210_CLK_OSC_DIV4 235
#घोषणा TEGRA210_CLK_PLL_REF 236
#घोषणा TEGRA210_CLK_PLL_C 237
#घोषणा TEGRA210_CLK_PLL_C_OUT1 238
#घोषणा TEGRA210_CLK_PLL_C2 239
#घोषणा TEGRA210_CLK_PLL_C3 240
#घोषणा TEGRA210_CLK_PLL_M 241
#घोषणा TEGRA210_CLK_PLL_M_OUT1 242
#घोषणा TEGRA210_CLK_PLL_P 243
#घोषणा TEGRA210_CLK_PLL_P_OUT1 244
#घोषणा TEGRA210_CLK_PLL_P_OUT2 245
#घोषणा TEGRA210_CLK_PLL_P_OUT3 246
#घोषणा TEGRA210_CLK_PLL_P_OUT4 247
#घोषणा TEGRA210_CLK_PLL_A 248
#घोषणा TEGRA210_CLK_PLL_A_OUT0 249
#घोषणा TEGRA210_CLK_PLL_D 250
#घोषणा TEGRA210_CLK_PLL_D_OUT0 251
#घोषणा TEGRA210_CLK_PLL_D2 252
#घोषणा TEGRA210_CLK_PLL_D2_OUT0 253
#घोषणा TEGRA210_CLK_PLL_U 254
#घोषणा TEGRA210_CLK_PLL_U_480M 255

#घोषणा TEGRA210_CLK_PLL_U_60M 256
#घोषणा TEGRA210_CLK_PLL_U_48M 257
/* 258 */
#घोषणा TEGRA210_CLK_PLL_X 259
#घोषणा TEGRA210_CLK_PLL_X_OUT0 260
#घोषणा TEGRA210_CLK_PLL_RE_VCO 261
#घोषणा TEGRA210_CLK_PLL_RE_OUT 262
#घोषणा TEGRA210_CLK_PLL_E 263
#घोषणा TEGRA210_CLK_SPDIF_IN_SYNC 264
#घोषणा TEGRA210_CLK_I2S0_SYNC 265
#घोषणा TEGRA210_CLK_I2S1_SYNC 266
#घोषणा TEGRA210_CLK_I2S2_SYNC 267
#घोषणा TEGRA210_CLK_I2S3_SYNC 268
#घोषणा TEGRA210_CLK_I2S4_SYNC 269
#घोषणा TEGRA210_CLK_VIMCLK_SYNC 270
#घोषणा TEGRA210_CLK_AUDIO0 271
#घोषणा TEGRA210_CLK_AUDIO1 272
#घोषणा TEGRA210_CLK_AUDIO2 273
#घोषणा TEGRA210_CLK_AUDIO3 274
#घोषणा TEGRA210_CLK_AUDIO4 275
#घोषणा TEGRA210_CLK_SPDIF 276
/* 277 */
#घोषणा TEGRA210_CLK_QSPI_PM 278
/* 279 */
/* 280 */
#घोषणा TEGRA210_CLK_SOR0_LVDS 281 /* deprecated */
#घोषणा TEGRA210_CLK_SOR0_OUT 281
#घोषणा TEGRA210_CLK_SOR1_OUT 282
/* 283 */
#घोषणा TEGRA210_CLK_XUSB_HOST_SRC 284
#घोषणा TEGRA210_CLK_XUSB_FALCON_SRC 285
#घोषणा TEGRA210_CLK_XUSB_FS_SRC 286
#घोषणा TEGRA210_CLK_XUSB_SS_SRC 287

#घोषणा TEGRA210_CLK_XUSB_DEV_SRC 288
#घोषणा TEGRA210_CLK_XUSB_DEV 289
#घोषणा TEGRA210_CLK_XUSB_HS_SRC 290
#घोषणा TEGRA210_CLK_SCLK 291
#घोषणा TEGRA210_CLK_HCLK 292
#घोषणा TEGRA210_CLK_PCLK 293
#घोषणा TEGRA210_CLK_CCLK_G 294
#घोषणा TEGRA210_CLK_CCLK_LP 295
#घोषणा TEGRA210_CLK_DFLL_REF 296
#घोषणा TEGRA210_CLK_DFLL_SOC 297
#घोषणा TEGRA210_CLK_VI_SENSOR2 298
#घोषणा TEGRA210_CLK_PLL_P_OUT5 299
#घोषणा TEGRA210_CLK_CML0 300
#घोषणा TEGRA210_CLK_CML1 301
#घोषणा TEGRA210_CLK_PLL_C4 302
#घोषणा TEGRA210_CLK_PLL_DP 303
#घोषणा TEGRA210_CLK_PLL_E_MUX 304
#घोषणा TEGRA210_CLK_PLL_MB 305
#घोषणा TEGRA210_CLK_PLL_A1 306
#घोषणा TEGRA210_CLK_PLL_D_DSI_OUT 307
#घोषणा TEGRA210_CLK_PLL_C4_OUT0 308
#घोषणा TEGRA210_CLK_PLL_C4_OUT1 309
#घोषणा TEGRA210_CLK_PLL_C4_OUT2 310
#घोषणा TEGRA210_CLK_PLL_C4_OUT3 311
#घोषणा TEGRA210_CLK_PLL_U_OUT 312
#घोषणा TEGRA210_CLK_PLL_U_OUT1 313
#घोषणा TEGRA210_CLK_PLL_U_OUT2 314
#घोषणा TEGRA210_CLK_USB2_HSIC_TRK 315
#घोषणा TEGRA210_CLK_PLL_P_OUT_HSIO 316
#घोषणा TEGRA210_CLK_PLL_P_OUT_XUSB 317
#घोषणा TEGRA210_CLK_XUSB_SSP_SRC 318
#घोषणा TEGRA210_CLK_PLL_RE_OUT1 319
#घोषणा TEGRA210_CLK_PLL_MB_UD 320
#घोषणा TEGRA210_CLK_PLL_P_UD 321
#घोषणा TEGRA210_CLK_ISP 322
#घोषणा TEGRA210_CLK_PLL_A_OUT_ADSP 323
#घोषणा TEGRA210_CLK_PLL_A_OUT0_OUT_ADSP 324
/* 325 */
#घोषणा TEGRA210_CLK_OSC 326
#घोषणा TEGRA210_CLK_CSI_TPG 327
/* 328 */
/* 329 */
/* 330 */
/* 331 */
/* 332 */
/* 333 */
/* 334 */
/* 335 */
/* 336 */
/* 337 */
/* 338 */
/* 339 */
/* 340 */
/* 341 */
/* 342 */
/* 343 */
/* 344 */
/* 345 */
/* 346 */
/* 347 */
/* 348 */
/* 349 */

#घोषणा TEGRA210_CLK_AUDIO0_MUX 350
#घोषणा TEGRA210_CLK_AUDIO1_MUX 351
#घोषणा TEGRA210_CLK_AUDIO2_MUX 352
#घोषणा TEGRA210_CLK_AUDIO3_MUX 353
#घोषणा TEGRA210_CLK_AUDIO4_MUX 354
#घोषणा TEGRA210_CLK_SPDIF_MUX 355
/* 356 */
/* 357 */
/* 358 */
#घोषणा TEGRA210_CLK_DSIA_MUX 359
#घोषणा TEGRA210_CLK_DSIB_MUX 360
/* 361 */
#घोषणा TEGRA210_CLK_XUSB_SS_DIV2 362

#घोषणा TEGRA210_CLK_PLL_M_UD 363
#घोषणा TEGRA210_CLK_PLL_C_UD 364
#घोषणा TEGRA210_CLK_SCLK_MUX 365

#घोषणा TEGRA210_CLK_ACLK 370

#घोषणा TEGRA210_CLK_DMIC1_SYNC_CLK 388
#घोषणा TEGRA210_CLK_DMIC1_SYNC_CLK_MUX 389
#घोषणा TEGRA210_CLK_DMIC2_SYNC_CLK 390
#घोषणा TEGRA210_CLK_DMIC2_SYNC_CLK_MUX 391
#घोषणा TEGRA210_CLK_DMIC3_SYNC_CLK 392
#घोषणा TEGRA210_CLK_DMIC3_SYNC_CLK_MUX 393

#घोषणा TEGRA210_CLK_CLK_MAX 394

#पूर्ण_अगर	/* _DT_BINDINGS_CLOCK_TEGRA210_CAR_H */
