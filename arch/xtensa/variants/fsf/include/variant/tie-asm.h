<शैली गुरु>
/*
 * This header file contains assembly-language definitions (assembly
 * macros, etc.) क्रम this specअगरic Xtensa processor's TIE extensions
 * and options.  It is customized to this Xtensa processor configuration.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999-2008 Tensilica Inc.
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
 * Save area ptr (clobbered):  ptr  (1 byte aligned)
 * Scratch regs  (clobbered):  at1..at4  (only first XCHAL_NCP_NUM_ATMPS needed)
 */
	.macro xchal_ncp_store  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL
	xchal_sa_start	\जारी, \ofs
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	rur	\चt1, THREADPTR		// thपढ़ोptr option
	s32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.endm	// xchal_ncp_store

/* Macro to save all non-coprocessor (extra) custom TIE and optional state
 * (not including zero-overhead loop रेजिस्टरs).
 * Save area ptr (clobbered):  ptr  (1 byte aligned)
 * Scratch regs  (clobbered):  at1..at4  (only first XCHAL_NCP_NUM_ATMPS needed)
 */
	.macro xchal_ncp_load  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL
	xchal_sa_start	\जारी, \ofs
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~\select
	xchal_sa_align	\ptr, 0, 1024-4, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_ + 0
	wur	\चt1, THREADPTR		// thपढ़ोptr option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	.endm	// xchal_ncp_load



#घोषणा XCHAL_NCP_NUM_ATMPS	1


#घोषणा XCHAL_SA_NUM_ATMPS	1

#पूर्ण_अगर /*_XTENSA_CORE_TIE_ASM_H*/

