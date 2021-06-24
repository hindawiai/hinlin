<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Codec driver क्रम ST STA350 2.1-channel high-efficiency digital audio प्रणाली
 *
 * Copyright: 2011 Raumfeld GmbH
 * Author: Sven Bअक्रमau <info@bअक्रमau.biz>
 *
 * based on code from:
 *      Raumfeld GmbH
 *        Johannes Stezenbach <js@sig21.net>
 *	Wolfson Microelectronics PLC.
 *	  Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */
#अगर_अघोषित _ASOC_STA_350_H
#घोषणा _ASOC_STA_350_H

/* STA50 रेजिस्टर addresses */

#घोषणा STA350_REGISTER_COUNT	0x4D
#घोषणा STA350_COEF_COUNT 62

#घोषणा STA350_CONFA	0x00
#घोषणा STA350_CONFB    0x01
#घोषणा STA350_CONFC    0x02
#घोषणा STA350_CONFD    0x03
#घोषणा STA350_CONFE    0x04
#घोषणा STA350_CONFF    0x05
#घोषणा STA350_MMUTE    0x06
#घोषणा STA350_MVOL     0x07
#घोषणा STA350_C1VOL    0x08
#घोषणा STA350_C2VOL    0x09
#घोषणा STA350_C3VOL    0x0a
#घोषणा STA350_AUTO1    0x0b
#घोषणा STA350_AUTO2    0x0c
#घोषणा STA350_AUTO3    0x0d
#घोषणा STA350_C1CFG    0x0e
#घोषणा STA350_C2CFG    0x0f
#घोषणा STA350_C3CFG    0x10
#घोषणा STA350_TONE     0x11
#घोषणा STA350_L1AR     0x12
#घोषणा STA350_L1ATRT   0x13
#घोषणा STA350_L2AR     0x14
#घोषणा STA350_L2ATRT   0x15
#घोषणा STA350_CFADDR2  0x16
#घोषणा STA350_B1CF1    0x17
#घोषणा STA350_B1CF2    0x18
#घोषणा STA350_B1CF3    0x19
#घोषणा STA350_B2CF1    0x1a
#घोषणा STA350_B2CF2    0x1b
#घोषणा STA350_B2CF3    0x1c
#घोषणा STA350_A1CF1    0x1d
#घोषणा STA350_A1CF2    0x1e
#घोषणा STA350_A1CF3    0x1f
#घोषणा STA350_A2CF1    0x20
#घोषणा STA350_A2CF2    0x21
#घोषणा STA350_A2CF3    0x22
#घोषणा STA350_B0CF1    0x23
#घोषणा STA350_B0CF2    0x24
#घोषणा STA350_B0CF3    0x25
#घोषणा STA350_CFUD     0x26
#घोषणा STA350_MPCC1    0x27
#घोषणा STA350_MPCC2    0x28
#घोषणा STA350_DCC1     0x29
#घोषणा STA350_DCC2     0x2a
#घोषणा STA350_FDRC1    0x2b
#घोषणा STA350_FDRC2    0x2c
#घोषणा STA350_STATUS   0x2d
/* reserved: 0x2d - 0x30 */
#घोषणा STA350_EQCFG    0x31
#घोषणा STA350_EATH1    0x32
#घोषणा STA350_ERTH1    0x33
#घोषणा STA350_EATH2    0x34
#घोषणा STA350_ERTH2    0x35
#घोषणा STA350_CONFX    0x36
#घोषणा STA350_SVCA     0x37
#घोषणा STA350_SVCB     0x38
#घोषणा STA350_RMS0A    0x39
#घोषणा STA350_RMS0B    0x3a
#घोषणा STA350_RMS0C    0x3b
#घोषणा STA350_RMS1A    0x3c
#घोषणा STA350_RMS1B    0x3d
#घोषणा STA350_RMS1C    0x3e
#घोषणा STA350_EVOLRES  0x3f
/* reserved: 0x40 - 0x47 */
#घोषणा STA350_NSHAPE   0x48
#घोषणा STA350_CTXB4B1  0x49
#घोषणा STA350_CTXB7B5  0x4a
#घोषणा STA350_MISC1    0x4b
#घोषणा STA350_MISC2    0x4c

