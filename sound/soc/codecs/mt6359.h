<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 MediaTek Inc.
 * Author: Argus Lin <argus.lin@mediatek.com>
 */

#अगर_अघोषित _MT6359_H_
#घोषणा _MT6359_H_

/*************Register Bit Define*************/
#घोषणा MT6359_TOP0_ID                       0x0
#घोषणा MT6359_SMT_CON1                      0x32
#घोषणा MT6359_DRV_CON2                      0x3c
#घोषणा MT6359_DRV_CON3                      0x3e
#घोषणा MT6359_DRV_CON4                      0x40
#घोषणा MT6359_TOP_CKPDN_CON0                0x10c
#घोषणा MT6359_TOP_CKPDN_CON0_SET            0x10e
#घोषणा MT6359_TOP_CKPDN_CON0_CLR            0x110
#घोषणा MT6359_AUXADC_RQST0                  0x1108
#घोषणा MT6359_AUXADC_CON10                  0x11a0
#घोषणा MT6359_AUXADC_ACCDET                 0x11ba
#घोषणा MT6359_LDO_VUSB_OP_EN                0x1d0c
#घोषणा MT6359_LDO_VUSB_OP_EN_SET            0x1d0e
#घोषणा MT6359_LDO_VUSB_OP_EN_CLR            0x1d10
#घोषणा MT6359_AUD_TOP_CKPDN_CON0            0x230c
#घोषणा MT6359_AUD_TOP_CKPDN_CON0_SET        0x230e
#घोषणा MT6359_AUD_TOP_CKPDN_CON0_CLR        0x2310
#घोषणा MT6359_AUD_TOP_RST_CON0              0x2320
#घोषणा MT6359_AUD_TOP_RST_CON0_SET          0x2322
#घोषणा MT6359_AUD_TOP_RST_CON0_CLR          0x2324
#घोषणा MT6359_AUD_TOP_INT_CON0              0x2328
#घोषणा MT6359_AUD_TOP_INT_CON0_SET          0x232a
#घोषणा MT6359_AUD_TOP_INT_CON0_CLR          0x232c
#घोषणा MT6359_AUD_TOP_INT_MASK_CON0         0x232e
#घोषणा MT6359_AUD_TOP_INT_MASK_CON0_SET     0x2330
#घोषणा MT6359_AUD_TOP_INT_MASK_CON0_CLR     0x2332
#घोषणा MT6359_AUD_TOP_INT_STATUS0           0x2334
#घोषणा MT6359_AFE_NCP_CFG2                  0x24e2
#घोषणा MT6359_AUDENC_DSN_ID                 0x2500
#घोषणा MT6359_AUDENC_DSN_REV0               0x2502
#घोषणा MT6359_AUDENC_DSN_DBI                0x2504
#घोषणा MT6359_AUDENC_DSN_FPI                0x2506
#घोषणा MT6359_AUDENC_ANA_CON0               0x2508
#घोषणा MT6359_AUDENC_ANA_CON1               0x250a
#घोषणा MT6359_AUDENC_ANA_CON2               0x250c
#घोषणा MT6359_AUDENC_ANA_CON3               0x250e
#घोषणा MT6359_AUDENC_ANA_CON4               0x2510
#घोषणा MT6359_AUDENC_ANA_CON5               0x2512
#घोषणा MT6359_AUDENC_ANA_CON6               0x2514
#घोषणा MT6359_AUDENC_ANA_CON7               0x2516
#घोषणा MT6359_AUDENC_ANA_CON8               0x2518
#घोषणा MT6359_AUDENC_ANA_CON9               0x251a
#घोषणा MT6359_AUDENC_ANA_CON10              0x251c
#घोषणा MT6359_AUDENC_ANA_CON11              0x251e
#घोषणा MT6359_AUDENC_ANA_CON12              0x2520
#घोषणा MT6359_AUDENC_ANA_CON13              0x2522
#घोषणा MT6359_AUDENC_ANA_CON14              0x2524
#घोषणा MT6359_AUDENC_ANA_CON15              0x2526
#घोषणा MT6359_AUDENC_ANA_CON16              0x2528
#घोषणा MT6359_AUDENC_ANA_CON17              0x252a
#घोषणा MT6359_AUDENC_ANA_CON18              0x252c
#घोषणा MT6359_AUDENC_ANA_CON19              0x252e
#घोषणा MT6359_AUDENC_ANA_CON20              0x2530
#घोषणा MT6359_AUDENC_ANA_CON21              0x2532
#घोषणा MT6359_AUDENC_ANA_CON22              0x2534
#घोषणा MT6359_AUDENC_ANA_CON23              0x2536
#घोषणा MT6359_AUDDEC_DSN_ID                 0x2580
#घोषणा MT6359_AUDDEC_DSN_REV0               0x2582
#घोषणा MT6359_AUDDEC_DSN_DBI                0x2584
#घोषणा MT6359_AUDDEC_DSN_FPI                0x2586
#घोषणा MT6359_AUDDEC_ANA_CON0               0x2588
#घोषणा MT6359_AUDDEC_ANA_CON1               0x258a
#घोषणा MT6359_AUDDEC_ANA_CON2               0x258c
#घोषणा MT6359_AUDDEC_ANA_CON3               0x258e
#घोषणा MT6359_AUDDEC_ANA_CON4               0x2590
#घोषणा MT6359_AUDDEC_ANA_CON5               0x2592
#घोषणा MT6359_AUDDEC_ANA_CON6               0x2594
#घोषणा MT6359_AUDDEC_ANA_CON7               0x2596
#घोषणा MT6359_AUDDEC_ANA_CON8               0x2598
#घोषणा MT6359_AUDDEC_ANA_CON9               0x259a
#घोषणा MT6359_AUDDEC_ANA_CON10              0x259c
#घोषणा MT6359_AUDDEC_ANA_CON11              0x259e
#घोषणा MT6359_AUDDEC_ANA_CON12              0x25a0
#घोषणा MT6359_AUDDEC_ANA_CON13              0x25a2
#घोषणा MT6359_AUDDEC_ANA_CON14              0x25a4
#घोषणा MT6359_ACCDET_DSN_DIG_ID             0x2680
#घोषणा MT6359_ACCDET_DSN_DIG_REV0           0x2682
#घोषणा MT6359_ACCDET_DSN_DBI                0x2684
#घोषणा MT6359_ACCDET_DSN_FPI                0x2686
#घोषणा MT6359_ACCDET_CON0                   0x2688
#घोषणा MT6359_ACCDET_CON1                   0x268a
#घोषणा MT6359_ACCDET_CON2                   0x268c
#घोषणा MT6359_ACCDET_CON3                   0x268e
#घोषणा MT6359_ACCDET_CON4                   0x2690
#घोषणा MT6359_ACCDET_CON5                   0x2692
#घोषणा MT6359_ACCDET_CON6                   0x2694
#घोषणा MT6359_ACCDET_CON7                   0x2696
#घोषणा MT6359_ACCDET_CON8                   0x2698
#घोषणा MT6359_ACCDET_CON9                   0x269a
#घोषणा MT6359_ACCDET_CON10                  0x269c
#घोषणा MT6359_ACCDET_CON11                  0x269e
#घोषणा MT6359_ACCDET_CON12                  0x26a0
#घोषणा MT6359_ACCDET_CON13                  0x26a2
#घोषणा MT6359_ACCDET_CON14                  0x26a4
#घोषणा MT6359_ACCDET_CON15                  0x26a6
#घोषणा MT6359_ACCDET_CON16                  0x26a8
#घोषणा MT6359_ACCDET_CON17                  0x26aa
#घोषणा MT6359_ACCDET_CON18                  0x26ac
#घोषणा MT6359_ACCDET_CON19                  0x26ae
#घोषणा MT6359_ACCDET_CON20                  0x26b0
#घोषणा MT6359_ACCDET_CON21                  0x26b2
#घोषणा MT6359_ACCDET_CON22                  0x26b4
#घोषणा MT6359_ACCDET_CON23                  0x26b6
#घोषणा MT6359_ACCDET_CON24                  0x26b8
#घोषणा MT6359_ACCDET_CON25                  0x26ba
#घोषणा MT6359_ACCDET_CON26                  0x26bc
#घोषणा MT6359_ACCDET_CON27                  0x26be
#घोषणा MT6359_ACCDET_CON28                  0x26c0
#घोषणा MT6359_ACCDET_CON29                  0x26c2
#घोषणा MT6359_ACCDET_CON30                  0x26c4
#घोषणा MT6359_ACCDET_CON31                  0x26c6
#घोषणा MT6359_ACCDET_CON32                  0x26c8
#घोषणा MT6359_ACCDET_CON33                  0x26ca
#घोषणा MT6359_ACCDET_CON34                  0x26cc
#घोषणा MT6359_ACCDET_CON35                  0x26ce
#घोषणा MT6359_ACCDET_CON36                  0x26d0
#घोषणा MT6359_ACCDET_CON37                  0x26d2
#घोषणा MT6359_ACCDET_CON38                  0x26d4
#घोषणा MT6359_ACCDET_CON39                  0x26d6
#घोषणा MT6359_ACCDET_CON40                  0x26d8

#घोषणा TOP0_ANA_ID_ADDR                               \
	MT6359_TOP0_ID
#घोषणा TOP0_ANA_ID_SFT                                0
#घोषणा TOP0_ANA_ID_MASK                               0xFF
#घोषणा TOP0_ANA_ID_MASK_SFT                           (0xFF << 0)
#घोषणा AUXADC_RQST_CH0_ADDR                           \
	MT6359_AUXADC_RQST0
#घोषणा AUXADC_RQST_CH0_SFT                            0
#घोषणा AUXADC_RQST_CH0_MASK                           0x1
#घोषणा AUXADC_RQST_CH0_MASK_SFT                       (0x1 << 0)
#घोषणा AUXADC_ACCDET_ANASWCTRL_EN_ADDR                \
	MT6359_AUXADC_CON15
#घोषणा AUXADC_ACCDET_ANASWCTRL_EN_SFT                 6
#घोषणा AUXADC_ACCDET_ANASWCTRL_EN_MASK                0x1
#घोषणा AUXADC_ACCDET_ANASWCTRL_EN_MASK_SFT            (0x1 << 6)

#घोषणा AUXADC_ACCDET_AUTO_SPL_ADDR                    \
	MT6359_AUXADC_ACCDET
#घोषणा AUXADC_ACCDET_AUTO_SPL_SFT                     0
#घोषणा AUXADC_ACCDET_AUTO_SPL_MASK                    0x1
#घोषणा AUXADC_ACCDET_AUTO_SPL_MASK_SFT                (0x1 << 0)
#घोषणा AUXADC_ACCDET_AUTO_RQST_CLR_ADDR               \
	MT6359_AUXADC_ACCDET
#घोषणा AUXADC_ACCDET_AUTO_RQST_CLR_SFT                1
#घोषणा AUXADC_ACCDET_AUTO_RQST_CLR_MASK               0x1
#घोषणा AUXADC_ACCDET_AUTO_RQST_CLR_MASK_SFT           (0x1 << 1)
#घोषणा AUXADC_ACCDET_DIG1_RSV0_ADDR                   \
	MT6359_AUXADC_ACCDET
#घोषणा AUXADC_ACCDET_DIG1_RSV0_SFT                    2
#घोषणा AUXADC_ACCDET_DIG1_RSV0_MASK                   0x3F
#घोषणा AUXADC_ACCDET_DIG1_RSV0_MASK_SFT               (0x3F << 2)
#घोषणा AUXADC_ACCDET_DIG0_RSV0_ADDR                   \
	MT6359_AUXADC_ACCDET
#घोषणा AUXADC_ACCDET_DIG0_RSV0_SFT                    8
#घोषणा AUXADC_ACCDET_DIG0_RSV0_MASK                   0xFF
#घोषणा AUXADC_ACCDET_DIG0_RSV0_MASK_SFT               (0xFF << 8)

#घोषणा RG_ACCDET_CK_PDN_ADDR                          \
	MT6359_AUD_TOP_CKPDN_CON0
#घोषणा RG_ACCDET_CK_PDN_SFT                           0
#घोषणा RG_ACCDET_CK_PDN_MASK                          0x1
#घोषणा RG_ACCDET_CK_PDN_MASK_SFT                      (0x1 << 0)

#घोषणा RG_ACCDET_RST_ADDR                             \
	MT6359_AUD_TOP_RST_CON0
#घोषणा RG_ACCDET_RST_SFT                              1
#घोषणा RG_ACCDET_RST_MASK                             0x1
#घोषणा RG_ACCDET_RST_MASK_SFT                         (0x1 << 1)
#घोषणा BANK_ACCDET_SWRST_ADDR                         \
	MT6359_AUD_TOP_RST_BANK_CON0
#घोषणा BANK_ACCDET_SWRST_SFT                          0
#घोषणा BANK_ACCDET_SWRST_MASK                         0x1
#घोषणा BANK_ACCDET_SWRST_MASK_SFT                     (0x1 << 0)

#घोषणा RG_INT_EN_ACCDET_ADDR                          \
	MT6359_AUD_TOP_INT_CON0
#घोषणा RG_INT_EN_ACCDET_SFT                           5
#घोषणा RG_INT_EN_ACCDET_MASK                          0x1
#घोषणा RG_INT_EN_ACCDET_MASK_SFT                      (0x1 << 5)
#घोषणा RG_INT_EN_ACCDET_EINT0_ADDR                    \
	MT6359_AUD_TOP_INT_CON0
#घोषणा RG_INT_EN_ACCDET_EINT0_SFT                     6
#घोषणा RG_INT_EN_ACCDET_EINT0_MASK                    0x1
#घोषणा RG_INT_EN_ACCDET_EINT0_MASK_SFT                (0x1 << 6)
#घोषणा RG_INT_EN_ACCDET_EINT1_ADDR                    \
	MT6359_AUD_TOP_INT_CON0
#घोषणा RG_INT_EN_ACCDET_EINT1_SFT                     7
#घोषणा RG_INT_EN_ACCDET_EINT1_MASK                    0x1
#घोषणा RG_INT_EN_ACCDET_EINT1_MASK_SFT                (0x1 << 7)

#घोषणा RG_INT_MASK_ACCDET_ADDR                        \
	MT6359_AUD_TOP_INT_MASK_CON0
#घोषणा RG_INT_MASK_ACCDET_SFT                         5
#घोषणा RG_INT_MASK_ACCDET_MASK                        0x1
#घोषणा RG_INT_MASK_ACCDET_MASK_SFT                    (0x1 << 5)
#घोषणा RG_INT_MASK_ACCDET_EINT0_ADDR                  \
	MT6359_AUD_TOP_INT_MASK_CON0
#घोषणा RG_INT_MASK_ACCDET_EINT0_SFT                   6
#घोषणा RG_INT_MASK_ACCDET_EINT0_MASK                  0x1
#घोषणा RG_INT_MASK_ACCDET_EINT0_MASK_SFT              (0x1 << 6)
#घोषणा RG_INT_MASK_ACCDET_EINT1_ADDR                  \
	MT6359_AUD_TOP_INT_MASK_CON0
#घोषणा RG_INT_MASK_ACCDET_EINT1_SFT                   7
#घोषणा RG_INT_MASK_ACCDET_EINT1_MASK                  0x1
#घोषणा RG_INT_MASK_ACCDET_EINT1_MASK_SFT              (0x1 << 7)

#घोषणा RG_INT_STATUS_ACCDET_ADDR                      \
	MT6359_AUD_TOP_INT_STATUS0
#घोषणा RG_INT_STATUS_ACCDET_SFT                       5
#घोषणा RG_INT_STATUS_ACCDET_MASK                      0x1
#घोषणा RG_INT_STATUS_ACCDET_MASK_SFT                  (0x1 << 5)
#घोषणा RG_INT_STATUS_ACCDET_EINT0_ADDR                \
	MT6359_AUD_TOP_INT_STATUS0
#घोषणा RG_INT_STATUS_ACCDET_EINT0_SFT                 6
#घोषणा RG_INT_STATUS_ACCDET_EINT0_MASK                0x1
#घोषणा RG_INT_STATUS_ACCDET_EINT0_MASK_SFT            (0x1 << 6)
#घोषणा RG_INT_STATUS_ACCDET_EINT1_ADDR                \
	MT6359_AUD_TOP_INT_STATUS0
#घोषणा RG_INT_STATUS_ACCDET_EINT1_SFT                 7
#घोषणा RG_INT_STATUS_ACCDET_EINT1_MASK                0x1
#घोषणा RG_INT_STATUS_ACCDET_EINT1_MASK_SFT            (0x1 << 7)

#घोषणा RG_INT_RAW_STATUS_ACCDET_ADDR                  \
	MT6359_AUD_TOP_INT_RAW_STATUS0
#घोषणा RG_INT_RAW_STATUS_ACCDET_SFT                   5
#घोषणा RG_INT_RAW_STATUS_ACCDET_MASK                  0x1
#घोषणा RG_INT_RAW_STATUS_ACCDET_MASK_SFT              (0x1 << 5)
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT0_ADDR            \
	MT6359_AUD_TOP_INT_RAW_STATUS0
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT0_SFT             6
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT0_MASK            0x1
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT0_MASK_SFT        (0x1 << 6)
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT1_ADDR            \
	MT6359_AUD_TOP_INT_RAW_STATUS0
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT1_SFT             7
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT1_MASK            0x1
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT1_MASK_SFT        (0x1 << 7)

#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_ADDR               \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_SFT                0
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_MASK               0x1
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_MASK_SFT           (0x1 << 0)
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_ADDR               \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_SFT                1
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_MASK               0x1
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_MASK_SFT           (0x1 << 1)
#घोषणा RG_AUDACCDETMICBIAS2PULLLOW_ADDR               \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETMICBIAS2PULLLOW_SFT                2
#घोषणा RG_AUDACCDETMICBIAS2PULLLOW_MASK               0x1
#घोषणा RG_AUDACCDETMICBIAS2PULLLOW_MASK_SFT           (0x1 << 2)
#घोषणा RG_AUDACCDETVIN1PULLLOW_ADDR                   \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETVIN1PULLLOW_SFT                    3
#घोषणा RG_AUDACCDETVIN1PULLLOW_MASK                   0x1
#घोषणा RG_AUDACCDETVIN1PULLLOW_MASK_SFT               (0x1 << 3)
#घोषणा RG_AUDACCDETVTHACAL_ADDR                       \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETVTHACAL_SFT                        4
#घोषणा RG_AUDACCDETVTHACAL_MASK                       0x1
#घोषणा RG_AUDACCDETVTHACAL_MASK_SFT                   (0x1 << 4)
#घोषणा RG_AUDACCDETVTHBCAL_ADDR                       \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETVTHBCAL_SFT                        5
#घोषणा RG_AUDACCDETVTHBCAL_MASK                       0x1
#घोषणा RG_AUDACCDETVTHBCAL_MASK_SFT                   (0x1 << 5)
#घोषणा RG_AUDACCDETTVDET_ADDR                         \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETTVDET_SFT                          6
#घोषणा RG_AUDACCDETTVDET_MASK                         0x1
#घोषणा RG_AUDACCDETTVDET_MASK_SFT                     (0x1 << 6)
#घोषणा RG_ACCDETSEL_ADDR                              \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_ACCDETSEL_SFT                               7
#घोषणा RG_ACCDETSEL_MASK                              0x1
#घोषणा RG_ACCDETSEL_MASK_SFT                          (0x1 << 7)

#घोषणा RG_AUDPWDBMICBIAS1_ADDR                        \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDPWDBMICBIAS1_SFT                         0
#घोषणा RG_AUDPWDBMICBIAS1_MASK                        0x1
#घोषणा RG_AUDPWDBMICBIAS1_MASK_SFT                    (0x1 << 0)
#घोषणा RG_AUDMICBIAS1BYPASSEN_ADDR                    \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDMICBIAS1BYPASSEN_SFT                     1
#घोषणा RG_AUDMICBIAS1BYPASSEN_MASK                    0x1
#घोषणा RG_AUDMICBIAS1BYPASSEN_MASK_SFT                (0x1 << 1)
#घोषणा RG_AUDMICBIAS1LOWPEN_ADDR                      \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDMICBIAS1LOWPEN_SFT                       2
#घोषणा RG_AUDMICBIAS1LOWPEN_MASK                      0x1
#घोषणा RG_AUDMICBIAS1LOWPEN_MASK_SFT                  (0x1 << 2)
#घोषणा RG_AUDMICBIAS1VREF_ADDR                        \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDMICBIAS1VREF_SFT                         4
#घोषणा RG_AUDMICBIAS1VREF_MASK                        0x7
#घोषणा RG_AUDMICBIAS1VREF_MASK_SFT                    (0x7 << 4)
#घोषणा RG_AUDMICBIAS1DCSW1PEN_ADDR                    \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDMICBIAS1DCSW1PEN_SFT                     8
#घोषणा RG_AUDMICBIAS1DCSW1PEN_MASK                    0x1
#घोषणा RG_AUDMICBIAS1DCSW1PEN_MASK_SFT                (0x1 << 8)
#घोषणा RG_AUDMICBIAS1DCSW1NEN_ADDR                    \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDMICBIAS1DCSW1NEN_SFT                     9
#घोषणा RG_AUDMICBIAS1DCSW1NEN_MASK                    0x1
#घोषणा RG_AUDMICBIAS1DCSW1NEN_MASK_SFT                (0x1 << 9)
#घोषणा RG_BANDGAPGEN_ADDR                             \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_BANDGAPGEN_SFT                              10
#घोषणा RG_BANDGAPGEN_MASK                             0x1
#घोषणा RG_BANDGAPGEN_MASK_SFT                         (0x1 << 10)
#घोषणा RG_AUDMICBIAS1HVEN_ADDR                        \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDMICBIAS1HVEN_SFT                         12
#घोषणा RG_AUDMICBIAS1HVEN_MASK                        0x1
#घोषणा RG_AUDMICBIAS1HVEN_MASK_SFT                    (0x1 << 12)
#घोषणा RG_AUDMICBIAS1HVVREF_ADDR                      \
	MT6359_AUDENC_ANA_CON16
#घोषणा RG_AUDMICBIAS1HVVREF_SFT                       13
#घोषणा RG_AUDMICBIAS1HVVREF_MASK                      0x1
#घोषणा RG_AUDMICBIAS1HVVREF_MASK_SFT                  (0x1 << 13)

#घोषणा RG_EINT0NOHYS_ADDR                             \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_EINT0NOHYS_SFT                              10
#घोषणा RG_EINT0NOHYS_MASK                             0x1
#घोषणा RG_EINT0NOHYS_MASK_SFT                         (0x1 << 10)
#घोषणा RG_EINT0CONFIGACCDET_ADDR                      \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_EINT0CONFIGACCDET_SFT                       11
#घोषणा RG_EINT0CONFIGACCDET_MASK                      0x1
#घोषणा RG_EINT0CONFIGACCDET_MASK_SFT                  (0x1 << 11)
#घोषणा RG_EINT0HIRENB_ADDR                            \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_EINT0HIRENB_SFT                             12
#घोषणा RG_EINT0HIRENB_MASK                            0x1
#घोषणा RG_EINT0HIRENB_MASK_SFT                        (0x1 << 12)
#घोषणा RG_ACCDET2AUXRESBYPASS_ADDR                    \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_ACCDET2AUXRESBYPASS_SFT                     13
#घोषणा RG_ACCDET2AUXRESBYPASS_MASK                    0x1
#घोषणा RG_ACCDET2AUXRESBYPASS_MASK_SFT                (0x1 << 13)
#घोषणा RG_ACCDET2AUXSWEN_ADDR                         \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_ACCDET2AUXSWEN_SFT                          14
#घोषणा RG_ACCDET2AUXSWEN_MASK                         0x1
#घोषणा RG_ACCDET2AUXSWEN_MASK_SFT                     (0x1 << 14)
#घोषणा RG_AUDACCDETMICBIAS3PULLLOW_ADDR               \
	MT6359_AUDENC_ANA_CON18
#घोषणा RG_AUDACCDETMICBIAS3PULLLOW_SFT                15
#घोषणा RG_AUDACCDETMICBIAS3PULLLOW_MASK               0x1
#घोषणा RG_AUDACCDETMICBIAS3PULLLOW_MASK_SFT           (0x1 << 15)
#घोषणा RG_EINT1CONFIGACCDET_ADDR                      \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_EINT1CONFIGACCDET_SFT                       0
#घोषणा RG_EINT1CONFIGACCDET_MASK                      0x1
#घोषणा RG_EINT1CONFIGACCDET_MASK_SFT                  (0x1 << 0)
#घोषणा RG_EINT1HIRENB_ADDR                            \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_EINT1HIRENB_SFT                             1
#घोषणा RG_EINT1HIRENB_MASK                            0x1
#घोषणा RG_EINT1HIRENB_MASK_SFT                        (0x1 << 1)
#घोषणा RG_EINT1NOHYS_ADDR                             \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_EINT1NOHYS_SFT                              2
#घोषणा RG_EINT1NOHYS_MASK                             0x1
#घोषणा RG_EINT1NOHYS_MASK_SFT                         (0x1 << 2)
#घोषणा RG_EINTCOMPVTH_ADDR                            \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_MTEST_EN_ADDR                               \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_MTEST_EN_SFT                                8
#घोषणा RG_MTEST_EN_MASK                               0x1
#घोषणा RG_MTEST_EN_MASK_SFT                           (0x1 << 8)
#घोषणा RG_MTEST_SEL_ADDR                              \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_MTEST_SEL_SFT                               9
#घोषणा RG_MTEST_SEL_MASK                              0x1
#घोषणा RG_MTEST_SEL_MASK_SFT                          (0x1 << 9)
#घोषणा RG_MTEST_CURRENT_ADDR                          \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_MTEST_CURRENT_SFT                           10
#घोषणा RG_MTEST_CURRENT_MASK                          0x1
#घोषणा RG_MTEST_CURRENT_MASK_SFT                      (0x1 << 10)
#घोषणा RG_ANALOGFDEN_ADDR                             \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_ANALOGFDEN_SFT                              12
#घोषणा RG_ANALOGFDEN_MASK                             0x1
#घोषणा RG_ANALOGFDEN_MASK_SFT                         (0x1 << 12)
#घोषणा RG_FDVIN1PPULLLOW_ADDR                         \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_FDVIN1PPULLLOW_SFT                          13
#घोषणा RG_FDVIN1PPULLLOW_MASK                         0x1
#घोषणा RG_FDVIN1PPULLLOW_MASK_SFT                     (0x1 << 13)
#घोषणा RG_FDEINT0TYPE_ADDR                            \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_FDEINT0TYPE_SFT                             14
#घोषणा RG_FDEINT0TYPE_MASK                            0x1
#घोषणा RG_FDEINT0TYPE_MASK_SFT                        (0x1 << 14)
#घोषणा RG_FDEINT1TYPE_ADDR                            \
	MT6359_AUDENC_ANA_CON19
#घोषणा RG_FDEINT1TYPE_SFT                             15
#घोषणा RG_FDEINT1TYPE_MASK                            0x1
#घोषणा RG_FDEINT1TYPE_MASK_SFT                        (0x1 << 15)
#घोषणा RG_EINT0CMPEN_ADDR                             \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT0CMPEN_SFT                              0
#घोषणा RG_EINT0CMPEN_MASK                             0x1
#घोषणा RG_EINT0CMPEN_MASK_SFT                         (0x1 << 0)
#घोषणा RG_EINT0CMPMEN_ADDR                            \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT0CMPMEN_SFT                             1
#घोषणा RG_EINT0CMPMEN_MASK                            0x1
#घोषणा RG_EINT0CMPMEN_MASK_SFT                        (0x1 << 1)
#घोषणा RG_EINT0EN_ADDR                                \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT0EN_SFT                                 2
#घोषणा RG_EINT0EN_MASK                                0x1
#घोषणा RG_EINT0EN_MASK_SFT                            (0x1 << 2)
#घोषणा RG_EINT0CEN_ADDR                               \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT0CEN_SFT                                3
#घोषणा RG_EINT0CEN_MASK                               0x1
#घोषणा RG_EINT0CEN_MASK_SFT                           (0x1 << 3)
#घोषणा RG_EINT0INVEN_ADDR                             \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT0INVEN_SFT                              4
#घोषणा RG_EINT0INVEN_MASK                             0x1
#घोषणा RG_EINT0INVEN_MASK_SFT                         (0x1 << 4)
#घोषणा RG_EINT0CTURBO_ADDR                            \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT0CTURBO_SFT                             5
#घोषणा RG_EINT0CTURBO_MASK                            0x7
#घोषणा RG_EINT0CTURBO_MASK_SFT                        (0x7 << 5)
#घोषणा RG_EINT1CMPEN_ADDR                             \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT1CMPEN_SFT                              8
#घोषणा RG_EINT1CMPEN_MASK                             0x1
#घोषणा RG_EINT1CMPEN_MASK_SFT                         (0x1 << 8)
#घोषणा RG_EINT1CMPMEN_ADDR                            \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT1CMPMEN_SFT                             9
#घोषणा RG_EINT1CMPMEN_MASK                            0x1
#घोषणा RG_EINT1CMPMEN_MASK_SFT                        (0x1 << 9)
#घोषणा RG_EINT1EN_ADDR                                \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT1EN_SFT                                 10
#घोषणा RG_EINT1EN_MASK                                0x1
#घोषणा RG_EINT1EN_MASK_SFT                            (0x1 << 10)
#घोषणा RG_EINT1CEN_ADDR                               \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT1CEN_SFT                                11
#घोषणा RG_EINT1CEN_MASK                               0x1
#घोषणा RG_EINT1CEN_MASK_SFT                           (0x1 << 11)
#घोषणा RG_EINT1INVEN_ADDR                             \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT1INVEN_SFT                              12
#घोषणा RG_EINT1INVEN_MASK                             0x1
#घोषणा RG_EINT1INVEN_MASK_SFT                         (0x1 << 12)
#घोषणा RG_EINT1CTURBO_ADDR                            \
	MT6359_AUDENC_ANA_CON20
#घोषणा RG_EINT1CTURBO_SFT                             13
#घोषणा RG_EINT1CTURBO_MASK                            0x7
#घोषणा RG_EINT1CTURBO_MASK_SFT                        (0x7 << 13)
#घोषणा RG_ACCDETSPARE_ADDR                            \
	MT6359_AUDENC_ANA_CON21

#घोषणा ACCDET_ANA_ID_ADDR                             \
	MT6359_ACCDET_DSN_DIG_ID
#घोषणा ACCDET_ANA_ID_SFT                              0
#घोषणा ACCDET_ANA_ID_MASK                             0xFF
#घोषणा ACCDET_ANA_ID_MASK_SFT                         (0xFF << 0)
#घोषणा ACCDET_DIG_ID_ADDR                             \
	MT6359_ACCDET_DSN_DIG_ID
#घोषणा ACCDET_DIG_ID_SFT                              8
#घोषणा ACCDET_DIG_ID_MASK                             0xFF
#घोषणा ACCDET_DIG_ID_MASK_SFT                         (0xFF << 8)
#घोषणा ACCDET_ANA_MINOR_REV_ADDR                      \
	MT6359_ACCDET_DSN_DIG_REV0
#घोषणा ACCDET_ANA_MINOR_REV_SFT                       0
#घोषणा ACCDET_ANA_MINOR_REV_MASK                      0xF
#घोषणा ACCDET_ANA_MINOR_REV_MASK_SFT                  (0xF << 0)
#घोषणा ACCDET_ANA_MAJOR_REV_ADDR                      \
	MT6359_ACCDET_DSN_DIG_REV0
#घोषणा ACCDET_ANA_MAJOR_REV_SFT                       4
#घोषणा ACCDET_ANA_MAJOR_REV_MASK                      0xF
#घोषणा ACCDET_ANA_MAJOR_REV_MASK_SFT                  (0xF << 4)
#घोषणा ACCDET_DIG_MINOR_REV_ADDR                      \
	MT6359_ACCDET_DSN_DIG_REV0
#घोषणा ACCDET_DIG_MINOR_REV_SFT                       8
#घोषणा ACCDET_DIG_MINOR_REV_MASK                      0xF
#घोषणा ACCDET_DIG_MINOR_REV_MASK_SFT                  (0xF << 8)
#घोषणा ACCDET_DIG_MAJOR_REV_ADDR                      \
	MT6359_ACCDET_DSN_DIG_REV0
#घोषणा ACCDET_DIG_MAJOR_REV_SFT                       12
#घोषणा ACCDET_DIG_MAJOR_REV_MASK                      0xF
#घोषणा ACCDET_DIG_MAJOR_REV_MASK_SFT                  (0xF << 12)
#घोषणा ACCDET_DSN_CBS_ADDR                            \
	MT6359_ACCDET_DSN_DBI
#घोषणा ACCDET_DSN_CBS_SFT                             0
#घोषणा ACCDET_DSN_CBS_MASK                            0x3
#घोषणा ACCDET_DSN_CBS_MASK_SFT                        (0x3 << 0)
#घोषणा ACCDET_DSN_BIX_ADDR                            \
	MT6359_ACCDET_DSN_DBI
#घोषणा ACCDET_DSN_BIX_SFT                             2
#घोषणा ACCDET_DSN_BIX_MASK                            0x3
#घोषणा ACCDET_DSN_BIX_MASK_SFT                        (0x3 << 2)
#घोषणा ACCDET_ESP_ADDR                                \
	MT6359_ACCDET_DSN_DBI
#घोषणा ACCDET_ESP_SFT                                 8
#घोषणा ACCDET_ESP_MASK                                0xFF
#घोषणा ACCDET_ESP_MASK_SFT                            (0xFF << 8)
#घोषणा ACCDET_DSN_FPI_ADDR                            \
	MT6359_ACCDET_DSN_FPI
#घोषणा ACCDET_DSN_FPI_SFT                             0
#घोषणा ACCDET_DSN_FPI_MASK                            0xFF
#घोषणा ACCDET_DSN_FPI_MASK_SFT                        (0xFF << 0)
#घोषणा ACCDET_AUXADC_SEL_ADDR                         \
	MT6359_ACCDET_CON0
#घोषणा ACCDET_AUXADC_SEL_SFT                          0
#घोषणा ACCDET_AUXADC_SEL_MASK                         0x1
#घोषणा ACCDET_AUXADC_SEL_MASK_SFT                     (0x1 << 0)
#घोषणा ACCDET_AUXADC_SW_ADDR                          \
	MT6359_ACCDET_CON0
#घोषणा ACCDET_AUXADC_SW_SFT                           1
#घोषणा ACCDET_AUXADC_SW_MASK                          0x1
#घोषणा ACCDET_AUXADC_SW_MASK_SFT                      (0x1 << 1)
#घोषणा ACCDET_TEST_AUXADC_ADDR                        \
	MT6359_ACCDET_CON0
#घोषणा ACCDET_TEST_AUXADC_SFT                         2
#घोषणा ACCDET_TEST_AUXADC_MASK                        0x1
#घोषणा ACCDET_TEST_AUXADC_MASK_SFT                    (0x1 << 2)
#घोषणा ACCDET_AUXADC_ANASWCTRL_SEL_ADDR               \
	MT6359_ACCDET_CON0
#घोषणा ACCDET_AUXADC_ANASWCTRL_SEL_SFT                8
#घोषणा ACCDET_AUXADC_ANASWCTRL_SEL_MASK               0x1
#घोषणा ACCDET_AUXADC_ANASWCTRL_SEL_MASK_SFT           (0x1 << 8)
#घोषणा AUDACCDETAUXADCSWCTRL_SEL_ADDR                 \
	MT6359_ACCDET_CON0
#घोषणा AUDACCDETAUXADCSWCTRL_SEL_SFT                  9
#घोषणा AUDACCDETAUXADCSWCTRL_SEL_MASK                 0x1
#घोषणा AUDACCDETAUXADCSWCTRL_SEL_MASK_SFT             (0x1 << 9)
#घोषणा AUDACCDETAUXADCSWCTRL_SW_ADDR                  \
	MT6359_ACCDET_CON0
#घोषणा AUDACCDETAUXADCSWCTRL_SW_SFT                   10
#घोषणा AUDACCDETAUXADCSWCTRL_SW_MASK                  0x1
#घोषणा AUDACCDETAUXADCSWCTRL_SW_MASK_SFT              (0x1 << 10)
#घोषणा ACCDET_TEST_ANA_ADDR                           \
	MT6359_ACCDET_CON0
#घोषणा ACCDET_TEST_ANA_SFT                            11
#घोषणा ACCDET_TEST_ANA_MASK                           0x1
#घोषणा ACCDET_TEST_ANA_MASK_SFT                       (0x1 << 11)
#घोषणा RG_AUDACCDETRSV_ADDR                           \
	MT6359_ACCDET_CON0
