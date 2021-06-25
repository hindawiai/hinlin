<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MT regs definitions, follows on from mipsregs.h
 * Copyright (C) 2004 - 2005 MIPS Technologies, Inc.  All rights reserved.
 * Elizabeth Clarke et. al.
 *
 */
#अगर_अघोषित _ASM_MIPSMTREGS_H
#घोषणा _ASM_MIPSMTREGS_H

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/war.h>

#अगर_अघोषित __ASSEMBLY__

/*
 * C macros
 */

#घोषणा पढ़ो_c0_mvpcontrol()		__पढ़ो_32bit_c0_रेजिस्टर($0, 1)
#घोषणा ग_लिखो_c0_mvpcontrol(val)	__ग_लिखो_32bit_c0_रेजिस्टर($0, 1, val)

#घोषणा पढ़ो_c0_mvpconf0()		__पढ़ो_32bit_c0_रेजिस्टर($0, 2)
#घोषणा पढ़ो_c0_mvpconf1()		__पढ़ो_32bit_c0_रेजिस्टर($0, 3)

#घोषणा पढ़ो_c0_vpecontrol()		__पढ़ो_32bit_c0_रेजिस्टर($1, 1)
#घोषणा ग_लिखो_c0_vpecontrol(val)	__ग_लिखो_32bit_c0_रेजिस्टर($1, 1, val)

#घोषणा पढ़ो_c0_vpeconf0()		__पढ़ो_32bit_c0_रेजिस्टर($1, 2)
#घोषणा ग_लिखो_c0_vpeconf0(val)		__ग_लिखो_32bit_c0_रेजिस्टर($1, 2, val)

#घोषणा पढ़ो_c0_vpeconf1()		__पढ़ो_32bit_c0_रेजिस्टर($1, 3)
#घोषणा ग_लिखो_c0_vpeconf1(val)		__ग_लिखो_32bit_c0_रेजिस्टर($1, 3, val)

#घोषणा पढ़ो_c0_tcstatus()		__पढ़ो_32bit_c0_रेजिस्टर($2, 1)
#घोषणा ग_लिखो_c0_tcstatus(val)		__ग_लिखो_32bit_c0_रेजिस्टर($2, 1, val)

#घोषणा पढ़ो_c0_tcbind()		__पढ़ो_32bit_c0_रेजिस्टर($2, 2)

#घोषणा ग_लिखो_c0_tchalt(val)		__ग_लिखो_32bit_c0_रेजिस्टर($2, 4, val)

#घोषणा पढ़ो_c0_tccontext()		__पढ़ो_32bit_c0_रेजिस्टर($2, 5)
#घोषणा ग_लिखो_c0_tccontext(val)		__ग_लिखो_32bit_c0_रेजिस्टर($2, 5, val)

#अन्यथा /* Assembly */
/*
 * Macros क्रम use in assembly language code
 */

#घोषणा CP0_MVPCONTROL		$0, 1
#घोषणा CP0_MVPCONF0		$0, 2
#घोषणा CP0_MVPCONF1		$0, 3
#घोषणा CP0_VPECONTROL		$1, 1
#घोषणा CP0_VPECONF0		$1, 2
#घोषणा CP0_VPECONF1		$1, 3
#घोषणा CP0_YQMASK		$1, 4
#घोषणा CP0_VPESCHEDULE		$1, 5
#घोषणा CP0_VPESCHEFBK		$1, 6
#घोषणा CP0_TCSTATUS		$2, 1
#घोषणा CP0_TCBIND		$2, 2
#घोषणा CP0_TCRESTART		$2, 3
#घोषणा CP0_TCHALT		$2, 4
#घोषणा CP0_TCCONTEXT		$2, 5
#घोषणा CP0_TCSCHEDULE		$2, 6
#घोषणा CP0_TCSCHEFBK		$2, 7
#घोषणा CP0_SRSCONF0		$6, 1
#घोषणा CP0_SRSCONF1		$6, 2
#घोषणा CP0_SRSCONF2		$6, 3
#घोषणा CP0_SRSCONF3		$6, 4
#घोषणा CP0_SRSCONF4		$6, 5

