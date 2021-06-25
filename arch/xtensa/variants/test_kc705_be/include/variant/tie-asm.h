<शैली गुरु>
/* 
 * tie-यंत्र.h -- compile-समय HAL assembler definitions dependent on CORE & TIE
 *
 *  NOTE:  This header file is not meant to be included directly.
 */

/* This header file contains assembly-language definitions (assembly
   macros, etc.) क्रम this specअगरic Xtensa processor's TIE extensions
   and options.  It is customized to this Xtensa processor configuration.

   Copyright (c) 1999-2015 Cadence Design Systems Inc.

   Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
   a copy of this software and associated करोcumentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modअगरy, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to करो so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#अगर_अघोषित _XTENSA_CORE_TIE_ASM_H
#घोषणा _XTENSA_CORE_TIE_ASM_H

/*  Selection parameter values क्रम save-area save/restore macros:  */
/*  Option vs. TIE:  */
#घोषणा XTHAL_SAS_TIE	0x0001	/* custom extension or coprocessor */
#घोषणा XTHAL_SAS_OPT	0x0002	/* optional (and not a coprocessor) */
#घोषणा XTHAL_SAS_ANYOT	0x0003	/* both of the above */
/*  Whether used स्वतःmatically by compiler:  */
#घोषणा XTHAL_SAS_NOCC	0x0004	/* not used by compiler w/o special opts/code */
#घोषणा XTHAL_SAS_CC	0x0008	/* used by compiler without special opts/code */
#घोषणा XTHAL_SAS_ANYCC	0x000C	/* both of the above */
/*  ABI handling across function calls:  */
#घोषणा XTHAL_SAS_CALR	0x0010	/* caller-saved */
#घोषणा XTHAL_SAS_CALE	0x0020	/* callee-saved */
#घोषणा XTHAL_SAS_GLOB	0x0040	/* global across function calls (in thपढ़ो) */
#घोषणा XTHAL_SAS_ANYABI	0x0070	/* all of the above three */
/*  Misc  */
#घोषणा XTHAL_SAS_ALL	0xFFFF	/* include all शेष NCP contents */
#घोषणा XTHAL_SAS3(optie,ccuse,abi)	( ((optie) & XTHAL_SAS_ANYOT)  \
					| ((ccuse) & XTHAL_SAS_ANYCC)  \
					| ((abi)   & XTHAL_SAS_ANYABI) )


    /*
      *  Macro to store all non-coprocessor (extra) custom TIE and optional state
      *  (not including zero-overhead loop रेजिस्टरs).
      *  Required parameters:
      *      ptr         Save area poपूर्णांकer address रेजिस्टर (clobbered)
      *                  (रेजिस्टर must contain a 4 byte aligned address).
      *      at1..at4    Four temporary address रेजिस्टरs (first XCHAL_NCP_NUM_ATMPS
      *                  रेजिस्टरs are clobbered, the reमुख्यing are unused).
      *  Optional parameters:
      *      जारी    If macro invoked as part of a larger store sequence, set to 1
      *                  अगर this is not the first in the sequence.  Defaults to 0.
      *      ofs         Offset from start of larger sequence (from value of first ptr
      *                  in sequence) at which to store.  Defaults to next available space
      *                  (or 0 अगर <जारी> is 0).
      *      select      Select what category(ies) of रेजिस्टरs to store, as a biपंचांगask
      *                  (see XTHAL_SAS_xxx स्थिरants).  Defaults to all रेजिस्टरs.
      *      alloc       Select what category(ies) of रेजिस्टरs to allocate; अगर any
      *                  category is selected here that is not in <select>, space क्रम
      *                  the corresponding रेजिस्टरs is skipped without करोing any store.
      */
    .macro xchal_ncp_store  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start	\जारी, \ofs
	// Optional global रेजिस्टरs used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\select)
	xchal_sa_align	\ptr, 0, 1020, 4, 4
	rur.THREADPTR	\चt1		// thपढ़ोptr option
	s32i	\चt1, \ptr, .Lxchal_ofs_+0
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1020, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	// Optional caller-saved रेजिस्टरs used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	rsr.ACCLO	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+0
	rsr.ACCHI	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.endअगर
	// Optional caller-saved रेजिस्टरs not used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 1000, 4, 4
	rsr.BR	\चt1		// boolean option
	s32i	\चt1, \ptr, .Lxchal_ofs_+0
	rsr.SCOMPARE1	\चt1		// conditional store option
	s32i	\चt1, \ptr, .Lxchal_ofs_+4
	rsr.M0	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+8
	rsr.M1	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+12
	rsr.M2	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+16
	rsr.M3	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+20
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1000, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.endअगर
    .endm	// xchal_ncp_store

    /*
      *  Macro to load all non-coprocessor (extra) custom TIE and optional state
      *  (not including zero-overhead loop रेजिस्टरs).
      *  Required parameters:
      *      ptr         Save area poपूर्णांकer address रेजिस्टर (clobbered)
      *                  (रेजिस्टर must contain a 4 byte aligned address).
      *      at1..at4    Four temporary address रेजिस्टरs (first XCHAL_NCP_NUM_ATMPS
      *                  रेजिस्टरs are clobbered, the reमुख्यing are unused).
      *  Optional parameters:
      *      जारी    If macro invoked as part of a larger load sequence, set to 1
      *                  अगर this is not the first in the sequence.  Defaults to 0.
      *      ofs         Offset from start of larger sequence (from value of first ptr
      *                  in sequence) at which to load.  Defaults to next available space
      *                  (or 0 अगर <जारी> is 0).
      *      select      Select what category(ies) of रेजिस्टरs to load, as a biपंचांगask
      *                  (see XTHAL_SAS_xxx स्थिरants).  Defaults to all रेजिस्टरs.
      *      alloc       Select what category(ies) of रेजिस्टरs to allocate; अगर any
      *                  category is selected here that is not in <select>, space क्रम
      *                  the corresponding रेजिस्टरs is skipped without करोing any load.
      */
    .macro xchal_ncp_load  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start	\जारी, \ofs
	// Optional global रेजिस्टरs used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\select)
	xchal_sa_align	\ptr, 0, 1020, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_+0
	wur.THREADPTR	\चt1		// thपढ़ोptr option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_GLOB) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1020, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 4
	.endअगर
	// Optional caller-saved रेजिस्टरs used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_+0
	wsr.ACCLO	\चt1		// MAC16 option
	l32i	\चt1, \ptr, .Lxchal_ofs_+4
	wsr.ACCHI	\चt1		// MAC16 option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_CC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1016, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 8
	.endअगर
	// Optional caller-saved रेजिस्टरs not used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 1000, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_+0
	wsr.BR	\चt1		// boolean option
	l32i	\चt1, \ptr, .Lxchal_ofs_+4
	wsr.SCOMPARE1	\चt1		// conditional store option
	l32i	\चt1, \ptr, .Lxchal_ofs_+8
	wsr.M0	\चt1		// MAC16 option
	l32i	\चt1, \ptr, .Lxchal_ofs_+12
	wsr.M1	\चt1		// MAC16 option
	l32i	\चt1, \ptr, .Lxchal_ofs_+16
	wsr.M2	\चt1		// MAC16 option
	l32i	\चt1, \ptr, .Lxchal_ofs_+20
	wsr.M3	\चt1		// MAC16 option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1000, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 24
	.endअगर
    .endm	// xchal_ncp_load