#घोषणा RG_AUDACCDETRSV_SFT                            13
#घोषणा RG_AUDACCDETRSV_MASK                           0x3
#घोषणा RG_AUDACCDETRSV_MASK_SFT                       (0x3 << 13)
#घोषणा ACCDET_SW_EN_ADDR                              \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_SW_EN_SFT                               0
#घोषणा ACCDET_SW_EN_MASK                              0x1
#घोषणा ACCDET_SW_EN_MASK_SFT                          (0x1 << 0)
#घोषणा ACCDET_SEQ_INIT_ADDR                           \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_SEQ_INIT_SFT                            1
#घोषणा ACCDET_SEQ_INIT_MASK                           0x1
#घोषणा ACCDET_SEQ_INIT_MASK_SFT                       (0x1 << 1)
#घोषणा ACCDET_EINT0_SW_EN_ADDR                        \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT0_SW_EN_SFT                         2
#घोषणा ACCDET_EINT0_SW_EN_MASK                        0x1
#घोषणा ACCDET_EINT0_SW_EN_MASK_SFT                    (0x1 << 2)
#घोषणा ACCDET_EINT0_SEQ_INIT_ADDR                     \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT0_SEQ_INIT_SFT                      3
#घोषणा ACCDET_EINT0_SEQ_INIT_MASK                     0x1
#घोषणा ACCDET_EINT0_SEQ_INIT_MASK_SFT                 (0x1 << 3)
#घोषणा ACCDET_EINT1_SW_EN_ADDR                        \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT1_SW_EN_SFT                         4
#घोषणा ACCDET_EINT1_SW_EN_MASK                        0x1
#घोषणा ACCDET_EINT1_SW_EN_MASK_SFT                    (0x1 << 4)
#घोषणा ACCDET_EINT1_SEQ_INIT_ADDR                     \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT1_SEQ_INIT_SFT                      5
#घोषणा ACCDET_EINT1_SEQ_INIT_MASK                     0x1
#घोषणा ACCDET_EINT1_SEQ_INIT_MASK_SFT                 (0x1 << 5)
#घोषणा ACCDET_EINT0_INVERTER_SW_EN_ADDR               \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT0_INVERTER_SW_EN_SFT                6
#घोषणा ACCDET_EINT0_INVERTER_SW_EN_MASK               0x1
#घोषणा ACCDET_EINT0_INVERTER_SW_EN_MASK_SFT           (0x1 << 6)
#घोषणा ACCDET_EINT0_INVERTER_SEQ_INIT_ADDR            \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT0_INVERTER_SEQ_INIT_SFT             7
#घोषणा ACCDET_EINT0_INVERTER_SEQ_INIT_MASK            0x1
#घोषणा ACCDET_EINT0_INVERTER_SEQ_INIT_MASK_SFT        (0x1 << 7)
#घोषणा ACCDET_EINT1_INVERTER_SW_EN_ADDR               \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT1_INVERTER_SW_EN_SFT                8
#घोषणा ACCDET_EINT1_INVERTER_SW_EN_MASK               0x1
#घोषणा ACCDET_EINT1_INVERTER_SW_EN_MASK_SFT           (0x1 << 8)
#घोषणा ACCDET_EINT1_INVERTER_SEQ_INIT_ADDR            \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT1_INVERTER_SEQ_INIT_SFT             9
#घोषणा ACCDET_EINT1_INVERTER_SEQ_INIT_MASK            0x1
#घोषणा ACCDET_EINT1_INVERTER_SEQ_INIT_MASK_SFT        (0x1 << 9)
#घोषणा ACCDET_EINT0_M_SW_EN_ADDR                      \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT0_M_SW_EN_SFT                       10
#घोषणा ACCDET_EINT0_M_SW_EN_MASK                      0x1
#घोषणा ACCDET_EINT0_M_SW_EN_MASK_SFT                  (0x1 << 10)
#घोषणा ACCDET_EINT1_M_SW_EN_ADDR                      \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT1_M_SW_EN_SFT                       11
#घोषणा ACCDET_EINT1_M_SW_EN_MASK                      0x1
#घोषणा ACCDET_EINT1_M_SW_EN_MASK_SFT                  (0x1 << 11)
#घोषणा ACCDET_EINT_M_DETECT_EN_ADDR                   \
	MT6359_ACCDET_CON1
#घोषणा ACCDET_EINT_M_DETECT_EN_SFT                    12
#घोषणा ACCDET_EINT_M_DETECT_EN_MASK                   0x1
#घोषणा ACCDET_EINT_M_DETECT_EN_MASK_SFT               (0x1 << 12)
#घोषणा ACCDET_CMP_PWM_EN_ADDR                         \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_CMP_PWM_EN_SFT                          0
#घोषणा ACCDET_CMP_PWM_EN_MASK                         0x1
#घोषणा ACCDET_CMP_PWM_EN_MASK_SFT                     (0x1 << 0)
#घोषणा ACCDET_VTH_PWM_EN_ADDR                         \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_VTH_PWM_EN_SFT                          1
#घोषणा ACCDET_VTH_PWM_EN_MASK                         0x1
#घोषणा ACCDET_VTH_PWM_EN_MASK_SFT                     (0x1 << 1)
#घोषणा ACCDET_MBIAS_PWM_EN_ADDR                       \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_MBIAS_PWM_EN_SFT                        2
#घोषणा ACCDET_MBIAS_PWM_EN_MASK                       0x1
#घोषणा ACCDET_MBIAS_PWM_EN_MASK_SFT                   (0x1 << 2)
#घोषणा ACCDET_EINT_EN_PWM_EN_ADDR                     \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_EINT_EN_PWM_EN_SFT                      3
#घोषणा ACCDET_EINT_EN_PWM_EN_MASK                     0x1
#घोषणा ACCDET_EINT_EN_PWM_EN_MASK_SFT                 (0x1 << 3)
#घोषणा ACCDET_EINT_CMPEN_PWM_EN_ADDR                  \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_EINT_CMPEN_PWM_EN_SFT                   4
#घोषणा ACCDET_EINT_CMPEN_PWM_EN_MASK                  0x1
#घोषणा ACCDET_EINT_CMPEN_PWM_EN_MASK_SFT              (0x1 << 4)
#घोषणा ACCDET_EINT_CMPMEN_PWM_EN_ADDR                 \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_EINT_CMPMEN_PWM_EN_SFT                  5
#घोषणा ACCDET_EINT_CMPMEN_PWM_EN_MASK                 0x1
#घोषणा ACCDET_EINT_CMPMEN_PWM_EN_MASK_SFT             (0x1 << 5)
#घोषणा ACCDET_EINT_CTURBO_PWM_EN_ADDR                 \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_EINT_CTURBO_PWM_EN_SFT                  6
#घोषणा ACCDET_EINT_CTURBO_PWM_EN_MASK                 0x1
#घोषणा ACCDET_EINT_CTURBO_PWM_EN_MASK_SFT             (0x1 << 6)
#घोषणा ACCDET_CMP_PWM_IDLE_ADDR                       \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_CMP_PWM_IDLE_SFT                        8
#घोषणा ACCDET_CMP_PWM_IDLE_MASK                       0x1
#घोषणा ACCDET_CMP_PWM_IDLE_MASK_SFT                   (0x1 << 8)
#घोषणा ACCDET_VTH_PWM_IDLE_ADDR                       \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_VTH_PWM_IDLE_SFT                        9
#घोषणा ACCDET_VTH_PWM_IDLE_MASK                       0x1
#घोषणा ACCDET_VTH_PWM_IDLE_MASK_SFT                   (0x1 << 9)
#घोषणा ACCDET_MBIAS_PWM_IDLE_ADDR                     \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_MBIAS_PWM_IDLE_SFT                      10
#घोषणा ACCDET_MBIAS_PWM_IDLE_MASK                     0x1
#घोषणा ACCDET_MBIAS_PWM_IDLE_MASK_SFT                 (0x1 << 10)
#घोषणा ACCDET_EINT0_CMPEN_PWM_IDLE_ADDR               \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_EINT0_CMPEN_PWM_IDLE_SFT                11
#घोषणा ACCDET_EINT0_CMPEN_PWM_IDLE_MASK               0x1
#घोषणा ACCDET_EINT0_CMPEN_PWM_IDLE_MASK_SFT           (0x1 << 11)
#घोषणा ACCDET_EINT1_CMPEN_PWM_IDLE_ADDR               \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_EINT1_CMPEN_PWM_IDLE_SFT                12
#घोषणा ACCDET_EINT1_CMPEN_PWM_IDLE_MASK               0x1
#घोषणा ACCDET_EINT1_CMPEN_PWM_IDLE_MASK_SFT           (0x1 << 12)
#घोषणा ACCDET_PWM_EN_SW_ADDR                          \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_PWM_EN_SW_SFT                           13
#घोषणा ACCDET_PWM_EN_SW_MASK                          0x1
#घोषणा ACCDET_PWM_EN_SW_MASK_SFT                      (0x1 << 13)
#घोषणा ACCDET_PWM_EN_SEL_ADDR                         \
	MT6359_ACCDET_CON2
#घोषणा ACCDET_PWM_EN_SEL_SFT                          14
#घोषणा ACCDET_PWM_EN_SEL_MASK                         0x3
#घोषणा ACCDET_PWM_EN_SEL_MASK_SFT                     (0x3 << 14)
#घोषणा ACCDET_PWM_WIDTH_ADDR                          \
	MT6359_ACCDET_CON3
#घोषणा ACCDET_PWM_WIDTH_SFT                           0
#घोषणा ACCDET_PWM_WIDTH_MASK                          0xFFFF
#घोषणा ACCDET_PWM_WIDTH_MASK_SFT                      (0xFFFF << 0)
#घोषणा ACCDET_PWM_THRESH_ADDR                         \
	MT6359_ACCDET_CON4
#घोषणा ACCDET_PWM_THRESH_SFT                          0
#घोषणा ACCDET_PWM_THRESH_MASK                         0xFFFF
#घोषणा ACCDET_PWM_THRESH_MASK_SFT                     (0xFFFF << 0)
#घोषणा ACCDET_RISE_DELAY_ADDR                         \
	MT6359_ACCDET_CON5
#घोषणा ACCDET_RISE_DELAY_SFT                          0
#घोषणा ACCDET_RISE_DELAY_MASK                         0x7FFF
#घोषणा ACCDET_RISE_DELAY_MASK_SFT                     (0x7FFF << 0)
#घोषणा ACCDET_FALL_DELAY_ADDR                         \
	MT6359_ACCDET_CON5
#घोषणा ACCDET_FALL_DELAY_SFT                          15
#घोषणा ACCDET_FALL_DELAY_MASK                         0x1
#घोषणा ACCDET_FALL_DELAY_MASK_SFT                     (0x1 << 15)
#घोषणा ACCDET_EINT_CMPMEN_PWM_THRESH_ADDR             \
	MT6359_ACCDET_CON6
#घोषणा ACCDET_EINT_CMPMEN_PWM_THRESH_SFT              0
#घोषणा ACCDET_EINT_CMPMEN_PWM_THRESH_MASK             0x7
#घोषणा ACCDET_EINT_CMPMEN_PWM_THRESH_MASK_SFT         (0x7 << 0)
#घोषणा ACCDET_EINT_CMPMEN_PWM_WIDTH_ADDR              \
	MT6359_ACCDET_CON6
#घोषणा ACCDET_EINT_CMPMEN_PWM_WIDTH_SFT               4
#घोषणा ACCDET_EINT_CMPMEN_PWM_WIDTH_MASK              0x7
#घोषणा ACCDET_EINT_CMPMEN_PWM_WIDTH_MASK_SFT          (0x7 << 4)
#घोषणा ACCDET_EINT_EN_PWM_THRESH_ADDR                 \
	MT6359_ACCDET_CON7
#घोषणा ACCDET_EINT_EN_PWM_THRESH_SFT                  0
#घोषणा ACCDET_EINT_EN_PWM_THRESH_MASK                 0x7
#घोषणा ACCDET_EINT_EN_PWM_THRESH_MASK_SFT             (0x7 << 0)
#घोषणा ACCDET_EINT_EN_PWM_WIDTH_ADDR                  \
	MT6359_ACCDET_CON7
#घोषणा ACCDET_EINT_EN_PWM_WIDTH_SFT                   4
#घोषणा ACCDET_EINT_EN_PWM_WIDTH_MASK                  0x3
#घोषणा ACCDET_EINT_EN_PWM_WIDTH_MASK_SFT              (0x3 << 4)
#घोषणा ACCDET_EINT_CMPEN_PWM_THRESH_ADDR              \
	MT6359_ACCDET_CON7
#घोषणा ACCDET_EINT_CMPEN_PWM_THRESH_SFT               8
#घोषणा ACCDET_EINT_CMPEN_PWM_THRESH_MASK              0x7
#घोषणा ACCDET_EINT_CMPEN_PWM_THRESH_MASK_SFT          (0x7 << 8)
#घोषणा ACCDET_EINT_CMPEN_PWM_WIDTH_ADDR               \
	MT6359_ACCDET_CON7
#घोषणा ACCDET_EINT_CMPEN_PWM_WIDTH_SFT                12
#घोषणा ACCDET_EINT_CMPEN_PWM_WIDTH_MASK               0x3
#घोषणा ACCDET_EINT_CMPEN_PWM_WIDTH_MASK_SFT           (0x3 << 12)
#घोषणा ACCDET_DEBOUNCE0_ADDR                          \
	MT6359_ACCDET_CON8
#घोषणा ACCDET_DEBOUNCE0_SFT                           0
#घोषणा ACCDET_DEBOUNCE0_MASK                          0xFFFF
#घोषणा ACCDET_DEBOUNCE0_MASK_SFT                      (0xFFFF << 0)
#घोषणा ACCDET_DEBOUNCE1_ADDR                          \
	MT6359_ACCDET_CON9
#घोषणा ACCDET_DEBOUNCE1_SFT                           0
#घोषणा ACCDET_DEBOUNCE1_MASK                          0xFFFF
#घोषणा ACCDET_DEBOUNCE1_MASK_SFT                      (0xFFFF << 0)
#घोषणा ACCDET_DEBOUNCE2_ADDR                          \
	MT6359_ACCDET_CON10
#घोषणा ACCDET_DEBOUNCE2_SFT                           0
#घोषणा ACCDET_DEBOUNCE2_MASK                          0xFFFF
#घोषणा ACCDET_DEBOUNCE2_MASK_SFT                      (0xFFFF << 0)
#घोषणा ACCDET_DEBOUNCE3_ADDR                          \
	MT6359_ACCDET_CON11
#घोषणा ACCDET_DEBOUNCE3_SFT                           0
#घोषणा ACCDET_DEBOUNCE3_MASK                          0xFFFF
#घोषणा ACCDET_DEBOUNCE3_MASK_SFT                      (0xFFFF << 0)
#घोषणा ACCDET_CONNECT_AUXADC_TIME_DIG_ADDR            \
	MT6359_ACCDET_CON12
#घोषणा ACCDET_CONNECT_AUXADC_TIME_DIG_SFT             0
#घोषणा ACCDET_CONNECT_AUXADC_TIME_DIG_MASK            0xFFFF
#घोषणा ACCDET_CONNECT_AUXADC_TIME_DIG_MASK_SFT        (0xFFFF << 0)
#घोषणा ACCDET_CONNECT_AUXADC_TIME_ANA_ADDR            \
	MT6359_ACCDET_CON13
#घोषणा ACCDET_CONNECT_AUXADC_TIME_ANA_SFT             0
#घोषणा ACCDET_CONNECT_AUXADC_TIME_ANA_MASK            0xFFFF
#घोषणा ACCDET_CONNECT_AUXADC_TIME_ANA_MASK_SFT        (0xFFFF << 0)
#घोषणा ACCDET_EINT_DEBOUNCE0_ADDR                     \
	MT6359_ACCDET_CON14
#घोषणा ACCDET_EINT_DEBOUNCE0_SFT                      0
#घोषणा ACCDET_EINT_DEBOUNCE0_MASK                     0xF
#घोषणा ACCDET_EINT_DEBOUNCE0_MASK_SFT                 (0xF << 0)
#घोषणा ACCDET_EINT_DEBOUNCE1_ADDR                     \
	MT6359_ACCDET_CON14
#घोषणा ACCDET_EINT_DEBOUNCE1_SFT                      4
#घोषणा ACCDET_EINT_DEBOUNCE1_MASK                     0xF
#घोषणा ACCDET_EINT_DEBOUNCE1_MASK_SFT                 (0xF << 4)
#घोषणा ACCDET_EINT_DEBOUNCE2_ADDR                     \
	MT6359_ACCDET_CON14
#घोषणा ACCDET_EINT_DEBOUNCE2_SFT                      8
#घोषणा ACCDET_EINT_DEBOUNCE2_MASK                     0xF
#घोषणा ACCDET_EINT_DEBOUNCE2_MASK_SFT                 (0xF << 8)
#घोषणा ACCDET_EINT_DEBOUNCE3_ADDR                     \
	MT6359_ACCDET_CON14
#घोषणा ACCDET_EINT_DEBOUNCE3_SFT                      12
#घोषणा ACCDET_EINT_DEBOUNCE3_MASK                     0xF
#घोषणा ACCDET_EINT_DEBOUNCE3_MASK_SFT                 (0xF << 12)
#घोषणा ACCDET_EINT_INVERTER_DEBOUNCE_ADDR             \
	MT6359_ACCDET_CON15
#घोषणा ACCDET_EINT_INVERTER_DEBOUNCE_SFT              0
#घोषणा ACCDET_EINT_INVERTER_DEBOUNCE_MASK             0xF
#घोषणा ACCDET_EINT_INVERTER_DEBOUNCE_MASK_SFT         (0xF << 0)
#घोषणा ACCDET_IVAL_CUR_IN_ADDR                        \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_IVAL_CUR_IN_SFT                         0
#घोषणा ACCDET_IVAL_CUR_IN_MASK                        0x3
#घोषणा ACCDET_IVAL_CUR_IN_MASK_SFT                    (0x3 << 0)
#घोषणा ACCDET_IVAL_SAM_IN_ADDR                        \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_IVAL_SAM_IN_SFT                         2
#घोषणा ACCDET_IVAL_SAM_IN_MASK                        0x3
#घोषणा ACCDET_IVAL_SAM_IN_MASK_SFT                    (0x3 << 2)
#घोषणा ACCDET_IVAL_MEM_IN_ADDR                        \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_IVAL_MEM_IN_SFT                         4
#घोषणा ACCDET_IVAL_MEM_IN_MASK                        0x3
#घोषणा ACCDET_IVAL_MEM_IN_MASK_SFT                    (0x3 << 4)
#घोषणा ACCDET_EINT_IVAL_CUR_IN_ADDR                   \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_EINT_IVAL_CUR_IN_SFT                    6
#घोषणा ACCDET_EINT_IVAL_CUR_IN_MASK                   0x3
#घोषणा ACCDET_EINT_IVAL_CUR_IN_MASK_SFT               (0x3 << 6)
#घोषणा ACCDET_EINT_IVAL_SAM_IN_ADDR                   \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_EINT_IVAL_SAM_IN_SFT                    8
#घोषणा ACCDET_EINT_IVAL_SAM_IN_MASK                   0x3
#घोषणा ACCDET_EINT_IVAL_SAM_IN_MASK_SFT               (0x3 << 8)
#घोषणा ACCDET_EINT_IVAL_MEM_IN_ADDR                   \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_EINT_IVAL_MEM_IN_SFT                    10
#घोषणा ACCDET_EINT_IVAL_MEM_IN_MASK                   0x3
#घोषणा ACCDET_EINT_IVAL_MEM_IN_MASK_SFT               (0x3 << 10)
#घोषणा ACCDET_IVAL_SEL_ADDR                           \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_IVAL_SEL_SFT                            12
#घोषणा ACCDET_IVAL_SEL_MASK                           0x1
#घोषणा ACCDET_IVAL_SEL_MASK_SFT                       (0x1 << 12)
#घोषणा ACCDET_EINT_IVAL_SEL_ADDR                      \
	MT6359_ACCDET_CON16
#घोषणा ACCDET_EINT_IVAL_SEL_SFT                       13
#घोषणा ACCDET_EINT_IVAL_SEL_MASK                      0x1
#घोषणा ACCDET_EINT_IVAL_SEL_MASK_SFT                  (0x1 << 13)
#घोषणा ACCDET_EINT_INVERTER_IVAL_CUR_IN_ADDR          \
	MT6359_ACCDET_CON17
#घोषणा ACCDET_EINT_INVERTER_IVAL_CUR_IN_SFT           0
#घोषणा ACCDET_EINT_INVERTER_IVAL_CUR_IN_MASK          0x1
#घोषणा ACCDET_EINT_INVERTER_IVAL_CUR_IN_MASK_SFT      (0x1 << 0)
#घोषणा ACCDET_EINT_INVERTER_IVAL_SAM_IN_ADDR          \
	MT6359_ACCDET_CON17
#घोषणा ACCDET_EINT_INVERTER_IVAL_SAM_IN_SFT           1
#घोषणा ACCDET_EINT_INVERTER_IVAL_SAM_IN_MASK          0x1
#घोषणा ACCDET_EINT_INVERTER_IVAL_SAM_IN_MASK_SFT      (0x1 << 1)
#घोषणा ACCDET_EINT_INVERTER_IVAL_MEM_IN_ADDR          \
	MT6359_ACCDET_CON17
#घोषणा ACCDET_EINT_INVERTER_IVAL_MEM_IN_SFT           2
#घोषणा ACCDET_EINT_INVERTER_IVAL_MEM_IN_MASK          0x1
#घोषणा ACCDET_EINT_INVERTER_IVAL_MEM_IN_MASK_SFT      (0x1 << 2)
#घोषणा ACCDET_EINT_INVERTER_IVAL_SEL_ADDR             \
	MT6359_ACCDET_CON17
#घोषणा ACCDET_EINT_INVERTER_IVAL_SEL_SFT              3
#घोषणा ACCDET_EINT_INVERTER_IVAL_SEL_MASK             0x1
#घोषणा ACCDET_EINT_INVERTER_IVAL_SEL_MASK_SFT         (0x1 << 3)
#घोषणा ACCDET_IRQ_ADDR                                \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_IRQ_SFT                                 0
#घोषणा ACCDET_IRQ_MASK                                0x1
#घोषणा ACCDET_IRQ_MASK_SFT                            (0x1 << 0)
#घोषणा ACCDET_EINT0_IRQ_ADDR                          \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_EINT0_IRQ_SFT                           2
#घोषणा ACCDET_EINT0_IRQ_MASK                          0x1
#घोषणा ACCDET_EINT0_IRQ_MASK_SFT                      (0x1 << 2)
#घोषणा ACCDET_EINT1_IRQ_ADDR                          \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_EINT1_IRQ_SFT                           3
#घोषणा ACCDET_EINT1_IRQ_MASK                          0x1
#घोषणा ACCDET_EINT1_IRQ_MASK_SFT                      (0x1 << 3)
#घोषणा ACCDET_EINT_IN_INVERSE_ADDR                    \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_EINT_IN_INVERSE_SFT                     4
#घोषणा ACCDET_EINT_IN_INVERSE_MASK                    0x1
#घोषणा ACCDET_EINT_IN_INVERSE_MASK_SFT                (0x1 << 4)
#घोषणा ACCDET_IRQ_CLR_ADDR                            \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_IRQ_CLR_SFT                             8
#घोषणा ACCDET_IRQ_CLR_MASK                            0x1
#घोषणा ACCDET_IRQ_CLR_MASK_SFT                        (0x1 << 8)
#घोषणा ACCDET_EINT0_IRQ_CLR_ADDR                      \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_EINT0_IRQ_CLR_SFT                       10
#घोषणा ACCDET_EINT0_IRQ_CLR_MASK                      0x1
#घोषणा ACCDET_EINT0_IRQ_CLR_MASK_SFT                  (0x1 << 10)
#घोषणा ACCDET_EINT1_IRQ_CLR_ADDR                      \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_EINT1_IRQ_CLR_SFT                       11
#घोषणा ACCDET_EINT1_IRQ_CLR_MASK                      0x1
#घोषणा ACCDET_EINT1_IRQ_CLR_MASK_SFT                  (0x1 << 11)
#घोषणा ACCDET_EINT_M_PLUG_IN_NUM_ADDR                 \
	MT6359_ACCDET_CON18
#घोषणा ACCDET_EINT_M_PLUG_IN_NUM_SFT                  12
#घोषणा ACCDET_EINT_M_PLUG_IN_NUM_MASK                 0x7
#घोषणा ACCDET_EINT_M_PLUG_IN_NUM_MASK_SFT             (0x7 << 12)
#घोषणा ACCDET_DA_STABLE_ADDR                          \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_DA_STABLE_SFT                           0
#घोषणा ACCDET_DA_STABLE_MASK                          0x1
#घोषणा ACCDET_DA_STABLE_MASK_SFT                      (0x1 << 0)
#घोषणा ACCDET_EINT0_EN_STABLE_ADDR                    \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT0_EN_STABLE_SFT                     1
#घोषणा ACCDET_EINT0_EN_STABLE_MASK                    0x1
#घोषणा ACCDET_EINT0_EN_STABLE_MASK_SFT                (0x1 << 1)
#घोषणा ACCDET_EINT0_CMPEN_STABLE_ADDR                 \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT0_CMPEN_STABLE_SFT                  2
#घोषणा ACCDET_EINT0_CMPEN_STABLE_MASK                 0x1
#घोषणा ACCDET_EINT0_CMPEN_STABLE_MASK_SFT             (0x1 << 2)
#घोषणा ACCDET_EINT0_CMPMEN_STABLE_ADDR                \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT0_CMPMEN_STABLE_SFT                 3
#घोषणा ACCDET_EINT0_CMPMEN_STABLE_MASK                0x1
#घोषणा ACCDET_EINT0_CMPMEN_STABLE_MASK_SFT            (0x1 << 3)
#घोषणा ACCDET_EINT0_CTURBO_STABLE_ADDR                \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT0_CTURBO_STABLE_SFT                 4
#घोषणा ACCDET_EINT0_CTURBO_STABLE_MASK                0x1
#घोषणा ACCDET_EINT0_CTURBO_STABLE_MASK_SFT            (0x1 << 4)
#घोषणा ACCDET_EINT0_CEN_STABLE_ADDR                   \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT0_CEN_STABLE_SFT                    5
#घोषणा ACCDET_EINT0_CEN_STABLE_MASK                   0x1
#घोषणा ACCDET_EINT0_CEN_STABLE_MASK_SFT               (0x1 << 5)
#घोषणा ACCDET_EINT1_EN_STABLE_ADDR                    \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT1_EN_STABLE_SFT                     6
#घोषणा ACCDET_EINT1_EN_STABLE_MASK                    0x1
#घोषणा ACCDET_EINT1_EN_STABLE_MASK_SFT                (0x1 << 6)
#घोषणा ACCDET_EINT1_CMPEN_STABLE_ADDR                 \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT1_CMPEN_STABLE_SFT                  7
#घोषणा ACCDET_EINT1_CMPEN_STABLE_MASK                 0x1
#घोषणा ACCDET_EINT1_CMPEN_STABLE_MASK_SFT             (0x1 << 7)
#घोषणा ACCDET_EINT1_CMPMEN_STABLE_ADDR                \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT1_CMPMEN_STABLE_SFT                 8
#घोषणा ACCDET_EINT1_CMPMEN_STABLE_MASK                0x1
#घोषणा ACCDET_EINT1_CMPMEN_STABLE_MASK_SFT            (0x1 << 8)
#घोषणा ACCDET_EINT1_CTURBO_STABLE_ADDR                \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT1_CTURBO_STABLE_SFT                 9
#घोषणा ACCDET_EINT1_CTURBO_STABLE_MASK                0x1
#घोषणा ACCDET_EINT1_CTURBO_STABLE_MASK_SFT            (0x1 << 9)
#घोषणा ACCDET_EINT1_CEN_STABLE_ADDR                   \
	MT6359_ACCDET_CON19
#घोषणा ACCDET_EINT1_CEN_STABLE_SFT                    10
#घोषणा ACCDET_EINT1_CEN_STABLE_MASK                   0x1
#घोषणा ACCDET_EINT1_CEN_STABLE_MASK_SFT               (0x1 << 10)
#घोषणा ACCDET_HWMODE_EN_ADDR                          \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_HWMODE_EN_SFT                           0
#घोषणा ACCDET_HWMODE_EN_MASK                          0x1
#घोषणा ACCDET_HWMODE_EN_MASK_SFT                      (0x1 << 0)
#घोषणा ACCDET_HWMODE_SEL_ADDR                         \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_HWMODE_SEL_SFT                          1
#घोषणा ACCDET_HWMODE_SEL_MASK                         0x3
#घोषणा ACCDET_HWMODE_SEL_MASK_SFT                     (0x3 << 1)
#घोषणा ACCDET_PLUG_OUT_DETECT_ADDR                    \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_PLUG_OUT_DETECT_SFT                     3
#घोषणा ACCDET_PLUG_OUT_DETECT_MASK                    0x1
#घोषणा ACCDET_PLUG_OUT_DETECT_MASK_SFT                (0x1 << 3)
#घोषणा ACCDET_EINT0_REVERSE_ADDR                      \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_EINT0_REVERSE_SFT                       4
#घोषणा ACCDET_EINT0_REVERSE_MASK                      0x1
#घोषणा ACCDET_EINT0_REVERSE_MASK_SFT                  (0x1 << 4)
#घोषणा ACCDET_EINT1_REVERSE_ADDR                      \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_EINT1_REVERSE_SFT                       5
#घोषणा ACCDET_EINT1_REVERSE_MASK                      0x1
#घोषणा ACCDET_EINT1_REVERSE_MASK_SFT                  (0x1 << 5)
#घोषणा ACCDET_EINT_HWMODE_EN_ADDR                     \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_EINT_HWMODE_EN_SFT                      8
#घोषणा ACCDET_EINT_HWMODE_EN_MASK                     0x1
#घोषणा ACCDET_EINT_HWMODE_EN_MASK_SFT                 (0x1 << 8)
#घोषणा ACCDET_EINT_PLUG_OUT_BYPASS_DEB_ADDR           \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_EINT_PLUG_OUT_BYPASS_DEB_SFT            9
#घोषणा ACCDET_EINT_PLUG_OUT_BYPASS_DEB_MASK           0x1
#घोषणा ACCDET_EINT_PLUG_OUT_BYPASS_DEB_MASK_SFT       (0x1 << 9)
#घोषणा ACCDET_EINT_M_PLUG_IN_EN_ADDR                  \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_EINT_M_PLUG_IN_EN_SFT                   10
#घोषणा ACCDET_EINT_M_PLUG_IN_EN_MASK                  0x1
#घोषणा ACCDET_EINT_M_PLUG_IN_EN_MASK_SFT              (0x1 << 10)
#घोषणा ACCDET_EINT_M_HWMODE_EN_ADDR                   \
	MT6359_ACCDET_CON20
#घोषणा ACCDET_EINT_M_HWMODE_EN_SFT                    11
#घोषणा ACCDET_EINT_M_HWMODE_EN_MASK                   0x1
#घोषणा ACCDET_EINT_M_HWMODE_EN_MASK_SFT               (0x1 << 11)
#घोषणा ACCDET_TEST_CMPEN_ADDR                         \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_TEST_CMPEN_SFT                          0
#घोषणा ACCDET_TEST_CMPEN_MASK                         0x1
#घोषणा ACCDET_TEST_CMPEN_MASK_SFT                     (0x1 << 0)
#घोषणा ACCDET_TEST_VTHEN_ADDR                         \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_TEST_VTHEN_SFT                          1
#घोषणा ACCDET_TEST_VTHEN_MASK                         0x1
#घोषणा ACCDET_TEST_VTHEN_MASK_SFT                     (0x1 << 1)
#घोषणा ACCDET_TEST_MBIASEN_ADDR                       \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_TEST_MBIASEN_SFT                        2
#घोषणा ACCDET_TEST_MBIASEN_MASK                       0x1
#घोषणा ACCDET_TEST_MBIASEN_MASK_SFT                   (0x1 << 2)
#घोषणा ACCDET_EINT_TEST_EN_ADDR                       \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_EN_SFT                        3
#घोषणा ACCDET_EINT_TEST_EN_MASK                       0x1
#घोषणा ACCDET_EINT_TEST_EN_MASK_SFT                   (0x1 << 3)
#घोषणा ACCDET_EINT_TEST_INVEN_ADDR                    \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_INVEN_SFT                     4
#घोषणा ACCDET_EINT_TEST_INVEN_MASK                    0x1
#घोषणा ACCDET_EINT_TEST_INVEN_MASK_SFT                (0x1 << 4)
#घोषणा ACCDET_EINT_TEST_CMPEN_ADDR                    \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_CMPEN_SFT                     5
#घोषणा ACCDET_EINT_TEST_CMPEN_MASK                    0x1
#घोषणा ACCDET_EINT_TEST_CMPEN_MASK_SFT                (0x1 << 5)
#घोषणा ACCDET_EINT_TEST_CMPMEN_ADDR                   \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_CMPMEN_SFT                    6
#घोषणा ACCDET_EINT_TEST_CMPMEN_MASK                   0x1
#घोषणा ACCDET_EINT_TEST_CMPMEN_MASK_SFT               (0x1 << 6)
#घोषणा ACCDET_EINT_TEST_CTURBO_ADDR                   \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_CTURBO_SFT                    7
#घोषणा ACCDET_EINT_TEST_CTURBO_MASK                   0x1
#घोषणा ACCDET_EINT_TEST_CTURBO_MASK_SFT               (0x1 << 7)
#घोषणा ACCDET_EINT_TEST_CEN_ADDR                      \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_CEN_SFT                       8
#घोषणा ACCDET_EINT_TEST_CEN_MASK                      0x1
#घोषणा ACCDET_EINT_TEST_CEN_MASK_SFT                  (0x1 << 8)
#घोषणा ACCDET_TEST_B_ADDR                             \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_TEST_B_SFT                              9
#घोषणा ACCDET_TEST_B_MASK                             0x1
#घोषणा ACCDET_TEST_B_MASK_SFT                         (0x1 << 9)
#घोषणा ACCDET_TEST_A_ADDR                             \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_TEST_A_SFT                              10
#घोषणा ACCDET_TEST_A_MASK                             0x1
#घोषणा ACCDET_TEST_A_MASK_SFT                         (0x1 << 10)
#घोषणा ACCDET_EINT_TEST_CMPOUT_ADDR                   \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_CMPOUT_SFT                    11
#घोषणा ACCDET_EINT_TEST_CMPOUT_MASK                   0x1
#घोषणा ACCDET_EINT_TEST_CMPOUT_MASK_SFT               (0x1 << 11)
#घोषणा ACCDET_EINT_TEST_CMPMOUT_ADDR                  \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_CMPMOUT_SFT                   12
#घोषणा ACCDET_EINT_TEST_CMPMOUT_MASK                  0x1
#घोषणा ACCDET_EINT_TEST_CMPMOUT_MASK_SFT              (0x1 << 12)
#घोषणा ACCDET_EINT_TEST_INVOUT_ADDR                   \
	MT6359_ACCDET_CON21
#घोषणा ACCDET_EINT_TEST_INVOUT_SFT                    13
#घोषणा ACCDET_EINT_TEST_INVOUT_MASK                   0x1
#घोषणा ACCDET_EINT_TEST_INVOUT_MASK_SFT               (0x1 << 13)
#घोषणा ACCDET_CMPEN_SEL_ADDR                          \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_CMPEN_SEL_SFT                           0
#घोषणा ACCDET_CMPEN_SEL_MASK                          0x1
#घोषणा ACCDET_CMPEN_SEL_MASK_SFT                      (0x1 << 0)
#घोषणा ACCDET_VTHEN_SEL_ADDR                          \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_VTHEN_SEL_SFT                           1
#घोषणा ACCDET_VTHEN_SEL_MASK                          0x1
#घोषणा ACCDET_VTHEN_SEL_MASK_SFT                      (0x1 << 1)
#घोषणा ACCDET_MBIASEN_SEL_ADDR                        \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_MBIASEN_SEL_SFT                         2
#घोषणा ACCDET_MBIASEN_SEL_MASK                        0x1
#घोषणा ACCDET_MBIASEN_SEL_MASK_SFT                    (0x1 << 2)
#घोषणा ACCDET_EINT_EN_SEL_ADDR                        \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_EN_SEL_SFT                         3
#घोषणा ACCDET_EINT_EN_SEL_MASK                        0x1
#घोषणा ACCDET_EINT_EN_SEL_MASK_SFT                    (0x1 << 3)
#घोषणा ACCDET_EINT_INVEN_SEL_ADDR                     \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_INVEN_SEL_SFT                      4
#घोषणा ACCDET_EINT_INVEN_SEL_MASK                     0x1
#घोषणा ACCDET_EINT_INVEN_SEL_MASK_SFT                 (0x1 << 4)
#घोषणा ACCDET_EINT_CMPEN_SEL_ADDR                     \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_CMPEN_SEL_SFT                      5
#घोषणा ACCDET_EINT_CMPEN_SEL_MASK                     0x1
#घोषणा ACCDET_EINT_CMPEN_SEL_MASK_SFT                 (0x1 << 5)
#घोषणा ACCDET_EINT_CMPMEN_SEL_ADDR                    \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_CMPMEN_SEL_SFT                     6
#घोषणा ACCDET_EINT_CMPMEN_SEL_MASK                    0x1
#घोषणा ACCDET_EINT_CMPMEN_SEL_MASK_SFT                (0x1 << 6)
#घोषणा ACCDET_EINT_CTURBO_SEL_ADDR                    \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_CTURBO_SEL_SFT                     7
#घोषणा ACCDET_EINT_CTURBO_SEL_MASK                    0x1
#घोषणा ACCDET_EINT_CTURBO_SEL_MASK_SFT                (0x1 << 7)
#घोषणा ACCDET_B_SEL_ADDR                              \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_B_SEL_SFT                               9
#घोषणा ACCDET_B_SEL_MASK                              0x1
#घोषणा ACCDET_B_SEL_MASK_SFT                          (0x1 << 9)
#घोषणा ACCDET_A_SEL_ADDR                              \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_A_SEL_SFT                               10
#घोषणा ACCDET_A_SEL_MASK                              0x1
#घोषणा ACCDET_A_SEL_MASK_SFT                          (0x1 << 10)
#घोषणा ACCDET_EINT_CMPOUT_SEL_ADDR                    \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_CMPOUT_SEL_SFT                     11
#घोषणा ACCDET_EINT_CMPOUT_SEL_MASK                    0x1
#घोषणा ACCDET_EINT_CMPOUT_SEL_MASK_SFT                (0x1 << 11)
#घोषणा ACCDET_EINT_CMPMOUT_SEL_ADDR                   \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_CMPMOUT_SEL_SFT                    12
#घोषणा ACCDET_EINT_CMPMOUT_SEL_MASK                   0x1
#घोषणा ACCDET_EINT_CMPMOUT_SEL_MASK_SFT               (0x1 << 12)
#घोषणा ACCDET_EINT_INVOUT_SEL_ADDR                    \
	MT6359_ACCDET_CON22
