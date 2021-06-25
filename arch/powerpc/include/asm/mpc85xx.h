<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * MPC85xx cpu type detection
 *
 * Copyright 2011-2012 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __ASM_PPC_MPC85XX_H
#घोषणा __ASM_PPC_MPC85XX_H

#घोषणा SVR_REV(svr)	((svr) & 0xFF)		/* SOC design resision */
#घोषणा SVR_MAJ(svr)	(((svr) >>  4) & 0xF)	/* Major revision field*/
#घोषणा SVR_MIN(svr)	(((svr) >>  0) & 0xF)	/* Minor revision field*/

/* Some parts define SVR[0:23] as the SOC version */
#घोषणा SVR_SOC_VER(svr) (((svr) >> 8) & 0xFFF7FF)	/* SOC Version fields */

#घोषणा SVR_8533	0x803400
#घोषणा SVR_8535	0x803701
#घोषणा SVR_8536	0x803700
#घोषणा SVR_8540	0x803000
#घोषणा SVR_8541	0x807200
#घोषणा SVR_8543	0x803200
#घोषणा SVR_8544	0x803401
#घोषणा SVR_8545	0x803102
#घोषणा SVR_8547	0x803101
#घोषणा SVR_8548	0x803100
#घोषणा SVR_8555	0x807100
#घोषणा SVR_8560	0x807000
#घोषणा SVR_8567	0x807501
#घोषणा SVR_8568	0x807500
#घोषणा SVR_8569	0x808000
#घोषणा SVR_8572	0x80E000
#घोषणा SVR_P1010	0x80F100
#घोषणा SVR_P1011	0x80E500
#घोषणा SVR_P1012	0x80E501
#घोषणा SVR_P1013	0x80E700
#घोषणा SVR_P1014	0x80F101
#घोषणा SVR_P1017	0x80F700
#घोषणा SVR_P1020	0x80E400
#घोषणा SVR_P1021	0x80E401
#घोषणा SVR_P1022	0x80E600
#घोषणा SVR_P1023	0x80F600
#घोषणा SVR_P1024	0x80E402
#घोषणा SVR_P1025	0x80E403
#घोषणा SVR_P2010	0x80E300
#घोषणा SVR_P2020	0x80E200
#घोषणा SVR_P2040	0x821000
#घोषणा SVR_P2041	0x821001
#घोषणा SVR_P3041	0x821103
#घोषणा SVR_P4040	0x820100
#घोषणा SVR_P4080	0x820000
#घोषणा SVR_P5010	0x822100
#घोषणा SVR_P5020	0x822000
#घोषणा SVR_P5021	0X820500
#घोषणा SVR_P5040	0x820400
#घोषणा SVR_T4240	0x824000
#घोषणा SVR_T4120	0x824001
#घोषणा SVR_T4160	0x824100
#घोषणा SVR_T4080	0x824102
#घोषणा SVR_C291	0x850000
#घोषणा SVR_C292	0x850020
#घोषणा SVR_C293	0x850030
#घोषणा SVR_B4860	0X868000
#घोषणा SVR_G4860	0x868001
#घोषणा SVR_G4060	0x868003
#घोषणा SVR_B4440	0x868100
#घोषणा SVR_G4440	0x868101
#घोषणा SVR_B4420	0x868102
#घोषणा SVR_B4220	0x868103
#घोषणा SVR_T1040	0x852000
#घोषणा SVR_T1041	0x852001
#घोषणा SVR_T1042	0x852002
#घोषणा SVR_T1020	0x852100
#घोषणा SVR_T1021	0x852101
#घोषणा SVR_T1022	0x852102
#घोषणा SVR_T2080	0x853000
#घोषणा SVR_T2081	0x853100

#घोषणा SVR_8610	0x80A000
#घोषणा SVR_8641	0x809000
#घोषणा SVR_8641D	0x809001

#घोषणा SVR_9130	0x860001
#घोषणा SVR_9131	0x860000
#घोषणा SVR_9132	0x861000
#घोषणा SVR_9232	0x861400

#घोषणा SVR_Unknown	0xFFFFFF

#पूर्ण_अगर
