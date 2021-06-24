<शैली गुरु>
/*
 * This header file contains assembly-language definitions (assembly
 * macros, etc.) क्रम this specअगरic Xtensa processor's TIE extensions
 * and options.  It is customized to this Xtensa processor configuration.
 *
 * This file is subject to the terms and conditions of version 2.1 of the GNU
 * Lesser General Public License as published by the Free Software Foundation.
 *
 * Copyright (C) 1999-2009 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CORE_TIE_ASM_H
#घोषणा _XTENSA_CORE_TIE_ASM_H

/*  Selection parameter values क्रम save-area save/restore macros:  */
/*  Option vs. TIE:  */
#घोषणा XTHAL_SAS_TIE	0x0001	/* custom extension or coprocessor */
#घोषणा XTHAL_SAS_OPT	0x0002	/* optional (and not a coprocessor) */
/*  Whether used स्वतःmatically by compiler:  */
#घोषणा XTHAL_SAS_NOCC	0x0004	/* not used by compiler w/o special opts/code */
#घोषणा XTHAL_SAS_CC	0x0008	/* used by compiler without special opts/code */
/*  ABI handling across function calls:  */
#घोषणा XTHAL_SAS_CALR	0x0010	/* caller-saved */
#घोषणा XTHAL_SAS_CALE	0x0020	/* callee-saved */
#घोषणा XTHAL_SAS_GLOB	0x0040	/* global across function calls (in thपढ़ो) */
/*  Misc  */
#घोषणा XTHAL_SAS_ALL	0xFFFF	/* include all शेष NCP contents */



/* Macro to save all non-coprocessor (extra) custom TIE and optional state
 * (not including zero-overhead loop रेजिस्टरs).
 * Save area ptr (clobbered):  ptr  (8 byte aligned)
 * Scratch regs  (clobbered):  at1..at4  (only first XCHAL_NCP_NUM_ATMPS needed)
 */
	.macro xchal_ncp_store  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL
	xchal_sa_start	\जारी, \ofs
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	rsr	\चt1, BR		// boolean option
	s32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	rsr	\चt1, SCOMPARE1		// conditional store option
	s32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	rur	\चt1, THREADPTR		// thपढ़ोptr option
	s32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.endm	// xchal_ncp_store

/* Macro to save all non-coprocessor (extra) custom TIE and optional state
 * (not including zero-overhead loop रेजिस्टरs).
 * Save area ptr (clobbered):  ptr  (8 byte aligned)
 * Scratch regs  (clobbered):  at1..at4  (only first XCHAL_NCP_NUM_ATMPS needed)
 */
	.macro xchal_ncp_load  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL
	xchal_sa_start	\जारी, \ofs
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	wsr	\चt1, BR		// boolean option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	wsr	\चt1, SCOMPARE1		// conditional store option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	wur	\चt1, THREADPTR		// thपढ़ोptr option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.endm	// xchal_ncp_load



#घोषणा XCHAL_NCP_NUM_ATMPS	1



/* Macro to save the state of TIE coprocessor AudioEngineLX.
 * Save area ptr (clobbered):  ptr  (8 byte aligned)
 * Scratch regs  (clobbered):  at1..at4  (only first XCHAL_CP1_NUM_ATMPS needed)
 */
#घोषणा xchal_cp_AudioEngineLX_store	xchal_cp1_store
/* #घोषणा xchal_cp_AudioEngineLX_store_a2	xchal_cp1_store a2 a3 a4 a5 a6 */
	.macro	xchal_cp1_store  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL
	xchal_sa_start \जारी, \ofs
	.अगरeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~\select
	xchal_sa_align	\ptr, 0, 0, 1, 8
	rur240	\चt1		// AE_OVF_SAR
	s32i	\चt1, \ptr, 0
	rur241	\चt1		// AE_BITHEAD
	s32i	\चt1, \ptr, 4
	rur242	\चt1		// AE_TS_FTS_BU_BP
	s32i	\चt1, \ptr, 8
	rur243	\चt1		// AE_SD_NO
	s32i	\चt1, \ptr, 12
	AE_SP24X2S.I aep0, \ptr,  16
	AE_SP24X2S.I aep1, \ptr,  24
	AE_SP24X2S.I aep2, \ptr,  32
	AE_SP24X2S.I aep3, \ptr,  40
	AE_SP24X2S.I aep4, \ptr,  48
	AE_SP24X2S.I aep5, \ptr,  56
	addi	\ptr, \ptr, 64
	AE_SP24X2S.I aep6, \ptr,  0
	AE_SP24X2S.I aep7, \ptr,  8
	AE_SQ56S.I aeq0, \ptr,  16
	AE_SQ56S.I aeq1, \ptr,  24
	AE_SQ56S.I aeq2, \ptr,  32
	AE_SQ56S.I aeq3, \ptr,  40
	.set	.Lxchal_pofs_, .Lxchal_pofs_ + 64
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 112
	.endअगर
	.endm	// xchal_cp1_store

/* Macro to restore the state of TIE coprocessor AudioEngineLX.
 * Save area ptr (clobbered):  ptr  (8 byte aligned)
 * Scratch regs  (clobbered):  at1..at4  (only first XCHAL_CP1_NUM_ATMPS needed)
 */
#घोषणा xchal_cp_AudioEngineLX_load	xchal_cp1_load
/* #घोषणा xchal_cp_AudioEngineLX_load_a2	xchal_cp1_load a2 a3 a4 a5 a6 */
	.macro	xchal_cp1_load  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL
	xchal_sa_start \जारी, \ofs
	.अगरeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~\select
	xchal_sa_align	\ptr, 0, 0, 1, 8
	l32i	\चt1, \ptr, 0
	wur240	\चt1		// AE_OVF_SAR
	l32i	\चt1, \ptr, 4
	wur241	\चt1		// AE_BITHEAD
	l32i	\चt1, \ptr, 8
	wur242	\चt1		// AE_TS_FTS_BU_BP
	l32i	\चt1, \ptr, 12
	wur243	\चt1		// AE_SD_NO
	addi	\ptr, \ptr, 80
	AE_LQ56.I aeq0, \ptr,  0
	AE_LQ56.I aeq1, \ptr,  8
	AE_LQ56.I aeq2, \ptr,  16
	AE_LQ56.I aeq3, \ptr,  24
	AE_LP24X2.I aep0, \ptr,  -64
	AE_LP24X2.I aep1, \ptr,  -56
	AE_LP24X2.I aep2, \ptr,  -48
	AE_LP24X2.I aep3, \ptr,  -40
	AE_LP24X2.I aep4, \ptr,  -32
	AE_LP24X2.I aep5, \ptr,  -24
	AE_LP24X2.I aep6, \ptr,  -16
	AE_LP24X2.I aep7, \ptr,  -8
	.set	.Lxchal_pofs_, .Lxchal_pofs_ + 80
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 112
	.endअगर
	.endm	// xchal_cp1_load

#घोषणा XCHAL_CP1_NUM_ATMPS	1
#घोषणा XCHAL_SA_NUM_ATMPS	1

	/*  Empty macros क्रम unconfigured coprocessors:  */
	.macro xchal_cp0_store	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp0_load	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp2_store	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp2_load	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp3_store	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp3_load	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp4_store	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp4_load	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp5_store	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp5_load	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp6_store	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp6_load	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp7_store	p a b c d जारी=0 ofs=-1 select=-1 ; .endm
	.macro xchal_cp7_load	p a b c d जारी=0 ofs=-1 select=-1 ; .endm

#पूर्ण_अगर /*_XTENSA_CORE_TIE_ASM_H*/