#घोषणा ACCDET_EINT_INVOUT_SEL_SFT                     13
#घोषणा ACCDET_EINT_INVOUT_SEL_MASK                    0x1
#घोषणा ACCDET_EINT_INVOUT_SEL_MASK_SFT                (0x1 << 13)
#घोषणा ACCDET_CMPEN_SW_ADDR                           \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_CMPEN_SW_SFT                            0
#घोषणा ACCDET_CMPEN_SW_MASK                           0x1
#घोषणा ACCDET_CMPEN_SW_MASK_SFT                       (0x1 << 0)
#घोषणा ACCDET_VTHEN_SW_ADDR                           \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_VTHEN_SW_SFT                            1
#घोषणा ACCDET_VTHEN_SW_MASK                           0x1
#घोषणा ACCDET_VTHEN_SW_MASK_SFT                       (0x1 << 1)
#घोषणा ACCDET_MBIASEN_SW_ADDR                         \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_MBIASEN_SW_SFT                          2
#घोषणा ACCDET_MBIASEN_SW_MASK                         0x1
#घोषणा ACCDET_MBIASEN_SW_MASK_SFT                     (0x1 << 2)
#घोषणा ACCDET_EINT0_EN_SW_ADDR                        \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT0_EN_SW_SFT                         3
#घोषणा ACCDET_EINT0_EN_SW_MASK                        0x1
#घोषणा ACCDET_EINT0_EN_SW_MASK_SFT                    (0x1 << 3)
#घोषणा ACCDET_EINT0_INVEN_SW_ADDR                     \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT0_INVEN_SW_SFT                      4
#घोषणा ACCDET_EINT0_INVEN_SW_MASK                     0x1
#घोषणा ACCDET_EINT0_INVEN_SW_MASK_SFT                 (0x1 << 4)
#घोषणा ACCDET_EINT0_CMPEN_SW_ADDR                     \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT0_CMPEN_SW_SFT                      5
#घोषणा ACCDET_EINT0_CMPEN_SW_MASK                     0x1
#घोषणा ACCDET_EINT0_CMPEN_SW_MASK_SFT                 (0x1 << 5)
#घोषणा ACCDET_EINT0_CMPMEN_SW_ADDR                    \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT0_CMPMEN_SW_SFT                     6
#घोषणा ACCDET_EINT0_CMPMEN_SW_MASK                    0x1
#घोषणा ACCDET_EINT0_CMPMEN_SW_MASK_SFT                (0x1 << 6)
#घोषणा ACCDET_EINT0_CTURBO_SW_ADDR                    \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT0_CTURBO_SW_SFT                     7
#घोषणा ACCDET_EINT0_CTURBO_SW_MASK                    0x1
#घोषणा ACCDET_EINT0_CTURBO_SW_MASK_SFT                (0x1 << 7)
#घोषणा ACCDET_EINT1_EN_SW_ADDR                        \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT1_EN_SW_SFT                         8
#घोषणा ACCDET_EINT1_EN_SW_MASK                        0x1
#घोषणा ACCDET_EINT1_EN_SW_MASK_SFT                    (0x1 << 8)
#घोषणा ACCDET_EINT1_INVEN_SW_ADDR                     \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT1_INVEN_SW_SFT                      9
#घोषणा ACCDET_EINT1_INVEN_SW_MASK                     0x1
#घोषणा ACCDET_EINT1_INVEN_SW_MASK_SFT                 (0x1 << 9)
#घोषणा ACCDET_EINT1_CMPEN_SW_ADDR                     \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT1_CMPEN_SW_SFT                      10
#घोषणा ACCDET_EINT1_CMPEN_SW_MASK                     0x1
#घोषणा ACCDET_EINT1_CMPEN_SW_MASK_SFT                 (0x1 << 10)
#घोषणा ACCDET_EINT1_CMPMEN_SW_ADDR                    \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT1_CMPMEN_SW_SFT                     11
#घोषणा ACCDET_EINT1_CMPMEN_SW_MASK                    0x1
#घोषणा ACCDET_EINT1_CMPMEN_SW_MASK_SFT                (0x1 << 11)
#घोषणा ACCDET_EINT1_CTURBO_SW_ADDR                    \
	MT6359_ACCDET_CON23
#घोषणा ACCDET_EINT1_CTURBO_SW_SFT                     12
#घोषणा ACCDET_EINT1_CTURBO_SW_MASK                    0x1
#घोषणा ACCDET_EINT1_CTURBO_SW_MASK_SFT                (0x1 << 12)
#घोषणा ACCDET_B_SW_ADDR                               \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_B_SW_SFT                                0
#घोषणा ACCDET_B_SW_MASK                               0x1
#घोषणा ACCDET_B_SW_MASK_SFT                           (0x1 << 0)
#घोषणा ACCDET_A_SW_ADDR                               \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_A_SW_SFT                                1
#घोषणा ACCDET_A_SW_MASK                               0x1
#घोषणा ACCDET_A_SW_MASK_SFT                           (0x1 << 1)
#घोषणा ACCDET_EINT0_CMPOUT_SW_ADDR                    \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_EINT0_CMPOUT_SW_SFT                     2
#घोषणा ACCDET_EINT0_CMPOUT_SW_MASK                    0x1
#घोषणा ACCDET_EINT0_CMPOUT_SW_MASK_SFT                (0x1 << 2)
#घोषणा ACCDET_EINT0_CMPMOUT_SW_ADDR                   \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_EINT0_CMPMOUT_SW_SFT                    3
#घोषणा ACCDET_EINT0_CMPMOUT_SW_MASK                   0x1
#घोषणा ACCDET_EINT0_CMPMOUT_SW_MASK_SFT               (0x1 << 3)
#घोषणा ACCDET_EINT0_INVOUT_SW_ADDR                    \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_EINT0_INVOUT_SW_SFT                     4
#घोषणा ACCDET_EINT0_INVOUT_SW_MASK                    0x1
#घोषणा ACCDET_EINT0_INVOUT_SW_MASK_SFT                (0x1 << 4)
#घोषणा ACCDET_EINT1_CMPOUT_SW_ADDR                    \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_EINT1_CMPOUT_SW_SFT                     5
#घोषणा ACCDET_EINT1_CMPOUT_SW_MASK                    0x1
#घोषणा ACCDET_EINT1_CMPOUT_SW_MASK_SFT                (0x1 << 5)
#घोषणा ACCDET_EINT1_CMPMOUT_SW_ADDR                   \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_EINT1_CMPMOUT_SW_SFT                    6
#घोषणा ACCDET_EINT1_CMPMOUT_SW_MASK                   0x1
#घोषणा ACCDET_EINT1_CMPMOUT_SW_MASK_SFT               (0x1 << 6)
#घोषणा ACCDET_EINT1_INVOUT_SW_ADDR                    \
	MT6359_ACCDET_CON24
#घोषणा ACCDET_EINT1_INVOUT_SW_SFT                     7
#घोषणा ACCDET_EINT1_INVOUT_SW_MASK                    0x1
#घोषणा ACCDET_EINT1_INVOUT_SW_MASK_SFT                (0x1 << 7)
#घोषणा AD_AUDACCDETCMPOB_ADDR                         \
	MT6359_ACCDET_CON25
#घोषणा AD_AUDACCDETCMPOB_SFT                          0
#घोषणा AD_AUDACCDETCMPOB_MASK                         0x1
#घोषणा AD_AUDACCDETCMPOB_MASK_SFT                     (0x1 << 0)
#घोषणा AD_AUDACCDETCMPOA_ADDR                         \
	MT6359_ACCDET_CON25
#घोषणा AD_AUDACCDETCMPOA_SFT                          1
#घोषणा AD_AUDACCDETCMPOA_MASK                         0x1
#घोषणा AD_AUDACCDETCMPOA_MASK_SFT                     (0x1 << 1)
#घोषणा ACCDET_CUR_IN_ADDR                             \
	MT6359_ACCDET_CON25
#घोषणा ACCDET_CUR_IN_SFT                              2
#घोषणा ACCDET_CUR_IN_MASK                             0x3
#घोषणा ACCDET_CUR_IN_MASK_SFT                         (0x3 << 2)
#घोषणा ACCDET_SAM_IN_ADDR                             \
	MT6359_ACCDET_CON25
#घोषणा ACCDET_SAM_IN_SFT                              4
#घोषणा ACCDET_SAM_IN_MASK                             0x3
#घोषणा ACCDET_SAM_IN_MASK_SFT                         (0x3 << 4)
#घोषणा ACCDET_MEM_IN_ADDR                             \
	MT6359_ACCDET_CON25
#घोषणा ACCDET_MEM_IN_SFT                              6
#घोषणा ACCDET_MEM_IN_MASK                             0x3
#घोषणा ACCDET_MEM_IN_MASK_SFT                         (0x3 << 6)
#घोषणा ACCDET_STATE_ADDR                              \
	MT6359_ACCDET_CON25
#घोषणा ACCDET_STATE_SFT                               8
#घोषणा ACCDET_STATE_MASK                              0x7
#घोषणा ACCDET_STATE_MASK_SFT                          (0x7 << 8)
#घोषणा DA_AUDACCDETMBIASCLK_ADDR                      \
	MT6359_ACCDET_CON25
#घोषणा DA_AUDACCDETMBIASCLK_SFT                       12
#घोषणा DA_AUDACCDETMBIASCLK_MASK                      0x1
#घोषणा DA_AUDACCDETMBIASCLK_MASK_SFT                  (0x1 << 12)
#घोषणा DA_AUDACCDETVTHCLK_ADDR                        \
	MT6359_ACCDET_CON25
#घोषणा DA_AUDACCDETVTHCLK_SFT                         13
#घोषणा DA_AUDACCDETVTHCLK_MASK                        0x1
#घोषणा DA_AUDACCDETVTHCLK_MASK_SFT                    (0x1 << 13)
#घोषणा DA_AUDACCDETCMPCLK_ADDR                        \
	MT6359_ACCDET_CON25
#घोषणा DA_AUDACCDETCMPCLK_SFT                         14
#घोषणा DA_AUDACCDETCMPCLK_MASK                        0x1
#घोषणा DA_AUDACCDETCMPCLK_MASK_SFT                    (0x1 << 14)
#घोषणा DA_AUDACCDETAUXADCSWCTRL_ADDR                  \
	MT6359_ACCDET_CON25
#घोषणा DA_AUDACCDETAUXADCSWCTRL_SFT                   15
#घोषणा DA_AUDACCDETAUXADCSWCTRL_MASK                  0x1
#घोषणा DA_AUDACCDETAUXADCSWCTRL_MASK_SFT              (0x1 << 15)
#घोषणा AD_EINT0CMPMOUT_ADDR                           \
	MT6359_ACCDET_CON26
#घोषणा AD_EINT0CMPMOUT_SFT                            0
#घोषणा AD_EINT0CMPMOUT_MASK                           0x1
#घोषणा AD_EINT0CMPMOUT_MASK_SFT                       (0x1 << 0)
#घोषणा AD_EINT0CMPOUT_ADDR                            \
	MT6359_ACCDET_CON26
#घोषणा AD_EINT0CMPOUT_SFT                             1
#घोषणा AD_EINT0CMPOUT_MASK                            0x1
#घोषणा AD_EINT0CMPOUT_MASK_SFT                        (0x1 << 1)
#घोषणा ACCDET_EINT0_CUR_IN_ADDR                       \
	MT6359_ACCDET_CON26
#घोषणा ACCDET_EINT0_CUR_IN_SFT                        2
#घोषणा ACCDET_EINT0_CUR_IN_MASK                       0x3
#घोषणा ACCDET_EINT0_CUR_IN_MASK_SFT                   (0x3 << 2)
#घोषणा ACCDET_EINT0_SAM_IN_ADDR                       \
	MT6359_ACCDET_CON26
#घोषणा ACCDET_EINT0_SAM_IN_SFT                        4
#घोषणा ACCDET_EINT0_SAM_IN_MASK                       0x3
#घोषणा ACCDET_EINT0_SAM_IN_MASK_SFT                   (0x3 << 4)
#घोषणा ACCDET_EINT0_MEM_IN_ADDR                       \
	MT6359_ACCDET_CON26
#घोषणा ACCDET_EINT0_MEM_IN_SFT                        6
#घोषणा ACCDET_EINT0_MEM_IN_MASK                       0x3
#घोषणा ACCDET_EINT0_MEM_IN_MASK_SFT                   (0x3 << 6)
#घोषणा ACCDET_EINT0_STATE_ADDR                        \
	MT6359_ACCDET_CON26
#घोषणा ACCDET_EINT0_STATE_SFT                         8
#घोषणा ACCDET_EINT0_STATE_MASK                        0x7
#घोषणा ACCDET_EINT0_STATE_MASK_SFT                    (0x7 << 8)
#घोषणा DA_EINT0CMPEN_ADDR                             \
	MT6359_ACCDET_CON26
#घोषणा DA_EINT0CMPEN_SFT                              13
#घोषणा DA_EINT0CMPEN_MASK                             0x1
#घोषणा DA_EINT0CMPEN_MASK_SFT                         (0x1 << 13)
#घोषणा DA_EINT0CMPMEN_ADDR                            \
	MT6359_ACCDET_CON26
#घोषणा DA_EINT0CMPMEN_SFT                             14
#घोषणा DA_EINT0CMPMEN_MASK                            0x1
#घोषणा DA_EINT0CMPMEN_MASK_SFT                        (0x1 << 14)
#घोषणा DA_EINT0CTURBO_ADDR                            \
	MT6359_ACCDET_CON26
#घोषणा DA_EINT0CTURBO_SFT                             15
#घोषणा DA_EINT0CTURBO_MASK                            0x1
#घोषणा DA_EINT0CTURBO_MASK_SFT                        (0x1 << 15)
#घोषणा AD_EINT1CMPMOUT_ADDR                           \
	MT6359_ACCDET_CON27
#घोषणा AD_EINT1CMPMOUT_SFT                            0
#घोषणा AD_EINT1CMPMOUT_MASK                           0x1
#घोषणा AD_EINT1CMPMOUT_MASK_SFT                       (0x1 << 0)
#घोषणा AD_EINT1CMPOUT_ADDR                            \
	MT6359_ACCDET_CON27
#घोषणा AD_EINT1CMPOUT_SFT                             1
#घोषणा AD_EINT1CMPOUT_MASK                            0x1
#घोषणा AD_EINT1CMPOUT_MASK_SFT                        (0x1 << 1)
#घोषणा ACCDET_EINT1_CUR_IN_ADDR                       \
	MT6359_ACCDET_CON27
#घोषणा ACCDET_EINT1_CUR_IN_SFT                        2
#घोषणा ACCDET_EINT1_CUR_IN_MASK                       0x3
#घोषणा ACCDET_EINT1_CUR_IN_MASK_SFT                   (0x3 << 2)
#घोषणा ACCDET_EINT1_SAM_IN_ADDR                       \
	MT6359_ACCDET_CON27
#घोषणा ACCDET_EINT1_SAM_IN_SFT                        4
#घोषणा ACCDET_EINT1_SAM_IN_MASK                       0x3
#घोषणा ACCDET_EINT1_SAM_IN_MASK_SFT                   (0x3 << 4)
#घोषणा ACCDET_EINT1_MEM_IN_ADDR                       \
	MT6359_ACCDET_CON27
#घोषणा ACCDET_EINT1_MEM_IN_SFT                        6
#घोषणा ACCDET_EINT1_MEM_IN_MASK                       0x3
#घोषणा ACCDET_EINT1_MEM_IN_MASK_SFT                   (0x3 << 6)
#घोषणा ACCDET_EINT1_STATE_ADDR                        \
	MT6359_ACCDET_CON27
#घोषणा ACCDET_EINT1_STATE_SFT                         8
#घोषणा ACCDET_EINT1_STATE_MASK                        0x7
#घोषणा ACCDET_EINT1_STATE_MASK_SFT                    (0x7 << 8)
#घोषणा DA_EINT1CMPEN_ADDR                             \
	MT6359_ACCDET_CON27
#घोषणा DA_EINT1CMPEN_SFT                              13
#घोषणा DA_EINT1CMPEN_MASK                             0x1
#घोषणा DA_EINT1CMPEN_MASK_SFT                         (0x1 << 13)
#घोषणा DA_EINT1CMPMEN_ADDR                            \
	MT6359_ACCDET_CON27
#घोषणा DA_EINT1CMPMEN_SFT                             14
#घोषणा DA_EINT1CMPMEN_MASK                            0x1
#घोषणा DA_EINT1CMPMEN_MASK_SFT                        (0x1 << 14)
#घोषणा DA_EINT1CTURBO_ADDR                            \
	MT6359_ACCDET_CON27
#घोषणा DA_EINT1CTURBO_SFT                             15
#घोषणा DA_EINT1CTURBO_MASK                            0x1
#घोषणा DA_EINT1CTURBO_MASK_SFT                        (0x1 << 15)
#घोषणा AD_EINT0INVOUT_ADDR                            \
	MT6359_ACCDET_CON28
#घोषणा AD_EINT0INVOUT_SFT                             0
#घोषणा AD_EINT0INVOUT_MASK                            0x1
#घोषणा AD_EINT0INVOUT_MASK_SFT                        (0x1 << 0)
#घोषणा ACCDET_EINT0_INVERTER_CUR_IN_ADDR              \
	MT6359_ACCDET_CON28
#घोषणा ACCDET_EINT0_INVERTER_CUR_IN_SFT               1
#घोषणा ACCDET_EINT0_INVERTER_CUR_IN_MASK              0x1
#घोषणा ACCDET_EINT0_INVERTER_CUR_IN_MASK_SFT          (0x1 << 1)
#घोषणा ACCDET_EINT0_INVERTER_SAM_IN_ADDR              \
	MT6359_ACCDET_CON28
#घोषणा ACCDET_EINT0_INVERTER_SAM_IN_SFT               2
#घोषणा ACCDET_EINT0_INVERTER_SAM_IN_MASK              0x1
#घोषणा ACCDET_EINT0_INVERTER_SAM_IN_MASK_SFT          (0x1 << 2)
#घोषणा ACCDET_EINT0_INVERTER_MEM_IN_ADDR              \
	MT6359_ACCDET_CON28
#घोषणा ACCDET_EINT0_INVERTER_MEM_IN_SFT               3
#घोषणा ACCDET_EINT0_INVERTER_MEM_IN_MASK              0x1
#घोषणा ACCDET_EINT0_INVERTER_MEM_IN_MASK_SFT          (0x1 << 3)
#घोषणा ACCDET_EINT0_INVERTER_STATE_ADDR               \
	MT6359_ACCDET_CON28
#घोषणा ACCDET_EINT0_INVERTER_STATE_SFT                8
#घोषणा ACCDET_EINT0_INVERTER_STATE_MASK               0x7
#घोषणा ACCDET_EINT0_INVERTER_STATE_MASK_SFT           (0x7 << 8)
#घोषणा DA_EINT0EN_ADDR                                \
	MT6359_ACCDET_CON28
#घोषणा DA_EINT0EN_SFT                                 12
#घोषणा DA_EINT0EN_MASK                                0x1
#घोषणा DA_EINT0EN_MASK_SFT                            (0x1 << 12)
#घोषणा DA_EINT0INVEN_ADDR                             \
	MT6359_ACCDET_CON28
#घोषणा DA_EINT0INVEN_SFT                              13
#घोषणा DA_EINT0INVEN_MASK                             0x1
#घोषणा DA_EINT0INVEN_MASK_SFT                         (0x1 << 13)
#घोषणा DA_EINT0CEN_ADDR                               \
	MT6359_ACCDET_CON28
#घोषणा DA_EINT0CEN_SFT                                14
#घोषणा DA_EINT0CEN_MASK                               0x1
#घोषणा DA_EINT0CEN_MASK_SFT                           (0x1 << 14)
#घोषणा AD_EINT1INVOUT_ADDR                            \
	MT6359_ACCDET_CON29
#घोषणा AD_EINT1INVOUT_SFT                             0
#घोषणा AD_EINT1INVOUT_MASK                            0x1
#घोषणा AD_EINT1INVOUT_MASK_SFT                        (0x1 << 0)
#घोषणा ACCDET_EINT1_INVERTER_CUR_IN_ADDR              \
	MT6359_ACCDET_CON29
#घोषणा ACCDET_EINT1_INVERTER_CUR_IN_SFT               1
#घोषणा ACCDET_EINT1_INVERTER_CUR_IN_MASK              0x1
#घोषणा ACCDET_EINT1_INVERTER_CUR_IN_MASK_SFT          (0x1 << 1)
#घोषणा ACCDET_EINT1_INVERTER_SAM_IN_ADDR              \
	MT6359_ACCDET_CON29
#घोषणा ACCDET_EINT1_INVERTER_SAM_IN_SFT               2
#घोषणा ACCDET_EINT1_INVERTER_SAM_IN_MASK              0x1
#घोषणा ACCDET_EINT1_INVERTER_SAM_IN_MASK_SFT          (0x1 << 2)
#घोषणा ACCDET_EINT1_INVERTER_MEM_IN_ADDR              \
	MT6359_ACCDET_CON29
#घोषणा ACCDET_EINT1_INVERTER_MEM_IN_SFT               3
#घोषणा ACCDET_EINT1_INVERTER_MEM_IN_MASK              0x1
#घोषणा ACCDET_EINT1_INVERTER_MEM_IN_MASK_SFT          (0x1 << 3)
#घोषणा ACCDET_EINT1_INVERTER_STATE_ADDR               \
	MT6359_ACCDET_CON29
#घोषणा ACCDET_EINT1_INVERTER_STATE_SFT                8
#घोषणा ACCDET_EINT1_INVERTER_STATE_MASK               0x7
#घोषणा ACCDET_EINT1_INVERTER_STATE_MASK_SFT           (0x7 << 8)
#घोषणा DA_EINT1EN_ADDR                                \
	MT6359_ACCDET_CON29
#घोषणा DA_EINT1EN_SFT                                 12
#घोषणा DA_EINT1EN_MASK                                0x1
#घोषणा DA_EINT1EN_MASK_SFT                            (0x1 << 12)
#घोषणा DA_EINT1INVEN_ADDR                             \
	MT6359_ACCDET_CON29
#घोषणा DA_EINT1INVEN_SFT                              13
#घोषणा DA_EINT1INVEN_MASK                             0x1
#घोषणा DA_EINT1INVEN_MASK_SFT                         (0x1 << 13)
#घोषणा DA_EINT1CEN_ADDR                               \
	MT6359_ACCDET_CON29
#घोषणा DA_EINT1CEN_SFT                                14
#घोषणा DA_EINT1CEN_MASK                               0x1
#घोषणा DA_EINT1CEN_MASK_SFT                           (0x1 << 14)
#घोषणा ACCDET_EN_ADDR                                 \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EN_SFT                                  0
#घोषणा ACCDET_EN_MASK                                 0x1
#घोषणा ACCDET_EN_MASK_SFT                             (0x1 << 0)
#घोषणा ACCDET_EINT0_EN_ADDR                           \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT0_EN_SFT                            1
#घोषणा ACCDET_EINT0_EN_MASK                           0x1
#घोषणा ACCDET_EINT0_EN_MASK_SFT                       (0x1 << 1)
#घोषणा ACCDET_EINT1_EN_ADDR                           \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT1_EN_SFT                            2
#घोषणा ACCDET_EINT1_EN_MASK                           0x1
#घोषणा ACCDET_EINT1_EN_MASK_SFT                       (0x1 << 2)
#घोषणा ACCDET_EINT0_M_EN_ADDR                         \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT0_M_EN_SFT                          3
#घोषणा ACCDET_EINT0_M_EN_MASK                         0x1
#घोषणा ACCDET_EINT0_M_EN_MASK_SFT                     (0x1 << 3)
#घोषणा ACCDET_EINT0_DETECT_MOISTURE_ADDR              \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT0_DETECT_MOISTURE_SFT               4
#घोषणा ACCDET_EINT0_DETECT_MOISTURE_MASK              0x1
#घोषणा ACCDET_EINT0_DETECT_MOISTURE_MASK_SFT          (0x1 << 4)
#घोषणा ACCDET_EINT0_PLUG_IN_ADDR                      \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT0_PLUG_IN_SFT                       5
#घोषणा ACCDET_EINT0_PLUG_IN_MASK                      0x1
#घोषणा ACCDET_EINT0_PLUG_IN_MASK_SFT                  (0x1 << 5)
#घोषणा ACCDET_EINT0_M_PLUG_IN_ADDR                    \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT0_M_PLUG_IN_SFT                     6
#घोषणा ACCDET_EINT0_M_PLUG_IN_MASK                    0x1
#घोषणा ACCDET_EINT0_M_PLUG_IN_MASK_SFT                (0x1 << 6)
#घोषणा ACCDET_EINT1_M_EN_ADDR                         \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT1_M_EN_SFT                          7
#घोषणा ACCDET_EINT1_M_EN_MASK                         0x1
#घोषणा ACCDET_EINT1_M_EN_MASK_SFT                     (0x1 << 7)
#घोषणा ACCDET_EINT1_DETECT_MOISTURE_ADDR              \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT1_DETECT_MOISTURE_SFT               8
#घोषणा ACCDET_EINT1_DETECT_MOISTURE_MASK              0x1
#घोषणा ACCDET_EINT1_DETECT_MOISTURE_MASK_SFT          (0x1 << 8)
#घोषणा ACCDET_EINT1_PLUG_IN_ADDR                      \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT1_PLUG_IN_SFT                       9
#घोषणा ACCDET_EINT1_PLUG_IN_MASK                      0x1
#घोषणा ACCDET_EINT1_PLUG_IN_MASK_SFT                  (0x1 << 9)
#घोषणा ACCDET_EINT1_M_PLUG_IN_ADDR                    \
	MT6359_ACCDET_CON30
#घोषणा ACCDET_EINT1_M_PLUG_IN_SFT                     10
#घोषणा ACCDET_EINT1_M_PLUG_IN_MASK                    0x1
#घोषणा ACCDET_EINT1_M_PLUG_IN_MASK_SFT                (0x1 << 10)
#घोषणा ACCDET_CUR_DEB_ADDR                            \
	MT6359_ACCDET_CON31
#घोषणा ACCDET_CUR_DEB_SFT                             0
#घोषणा ACCDET_CUR_DEB_MASK                            0xFFFF
#घोषणा ACCDET_CUR_DEB_MASK_SFT                        (0xFFFF << 0)
#घोषणा ACCDET_EINT0_CUR_DEB_ADDR                      \
	MT6359_ACCDET_CON32
#घोषणा ACCDET_EINT0_CUR_DEB_SFT                       0
#घोषणा ACCDET_EINT0_CUR_DEB_MASK                      0x7FFF
#घोषणा ACCDET_EINT0_CUR_DEB_MASK_SFT                  (0x7FFF << 0)
#घोषणा ACCDET_EINT1_CUR_DEB_ADDR                      \
	MT6359_ACCDET_CON33
#घोषणा ACCDET_EINT1_CUR_DEB_SFT                       0
#घोषणा ACCDET_EINT1_CUR_DEB_MASK                      0x7FFF
#घोषणा ACCDET_EINT1_CUR_DEB_MASK_SFT                  (0x7FFF << 0)
#घोषणा ACCDET_EINT0_INVERTER_CUR_DEB_ADDR             \
	MT6359_ACCDET_CON34
#घोषणा ACCDET_EINT0_INVERTER_CUR_DEB_SFT              0
#घोषणा ACCDET_EINT0_INVERTER_CUR_DEB_MASK             0x7FFF
#घोषणा ACCDET_EINT0_INVERTER_CUR_DEB_MASK_SFT         (0x7FFF << 0)
#घोषणा ACCDET_EINT1_INVERTER_CUR_DEB_ADDR             \
	MT6359_ACCDET_CON35
#घोषणा ACCDET_EINT1_INVERTER_CUR_DEB_SFT              0
#घोषणा ACCDET_EINT1_INVERTER_CUR_DEB_MASK             0x7FFF
#घोषणा ACCDET_EINT1_INVERTER_CUR_DEB_MASK_SFT         (0x7FFF << 0)
#घोषणा AD_AUDACCDETCMPOB_MON_ADDR                     \
	MT6359_ACCDET_CON36
#घोषणा AD_AUDACCDETCMPOB_MON_SFT                      0
#घोषणा AD_AUDACCDETCMPOB_MON_MASK                     0x1
#घोषणा AD_AUDACCDETCMPOB_MON_MASK_SFT                 (0x1 << 0)
#घोषणा AD_AUDACCDETCMPOA_MON_ADDR                     \
	MT6359_ACCDET_CON36
#घोषणा AD_AUDACCDETCMPOA_MON_SFT                      1
#घोषणा AD_AUDACCDETCMPOA_MON_MASK                     0x1
#घोषणा AD_AUDACCDETCMPOA_MON_MASK_SFT                 (0x1 << 1)
#घोषणा AD_EINT0CMPMOUT_MON_ADDR                       \
	MT6359_ACCDET_CON36
#घोषणा AD_EINT0CMPMOUT_MON_SFT                        2
#घोषणा AD_EINT0CMPMOUT_MON_MASK                       0x1
#घोषणा AD_EINT0CMPMOUT_MON_MASK_SFT                   (0x1 << 2)
#घोषणा AD_EINT0CMPOUT_MON_ADDR                        \
	MT6359_ACCDET_CON36
#घोषणा AD_EINT0CMPOUT_MON_SFT                         3
#घोषणा AD_EINT0CMPOUT_MON_MASK                        0x1
#घोषणा AD_EINT0CMPOUT_MON_MASK_SFT                    (0x1 << 3)
#घोषणा AD_EINT0INVOUT_MON_ADDR                        \
	MT6359_ACCDET_CON36
#घोषणा AD_EINT0INVOUT_MON_SFT                         4
#घोषणा AD_EINT0INVOUT_MON_MASK                        0x1
#घोषणा AD_EINT0INVOUT_MON_MASK_SFT                    (0x1 << 4)
#घोषणा AD_EINT1CMPMOUT_MON_ADDR                       \
	MT6359_ACCDET_CON36
#घोषणा AD_EINT1CMPMOUT_MON_SFT                        5
#घोषणा AD_EINT1CMPMOUT_MON_MASK                       0x1
#घोषणा AD_EINT1CMPMOUT_MON_MASK_SFT                   (0x1 << 5)
#घोषणा AD_EINT1CMPOUT_MON_ADDR                        \
	MT6359_ACCDET_CON36
#घोषणा AD_EINT1CMPOUT_MON_SFT                         6
#घोषणा AD_EINT1CMPOUT_MON_MASK                        0x1
#घोषणा AD_EINT1CMPOUT_MON_MASK_SFT                    (0x1 << 6)
#घोषणा AD_EINT1INVOUT_MON_ADDR                        \
	MT6359_ACCDET_CON36
#घोषणा AD_EINT1INVOUT_MON_SFT                         7
#घोषणा AD_EINT1INVOUT_MON_MASK                        0x1
#घोषणा AD_EINT1INVOUT_MON_MASK_SFT                    (0x1 << 7)
#घोषणा DA_AUDACCDETCMPCLK_MON_ADDR                    \
	MT6359_ACCDET_CON37
#घोषणा DA_AUDACCDETCMPCLK_MON_SFT                     0
#घोषणा DA_AUDACCDETCMPCLK_MON_MASK                    0x1
#घोषणा DA_AUDACCDETCMPCLK_MON_MASK_SFT                (0x1 << 0)
#घोषणा DA_AUDACCDETVTHCLK_MON_ADDR                    \
	MT6359_ACCDET_CON37
#घोषणा DA_AUDACCDETVTHCLK_MON_SFT                     1
#घोषणा DA_AUDACCDETVTHCLK_MON_MASK                    0x1
#घोषणा DA_AUDACCDETVTHCLK_MON_MASK_SFT                (0x1 << 1)
#घोषणा DA_AUDACCDETMBIASCLK_MON_ADDR                  \
	MT6359_ACCDET_CON37
#घोषणा DA_AUDACCDETMBIASCLK_MON_SFT                   2
#घोषणा DA_AUDACCDETMBIASCLK_MON_MASK                  0x1
#घोषणा DA_AUDACCDETMBIASCLK_MON_MASK_SFT              (0x1 << 2)
#घोषणा DA_AUDACCDETAUXADCSWCTRL_MON_ADDR              \
	MT6359_ACCDET_CON37
#घोषणा DA_AUDACCDETAUXADCSWCTRL_MON_SFT               3
#घोषणा DA_AUDACCDETAUXADCSWCTRL_MON_MASK              0x1
#घोषणा DA_AUDACCDETAUXADCSWCTRL_MON_MASK_SFT          (0x1 << 3)
#घोषणा DA_EINT0CTURBO_MON_ADDR                        \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT0CTURBO_MON_SFT                         0
#घोषणा DA_EINT0CTURBO_MON_MASK                        0x1
#घोषणा DA_EINT0CTURBO_MON_MASK_SFT                    (0x1 << 0)
#घोषणा DA_EINT0CMPMEN_MON_ADDR                        \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT0CMPMEN_MON_SFT                         1
#घोषणा DA_EINT0CMPMEN_MON_MASK                        0x1
#घोषणा DA_EINT0CMPMEN_MON_MASK_SFT                    (0x1 << 1)
#घोषणा DA_EINT0CMPEN_MON_ADDR                         \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT0CMPEN_MON_SFT                          2
#घोषणा DA_EINT0CMPEN_MON_MASK                         0x1
#घोषणा DA_EINT0CMPEN_MON_MASK_SFT                     (0x1 << 2)
#घोषणा DA_EINT0INVEN_MON_ADDR                         \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT0INVEN_MON_SFT                          3
#घोषणा DA_EINT0INVEN_MON_MASK                         0x1
#घोषणा DA_EINT0INVEN_MON_MASK_SFT                     (0x1 << 3)
#घोषणा DA_EINT0CEN_MON_ADDR                           \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT0CEN_MON_SFT                            4
#घोषणा DA_EINT0CEN_MON_MASK                           0x1
#घोषणा DA_EINT0CEN_MON_MASK_SFT                       (0x1 << 4)
#घोषणा DA_EINT0EN_MON_ADDR                            \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT0EN_MON_SFT                             5
#घोषणा DA_EINT0EN_MON_MASK                            0x1
#घोषणा DA_EINT0EN_MON_MASK_SFT                        (0x1 << 5)
#घोषणा DA_EINT1CTURBO_MON_ADDR                        \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT1CTURBO_MON_SFT                         8
#घोषणा DA_EINT1CTURBO_MON_MASK                        0x1
#घोषणा DA_EINT1CTURBO_MON_MASK_SFT                    (0x1 << 8)
#घोषणा DA_EINT1CMPMEN_MON_ADDR                        \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT1CMPMEN_MON_SFT                         9
#घोषणा DA_EINT1CMPMEN_MON_MASK                        0x1
#घोषणा DA_EINT1CMPMEN_MON_MASK_SFT                    (0x1 << 9)
#घोषणा DA_EINT1CMPEN_MON_ADDR                         \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT1CMPEN_MON_SFT                          10
#घोषणा DA_EINT1CMPEN_MON_MASK                         0x1
#घोषणा DA_EINT1CMPEN_MON_MASK_SFT                     (0x1 << 10)
#घोषणा DA_EINT1INVEN_MON_ADDR                         \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT1INVEN_MON_SFT                          11
#घोषणा DA_EINT1INVEN_MON_MASK                         0x1
#घोषणा DA_EINT1INVEN_MON_MASK_SFT                     (0x1 << 11)
#घोषणा DA_EINT1CEN_MON_ADDR                           \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT1CEN_MON_SFT                            12
#घोषणा DA_EINT1CEN_MON_MASK                           0x1
#घोषणा DA_EINT1CEN_MON_MASK_SFT                       (0x1 << 12)
#घोषणा DA_EINT1EN_MON_ADDR                            \
	MT6359_ACCDET_CON38
#घोषणा DA_EINT1EN_MON_SFT                             13
#घोषणा DA_EINT1EN_MON_MASK                            0x1
#घोषणा DA_EINT1EN_MON_MASK_SFT                        (0x1 << 13)
#घोषणा ACCDET_EINT0_M_PLUG_IN_COUNT_ADDR              \
	MT6359_ACCDET_CON39