/* 0x00 CONFA */
#घोषणा STA350_CONFA_MCS_MASK	0x03
#घोषणा STA350_CONFA_MCS_SHIFT	0
#घोषणा STA350_CONFA_IR_MASK	0x18
#घोषणा STA350_CONFA_IR_SHIFT	3
#घोषणा STA350_CONFA_TWRB	BIT(5)
#घोषणा STA350_CONFA_TWAB	BIT(6)
#घोषणा STA350_CONFA_FDRB	BIT(7)

/* 0x01 CONFB */
#घोषणा STA350_CONFB_SAI_MASK	0x0f
#घोषणा STA350_CONFB_SAI_SHIFT	0
#घोषणा STA350_CONFB_SAIFB	BIT(4)
#घोषणा STA350_CONFB_DSCKE	BIT(5)
#घोषणा STA350_CONFB_C1IM	BIT(6)
#घोषणा STA350_CONFB_C2IM	BIT(7)

/* 0x02 CONFC */
#घोषणा STA350_CONFC_OM_MASK	0x03
#घोषणा STA350_CONFC_OM_SHIFT	0
#घोषणा STA350_CONFC_CSZ_MASK	0x3c
#घोषणा STA350_CONFC_CSZ_SHIFT	2
#घोषणा STA350_CONFC_OCRB	BIT(7)

/* 0x03 CONFD */
#घोषणा STA350_CONFD_HPB_SHIFT	0
#घोषणा STA350_CONFD_DEMP_SHIFT	1
#घोषणा STA350_CONFD_DSPB_SHIFT	2
#घोषणा STA350_CONFD_PSL_SHIFT	3
#घोषणा STA350_CONFD_BQL_SHIFT	4
#घोषणा STA350_CONFD_DRC_SHIFT	5
#घोषणा STA350_CONFD_ZDE_SHIFT	6
#घोषणा STA350_CONFD_SME_SHIFT	7

/* 0x04 CONFE */
#घोषणा STA350_CONFE_MPCV	BIT(0)
#घोषणा STA350_CONFE_MPCV_SHIFT	0
#घोषणा STA350_CONFE_MPC	BIT(1)
#घोषणा STA350_CONFE_MPC_SHIFT	1
#घोषणा STA350_CONFE_NSBW	BIT(2)
#घोषणा STA350_CONFE_NSBW_SHIFT	2
#घोषणा STA350_CONFE_AME	BIT(3)
#घोषणा STA350_CONFE_AME_SHIFT	3
#घोषणा STA350_CONFE_PWMS	BIT(4)
#घोषणा STA350_CONFE_PWMS_SHIFT	4
#घोषणा STA350_CONFE_DCCV	BIT(5)
#घोषणा STA350_CONFE_DCCV_SHIFT	5
#घोषणा STA350_CONFE_ZCE	BIT(6)
#घोषणा STA350_CONFE_ZCE_SHIFT	6
#घोषणा STA350_CONFE_SVE	BIT(7)
#घोषणा STA350_CONFE_SVE_SHIFT	7

/* 0x05 CONFF */
#घोषणा STA350_CONFF_OCFG_MASK	0x03
#घोषणा STA350_CONFF_OCFG_SHIFT	0
#घोषणा STA350_CONFF_IDE	BIT(2)
#घोषणा STA350_CONFF_BCLE	BIT(3)
#घोषणा STA350_CONFF_LDTE	BIT(4)
#घोषणा STA350_CONFF_ECLE	BIT(5)
#घोषणा STA350_CONFF_PWDN	BIT(6)
#घोषणा STA350_CONFF_EAPD	BIT(7)

