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
	xchal_sa_align	\ptr, 0, 1004, 4, 4
	rsr.SCOMPARE1	\चt1		// conditional store option
	s32i	\चt1, \ptr, .Lxchal_ofs_+0
	rsr.M0	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+4
	rsr.M1	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+8
	rsr.M2	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+12
	rsr.M3	\चt1		// MAC16 option
	s32i	\चt1, \ptr, .Lxchal_ofs_+16
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 20
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1004, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 20
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
	xchal_sa_align	\ptr, 0, 1004, 4, 4
	l32i	\चt1, \ptr, .Lxchal_ofs_+0
	wsr.SCOMPARE1	\चt1		// conditional store option
	l32i	\चt1, \ptr, .Lxchal_ofs_+4
	wsr.M0	\चt1		// MAC16 option
	l32i	\चt1, \ptr, .Lxchal_ofs_+8
	wsr.M1	\चt1		// MAC16 option
	l32i	\चt1, \ptr, .Lxchal_ofs_+12
	wsr.M2	\चt1		// MAC16 option
	l32i	\चt1, \ptr, .Lxchal_ofs_+16
	wsr.M3	\चt1		// MAC16 option
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 20
	.अन्यथाअगर ((XTHAL_SAS_OPT | XTHAL_SAS_NOCC | XTHAL_SAS_CALR) & ~(\चlloc)) == 0
	xchal_sa_align	\ptr, 0, 1004, 4, 4
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + 20
	.endअगर
    .endm	// xchal_ncp_load


#घोषणा XCHAL_NCP_NUM_ATMPS	1

#घोषणा XCHAL_SA_NUM_ATMPS	1

#पूर्ण_अगर /*_XTENSA_CORE_TIE_ASM_H*/

