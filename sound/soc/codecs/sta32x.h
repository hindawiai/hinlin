<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Codec driver क्रम ST STA32x 2.1-channel high-efficiency digital audio प्रणाली
 *
 * Copyright: 2011 Raumfeld GmbH
 * Author: Johannes Stezenbach <js@sig21.net>
 *
 * based on code from:
 *	Wolfson Microelectronics PLC.
 *	Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */
#अगर_अघोषित _ASOC_STA_32X_H
#घोषणा _ASOC_STA_32X_H

/* STA326 रेजिस्टर addresses */

#घोषणा STA32X_REGISTER_COUNT	0x2d
#घोषणा STA32X_COEF_COUNT 62

#घोषणा STA32X_CONFA	0x00
#घोषणा STA32X_CONFB    0x01
#घोषणा STA32X_CONFC    0x02
#घोषणा STA32X_CONFD    0x03
#घोषणा STA32X_CONFE    0x04
#घोषणा STA32X_CONFF    0x05
#घोषणा STA32X_MMUTE    0x06
#घोषणा STA32X_MVOL     0x07
#घोषणा STA32X_C1VOL    0x08
#घोषणा STA32X_C2VOL    0x09
#घोषणा STA32X_C3VOL    0x0a
#घोषणा STA32X_AUTO1    0x0b
#घोषणा STA32X_AUTO2    0x0c
#घोषणा STA32X_AUTO3    0x0d
#घोषणा STA32X_C1CFG    0x0e
#घोषणा STA32X_C2CFG    0x0f
#घोषणा STA32X_C3CFG    0x10
#घोषणा STA32X_TONE     0x11
#घोषणा STA32X_L1AR     0x12
#घोषणा STA32X_L1ATRT   0x13
#घोषणा STA32X_L2AR     0x14
#घोषणा STA32X_L2ATRT   0x15
#घोषणा STA32X_CFADDR2  0x16
#घोषणा STA32X_B1CF1    0x17
#घोषणा STA32X_B1CF2    0x18
#घोषणा STA32X_B1CF3    0x19
#घोषणा STA32X_B2CF1    0x1a
#घोषणा STA32X_B2CF2    0x1b
#घोषणा STA32X_B2CF3    0x1c
#घोषणा STA32X_A1CF1    0x1d
#घोषणा STA32X_A1CF2    0x1e
#घोषणा STA32X_A1CF3    0x1f
#घोषणा STA32X_A2CF1    0x20
#घोषणा STA32X_A2CF2    0x21
#घोषणा STA32X_A2CF3    0x22
#घोषणा STA32X_B0CF1    0x23
#घोषणा STA32X_B0CF2    0x24
#घोषणा STA32X_B0CF3    0x25
#घोषणा STA32X_CFUD     0x26
#घोषणा STA32X_MPCC1    0x27
#घोषणा STA32X_MPCC2    0x28
/* Reserved 0x29 */
/* Reserved 0x2a */
#घोषणा STA32X_Reserved 0x2a
#घोषणा STA32X_FDRC1    0x2b
#घोषणा STA32X_FDRC2    0x2c
/* Reserved 0x2d */


/* STA326 रेजिस्टर field definitions */

/* 0x00 CONFA */
#घोषणा STA32X_CONFA_MCS_MASK	0x03
#घोषणा STA32X_CONFA_MCS_SHIFT	0
#घोषणा STA32X_CONFA_IR_MASK	0x18
#घोषणा STA32X_CONFA_IR_SHIFT	3
#घोषणा STA32X_CONFA_TWRB	0x20
#घोषणा STA32X_CONFA_TWAB	0x40
#घोषणा STA32X_CONFA_FDRB	0x80

/* 0x01 CONFB */
#घोषणा STA32X_CONFB_SAI_MASK	0x0f
#घोषणा STA32X_CONFB_SAI_SHIFT	0
#घोषणा STA32X_CONFB_SAIFB	0x10
#घोषणा STA32X_CONFB_DSCKE	0x20
#घोषणा STA32X_CONFB_C1IM	0x40
#घोषणा STA32X_CONFB_C2IM	0x80

/* 0x02 CONFC */
#घोषणा STA32X_CONFC_OM_MASK	0x03
#घोषणा STA32X_CONFC_OM_SHIFT	0
#घोषणा STA32X_CONFC_CSZ_MASK	0x7c
#घोषणा STA32X_CONFC_CSZ_SHIFT	2

/* 0x03 CONFD */
#घोषणा STA32X_CONFD_HPB	0x01
#घोषणा STA32X_CONFD_HPB_SHIFT	0
#घोषणा STA32X_CONFD_DEMP	0x02
#घोषणा STA32X_CONFD_DEMP_SHIFT	1
#घोषणा STA32X_CONFD_DSPB	0x04
#घोषणा STA32X_CONFD_DSPB_SHIFT	2
#घोषणा STA32X_CONFD_PSL	0x08
#घोषणा STA32X_CONFD_PSL_SHIFT	3
#घोषणा STA32X_CONFD_BQL	0x10
#घोषणा STA32X_CONFD_BQL_SHIFT	4
#घोषणा STA32X_CONFD_DRC	0x20
#घोषणा STA32X_CONFD_DRC_SHIFT	5
#घोषणा STA32X_CONFD_ZDE	0x40
#घोषणा STA32X_CONFD_ZDE_SHIFT	6
#घोषणा STA32X_CONFD_MME	0x80
#घोषणा STA32X_CONFD_MME_SHIFT	7