#घोषणा ACCDET_EINT0_M_PLUG_IN_COUNT_SFT               0
#घोषणा ACCDET_EINT0_M_PLUG_IN_COUNT_MASK              0x7
#घोषणा ACCDET_EINT0_M_PLUG_IN_COUNT_MASK_SFT          (0x7 << 0)
#घोषणा ACCDET_EINT1_M_PLUG_IN_COUNT_ADDR              \
	MT6359_ACCDET_CON39
#घोषणा ACCDET_EINT1_M_PLUG_IN_COUNT_SFT               4
#घोषणा ACCDET_EINT1_M_PLUG_IN_COUNT_MASK              0x7
#घोषणा ACCDET_EINT1_M_PLUG_IN_COUNT_MASK_SFT          (0x7 << 4)
#घोषणा ACCDET_MON_FLAG_EN_ADDR                        \
	MT6359_ACCDET_CON40
#घोषणा ACCDET_MON_FLAG_EN_SFT                         0
#घोषणा ACCDET_MON_FLAG_EN_MASK                        0x1
#घोषणा ACCDET_MON_FLAG_EN_MASK_SFT                    (0x1 << 0)
#घोषणा ACCDET_MON_FLAG_SEL_ADDR                       \
	MT6359_ACCDET_CON40
#घोषणा ACCDET_MON_FLAG_SEL_SFT                        4
#घोषणा ACCDET_MON_FLAG_SEL_MASK                       0xF
#घोषणा ACCDET_MON_FLAG_SEL_MASK_SFT                   (0xF << 4)

#घोषणा RG_AUDPWDBMICBIAS0_ADDR                        \
	MT6359_AUDENC_ANA_CON15
#घोषणा RG_AUDPWDBMICBIAS0_SFT                         0
#घोषणा RG_AUDPWDBMICBIAS0_MASK                        0x1
#घोषणा RG_AUDPWDBMICBIAS0_MASK_SFT                    (0x1 << 0)
#घोषणा RG_AUDPREAMPLON_ADDR                           \
	MT6359_AUDENC_ANA_CON0
#घोषणा RG_AUDPREAMPLON_SFT                            0
#घोषणा RG_AUDPREAMPLON_MASK                           0x1
#घोषणा RG_AUDPREAMPLON_MASK_SFT                       (0x1 << 0)
#घोषणा RG_CLKSQ_EN_ADDR                               \
	MT6359_AUDENC_ANA_CON23
#घोषणा RG_CLKSQ_EN_SFT                                0
#घोषणा RG_CLKSQ_EN_MASK                               0x1
#घोषणा RG_CLKSQ_EN_MASK_SFT                           (0x1 << 0)
#घोषणा RG_RTC32K_CK_PDN_ADDR                          \
	MT6359_TOP_CKPDN_CON0
#घोषणा RG_RTC32K_CK_PDN_SFT                           15
#घोषणा RG_RTC32K_CK_PDN_MASK                          0x1
#घोषणा RG_RTC32K_CK_PDN_MASK_SFT                      (0x1 << 15)
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP32_ADDR                \
	MT6359_AUDDEC_ANA_CON2
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP32_SFT                 0
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP32_MASK                0x7
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP32_MASK_SFT            (0x7 << 0)
#घोषणा AUXADC_RQST_CH5_ADDR                           \
	MT6359_AUXADC_RQST0
#घोषणा AUXADC_RQST_CH5_SFT                            5
#घोषणा AUXADC_RQST_CH5_MASK                           0x1
#घोषणा AUXADC_RQST_CH5_MASK_SFT                       (0x1 << 5)
#घोषणा RG_LDO_VUSB_HW0_OP_EN_ADDR                     \
	MT6359_LDO_VUSB_OP_EN
#घोषणा RG_LDO_VUSB_HW0_OP_EN_SFT                      0
#घोषणा RG_LDO_VUSB_HW0_OP_EN_MASK                     0x1
#घोषणा RG_LDO_VUSB_HW0_OP_EN_MASK_SFT                 (0x1 << 0)
#घोषणा RG_HPROUTPUTSTBENH_VAUDP32_ADDR                \
	MT6359_AUDDEC_ANA_CON2
#घोषणा RG_HPROUTPUTSTBENH_VAUDP32_SFT                 4
#घोषणा RG_HPROUTPUTSTBENH_VAUDP32_MASK                0x7
#घोषणा RG_HPROUTPUTSTBENH_VAUDP32_MASK_SFT            (0x7 << 4)
#घोषणा RG_NCP_PDDIS_EN_ADDR                           \
	MT6359_AFE_NCP_CFG2
#घोषणा RG_NCP_PDDIS_EN_SFT                            0
#घोषणा RG_NCP_PDDIS_EN_MASK                           0x1
#घोषणा RG_NCP_PDDIS_EN_MASK_SFT                       (0x1 << 0)
#घोषणा RG_SCK32K_CK_PDN_ADDR                          \
	MT6359_TOP_CKPDN_CON0
#घोषणा RG_SCK32K_CK_PDN_SFT                           0
#घोषणा RG_SCK32K_CK_PDN_MASK                          0x1
#घोषणा RG_SCK32K_CK_PDN_MASK_SFT                      (0x1 << 0)
/* AUDENC_ANA_CON18: */
#घोषणा RG_ACCDET_MODE_ANA11_MODE1	(0x000F)
#घोषणा RG_ACCDET_MODE_ANA11_MODE2	(0x008F)
#घोषणा RG_ACCDET_MODE_ANA11_MODE6	(0x008F)

/* AUXADC_ADC5:  Auxadc CH5 पढ़ो data */
#घोषणा AUXADC_DATA_RDY_CH5		BIT(15)
#घोषणा AUXADC_DATA_PROCEED_CH5		BIT(15)
#घोषणा AUXADC_DATA_MASK		(0x0FFF)

/* AUXADC_RQST0_SET:  Auxadc CH5 request, relevant 0x07EC */
#घोषणा AUXADC_RQST_CH5_SET		BIT(5)
/* AUXADC_RQST0_CLR:  Auxadc CH5 request, relevant 0x07EC */
#घोषणा AUXADC_RQST_CH5_CLR		BIT(5)

#घोषणा ACCDET_CALI_MASK0		(0xFF)
#घोषणा ACCDET_CALI_MASK1		(0xFF << 8)
#घोषणा ACCDET_CALI_MASK2		(0xFF)
#घोषणा ACCDET_CALI_MASK3		(0xFF << 8)
#घोषणा ACCDET_CALI_MASK4		(0xFF)

#घोषणा ACCDET_EINT_IRQ_B2_B3		(0x03 << ACCDET_EINT0_IRQ_SFT)

/* ACCDET_CON25: RO, accdet FSM state,etc.*/
#घोषणा ACCDET_STATE_MEM_IN_OFFSET	(ACCDET_MEM_IN_SFT)
#घोषणा ACCDET_STATE_AB_MASK		(0x03)
#घोषणा ACCDET_STATE_AB_00		(0x00)
#घोषणा ACCDET_STATE_AB_01		(0x01)
#घोषणा ACCDET_STATE_AB_10		(0x02)
#घोषणा ACCDET_STATE_AB_11		(0x03)

/* ACCDET_CON19 */
#घोषणा ACCDET_EINT0_STABLE_VAL ((ACCDET_DA_STABLE_MASK_SFT) | \
				(ACCDET_EINT0_EN_STABLE_MASK_SFT) | \
				(ACCDET_EINT0_CMPEN_STABLE_MASK_SFT) | \
				(ACCDET_EINT0_CEN_STABLE_MASK_SFT))

#घोषणा ACCDET_EINT1_STABLE_VAL ((ACCDET_DA_STABLE_MASK_SFT) | \
				(ACCDET_EINT1_EN_STABLE_MASK_SFT) | \
				(ACCDET_EINT1_CMPEN_STABLE_MASK_SFT) | \
				(ACCDET_EINT1_CEN_STABLE_MASK_SFT))
/* The following are used क्रम mt6359.c */
/* MT6359_DCXO_CW12 */
#घोषणा RG_XO_AUDIO_EN_M_SFT				13

/* AUD_TOP_CKPDN_CON0 */
#घोषणा RG_VOW13M_CK_PDN_SFT				13
#घोषणा RG_VOW13M_CK_PDN_MASK				0x1
#घोषणा RG_VOW13M_CK_PDN_MASK_SFT			(0x1 << 13)
#घोषणा RG_VOW32K_CK_PDN_SFT				12
#घोषणा RG_VOW32K_CK_PDN_MASK				0x1
#घोषणा RG_VOW32K_CK_PDN_MASK_SFT			(0x1 << 12)
#घोषणा RG_AUD_INTRP_CK_PDN_SFT				8
#घोषणा RG_AUD_INTRP_CK_PDN_MASK			0x1
#घोषणा RG_AUD_INTRP_CK_PDN_MASK_SFT			(0x1 << 8)
#घोषणा RG_PAD_AUD_CLK_MISO_CK_PDN_SFT			7
#घोषणा RG_PAD_AUD_CLK_MISO_CK_PDN_MASK			0x1
#घोषणा RG_PAD_AUD_CLK_MISO_CK_PDN_MASK_SFT		(0x1 << 7)
#घोषणा RG_AUDNCP_CK_PDN_SFT				6
#घोषणा RG_AUDNCP_CK_PDN_MASK				0x1
#घोषणा RG_AUDNCP_CK_PDN_MASK_SFT			(0x1 << 6)
#घोषणा RG_ZCD13M_CK_PDN_SFT				5
#घोषणा RG_ZCD13M_CK_PDN_MASK				0x1
#घोषणा RG_ZCD13M_CK_PDN_MASK_SFT			(0x1 << 5)
#घोषणा RG_AUDIF_CK_PDN_SFT				2
#घोषणा RG_AUDIF_CK_PDN_MASK				0x1
#घोषणा RG_AUDIF_CK_PDN_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUD_CK_PDN_SFT				1
#घोषणा RG_AUD_CK_PDN_MASK				0x1
#घोषणा RG_AUD_CK_PDN_MASK_SFT				(0x1 << 1)
#घोषणा RG_ACCDET_CK_PDN_SFT				0
#घोषणा RG_ACCDET_CK_PDN_MASK				0x1
#घोषणा RG_ACCDET_CK_PDN_MASK_SFT			(0x1 << 0)

/* AUD_TOP_CKPDN_CON0_SET */
#घोषणा RG_AUD_TOP_CKPDN_CON0_SET_SFT			0
#घोषणा RG_AUD_TOP_CKPDN_CON0_SET_MASK			0x3fff
#घोषणा RG_AUD_TOP_CKPDN_CON0_SET_MASK_SFT		(0x3fff << 0)

/* AUD_TOP_CKPDN_CON0_CLR */
#घोषणा RG_AUD_TOP_CKPDN_CON0_CLR_SFT			0
#घोषणा RG_AUD_TOP_CKPDN_CON0_CLR_MASK			0x3fff
#घोषणा RG_AUD_TOP_CKPDN_CON0_CLR_MASK_SFT		(0x3fff << 0)

/* AUD_TOP_CKSEL_CON0 */
#घोषणा RG_AUDIF_CK_CKSEL_SFT				3
#घोषणा RG_AUDIF_CK_CKSEL_MASK				0x1
#घोषणा RG_AUDIF_CK_CKSEL_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUD_CK_CKSEL_SFT				2
#घोषणा RG_AUD_CK_CKSEL_MASK				0x1
#घोषणा RG_AUD_CK_CKSEL_MASK_SFT			(0x1 << 2)

/* AUD_TOP_CKSEL_CON0_SET */
#घोषणा RG_AUD_TOP_CKSEL_CON0_SET_SFT			0
#घोषणा RG_AUD_TOP_CKSEL_CON0_SET_MASK			0xf
#घोषणा RG_AUD_TOP_CKSEL_CON0_SET_MASK_SFT		(0xf << 0)

/* AUD_TOP_CKSEL_CON0_CLR */
#घोषणा RG_AUD_TOP_CKSEL_CON0_CLR_SFT			0
#घोषणा RG_AUD_TOP_CKSEL_CON0_CLR_MASK			0xf
#घोषणा RG_AUD_TOP_CKSEL_CON0_CLR_MASK_SFT		(0xf << 0)

/* AUD_TOP_CKTST_CON0 */
#घोषणा RG_VOW13M_CK_TSTSEL_SFT				9
#घोषणा RG_VOW13M_CK_TSTSEL_MASK			0x1
#घोषणा RG_VOW13M_CK_TSTSEL_MASK_SFT			(0x1 << 9)
#घोषणा RG_VOW13M_CK_TST_DIS_SFT			8
#घोषणा RG_VOW13M_CK_TST_DIS_MASK			0x1
#घोषणा RG_VOW13M_CK_TST_DIS_MASK_SFT			(0x1 << 8)
#घोषणा RG_AUD26M_CK_TSTSEL_SFT				4
#घोषणा RG_AUD26M_CK_TSTSEL_MASK			0x1
#घोषणा RG_AUD26M_CK_TSTSEL_MASK_SFT			(0x1 << 4)
#घोषणा RG_AUDIF_CK_TSTSEL_SFT				3
#घोषणा RG_AUDIF_CK_TSTSEL_MASK				0x1
#घोषणा RG_AUDIF_CK_TSTSEL_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUD_CK_TSTSEL_SFT				2
#घोषणा RG_AUD_CK_TSTSEL_MASK				0x1
#घोषणा RG_AUD_CK_TSTSEL_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUD26M_CK_TST_DIS_SFT			0
#घोषणा RG_AUD26M_CK_TST_DIS_MASK			0x1
#घोषणा RG_AUD26M_CK_TST_DIS_MASK_SFT			(0x1 << 0)

/* AUD_TOP_CLK_HWEN_CON0 */
#घोषणा RG_AUD_INTRP_CK_PDN_HWEN_SFT			0
#घोषणा RG_AUD_INTRP_CK_PDN_HWEN_MASK			0x1
#घोषणा RG_AUD_INTRP_CK_PDN_HWEN_MASK_SFT		(0x1 << 0)

/* AUD_TOP_CLK_HWEN_CON0_SET */
#घोषणा RG_AUD_INTRP_CK_PND_HWEN_CON0_SET_SFT		0
#घोषणा RG_AUD_INTRP_CK_PND_HWEN_CON0_SET_MASK		0xffff
#घोषणा RG_AUD_INTRP_CK_PND_HWEN_CON0_SET_MASK_SFT	(0xffff << 0)

/* AUD_TOP_CLK_HWEN_CON0_CLR */
#घोषणा RG_AUD_INTRP_CLK_PDN_HWEN_CON0_CLR_SFT		0
#घोषणा RG_AUD_INTRP_CLK_PDN_HWEN_CON0_CLR_MASK		0xffff
#घोषणा RG_AUD_INTRP_CLK_PDN_HWEN_CON0_CLR_MASK_SFT	(0xffff << 0)

/* AUD_TOP_RST_CON0 */
#घोषणा RG_AUDNCP_RST_SFT				3
#घोषणा RG_AUDNCP_RST_MASK				0x1
#घोषणा RG_AUDNCP_RST_MASK_SFT				(0x1 << 3)
#घोषणा RG_ZCD_RST_SFT					2
#घोषणा RG_ZCD_RST_MASK					0x1
#घोषणा RG_ZCD_RST_MASK_SFT				(0x1 << 2)
#घोषणा RG_ACCDET_RST_SFT				1
#घोषणा RG_ACCDET_RST_MASK				0x1
#घोषणा RG_ACCDET_RST_MASK_SFT				(0x1 << 1)
#घोषणा RG_AUDIO_RST_SFT				0
#घोषणा RG_AUDIO_RST_MASK				0x1
#घोषणा RG_AUDIO_RST_MASK_SFT				(0x1 << 0)

/* AUD_TOP_RST_CON0_SET */
#घोषणा RG_AUD_TOP_RST_CON0_SET_SFT			0
#घोषणा RG_AUD_TOP_RST_CON0_SET_MASK			0xf
#घोषणा RG_AUD_TOP_RST_CON0_SET_MASK_SFT		(0xf << 0)

/* AUD_TOP_RST_CON0_CLR */
#घोषणा RG_AUD_TOP_RST_CON0_CLR_SFT			0
#घोषणा RG_AUD_TOP_RST_CON0_CLR_MASK			0xf
#घोषणा RG_AUD_TOP_RST_CON0_CLR_MASK_SFT		(0xf << 0)

/* AUD_TOP_RST_BANK_CON0 */
#घोषणा BANK_AUDZCD_SWRST_SFT				2
#घोषणा BANK_AUDZCD_SWRST_MASK				0x1
#घोषणा BANK_AUDZCD_SWRST_MASK_SFT			(0x1 << 2)
#घोषणा BANK_AUDIO_SWRST_SFT				1
#घोषणा BANK_AUDIO_SWRST_MASK				0x1
#घोषणा BANK_AUDIO_SWRST_MASK_SFT			(0x1 << 1)
#घोषणा BANK_ACCDET_SWRST_SFT				0
#घोषणा BANK_ACCDET_SWRST_MASK				0x1
#घोषणा BANK_ACCDET_SWRST_MASK_SFT			(0x1 << 0)

/* AFE_UL_DL_CON0 */
#घोषणा AFE_UL_LR_SWAP_SFT				15
#घोषणा AFE_UL_LR_SWAP_MASK				0x1
#घोषणा AFE_UL_LR_SWAP_MASK_SFT				(0x1 << 15)
#घोषणा AFE_DL_LR_SWAP_SFT				14
#घोषणा AFE_DL_LR_SWAP_MASK				0x1
#घोषणा AFE_DL_LR_SWAP_MASK_SFT				(0x1 << 14)
#घोषणा AFE_ON_SFT					0
#घोषणा AFE_ON_MASK					0x1
#घोषणा AFE_ON_MASK_SFT					(0x1 << 0)

/* AFE_DL_SRC2_CON0_L */
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_SFT			0
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK			0x1
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK_SFT		(0x1 << 0)

/* AFE_UL_SRC_CON0_H */
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_SFT			11
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_MASK			0x7
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_MASK_SFT		(0x7 << 11)
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_SFT			8
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_MASK			0x7
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_MASK_SFT		(0x7 << 8)
#घोषणा C_TWO_DIGITAL_MIC_CTL_SFT			7
#घोषणा C_TWO_DIGITAL_MIC_CTL_MASK			0x1
#घोषणा C_TWO_DIGITAL_MIC_CTL_MASK_SFT			(0x1 << 7)

/* AFE_UL_SRC_CON0_L */
#घोषणा DMIC_LOW_POWER_MODE_CTL_SFT			14
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK			0x3
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK_SFT		(0x3 << 14)
#घोषणा DIGMIC_4P33M_SEL_CTL_SFT			6
#घोषणा DIGMIC_4P33M_SEL_CTL_MASK			0x1
#घोषणा DIGMIC_4P33M_SEL_CTL_MASK_SFT			(0x1 << 6)
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_SFT			5
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK		0x1
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK_SFT		(0x1 << 5)
#घोषणा UL_LOOP_BACK_MODE_CTL_SFT			2
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK			0x1
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK_SFT			(0x1 << 2)
#घोषणा UL_SDM_3_LEVEL_CTL_SFT				1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK				0x1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK_SFT			(0x1 << 1)
#घोषणा UL_SRC_ON_TMP_CTL_SFT				0
#घोषणा UL_SRC_ON_TMP_CTL_MASK				0x1
#घोषणा UL_SRC_ON_TMP_CTL_MASK_SFT			(0x1 << 0)

/* AFE_ADDA6_L_SRC_CON0_H */
#घोषणा ADDA6_C_DIGMIC_PHASE_SEL_CH1_CTL_SFT		11
#घोषणा ADDA6_C_DIGMIC_PHASE_SEL_CH1_CTL_MASK		0x7
#घोषणा ADDA6_C_DIGMIC_PHASE_SEL_CH1_CTL_MASK_SFT	(0x7 << 11)
#घोषणा ADDA6_C_DIGMIC_PHASE_SEL_CH2_CTL_SFT		8
#घोषणा ADDA6_C_DIGMIC_PHASE_SEL_CH2_CTL_MASK		0x7
#घोषणा ADDA6_C_DIGMIC_PHASE_SEL_CH2_CTL_MASK_SFT	(0x7 << 8)
#घोषणा ADDA6_C_TWO_DIGITAL_MIC_CTL_SFT			7
#घोषणा ADDA6_C_TWO_DIGITAL_MIC_CTL_MASK		0x1
#घोषणा ADDA6_C_TWO_DIGITAL_MIC_CTL_MASK_SFT		(0x1 << 7)

/* AFE_ADDA6_UL_SRC_CON0_L */
#घोषणा ADDA6_DMIC_LOW_POWER_MODE_CTL_SFT		14
#घोषणा ADDA6_DMIC_LOW_POWER_MODE_CTL_MASK		0x3
#घोषणा ADDA6_DMIC_LOW_POWER_MODE_CTL_MASK_SFT		(0x3 << 14)
#घोषणा ADDA6_DIGMIC_4P33M_SEL_CTL_SFT			6
#घोषणा ADDA6_DIGMIC_4P33M_SEL_CTL_MASK			0x1
#घोषणा ADDA6_DIGMIC_4P33M_SEL_CTL_MASK_SFT		(0x1 << 6)
#घोषणा ADDA6_DIGMIC_3P25M_1P625M_SEL_CTL_SFT		5
#घोषणा ADDA6_DIGMIC_3P25M_1P625M_SEL_CTL_MASK		0x1
#घोषणा ADDA6_DIGMIC_3P25M_1P625M_SEL_CTL_MASK_SFT	(0x1 << 5)
#घोषणा ADDA6_UL_LOOP_BACK_MODE_CTL_SFT			2
#घोषणा ADDA6_UL_LOOP_BACK_MODE_CTL_MASK		0x1
#घोषणा ADDA6_UL_LOOP_BACK_MODE_CTL_MASK_SFT		(0x1 << 2)
#घोषणा ADDA6_UL_SDM_3_LEVEL_CTL_SFT			1
#घोषणा ADDA6_UL_SDM_3_LEVEL_CTL_MASK			0x1
#घोषणा ADDA6_UL_SDM_3_LEVEL_CTL_MASK_SFT		(0x1 << 1)
#घोषणा ADDA6_UL_SRC_ON_TMP_CTL_SFT			0
#घोषणा ADDA6_UL_SRC_ON_TMP_CTL_MASK			0x1
#घोषणा ADDA6_UL_SRC_ON_TMP_CTL_MASK_SFT		(0x1 << 0)

/* AFE_TOP_CON0 */
#घोषणा ADDA6_MTKAIF_SINE_ON_SFT			4
#घोषणा ADDA6_MTKAIF_SINE_ON_MASK			0x1
#घोषणा ADDA6_MTKAIF_SINE_ON_MASK_SFT			(0x1 << 4)
#घोषणा ADDA6_UL_SINE_ON_SFT				3
#घोषणा ADDA6_UL_SINE_ON_MASK				0x1
#घोषणा ADDA6_UL_SINE_ON_MASK_SFT			(0x1 << 3)
#घोषणा MTKAIF_SINE_ON_SFT				2
#घोषणा MTKAIF_SINE_ON_MASK				0x1
#घोषणा MTKAIF_SINE_ON_MASK_SFT				(0x1 << 2)
#घोषणा UL_SINE_ON_SFT					1
#घोषणा UL_SINE_ON_MASK					0x1
#घोषणा UL_SINE_ON_MASK_SFT				(0x1 << 1)
#घोषणा DL_SINE_ON_SFT					0
#घोषणा DL_SINE_ON_MASK					0x1
#घोषणा DL_SINE_ON_MASK_SFT				(0x1 << 0)

/* AUDIO_TOP_CON0 */
#घोषणा PDN_AFE_CTL_SFT					7
#घोषणा PDN_AFE_CTL_MASK				0x1
#घोषणा PDN_AFE_CTL_MASK_SFT				(0x1 << 7)
#घोषणा PDN_DAC_CTL_SFT					6
#घोषणा PDN_DAC_CTL_MASK				0x1
#घोषणा PDN_DAC_CTL_MASK_SFT				(0x1 << 6)
#घोषणा PDN_ADC_CTL_SFT					5
#घोषणा PDN_ADC_CTL_MASK				0x1
#घोषणा PDN_ADC_CTL_MASK_SFT				(0x1 << 5)
#घोषणा PDN_ADDA6_ADC_CTL_SFT				4
#घोषणा PDN_ADDA6_ADC_CTL_MASK				0x1
#घोषणा PDN_ADDA6_ADC_CTL_MASK_SFT			(0x1 << 4)
#घोषणा PDN_I2S_DL_CTL_SFT				3
#घोषणा PDN_I2S_DL_CTL_MASK				0x1
#घोषणा PDN_I2S_DL_CTL_MASK_SFT				(0x1 << 3)
#घोषणा PWR_CLK_DIS_CTL_SFT				2
#घोषणा PWR_CLK_DIS_CTL_MASK				0x1
#घोषणा PWR_CLK_DIS_CTL_MASK_SFT			(0x1 << 2)
#घोषणा PDN_AFE_TESTMODEL_CTL_SFT			1
#घोषणा PDN_AFE_TESTMODEL_CTL_MASK			0x1
#घोषणा PDN_AFE_TESTMODEL_CTL_MASK_SFT			(0x1 << 1)
#घोषणा PDN_RESERVED_SFT				0
#घोषणा PDN_RESERVED_MASK				0x1
#घोषणा PDN_RESERVED_MASK_SFT				(0x1 << 0)

/* AFE_MON_DEBUG0 */
#घोषणा AUDIO_SYS_TOP_MON_SWAP_SFT			14
#घोषणा AUDIO_SYS_TOP_MON_SWAP_MASK			0x3
#घोषणा AUDIO_SYS_TOP_MON_SWAP_MASK_SFT			(0x3 << 14)
#घोषणा AUDIO_SYS_TOP_MON_SEL_SFT			8
#घोषणा AUDIO_SYS_TOP_MON_SEL_MASK			0x1f
#घोषणा AUDIO_SYS_TOP_MON_SEL_MASK_SFT			(0x1f << 8)
#घोषणा AFE_MON_SEL_SFT					0
#घोषणा AFE_MON_SEL_MASK				0xff
#घोषणा AFE_MON_SEL_MASK_SFT				(0xff << 0)

/* AFUNC_AUD_CON0 */
#घोषणा CCI_AUD_ANACK_SEL_SFT				15
#घोषणा CCI_AUD_ANACK_SEL_MASK				0x1
#घोषणा CCI_AUD_ANACK_SEL_MASK_SFT			(0x1 << 15)
#घोषणा CCI_AUDIO_FIFO_WPTR_SFT				12
#घोषणा CCI_AUDIO_FIFO_WPTR_MASK			0x7
#घोषणा CCI_AUDIO_FIFO_WPTR_MASK_SFT			(0x7 << 12)
#घोषणा CCI_SCRAMBLER_CG_EN_SFT				11
#घोषणा CCI_SCRAMBLER_CG_EN_MASK			0x1
#घोषणा CCI_SCRAMBLER_CG_EN_MASK_SFT			(0x1 << 11)
#घोषणा CCI_LCH_INV_SFT					10
#घोषणा CCI_LCH_INV_MASK				0x1
#घोषणा CCI_LCH_INV_MASK_SFT				(0x1 << 10)
#घोषणा CCI_RAND_EN_SFT					9
#घोषणा CCI_RAND_EN_MASK				0x1
#घोषणा CCI_RAND_EN_MASK_SFT				(0x1 << 9)
#घोषणा CCI_SPLT_SCRMB_CLK_ON_SFT			8
#घोषणा CCI_SPLT_SCRMB_CLK_ON_MASK			0x1
#घोषणा CCI_SPLT_SCRMB_CLK_ON_MASK_SFT			(0x1 << 8)
#घोषणा CCI_SPLT_SCRMB_ON_SFT				7
#घोषणा CCI_SPLT_SCRMB_ON_MASK				0x1
#घोषणा CCI_SPLT_SCRMB_ON_MASK_SFT			(0x1 << 7)
#घोषणा CCI_AUD_IDAC_TEST_EN_SFT			6
#घोषणा CCI_AUD_IDAC_TEST_EN_MASK			0x1
#घोषणा CCI_AUD_IDAC_TEST_EN_MASK_SFT			(0x1 << 6)
#घोषणा CCI_ZERO_PAD_DISABLE_SFT			5
#घोषणा CCI_ZERO_PAD_DISABLE_MASK			0x1
#घोषणा CCI_ZERO_PAD_DISABLE_MASK_SFT			(0x1 << 5)
#घोषणा CCI_AUD_SPLIT_TEST_EN_SFT			4
#घोषणा CCI_AUD_SPLIT_TEST_EN_MASK			0x1
#घोषणा CCI_AUD_SPLIT_TEST_EN_MASK_SFT			(0x1 << 4)
#घोषणा CCI_AUD_SDM_MUTEL_SFT				3
#घोषणा CCI_AUD_SDM_MUTEL_MASK				0x1
#घोषणा CCI_AUD_SDM_MUTEL_MASK_SFT			(0x1 << 3)
#घोषणा CCI_AUD_SDM_MUTER_SFT				2
#घोषणा CCI_AUD_SDM_MUTER_MASK				0x1
#घोषणा CCI_AUD_SDM_MUTER_MASK_SFT			(0x1 << 2)
#घोषणा CCI_AUD_SDM_7BIT_SEL_SFT			1
#घोषणा CCI_AUD_SDM_7BIT_SEL_MASK			0x1
#घोषणा CCI_AUD_SDM_7BIT_SEL_MASK_SFT			(0x1 << 1)
#घोषणा CCI_SCRAMBLER_EN_SFT				0
#घोषणा CCI_SCRAMBLER_EN_MASK				0x1
#घोषणा CCI_SCRAMBLER_EN_MASK_SFT			(0x1 << 0)

/* AFUNC_AUD_CON1 */
#घोषणा AUD_SDM_TEST_L_SFT				8
#घोषणा AUD_SDM_TEST_L_MASK				0xff
#घोषणा AUD_SDM_TEST_L_MASK_SFT				(0xff << 8)
#घोषणा AUD_SDM_TEST_R_SFT				0
#घोषणा AUD_SDM_TEST_R_MASK				0xff
#घोषणा AUD_SDM_TEST_R_MASK_SFT				(0xff << 0)

/* AFUNC_AUD_CON2 */
#घोषणा CCI_AUD_DAC_ANA_MUTE_SFT			7
#घोषणा CCI_AUD_DAC_ANA_MUTE_MASK			0x1
#घोषणा CCI_AUD_DAC_ANA_MUTE_MASK_SFT			(0x1 << 7)
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_SFT			6
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_MASK			0x1
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_MASK_SFT		(0x1 << 6)
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_SFT			4
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_MASK			0x1
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_MASK_SFT		(0x1 << 4)
#घोषणा CCI_AUDIO_FIFO_ENABLE_SFT			3
#घोषणा CCI_AUDIO_FIFO_ENABLE_MASK			0x1
#घोषणा CCI_AUDIO_FIFO_ENABLE_MASK_SFT			(0x1 << 3)
#घोषणा CCI_ACD_MODE_SFT				2
#घोषणा CCI_ACD_MODE_MASK				0x1
#घोषणा CCI_ACD_MODE_MASK_SFT				(0x1 << 2)
#घोषणा CCI_AFIFO_CLK_PWDB_SFT				1
#घोषणा CCI_AFIFO_CLK_PWDB_MASK				0x1
#घोषणा CCI_AFIFO_CLK_PWDB_MASK_SFT			(0x1 << 1)
#घोषणा CCI_ACD_FUNC_RSTB_SFT				0
#घोषणा CCI_ACD_FUNC_RSTB_MASK				0x1
#घोषणा CCI_ACD_FUNC_RSTB_MASK_SFT			(0x1 << 0)

/* AFUNC_AUD_CON3 */
#घोषणा SDM_ANA13M_TESTCK_SEL_SFT			15
#घोषणा SDM_ANA13M_TESTCK_SEL_MASK			0x1
#घोषणा SDM_ANA13M_TESTCK_SEL_MASK_SFT			(0x1 << 15)
#घोषणा SDM_ANA13M_TESTCK_SRC_SEL_SFT			12
#घोषणा SDM_ANA13M_TESTCK_SRC_SEL_MASK			0x7
#घोषणा SDM_ANA13M_TESTCK_SRC_SEL_MASK_SFT		(0x7 << 12)
#घोषणा SDM_TESTCK_SRC_SEL_SFT				8
#घोषणा SDM_TESTCK_SRC_SEL_MASK				0x7
#घोषणा SDM_TESTCK_SRC_SEL_MASK_SFT			(0x7 << 8)
#घोषणा DIGMIC_TESTCK_SRC_SEL_SFT			4
#घोषणा DIGMIC_TESTCK_SRC_SEL_MASK			0x7
#घोषणा DIGMIC_TESTCK_SRC_SEL_MASK_SFT			(0x7 << 4)
#घोषणा DIGMIC_TESTCK_SEL_SFT				0
#घोषणा DIGMIC_TESTCK_SEL_MASK				0x1
#घोषणा DIGMIC_TESTCK_SEL_MASK_SFT			(0x1 << 0)

/* AFUNC_AUD_CON4 */
#घोषणा UL_FIFO_WCLK_INV_SFT				8
#घोषणा UL_FIFO_WCLK_INV_MASK				0x1
#घोषणा UL_FIFO_WCLK_INV_MASK_SFT			(0x1 << 8)
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTSRC_SEL_SFT		6
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTSRC_SEL_MASK		0x1
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTSRC_SEL_MASK_SFT	(0x1 << 6)
#घोषणा UL_FIFO_WDATA_TESTEN_SFT			5
#घोषणा UL_FIFO_WDATA_TESTEN_MASK			0x1
#घोषणा UL_FIFO_WDATA_TESTEN_MASK_SFT			(0x1 << 5)
#घोषणा UL_FIFO_WDATA_TESTSRC_SEL_SFT			4
#घोषणा UL_FIFO_WDATA_TESTSRC_SEL_MASK			0x1
#घोषणा UL_FIFO_WDATA_TESTSRC_SEL_MASK_SFT		(0x1 << 4)
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SEL_SFT		 3
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SEL_MASK		0x1
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SEL_MASK_SFT		(0x1 << 3)
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_SFT		0
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_MASK		0x7
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_MASK_SFT	(0x7 << 0)

/* AFUNC_AUD_CON5 */
#घोषणा R_AUD_DAC_POS_LARGE_MONO_SFT			8
#घोषणा R_AUD_DAC_POS_LARGE_MONO_MASK			0xff
#घोषणा R_AUD_DAC_POS_LARGE_MONO_MASK_SFT		(0xff << 8)
#घोषणा R_AUD_DAC_NEG_LARGE_MONO_SFT			0
#घोषणा R_AUD_DAC_NEG_LARGE_MONO_MASK			0xff
#घोषणा R_AUD_DAC_NEG_LARGE_MONO_MASK_SFT		(0xff << 0)

/* AFUNC_AUD_CON6 */
#घोषणा R_AUD_DAC_POS_SMALL_MONO_SFT			12
#घोषणा R_AUD_DAC_POS_SMALL_MONO_MASK			0xf
#घोषणा R_AUD_DAC_POS_SMALL_MONO_MASK_SFT		(0xf << 12)
#घोषणा R_AUD_DAC_NEG_SMALL_MONO_SFT			8
#घोषणा R_AUD_DAC_NEG_SMALL_MONO_MASK			0xf
#घोषणा R_AUD_DAC_NEG_SMALL_MONO_MASK_SFT		(0xf << 8)
#घोषणा R_AUD_DAC_POS_TINY_MONO_SFT			6
#घोषणा R_AUD_DAC_POS_TINY_MONO_MASK			0x3
#घोषणा R_AUD_DAC_POS_TINY_MONO_MASK_SFT		(0x3 << 6)
#घोषणा R_AUD_DAC_NEG_TINY_MONO_SFT			4
#घोषणा R_AUD_DAC_NEG_TINY_MONO_MASK			0x3
#घोषणा R_AUD_DAC_NEG_TINY_MONO_MASK_SFT		(0x3 << 4)
#घोषणा R_AUD_DAC_MONO_SEL_SFT				3
#घोषणा R_AUD_DAC_MONO_SEL_MASK				0x1
#घोषणा R_AUD_DAC_MONO_SEL_MASK_SFT			(0x1 << 3)
#घोषणा R_AUD_DAC_3TH_SEL_SFT				1
#घोषणा R_AUD_DAC_3TH_SEL_MASK				0x1
#घोषणा R_AUD_DAC_3TH_SEL_MASK_SFT			(0x1 << 1)
#घोषणा R_AUD_DAC_SW_RSTB_SFT				0
#घोषणा R_AUD_DAC_SW_RSTB_MASK				0x1
#घोषणा R_AUD_DAC_SW_RSTB_MASK_SFT			(0x1 << 0)