#घोषणा XCHAL_NCP_NUM_ATMPS	1

    /* 
     *  Macro to store the state of TIE coprocessor AudioEngineLX.
     *  Required parameters:
     *      ptr         Save area poपूर्णांकer address रेजिस्टर (clobbered)
     *                  (रेजिस्टर must contain a 8 byte aligned address).
     *      at1..at4    Four temporary address रेजिस्टरs (first XCHAL_CP1_NUM_ATMPS
     *                  रेजिस्टरs are clobbered, the reमुख्यing are unused).
     *  Optional parameters are the same as क्रम xchal_ncp_store.
     */
#घोषणा xchal_cp_AudioEngineLX_store	xchal_cp1_store
    .macro	xchal_cp1_store  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start \जारी, \ofs
	// Custom caller-saved रेजिस्टरs not used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 0, 8, 8
	rur.AE_OVF_SAR	\चt1		// ureg 240
	s32i	\चt1, \ptr, .Lxchal_ofs_+0
	rur.AE_BITHEAD	\चt1		// ureg 241
	s32i	\चt1, \ptr, .Lxchal_ofs_+4
	rur.AE_TS_FTS_BU_BP	\चt1		// ureg 242
	s32i	\चt1, \ptr, .Lxchal_ofs_+8
	rur.AE_SD_NO	\चt1		// ureg 243
	s32i	\चt1, \ptr, .Lxchal_ofs_+12
	rur.AE_CBEGIN0	\चt1		// ureg 246
	s32i	\चt1, \ptr, .Lxchal_ofs_+16
	rur.AE_CEND0	\चt1		// ureg 247
	s32i	\चt1, \ptr, .Lxchal_ofs_+20
	ae_sp24x2s.i	aep0, \ptr, .Lxchal_ofs_+24
	ae_sp24x2s.i	aep1, \ptr, .Lxchal_ofs_+32
	ae_sp24x2s.i	aep2, \ptr, .Lxchal_ofs_+40
	ae_sp24x2s.i	aep3, \ptr, .Lxchal_ofs_+48
	ae_sp24x2s.i	aep4, \ptr, .Lxchal_ofs_+56
	addi	\ptr, \ptr, 64
	ae_sp24x2s.i	aep5, \ptr, .Lxchal_ofs_+0
	ae_sp24x2s.i	aep6, \ptr, .Lxchal_ofs_+8
	ae_sp24x2s.i	aep7, \ptr, .Lxchal_ofs_+16
	ae_sq56s.i	aeq0, \ptr, .Lxchal_ofs_+24
	ae_sq56s.i	aeq1, \ptr, .Lxchal_ofs_+32
	ae_sq56s.i	aeq2, \ptr, .Lxchal_ofs_+40
	ae_sq56s.i	aeq3, \ptr, .Lxchal_ofs_+48
	.set	.Lxchal_pofs_, .Lxchal_pofs_ + 64
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 56
	.अन्यथाअगर ((XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 0, 8, 8
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 120
	.endअगर
    .endm	// xchal_cp1_store

    /* 
     *  Macro to load the state of TIE coprocessor AudioEngineLX.
     *  Required parameters:
     *      ptr         Save area poपूर्णांकer address रेजिस्टर (clobbered)
     *                  (रेजिस्टर must contain a 8 byte aligned address).
     *      at1..at4    Four temporary address रेजिस्टरs (first XCHAL_CP1_NUM_ATMPS
     *                  रेजिस्टरs are clobbered, the reमुख्यing are unused).
     *  Optional parameters are the same as क्रम xchal_ncp_load.
     */
#घोषणा xchal_cp_AudioEngineLX_load	xchal_cp1_load
    .macro	xchal_cp1_load  ptr at1 at2 at3 at4  जारी=0 ofs=-1 select=XTHAL_SAS_ALL alloc=0
	xchal_sa_start \जारी, \ofs
	// Custom caller-saved रेजिस्टरs not used by शेष by the compiler:
	.अगरeq (XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\select)
	xchal_sa_align	\ptr, 0, 0, 8, 8
	l32i	\चt1, \ptr, .Lxchal_ofs_+0
	wur.AE_OVF_SAR	\चt1		// ureg 240
	l32i	\चt1, \ptr, .Lxchal_ofs_+4
	wur.AE_BITHEAD	\चt1		// ureg 241
	l32i	\चt1, \ptr, .Lxchal_ofs_+8
	wur.AE_TS_FTS_BU_BP	\चt1		// ureg 242
	l32i	\चt1, \ptr, .Lxchal_ofs_+12
	wur.AE_SD_NO	\चt1		// ureg 243
	l32i	\चt1, \ptr, .Lxchal_ofs_+16
	wur.AE_CBEGIN0	\चt1		// ureg 246
	l32i	\चt1, \ptr, .Lxchal_ofs_+20
	wur.AE_CEND0	\चt1		// ureg 247
	ae_lp24x2.i	aep0, \ptr, .Lxchal_ofs_+24
	ae_lp24x2.i	aep1, \ptr, .Lxchal_ofs_+32
	ae_lp24x2.i	aep2, \ptr, .Lxchal_ofs_+40
	ae_lp24x2.i	aep3, \ptr, .Lxchal_ofs_+48
	ae_lp24x2.i	aep4, \ptr, .Lxchal_ofs_+56
	addi	\ptr, \ptr, 64
	ae_lp24x2.i	aep5, \ptr, .Lxchal_ofs_+0
	ae_lp24x2.i	aep6, \ptr, .Lxchal_ofs_+8
	ae_lp24x2.i	aep7, \ptr, .Lxchal_ofs_+16
	addi	\ptr, \ptr, 24
	ae_lq56.i	aeq0, \ptr, .Lxchal_ofs_+0
	ae_lq56.i	aeq1, \ptr, .Lxchal_ofs_+8
	ae_lq56.i	aeq2, \ptr, .Lxchal_ofs_+16
	ae_lq56.i	aeq3, \ptr, .Lxchal_ofs_+24
	.set	.Lxchal_pofs_, .Lxchal_pofs_ + 88
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 32
	.अन्यथाअगर ((XTHAL_SAS_TIE | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 0, 8, 8
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 120
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