#पूर्ण_अगर

/* MVPControl fields */
#घोषणा MVPCONTROL_EVP		(_ULCAST_(1))

#घोषणा MVPCONTROL_VPC_SHIFT	1
#घोषणा MVPCONTROL_VPC		(_ULCAST_(1) << MVPCONTROL_VPC_SHIFT)

#घोषणा MVPCONTROL_STLB_SHIFT	2
#घोषणा MVPCONTROL_STLB		(_ULCAST_(1) << MVPCONTROL_STLB_SHIFT)


/* MVPConf0 fields */
#घोषणा MVPCONF0_PTC_SHIFT	0
#घोषणा MVPCONF0_PTC		( _ULCAST_(0xff))
#घोषणा MVPCONF0_PVPE_SHIFT	10
#घोषणा MVPCONF0_PVPE		( _ULCAST_(0xf) << MVPCONF0_PVPE_SHIFT)
#घोषणा MVPCONF0_TCA_SHIFT	15
#घोषणा MVPCONF0_TCA		( _ULCAST_(1) << MVPCONF0_TCA_SHIFT)
#घोषणा MVPCONF0_PTLBE_SHIFT	16
#घोषणा MVPCONF0_PTLBE		(_ULCAST_(0x3ff) << MVPCONF0_PTLBE_SHIFT)
#घोषणा MVPCONF0_TLBS_SHIFT	29
#घोषणा MVPCONF0_TLBS		(_ULCAST_(1) << MVPCONF0_TLBS_SHIFT)
#घोषणा MVPCONF0_M_SHIFT	31
#घोषणा MVPCONF0_M		(_ULCAST_(0x1) << MVPCONF0_M_SHIFT)


/* config3 fields */
#घोषणा CONFIG3_MT_SHIFT	2
#घोषणा CONFIG3_MT		(_ULCAST_(1) << CONFIG3_MT_SHIFT)


/* VPEControl fields (per VPE) */
#घोषणा VPECONTROL_TARGTC	(_ULCAST_(0xff))

#घोषणा VPECONTROL_TE_SHIFT	15
#घोषणा VPECONTROL_TE		(_ULCAST_(1) << VPECONTROL_TE_SHIFT)
#घोषणा VPECONTROL_EXCPT_SHIFT	16
#घोषणा VPECONTROL_EXCPT	(_ULCAST_(0x7) << VPECONTROL_EXCPT_SHIFT)

/* Thपढ़ो Exception Codes क्रम EXCPT field */
#घोषणा THREX_TU		0
#घोषणा THREX_TO		1
#घोषणा THREX_IYQ		2
#घोषणा THREX_GSX		3
#घोषणा THREX_YSCH		4
#घोषणा THREX_GSSCH		5

#घोषणा VPECONTROL_GSI_SHIFT	20
#घोषणा VPECONTROL_GSI		(_ULCAST_(1) << VPECONTROL_GSI_SHIFT)
#घोषणा VPECONTROL_YSI_SHIFT	21
#घोषणा VPECONTROL_YSI		(_ULCAST_(1) << VPECONTROL_YSI_SHIFT)

/* VPEConf0 fields (per VPE) */
#घोषणा VPECONF0_VPA_SHIFT	0
#घोषणा VPECONF0_VPA		(_ULCAST_(1) << VPECONF0_VPA_SHIFT)
#घोषणा VPECONF0_MVP_SHIFT	1
#घोषणा VPECONF0_MVP		(_ULCAST_(1) << VPECONF0_MVP_SHIFT)
#घोषणा VPECONF0_XTC_SHIFT	21
#घोषणा VPECONF0_XTC		(_ULCAST_(0xff) << VPECONF0_XTC_SHIFT)