/* 0x04 CONFE */
#घोषणा STA32X_CONFE_MPCV	0x01
#घोषणा STA32X_CONFE_MPCV_SHIFT	0
#घोषणा STA32X_CONFE_MPC	0x02
#घोषणा STA32X_CONFE_MPC_SHIFT	1
#घोषणा STA32X_CONFE_AME	0x08
#घोषणा STA32X_CONFE_AME_SHIFT	3
#घोषणा STA32X_CONFE_PWMS	0x10
#घोषणा STA32X_CONFE_PWMS_SHIFT	4
#घोषणा STA32X_CONFE_ZCE	0x40
#घोषणा STA32X_CONFE_ZCE_SHIFT	6
#घोषणा STA32X_CONFE_SVE	0x80
#घोषणा STA32X_CONFE_SVE_SHIFT	7

/* 0x05 CONFF */
#घोषणा STA32X_CONFF_OCFG_MASK	0x03
#घोषणा STA32X_CONFF_OCFG_SHIFT	0
#घोषणा STA32X_CONFF_IDE	0x04
#घोषणा STA32X_CONFF_IDE_SHIFT	2
#घोषणा STA32X_CONFF_BCLE	0x08
#घोषणा STA32X_CONFF_ECLE	0x20
#घोषणा STA32X_CONFF_PWDN	0x40
#घोषणा STA32X_CONFF_EAPD	0x80

/* 0x06 MMUTE */
#घोषणा STA32X_MMUTE_MMUTE	0x01

/* 0x0b AUTO1 */
#घोषणा STA32X_AUTO1_AMEQ_MASK	0x03
#घोषणा STA32X_AUTO1_AMEQ_SHIFT	0
#घोषणा STA32X_AUTO1_AMV_MASK	0xc0
#घोषणा STA32X_AUTO1_AMV_SHIFT	2
#घोषणा STA32X_AUTO1_AMGC_MASK	0x30
#घोषणा STA32X_AUTO1_AMGC_SHIFT	4
#घोषणा STA32X_AUTO1_AMPS	0x80

/* 0x0c AUTO2 */
#घोषणा STA32X_AUTO2_AMAME	0x01
#घोषणा STA32X_AUTO2_AMAM_MASK	0x0e
#घोषणा STA32X_AUTO2_AMAM_SHIFT	1
#घोषणा STA32X_AUTO2_XO_MASK	0xf0
#घोषणा STA32X_AUTO2_XO_SHIFT	4

/* 0x0d AUTO3 */
#घोषणा STA32X_AUTO3_PEQ_MASK	0x1f
#घोषणा STA32X_AUTO3_PEQ_SHIFT	0

/* 0x0e 0x0f 0x10 CxCFG */
#घोषणा STA32X_CxCFG_TCB	0x01	/* only C1 and C2 */
#घोषणा STA32X_CxCFG_TCB_SHIFT	0
#घोषणा STA32X_CxCFG_EQBP	0x02	/* only C1 and C2 */
#घोषणा STA32X_CxCFG_EQBP_SHIFT	1
#घोषणा STA32X_CxCFG_VBP	0x03
#घोषणा STA32X_CxCFG_VBP_SHIFT	2
#घोषणा STA32X_CxCFG_BO		0x04
#घोषणा STA32X_CxCFG_LS_MASK	0x30
#घोषणा STA32X_CxCFG_LS_SHIFT	4
#घोषणा STA32X_CxCFG_OM_MASK	0xc0
#घोषणा STA32X_CxCFG_OM_SHIFT	6

/* 0x11 TONE */
#घोषणा STA32X_TONE_BTC_SHIFT	0
#घोषणा STA32X_TONE_TTC_SHIFT	4

/* 0x12 0x13 0x14 0x15 limiter attack/release */
#घोषणा STA32X_LxA_SHIFT	0
#घोषणा STA32X_LxR_SHIFT	4

/* 0x26 CFUD */
#घोषणा STA32X_CFUD_W1		0x01
#घोषणा STA32X_CFUD_WA		0x02
#घोषणा STA32X_CFUD_R1		0x04
#घोषणा STA32X_CFUD_RA		0x08


/* biquad filter coefficient table offsets */
#घोषणा STA32X_C1_BQ_BASE	0
#घोषणा STA32X_C2_BQ_BASE	20
#घोषणा STA32X_CH_BQ_NUM	4
#घोषणा STA32X_BQ_NUM_COEF	5
#घोषणा STA32X_XO_HP_BQ_BASE	40
#घोषणा STA32X_XO_LP_BQ_BASE	45
#घोषणा STA32X_C1_PRESCALE	50
#घोषणा STA32X_C2_PRESCALE	51
#घोषणा STA32X_C1_POSTSCALE	52
#घोषणा STA32X_C2_POSTSCALE	53
#घोषणा STA32X_C3_POSTSCALE	54
#घोषणा STA32X_TW_POSTSCALE	55
#घोषणा STA32X_C1_MIX1		56
#घोषणा STA32X_C1_MIX2		57
#घोषणा STA32X_C2_MIX1		58
#घोषणा STA32X_C2_MIX2		59
#घोषणा STA32X_C3_MIX1		60
#घोषणा STA32X_C3_MIX2		61

#पूर्ण_अगर /* _ASOC_STA_32X_H */
