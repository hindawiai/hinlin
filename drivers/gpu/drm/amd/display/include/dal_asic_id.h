<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_ASIC_ID_H__
#घोषणा __DAL_ASIC_ID_H__

/*
 * ASIC पूर्णांकernal revision ID
 */

/* DCE60 (based on si_id.h in GPUOpen-Tools CodeXL) */
#घोषणा SI_TAHITI_P_A0    0x01
#घोषणा SI_TAHITI_P_B0    0x05
#घोषणा SI_TAHITI_P_B1    0x06
#घोषणा SI_PITCAIRN_PM_A0 0x14
#घोषणा SI_PITCAIRN_PM_A1 0x15
#घोषणा SI_CAPEVERDE_M_A0 0x28
#घोषणा SI_CAPEVERDE_M_A1 0x29
#घोषणा SI_OLAND_M_A0     0x3C
#घोषणा SI_HAIन_अंक_V_A0    0x46

#घोषणा SI_UNKNOWN        0xFF

#घोषणा ASIC_REV_IS_TAHITI_P(rev) \
	((rev >= SI_TAHITI_P_A0) && (rev < SI_PITCAIRN_PM_A0))

#घोषणा ASIC_REV_IS_PITCAIRN_PM(rev) \
	((rev >= SI_PITCAIRN_PM_A0) && (rev < SI_CAPEVERDE_M_A0))

#घोषणा ASIC_REV_IS_CAPEVERDE_M(rev) \
	((rev >= SI_CAPEVERDE_M_A0) && (rev < SI_OLAND_M_A0))

#घोषणा ASIC_REV_IS_OLAND_M(rev) \
	((rev >= SI_OLAND_M_A0) && (rev < SI_HAIन_अंक_V_A0))

#घोषणा ASIC_REV_IS_HAIन_अंक_V(rev) \
	((rev >= SI_HAIन_अंक_V_A0) && (rev < SI_UNKNOWN))

/* DCE80 (based on ci_id.h in Perक्रमce) */
#घोषणा	CI_BONAIRE_M_A0 0x14
#घोषणा	CI_BONAIRE_M_A1	0x15
#घोषणा	CI_HAWAII_P_A0	0x28

#घोषणा CI_UNKNOWN	0xFF

#घोषणा ASIC_REV_IS_BONAIRE_M(rev) \
	((rev >= CI_BONAIRE_M_A0) && (rev < CI_HAWAII_P_A0))

#घोषणा ASIC_REV_IS_HAWAII_P(rev) \
	(rev >= CI_HAWAII_P_A0)

/* KV1 with Spectre GFX core, 8-8-1-2 (CU-Pix-Primitive-RB) */
#घोषणा KV_SPECTRE_A0 0x01

/* KV2 with Spooky GFX core, including करोwngraded from Spectre core,
 * 3-4-1-1 (CU-Pix-Primitive-RB) */
#घोषणा KV_SPOOKY_A0 0x41

/* KB with Kalindi GFX core, 2-4-1-1 (CU-Pix-Primitive-RB) */
#घोषणा KB_KALINDI_A0 0x81

/* KB with Kalindi GFX core, 2-4-1-1 (CU-Pix-Primitive-RB) */
#घोषणा KB_KALINDI_A1 0x82

/* BV with Kalindi GFX core, 2-4-1-1 (CU-Pix-Primitive-RB) */
#घोषणा BV_KALINDI_A2 0x85

/* ML with Godavari GFX core, 2-4-1-1 (CU-Pix-Primitive-RB) */
#घोषणा ML_GODAVARI_A0 0xA1

/* ML with Godavari GFX core, 2-4-1-1 (CU-Pix-Primitive-RB) */
#घोषणा ML_GODAVARI_A1 0xA2

#घोषणा KV_UNKNOWN 0xFF

#घोषणा ASIC_REV_IS_KALINDI(rev) \
	((rev >= KB_KALINDI_A0) && (rev < KV_UNKNOWN))

#घोषणा ASIC_REV_IS_BHAVANI(rev) \
	((rev >= BV_KALINDI_A2) && (rev < ML_GODAVARI_A0))

#घोषणा ASIC_REV_IS_GODAVARI(rev) \
	((rev >= ML_GODAVARI_A0) && (rev < KV_UNKNOWN))

/* VI Family */
/* DCE10 */
#घोषणा VI_TONGA_P_A0 20
#घोषणा VI_TONGA_P_A1 21
#घोषणा VI_FIJI_P_A0 60

/* DCE112 */
#घोषणा VI_POLARIS10_P_A0 80
#घोषणा VI_POLARIS11_M_A0 90
#घोषणा VI_POLARIS12_V_A0 100
#घोषणा VI_VEGAM_A0 110