/* AFUNC_AUD_CON7 */
#घोषणा UL2_DIGMIC_TESTCK_SRC_SEL_SFT			10
#घोषणा UL2_DIGMIC_TESTCK_SRC_SEL_MASK			0x7
#घोषणा UL2_DIGMIC_TESTCK_SRC_SEL_MASK_SFT		(0x7 << 10)
#घोषणा UL2_DIGMIC_TESTCK_SEL_SFT			9
#घोषणा UL2_DIGMIC_TESTCK_SEL_MASK			0x1
#घोषणा UL2_DIGMIC_TESTCK_SEL_MASK_SFT			(0x1 << 9)
#घोषणा UL2_FIFO_WCLK_INV_SFT				8
#घोषणा UL2_FIFO_WCLK_INV_MASK				0x1
#घोषणा UL2_FIFO_WCLK_INV_MASK_SFT			(0x1 << 8)
#घोषणा UL2_FIFO_DIGMIC_WDATA_TESTSRC_SEL_SFT		6
#घोषणा UL2_FIFO_DIGMIC_WDATA_TESTSRC_SEL_MASK		0x1
#घोषणा UL2_FIFO_DIGMIC_WDATA_TESTSRC_SEL_MASK_SFT	(0x1 << 6)
#घोषणा UL2_FIFO_WDATA_TESTEN_SFT			5
#घोषणा UL2_FIFO_WDATA_TESTEN_MASK			0x1
#घोषणा UL2_FIFO_WDATA_TESTEN_MASK_SFT			(0x1 << 5)
#घोषणा UL2_FIFO_WDATA_TESTSRC_SEL_SFT			4
#घोषणा UL2_FIFO_WDATA_TESTSRC_SEL_MASK			0x1
#घोषणा UL2_FIFO_WDATA_TESTSRC_SEL_MASK_SFT		(0x1 << 4)
#घोषणा UL2_FIFO_WCLK_6P5M_TESTCK_SEL_SFT		3
#घोषणा UL2_FIFO_WCLK_6P5M_TESTCK_SEL_MASK		0x1
#घोषणा UL2_FIFO_WCLK_6P5M_TESTCK_SEL_MASK_SFT		(0x1 << 3)
#घोषणा UL2_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_SFT		0
#घोषणा UL2_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_MASK		0x7
#घोषणा UL2_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_MASK_SFT	(0x7 << 0)

/* AFUNC_AUD_CON8 */
#घोषणा SPLITTER2_DITHER_EN_SFT				9
#घोषणा SPLITTER2_DITHER_EN_MASK			0x1
#घोषणा SPLITTER2_DITHER_EN_MASK_SFT			(0x1 << 9)
#घोषणा SPLITTER1_DITHER_EN_SFT				8
#घोषणा SPLITTER1_DITHER_EN_MASK			0x1
#घोषणा SPLITTER1_DITHER_EN_MASK_SFT			(0x1 << 8)
#घोषणा SPLITTER2_DITHER_GAIN_SFT			4
#घोषणा SPLITTER2_DITHER_GAIN_MASK			0xf
#घोषणा SPLITTER2_DITHER_GAIN_MASK_SFT			(0xf << 4)
#घोषणा SPLITTER1_DITHER_GAIN_SFT			0
#घोषणा SPLITTER1_DITHER_GAIN_MASK			0xf
#घोषणा SPLITTER1_DITHER_GAIN_MASK_SFT			(0xf << 0)

/* AFUNC_AUD_CON9 */
#घोषणा CCI_AUD_ANACK_SEL_2ND_SFT			15
#घोषणा CCI_AUD_ANACK_SEL_2ND_MASK			0x1
#घोषणा CCI_AUD_ANACK_SEL_2ND_MASK_SFT			(0x1 << 15)
#घोषणा CCI_AUDIO_FIFO_WPTR_2ND_SFT			12
#घोषणा CCI_AUDIO_FIFO_WPTR_2ND_MASK			0x7
#घोषणा CCI_AUDIO_FIFO_WPTR_2ND_MASK_SFT		(0x7 << 12)
#घोषणा CCI_SCRAMBLER_CG_EN_2ND_SFT			11
#घोषणा CCI_SCRAMBLER_CG_EN_2ND_MASK			0x1
#घोषणा CCI_SCRAMBLER_CG_EN_2ND_MASK_SFT		 (0x1 << 11)
#घोषणा CCI_LCH_INV_2ND_SFT				10
#घोषणा CCI_LCH_INV_2ND_MASK				0x1
#घोषणा CCI_LCH_INV_2ND_MASK_SFT			(0x1 << 10)
#घोषणा CCI_RAND_EN_2ND_SFT				9
#घोषणा CCI_RAND_EN_2ND_MASK				0x1
#घोषणा CCI_RAND_EN_2ND_MASK_SFT			(0x1 << 9)
#घोषणा CCI_SPLT_SCRMB_CLK_ON_2ND_SFT			8
#घोषणा CCI_SPLT_SCRMB_CLK_ON_2ND_MASK			0x1
#घोषणा CCI_SPLT_SCRMB_CLK_ON_2ND_MASK_SFT		(0x1 << 8)
#घोषणा CCI_SPLT_SCRMB_ON_2ND_SFT			7
#घोषणा CCI_SPLT_SCRMB_ON_2ND_MASK			0x1
#घोषणा CCI_SPLT_SCRMB_ON_2ND_MASK_SFT			(0x1 << 7)
#घोषणा CCI_AUD_IDAC_TEST_EN_2ND_SFT			6
#घोषणा CCI_AUD_IDAC_TEST_EN_2ND_MASK			0x1
#घोषणा CCI_AUD_IDAC_TEST_EN_2ND_MASK_SFT		(0x1 << 6)
#घोषणा CCI_ZERO_PAD_DISABLE_2ND_SFT			5
#घोषणा CCI_ZERO_PAD_DISABLE_2ND_MASK			0x1
#घोषणा CCI_ZERO_PAD_DISABLE_2ND_MASK_SFT		(0x1 << 5)
#घोषणा CCI_AUD_SPLIT_TEST_EN_2ND_SFT			4
#घोषणा CCI_AUD_SPLIT_TEST_EN_2ND_MASK			0x1
#घोषणा CCI_AUD_SPLIT_TEST_EN_2ND_MASK_SFT		(0x1 << 4)
#घोषणा CCI_AUD_SDM_MUTEL_2ND_SFT			3
#घोषणा CCI_AUD_SDM_MUTEL_2ND_MASK			0x1
#घोषणा CCI_AUD_SDM_MUTEL_2ND_MASK_SFT			(0x1 << 3)
#घोषणा CCI_AUD_SDM_MUTER_2ND_SFT			2
#घोषणा CCI_AUD_SDM_MUTER_2ND_MASK			0x1
#घोषणा CCI_AUD_SDM_MUTER_2ND_MASK_SFT			(0x1 << 2)
#घोषणा CCI_AUD_SDM_7BIT_SEL_2ND_SFT			1
#घोषणा CCI_AUD_SDM_7BIT_SEL_2ND_MASK			0x1
#घोषणा CCI_AUD_SDM_7BIT_SEL_2ND_MASK_SFT		(0x1 << 1)
#घोषणा CCI_SCRAMBLER_EN_2ND_SFT			0
#घोषणा CCI_SCRAMBLER_EN_2ND_MASK			0x1
#घोषणा CCI_SCRAMBLER_EN_2ND_MASK_SFT			(0x1 << 0)

/* AFUNC_AUD_CON10 */
#घोषणा AUD_SDM_TEST_L_2ND_SFT				8
#घोषणा AUD_SDM_TEST_L_2ND_MASK				0xff
#घोषणा AUD_SDM_TEST_L_2ND_MASK_SFT			(0xff << 8)
#घोषणा AUD_SDM_TEST_R_2ND_SFT				0
#घोषणा AUD_SDM_TEST_R_2ND_MASK				0xff
#घोषणा AUD_SDM_TEST_R_2ND_MASK_SFT			(0xff << 0)

/* AFUNC_AUD_CON11 */
#घोषणा CCI_AUD_DAC_ANA_MUTE_2ND_SFT			7
#घोषणा CCI_AUD_DAC_ANA_MUTE_2ND_MASK			0x1
#घोषणा CCI_AUD_DAC_ANA_MUTE_2ND_MASK_SFT		(0x1 << 7)
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_2ND_SFT		6
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_2ND_MASK		0x1
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_2ND_MASK_SFT		(0x1 << 6)
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_2ND_SFT		4
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_2ND_MASK		0x1
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_2ND_MASK_SFT		(0x1 << 4)
#घोषणा CCI_AUDIO_FIFO_ENABLE_2ND_SFT			3
#घोषणा CCI_AUDIO_FIFO_ENABLE_2ND_MASK			0x1
#घोषणा CCI_AUDIO_FIFO_ENABLE_2ND_MASK_SFT		(0x1 << 3)
#घोषणा CCI_ACD_MODE_2ND_SFT				2
#घोषणा CCI_ACD_MODE_2ND_MASK				0x1
#घोषणा CCI_ACD_MODE_2ND_MASK_SFT			(0x1 << 2)
#घोषणा CCI_AFIFO_CLK_PWDB_2ND_SFT			1
#घोषणा CCI_AFIFO_CLK_PWDB_2ND_MASK			0x1
#घोषणा CCI_AFIFO_CLK_PWDB_2ND_MASK_SFT			(0x1 << 1)
#घोषणा CCI_ACD_FUNC_RSTB_2ND_SFT			0
#घोषणा CCI_ACD_FUNC_RSTB_2ND_MASK			0x1
#घोषणा CCI_ACD_FUNC_RSTB_2ND_MASK_SFT			(0x1 << 0)

/* AFUNC_AUD_CON12 */
#घोषणा SPLITTER2_DITHER_EN_2ND_SFT			9
#घोषणा SPLITTER2_DITHER_EN_2ND_MASK			0x1
#घोषणा SPLITTER2_DITHER_EN_2ND_MASK_SFT		(0x1 << 9)
#घोषणा SPLITTER1_DITHER_EN_2ND_SFT			8
#घोषणा SPLITTER1_DITHER_EN_2ND_MASK			0x1
#घोषणा SPLITTER1_DITHER_EN_2ND_MASK_SFT		(0x1 << 8)
#घोषणा SPLITTER2_DITHER_GAIN_2ND_SFT			4
#घोषणा SPLITTER2_DITHER_GAIN_2ND_MASK			0xf
#घोषणा SPLITTER2_DITHER_GAIN_2ND_MASK_SFT		(0xf << 4)
#घोषणा SPLITTER1_DITHER_GAIN_2ND_SFT			0
#घोषणा SPLITTER1_DITHER_GAIN_2ND_MASK			0xf
#घोषणा SPLITTER1_DITHER_GAIN_2ND_MASK_SFT		(0xf << 0)

/* AFUNC_AUD_MON0 */
#घोषणा AUD_SCR_OUT_L_SFT				8
#घोषणा AUD_SCR_OUT_L_MASK				0xff
#घोषणा AUD_SCR_OUT_L_MASK_SFT				(0xff << 8)
#घोषणा AUD_SCR_OUT_R_SFT				0
#घोषणा AUD_SCR_OUT_R_MASK				0xff
#घोषणा AUD_SCR_OUT_R_MASK_SFT				(0xff << 0)

/* AFUNC_AUD_MON1 */
#घोषणा AUD_SCR_OUT_L_2ND_SFT				8
#घोषणा AUD_SCR_OUT_L_2ND_MASK				0xff
#घोषणा AUD_SCR_OUT_L_2ND_MASK_SFT			(0xff << 8)
#घोषणा AUD_SCR_OUT_R_2ND_SFT				0
#घोषणा AUD_SCR_OUT_R_2ND_MASK				0xff
#घोषणा AUD_SCR_OUT_R_2ND_MASK_SFT			(0xff << 0)

/* AUDRC_TUNE_MON0 */
#घोषणा ASYNC_TEST_OUT_BCK_SFT				15
#घोषणा ASYNC_TEST_OUT_BCK_MASK				0x1
#घोषणा ASYNC_TEST_OUT_BCK_MASK_SFT			(0x1 << 15)
#घोषणा RGS_AUDRCTUNE1READ_SFT				8
#घोषणा RGS_AUDRCTUNE1READ_MASK				0x1f
#घोषणा RGS_AUDRCTUNE1READ_MASK_SFT			(0x1f << 8)
#घोषणा RGS_AUDRCTUNE0READ_SFT				0
#घोषणा RGS_AUDRCTUNE0READ_MASK				0x1f
#घोषणा RGS_AUDRCTUNE0READ_MASK_SFT			(0x1f << 0)

/* AFE_ADDA_MTKAIF_FIFO_CFG0 */
#घोषणा AFE_RESERVED_SFT				1
#घोषणा AFE_RESERVED_MASK				0x7fff
#घोषणा AFE_RESERVED_MASK_SFT				(0x7fff << 1)
#घोषणा RG_MTKAIF_RXIF_FIFO_INTEN_SFT			0
#घोषणा RG_MTKAIF_RXIF_FIFO_INTEN_MASK			0x1
#घोषणा RG_MTKAIF_RXIF_FIFO_INTEN_MASK_SFT		(0x1 << 0)

/* AFE_ADDA_MTKAIF_FIFO_LOG_MON1 */
#घोषणा MTKAIF_RXIF_WR_FULL_STATUS_SFT			1
#घोषणा MTKAIF_RXIF_WR_FULL_STATUS_MASK			0x1
#घोषणा MTKAIF_RXIF_WR_FULL_STATUS_MASK_SFT		(0x1 << 1)
#घोषणा MTKAIF_RXIF_RD_EMPTY_STATUS_SFT			0
#घोषणा MTKAIF_RXIF_RD_EMPTY_STATUS_MASK		0x1
#घोषणा MTKAIF_RXIF_RD_EMPTY_STATUS_MASK_SFT		(0x1 << 0)

/* AFE_ADDA_MTKAIF_MON0 */
#घोषणा MTKAIFTX_V3_SYNC_OUT_SFT			15
#घोषणा MTKAIFTX_V3_SYNC_OUT_MASK			0x1
#घोषणा MTKAIFTX_V3_SYNC_OUT_MASK_SFT			(0x1 << 15)
#घोषणा MTKAIFTX_V3_SDATA_OUT3_SFT			14
#घोषणा MTKAIFTX_V3_SDATA_OUT3_MASK			0x1
#घोषणा MTKAIFTX_V3_SDATA_OUT3_MASK_SFT			(0x1 << 14)
#घोषणा MTKAIFTX_V3_SDATA_OUT2_SFT			13
#घोषणा MTKAIFTX_V3_SDATA_OUT2_MASK			0x1
#घोषणा MTKAIFTX_V3_SDATA_OUT2_MASK_SFT			(0x1 << 13)
#घोषणा MTKAIFTX_V3_SDATA_OUT1_SFT			12
#घोषणा MTKAIFTX_V3_SDATA_OUT1_MASK			0x1
#घोषणा MTKAIFTX_V3_SDATA_OUT1_MASK_SFT			(0x1 << 12)
#घोषणा MTKAIF_RXIF_FIFO_STATUS_SFT			0
#घोषणा MTKAIF_RXIF_FIFO_STATUS_MASK			0xfff
#घोषणा MTKAIF_RXIF_FIFO_STATUS_MASK_SFT		(0xfff << 0)

/* AFE_ADDA_MTKAIF_MON1 */
#घोषणा MTKAIFRX_V3_SYNC_IN_SFT				15
#घोषणा MTKAIFRX_V3_SYNC_IN_MASK			0x1
#घोषणा MTKAIFRX_V3_SYNC_IN_MASK_SFT			(0x1 << 15)
#घोषणा MTKAIFRX_V3_SDATA_IN3_SFT			14
#घोषणा MTKAIFRX_V3_SDATA_IN3_MASK			0x1
#घोषणा MTKAIFRX_V3_SDATA_IN3_MASK_SFT			(0x1 << 14)
#घोषणा MTKAIFRX_V3_SDATA_IN2_SFT			13
#घोषणा MTKAIFRX_V3_SDATA_IN2_MASK			0x1
#घोषणा MTKAIFRX_V3_SDATA_IN2_MASK_SFT			(0x1 << 13)
#घोषणा MTKAIFRX_V3_SDATA_IN1_SFT			12
#घोषणा MTKAIFRX_V3_SDATA_IN1_MASK			0x1
#घोषणा MTKAIFRX_V3_SDATA_IN1_MASK_SFT			(0x1 << 12)
#घोषणा MTKAIF_RXIF_SEARCH_FAIL_FLAG_SFT		11
#घोषणा MTKAIF_RXIF_SEARCH_FAIL_FLAG_MASK		0x1
#घोषणा MTKAIF_RXIF_SEARCH_FAIL_FLAG_MASK_SFT		(0x1 << 11)
#घोषणा MTKAIF_RXIF_INVALID_FLAG_SFT			8
#घोषणा MTKAIF_RXIF_INVALID_FLAG_MASK			0x1
#घोषणा MTKAIF_RXIF_INVALID_FLAG_MASK_SFT		(0x1 << 8)
#घोषणा MTKAIF_RXIF_INVALID_CYCLE_SFT			0
#घोषणा MTKAIF_RXIF_INVALID_CYCLE_MASK			0xff
#घोषणा MTKAIF_RXIF_INVALID_CYCLE_MASK_SFT		(0xff << 0)

/* AFE_ADDA_MTKAIF_MON2 */
#घोषणा MTKAIF_TXIF_IN_CH2_SFT				8
#घोषणा MTKAIF_TXIF_IN_CH2_MASK				0xff
#घोषणा MTKAIF_TXIF_IN_CH2_MASK_SFT			(0xff << 8)
#घोषणा MTKAIF_TXIF_IN_CH1_SFT				0
#घोषणा MTKAIF_TXIF_IN_CH1_MASK				0xff
#घोषणा MTKAIF_TXIF_IN_CH1_MASK_SFT			(0xff << 0)

/* AFE_ADDA6_MTKAIF_MON3 */
#घोषणा ADDA6_MTKAIF_TXIF_IN_CH2_SFT			8
#घोषणा ADDA6_MTKAIF_TXIF_IN_CH2_MASK			0xff
#घोषणा ADDA6_MTKAIF_TXIF_IN_CH2_MASK_SFT		(0xff << 8)
#घोषणा ADDA6_MTKAIF_TXIF_IN_CH1_SFT			0
#घोषणा ADDA6_MTKAIF_TXIF_IN_CH1_MASK			0xff
#घोषणा ADDA6_MTKAIF_TXIF_IN_CH1_MASK_SFT		(0xff << 0)

/* AFE_ADDA_MTKAIF_MON4 */
#घोषणा MTKAIF_RXIF_OUT_CH2_SFT				8
#घोषणा MTKAIF_RXIF_OUT_CH2_MASK			0xff
#घोषणा MTKAIF_RXIF_OUT_CH2_MASK_SFT			(0xff << 8)
#घोषणा MTKAIF_RXIF_OUT_CH1_SFT				0
#घोषणा MTKAIF_RXIF_OUT_CH1_MASK			0xff
#घोषणा MTKAIF_RXIF_OUT_CH1_MASK_SFT			(0xff << 0)

/* AFE_ADDA_MTKAIF_MON5 */
#घोषणा MTKAIF_RXIF_OUT_CH3_SFT				0
#घोषणा MTKAIF_RXIF_OUT_CH3_MASK			0xff
#घोषणा MTKAIF_RXIF_OUT_CH3_MASK_SFT			(0xff << 0)

/* AFE_ADDA_MTKAIF_CFG0 */
#घोषणा RG_MTKAIF_RXIF_CLKINV_SFT			15
#घोषणा RG_MTKAIF_RXIF_CLKINV_MASK			0x1
#घोषणा RG_MTKAIF_RXIF_CLKINV_MASK_SFT			(0x1 << 15)
#घोषणा RG_ADDA6_MTKAIF_TXIF_PROTOCOL2_SFT		9
#घोषणा RG_ADDA6_MTKAIF_TXIF_PROTOCOL2_MASK		0x1
#घोषणा RG_ADDA6_MTKAIF_TXIF_PROTOCOL2_MASK_SFT		(0x1 << 9)
#घोषणा RG_MTKAIF_RXIF_PROTOCOL2_SFT			8
#घोषणा RG_MTKAIF_RXIF_PROTOCOL2_MASK			0x1
#घोषणा RG_MTKAIF_RXIF_PROTOCOL2_MASK_SFT		(0x1 << 8)
#घोषणा RG_MTKAIF_BYPASS_SRC_MODE_SFT			6
#घोषणा RG_MTKAIF_BYPASS_SRC_MODE_MASK			0x3
#घोषणा RG_MTKAIF_BYPASS_SRC_MODE_MASK_SFT		(0x3 << 6)
#घोषणा RG_MTKAIF_BYPASS_SRC_TEST_SFT			5
#घोषणा RG_MTKAIF_BYPASS_SRC_TEST_MASK			0x1
#घोषणा RG_MTKAIF_BYPASS_SRC_TEST_MASK_SFT		(0x1 << 5)
#घोषणा RG_MTKAIF_TXIF_PROTOCOL2_SFT			4
#घोषणा RG_MTKAIF_TXIF_PROTOCOL2_MASK			0x1
#घोषणा RG_MTKAIF_TXIF_PROTOCOL2_MASK_SFT		(0x1 << 4)
#घोषणा RG_ADDA6_MTKAIF_PMIC_TXIF_8TO5_SFT		3
#घोषणा RG_ADDA6_MTKAIF_PMIC_TXIF_8TO5_MASK		0x1
#घोषणा RG_ADDA6_MTKAIF_PMIC_TXIF_8TO5_MASK_SFT		(0x1 << 3)
#घोषणा RG_MTKAIF_PMIC_TXIF_8TO5_SFT			2
#घोषणा RG_MTKAIF_PMIC_TXIF_8TO5_MASK			0x1
#घोषणा RG_MTKAIF_PMIC_TXIF_8TO5_MASK_SFT		(0x1 << 2)
#घोषणा RG_MTKAIF_LOOPBACK_TEST2_SFT			1
#घोषणा RG_MTKAIF_LOOPBACK_TEST2_MASK			0x1
#घोषणा RG_MTKAIF_LOOPBACK_TEST2_MASK_SFT		(0x1 << 1)
#घोषणा RG_MTKAIF_LOOPBACK_TEST1_SFT			0
#घोषणा RG_MTKAIF_LOOPBACK_TEST1_MASK			0x1
#घोषणा RG_MTKAIF_LOOPBACK_TEST1_MASK_SFT		(0x1 << 0)

/* AFE_ADDA_MTKAIF_RX_CFG0 */
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_SFT			12
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_MASK			0xf
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_MASK_SFT		(0xf << 12)
#घोषणा RG_MTKAIF_RXIF_DATA_BIT_SFT			8
#घोषणा RG_MTKAIF_RXIF_DATA_BIT_MASK			0x7
#घोषणा RG_MTKAIF_RXIF_DATA_BIT_MASK_SFT		(0x7 << 8)
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_SFT			4
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_MASK			0x7
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_MASK_SFT		(0x7 << 4)
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_SFT			3
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_MASK			0x1
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_MASK_SFT		(0x1 << 3)
#घोषणा RG_MTKAIF_RXIF_DATA_MODE_SFT			0
#घोषणा RG_MTKAIF_RXIF_DATA_MODE_MASK			0x1
#घोषणा RG_MTKAIF_RXIF_DATA_MODE_MASK_SFT		(0x1 << 0)

/* AFE_ADDA_MTKAIF_RX_CFG1 */
#घोषणा RG_MTKAIF_RXIF_SYNC_SEARCH_TABLE_SFT		12
#घोषणा RG_MTKAIF_RXIF_SYNC_SEARCH_TABLE_MASK		0xf
#घोषणा RG_MTKAIF_RXIF_SYNC_SEARCH_TABLE_MASK_SFT	(0xf << 12)
#घोषणा RG_MTKAIF_RXIF_INVALID_SYNC_CHECK_ROUND_SFT	8
#घोषणा RG_MTKAIF_RXIF_INVALID_SYNC_CHECK_ROUND_MASK	0xf
#घोषणा RG_MTKAIF_RXIF_INVALID_SYNC_CHECK_ROUND_MASK_SFT	(0xf << 8)
#घोषणा RG_MTKAIF_RXIF_SYNC_CHECK_ROUND_SFT		4
#घोषणा RG_MTKAIF_RXIF_SYNC_CHECK_ROUND_MASK		0xf
#घोषणा RG_MTKAIF_RXIF_SYNC_CHECK_ROUND_MASK_SFT	(0xf << 4)
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_PROTOCOL2_SFT		0
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_PROTOCOL2_MASK	0xf
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_PROTOCOL2_MASK_SFT	(0xf << 0)

/* AFE_ADDA_MTKAIF_RX_CFG2 */
#घोषणा RG_MTKAIF_RXIF_P2_INPUT_SEL_SFT			15
#घोषणा RG_MTKAIF_RXIF_P2_INPUT_SEL_MASK		0x1
#घोषणा RG_MTKAIF_RXIF_P2_INPUT_SEL_MASK_SFT		(0x1 << 15)
#घोषणा RG_MTKAIF_RXIF_SYNC_WORD2_DISABLE_SFT		14
#घोषणा RG_MTKAIF_RXIF_SYNC_WORD2_DISABLE_MASK		0x1
#घोषणा RG_MTKAIF_RXIF_SYNC_WORD2_DISABLE_MASK_SFT	(0x1 << 14)
#घोषणा RG_MTKAIF_RXIF_SYNC_WORD1_DISABLE_SFT		13
#घोषणा RG_MTKAIF_RXIF_SYNC_WORD1_DISABLE_MASK		0x1
#घोषणा RG_MTKAIF_RXIF_SYNC_WORD1_DISABLE_MASK_SFT	(0x1 << 13)
#घोषणा RG_MTKAIF_RXIF_CLEAR_SYNC_FAIL_SFT		12
#घोषणा RG_MTKAIF_RXIF_CLEAR_SYNC_FAIL_MASK		0x1
#घोषणा RG_MTKAIF_RXIF_CLEAR_SYNC_FAIL_MASK_SFT		(0x1 << 12)
#घोषणा RG_MTKAIF_RXIF_SYNC_CNT_TABLE_SFT		0
#घोषणा RG_MTKAIF_RXIF_SYNC_CNT_TABLE_MASK		0xfff
#घोषणा RG_MTKAIF_RXIF_SYNC_CNT_TABLE_MASK_SFT		(0xfff << 0)

/* AFE_ADDA_MTKAIF_RX_CFG3 */
#घोषणा RG_MTKAIF_RXIF_LOOPBACK_USE_NLE_SFT		7
#घोषणा RG_MTKAIF_RXIF_LOOPBACK_USE_NLE_MASK		0x1
#घोषणा RG_MTKAIF_RXIF_LOOPBACK_USE_NLE_MASK_SFT	(0x1 << 7)
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_SFT		4
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK		0x7
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK_SFT	(0x7 << 4)
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_PROTOCOL2_SFT		3
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK		0x1
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK_SFT	(0x1 << 3)

/* AFE_ADDA_MTKAIF_SYNCWORD_CFG0 */
#घोषणा RG_MTKAIF_RX_SYNC_WORD2_SFT			4
#घोषणा RG_MTKAIF_RX_SYNC_WORD2_MASK			0x7
#घोषणा RG_MTKAIF_RX_SYNC_WORD2_MASK_SFT		(0x7 << 4)
#घोषणा RG_MTKAIF_RX_SYNC_WORD1_SFT			0
#घोषणा RG_MTKAIF_RX_SYNC_WORD1_MASK			0x7
#घोषणा RG_MTKAIF_RX_SYNC_WORD1_MASK_SFT		(0x7 << 0)

/* AFE_ADDA_MTKAIF_SYNCWORD_CFG1 */
#घोषणा RG_ADDA6_MTKAIF_TX_SYNC_WORD2_SFT		12
#घोषणा RG_ADDA6_MTKAIF_TX_SYNC_WORD2_MASK		0x7
#घोषणा RG_ADDA6_MTKAIF_TX_SYNC_WORD2_MASK_SFT		(0x7 << 12)
#घोषणा RG_ADDA6_MTKAIF_TX_SYNC_WORD1_SFT		8
#घोषणा RG_ADDA6_MTKAIF_TX_SYNC_WORD1_MASK		0x7
#घोषणा RG_ADDA6_MTKAIF_TX_SYNC_WORD1_MASK_SFT		(0x7 << 8)
#घोषणा RG_ADDA_MTKAIF_TX_SYNC_WORD2_SFT		4
#घोषणा RG_ADDA_MTKAIF_TX_SYNC_WORD2_MASK		0x7
#घोषणा RG_ADDA_MTKAIF_TX_SYNC_WORD2_MASK_SFT		(0x7 << 4)
#घोषणा RG_ADDA_MTKAIF_TX_SYNC_WORD1_SFT		0
#घोषणा RG_ADDA_MTKAIF_TX_SYNC_WORD1_MASK		0x7
#घोषणा RG_ADDA_MTKAIF_TX_SYNC_WORD1_MASK_SFT		(0x7 << 0)

/* AFE_SGEN_CFG0 */
#घोषणा SGEN_AMP_DIV_CH1_CTL_SFT			12
#घोषणा SGEN_AMP_DIV_CH1_CTL_MASK			0xf
#घोषणा SGEN_AMP_DIV_CH1_CTL_MASK_SFT			(0xf << 12)
#घोषणा SGEN_DAC_EN_CTL_SFT				7
#घोषणा SGEN_DAC_EN_CTL_MASK				0x1
#घोषणा SGEN_DAC_EN_CTL_MASK_SFT			(0x1 << 7)
#घोषणा SGEN_MUTE_SW_CTL_SFT				6
#घोषणा SGEN_MUTE_SW_CTL_MASK				0x1
#घोषणा SGEN_MUTE_SW_CTL_MASK_SFT			(0x1 << 6)
#घोषणा R_AUD_SDM_MUTE_L_SFT				5
#घोषणा R_AUD_SDM_MUTE_L_MASK				0x1
#घोषणा R_AUD_SDM_MUTE_L_MASK_SFT			(0x1 << 5)
#घोषणा R_AUD_SDM_MUTE_R_SFT				4
#घोषणा R_AUD_SDM_MUTE_R_MASK				0x1
#घोषणा R_AUD_SDM_MUTE_R_MASK_SFT			(0x1 << 4)
#घोषणा R_AUD_SDM_MUTE_L_2ND_SFT			3
#घोषणा R_AUD_SDM_MUTE_L_2ND_MASK			0x1
#घोषणा R_AUD_SDM_MUTE_L_2ND_MASK_SFT			(0x1 << 3)
#घोषणा R_AUD_SDM_MUTE_R_2ND_SFT			2
#घोषणा R_AUD_SDM_MUTE_R_2ND_MASK			0x1
#घोषणा R_AUD_SDM_MUTE_R_2ND_MASK_SFT			(0x1 << 2)

/* AFE_SGEN_CFG1 */
#घोषणा C_SGEN_RCH_INV_5BIT_SFT				15
#घोषणा C_SGEN_RCH_INV_5BIT_MASK			0x1
#घोषणा C_SGEN_RCH_INV_5BIT_MASK_SFT			(0x1 << 15)
#घोषणा C_SGEN_RCH_INV_8BIT_SFT				14
#घोषणा C_SGEN_RCH_INV_8BIT_MASK			0x1
#घोषणा C_SGEN_RCH_INV_8BIT_MASK_SFT			(0x1 << 14)
#घोषणा SGEN_FREQ_DIV_CH1_CTL_SFT			0
#घोषणा SGEN_FREQ_DIV_CH1_CTL_MASK			0x1f
#घोषणा SGEN_FREQ_DIV_CH1_CTL_MASK_SFT			(0x1f << 0)

/* AFE_ADC_ASYNC_FIFO_CFG */
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_EN_SFT		5
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_EN_MASK		0x1
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_EN_MASK_SFT		(0x1 << 5)
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_SFT			4
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_MASK			0x1
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_MASK_SFT		(0x1 << 4)
#घोषणा RG_AMIC_UL_ADC_CLK_SEL_SFT			1
#घोषणा RG_AMIC_UL_ADC_CLK_SEL_MASK			0x1
#घोषणा RG_AMIC_UL_ADC_CLK_SEL_MASK_SFT			(0x1 << 1)

/* AFE_ADC_ASYNC_FIFO_CFG1 */
#घोषणा RG_UL2_ASYNC_FIFO_SOFT_RST_EN_SFT		5
#घोषणा RG_UL2_ASYNC_FIFO_SOFT_RST_EN_MASK		0x1
#घोषणा RG_UL2_ASYNC_FIFO_SOFT_RST_EN_MASK_SFT		(0x1 << 5)
#घोषणा RG_UL2_ASYNC_FIFO_SOFT_RST_SFT			4
#घोषणा RG_UL2_ASYNC_FIFO_SOFT_RST_MASK			0x1
#घोषणा RG_UL2_ASYNC_FIFO_SOFT_RST_MASK_SFT		(0x1 << 4)

/* AFE_DCCLK_CFG0 */
#घोषणा DCCLK_DIV_SFT					5
#घोषणा DCCLK_DIV_MASK					0x7ff
#घोषणा DCCLK_DIV_MASK_SFT				(0x7ff << 5)
#घोषणा DCCLK_INV_SFT					4
#घोषणा DCCLK_INV_MASK					0x1
#घोषणा DCCLK_INV_MASK_SFT				(0x1 << 4)
#घोषणा DCCLK_REF_CK_SEL_SFT				2
#घोषणा DCCLK_REF_CK_SEL_MASK				0x3
#घोषणा DCCLK_REF_CK_SEL_MASK_SFT			(0x3 << 2)
#घोषणा DCCLK_PDN_SFT					1
#घोषणा DCCLK_PDN_MASK					0x1
#घोषणा DCCLK_PDN_MASK_SFT				(0x1 << 1)
#घोषणा DCCLK_GEN_ON_SFT				0
#घोषणा DCCLK_GEN_ON_MASK				0x1
#घोषणा DCCLK_GEN_ON_MASK_SFT				(0x1 << 0)

/* AFE_DCCLK_CFG1 */
#घोषणा RESYNC_SRC_SEL_SFT				10
#घोषणा RESYNC_SRC_SEL_MASK				0x3
#घोषणा RESYNC_SRC_SEL_MASK_SFT				(0x3 << 10)
#घोषणा RESYNC_SRC_CK_INV_SFT				9
#घोषणा RESYNC_SRC_CK_INV_MASK				0x1
#घोषणा RESYNC_SRC_CK_INV_MASK_SFT			(0x1 << 9)
#घोषणा DCCLK_RESYNC_BYPASS_SFT				8
#घोषणा DCCLK_RESYNC_BYPASS_MASK			0x1
#घोषणा DCCLK_RESYNC_BYPASS_MASK_SFT			(0x1 << 8)
#घोषणा DCCLK_PHASE_SEL_SFT				4
#घोषणा DCCLK_PHASE_SEL_MASK				0xf
#घोषणा DCCLK_PHASE_SEL_MASK_SFT			(0xf << 4)

/* AUDIO_DIG_CFG */
#घोषणा RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT		15
#घोषणा RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK		0x1
#घोषणा RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT	(0x1 << 15)
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE2_SFT			8
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE2_MASK			0x7f
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE2_MASK_SFT		(0x7f << 8)
#घोषणा RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT		7
#घोषणा RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK		0x1
#घोषणा RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT	(0x1 << 7)
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE_SFT			0
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE_MASK			0x7f
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE_MASK_SFT		(0x7f << 0)

/* AUDIO_DIG_CFG1 */
#घोषणा RG_AUD_PAD_TOP_DAT_MISO3_LOOPBACK_SFT		7
#घोषणा RG_AUD_PAD_TOP_DAT_MISO3_LOOPBACK_MASK		0x1
#घोषणा RG_AUD_PAD_TOP_DAT_MISO3_LOOPBACK_MASK_SFT	(0x1 << 7)
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE3_SFT			0
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE3_MASK			0x7f
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE3_MASK_SFT		(0x7f << 0)

/* AFE_AUD_PAD_TOP */
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_RSP_SFT			12
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_RSP_MASK			0x7
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_RSP_MASK_SFT		(0x7 << 12)
#घोषणा RG_AUD_PAD_TOP_MTKAIF_CLK_PROTOCOL2_SFT		11
#घोषणा RG_AUD_PAD_TOP_MTKAIF_CLK_PROTOCOL2_MASK	0x1
#घोषणा RG_AUD_PAD_TOP_MTKAIF_CLK_PROTOCOL2_MASK_SFT	(0x1 << 11)
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_ON_SFT			8
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_ON_MASK			0x1
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_ON_MASK_SFT		(0x1 << 8)

/* AFE_AUD_PAD_TOP_MON */
#घोषणा ADDA_AUD_PAD_TOP_MON_SFT			0
#घोषणा ADDA_AUD_PAD_TOP_MON_MASK			0xffff
#घोषणा ADDA_AUD_PAD_TOP_MON_MASK_SFT			(0xffff << 0)

/* AFE_AUD_PAD_TOP_MON1 */
#घोषणा ADDA_AUD_PAD_TOP_MON1_SFT			0
#घोषणा ADDA_AUD_PAD_TOP_MON1_MASK			0xffff
#घोषणा ADDA_AUD_PAD_TOP_MON1_MASK_SFT			(0xffff << 0)

/* AFE_AUD_PAD_TOP_MON2 */
#घोषणा ADDA_AUD_PAD_TOP_MON2_SFT			0
#घोषणा ADDA_AUD_PAD_TOP_MON2_MASK			0xffff
#घोषणा ADDA_AUD_PAD_TOP_MON2_MASK_SFT			(0xffff << 0)