/* VPEConf1 fields (per VPE) */
#घोषणा VPECONF1_NCP1_SHIFT	0
#घोषणा VPECONF1_NCP1		(_ULCAST_(0xff) << VPECONF1_NCP1_SHIFT)
#घोषणा VPECONF1_NCP2_SHIFT	10
#घोषणा VPECONF1_NCP2		(_ULCAST_(0xff) << VPECONF1_NCP2_SHIFT)
#घोषणा VPECONF1_NCX_SHIFT	20
#घोषणा VPECONF1_NCX		(_ULCAST_(0xff) << VPECONF1_NCX_SHIFT)

/* TCStatus fields (per TC) */
#घोषणा TCSTATUS_TASID		(_ULCAST_(0xff))
#घोषणा TCSTATUS_IXMT_SHIFT	10
#घोषणा TCSTATUS_IXMT		(_ULCAST_(1) << TCSTATUS_IXMT_SHIFT)
#घोषणा TCSTATUS_TKSU_SHIFT	11
#घोषणा TCSTATUS_TKSU		(_ULCAST_(3) << TCSTATUS_TKSU_SHIFT)
#घोषणा TCSTATUS_A_SHIFT	13
#घोषणा TCSTATUS_A		(_ULCAST_(1) << TCSTATUS_A_SHIFT)
#घोषणा TCSTATUS_DA_SHIFT	15
#घोषणा TCSTATUS_DA		(_ULCAST_(1) << TCSTATUS_DA_SHIFT)
#घोषणा TCSTATUS_DT_SHIFT	20
#घोषणा TCSTATUS_DT		(_ULCAST_(1) << TCSTATUS_DT_SHIFT)
#घोषणा TCSTATUS_TDS_SHIFT	21
#घोषणा TCSTATUS_TDS		(_ULCAST_(1) << TCSTATUS_TDS_SHIFT)
#घोषणा TCSTATUS_TSST_SHIFT	22
#घोषणा TCSTATUS_TSST		(_ULCAST_(1) << TCSTATUS_TSST_SHIFT)
#घोषणा TCSTATUS_RNST_SHIFT	23
#घोषणा TCSTATUS_RNST		(_ULCAST_(3) << TCSTATUS_RNST_SHIFT)
/* Codes क्रम RNST */
#घोषणा TC_RUNNING		0
#घोषणा TC_WAITING		1
#घोषणा TC_YIELDING		2
#घोषणा TC_GATED		3

#घोषणा TCSTATUS_TMX_SHIFT	27
#घोषणा TCSTATUS_TMX		(_ULCAST_(1) << TCSTATUS_TMX_SHIFT)
/* TCStatus TCU bits can use same definitions/offsets as CU bits in Status */

/* TCBind */
#घोषणा TCBIND_CURVPE_SHIFT	0
#घोषणा TCBIND_CURVPE		(_ULCAST_(0xf))

#घोषणा TCBIND_CURTC_SHIFT	21

#घोषणा TCBIND_CURTC		(_ULCAST_(0xff) << TCBIND_CURTC_SHIFT)

/* TCHalt */
#घोषणा TCHALT_H		(_ULCAST_(1))

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत अचिन्हित core_nvpes(व्योम)
अणु
	अचिन्हित conf0;

	अगर (!cpu_has_mipsmt)
		वापस 1;

	conf0 = पढ़ो_c0_mvpconf0();
	वापस ((conf0 & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT) + 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dvpe(व्योम)
अणु
	पूर्णांक res = 0;

	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	noreorder					\n"
	"	.set	noat						\n"
	"	.set	mips32r2					\n"
	"	.word	0x41610001		# dvpe $1		\n"
	"	move	%0, $1						\n"
	"	ehb							\n"
	"	.set	pop						\n"
	: "=r" (res));

	inकाष्ठाion_hazard();

	वापस res;
पूर्ण

अटल अंतरभूत व्योम __raw_evpe(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	noreorder					\n"
	"	.set	noat						\n"
	"	.set	mips32r2					\n"
	"	.word	0x41600021		# evpe			\n"
	"	ehb							\n"
	"	.set	pop						\n");
