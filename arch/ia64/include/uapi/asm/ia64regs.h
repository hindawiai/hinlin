<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2002,2003 Intel Corp.
 *      Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 *      Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 */

#अगर_अघोषित _ASM_IA64_IA64REGS_H
#घोषणा _ASM_IA64_IA64REGS_H

/*
 * Register Names क्रम getreg() and setreg().
 *
 * The "magic" numbers happen to match the values used by the Intel compiler's
 * getreg()/setreg() पूर्णांकrinsics.
 */

/* Special Registers */

#घोषणा _IA64_REG_IP		1016	/* getreg only */
#घोषणा _IA64_REG_PSR		1019
#घोषणा _IA64_REG_PSR_L		1019

/* General Integer Registers */

#घोषणा _IA64_REG_GP		1025	/* R1 */
#घोषणा _IA64_REG_R8		1032	/* R8 */
#घोषणा _IA64_REG_R9		1033	/* R9 */
#घोषणा _IA64_REG_SP		1036	/* R12 */
#घोषणा _IA64_REG_TP		1037	/* R13 */

/* Application Registers */

#घोषणा _IA64_REG_AR_KR0	3072
#घोषणा _IA64_REG_AR_KR1	3073
#घोषणा _IA64_REG_AR_KR2	3074
#घोषणा _IA64_REG_AR_KR3	3075
#घोषणा _IA64_REG_AR_KR4	3076
#घोषणा _IA64_REG_AR_KR5	3077
#घोषणा _IA64_REG_AR_KR6	3078
#घोषणा _IA64_REG_AR_KR7	3079
#घोषणा _IA64_REG_AR_RSC	3088
#घोषणा _IA64_REG_AR_BSP	3089
#घोषणा _IA64_REG_AR_BSPSTORE	3090
#घोषणा _IA64_REG_AR_RNAT	3091
#घोषणा _IA64_REG_AR_FCR	3093
#घोषणा _IA64_REG_AR_EFLAG	3096
#घोषणा _IA64_REG_AR_CSD	3097
#घोषणा _IA64_REG_AR_SSD	3098
#घोषणा _IA64_REG_AR_CFLAG	3099
#घोषणा _IA64_REG_AR_FSR	3100
#घोषणा _IA64_REG_AR_FIR	3101
#घोषणा _IA64_REG_AR_FDR	3102
#घोषणा _IA64_REG_AR_CCV	3104
#घोषणा _IA64_REG_AR_UNAT	3108
#घोषणा _IA64_REG_AR_FPSR	3112
#घोषणा _IA64_REG_AR_ITC	3116
#घोषणा _IA64_REG_AR_PFS	3136
#घोषणा _IA64_REG_AR_LC		3137
#घोषणा _IA64_REG_AR_EC		3138

/* Control Registers */

#घोषणा _IA64_REG_CR_DCR	4096
#घोषणा _IA64_REG_CR_ITM	4097
#घोषणा _IA64_REG_CR_IVA	4098
#घोषणा _IA64_REG_CR_PTA	4104
#घोषणा _IA64_REG_CR_IPSR	4112
#घोषणा _IA64_REG_CR_ISR	4113
#घोषणा _IA64_REG_CR_IIP	4115
#घोषणा _IA64_REG_CR_IFA	4116
#घोषणा _IA64_REG_CR_ITIR	4117
#घोषणा _IA64_REG_CR_IIPA	4118
#घोषणा _IA64_REG_CR_IFS	4119
#घोषणा _IA64_REG_CR_IIM	4120
#घोषणा _IA64_REG_CR_IHA	4121
#घोषणा _IA64_REG_CR_LID	4160
#घोषणा _IA64_REG_CR_IVR	4161	/* getreg only */
#घोषणा _IA64_REG_CR_TPR	4162
#घोषणा _IA64_REG_CR_EOI	4163
#घोषणा _IA64_REG_CR_IRR0	4164	/* getreg only */
#घोषणा _IA64_REG_CR_IRR1	4165	/* getreg only */
#घोषणा _IA64_REG_CR_IRR2	4166	/* getreg only */
#घोषणा _IA64_REG_CR_IRR3	4167	/* getreg only */
#घोषणा _IA64_REG_CR_ITV	4168
#घोषणा _IA64_REG_CR_PMV	4169
#घोषणा _IA64_REG_CR_CMCV	4170
#घोषणा _IA64_REG_CR_LRR0	4176
#घोषणा _IA64_REG_CR_LRR1	4177

/* Indirect Registers क्रम getindreg() and setindreg() */

#घोषणा _IA64_REG_INDR_CPUID	9000	/* getindreg only */
#घोषणा _IA64_REG_INDR_DBR	9001
#घोषणा _IA64_REG_INDR_IBR	9002
#घोषणा _IA64_REG_INDR_PKR	9003
#घोषणा _IA64_REG_INDR_PMC	9004
#घोषणा _IA64_REG_INDR_PMD	9005
#घोषणा _IA64_REG_INDR_RR	9006

#पूर्ण_अगर /* _ASM_IA64_IA64REGS_H */