/* AFE_DL_NLE_CFG */
#घोषणा NLE_RCH_HPGAIN_SEL_SFT				10
#घोषणा NLE_RCH_HPGAIN_SEL_MASK				0x1
#घोषणा NLE_RCH_HPGAIN_SEL_MASK_SFT			(0x1 << 10)
#घोषणा NLE_RCH_CH_SEL_SFT				9
#घोषणा NLE_RCH_CH_SEL_MASK				0x1
#घोषणा NLE_RCH_CH_SEL_MASK_SFT				(0x1 << 9)
#घोषणा NLE_RCH_ON_SFT					8
#घोषणा NLE_RCH_ON_MASK					0x1
#घोषणा NLE_RCH_ON_MASK_SFT				(0x1 << 8)
#घोषणा NLE_LCH_HPGAIN_SEL_SFT				2
#घोषणा NLE_LCH_HPGAIN_SEL_MASK				0x1
#घोषणा NLE_LCH_HPGAIN_SEL_MASK_SFT			(0x1 << 2)
#घोषणा NLE_LCH_CH_SEL_SFT				1
#घोषणा NLE_LCH_CH_SEL_MASK				0x1
#घोषणा NLE_LCH_CH_SEL_MASK_SFT				(0x1 << 1)
#घोषणा NLE_LCH_ON_SFT					0
#घोषणा NLE_LCH_ON_MASK					0x1
#घोषणा NLE_LCH_ON_MASK_SFT				(0x1 << 0)

/* AFE_DL_NLE_MON */
#घोषणा NLE_MONITOR_SFT					0
#घोषणा NLE_MONITOR_MASK				0x3fff
#घोषणा NLE_MONITOR_MASK_SFT				(0x3fff << 0)

/* AFE_CG_EN_MON */
#घोषणा CK_CG_EN_MON_SFT				0
#घोषणा CK_CG_EN_MON_MASK				0x3f
#घोषणा CK_CG_EN_MON_MASK_SFT				(0x3f << 0)

/* AFE_MIC_ARRAY_CFG */
#घोषणा RG_AMIC_ADC1_SOURCE_SEL_SFT			10
#घोषणा RG_AMIC_ADC1_SOURCE_SEL_MASK			0x3
#घोषणा RG_AMIC_ADC1_SOURCE_SEL_MASK_SFT		(0x3 << 10)
#घोषणा RG_AMIC_ADC2_SOURCE_SEL_SFT			8
#घोषणा RG_AMIC_ADC2_SOURCE_SEL_MASK			0x3
#घोषणा RG_AMIC_ADC2_SOURCE_SEL_MASK_SFT		(0x3 << 8)
#घोषणा RG_AMIC_ADC3_SOURCE_SEL_SFT			6
#घोषणा RG_AMIC_ADC3_SOURCE_SEL_MASK			0x3
#घोषणा RG_AMIC_ADC3_SOURCE_SEL_MASK_SFT		(0x3 << 6)
#घोषणा RG_DMIC_ADC1_SOURCE_SEL_SFT			4
#घोषणा RG_DMIC_ADC1_SOURCE_SEL_MASK			0x3
#घोषणा RG_DMIC_ADC1_SOURCE_SEL_MASK_SFT		(0x3 << 4)
#घोषणा RG_DMIC_ADC2_SOURCE_SEL_SFT			2
#घोषणा RG_DMIC_ADC2_SOURCE_SEL_MASK			0x3
#घोषणा RG_DMIC_ADC2_SOURCE_SEL_MASK_SFT		(0x3 << 2)
#घोषणा RG_DMIC_ADC3_SOURCE_SEL_SFT			0
#घोषणा RG_DMIC_ADC3_SOURCE_SEL_MASK			0x3
#घोषणा RG_DMIC_ADC3_SOURCE_SEL_MASK_SFT		(0x3 << 0)

/* AFE_CHOP_CFG0 */
#घोषणा RG_CHOP_DIV_SEL_SFT				4
#घोषणा RG_CHOP_DIV_SEL_MASK				0x1f
#घोषणा RG_CHOP_DIV_SEL_MASK_SFT			(0x1f << 4)
#घोषणा RG_CHOP_DIV_EN_SFT				0
#घोषणा RG_CHOP_DIV_EN_MASK				0x1
#घोषणा RG_CHOP_DIV_EN_MASK_SFT				(0x1 << 0)

/* AFE_MTKAIF_MUX_CFG */
#घोषणा RG_ADDA6_EN_SEL_SFT				12
#घोषणा RG_ADDA6_EN_SEL_MASK				0x1
#घोषणा RG_ADDA6_EN_SEL_MASK_SFT			(0x1 << 12)
#घोषणा RG_ADDA6_CH2_SEL_SFT				10
#घोषणा RG_ADDA6_CH2_SEL_MASK				0x3
#घोषणा RG_ADDA6_CH2_SEL_MASK_SFT			(0x3 << 10)
#घोषणा RG_ADDA6_CH1_SEL_SFT				8
#घोषणा RG_ADDA6_CH1_SEL_MASK				0x3
#घोषणा RG_ADDA6_CH1_SEL_MASK_SFT			(0x3 << 8)
#घोषणा RG_ADDA_EN_SEL_SFT				4
#घोषणा RG_ADDA_EN_SEL_MASK				0x1
#घोषणा RG_ADDA_EN_SEL_MASK_SFT				(0x1 << 4)
#घोषणा RG_ADDA_CH2_SEL_SFT				2
#घोषणा RG_ADDA_CH2_SEL_MASK				0x3
#घोषणा RG_ADDA_CH2_SEL_MASK_SFT			(0x3 << 2)
#घोषणा RG_ADDA_CH1_SEL_SFT				0
#घोषणा RG_ADDA_CH1_SEL_MASK				0x3
#घोषणा RG_ADDA_CH1_SEL_MASK_SFT			(0x3 << 0)

/* AFE_PMIC_NEWIF_CFG3 */
#घोषणा RG_UP8X_SYNC_WORD_SFT				0
#घोषणा RG_UP8X_SYNC_WORD_MASK				0xffff
#घोषणा RG_UP8X_SYNC_WORD_MASK_SFT			(0xffff << 0)

/* AFE_NCP_CFG0 */
#घोषणा  RG_NCP_CK1_VALID_CNT_SFT			9
#घोषणा  RG_NCP_CK1_VALID_CNT_MASK			0x7f
#घोषणा  RG_NCP_CK1_VALID_CNT_MASK_SFT			(0x7f << 9)
#घोषणा RG_NCP_ADITH_SFT				8
#घोषणा RG_NCP_ADITH_MASK				0x1
#घोषणा RG_NCP_ADITH_MASK_SFT				(0x1 << 8)
#घोषणा RG_NCP_DITHER_EN_SFT				7
#घोषणा RG_NCP_DITHER_EN_MASK				0x1
#घोषणा RG_NCP_DITHER_EN_MASK_SFT			(0x1 << 7)
#घोषणा RG_NCP_DITHER_FIXED_CK0_ACK1_2P_SFT		4
#घोषणा RG_NCP_DITHER_FIXED_CK0_ACK1_2P_MASK		0x7
#घोषणा RG_NCP_DITHER_FIXED_CK0_ACK1_2P_MASK_SFT	(0x7 << 4)
#घोषणा RG_NCP_DITHER_FIXED_CK0_ACK2_2P_SFT		1
#घोषणा RG_NCP_DITHER_FIXED_CK0_ACK2_2P_MASK		0x7
#घोषणा RG_NCP_DITHER_FIXED_CK0_ACK2_2P_MASK_SFT	(0x7 << 1)
#घोषणा RG_NCP_ON_SFT					0
#घोषणा RG_NCP_ON_MASK					0x1
#घोषणा RG_NCP_ON_MASK_SFT				(0x1 << 0)

/* AFE_NCP_CFG1 */
#घोषणा RG_XY_VAL_CFG_EN_SFT				15
#घोषणा RG_XY_VAL_CFG_EN_MASK				0x1
#घोषणा RG_XY_VAL_CFG_EN_MASK_SFT			(0x1 << 15)
#घोषणा RG_X_VAL_CFG_SFT				8
#घोषणा RG_X_VAL_CFG_MASK				0x7f
#घोषणा RG_X_VAL_CFG_MASK_SFT				(0x7f << 8)
#घोषणा RG_Y_VAL_CFG_SFT				0
#घोषणा RG_Y_VAL_CFG_MASK				0x7f
#घोषणा RG_Y_VAL_CFG_MASK_SFT				(0x7f << 0)

/* AFE_NCP_CFG2 */
#घोषणा RG_NCP_NONCLK_SET_SFT				1
#घोषणा RG_NCP_NONCLK_SET_MASK				0x1
#घोषणा RG_NCP_NONCLK_SET_MASK_SFT			(0x1 << 1)
#घोषणा RG_NCP_PDDIS_EN_SFT				0
#घोषणा RG_NCP_PDDIS_EN_MASK				0x1
#घोषणा RG_NCP_PDDIS_EN_MASK_SFT			(0x1 << 0)

/* AUDENC_ANA_CON0 */
#घोषणा RG_AUDPREAMPLON_SFT				0
#घोषणा RG_AUDPREAMPLON_MASK				0x1
#घोषणा RG_AUDPREAMPLON_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDPREAMPLDCCEN_SFT				1
#घोषणा RG_AUDPREAMPLDCCEN_MASK				0x1
#घोषणा RG_AUDPREAMPLDCCEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDPREAMPLDCPRECHARGE_SFT			2
#घोषणा RG_AUDPREAMPLDCPRECHARGE_MASK			0x1
#घोषणा RG_AUDPREAMPLDCPRECHARGE_MASK_SFT		(0x1 << 2)
#घोषणा RG_AUDPREAMPLPGATEST_SFT			3
#घोषणा RG_AUDPREAMPLPGATEST_MASK			0x1
#घोषणा RG_AUDPREAMPLPGATEST_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDPREAMPLVSCALE_SFT				4
#घोषणा RG_AUDPREAMPLVSCALE_MASK			0x3
#घोषणा RG_AUDPREAMPLVSCALE_MASK_SFT			(0x3 << 4)
#घोषणा RG_AUDPREAMPLINPUTSEL_SFT			6
#घोषणा RG_AUDPREAMPLINPUTSEL_MASK			0x3
#घोषणा RG_AUDPREAMPLINPUTSEL_MASK_SFT			(0x3 << 6)
#घोषणा RG_AUDPREAMPLGAIN_SFT				8
#घोषणा RG_AUDPREAMPLGAIN_MASK				0x7
#घोषणा RG_AUDPREAMPLGAIN_MASK_SFT			(0x7 << 8)
#घोषणा RG_BULKL_VCM_EN_SFT				11
#घोषणा RG_BULKL_VCM_EN_MASK				0x1
#घोषणा RG_BULKL_VCM_EN_MASK_SFT			(0x1 << 11)
#घोषणा RG_AUDADCLPWRUP_SFT				12
#घोषणा RG_AUDADCLPWRUP_MASK				0x1
#घोषणा RG_AUDADCLPWRUP_MASK_SFT			(0x1 << 12)
#घोषणा RG_AUDADCLINPUTSEL_SFT				13
#घोषणा RG_AUDADCLINPUTSEL_MASK				0x3
#घोषणा RG_AUDADCLINPUTSEL_MASK_SFT			(0x3 << 13)

/* AUDENC_ANA_CON1 */
#घोषणा RG_AUDPREAMPRON_SFT				0
#घोषणा RG_AUDPREAMPRON_MASK				0x1
#घोषणा RG_AUDPREAMPRON_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDPREAMPRDCCEN_SFT				1
#घोषणा RG_AUDPREAMPRDCCEN_MASK				0x1
#घोषणा RG_AUDPREAMPRDCCEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDPREAMPRDCPRECHARGE_SFT			2
#घोषणा RG_AUDPREAMPRDCPRECHARGE_MASK			0x1
#घोषणा RG_AUDPREAMPRDCPRECHARGE_MASK_SFT		(0x1 << 2)
#घोषणा RG_AUDPREAMPRPGATEST_SFT			3
#घोषणा RG_AUDPREAMPRPGATEST_MASK			0x1
#घोषणा RG_AUDPREAMPRPGATEST_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDPREAMPRVSCALE_SFT				4
#घोषणा RG_AUDPREAMPRVSCALE_MASK			0x3
#घोषणा RG_AUDPREAMPRVSCALE_MASK_SFT			(0x3 << 4)
#घोषणा RG_AUDPREAMPRINPUTSEL_SFT			6
#घोषणा RG_AUDPREAMPRINPUTSEL_MASK			0x3
#घोषणा RG_AUDPREAMPRINPUTSEL_MASK_SFT			(0x3 << 6)
#घोषणा RG_AUDPREAMPRGAIN_SFT				8
#घोषणा RG_AUDPREAMPRGAIN_MASK				0x7
#घोषणा RG_AUDPREAMPRGAIN_MASK_SFT			(0x7 << 8)
#घोषणा RG_BULKR_VCM_EN_SFT				11
#घोषणा RG_BULKR_VCM_EN_MASK				0x1
#घोषणा RG_BULKR_VCM_EN_MASK_SFT			(0x1 << 11)
#घोषणा RG_AUDADCRPWRUP_SFT				12
#घोषणा RG_AUDADCRPWRUP_MASK				0x1
#घोषणा RG_AUDADCRPWRUP_MASK_SFT			(0x1 << 12)
#घोषणा RG_AUDADCRINPUTSEL_SFT				13
#घोषणा RG_AUDADCRINPUTSEL_MASK				0x3
#घोषणा RG_AUDADCRINPUTSEL_MASK_SFT			(0x3 << 13)

/* AUDENC_ANA_CON2 */
#घोषणा RG_AUDPREAMP3ON_SFT				0
#घोषणा RG_AUDPREAMP3ON_MASK				0x1
#घोषणा RG_AUDPREAMP3ON_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDPREAMP3DCCEN_SFT				1
#घोषणा RG_AUDPREAMP3DCCEN_MASK				0x1
#घोषणा RG_AUDPREAMP3DCCEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDPREAMP3DCPRECHARGE_SFT			2
#घोषणा RG_AUDPREAMP3DCPRECHARGE_MASK			0x1
#घोषणा RG_AUDPREAMP3DCPRECHARGE_MASK_SFT		(0x1 << 2)
#घोषणा RG_AUDPREAMP3PGATEST_SFT			3
#घोषणा RG_AUDPREAMP3PGATEST_MASK			0x1
#घोषणा RG_AUDPREAMP3PGATEST_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDPREAMP3VSCALE_SFT				4
#घोषणा RG_AUDPREAMP3VSCALE_MASK			0x3
#घोषणा RG_AUDPREAMP3VSCALE_MASK_SFT			(0x3 << 4)
#घोषणा RG_AUDPREAMP3INPUTSEL_SFT			6
#घोषणा RG_AUDPREAMP3INPUTSEL_MASK			0x3
#घोषणा RG_AUDPREAMP3INPUTSEL_MASK_SFT			(0x3 << 6)
#घोषणा RG_AUDPREAMP3GAIN_SFT				8
#घोषणा RG_AUDPREAMP3GAIN_MASK				0x7
#घोषणा RG_AUDPREAMP3GAIN_MASK_SFT			(0x7 << 8)
#घोषणा RG_BULK3_VCM_EN_SFT				11
#घोषणा RG_BULK3_VCM_EN_MASK				0x1
#घोषणा RG_BULK3_VCM_EN_MASK_SFT			(0x1 << 11)
#घोषणा RG_AUDADC3PWRUP_SFT				12
#घोषणा RG_AUDADC3PWRUP_MASK				0x1
#घोषणा RG_AUDADC3PWRUP_MASK_SFT			(0x1 << 12)
#घोषणा RG_AUDADC3INPUTSEL_SFT				13
#घोषणा RG_AUDADC3INPUTSEL_MASK				0x3
#घोषणा RG_AUDADC3INPUTSEL_MASK_SFT			(0x3 << 13)

/* AUDENC_ANA_CON3 */
#घोषणा RG_AUDULHALFBIAS_SFT				0
#घोषणा RG_AUDULHALFBIAS_MASK				0x1
#घोषणा RG_AUDULHALFBIAS_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDGLBVOWLPWEN_SFT				1
#घोषणा RG_AUDGLBVOWLPWEN_MASK				0x1
#घोषणा RG_AUDGLBVOWLPWEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDPREAMPLPEN_SFT				2
#घोषणा RG_AUDPREAMPLPEN_MASK				0x1
#घोषणा RG_AUDPREAMPLPEN_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDADC1STSTAGELPEN_SFT			3
#घोषणा RG_AUDADC1STSTAGELPEN_MASK			0x1
#घोषणा RG_AUDADC1STSTAGELPEN_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDADC2NDSTAGELPEN_SFT			4
#घोषणा RG_AUDADC2NDSTAGELPEN_MASK			0x1
#घोषणा RG_AUDADC2NDSTAGELPEN_MASK_SFT			(0x1 << 4)
#घोषणा RG_AUDADCFLASHLPEN_SFT				5
#घोषणा RG_AUDADCFLASHLPEN_MASK				0x1
#घोषणा RG_AUDADCFLASHLPEN_MASK_SFT			(0x1 << 5)
#घोषणा RG_AUDPREAMPIDDTEST_SFT				6
#घोषणा RG_AUDPREAMPIDDTEST_MASK			0x3
#घोषणा RG_AUDPREAMPIDDTEST_MASK_SFT			(0x3 << 6)
#घोषणा RG_AUDADC1STSTAGEIDDTEST_SFT			8
#घोषणा RG_AUDADC1STSTAGEIDDTEST_MASK			0x3
#घोषणा RG_AUDADC1STSTAGEIDDTEST_MASK_SFT		(0x3 << 8)
#घोषणा RG_AUDADC2NDSTAGEIDDTEST_SFT			10
#घोषणा RG_AUDADC2NDSTAGEIDDTEST_MASK			0x3
#घोषणा RG_AUDADC2NDSTAGEIDDTEST_MASK_SFT		(0x3 << 10)
#घोषणा RG_AUDADCREFBUFIDDTEST_SFT			12
#घोषणा RG_AUDADCREFBUFIDDTEST_MASK			0x3
#घोषणा RG_AUDADCREFBUFIDDTEST_MASK_SFT			(0x3 << 12)
#घोषणा RG_AUDADCFLASHIDDTEST_SFT			14
#घोषणा RG_AUDADCFLASHIDDTEST_MASK			0x3
#घोषणा RG_AUDADCFLASHIDDTEST_MASK_SFT			(0x3 << 14)

/* AUDENC_ANA_CON4 */
#घोषणा RG_AUDRULHALFBIAS_SFT				0
#घोषणा RG_AUDRULHALFBIAS_MASK				0x1
#घोषणा RG_AUDRULHALFBIAS_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDGLBRVOWLPWEN_SFT				1
#घोषणा RG_AUDGLBRVOWLPWEN_MASK				0x1
#घोषणा RG_AUDGLBRVOWLPWEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDRPREAMPLPEN_SFT				2
#घोषणा RG_AUDRPREAMPLPEN_MASK				0x1
#घोषणा RG_AUDRPREAMPLPEN_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDRADC1STSTAGELPEN_SFT			3
#घोषणा RG_AUDRADC1STSTAGELPEN_MASK			0x1
#घोषणा RG_AUDRADC1STSTAGELPEN_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDRADC2NDSTAGELPEN_SFT			4
#घोषणा RG_AUDRADC2NDSTAGELPEN_MASK			0x1
#घोषणा RG_AUDRADC2NDSTAGELPEN_MASK_SFT			(0x1 << 4)
#घोषणा RG_AUDRADCFLASHLPEN_SFT				5
#घोषणा RG_AUDRADCFLASHLPEN_MASK			0x1
#घोषणा RG_AUDRADCFLASHLPEN_MASK_SFT			(0x1 << 5)
#घोषणा RG_AUDRPREAMPIDDTEST_SFT			6
#घोषणा RG_AUDRPREAMPIDDTEST_MASK			0x3
#घोषणा RG_AUDRPREAMPIDDTEST_MASK_SFT			(0x3 << 6)
#घोषणा RG_AUDRADC1STSTAGEIDDTEST_SFT			8
#घोषणा RG_AUDRADC1STSTAGEIDDTEST_MASK			0x3
#घोषणा RG_AUDRADC1STSTAGEIDDTEST_MASK_SFT		(0x3 << 8)
#घोषणा RG_AUDRADC2NDSTAGEIDDTEST_SFT			10
#घोषणा RG_AUDRADC2NDSTAGEIDDTEST_MASK			0x3
#घोषणा RG_AUDRADC2NDSTAGEIDDTEST_MASK_SFT		(0x3 << 10)
#घोषणा RG_AUDRADCREFBUFIDDTEST_SFT			12
#घोषणा RG_AUDRADCREFBUFIDDTEST_MASK			0x3
#घोषणा RG_AUDRADCREFBUFIDDTEST_MASK_SFT		(0x3 << 12)
#घोषणा RG_AUDRADCFLASHIDDTEST_SFT			14
#घोषणा RG_AUDRADCFLASHIDDTEST_MASK			0x3
#घोषणा RG_AUDRADCFLASHIDDTEST_MASK_SFT			(0x3 << 14)

/* AUDENC_ANA_CON5 */
#घोषणा RG_AUDADCCLKRSTB_SFT				0
#घोषणा RG_AUDADCCLKRSTB_MASK				0x1
#घोषणा RG_AUDADCCLKRSTB_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDADCCLKSEL_SFT				1
#घोषणा RG_AUDADCCLKSEL_MASK				0x3
#घोषणा RG_AUDADCCLKSEL_MASK_SFT			(0x3 << 1)
#घोषणा RG_AUDADCCLKSOURCE_SFT				3
#घोषणा RG_AUDADCCLKSOURCE_MASK				0x3
#घोषणा RG_AUDADCCLKSOURCE_MASK_SFT			(0x3 << 3)
#घोषणा RG_AUDADCCLKGENMODE_SFT				5
#घोषणा RG_AUDADCCLKGENMODE_MASK			0x3
#घोषणा RG_AUDADCCLKGENMODE_MASK_SFT			(0x3 << 5)
#घोषणा RG_AUDPREAMP_ACCFS_SFT				7
#घोषणा RG_AUDPREAMP_ACCFS_MASK				0x1
#घोषणा RG_AUDPREAMP_ACCFS_MASK_SFT			(0x1 << 7)
#घोषणा RG_AUDPREAMPAAFEN_SFT				8
#घोषणा RG_AUDPREAMPAAFEN_MASK				0x1
#घोषणा RG_AUDPREAMPAAFEN_MASK_SFT			(0x1 << 8)
#घोषणा RG_DCCVCMBUFLPMODSEL_SFT			9
#घोषणा RG_DCCVCMBUFLPMODSEL_MASK			0x1
#घोषणा RG_DCCVCMBUFLPMODSEL_MASK_SFT			(0x1 << 9)
#घोषणा RG_DCCVCMBUFLPSWEN_SFT				10
#घोषणा RG_DCCVCMBUFLPSWEN_MASK				0x1
#घोषणा RG_DCCVCMBUFLPSWEN_MASK_SFT			(0x1 << 10)
#घोषणा RG_AUDSPAREPGA_SFT				11
#घोषणा RG_AUDSPAREPGA_MASK				0x1f
#घोषणा RG_AUDSPAREPGA_MASK_SFT				(0x1f << 11)

/* AUDENC_ANA_CON6 */
#घोषणा RG_AUDADC1STSTAGESDENB_SFT			0
#घोषणा RG_AUDADC1STSTAGESDENB_MASK			0x1
#घोषणा RG_AUDADC1STSTAGESDENB_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDADC2NDSTAGERESET_SFT			1
#घोषणा RG_AUDADC2NDSTAGERESET_MASK			0x1
#घोषणा RG_AUDADC2NDSTAGERESET_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDADC3RDSTAGERESET_SFT			2
#घोषणा RG_AUDADC3RDSTAGERESET_MASK			0x1
#घोषणा RG_AUDADC3RDSTAGERESET_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDADCFSRESET_SFT				3
#घोषणा RG_AUDADCFSRESET_MASK				0x1
#घोषणा RG_AUDADCFSRESET_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDADCWIDECM_SFT				4
#घोषणा RG_AUDADCWIDECM_MASK				0x1
#घोषणा RG_AUDADCWIDECM_MASK_SFT			(0x1 << 4)
#घोषणा RG_AUDADCNOPATEST_SFT				5
#घोषणा RG_AUDADCNOPATEST_MASK				0x1
#घोषणा RG_AUDADCNOPATEST_MASK_SFT			(0x1 << 5)
#घोषणा RG_AUDADCBYPASS_SFT				6
#घोषणा RG_AUDADCBYPASS_MASK				0x1
#घोषणा RG_AUDADCBYPASS_MASK_SFT			(0x1 << 6)
#घोषणा RG_AUDADCFFBYPASS_SFT				7
#घोषणा RG_AUDADCFFBYPASS_MASK				0x1
#घोषणा RG_AUDADCFFBYPASS_MASK_SFT			(0x1 << 7)
#घोषणा RG_AUDADCDACFBCURRENT_SFT			8
#घोषणा RG_AUDADCDACFBCURRENT_MASK			0x1
#घोषणा RG_AUDADCDACFBCURRENT_MASK_SFT			(0x1 << 8)
#घोषणा RG_AUDADCDACIDDTEST_SFT				9
#घोषणा RG_AUDADCDACIDDTEST_MASK			0x3
#घोषणा RG_AUDADCDACIDDTEST_MASK_SFT			(0x3 << 9)
#घोषणा RG_AUDADCDACNRZ_SFT				11
#घोषणा RG_AUDADCDACNRZ_MASK				0x1
#घोषणा RG_AUDADCDACNRZ_MASK_SFT			(0x1 << 11)
#घोषणा RG_AUDADCNODEM_SFT				12
#घोषणा RG_AUDADCNODEM_MASK				0x1
#घोषणा RG_AUDADCNODEM_MASK_SFT				(0x1 << 12)
#घोषणा RG_AUDADCDACTEST_SFT				13
#घोषणा RG_AUDADCDACTEST_MASK				0x1
#घोषणा RG_AUDADCDACTEST_MASK_SFT			(0x1 << 13)
#घोषणा RG_AUDADCDAC0P25FS_SFT				14
#घोषणा RG_AUDADCDAC0P25FS_MASK				0x1
#घोषणा RG_AUDADCDAC0P25FS_MASK_SFT			(0x1 << 14)
#घोषणा RG_AUDADCRDAC0P25FS_SFT				15
#घोषणा RG_AUDADCRDAC0P25FS_MASK			0x1
#घोषणा RG_AUDADCRDAC0P25FS_MASK_SFT			(0x1 << 15)

/* AUDENC_ANA_CON7 */
#घोषणा RG_AUDADCTESTDATA_SFT				0
#घोषणा RG_AUDADCTESTDATA_MASK				0xffff
#घोषणा RG_AUDADCTESTDATA_MASK_SFT			(0xffff << 0)

/* AUDENC_ANA_CON8 */
#घोषणा RG_AUDRCTUNEL_SFT				0
#घोषणा RG_AUDRCTUNEL_MASK				0x1f
#घोषणा RG_AUDRCTUNEL_MASK_SFT				(0x1f << 0)
#घोषणा RG_AUDRCTUNELSEL_SFT				5
#घोषणा RG_AUDRCTUNELSEL_MASK				0x1
#घोषणा RG_AUDRCTUNELSEL_MASK_SFT			(0x1 << 5)
#घोषणा RG_AUDRCTUNER_SFT				8
#घोषणा RG_AUDRCTUNER_MASK				0x1f
#घोषणा RG_AUDRCTUNER_MASK_SFT				(0x1f << 8)
#घोषणा RG_AUDRCTUNERSEL_SFT				13
#घोषणा RG_AUDRCTUNERSEL_MASK				0x1
#घोषणा RG_AUDRCTUNERSEL_MASK_SFT			(0x1 << 13)

/* AUDENC_ANA_CON9 */
#घोषणा RG_AUD3CTUNEL_SFT				0
#घोषणा RG_AUD3CTUNEL_MASK				0x1f
#घोषणा RG_AUD3CTUNEL_MASK_SFT				(0x1f << 0)
#घोषणा RG_AUD3CTUNELSEL_SFT				5
#घोषणा RG_AUD3CTUNELSEL_MASK				0x1
#घोषणा RG_AUD3CTUNELSEL_MASK_SFT			(0x1 << 5)
#घोषणा RGS_AUDRCTUNE3READ_SFT				6
#घोषणा RGS_AUDRCTUNE3READ_MASK				0x1f
#घोषणा RGS_AUDRCTUNE3READ_MASK_SFT			(0x1f << 6)
#घोषणा RG_AUD3SPARE_SFT				11
#घोषणा RG_AUD3SPARE_MASK				0x1f
#घोषणा RG_AUD3SPARE_MASK_SFT				(0x1f << 11)

/* AUDENC_ANA_CON10 */
#घोषणा RGS_AUDRCTUNELREAD_SFT				0
#घोषणा RGS_AUDRCTUNELREAD_MASK				0x1f
#घोषणा RGS_AUDRCTUNELREAD_MASK_SFT			(0x1f << 0)
#घोषणा RGS_AUDRCTUNERREAD_SFT				8
#घोषणा RGS_AUDRCTUNERREAD_MASK				0x1f
#घोषणा RGS_AUDRCTUNERREAD_MASK_SFT			(0x1f << 8)

/* AUDENC_ANA_CON11 */
#घोषणा RG_AUDSPAREVA30_SFT				0
#घोषणा RG_AUDSPAREVA30_MASK				0xff
#घोषणा RG_AUDSPAREVA30_MASK_SFT			(0xff << 0)
#घोषणा RG_AUDSPAREVA18_SFT				8
#घोषणा RG_AUDSPAREVA18_MASK				0xff
#घोषणा RG_AUDSPAREVA18_MASK_SFT			(0xff << 8)

/* AUDENC_ANA_CON12 */
#घोषणा RG_AUDPGA_DECAP_SFT				0
#घोषणा RG_AUDPGA_DECAP_MASK				0x1
#घोषणा RG_AUDPGA_DECAP_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDPGA_CAPRA_SFT				1
#घोषणा RG_AUDPGA_CAPRA_MASK				0x1
#घोषणा RG_AUDPGA_CAPRA_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDPGA_ACCCMP_SFT				2
#घोषणा RG_AUDPGA_ACCCMP_MASK				0x1
#घोषणा RG_AUDPGA_ACCCMP_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDENC_SPARE2_SFT				3
#घोषणा RG_AUDENC_SPARE2_MASK				0x1fff
#घोषणा RG_AUDENC_SPARE2_MASK_SFT			(0x1fff << 3)

/* AUDENC_ANA_CON13 */
#घोषणा RG_AUDDIGMICEN_SFT				0
#घोषणा RG_AUDDIGMICEN_MASK				0x1
#घोषणा RG_AUDDIGMICEN_MASK_SFT				(0x1 << 0)
#घोषणा RG_AUDDIGMICBIAS_SFT				1
#घोषणा RG_AUDDIGMICBIAS_MASK				0x3
#घोषणा RG_AUDDIGMICBIAS_MASK_SFT			(0x3 << 1)
#घोषणा RG_DMICHPCLKEN_SFT				3
#घोषणा RG_DMICHPCLKEN_MASK				0x1
#घोषणा RG_DMICHPCLKEN_MASK_SFT				(0x1 << 3)
#घोषणा RG_AUDDIGMICPDUTY_SFT				4
#घोषणा RG_AUDDIGMICPDUTY_MASK				0x3
#घोषणा RG_AUDDIGMICPDUTY_MASK_SFT			(0x3 << 4)
#घोषणा RG_AUDDIGMICNDUTY_SFT				6
#घोषणा RG_AUDDIGMICNDUTY_MASK				0x3
#घोषणा RG_AUDDIGMICNDUTY_MASK_SFT			(0x3 << 6)
#घोषणा RG_DMICMONEN_SFT				8
#घोषणा RG_DMICMONEN_MASK				0x1
#घोषणा RG_DMICMONEN_MASK_SFT				(0x1 << 8)
#घोषणा RG_DMICMONSEL_SFT				9
#घोषणा RG_DMICMONSEL_MASK				0x7
#घोषणा RG_DMICMONSEL_MASK_SFT				(0x7 << 9)

/* AUDENC_ANA_CON14 */
#घोषणा RG_AUDDIGMIC1EN_SFT				0
#घोषणा RG_AUDDIGMIC1EN_MASK				0x1
#घोषणा RG_AUDDIGMIC1EN_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDDIGMICBIAS1_SFT				1
#घोषणा RG_AUDDIGMICBIAS1_MASK				0x3
#घोषणा RG_AUDDIGMICBIAS1_MASK_SFT			(0x3 << 1)
#घोषणा RG_DMIC1HPCLKEN_SFT				3
#घोषणा RG_DMIC1HPCLKEN_MASK				0x1
#घोषणा RG_DMIC1HPCLKEN_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDDIGMIC1PDUTY_SFT				4
#घोषणा RG_AUDDIGMIC1PDUTY_MASK				0x3
#घोषणा RG_AUDDIGMIC1PDUTY_MASK_SFT			(0x3 << 4)
#घोषणा RG_AUDDIGMIC1NDUTY_SFT				6
#घोषणा RG_AUDDIGMIC1NDUTY_MASK				0x3
#घोषणा RG_AUDDIGMIC1NDUTY_MASK_SFT			(0x3 << 6)
#घोषणा RG_DMIC1MONEN_SFT				8
#घोषणा RG_DMIC1MONEN_MASK				0x1
#घोषणा RG_DMIC1MONEN_MASK_SFT				(0x1 << 8)
#घोषणा RG_DMIC1MONSEL_SFT				9
#घोषणा RG_DMIC1MONSEL_MASK				0x7
#घोषणा RG_DMIC1MONSEL_MASK_SFT				(0x7 << 9)
#घोषणा RG_AUDSPAREVMIC_SFT				12
#घोषणा RG_AUDSPAREVMIC_MASK				0xf
#घोषणा RG_AUDSPAREVMIC_MASK_SFT			(0xf << 12)

/* AUDENC_ANA_CON15 */
#घोषणा RG_AUDPWDBMICBIAS0_SFT				0
#घोषणा RG_AUDPWDBMICBIAS0_MASK				0x1
#घोषणा RG_AUDPWDBMICBIAS0_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDMICBIAS0BYPASSEN_SFT			1
#घोषणा RG_AUDMICBIAS0BYPASSEN_MASK			0x1
#घोषणा RG_AUDMICBIAS0BYPASSEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDMICBIAS0LOWPEN_SFT			2
#घोषणा RG_AUDMICBIAS0LOWPEN_MASK			0x1
#घोषणा RG_AUDMICBIAS0LOWPEN_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDPWDBMICBIAS3_SFT				3
#घोषणा RG_AUDPWDBMICBIAS3_MASK				0x1
#घोषणा RG_AUDPWDBMICBIAS3_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDMICBIAS0VREF_SFT				4
#घोषणा RG_AUDMICBIAS0VREF_MASK				0x7
#घोषणा RG_AUDMICBIAS0VREF_MASK_SFT			(0x7 << 4)
#घोषणा RG_AUDMICBIAS0DCSW0P1EN_SFT			8
#घोषणा RG_AUDMICBIAS0DCSW0P1EN_MASK			0x1
#घोषणा RG_AUDMICBIAS0DCSW0P1EN_MASK_SFT		(0x1 << 8)
#घोषणा RG_AUDMICBIAS0DCSW0P2EN_SFT			9
#घोषणा RG_AUDMICBIAS0DCSW0P2EN_MASK			0x1
#घोषणा RG_AUDMICBIAS0DCSW0P2EN_MASK_SFT		(0x1 << 9)
#घोषणा RG_AUDMICBIAS0DCSW0NEN_SFT			10
#घोषणा RG_AUDMICBIAS0DCSW0NEN_MASK			0x1
#घोषणा RG_AUDMICBIAS0DCSW0NEN_MASK_SFT			(0x1 << 10)
#घोषणा RG_AUDMICBIAS0DCSW2P1EN_SFT			12
#घोषणा RG_AUDMICBIAS0DCSW2P1EN_MASK			0x1
#घोषणा RG_AUDMICBIAS0DCSW2P1EN_MASK_SFT		(0x1 << 12)
#घोषणा RG_AUDMICBIAS0DCSW2P2EN_SFT			13
#घोषणा RG_AUDMICBIAS0DCSW2P2EN_MASK			0x1
#घोषणा RG_AUDMICBIAS0DCSW2P2EN_MASK_SFT		(0x1 << 13)
#घोषणा RG_AUDMICBIAS0DCSW2NEN_SFT			14
#घोषणा RG_AUDMICBIAS0DCSW2NEN_MASK			0x1
#घोषणा RG_AUDMICBIAS0DCSW2NEN_MASK_SFT			(0x1 << 14)