पूर्ण

/* Enable भव processor execution अगर previous suggested it should be.
   EVPE_ENABLE to क्रमce */

#घोषणा EVPE_ENABLE MVPCONTROL_EVP

अटल अंतरभूत व्योम evpe(पूर्णांक previous)
अणु
	अगर ((previous & MVPCONTROL_EVP))
		__raw_evpe();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dmt(व्योम)
अणु
	पूर्णांक res;

	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	mips32r2					\n"
	"	.set	noat						\n"
	"	.word	0x41610BC1			# dmt $1	\n"
	"	ehb							\n"
	"	move	%0, $1						\n"
	"	.set	pop						\n"
	: "=r" (res));

	inकाष्ठाion_hazard();

	वापस res;
पूर्ण

अटल अंतरभूत व्योम __raw_emt(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	noreorder					\n"
	"	.set	mips32r2					\n"
	"	.word	0x41600be1			# emt		\n"
	"	ehb							\n"
	"	.set	pop");
पूर्ण

/* enable multi-thपढ़ोed execution अगर previous suggested it should be.
   EMT_ENABLE to क्रमce */

#घोषणा EMT_ENABLE VPECONTROL_TE

अटल अंतरभूत व्योम emt(पूर्णांक previous)
अणु
	अगर ((previous & EMT_ENABLE))
		__raw_emt();
पूर्ण

अटल अंतरभूत व्योम ehb(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
	"	.set	push					\n"
	"	.set	mips32r2				\n"
	"	ehb						\n"
	"	.set	pop					\n");
पूर्ण

#घोषणा mftc0(rt,sel)							\
(अणु									\
	 अचिन्हित दीर्घ	__res;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	mips32r2				\n"	\
	"	.set	noat					\n"	\
	"	# mftc0 $1, $" #rt ", " #sel "			\n"	\
	"	.word	0x41000800 | (" #rt " << 16) | " #sel " \n"	\
	"	move	%0, $1					\n"	\
	"	.set	pop					\n"	\
	: "=r" (__res));						\
									\
	__res;								\
पूर्ण)

#घोषणा mftgpr(rt)							\
(अणु									\
	अचिन्हित दीर्घ __res;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	.set	mips32r2				\n"	\
	"	# mftgpr $1," #rt "				\n"	\
	"	.word	0x41000820 | (" #rt " << 16)		\n"	\
	"	move	%0, $1					\n"	\
	"	.set	pop					\n"	\
	: "=r" (__res));						\
									\
	__res;								\
पूर्ण)

#घोषणा mftr(rt, u, sel)							\
(अणु									\
	अचिन्हित दीर्घ __res;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	mftr	%0, " #rt ", " #u ", " #sel "		\n"	\
	: "=r" (__res));						\
									\
	__res;								\
पूर्ण)

#घोषणा mttgpr(rd,v)							\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	mips32r2				\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mttgpr $1, " #rd "				\n"	\
	"	.word	0x41810020 | (" #rd " << 11)		\n"	\
	"	.set	pop					\n"	\
	: : "r" (v));							\
पूर्ण जबतक (0)

#घोषणा mttc0(rd, sel, v)							\
(अणु									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	mips32r2				\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# mttc0 %0," #rd ", " #sel "			\n"	\
	"	.word	0x41810000 | (" #rd " << 11) | " #sel " \n"	\
	"	.set	pop					\n"	\
	:								\
	: "r" (v));							\
पूर्ण)


#घोषणा mttr(rd, u, sel, v)						\
(अणु									\
	__यंत्र__ __अस्थिर__(						\
	"mttr	%0," #rd ", " #u ", " #sel				\
	: : "r" (v));							\
पूर्ण)


#घोषणा settc(tc)							\
करो अणु									\
	ग_लिखो_c0_vpecontrol((पढ़ो_c0_vpecontrol()&~VPECONTROL_TARGTC) | (tc)); \
	ehb();								\