#घोषणा VI_UNKNOWN 0xFF

#घोषणा ASIC_REV_IS_TONGA_P(eChipRev) ((eChipRev >= VI_TONGA_P_A0) && \
		(eChipRev < 40))
#घोषणा ASIC_REV_IS_FIJI_P(eChipRev) ((eChipRev >= VI_FIJI_P_A0) && \
		(eChipRev < 80))

#घोषणा ASIC_REV_IS_POLARIS10_P(eChipRev) ((eChipRev >= VI_POLARIS10_P_A0) && \
		(eChipRev < VI_POLARIS11_M_A0))
#घोषणा ASIC_REV_IS_POLARIS11_M(eChipRev) ((eChipRev >= VI_POLARIS11_M_A0) &&  \
		(eChipRev < VI_POLARIS12_V_A0))
#घोषणा ASIC_REV_IS_POLARIS12_V(eChipRev) ((eChipRev >= VI_POLARIS12_V_A0) && \
		(eChipRev < VI_VEGAM_A0))
#घोषणा ASIC_REV_IS_VEGAM(eChipRev) (eChipRev >= VI_VEGAM_A0)

/* DCE11 */
#घोषणा CZ_CARRIZO_A0 0x01

#घोषणा STONEY_A0 0x61
#घोषणा CZ_UNKNOWN 0xFF

#घोषणा ASIC_REV_IS_STONEY(rev) \
	((rev >= STONEY_A0) && (rev < CZ_UNKNOWN))

/* DCE12 */
#घोषणा AI_UNKNOWN 0xFF

#घोषणा AI_GREENLAND_P_A0 1
#घोषणा AI_GREENLAND_P_A1 2
#घोषणा AI_UNKNOWN 0xFF

#घोषणा AI_VEGA12_P_A0 20
#घोषणा AI_VEGA20_P_A0 40
#घोषणा ASICREV_IS_GREENLAND_M(eChipRev)  (eChipRev < AI_VEGA12_P_A0)
#घोषणा ASICREV_IS_GREENLAND_P(eChipRev)  (eChipRev < AI_VEGA12_P_A0)

#घोषणा ASICREV_IS_VEGA12_P(eChipRev) ((eChipRev >= AI_VEGA12_P_A0) && (eChipRev < AI_VEGA20_P_A0))
#घोषणा ASICREV_IS_VEGA20_P(eChipRev) ((eChipRev >= AI_VEGA20_P_A0) && (eChipRev < AI_UNKNOWN))

/* DCN1_0 */
#घोषणा INTERNAL_REV_RAVEN_A0             0x00    /* First spin of Raven */
#घोषणा RAVEN_A0 0x01
#घोषणा RAVEN_B0 0x21
#घोषणा PICASSO_A0 0x41
/* DCN1_01 */
#घोषणा RAVEN2_A0 0x81
#घोषणा RAVEN1_F0 0xF0
#घोषणा RAVEN_UNKNOWN 0xFF
#घोषणा RENOIR_A0 0x91
#अगर_अघोषित ASICREV_IS_RAVEN
#घोषणा ASICREV_IS_RAVEN(eChipRev) ((eChipRev >= RAVEN_A0) && eChipRev < RAVEN_UNKNOWN)
#पूर्ण_अगर
#घोषणा PRID_DALI_DE 0xDE
#घोषणा PRID_DALI_DF 0xDF
#घोषणा PRID_DALI_E3 0xE3
#घोषणा PRID_DALI_E4 0xE4

#घोषणा PRID_POLLOCK_94 0x94
#घोषणा PRID_POLLOCK_95 0x95
#घोषणा PRID_POLLOCK_E9 0xE9
#घोषणा PRID_POLLOCK_EA 0xEA
#घोषणा PRID_POLLOCK_EB 0xEB

#घोषणा ASICREV_IS_PICASSO(eChipRev) ((eChipRev >= PICASSO_A0) && (eChipRev < RAVEN2_A0))
#अगर_अघोषित ASICREV_IS_RAVEN2
#घोषणा ASICREV_IS_RAVEN2(eChipRev) ((eChipRev >= RAVEN2_A0) && (eChipRev < RENOIR_A0))
#पूर्ण_अगर
#घोषणा ASICREV_IS_RV1_F0(eChipRev) ((eChipRev >= RAVEN1_F0) && (eChipRev < RAVEN_UNKNOWN))

#घोषणा FAMILY_RV 142 /* DCN 1*/


#घोषणा FAMILY_NV 143 /* DCN 2*/

