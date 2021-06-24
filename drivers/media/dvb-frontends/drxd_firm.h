<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drxd_firm.h
 *
 * Copyright (C) 2006-2007 Micronas
 */

#अगर_अघोषित _DRXD_FIRM_H_
#घोषणा _DRXD_FIRM_H_

#समावेश <linux/types.h>
#समावेश "drxd_map_firm.h"

#घोषणा VERSION_MAJOR 1
#घोषणा VERSION_MINOR 4
#घोषणा VERSION_PATCH 23

#घोषणा HI_TR_FUNC_ADDR HI_IF_RAM_USR_BEGIN__A

#घोषणा DRXD_MAX_RETRIES (1000)
#घोषणा HI_I2C_DELAY     84
#घोषणा HI_I2C_BRIDGE_DELAY   750

#घोषणा EQ_TD_TPS_PWR_UNKNOWN          0x00C0	/* Unknown configurations */
#घोषणा EQ_TD_TPS_PWR_QPSK             0x016a
#घोषणा EQ_TD_TPS_PWR_QAM16_ALPHAN     0x0195
#घोषणा EQ_TD_TPS_PWR_QAM16_ALPHA1     0x0195
#घोषणा EQ_TD_TPS_PWR_QAM16_ALPHA2     0x011E
#घोषणा EQ_TD_TPS_PWR_QAM16_ALPHA4     0x01CE
#घोषणा EQ_TD_TPS_PWR_QAM64_ALPHAN     0x019F
#घोषणा EQ_TD_TPS_PWR_QAM64_ALPHA1     0x019F
#घोषणा EQ_TD_TPS_PWR_QAM64_ALPHA2     0x00F8
#घोषणा EQ_TD_TPS_PWR_QAM64_ALPHA4     0x014D

#घोषणा DRXD_DEF_AG_PWD_CONSUMER 0x000E
#घोषणा DRXD_DEF_AG_PWD_PRO 0x0000
#घोषणा DRXD_DEF_AG_AGC_SIO 0x0000

#घोषणा DRXD_FE_CTRL_MAX 1023

#घोषणा DRXD_OSCDEV_DO_SCAN  (16)

#घोषणा DRXD_OSCDEV_DONT_SCAN  (0)

#घोषणा DRXD_OSCDEV_STEP  (275)

#घोषणा DRXD_SCAN_TIMEOUT    (650)

#घोषणा DRXD_BANDWIDTH_8MHZ_IN_HZ  (0x8B8249L)
#घोषणा DRXD_BANDWIDTH_7MHZ_IN_HZ  (0x7A1200L)
#घोषणा DRXD_BANDWIDTH_6MHZ_IN_HZ  (0x68A1B6L)

#घोषणा IRLEN_COARSE_8K       (10)
#घोषणा IRLEN_FINE_8K         (10)
#घोषणा IRLEN_COARSE_2K       (7)
#घोषणा IRLEN_FINE_2K         (9)
#घोषणा DIFF_INVALID          (511)
#घोषणा DIFF_TARGET           (4)
#घोषणा DIFF_MARGIN           (1)

बाह्य u8 DRXD_InitAtomicRead[];
बाह्य u8 DRXD_HiI2cPatch_1[];
बाह्य u8 DRXD_HiI2cPatch_3[];

बाह्य u8 DRXD_InitSC[];

बाह्य u8 DRXD_ResetCEFR[];
बाह्य u8 DRXD_InitFEA2_1[];
बाह्य u8 DRXD_InitFEA2_2[];
बाह्य u8 DRXD_InitCPA2[];
बाह्य u8 DRXD_InitCEA2[];
बाह्य u8 DRXD_InitEQA2[];
बाह्य u8 DRXD_InitECA2[];
बाह्य u8 DRXD_ResetECA2[];
बाह्य u8 DRXD_ResetECRAM[];

बाह्य u8 DRXD_A2_microcode[];
बाह्य u32 DRXD_A2_microcode_length;

बाह्य u8 DRXD_InitFEB1_1[];
बाह्य u8 DRXD_InitFEB1_2[];
बाह्य u8 DRXD_InitCPB1[];
बाह्य u8 DRXD_InitCEB1[];
बाह्य u8 DRXD_InitEQB1[];
बाह्य u8 DRXD_InitECB1[];

बाह्य u8 DRXD_InitDiversityFront[];
बाह्य u8 DRXD_InitDiversityEnd[];
बाह्य u8 DRXD_DisableDiversity[];
बाह्य u8 DRXD_StartDiversityFront[];
बाह्य u8 DRXD_StartDiversityEnd[];

बाह्य u8 DRXD_DiversityDelay8MHZ[];
बाह्य u8 DRXD_DiversityDelay6MHZ[];

बाह्य u8 DRXD_B1_microcode[];
बाह्य u32 DRXD_B1_microcode_length;

#पूर्ण_अगर