/* AUDENC_ANA_CON16 */
#घोषणा RG_AUDPWDBMICBIAS1_SFT				0
#घोषणा RG_AUDPWDBMICBIAS1_MASK				0x1
#घोषणा RG_AUDPWDBMICBIAS1_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDMICBIAS1BYPASSEN_SFT			1
#घोषणा RG_AUDMICBIAS1BYPASSEN_MASK			0x1
#घोषणा RG_AUDMICBIAS1BYPASSEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDMICBIAS1LOWPEN_SFT			2
#घोषणा RG_AUDMICBIAS1LOWPEN_MASK			0x1
#घोषणा RG_AUDMICBIAS1LOWPEN_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDMICBIAS1VREF_SFT				4
#घोषणा RG_AUDMICBIAS1VREF_MASK				0x7
#घोषणा RG_AUDMICBIAS1VREF_MASK_SFT			(0x7 << 4)
#घोषणा RG_AUDMICBIAS1DCSW1PEN_SFT			8
#घोषणा RG_AUDMICBIAS1DCSW1PEN_MASK			0x1
#घोषणा RG_AUDMICBIAS1DCSW1PEN_MASK_SFT			(0x1 << 8)
#घोषणा RG_AUDMICBIAS1DCSW1NEN_SFT			9
#घोषणा RG_AUDMICBIAS1DCSW1NEN_MASK			0x1
#घोषणा RG_AUDMICBIAS1DCSW1NEN_MASK_SFT			(0x1 << 9)
#घोषणा RG_BANDGAPGEN_SFT				10
#घोषणा RG_BANDGAPGEN_MASK				0x1
#घोषणा RG_BANDGAPGEN_MASK_SFT				(0x1 << 10)
#घोषणा RG_AUDMICBIAS1HVEN_SFT				12
#घोषणा RG_AUDMICBIAS1HVEN_MASK				0x1
#घोषणा RG_AUDMICBIAS1HVEN_MASK_SFT			(0x1 << 12)
#घोषणा RG_AUDMICBIAS1HVVREF_SFT			13
#घोषणा RG_AUDMICBIAS1HVVREF_MASK			0x1
#घोषणा RG_AUDMICBIAS1HVVREF_MASK_SFT			(0x1 << 13)

/* AUDENC_ANA_CON17 */
#घोषणा RG_AUDPWDBMICBIAS2_SFT				0
#घोषणा RG_AUDPWDBMICBIAS2_MASK				0x1
#घोषणा RG_AUDPWDBMICBIAS2_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDMICBIAS2BYPASSEN_SFT			1
#घोषणा RG_AUDMICBIAS2BYPASSEN_MASK			0x1
#घोषणा RG_AUDMICBIAS2BYPASSEN_MASK_SFT			(0x1 << 1)
#घोषणा RG_AUDMICBIAS2LOWPEN_SFT			2
#घोषणा RG_AUDMICBIAS2LOWPEN_MASK			0x1
#घोषणा RG_AUDMICBIAS2LOWPEN_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDMICBIAS2VREF_SFT				4
#घोषणा RG_AUDMICBIAS2VREF_MASK				0x7
#घोषणा RG_AUDMICBIAS2VREF_MASK_SFT			(0x7 << 4)
#घोषणा RG_AUDMICBIAS2DCSW3P1EN_SFT			8
#घोषणा RG_AUDMICBIAS2DCSW3P1EN_MASK			0x1
#घोषणा RG_AUDMICBIAS2DCSW3P1EN_MASK_SFT		(0x1 << 8)
#घोषणा RG_AUDMICBIAS2DCSW3P2EN_SFT			9
#घोषणा RG_AUDMICBIAS2DCSW3P2EN_MASK			0x1
#घोषणा RG_AUDMICBIAS2DCSW3P2EN_MASK_SFT		(0x1 << 9)
#घोषणा RG_AUDMICBIAS2DCSW3NEN_SFT			10
#घोषणा RG_AUDMICBIAS2DCSW3NEN_MASK			0x1
#घोषणा RG_AUDMICBIAS2DCSW3NEN_MASK_SFT			(0x1 << 10)
#घोषणा RG_AUDMICBIASSPARE_SFT				12
#घोषणा RG_AUDMICBIASSPARE_MASK				0xf
#घोषणा RG_AUDMICBIASSPARE_MASK_SFT			(0xf << 12)

/* AUDENC_ANA_CON18 */
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_SFT			0
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_MASK		0x1
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_MASK_SFT		(0x1 << 0)
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_SFT			1
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_MASK		0x1
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_MASK_SFT		(0x1 << 1)
#घोषणा RG_AUDACCDETMICBIAS2PULLLOW_SFT			2
#घोषणा RG_AUDACCDETMICBIAS2PULLLOW_MASK		0x1
#घोषणा RG_AUDACCDETMICBIAS2PULLLOW_MASK_SFT		(0x1 << 2)
#घोषणा RG_AUDACCDETVIN1PULLLOW_SFT			3
#घोषणा RG_AUDACCDETVIN1PULLLOW_MASK			0x1
#घोषणा RG_AUDACCDETVIN1PULLLOW_MASK_SFT		(0x1 << 3)
#घोषणा RG_AUDACCDETVTHACAL_SFT				4
#घोषणा RG_AUDACCDETVTHACAL_MASK			0x1
#घोषणा RG_AUDACCDETVTHACAL_MASK_SFT			(0x1 << 4)
#घोषणा RG_AUDACCDETVTHBCAL_SFT				5
#घोषणा RG_AUDACCDETVTHBCAL_MASK			0x1
#घोषणा RG_AUDACCDETVTHBCAL_MASK_SFT			(0x1 << 5)
#घोषणा RG_AUDACCDETTVDET_SFT				6
#घोषणा RG_AUDACCDETTVDET_MASK				0x1
#घोषणा RG_AUDACCDETTVDET_MASK_SFT			(0x1 << 6)
#घोषणा RG_ACCDETSEL_SFT				7
#घोषणा RG_ACCDETSEL_MASK				0x1
#घोषणा RG_ACCDETSEL_MASK_SFT				(0x1 << 7)
#घोषणा RG_SWBUFMODSEL_SFT				8
#घोषणा RG_SWBUFMODSEL_MASK				0x1
#घोषणा RG_SWBUFMODSEL_MASK_SFT				(0x1 << 8)
#घोषणा RG_SWBUFSWEN_SFT				9
#घोषणा RG_SWBUFSWEN_MASK				0x1
#घोषणा RG_SWBUFSWEN_MASK_SFT				(0x1 << 9)
#घोषणा RG_EINT0NOHYS_SFT				10
#घोषणा RG_EINT0NOHYS_MASK				0x1
#घोषणा RG_EINT0NOHYS_MASK_SFT				(0x1 << 10)
#घोषणा RG_EINT0CONFIGACCDET_SFT			11
#घोषणा RG_EINT0CONFIGACCDET_MASK			0x1
#घोषणा RG_EINT0CONFIGACCDET_MASK_SFT			(0x1 << 11)
#घोषणा RG_EINT0HIRENB_SFT				12
#घोषणा RG_EINT0HIRENB_MASK				0x1
#घोषणा RG_EINT0HIRENB_MASK_SFT				(0x1 << 12)
#घोषणा RG_ACCDET2AUXRESBYPASS_SFT			13
#घोषणा RG_ACCDET2AUXRESBYPASS_MASK			0x1
#घोषणा RG_ACCDET2AUXRESBYPASS_MASK_SFT			(0x1 << 13)
#घोषणा RG_ACCDET2AUXSWEN_SFT				14
#घोषणा RG_ACCDET2AUXSWEN_MASK				0x1
#घोषणा RG_ACCDET2AUXSWEN_MASK_SFT			(0x1 << 14)
#घोषणा RG_AUDACCDETMICBIAS3PULLLOW_SFT			15
#घोषणा RG_AUDACCDETMICBIAS3PULLLOW_MASK		0x1
#घोषणा RG_AUDACCDETMICBIAS3PULLLOW_MASK_SFT		(0x1 << 15)

/* AUDENC_ANA_CON19 */
#घोषणा RG_EINT1CONFIGACCDET_SFT			0
#घोषणा RG_EINT1CONFIGACCDET_MASK			0x1
#घोषणा RG_EINT1CONFIGACCDET_MASK_SFT			(0x1 << 0)
#घोषणा RG_EINT1HIRENB_SFT				1
#घोषणा RG_EINT1HIRENB_MASK				0x1
#घोषणा RG_EINT1HIRENB_MASK_SFT				(0x1 << 1)
#घोषणा RG_EINT1NOHYS_SFT				2
#घोषणा RG_EINT1NOHYS_MASK				0x1
#घोषणा RG_EINT1NOHYS_MASK_SFT				(0x1 << 2)
#घोषणा RG_EINTCOMPVTH_SFT				4
#घोषणा RG_EINTCOMPVTH_MASK				0xf
#घोषणा RG_EINTCOMPVTH_MASK_SFT				(0xf << 4)
#घोषणा RG_MTEST_EN_SFT					8
#घोषणा RG_MTEST_EN_MASK				0x1
#घोषणा RG_MTEST_EN_MASK_SFT				(0x1 << 8)
#घोषणा RG_MTEST_SEL_SFT				9
#घोषणा RG_MTEST_SEL_MASK				0x1
#घोषणा RG_MTEST_SEL_MASK_SFT				(0x1 << 9)
#घोषणा RG_MTEST_CURRENT_SFT				10
#घोषणा RG_MTEST_CURRENT_MASK				0x1
#घोषणा RG_MTEST_CURRENT_MASK_SFT			(0x1 << 10)
#घोषणा RG_ANALOGFDEN_SFT				12
#घोषणा RG_ANALOGFDEN_MASK				0x1
#घोषणा RG_ANALOGFDEN_MASK_SFT				(0x1 << 12)
#घोषणा RG_FDVIN1PPULLLOW_SFT				13
#घोषणा RG_FDVIN1PPULLLOW_MASK				0x1
#घोषणा RG_FDVIN1PPULLLOW_MASK_SFT			(0x1 << 13)
#घोषणा RG_FDEINT0TYPE_SFT				14
#घोषणा RG_FDEINT0TYPE_MASK				0x1
#घोषणा RG_FDEINT0TYPE_MASK_SFT				(0x1 << 14)
#घोषणा RG_FDEINT1TYPE_SFT				15
#घोषणा RG_FDEINT1TYPE_MASK				0x1
#घोषणा RG_FDEINT1TYPE_MASK_SFT				(0x1 << 15)

/* AUDENC_ANA_CON20 */
#घोषणा RG_EINT0CMPEN_SFT				0
#घोषणा RG_EINT0CMPEN_MASK				0x1
#घोषणा RG_EINT0CMPEN_MASK_SFT				(0x1 << 0)
#घोषणा RG_EINT0CMPMEN_SFT				1
#घोषणा RG_EINT0CMPMEN_MASK				0x1
#घोषणा RG_EINT0CMPMEN_MASK_SFT				(0x1 << 1)
#घोषणा RG_EINT0EN_SFT					2
#घोषणा RG_EINT0EN_MASK					0x1
#घोषणा RG_EINT0EN_MASK_SFT				(0x1 << 2)
#घोषणा RG_EINT0CEN_SFT					3
#घोषणा RG_EINT0CEN_MASK				0x1
#घोषणा RG_EINT0CEN_MASK_SFT				(0x1 << 3)
#घोषणा RG_EINT0INVEN_SFT				4
#घोषणा RG_EINT0INVEN_MASK				0x1
#घोषणा RG_EINT0INVEN_MASK_SFT				(0x1 << 4)
#घोषणा RG_EINT0CTURBO_SFT				5
#घोषणा RG_EINT0CTURBO_MASK				0x7
#घोषणा RG_EINT0CTURBO_MASK_SFT				(0x7 << 5)
#घोषणा RG_EINT1CMPEN_SFT				8
#घोषणा RG_EINT1CMPEN_MASK				0x1
#घोषणा RG_EINT1CMPEN_MASK_SFT				(0x1 << 8)
#घोषणा RG_EINT1CMPMEN_SFT				9
#घोषणा RG_EINT1CMPMEN_MASK				0x1
#घोषणा RG_EINT1CMPMEN_MASK_SFT				(0x1 << 9)
#घोषणा RG_EINT1EN_SFT					10
#घोषणा RG_EINT1EN_MASK					0x1
#घोषणा RG_EINT1EN_MASK_SFT				(0x1 << 10)
#घोषणा RG_EINT1CEN_SFT					11
#घोषणा RG_EINT1CEN_MASK				0x1
#घोषणा RG_EINT1CEN_MASK_SFT				(0x1 << 11)
#घोषणा RG_EINT1INVEN_SFT				12
#घोषणा RG_EINT1INVEN_MASK				0x1
#घोषणा RG_EINT1INVEN_MASK_SFT				(0x1 << 12)
#घोषणा RG_EINT1CTURBO_SFT				13
#घोषणा RG_EINT1CTURBO_MASK				0x7
#घोषणा RG_EINT1CTURBO_MASK_SFT				(0x7 << 13)

/* AUDENC_ANA_CON21 */
#घोषणा RG_ACCDETSPARE_SFT				0
#घोषणा RG_ACCDETSPARE_MASK				0xffff
#घोषणा RG_ACCDETSPARE_MASK_SFT				(0xffff << 0)

/* AUDENC_ANA_CON22 */
#घोषणा RG_AUDENCSPAREVA30_SFT				0
#घोषणा RG_AUDENCSPAREVA30_MASK				0xff
#घोषणा RG_AUDENCSPAREVA30_MASK_SFT			(0xff << 0)
#घोषणा RG_AUDENCSPAREVA18_SFT				8
#घोषणा RG_AUDENCSPAREVA18_MASK				0xff
#घोषणा RG_AUDENCSPAREVA18_MASK_SFT			(0xff << 8)

/* AUDENC_ANA_CON23 */
#घोषणा RG_CLKSQ_EN_SFT					0
#घोषणा RG_CLKSQ_EN_MASK				0x1
#घोषणा RG_CLKSQ_EN_MASK_SFT				(0x1 << 0)
#घोषणा RG_CLKSQ_IN_SEL_TEST_SFT			1
#घोषणा RG_CLKSQ_IN_SEL_TEST_MASK			0x1
#घोषणा RG_CLKSQ_IN_SEL_TEST_MASK_SFT			(0x1 << 1)
#घोषणा RG_CM_REFGENSEL_SFT				2
#घोषणा RG_CM_REFGENSEL_MASK				0x1
#घोषणा RG_CM_REFGENSEL_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDIO_VOW_EN_SFT				3
#घोषणा RG_AUDIO_VOW_EN_MASK				0x1
#घोषणा RG_AUDIO_VOW_EN_MASK_SFT			(0x1 << 3)
#घोषणा RG_CLKSQ_EN_VOW_SFT				4
#घोषणा RG_CLKSQ_EN_VOW_MASK				0x1
#घोषणा RG_CLKSQ_EN_VOW_MASK_SFT			(0x1 << 4)
#घोषणा RG_CLKAND_EN_VOW_SFT				5
#घोषणा RG_CLKAND_EN_VOW_MASK				0x1
#घोषणा RG_CLKAND_EN_VOW_MASK_SFT			(0x1 << 5)
#घोषणा RG_VOWCLK_SEL_EN_VOW_SFT			6
#घोषणा RG_VOWCLK_SEL_EN_VOW_MASK			0x1
#घोषणा RG_VOWCLK_SEL_EN_VOW_MASK_SFT			(0x1 << 6)
#घोषणा RG_SPARE_VOW_SFT				7
#घोषणा RG_SPARE_VOW_MASK				0x7
#घोषणा RG_SPARE_VOW_MASK_SFT				(0x7 << 7)

/* AUDDEC_ANA_CON0 */
#घोषणा RG_AUDDACLPWRUP_VAUDP32_SFT			0
#घोषणा RG_AUDDACLPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDDACLPWRUP_VAUDP32_MASK_SFT		(0x1 << 0)
#घोषणा RG_AUDDACRPWRUP_VAUDP32_SFT			1
#घोषणा RG_AUDDACRPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDDACRPWRUP_VAUDP32_MASK_SFT		(0x1 << 1)
#घोषणा RG_AUD_DAC_PWR_UP_VA32_SFT			2
#घोषणा RG_AUD_DAC_PWR_UP_VA32_MASK			0x1
#घोषणा RG_AUD_DAC_PWR_UP_VA32_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUD_DAC_PWL_UP_VA32_SFT			3
#घोषणा RG_AUD_DAC_PWL_UP_VA32_MASK			0x1
#घोषणा RG_AUD_DAC_PWL_UP_VA32_MASK_SFT			(0x1 << 3)
#घोषणा RG_AUDHPLPWRUP_VAUDP32_SFT			4
#घोषणा RG_AUDHPLPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPLPWRUP_VAUDP32_MASK_SFT			(0x1 << 4)
#घोषणा RG_AUDHPRPWRUP_VAUDP32_SFT			5
#घोषणा RG_AUDHPRPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPRPWRUP_VAUDP32_MASK_SFT			(0x1 << 5)
#घोषणा RG_AUDHPLPWRUP_IBIAS_VAUDP32_SFT		6
#घोषणा RG_AUDHPLPWRUP_IBIAS_VAUDP32_MASK		0x1
#घोषणा RG_AUDHPLPWRUP_IBIAS_VAUDP32_MASK_SFT		(0x1 << 6)
#घोषणा RG_AUDHPRPWRUP_IBIAS_VAUDP32_SFT		7
#घोषणा RG_AUDHPRPWRUP_IBIAS_VAUDP32_MASK		0x1
#घोषणा RG_AUDHPRPWRUP_IBIAS_VAUDP32_MASK_SFT		(0x1 << 7)
#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP32_SFT		8
#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP32_MASK		0x3
#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP32_MASK_SFT		(0x3 << 8)
#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP32_SFT		10
#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP32_MASK		0x3
#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP32_MASK_SFT		(0x3 << 10)
#घोषणा RG_AUDHPLSCDISABLE_VAUDP32_SFT			12
#घोषणा RG_AUDHPLSCDISABLE_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPLSCDISABLE_VAUDP32_MASK_SFT		(0x1 << 12)
#घोषणा RG_AUDHPRSCDISABLE_VAUDP32_SFT			13
#घोषणा RG_AUDHPRSCDISABLE_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPRSCDISABLE_VAUDP32_MASK_SFT		(0x1 << 13)
#घोषणा RG_AUDHPLBSCCURRENT_VAUDP32_SFT			14
#घोषणा RG_AUDHPLBSCCURRENT_VAUDP32_MASK		0x1
#घोषणा RG_AUDHPLBSCCURRENT_VAUDP32_MASK_SFT		(0x1 << 14)
#घोषणा RG_AUDHPRBSCCURRENT_VAUDP32_SFT			15
#घोषणा RG_AUDHPRBSCCURRENT_VAUDP32_MASK		0x1
#घोषणा RG_AUDHPRBSCCURRENT_VAUDP32_MASK_SFT		(0x1 << 15)

/* AUDDEC_ANA_CON1 */
#घोषणा RG_AUDHPLOUTPWRUP_VAUDP32_SFT			0
#घोषणा RG_AUDHPLOUTPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPLOUTPWRUP_VAUDP32_MASK_SFT		(0x1 << 0)
#घोषणा RG_AUDHPROUTPWRUP_VAUDP32_SFT			1
#घोषणा RG_AUDHPROUTPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPROUTPWRUP_VAUDP32_MASK_SFT		(0x1 << 1)
#घोषणा RG_AUDHPLOUTAUXPWRUP_VAUDP32_SFT		2
#घोषणा RG_AUDHPLOUTAUXPWRUP_VAUDP32_MASK		0x1
#घोषणा RG_AUDHPLOUTAUXPWRUP_VAUDP32_MASK_SFT		(0x1 << 2)
#घोषणा RG_AUDHPROUTAUXPWRUP_VAUDP32_SFT		3
#घोषणा RG_AUDHPROUTAUXPWRUP_VAUDP32_MASK		0x1
#घोषणा RG_AUDHPROUTAUXPWRUP_VAUDP32_MASK_SFT		(0x1 << 3)
#घोषणा RG_HPLAUXFBRSW_EN_VAUDP32_SFT			4
#घोषणा RG_HPLAUXFBRSW_EN_VAUDP32_MASK			0x1
#घोषणा RG_HPLAUXFBRSW_EN_VAUDP32_MASK_SFT		(0x1 << 4)
#घोषणा RG_HPRAUXFBRSW_EN_VAUDP32_SFT			5
#घोषणा RG_HPRAUXFBRSW_EN_VAUDP32_MASK			0x1
#घोषणा RG_HPRAUXFBRSW_EN_VAUDP32_MASK_SFT		(0x1 << 5)
#घोषणा RG_HPLSHORT2HPLAUX_EN_VAUDP32_SFT		6
#घोषणा RG_HPLSHORT2HPLAUX_EN_VAUDP32_MASK		0x1
#घोषणा RG_HPLSHORT2HPLAUX_EN_VAUDP32_MASK_SFT		(0x1 << 6)
#घोषणा RG_HPRSHORT2HPRAUX_EN_VAUDP32_SFT		7
#घोषणा RG_HPRSHORT2HPRAUX_EN_VAUDP32_MASK		0x1
#घोषणा RG_HPRSHORT2HPRAUX_EN_VAUDP32_MASK_SFT		(0x1 << 7)
#घोषणा RG_HPLOUTSTGCTRL_VAUDP32_SFT			8
#घोषणा RG_HPLOUTSTGCTRL_VAUDP32_MASK			0x7
#घोषणा RG_HPLOUTSTGCTRL_VAUDP32_MASK_SFT		(0x7 << 8)
#घोषणा RG_HPROUTSTGCTRL_VAUDP32_SFT			12
#घोषणा RG_HPROUTSTGCTRL_VAUDP32_MASK			0x7
#घोषणा RG_HPROUTSTGCTRL_VAUDP32_MASK_SFT		(0x7 << 12)

/* AUDDEC_ANA_CON2 */
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP32_SFT			0
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP32_MASK			0x7
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP32_MASK_SFT		(0x7 << 0)
#घोषणा RG_HPROUTPUTSTBENH_VAUDP32_SFT			4
#घोषणा RG_HPROUTPUTSTBENH_VAUDP32_MASK			0x7
#घोषणा RG_HPROUTPUTSTBENH_VAUDP32_MASK_SFT		(0x7 << 4)
#घोषणा RG_AUDHPSTARTUP_VAUDP32_SFT			7
#घोषणा RG_AUDHPSTARTUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPSTARTUP_VAUDP32_MASK_SFT		(0x1 << 7)
#घोषणा RG_AUDREFN_DERES_EN_VAUDP32_SFT			8
#घोषणा RG_AUDREFN_DERES_EN_VAUDP32_MASK		0x1
#घोषणा RG_AUDREFN_DERES_EN_VAUDP32_MASK_SFT		(0x1 << 8)
#घोषणा RG_HPINPUTSTBENH_VAUDP32_SFT			9
#घोषणा RG_HPINPUTSTBENH_VAUDP32_MASK			0x1
#घोषणा RG_HPINPUTSTBENH_VAUDP32_MASK_SFT		(0x1 << 9)
#घोषणा RG_HPINPUTRESET0_VAUDP32_SFT			10
#घोषणा RG_HPINPUTRESET0_VAUDP32_MASK			0x1
#घोषणा RG_HPINPUTRESET0_VAUDP32_MASK_SFT		(0x1 << 10)
#घोषणा RG_HPOUTPUTRESET0_VAUDP32_SFT			11
#घोषणा RG_HPOUTPUTRESET0_VAUDP32_MASK			0x1
#घोषणा RG_HPOUTPUTRESET0_VAUDP32_MASK_SFT		(0x1 << 11)
#घोषणा RG_HPPSHORT2VCM_VAUDP32_SFT			12
#घोषणा RG_HPPSHORT2VCM_VAUDP32_MASK			0x7
#घोषणा RG_HPPSHORT2VCM_VAUDP32_MASK_SFT		(0x7 << 12)
#घोषणा RG_AUDHPTRIM_EN_VAUDP32_SFT			15
#घोषणा RG_AUDHPTRIM_EN_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPTRIM_EN_VAUDP32_MASK_SFT		(0x1 << 15)

/* AUDDEC_ANA_CON3 */
#घोषणा RG_AUDHPLTRIM_VAUDP32_SFT			0
#घोषणा RG_AUDHPLTRIM_VAUDP32_MASK			0x1f
#घोषणा RG_AUDHPLTRIM_VAUDP32_MASK_SFT			(0x1f << 0)
#घोषणा RG_AUDHPLFINETRIM_VAUDP32_SFT			5
#घोषणा RG_AUDHPLFINETRIM_VAUDP32_MASK			0x7
#घोषणा RG_AUDHPLFINETRIM_VAUDP32_MASK_SFT		(0x7 << 5)
#घोषणा RG_AUDHPRTRIM_VAUDP32_SFT			8
#घोषणा RG_AUDHPRTRIM_VAUDP32_MASK			0x1f
#घोषणा RG_AUDHPRTRIM_VAUDP32_MASK_SFT			(0x1f << 8)
#घोषणा RG_AUDHPRFINETRIM_VAUDP32_SFT			13
#घोषणा RG_AUDHPRFINETRIM_VAUDP32_MASK			0x7
#घोषणा RG_AUDHPRFINETRIM_VAUDP32_MASK_SFT		(0x7 << 13)

/* AUDDEC_ANA_CON4 */
#घोषणा RG_AUDHPDIFFINPBIASADJ_VAUDP32_SFT		0
#घोषणा RG_AUDHPDIFFINPBIASADJ_VAUDP32_MASK		0x7
#घोषणा RG_AUDHPDIFFINPBIASADJ_VAUDP32_MASK_SFT		(0x7 << 0)
#घोषणा RG_AUDHPLFCOMPRESSEL_VAUDP32_SFT		4
#घोषणा RG_AUDHPLFCOMPRESSEL_VAUDP32_MASK		0x7
#घोषणा RG_AUDHPLFCOMPRESSEL_VAUDP32_MASK_SFT		(0x7 << 4)
#घोषणा RG_AUDHPHFCOMPRESSEL_VAUDP32_SFT		8
#घोषणा RG_AUDHPHFCOMPRESSEL_VAUDP32_MASK		0x7
#घोषणा RG_AUDHPHFCOMPRESSEL_VAUDP32_MASK_SFT		(0x7 << 8)
#घोषणा RG_AUDHPHFCOMPBUFGAINSEL_VAUDP32_SFT		12
#घोषणा RG_AUDHPHFCOMPBUFGAINSEL_VAUDP32_MASK		0x3
#घोषणा RG_AUDHPHFCOMPBUFGAINSEL_VAUDP32_MASK_SFT	(0x3 << 12)
#घोषणा RG_AUDHPCOMP_EN_VAUDP32_SFT			15
#घोषणा RG_AUDHPCOMP_EN_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPCOMP_EN_VAUDP32_MASK_SFT		(0x1 << 15)

/* AUDDEC_ANA_CON5 */
#घोषणा RG_AUDHPDECMGAINADJ_VAUDP32_SFT			0
#घोषणा RG_AUDHPDECMGAINADJ_VAUDP32_MASK		0x7
#घोषणा RG_AUDHPDECMGAINADJ_VAUDP32_MASK_SFT		(0x7 << 0)
#घोषणा RG_AUDHPDEDMGAINADJ_VAUDP32_SFT			4
#घोषणा RG_AUDHPDEDMGAINADJ_VAUDP32_MASK		0x7
#घोषणा RG_AUDHPDEDMGAINADJ_VAUDP32_MASK_SFT		(0x7 << 4)

/* AUDDEC_ANA_CON6 */
#घोषणा RG_AUDHSPWRUP_VAUDP32_SFT			0
#घोषणा RG_AUDHSPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDHSPWRUP_VAUDP32_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDHSPWRUP_IBIAS_VAUDP32_SFT			1
#घोषणा RG_AUDHSPWRUP_IBIAS_VAUDP32_MASK		0x1
#घोषणा RG_AUDHSPWRUP_IBIAS_VAUDP32_MASK_SFT		(0x1 << 1)
#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP32_SFT			2
#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP32_MASK		0x3
#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP32_MASK_SFT		(0x3 << 2)
#घोषणा RG_AUDHSSCDISABLE_VAUDP32_SFT			4
#घोषणा RG_AUDHSSCDISABLE_VAUDP32_MASK			0x1
#घोषणा RG_AUDHSSCDISABLE_VAUDP32_MASK_SFT		(0x1 << 4)
#घोषणा RG_AUDHSBSCCURRENT_VAUDP32_SFT			5
#घोषणा RG_AUDHSBSCCURRENT_VAUDP32_MASK			0x1
#घोषणा RG_AUDHSBSCCURRENT_VAUDP32_MASK_SFT		(0x1 << 5)
#घोषणा RG_AUDHSSTARTUP_VAUDP32_SFT			6
#घोषणा RG_AUDHSSTARTUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDHSSTARTUP_VAUDP32_MASK_SFT		(0x1 << 6)
#घोषणा RG_HSOUTPUTSTBENH_VAUDP32_SFT			7
#घोषणा RG_HSOUTPUTSTBENH_VAUDP32_MASK			0x1
#घोषणा RG_HSOUTPUTSTBENH_VAUDP32_MASK_SFT		(0x1 << 7)
#घोषणा RG_HSINPUTSTBENH_VAUDP32_SFT			8
#घोषणा RG_HSINPUTSTBENH_VAUDP32_MASK			0x1
#घोषणा RG_HSINPUTSTBENH_VAUDP32_MASK_SFT		(0x1 << 8)
#घोषणा RG_HSINPUTRESET0_VAUDP32_SFT			9
#घोषणा RG_HSINPUTRESET0_VAUDP32_MASK			0x1
#घोषणा RG_HSINPUTRESET0_VAUDP32_MASK_SFT		(0x1 << 9)
#घोषणा RG_HSOUTPUTRESET0_VAUDP32_SFT			10
#घोषणा RG_HSOUTPUTRESET0_VAUDP32_MASK			0x1
#घोषणा RG_HSOUTPUTRESET0_VAUDP32_MASK_SFT		(0x1 << 10)
#घोषणा RG_HSOUT_SHORTVCM_VAUDP32_SFT			11
#घोषणा RG_HSOUT_SHORTVCM_VAUDP32_MASK			0x1
#घोषणा RG_HSOUT_SHORTVCM_VAUDP32_MASK_SFT		(0x1 << 11)

/* AUDDEC_ANA_CON7 */
#घोषणा RG_AUDLOLPWRUP_VAUDP32_SFT			0
#घोषणा RG_AUDLOLPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDLOLPWRUP_VAUDP32_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDLOLPWRUP_IBIAS_VAUDP32_SFT		1
#घोषणा RG_AUDLOLPWRUP_IBIAS_VAUDP32_MASK		0x1
#घोषणा RG_AUDLOLPWRUP_IBIAS_VAUDP32_MASK_SFT		(0x1 << 1)
#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP32_SFT		2
#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP32_MASK		0x3
#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP32_MASK_SFT		(0x3 << 2)
#घोषणा RG_AUDLOLSCDISABLE_VAUDP32_SFT			4
#घोषणा RG_AUDLOLSCDISABLE_VAUDP32_MASK			0x1
#घोषणा RG_AUDLOLSCDISABLE_VAUDP32_MASK_SFT		(0x1 << 4)
#घोषणा RG_AUDLOLBSCCURRENT_VAUDP32_SFT			5
#घोषणा RG_AUDLOLBSCCURRENT_VAUDP32_MASK		0x1
#घोषणा RG_AUDLOLBSCCURRENT_VAUDP32_MASK_SFT		(0x1 << 5)
#घोषणा RG_AUDLOSTARTUP_VAUDP32_SFT			6
#घोषणा RG_AUDLOSTARTUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDLOSTARTUP_VAUDP32_MASK_SFT		(0x1 << 6)
#घोषणा RG_LOINPUTSTBENH_VAUDP32_SFT			7
#घोषणा RG_LOINPUTSTBENH_VAUDP32_MASK			0x1
#घोषणा RG_LOINPUTSTBENH_VAUDP32_MASK_SFT		(0x1 << 7)
#घोषणा RG_LOOUTPUTSTBENH_VAUDP32_SFT			8
#घोषणा RG_LOOUTPUTSTBENH_VAUDP32_MASK			0x1
#घोषणा RG_LOOUTPUTSTBENH_VAUDP32_MASK_SFT		(0x1 << 8)
#घोषणा RG_LOINPUTRESET0_VAUDP32_SFT			9
#घोषणा RG_LOINPUTRESET0_VAUDP32_MASK			0x1
#घोषणा RG_LOINPUTRESET0_VAUDP32_MASK_SFT		(0x1 << 9)
#घोषणा RG_LOOUTPUTRESET0_VAUDP32_SFT			10
#घोषणा RG_LOOUTPUTRESET0_VAUDP32_MASK			0x1
#घोषणा RG_LOOUTPUTRESET0_VAUDP32_MASK_SFT		(0x1 << 10)
#घोषणा RG_LOOUT_SHORTVCM_VAUDP32_SFT			11
#घोषणा RG_LOOUT_SHORTVCM_VAUDP32_MASK			0x1
#घोषणा RG_LOOUT_SHORTVCM_VAUDP32_MASK_SFT		(0x1 << 11)
#घोषणा RG_AUDDACTPWRUP_VAUDP32_SFT			12
#घोषणा RG_AUDDACTPWRUP_VAUDP32_MASK			0x1
#घोषणा RG_AUDDACTPWRUP_VAUDP32_MASK_SFT		(0x1 << 12)
#घोषणा RG_AUD_DAC_PWT_UP_VA32_SFT			13
#घोषणा RG_AUD_DAC_PWT_UP_VA32_MASK			0x1
#घोषणा RG_AUD_DAC_PWT_UP_VA32_MASK_SFT			(0x1 << 13)

/* AUDDEC_ANA_CON8 */
#घोषणा RG_AUDTRIMBUF_INPUTMUXSEL_VAUDP32_SFT		0
#घोषणा RG_AUDTRIMBUF_INPUTMUXSEL_VAUDP32_MASK		0xf
#घोषणा RG_AUDTRIMBUF_INPUTMUXSEL_VAUDP32_MASK_SFT	(0xf << 0)
#घोषणा RG_AUDTRIMBUF_GAINSEL_VAUDP32_SFT		4
#घोषणा RG_AUDTRIMBUF_GAINSEL_VAUDP32_MASK		0x3
#घोषणा RG_AUDTRIMBUF_GAINSEL_VAUDP32_MASK_SFT		(0x3 << 4)
#घोषणा RG_AUDTRIMBUF_EN_VAUDP32_SFT			6
#घोषणा RG_AUDTRIMBUF_EN_VAUDP32_MASK			0x1
#घोषणा RG_AUDTRIMBUF_EN_VAUDP32_MASK_SFT		(0x1 << 6)
#घोषणा RG_AUDHPSPKDET_INPUTMUXSEL_VAUDP32_SFT		8
#घोषणा RG_AUDHPSPKDET_INPUTMUXSEL_VAUDP32_MASK		0x3
#घोषणा RG_AUDHPSPKDET_INPUTMUXSEL_VAUDP32_MASK_SFT	(0x3 << 8)
#घोषणा RG_AUDHPSPKDET_OUTPUTMUXSEL_VAUDP32_SFT		10
#घोषणा RG_AUDHPSPKDET_OUTPUTMUXSEL_VAUDP32_MASK	0x3
#घोषणा RG_AUDHPSPKDET_OUTPUTMUXSEL_VAUDP32_MASK_SFT	(0x3 << 10)
#घोषणा RG_AUDHPSPKDET_EN_VAUDP32_SFT			12
#घोषणा RG_AUDHPSPKDET_EN_VAUDP32_MASK			0x1
#घोषणा RG_AUDHPSPKDET_EN_VAUDP32_MASK_SFT		(0x1 << 12)

/* AUDDEC_ANA_CON9 */
#घोषणा RG_ABIDEC_RSVD0_VA32_SFT			0
#घोषणा RG_ABIDEC_RSVD0_VA32_MASK			0xff
#घोषणा RG_ABIDEC_RSVD0_VA32_MASK_SFT			(0xff << 0)
#घोषणा RG_ABIDEC_RSVD0_VAUDP32_SFT			8
#घोषणा RG_ABIDEC_RSVD0_VAUDP32_MASK			0xff
#घोषणा RG_ABIDEC_RSVD0_VAUDP32_MASK_SFT		(0xff << 8)

/* AUDDEC_ANA_CON10 */
#घोषणा RG_ABIDEC_RSVD1_VAUDP32_SFT			0
#घोषणा RG_ABIDEC_RSVD1_VAUDP32_MASK			0xff
#घोषणा RG_ABIDEC_RSVD1_VAUDP32_MASK_SFT		(0xff << 0)
#घोषणा RG_ABIDEC_RSVD2_VAUDP32_SFT			8
#घोषणा RG_ABIDEC_RSVD2_VAUDP32_MASK			0xff
#घोषणा RG_ABIDEC_RSVD2_VAUDP32_MASK_SFT		(0xff << 8)

/* AUDDEC_ANA_CON11 */
#घोषणा RG_AUDZCDMUXSEL_VAUDP32_SFT			0
#घोषणा RG_AUDZCDMUXSEL_VAUDP32_MASK			0x7
#घोषणा RG_AUDZCDMUXSEL_VAUDP32_MASK_SFT		(0x7 << 0)
#घोषणा RG_AUDZCDCLKSEL_VAUDP32_SFT			3
#घोषणा RG_AUDZCDCLKSEL_VAUDP32_MASK			0x1
#घोषणा RG_AUDZCDCLKSEL_VAUDP32_MASK_SFT		(0x1 << 3)
#घोषणा RG_AUDBIASADJ_0_VAUDP32_SFT			7
#घोषणा RG_AUDBIASADJ_0_VAUDP32_MASK			0x1ff
#घोषणा RG_AUDBIASADJ_0_VAUDP32_MASK_SFT		(0x1ff << 7)