क्रमागत अणु
	NV_NAVI10_P_A0      = 1,
	NV_NAVI12_P_A0      = 10,
	NV_NAVI14_M_A0      = 20,
	NV_SIENNA_CICHLID_P_A0      = 40,
	NV_DIMGREY_CAVEFISH_P_A0      = 60,
	NV_UNKNOWN          = 0xFF
पूर्ण;

#घोषणा ASICREV_IS_NAVI10_P(eChipRev)        (eChipRev < NV_NAVI12_P_A0)
#घोषणा ASICREV_IS_NAVI12_P(eChipRev)        ((eChipRev >= NV_NAVI12_P_A0) && (eChipRev < NV_NAVI14_M_A0))
#घोषणा ASICREV_IS_NAVI14_M(eChipRev)        ((eChipRev >= NV_NAVI14_M_A0) && (eChipRev < NV_UNKNOWN))
#घोषणा ASICREV_IS_RENOIR(eChipRev) ((eChipRev >= RENOIR_A0) && (eChipRev < RAVEN1_F0))
#घोषणा ASICREV_IS_SIENNA_CICHLID_P(eChipRev)        ((eChipRev >= NV_SIENNA_CICHLID_P_A0) && (eChipRev < NV_DIMGREY_CAVEFISH_P_A0))
#घोषणा ASICREV_IS_DIMGREY_CAVEFISH_P(eChipRev)        ((eChipRev >= NV_DIMGREY_CAVEFISH_P_A0) && (eChipRev < NV_UNKNOWN))
#घोषणा GREEN_SARDINE_A0 0xA1
#अगर_अघोषित ASICREV_IS_GREEN_SARDINE
#घोषणा ASICREV_IS_GREEN_SARDINE(eChipRev) ((eChipRev >= GREEN_SARDINE_A0) && (eChipRev < 0xFF))
#पूर्ण_अगर
#घोषणा FAMILY_VGH 144
#घोषणा DEVICE_ID_VGH_163F 0x163F
#घोषणा VANGOGH_A0 0x01
#घोषणा VANGOGH_UNKNOWN 0xFF

#अगर_अघोषित ASICREV_IS_VANGOGH
#घोषणा ASICREV_IS_VANGOGH(eChipRev) ((eChipRev >= VANGOGH_A0) && (eChipRev < VANGOGH_UNKNOWN))
#पूर्ण_अगर
#घोषणा GREEN_SARDINE_A0 0xA1
#अगर_अघोषित ASICREV_IS_GREEN_SARDINE
#घोषणा ASICREV_IS_GREEN_SARDINE(eChipRev) ((eChipRev >= GREEN_SARDINE_A0) && (eChipRev < 0xFF))
#पूर्ण_अगर

/*
 * ASIC chip ID
 */

/* DCE60 */
#घोषणा DEVICE_ID_SI_TAHITI_P_6780 0x6780
#घोषणा DEVICE_ID_SI_PITCAIRN_PM_6800 0x6800
#घोषणा DEVICE_ID_SI_PITCAIRN_PM_6808 0x6808
#घोषणा DEVICE_ID_SI_CAPEVERDE_M_6820 0x6820
#घोषणा DEVICE_ID_SI_CAPEVERDE_M_6828 0x6828
#घोषणा DEVICE_ID_SI_OLAND_M_6600 0x6600
#घोषणा DEVICE_ID_SI_OLAND_M_6608 0x6608
#घोषणा DEVICE_ID_SI_HAIन_अंक_V_6660 0x6660

/* DCE80 */
#घोषणा DEVICE_ID_KALINDI_9834 0x9834
#घोषणा DEVICE_ID_TEMASH_9839 0x9839
#घोषणा DEVICE_ID_TEMASH_983D 0x983D

/* RENOIR */
#घोषणा DEVICE_ID_RENOIR_1636 0x1636

/* Asic Family IDs क्रम dअगरferent asic family. */
#घोषणा FAMILY_SI 110 /* Southern Islands: Tahiti (P), Pitcairn (PM), Cape Verde (M), Oland (M), Hainan (V) */
#घोषणा FAMILY_CI 120 /* Sea Islands: Hawaii (P), Bonaire (M) */
#घोषणा FAMILY_KV 125 /* Fusion => Kaveri: Spectre, Spooky; Kabini: Kalindi */
#घोषणा FAMILY_VI 130 /* Volcanic Islands: Iceland (V), Tonga (M) */
#घोषणा FAMILY_CZ 135 /* Carrizo */

#घोषणा FAMILY_AI 141

#घोषणा	FAMILY_UNKNOWN 0xFF



#पूर्ण_अगर /* __DAL_ASIC_ID_H__ */