पूर्ण जबतक (0)


/* you *must* set the target tc (settc) beक्रमe trying to use these */
#घोषणा पढ़ो_vpe_c0_vpecontrol()	mftc0(1, 1)
#घोषणा ग_लिखो_vpe_c0_vpecontrol(val)	mttc0(1, 1, val)
#घोषणा पढ़ो_vpe_c0_vpeconf0()		mftc0(1, 2)
#घोषणा ग_लिखो_vpe_c0_vpeconf0(val)	mttc0(1, 2, val)
#घोषणा पढ़ो_vpe_c0_vpeconf1()		mftc0(1, 3)
#घोषणा ग_लिखो_vpe_c0_vpeconf1(val)	mttc0(1, 3, val)
#घोषणा पढ़ो_vpe_c0_count()		mftc0(9, 0)
#घोषणा ग_लिखो_vpe_c0_count(val)		mttc0(9, 0, val)
#घोषणा पढ़ो_vpe_c0_status()		mftc0(12, 0)
#घोषणा ग_लिखो_vpe_c0_status(val)	mttc0(12, 0, val)
#घोषणा पढ़ो_vpe_c0_cause()		mftc0(13, 0)
#घोषणा ग_लिखो_vpe_c0_cause(val)		mttc0(13, 0, val)
#घोषणा पढ़ो_vpe_c0_config()		mftc0(16, 0)
#घोषणा ग_लिखो_vpe_c0_config(val)	mttc0(16, 0, val)
#घोषणा पढ़ो_vpe_c0_config1()		mftc0(16, 1)
#घोषणा ग_लिखो_vpe_c0_config1(val)	mttc0(16, 1, val)
#घोषणा पढ़ो_vpe_c0_config7()		mftc0(16, 7)
#घोषणा ग_लिखो_vpe_c0_config7(val)	mttc0(16, 7, val)
#घोषणा पढ़ो_vpe_c0_ebase()		mftc0(15, 1)
#घोषणा ग_लिखो_vpe_c0_ebase(val)		mttc0(15, 1, val)
#घोषणा ग_लिखो_vpe_c0_compare(val)	mttc0(11, 0, val)
#घोषणा पढ़ो_vpe_c0_badvaddr()		mftc0(8, 0)
#घोषणा पढ़ो_vpe_c0_epc()		mftc0(14, 0)
#घोषणा ग_लिखो_vpe_c0_epc(val)		mttc0(14, 0, val)


/* TC */
#घोषणा पढ़ो_tc_c0_tcstatus()		mftc0(2, 1)
#घोषणा ग_लिखो_tc_c0_tcstatus(val)	mttc0(2, 1, val)
#घोषणा पढ़ो_tc_c0_tcbind()		mftc0(2, 2)
#घोषणा ग_लिखो_tc_c0_tcbind(val)		mttc0(2, 2, val)
#घोषणा पढ़ो_tc_c0_tcrestart()		mftc0(2, 3)
#घोषणा ग_लिखो_tc_c0_tcrestart(val)	mttc0(2, 3, val)
#घोषणा पढ़ो_tc_c0_tchalt()		mftc0(2, 4)
#घोषणा ग_लिखो_tc_c0_tchalt(val)		mttc0(2, 4, val)
#घोषणा पढ़ो_tc_c0_tccontext()		mftc0(2, 5)
#घोषणा ग_लिखो_tc_c0_tccontext(val)	mttc0(2, 5, val)

/* GPR */
#घोषणा पढ़ो_tc_gpr_sp()		mftgpr(29)
#घोषणा ग_लिखो_tc_gpr_sp(val)		mttgpr(29, val)
#घोषणा पढ़ो_tc_gpr_gp()		mftgpr(28)
#घोषणा ग_लिखो_tc_gpr_gp(val)		mttgpr(28, val)

__BUILD_SET_C0(mvpcontrol)

#पूर्ण_अगर /* Not __ASSEMBLY__ */

#पूर्ण_अगर