/* AUDDEC_ANA_CON12 */
#घोषणा RG_AUDBIASADJ_1_VAUDP32_SFT			0
#घोषणा RG_AUDBIASADJ_1_VAUDP32_MASK			0xff
#घोषणा RG_AUDBIASADJ_1_VAUDP32_MASK_SFT		(0xff << 0)
#घोषणा RG_AUDIBIASPWRDN_VAUDP32_SFT			8
#घोषणा RG_AUDIBIASPWRDN_VAUDP32_MASK			0x1
#घोषणा RG_AUDIBIASPWRDN_VAUDP32_MASK_SFT		(0x1 << 8)

/* AUDDEC_ANA_CON13 */
#घोषणा RG_RSTB_DECODER_VA32_SFT			0
#घोषणा RG_RSTB_DECODER_VA32_MASK			0x1
#घोषणा RG_RSTB_DECODER_VA32_MASK_SFT			(0x1 << 0)
#घोषणा RG_SEL_DECODER_96K_VA32_SFT			1
#घोषणा RG_SEL_DECODER_96K_VA32_MASK			0x1
#घोषणा RG_SEL_DECODER_96K_VA32_MASK_SFT		(0x1 << 1)
#घोषणा RG_SEL_DELAY_VCORE_SFT				2
#घोषणा RG_SEL_DELAY_VCORE_MASK				0x1
#घोषणा RG_SEL_DELAY_VCORE_MASK_SFT			(0x1 << 2)
#घोषणा RG_AUDGLB_PWRDN_VA32_SFT			4
#घोषणा RG_AUDGLB_PWRDN_VA32_MASK			0x1
#घोषणा RG_AUDGLB_PWRDN_VA32_MASK_SFT			(0x1 << 4)
#घोषणा RG_AUDGLB_LP_VOW_EN_VA32_SFT			5
#घोषणा RG_AUDGLB_LP_VOW_EN_VA32_MASK			0x1
#घोषणा RG_AUDGLB_LP_VOW_EN_VA32_MASK_SFT		(0x1 << 5)
#घोषणा RG_AUDGLB_LP2_VOW_EN_VA32_SFT			6
#घोषणा RG_AUDGLB_LP2_VOW_EN_VA32_MASK			0x1
#घोषणा RG_AUDGLB_LP2_VOW_EN_VA32_MASK_SFT		(0x1 << 6)

/* AUDDEC_ANA_CON14 */
#घोषणा RG_LCLDO_DEC_EN_VA32_SFT			0
#घोषणा RG_LCLDO_DEC_EN_VA32_MASK			0x1
#घोषणा RG_LCLDO_DEC_EN_VA32_MASK_SFT			(0x1 << 0)
#घोषणा RG_LCLDO_DEC_PDDIS_EN_VA18_SFT			1
#घोषणा RG_LCLDO_DEC_PDDIS_EN_VA18_MASK			0x1
#घोषणा RG_LCLDO_DEC_PDDIS_EN_VA18_MASK_SFT		(0x1 << 1)
#घोषणा RG_LCLDO_DEC_REMOTE_SENSE_VA18_SFT		2
#घोषणा RG_LCLDO_DEC_REMOTE_SENSE_VA18_MASK		0x1
#घोषणा RG_LCLDO_DEC_REMOTE_SENSE_VA18_MASK_SFT		(0x1 << 2)
#घोषणा RG_NVREG_EN_VAUDP32_SFT				4
#घोषणा RG_NVREG_EN_VAUDP32_MASK			0x1
#घोषणा RG_NVREG_EN_VAUDP32_MASK_SFT			(0x1 << 4)
#घोषणा RG_NVREG_PULL0V_VAUDP32_SFT			5
#घोषणा RG_NVREG_PULL0V_VAUDP32_MASK			0x1
#घोषणा RG_NVREG_PULL0V_VAUDP32_MASK_SFT		(0x1 << 5)
#घोषणा RG_AUDPMU_RSVD_VA18_SFT				8
#घोषणा RG_AUDPMU_RSVD_VA18_MASK			0xff
#घोषणा RG_AUDPMU_RSVD_VA18_MASK_SFT			(0xff << 8)

/* MT6359_ZCD_CON0 */
#घोषणा RG_AUDZCDENABLE_SFT				0
#घोषणा RG_AUDZCDENABLE_MASK				0x1
#घोषणा RG_AUDZCDENABLE_MASK_SFT			(0x1 << 0)
#घोषणा RG_AUDZCDGAINSTEPTIME_SFT			1
#घोषणा RG_AUDZCDGAINSTEPTIME_MASK			0x7
#घोषणा RG_AUDZCDGAINSTEPTIME_MASK_SFT			(0x7 << 1)
#घोषणा RG_AUDZCDGAINSTEPSIZE_SFT			4
#घोषणा RG_AUDZCDGAINSTEPSIZE_MASK			0x3
#घोषणा RG_AUDZCDGAINSTEPSIZE_MASK_SFT			(0x3 << 4)
#घोषणा RG_AUDZCDTIMEOUTMODESEL_SFT			6
#घोषणा RG_AUDZCDTIMEOUTMODESEL_MASK			0x1
#घोषणा RG_AUDZCDTIMEOUTMODESEL_MASK_SFT		(0x1 << 6)

/* MT6359_ZCD_CON1 */
#घोषणा RG_AUDLOLGAIN_SFT				0
#घोषणा RG_AUDLOLGAIN_MASK				0x1f
#घोषणा RG_AUDLOLGAIN_MASK_SFT				(0x1f << 0)
#घोषणा RG_AUDLORGAIN_SFT				7
#घोषणा RG_AUDLORGAIN_MASK				0x1f
#घोषणा RG_AUDLORGAIN_MASK_SFT				(0x1f << 7)

/* MT6359_ZCD_CON2 */
#घोषणा RG_AUDHPLGAIN_SFT				0
#घोषणा RG_AUDHPLGAIN_MASK				0x1f
#घोषणा RG_AUDHPLGAIN_MASK_SFT				(0x1f << 0)
#घोषणा RG_AUDHPRGAIN_SFT				7
#घोषणा RG_AUDHPRGAIN_MASK				0x1f
#घोषणा RG_AUDHPRGAIN_MASK_SFT				(0x1f << 7)

/* MT6359_ZCD_CON3 */
#घोषणा RG_AUDHSGAIN_SFT				0
#घोषणा RG_AUDHSGAIN_MASK				0x1f
#घोषणा RG_AUDHSGAIN_MASK_SFT				(0x1f << 0)

/* MT6359_ZCD_CON4 */
#घोषणा RG_AUDIVLGAIN_SFT				0
#घोषणा RG_AUDIVLGAIN_MASK				0x7
#घोषणा RG_AUDIVLGAIN_MASK_SFT				(0x7 << 0)
#घोषणा RG_AUDIVRGAIN_SFT				8
#घोषणा RG_AUDIVRGAIN_MASK				0x7
#घोषणा RG_AUDIVRGAIN_MASK_SFT				(0x7 << 8)

/* MT6359_ZCD_CON5 */
#घोषणा RG_AUDINTGAIN1_SFT				0
#घोषणा RG_AUDINTGAIN1_MASK				0x3f
#घोषणा RG_AUDINTGAIN1_MASK_SFT				(0x3f << 0)
#घोषणा RG_AUDINTGAIN2_SFT				8
#घोषणा RG_AUDINTGAIN2_MASK				0x3f
#घोषणा RG_AUDINTGAIN2_MASK_SFT				(0x3f << 8)

/* audio रेजिस्टर */
#घोषणा MT6359_GPIO_सूची0				0x88
#घोषणा MT6359_GPIO_सूची0_SET				0x8a
#घोषणा MT6359_GPIO_सूची0_CLR				0x8c
#घोषणा MT6359_GPIO_सूची1				0x8e
#घोषणा MT6359_GPIO_सूची1_SET				0x90
#घोषणा MT6359_GPIO_सूची1_CLR				0x92

#घोषणा MT6359_DCXO_CW11				0x7a6
#घोषणा MT6359_DCXO_CW12				0x7a8

#घोषणा MT6359_GPIO_MODE0				0xcc
#घोषणा MT6359_GPIO_MODE0_SET				0xce
#घोषणा MT6359_GPIO_MODE0_CLR				0xd0
#घोषणा MT6359_GPIO_MODE1				0xd2
#घोषणा MT6359_GPIO_MODE1_SET				0xd4
#घोषणा MT6359_GPIO_MODE1_CLR				0xd6
#घोषणा MT6359_GPIO_MODE2				0xd8
#घोषणा MT6359_GPIO_MODE2_SET				0xda
#घोषणा MT6359_GPIO_MODE2_CLR				0xdc
#घोषणा MT6359_GPIO_MODE3				0xde
#घोषणा MT6359_GPIO_MODE3_SET				0xe0
#घोषणा MT6359_GPIO_MODE3_CLR				0xe2
#घोषणा MT6359_GPIO_MODE4				0xe4
#घोषणा MT6359_GPIO_MODE4_SET				0xe6
#घोषणा MT6359_GPIO_MODE4_CLR				0xe8

#घोषणा MT6359_AUD_TOP_ID				0x2300
#घोषणा MT6359_AUD_TOP_REV0				0x2302
#घोषणा MT6359_AUD_TOP_DBI				0x2304
#घोषणा MT6359_AUD_TOP_DXI				0x2306
#घोषणा MT6359_AUD_TOP_CKPDN_TPM0			0x2308
#घोषणा MT6359_AUD_TOP_CKPDN_TPM1			0x230a
#घोषणा MT6359_AUD_TOP_CKPDN_CON0			0x230c
#घोषणा MT6359_AUD_TOP_CKPDN_CON0_SET			0x230e
#घोषणा MT6359_AUD_TOP_CKPDN_CON0_CLR			0x2310
#घोषणा MT6359_AUD_TOP_CKSEL_CON0			0x2312
#घोषणा MT6359_AUD_TOP_CKSEL_CON0_SET			0x2314
#घोषणा MT6359_AUD_TOP_CKSEL_CON0_CLR			0x2316
#घोषणा MT6359_AUD_TOP_CKTST_CON0			0x2318
#घोषणा MT6359_AUD_TOP_CLK_HWEN_CON0			0x231a
#घोषणा MT6359_AUD_TOP_CLK_HWEN_CON0_SET		0x231c
#घोषणा MT6359_AUD_TOP_CLK_HWEN_CON0_CLR		0x231e
#घोषणा MT6359_AUD_TOP_RST_CON0				0x2320
#घोषणा MT6359_AUD_TOP_RST_CON0_SET			0x2322
#घोषणा MT6359_AUD_TOP_RST_CON0_CLR			0x2324
#घोषणा MT6359_AUD_TOP_RST_BANK_CON0			0x2326
#घोषणा MT6359_AUD_TOP_INT_CON0				0x2328
#घोषणा MT6359_AUD_TOP_INT_CON0_SET			0x232a
#घोषणा MT6359_AUD_TOP_INT_CON0_CLR			0x232c
#घोषणा MT6359_AUD_TOP_INT_MASK_CON0			0x232e
#घोषणा MT6359_AUD_TOP_INT_MASK_CON0_SET		0x2330
#घोषणा MT6359_AUD_TOP_INT_MASK_CON0_CLR		0x2332
#घोषणा MT6359_AUD_TOP_INT_STATUS0			0x2334
#घोषणा MT6359_AUD_TOP_INT_RAW_STATUS0			0x2336
#घोषणा MT6359_AUD_TOP_INT_MISC_CON0			0x2338
#घोषणा MT6359_AUD_TOP_MON_CON0				0x233a
#घोषणा MT6359_AUDIO_DIG_DSN_ID				0x2380
#घोषणा MT6359_AUDIO_DIG_DSN_REV0			0x2382
#घोषणा MT6359_AUDIO_DIG_DSN_DBI			0x2384
#घोषणा MT6359_AUDIO_DIG_DSN_DXI			0x2386
#घोषणा MT6359_AFE_UL_DL_CON0				0x2388
#घोषणा MT6359_AFE_DL_SRC2_CON0_L			0x238a
#घोषणा MT6359_AFE_UL_SRC_CON0_H			0x238c
#घोषणा MT6359_AFE_UL_SRC_CON0_L			0x238e
#घोषणा MT6359_AFE_ADDA6_L_SRC_CON0_H			0x2390
#घोषणा MT6359_AFE_ADDA6_UL_SRC_CON0_L			0x2392
#घोषणा MT6359_AFE_TOP_CON0				0x2394
#घोषणा MT6359_AUDIO_TOP_CON0				0x2396
#घोषणा MT6359_AFE_MON_DEBUG0				0x2398
#घोषणा MT6359_AFUNC_AUD_CON0				0x239a
#घोषणा MT6359_AFUNC_AUD_CON1				0x239c
#घोषणा MT6359_AFUNC_AUD_CON2				0x239e
#घोषणा MT6359_AFUNC_AUD_CON3				0x23a0
#घोषणा MT6359_AFUNC_AUD_CON4				0x23a2
#घोषणा MT6359_AFUNC_AUD_CON5				0x23a4
#घोषणा MT6359_AFUNC_AUD_CON6				0x23a6
#घोषणा MT6359_AFUNC_AUD_CON7				0x23a8
#घोषणा MT6359_AFUNC_AUD_CON8				0x23aa
#घोषणा MT6359_AFUNC_AUD_CON9				0x23ac
#घोषणा MT6359_AFUNC_AUD_CON10				0x23ae
#घोषणा MT6359_AFUNC_AUD_CON11				0x23b0
#घोषणा MT6359_AFUNC_AUD_CON12				0x23b2
#घोषणा MT6359_AFUNC_AUD_MON0				0x23b4
#घोषणा MT6359_AFUNC_AUD_MON1				0x23b6
#घोषणा MT6359_AUDRC_TUNE_MON0				0x23b8
#घोषणा MT6359_AFE_ADDA_MTKAIF_FIFO_CFG0		0x23ba
#घोषणा MT6359_AFE_ADDA_MTKAIF_FIFO_LOG_MON1		0x23bc
#घोषणा MT6359_AFE_ADDA_MTKAIF_MON0			0x23be
#घोषणा MT6359_AFE_ADDA_MTKAIF_MON1			0x23c0
#घोषणा MT6359_AFE_ADDA_MTKAIF_MON2			0x23c2
#घोषणा MT6359_AFE_ADDA6_MTKAIF_MON3			0x23c4
#घोषणा MT6359_AFE_ADDA_MTKAIF_MON4			0x23c6
#घोषणा MT6359_AFE_ADDA_MTKAIF_MON5			0x23c8
#घोषणा MT6359_AFE_ADDA_MTKAIF_CFG0			0x23ca
#घोषणा MT6359_AFE_ADDA_MTKAIF_RX_CFG0			0x23cc
#घोषणा MT6359_AFE_ADDA_MTKAIF_RX_CFG1			0x23ce
#घोषणा MT6359_AFE_ADDA_MTKAIF_RX_CFG2			0x23d0
#घोषणा MT6359_AFE_ADDA_MTKAIF_RX_CFG3			0x23d2
#घोषणा MT6359_AFE_ADDA_MTKAIF_SYNCWORD_CFG0		0x23d4
#घोषणा MT6359_AFE_ADDA_MTKAIF_SYNCWORD_CFG1		0x23d6
#घोषणा MT6359_AFE_SGEN_CFG0				0x23d8
#घोषणा MT6359_AFE_SGEN_CFG1				0x23da
#घोषणा MT6359_AFE_ADC_ASYNC_FIFO_CFG			0x23dc
#घोषणा MT6359_AFE_ADC_ASYNC_FIFO_CFG1			0x23de
#घोषणा MT6359_AFE_DCCLK_CFG0				0x23e0
#घोषणा MT6359_AFE_DCCLK_CFG1				0x23e2
#घोषणा MT6359_AUDIO_DIG_CFG				0x23e4
#घोषणा MT6359_AUDIO_DIG_CFG1				0x23e6
#घोषणा MT6359_AFE_AUD_PAD_TOP				0x23e8
#घोषणा MT6359_AFE_AUD_PAD_TOP_MON			0x23ea
#घोषणा MT6359_AFE_AUD_PAD_TOP_MON1			0x23ec
#घोषणा MT6359_AFE_AUD_PAD_TOP_MON2			0x23ee
#घोषणा MT6359_AFE_DL_NLE_CFG				0x23f0
#घोषणा MT6359_AFE_DL_NLE_MON				0x23f2
#घोषणा MT6359_AFE_CG_EN_MON				0x23f4
#घोषणा MT6359_AFE_MIC_ARRAY_CFG			0x23f6
#घोषणा MT6359_AFE_CHOP_CFG0				0x23f8
#घोषणा MT6359_AFE_MTKAIF_MUX_CFG			0x23fa
#घोषणा MT6359_AUDIO_DIG_2ND_DSN_ID			0x2400
#घोषणा MT6359_AUDIO_DIG_2ND_DSN_REV0			0x2402
#घोषणा MT6359_AUDIO_DIG_2ND_DSN_DBI			0x2404
#घोषणा MT6359_AUDIO_DIG_2ND_DSN_DXI			0x2406
#घोषणा MT6359_AFE_PMIC_NEWIF_CFG3			0x2408
#घोषणा MT6359_AUDIO_DIG_3RD_DSN_ID			0x2480
#घोषणा MT6359_AUDIO_DIG_3RD_DSN_REV0			0x2482
#घोषणा MT6359_AUDIO_DIG_3RD_DSN_DBI			0x2484
#घोषणा MT6359_AUDIO_DIG_3RD_DSN_DXI			0x2486
#घोषणा MT6359_AFE_NCP_CFG0				0x24de
#घोषणा MT6359_AFE_NCP_CFG1				0x24e0
#घोषणा MT6359_AFE_NCP_CFG2				0x24e2
#घोषणा MT6359_AUDENC_DSN_ID				0x2500
#घोषणा MT6359_AUDENC_DSN_REV0				0x2502
#घोषणा MT6359_AUDENC_DSN_DBI				0x2504
#घोषणा MT6359_AUDENC_DSN_FPI				0x2506
#घोषणा MT6359_AUDENC_ANA_CON0				0x2508
#घोषणा MT6359_AUDENC_ANA_CON1				0x250a
#घोषणा MT6359_AUDENC_ANA_CON2				0x250c
#घोषणा MT6359_AUDENC_ANA_CON3				0x250e
#घोषणा MT6359_AUDENC_ANA_CON4				0x2510
#घोषणा MT6359_AUDENC_ANA_CON5				0x2512
#घोषणा MT6359_AUDENC_ANA_CON6				0x2514
#घोषणा MT6359_AUDENC_ANA_CON7				0x2516
#घोषणा MT6359_AUDENC_ANA_CON8				0x2518
#घोषणा MT6359_AUDENC_ANA_CON9				0x251a
#घोषणा MT6359_AUDENC_ANA_CON10				0x251c
#घोषणा MT6359_AUDENC_ANA_CON11				0x251e
#घोषणा MT6359_AUDENC_ANA_CON12				0x2520
#घोषणा MT6359_AUDENC_ANA_CON13				0x2522
#घोषणा MT6359_AUDENC_ANA_CON14				0x2524
#घोषणा MT6359_AUDENC_ANA_CON15				0x2526
#घोषणा MT6359_AUDENC_ANA_CON16				0x2528
#घोषणा MT6359_AUDENC_ANA_CON17				0x252a
#घोषणा MT6359_AUDENC_ANA_CON18				0x252c
#घोषणा MT6359_AUDENC_ANA_CON19				0x252e
#घोषणा MT6359_AUDENC_ANA_CON20				0x2530
#घोषणा MT6359_AUDENC_ANA_CON21				0x2532
#घोषणा MT6359_AUDENC_ANA_CON22				0x2534
#घोषणा MT6359_AUDENC_ANA_CON23				0x2536
#घोषणा MT6359_AUDDEC_DSN_ID				0x2580
#घोषणा MT6359_AUDDEC_DSN_REV0				0x2582
#घोषणा MT6359_AUDDEC_DSN_DBI				0x2584
#घोषणा MT6359_AUDDEC_DSN_FPI				0x2586
#घोषणा MT6359_AUDDEC_ANA_CON0				0x2588
#घोषणा MT6359_AUDDEC_ANA_CON1				0x258a
#घोषणा MT6359_AUDDEC_ANA_CON2				0x258c
#घोषणा MT6359_AUDDEC_ANA_CON3				0x258e
#घोषणा MT6359_AUDDEC_ANA_CON4				0x2590
#घोषणा MT6359_AUDDEC_ANA_CON5				0x2592
#घोषणा MT6359_AUDDEC_ANA_CON6				0x2594
#घोषणा MT6359_AUDDEC_ANA_CON7				0x2596
#घोषणा MT6359_AUDDEC_ANA_CON8				0x2598
#घोषणा MT6359_AUDDEC_ANA_CON9				0x259a
#घोषणा MT6359_AUDDEC_ANA_CON10				0x259c
#घोषणा MT6359_AUDDEC_ANA_CON11				0x259e
#घोषणा MT6359_AUDDEC_ANA_CON12				0x25a0
#घोषणा MT6359_AUDDEC_ANA_CON13				0x25a2
#घोषणा MT6359_AUDDEC_ANA_CON14				0x25a4
#घोषणा MT6359_AUDZCD_DSN_ID				0x2600
#घोषणा MT6359_AUDZCD_DSN_REV0				0x2602
#घोषणा MT6359_AUDZCD_DSN_DBI				0x2604
#घोषणा MT6359_AUDZCD_DSN_FPI				0x2606
#घोषणा MT6359_ZCD_CON0					0x2608
#घोषणा MT6359_ZCD_CON1					0x260a
#घोषणा MT6359_ZCD_CON2					0x260c
#घोषणा MT6359_ZCD_CON3					0x260e
#घोषणा MT6359_ZCD_CON4					0x2610
#घोषणा MT6359_ZCD_CON5					0x2612
#घोषणा MT6359_ACCDET_DSN_DIG_ID			0x2680
#घोषणा MT6359_ACCDET_DSN_DIG_REV0			0x2682
#घोषणा MT6359_ACCDET_DSN_DBI				0x2684
#घोषणा MT6359_ACCDET_DSN_FPI				0x2686
#घोषणा MT6359_ACCDET_CON0				0x2688
#घोषणा MT6359_ACCDET_CON1				0x268a
#घोषणा MT6359_ACCDET_CON2				0x268c
#घोषणा MT6359_ACCDET_CON3				0x268e
#घोषणा MT6359_ACCDET_CON4				0x2690
#घोषणा MT6359_ACCDET_CON5				0x2692
#घोषणा MT6359_ACCDET_CON6				0x2694
#घोषणा MT6359_ACCDET_CON7				0x2696
#घोषणा MT6359_ACCDET_CON8				0x2698
#घोषणा MT6359_ACCDET_CON9				0x269a
#घोषणा MT6359_ACCDET_CON10				0x269c
#घोषणा MT6359_ACCDET_CON11				0x269e
#घोषणा MT6359_ACCDET_CON12				0x26a0
#घोषणा MT6359_ACCDET_CON13				0x26a2
#घोषणा MT6359_ACCDET_CON14				0x26a4
#घोषणा MT6359_ACCDET_CON15				0x26a6
#घोषणा MT6359_ACCDET_CON16				0x26a8
#घोषणा MT6359_ACCDET_CON17				0x26aa
#घोषणा MT6359_ACCDET_CON18				0x26ac
#घोषणा MT6359_ACCDET_CON19				0x26ae
#घोषणा MT6359_ACCDET_CON20				0x26b0
#घोषणा MT6359_ACCDET_CON21				0x26b2
#घोषणा MT6359_ACCDET_CON22				0x26b4
#घोषणा MT6359_ACCDET_CON23				0x26b6
#घोषणा MT6359_ACCDET_CON24				0x26b8
#घोषणा MT6359_ACCDET_CON25				0x26ba
#घोषणा MT6359_ACCDET_CON26				0x26bc
#घोषणा MT6359_ACCDET_CON27				0x26be
#घोषणा MT6359_ACCDET_CON28				0x26c0
#घोषणा MT6359_ACCDET_CON29				0x26c2
#घोषणा MT6359_ACCDET_CON30				0x26c4
#घोषणा MT6359_ACCDET_CON31				0x26c6
#घोषणा MT6359_ACCDET_CON32				0x26c8
#घोषणा MT6359_ACCDET_CON33				0x26ca
#घोषणा MT6359_ACCDET_CON34				0x26cc
#घोषणा MT6359_ACCDET_CON35				0x26ce
#घोषणा MT6359_ACCDET_CON36				0x26d0
#घोषणा MT6359_ACCDET_CON37				0x26d2
#घोषणा MT6359_ACCDET_CON38				0x26d4
#घोषणा MT6359_ACCDET_CON39				0x26d6
#घोषणा MT6359_ACCDET_CON40				0x26d8
#घोषणा MT6359_MAX_REGISTER				MT6359_ZCD_CON5

/* dl bias */
#घोषणा DRBIAS_MASK 0x7
#घोषणा DRBIAS_HP_SFT (RG_AUDBIASADJ_0_VAUDP32_SFT + 0)
#घोषणा DRBIAS_HP_MASK_SFT (DRBIAS_MASK << DRBIAS_HP_SFT)
#घोषणा DRBIAS_HS_SFT (RG_AUDBIASADJ_0_VAUDP32_SFT + 3)
#घोषणा DRBIAS_HS_MASK_SFT (DRBIAS_MASK << DRBIAS_HS_SFT)
#घोषणा DRBIAS_LO_SFT (RG_AUDBIASADJ_0_VAUDP32_SFT + 6)
#घोषणा DRBIAS_LO_MASK_SFT (DRBIAS_MASK << DRBIAS_LO_SFT)
#घोषणा IBIAS_MASK 0x3
#घोषणा IBIAS_HP_SFT (RG_AUDBIASADJ_1_VAUDP32_SFT + 0)
#घोषणा IBIAS_HP_MASK_SFT (IBIAS_MASK << IBIAS_HP_SFT)
#घोषणा IBIAS_HS_SFT (RG_AUDBIASADJ_1_VAUDP32_SFT + 2)
#घोषणा IBIAS_HS_MASK_SFT (IBIAS_MASK << IBIAS_HS_SFT)
#घोषणा IBIAS_LO_SFT (RG_AUDBIASADJ_1_VAUDP32_SFT + 4)
#घोषणा IBIAS_LO_MASK_SFT (IBIAS_MASK << IBIAS_LO_SFT)
#घोषणा IBIAS_ZCD_SFT (RG_AUDBIASADJ_1_VAUDP32_SFT + 6)
#घोषणा IBIAS_ZCD_MASK_SFT (IBIAS_MASK << IBIAS_ZCD_SFT)

/* dl gain */
#घोषणा DL_GAIN_N_10DB_REG (DL_GAIN_N_10DB << 7 | DL_GAIN_N_10DB)
#घोषणा DL_GAIN_N_22DB_REG (DL_GAIN_N_22DB << 7 | DL_GAIN_N_22DB)
#घोषणा DL_GAIN_N_40DB_REG (DL_GAIN_N_40DB << 7 | DL_GAIN_N_40DB)
#घोषणा DL_GAIN_REG_MASK 0x0f9f

/* mic type mux */
#घोषणा MT_SOC_ENUM_EXT_ID(xname, xक्रमागत, xhandler_get, xhandler_put, id) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .device = id,\
	.info = snd_soc_info_क्रमागत_द्विगुन, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = (अचिन्हित दीर्घ)&(xक्रमागत) पूर्ण

क्रमागत अणु
	MT6359_MTKAIF_PROTOCOL_1 = 0,
	MT6359_MTKAIF_PROTOCOL_2,
	MT6359_MTKAIF_PROTOCOL_2_CLK_P2,
पूर्ण;

क्रमागत अणु
	MT6359_AIF_1 = 0,	/* dl: hp, rcv, hp+lo */
	MT6359_AIF_2,		/* dl: lo only */
	MT6359_AIF_NUM,
पूर्ण;

क्रमागत अणु
	AUDIO_ANALOG_VOLUME_HSOUTL,
	AUDIO_ANALOG_VOLUME_HSOUTR,
	AUDIO_ANALOG_VOLUME_HPOUTL,
	AUDIO_ANALOG_VOLUME_HPOUTR,
	AUDIO_ANALOG_VOLUME_LINEOUTL,
	AUDIO_ANALOG_VOLUME_LINEOUTR,
	AUDIO_ANALOG_VOLUME_MICAMP1,
	AUDIO_ANALOG_VOLUME_MICAMP2,
	AUDIO_ANALOG_VOLUME_MICAMP3,
	AUDIO_ANALOG_VOLUME_TYPE_MAX
पूर्ण;

क्रमागत अणु
	MUX_MIC_TYPE_0,	/* ain0, micbias 0 */
	MUX_MIC_TYPE_1,	/* ain1, micbias 1 */
	MUX_MIC_TYPE_2,	/* ain2/3, micbias 2 */
	MUX_PGA_L,
	MUX_PGA_R,
	MUX_PGA_3,
	MUX_HP,
	MUX_NUM,
पूर्ण;

क्रमागत अणु
	DEVICE_HP,
	DEVICE_LO,
	DEVICE_RCV,
	DEVICE_MIC1,
	DEVICE_MIC2,
	DEVICE_NUM
पूर्ण;

क्रमागत अणु
	HP_GAIN_CTL_ZCD = 0,
	HP_GAIN_CTL_NLE,
	HP_GAIN_CTL_NUM,
पूर्ण;

क्रमागत अणु
	HP_MUX_OPEN = 0,
	HP_MUX_HPSPK,
	HP_MUX_HP,
	HP_MUX_TEST_MODE,
	HP_MUX_HP_IMPEDANCE,
	HP_MUX_MASK = 0x7,
पूर्ण;

क्रमागत अणु
	RCV_MUX_OPEN = 0,
	RCV_MUX_MUTE,
	RCV_MUX_VOICE_PLAYBACK,
	RCV_MUX_TEST_MODE,
	RCV_MUX_MASK = 0x3,
पूर्ण;

क्रमागत अणु
	LO_MUX_OPEN = 0,
	LO_MUX_L_DAC,
	LO_MUX_3RD_DAC,
	LO_MUX_TEST_MODE,
	LO_MUX_MASK = 0x3,
पूर्ण;

/* Supply widget subseq */
क्रमागत अणु
	/* common */
	SUPPLY_SEQ_CLK_BUF,
	SUPPLY_SEQ_AUD_GLB,
	SUPPLY_SEQ_HP_PULL_DOWN,
	SUPPLY_SEQ_CLKSQ,
	SUPPLY_SEQ_ADC_CLKGEN,
	SUPPLY_SEQ_TOP_CK,
	SUPPLY_SEQ_TOP_CK_LAST,
	SUPPLY_SEQ_DCC_CLK,
	SUPPLY_SEQ_MIC_BIAS,
	SUPPLY_SEQ_DMIC,
	SUPPLY_SEQ_AUD_TOP,
	SUPPLY_SEQ_AUD_TOP_LAST,
	SUPPLY_SEQ_DL_SDM_FIFO_CLK,
	SUPPLY_SEQ_DL_SDM,
	SUPPLY_SEQ_DL_NCP,
	SUPPLY_SEQ_AFE,
	/* playback */
	SUPPLY_SEQ_DL_SRC,
	SUPPLY_SEQ_DL_ESD_RESIST,
	SUPPLY_SEQ_HP_DAMPING_OFF_RESET_CMFB,
	SUPPLY_SEQ_HP_MUTE,
	SUPPLY_SEQ_DL_LDO_REMOTE_SENSE,
	SUPPLY_SEQ_DL_LDO,
	SUPPLY_SEQ_DL_NV,
	SUPPLY_SEQ_HP_ANA_TRIM,
	SUPPLY_SEQ_DL_IBIST,
	/* capture */
	SUPPLY_SEQ_UL_PGA,
	SUPPLY_SEQ_UL_ADC,
	SUPPLY_SEQ_UL_MTKAIF,
	SUPPLY_SEQ_UL_SRC_DMIC,
	SUPPLY_SEQ_UL_SRC,
पूर्ण;

क्रमागत अणु
	CH_L = 0,
	CH_R,
	NUM_CH,
पूर्ण;

क्रमागत अणु
	DRBIAS_4UA = 0,
	DRBIAS_5UA,
	DRBIAS_6UA,
	DRBIAS_7UA,
	DRBIAS_8UA,
	DRBIAS_9UA,
	DRBIAS_10UA,
	DRBIAS_11UA,
पूर्ण;

क्रमागत अणु
	IBIAS_4UA = 0,
	IBIAS_5UA,
	IBIAS_6UA,
	IBIAS_7UA,
पूर्ण;

क्रमागत अणु
	IBIAS_ZCD_3UA = 0,
	IBIAS_ZCD_4UA,
	IBIAS_ZCD_5UA,
	IBIAS_ZCD_6UA,
पूर्ण;

क्रमागत अणु
	MIC_BIAS_1P7 = 0,
	MIC_BIAS_1P8,
	MIC_BIAS_1P9,
	MIC_BIAS_2P0,
	MIC_BIAS_2P1,
	MIC_BIAS_2P5,
	MIC_BIAS_2P6,
	MIC_BIAS_2P7,
पूर्ण;

/* dl pga gain */
क्रमागत अणु
	DL_GAIN_8DB = 0,
	DL_GAIN_0DB = 8,
	DL_GAIN_N_1DB = 9,
	DL_GAIN_N_10DB = 18,
	DL_GAIN_N_22DB = 30,
	DL_GAIN_N_40DB = 0x1f,
पूर्ण;

/* Mic Type MUX */
क्रमागत अणु
	MIC_TYPE_MUX_IDLE = 0,
	MIC_TYPE_MUX_ACC,
	MIC_TYPE_MUX_DMIC,
	MIC_TYPE_MUX_DCC,
	MIC_TYPE_MUX_DCC_ECM_DIFF,
	MIC_TYPE_MUX_DCC_ECM_SINGLE,
पूर्ण;

/* UL SRC MUX */
क्रमागत अणु
	UL_SRC_MUX_AMIC = 0,
	UL_SRC_MUX_DMIC,
पूर्ण;

/* MISO MUX */
क्रमागत अणु
	MISO_MUX_UL1_CH1 = 0,
	MISO_MUX_UL1_CH2,
	MISO_MUX_UL2_CH1,
	MISO_MUX_UL2_CH2,
पूर्ण;

/* DMIC MUX */
क्रमागत अणु
	DMIC_MUX_DMIC_DATA0 = 0,
	DMIC_MUX_DMIC_DATA1_L,
	DMIC_MUX_DMIC_DATA1_L_1,
	DMIC_MUX_DMIC_DATA1_R,
पूर्ण;

/* ADC L MUX */
क्रमागत अणु
	ADC_MUX_IDLE = 0,
	ADC_MUX_AIN0,
	ADC_MUX_PREAMPLIFIER,
	ADC_MUX_IDLE1,
पूर्ण;

/* PGA L MUX */
क्रमागत अणु
	PGA_L_MUX_NONE = 0,
	PGA_L_MUX_AIN0,
	PGA_L_MUX_AIN1,
पूर्ण;

/* PGA R MUX */
क्रमागत अणु
	PGA_R_MUX_NONE = 0,
	PGA_R_MUX_AIN2,
	PGA_R_MUX_AIN3,
	PGA_R_MUX_AIN0,
पूर्ण;

/* PGA 3 MUX */
क्रमागत अणु
	PGA_3_MUX_NONE = 0,
	PGA_3_MUX_AIN3,
	PGA_3_MUX_AIN2,
पूर्ण;

काष्ठा mt6359_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक dl_rate[MT6359_AIF_NUM];
	अचिन्हित पूर्णांक ul_rate[MT6359_AIF_NUM];
	पूर्णांक ana_gain[AUDIO_ANALOG_VOLUME_TYPE_MAX];
	अचिन्हित पूर्णांक mux_select[MUX_NUM];
	अचिन्हित पूर्णांक dmic_one_wire_mode;
	पूर्णांक dev_counter[DEVICE_NUM];
	पूर्णांक hp_gain_ctl;
	पूर्णांक hp_hअगरi_mode;
	पूर्णांक mtkaअगर_protocol;
पूर्ण;

#घोषणा CODEC_MT6359_NAME "mtk-codec-mt6359"
#घोषणा IS_DCC_BASE(type) ((type) == MIC_TYPE_MUX_DCC || \
			   (type) == MIC_TYPE_MUX_DCC_ECM_DIFF || \
			   (type) == MIC_TYPE_MUX_DCC_ECM_SINGLE)

व्योम mt6359_set_mtkaअगर_protocol(काष्ठा snd_soc_component *cmpnt,
				पूर्णांक mtkaअगर_protocol);
व्योम mt6359_mtkaअगर_calibration_enable(काष्ठा snd_soc_component *cmpnt);
व्योम mt6359_mtkaअगर_calibration_disable(काष्ठा snd_soc_component *cmpnt);
व्योम mt6359_set_mtkaअगर_calibration_phase(काष्ठा snd_soc_component *cmpnt,
					 पूर्णांक phase_1, पूर्णांक phase_2, पूर्णांक phase_3);

#पूर्ण_अगर/* end _MT6359_H_ */
