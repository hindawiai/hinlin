<शैली गुरु>
/*
 * include/यंत्र-xtensa/coprocessor.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 - 2007 Tensilica Inc.
 */


#अगर_अघोषित _XTENSA_COPROCESSOR_H
#घोषणा _XTENSA_COPROCESSOR_H

#समावेश <variant/tie.h>
#समावेश <यंत्र/core.h>
#समावेश <यंत्र/types.h>

#अगर_घोषित __ASSEMBLY__
# include <variant/tie-यंत्र.h>

.macro	xchal_sa_start  a b
	.set .Lxchal_pofs_, 0
	.set .Lxchal_ofs_, 0
.endm

.macro	xchal_sa_align  ptr minofs maxofs ofsalign totalign
	.set	.Lxchal_ofs_, .Lxchal_ofs_ + .Lxchal_pofs_ + \टotalign - 1
	.set	.Lxchal_ofs_, (.Lxchal_ofs_ & -\टotalign) - .Lxchal_pofs_
.endm

#घोषणा _SELECT	(  XTHAL_SAS_TIE | XTHAL_SAS_OPT \
		 | XTHAL_SAS_CC \
		 | XTHAL_SAS_CALR | XTHAL_SAS_CALE )

.macro save_xtregs_opt ptr clb at1 at2 at3 at4 offset
	.अगर XTREGS_OPT_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_store \clb \चt1 \चt2 \चt3 \चt4 select=_SELECT
	.endअगर
.endm

.macro load_xtregs_opt ptr clb at1 at2 at3 at4 offset
	.अगर XTREGS_OPT_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_load \clb \चt1 \चt2 \चt3 \चt4 select=_SELECT
	.endअगर
.endm
#अघोषित _SELECT

#घोषणा _SELECT	(  XTHAL_SAS_TIE | XTHAL_SAS_OPT \
		 | XTHAL_SAS_NOCC \
		 | XTHAL_SAS_CALR | XTHAL_SAS_CALE | XTHAL_SAS_GLOB )

.macro save_xtregs_user ptr clb at1 at2 at3 at4 offset
	.अगर XTREGS_USER_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_store \clb \चt1 \चt2 \चt3 \चt4 select=_SELECT
	.endअगर
.endm

.macro load_xtregs_user ptr clb at1 at2 at3 at4 offset
	.अगर XTREGS_USER_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_load \clb \चt1 \चt2 \चt3 \चt4 select=_SELECT
	.endअगर
.endm
#अघोषित _SELECT



#पूर्ण_अगर	/* __ASSEMBLY__ */

/*
 * XTENSA_HAVE_COPROCESSOR(x) वापसs 1 अगर coprocessor x is configured.
 *
 * XTENSA_HAVE_IO_PORT(x) वापसs 1 अगर io-port x is configured.
 *
 */

#घोषणा XTENSA_HAVE_COPROCESSOR(x)					\
	((XCHAL_CP_MASK ^ XCHAL_CP_PORT_MASK) & (1 << (x)))
#घोषणा XTENSA_HAVE_COPROCESSORS					\
	(XCHAL_CP_MASK ^ XCHAL_CP_PORT_MASK)
#घोषणा XTENSA_HAVE_IO_PORT(x)						\
	(XCHAL_CP_PORT_MASK & (1 << (x)))
#घोषणा XTENSA_HAVE_IO_PORTS						\
	XCHAL_CP_PORT_MASK

#अगर_अघोषित __ASSEMBLY__

/*
 * Additional रेजिस्टरs.
 * We define three types of additional रेजिस्टरs:
 *  ext: extra रेजिस्टरs that are used by the compiler
 *  cpn: optional रेजिस्टरs that can be used by a user application
 *  cpX: coprocessor रेजिस्टरs that can only be used अगर the corresponding
 *       CPENABLE bit is set.
 */

#घोषणा XCHAL_SA_REG(list,cc,abi,type,y,name,z,align,size,...)	\
	__REG ## list (cc, abi, type, name, size, align)

#घोषणा __REG0(cc,abi,t,name,s,a)	__REG0_ ## cc (abi,name)
#घोषणा __REG1(cc,abi,t,name,s,a)	__REG1_ ## cc (name)
#घोषणा __REG2(cc,abi,type,...)		__REG2_ ## type (__VA_ARGS__)

#घोषणा __REG0_0(abi,name)
#घोषणा __REG0_1(abi,name)		__REG0_1 ## abi (name)
#घोषणा __REG0_10(name)	__u32 name;
#घोषणा __REG0_11(name)	__u32 name;
#घोषणा __REG0_12(name)

#घोषणा __REG1_0(name)	__u32 name;
#घोषणा __REG1_1(name)

#घोषणा __REG2_0(n,s,a)	__u32 name;
#घोषणा __REG2_1(n,s,a)	अचिन्हित अक्षर n[s] __attribute__ ((aligned(a)));
#घोषणा __REG2_2(n,s,a) अचिन्हित अक्षर n[s] __attribute__ ((aligned(a)));

प्रकार काष्ठा अणु XCHAL_NCP_SA_LIST(0) पूर्ण xtregs_opt_t
	__attribute__ ((aligned (XCHAL_NCP_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_NCP_SA_LIST(1) पूर्ण xtregs_user_t
	__attribute__ ((aligned (XCHAL_NCP_SA_ALIGN)));

#अगर XTENSA_HAVE_COPROCESSORS

प्रकार काष्ठा अणु XCHAL_CP0_SA_LIST(2) पूर्ण xtregs_cp0_t
	__attribute__ ((aligned (XCHAL_CP0_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_CP1_SA_LIST(2) पूर्ण xtregs_cp1_t
	__attribute__ ((aligned (XCHAL_CP1_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_CP2_SA_LIST(2) पूर्ण xtregs_cp2_t
	__attribute__ ((aligned (XCHAL_CP2_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_CP3_SA_LIST(2) पूर्ण xtregs_cp3_t
	__attribute__ ((aligned (XCHAL_CP3_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_CP4_SA_LIST(2) पूर्ण xtregs_cp4_t
	__attribute__ ((aligned (XCHAL_CP4_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_CP5_SA_LIST(2) पूर्ण xtregs_cp5_t
	__attribute__ ((aligned (XCHAL_CP5_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_CP6_SA_LIST(2) पूर्ण xtregs_cp6_t
	__attribute__ ((aligned (XCHAL_CP6_SA_ALIGN)));
प्रकार काष्ठा अणु XCHAL_CP7_SA_LIST(2) पूर्ण xtregs_cp7_t
	__attribute__ ((aligned (XCHAL_CP7_SA_ALIGN)));

बाह्य काष्ठा thपढ़ो_info* coprocessor_owner[XCHAL_CP_MAX];
बाह्य व्योम coprocessor_flush(काष्ठा thपढ़ो_info*, पूर्णांक);

बाह्य व्योम coprocessor_release_all(काष्ठा thपढ़ो_info*);
बाह्य व्योम coprocessor_flush_all(काष्ठा thपढ़ो_info*);

#पूर्ण_अगर	/* XTENSA_HAVE_COPROCESSORS */

#पूर्ण_अगर	/* !__ASSEMBLY__ */
#पूर्ण_अगर	/* _XTENSA_COPROCESSOR_H */