/* 0x06 MMUTE */
#घोषणा STA350_MMUTE_MMUTE		0x01
#घोषणा STA350_MMUTE_MMUTE_SHIFT	0
#घोषणा STA350_MMUTE_C1M		0x02
#घोषणा STA350_MMUTE_C1M_SHIFT		1
#घोषणा STA350_MMUTE_C2M		0x04
#घोषणा STA350_MMUTE_C2M_SHIFT		2
#घोषणा STA350_MMUTE_C3M		0x08
#घोषणा STA350_MMUTE_C3M_SHIFT		3
#घोषणा STA350_MMUTE_LOC_MASK		0xC0
#घोषणा STA350_MMUTE_LOC_SHIFT		6

/* 0x0b AUTO1 */
#घोषणा STA350_AUTO1_AMGC_MASK	0x30
#घोषणा STA350_AUTO1_AMGC_SHIFT	4

/* 0x0c AUTO2 */
#घोषणा STA350_AUTO2_AMAME	0x01
#घोषणा STA350_AUTO2_AMAM_MASK	0x0e
#घोषणा STA350_AUTO2_AMAM_SHIFT	1
#घोषणा STA350_AUTO2_XO_MASK	0xf0
#घोषणा STA350_AUTO2_XO_SHIFT	4

/* 0x0d AUTO3 */
#घोषणा STA350_AUTO3_PEQ_MASK	0x1f
#घोषणा STA350_AUTO3_PEQ_SHIFT	0

/* 0x0e 0x0f 0x10 CxCFG */
#घोषणा STA350_CxCFG_TCB_SHIFT	0
#घोषणा STA350_CxCFG_EQBP_SHIFT	1
#घोषणा STA350_CxCFG_VBP_SHIFT	2
#घोषणा STA350_CxCFG_BO_SHIFT	3
#घोषणा STA350_CxCFG_LS_SHIFT	4
#घोषणा STA350_CxCFG_OM_MASK	0xc0
#घोषणा STA350_CxCFG_OM_SHIFT	6

/* 0x11 TONE */
#घोषणा STA350_TONE_BTC_SHIFT	0
#घोषणा STA350_TONE_TTC_SHIFT	4

/* 0x12 0x13 0x14 0x15 limiter attack/release */
#घोषणा STA350_LxA_SHIFT	0
#घोषणा STA350_LxR_SHIFT	4

/* 0x26 CFUD */
#घोषणा STA350_CFUD_W1		0x01
#घोषणा STA350_CFUD_WA		0x02
#घोषणा STA350_CFUD_R1		0x04
#घोषणा STA350_CFUD_RA		0x08


/* biquad filter coefficient table offsets */
#घोषणा STA350_C1_BQ_BASE	0
#घोषणा STA350_C2_BQ_BASE	20
#घोषणा STA350_CH_BQ_NUM	4
#घोषणा STA350_BQ_NUM_COEF	5
#घोषणा STA350_XO_HP_BQ_BASE	40
#घोषणा STA350_XO_LP_BQ_BASE	45
#घोषणा STA350_C1_PRESCALE	50
#घोषणा STA350_C2_PRESCALE	51
#घोषणा STA350_C1_POSTSCALE	52
#घोषणा STA350_C2_POSTSCALE	53
#घोषणा STA350_C3_POSTSCALE	54
#घोषणा STA350_TW_POSTSCALE	55
#घोषणा STA350_C1_MIX1		56
#घोषणा STA350_C1_MIX2		57
#घोषणा STA350_C2_MIX1		58
#घोषणा STA350_C2_MIX2		59
#घोषणा STA350_C3_MIX1		60
#घोषणा STA350_C3_MIX2		61

/* miscellaneous रेजिस्टर 1 */
#घोषणा STA350_MISC1_CPWMEN	BIT(2)
#घोषणा STA350_MISC1_BRIDGOFF	BIT(5)
#घोषणा STA350_MISC1_NSHHPEN	BIT(6)
#घोषणा STA350_MISC1_RPDNEN	BIT(7)

/* miscellaneous रेजिस्टर 2 */
#घोषणा STA350_MISC2_PNDLSL_MASK	0x1c
#घोषणा STA350_MISC2_PNDLSL_SHIFT	2

#पूर्ण_अगर /* _ASOC_STA_350_H */
