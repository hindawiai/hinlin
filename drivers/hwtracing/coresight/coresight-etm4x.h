<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _CORESIGHT_CORESIGHT_ETM_H
#घोषणा _CORESIGHT_CORESIGHT_ETM_H

#समावेश <यंत्र/local.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश "coresight-priv.h"

/*
 * Device रेजिस्टरs:
 * 0x000 - 0x2FC: Trace		रेजिस्टरs
 * 0x300 - 0x314: Management	रेजिस्टरs
 * 0x318 - 0xEFC: Trace		रेजिस्टरs
 * 0xF00: Management		रेजिस्टरs
 * 0xFA0 - 0xFA4: Trace		रेजिस्टरs
 * 0xFA8 - 0xFFC: Management	रेजिस्टरs
 */
/* Trace रेजिस्टरs (0x000-0x2FC) */
/* Main control and configuration रेजिस्टरs */
#घोषणा TRCPRGCTLR			0x004
#घोषणा TRCPROCSELR			0x008
#घोषणा TRCSTATR			0x00C
#घोषणा TRCCONFIGR			0x010
#घोषणा TRCAUXCTLR			0x018
#घोषणा TRCEVENTCTL0R			0x020
#घोषणा TRCEVENTCTL1R			0x024
#घोषणा TRCRSR				0x028
#घोषणा TRCSTALLCTLR			0x02C
#घोषणा TRCTSCTLR			0x030
#घोषणा TRCSYNCPR			0x034
#घोषणा TRCCCCTLR			0x038
#घोषणा TRCBBCTLR			0x03C
#घोषणा TRCTRACEIDR			0x040
#घोषणा TRCQCTLR			0x044
/* Filtering control रेजिस्टरs */
#घोषणा TRCVICTLR			0x080
#घोषणा TRCVIIECTLR			0x084
#घोषणा TRCVISSCTLR			0x088
#घोषणा TRCVIPCSSCTLR			0x08C
#घोषणा TRCVDCTLR			0x0A0
#घोषणा TRCVDSACCTLR			0x0A4
#घोषणा TRCVDARCCTLR			0x0A8
/* Derived resources रेजिस्टरs */
#घोषणा TRCSEQEVRn(n)			(0x100 + (n * 4)) /* n = 0-2 */
#घोषणा TRCSEQRSTEVR			0x118
#घोषणा TRCSEQSTR			0x11C
#घोषणा TRCEXTINSELR			0x120
#घोषणा TRCEXTINSELRn(n)		(0x120 + (n * 4)) /* n = 0-3 */
#घोषणा TRCCNTRLDVRn(n)			(0x140 + (n * 4)) /* n = 0-3 */
#घोषणा TRCCNTCTLRn(n)			(0x150 + (n * 4)) /* n = 0-3 */
#घोषणा TRCCNTVRn(n)			(0x160 + (n * 4)) /* n = 0-3 */
/* ID रेजिस्टरs */
#घोषणा TRCIDR8				0x180
#घोषणा TRCIDR9				0x184
#घोषणा TRCIDR10			0x188
#घोषणा TRCIDR11			0x18C
#घोषणा TRCIDR12			0x190
#घोषणा TRCIDR13			0x194
#घोषणा TRCIMSPEC0			0x1C0
#घोषणा TRCIMSPECn(n)			(0x1C0 + (n * 4)) /* n = 1-7 */
#घोषणा TRCIDR0				0x1E0
#घोषणा TRCIDR1				0x1E4
#घोषणा TRCIDR2				0x1E8
#घोषणा TRCIDR3				0x1EC
#घोषणा TRCIDR4				0x1F0
#घोषणा TRCIDR5				0x1F4
#घोषणा TRCIDR6				0x1F8
#घोषणा TRCIDR7				0x1FC
/*
 * Resource selection रेजिस्टरs, n = 2-31.
 * First pair (regs 0, 1) is always present and is reserved.
 */
#घोषणा TRCRSCTLRn(n)			(0x200 + (n * 4))
/* Single-shot comparator रेजिस्टरs, n = 0-7 */
#घोषणा TRCSSCCRn(n)			(0x280 + (n * 4))
#घोषणा TRCSSCSRn(n)			(0x2A0 + (n * 4))
#घोषणा TRCSSPCICRn(n)			(0x2C0 + (n * 4))
/* Management रेजिस्टरs (0x300-0x314) */
#घोषणा TRCOSLAR			0x300
#घोषणा TRCOSLSR			0x304
#घोषणा TRCPDCR				0x310
#घोषणा TRCPDSR				0x314
/* Trace रेजिस्टरs (0x318-0xEFC) */
/* Address Comparator रेजिस्टरs n = 0-15 */
#घोषणा TRCACVRn(n)			(0x400 + (n * 8))
#घोषणा TRCACATRn(n)			(0x480 + (n * 8))
/* Data Value Comparator Value रेजिस्टरs, n = 0-7 */
#घोषणा TRCDVCVRn(n)			(0x500 + (n * 16))
#घोषणा TRCDVCMRn(n)			(0x580 + (n * 16))
/* ContextID/Virtual ContextID comparators, n = 0-7 */
#घोषणा TRCCIDCVRn(n)			(0x600 + (n * 8))
#घोषणा TRCVMIDCVRn(n)			(0x640 + (n * 8))
#घोषणा TRCCIDCCTLR0			0x680
#घोषणा TRCCIDCCTLR1			0x684
#घोषणा TRCVMIDCCTLR0			0x688
#घोषणा TRCVMIDCCTLR1			0x68C
/* Management रेजिस्टर (0xF00) */
/* Integration control रेजिस्टरs */
#घोषणा TRCITCTRL			0xF00
/* Trace रेजिस्टरs (0xFA0-0xFA4) */
/* Claim tag रेजिस्टरs */
#घोषणा TRCCLAIMSET			0xFA0
#घोषणा TRCCLAIMCLR			0xFA4
/* Management रेजिस्टरs (0xFA8-0xFFC) */
#घोषणा TRCDEVAFF0			0xFA8
#घोषणा TRCDEVAFF1			0xFAC
#घोषणा TRCLAR				0xFB0
#घोषणा TRCLSR				0xFB4
#घोषणा TRCAUTHSTATUS			0xFB8
#घोषणा TRCDEVARCH			0xFBC
#घोषणा TRCDEVID			0xFC8
#घोषणा TRCDEVTYPE			0xFCC
#घोषणा TRCPIDR4			0xFD0
#घोषणा TRCPIDR5			0xFD4
#घोषणा TRCPIDR6			0xFD8
#घोषणा TRCPIDR7			0xFDC
#घोषणा TRCPIDR0			0xFE0
#घोषणा TRCPIDR1			0xFE4
#घोषणा TRCPIDR2			0xFE8
#घोषणा TRCPIDR3			0xFEC
#घोषणा TRCCIDR0			0xFF0
#घोषणा TRCCIDR1			0xFF4
#घोषणा TRCCIDR2			0xFF8
#घोषणा TRCCIDR3			0xFFC

#घोषणा TRCRSR_TA			BIT(12)

/*
 * System inकाष्ठाions to access ETM रेजिस्टरs.
 * See ETMv4.4 spec ARM IHI0064F section 4.3.6 System inकाष्ठाions
 */
#घोषणा ETM4x_OFFSET_TO_REG(x)		((x) >> 2)

#घोषणा ETM4x_CRn(n)			(((n) >> 7) & 0x7)
#घोषणा ETM4x_Op2(n)			(((n) >> 4) & 0x7)
#घोषणा ETM4x_CRm(n)			((n) & 0xf)

#समावेश <यंत्र/sysreg.h>
#घोषणा ETM4x_REG_NUM_TO_SYSREG(n)				\
	sys_reg(2, 1, ETM4x_CRn(n), ETM4x_CRm(n), ETM4x_Op2(n))

#घोषणा READ_ETM4x_REG(reg)					\
	पढ़ो_sysreg_s(ETM4x_REG_NUM_TO_SYSREG((reg)))
#घोषणा WRITE_ETM4x_REG(val, reg)				\
	ग_लिखो_sysreg_s(val, ETM4x_REG_NUM_TO_SYSREG((reg)))

#घोषणा पढ़ो_eपंचांग4x_sysreg_स्थिर_offset(offset)			\
	READ_ETM4x_REG(ETM4x_OFFSET_TO_REG(offset))

#घोषणा ग_लिखो_eपंचांग4x_sysreg_स्थिर_offset(val, offset)		\
	WRITE_ETM4x_REG(val, ETM4x_OFFSET_TO_REG(offset))

#घोषणा CASE_READ(res, x)					\
	हाल (x): अणु (res) = पढ़ो_eपंचांग4x_sysreg_स्थिर_offset((x)); अवरोध; पूर्ण

#घोषणा CASE_WRITE(val, x)					\
	हाल (x): अणु ग_लिखो_eपंचांग4x_sysreg_स्थिर_offset((val), (x)); अवरोध; पूर्ण

#घोषणा CASE_NOP(__unused, x)					\
	हाल (x):	/* fall through */

#घोषणा ETE_ONLY_SYSREG_LIST(op, val)		\
	CASE_##op((val), TRCRSR)		\
	CASE_##op((val), TRCEXTINSELRn(1))	\
	CASE_##op((val), TRCEXTINSELRn(2))	\
	CASE_##op((val), TRCEXTINSELRn(3))

/* List of रेजिस्टरs accessible via System inकाष्ठाions */
#घोषणा ETM4x_ONLY_SYSREG_LIST(op, val)		\
	CASE_##op((val), TRCPROCSELR)		\
	CASE_##op((val), TRCVDCTLR)		\
	CASE_##op((val), TRCVDSACCTLR)		\
	CASE_##op((val), TRCVDARCCTLR)		\
	CASE_##op((val), TRCOSLAR)

#घोषणा ETM_COMMON_SYSREG_LIST(op, val)		\
	CASE_##op((val), TRCPRGCTLR)		\
	CASE_##op((val), TRCSTATR)		\
	CASE_##op((val), TRCCONFIGR)		\
	CASE_##op((val), TRCAUXCTLR)		\
	CASE_##op((val), TRCEVENTCTL0R)		\
	CASE_##op((val), TRCEVENTCTL1R)		\
	CASE_##op((val), TRCSTALLCTLR)		\
	CASE_##op((val), TRCTSCTLR)		\
	CASE_##op((val), TRCSYNCPR)		\
	CASE_##op((val), TRCCCCTLR)		\
	CASE_##op((val), TRCBBCTLR)		\
	CASE_##op((val), TRCTRACEIDR)		\
	CASE_##op((val), TRCQCTLR)		\
	CASE_##op((val), TRCVICTLR)		\
	CASE_##op((val), TRCVIIECTLR)		\
	CASE_##op((val), TRCVISSCTLR)		\
	CASE_##op((val), TRCVIPCSSCTLR)		\
	CASE_##op((val), TRCSEQEVRn(0))		\
	CASE_##op((val), TRCSEQEVRn(1))		\
	CASE_##op((val), TRCSEQEVRn(2))		\
	CASE_##op((val), TRCSEQRSTEVR)		\
	CASE_##op((val), TRCSEQSTR)		\
	CASE_##op((val), TRCEXTINSELR)		\
	CASE_##op((val), TRCCNTRLDVRn(0))	\
	CASE_##op((val), TRCCNTRLDVRn(1))	\
	CASE_##op((val), TRCCNTRLDVRn(2))	\
	CASE_##op((val), TRCCNTRLDVRn(3))	\
	CASE_##op((val), TRCCNTCTLRn(0))	\
	CASE_##op((val), TRCCNTCTLRn(1))	\
	CASE_##op((val), TRCCNTCTLRn(2))	\
	CASE_##op((val), TRCCNTCTLRn(3))	\
	CASE_##op((val), TRCCNTVRn(0))		\
	CASE_##op((val), TRCCNTVRn(1))		\
	CASE_##op((val), TRCCNTVRn(2))		\
	CASE_##op((val), TRCCNTVRn(3))		\
	CASE_##op((val), TRCIDR8)		\
	CASE_##op((val), TRCIDR9)		\
	CASE_##op((val), TRCIDR10)		\
	CASE_##op((val), TRCIDR11)		\
	CASE_##op((val), TRCIDR12)		\
	CASE_##op((val), TRCIDR13)		\
	CASE_##op((val), TRCIMSPECn(0))		\
	CASE_##op((val), TRCIMSPECn(1))		\
	CASE_##op((val), TRCIMSPECn(2))		\
	CASE_##op((val), TRCIMSPECn(3))		\
	CASE_##op((val), TRCIMSPECn(4))		\
	CASE_##op((val), TRCIMSPECn(5))		\
	CASE_##op((val), TRCIMSPECn(6))		\
	CASE_##op((val), TRCIMSPECn(7))		\
	CASE_##op((val), TRCIDR0)		\
	CASE_##op((val), TRCIDR1)		\
	CASE_##op((val), TRCIDR2)		\
	CASE_##op((val), TRCIDR3)		\
	CASE_##op((val), TRCIDR4)		\
	CASE_##op((val), TRCIDR5)		\
	CASE_##op((val), TRCIDR6)		\
	CASE_##op((val), TRCIDR7)		\
	CASE_##op((val), TRCRSCTLRn(2))		\
	CASE_##op((val), TRCRSCTLRn(3))		\
	CASE_##op((val), TRCRSCTLRn(4))		\
	CASE_##op((val), TRCRSCTLRn(5))		\
	CASE_##op((val), TRCRSCTLRn(6))		\
	CASE_##op((val), TRCRSCTLRn(7))		\
	CASE_##op((val), TRCRSCTLRn(8))		\
	CASE_##op((val), TRCRSCTLRn(9))		\
	CASE_##op((val), TRCRSCTLRn(10))	\
	CASE_##op((val), TRCRSCTLRn(11))	\
	CASE_##op((val), TRCRSCTLRn(12))	\
	CASE_##op((val), TRCRSCTLRn(13))	\
	CASE_##op((val), TRCRSCTLRn(14))	\
	CASE_##op((val), TRCRSCTLRn(15))	\
	CASE_##op((val), TRCRSCTLRn(16))	\
	CASE_##op((val), TRCRSCTLRn(17))	\
	CASE_##op((val), TRCRSCTLRn(18))	\
	CASE_##op((val), TRCRSCTLRn(19))	\
	CASE_##op((val), TRCRSCTLRn(20))	\
	CASE_##op((val), TRCRSCTLRn(21))	\
	CASE_##op((val), TRCRSCTLRn(22))	\
	CASE_##op((val), TRCRSCTLRn(23))	\
	CASE_##op((val), TRCRSCTLRn(24))	\
	CASE_##op((val), TRCRSCTLRn(25))	\
	CASE_##op((val), TRCRSCTLRn(26))	\
	CASE_##op((val), TRCRSCTLRn(27))	\
	CASE_##op((val), TRCRSCTLRn(28))	\
	CASE_##op((val), TRCRSCTLRn(29))	\
	CASE_##op((val), TRCRSCTLRn(30))	\
	CASE_##op((val), TRCRSCTLRn(31))	\
	CASE_##op((val), TRCSSCCRn(0))		\
	CASE_##op((val), TRCSSCCRn(1))		\
	CASE_##op((val), TRCSSCCRn(2))		\
	CASE_##op((val), TRCSSCCRn(3))		\
	CASE_##op((val), TRCSSCCRn(4))		\
	CASE_##op((val), TRCSSCCRn(5))		\
	CASE_##op((val), TRCSSCCRn(6))		\
	CASE_##op((val), TRCSSCCRn(7))		\
	CASE_##op((val), TRCSSCSRn(0))		\
	CASE_##op((val), TRCSSCSRn(1))		\
	CASE_##op((val), TRCSSCSRn(2))		\
	CASE_##op((val), TRCSSCSRn(3))		\
	CASE_##op((val), TRCSSCSRn(4))		\
	CASE_##op((val), TRCSSCSRn(5))		\
	CASE_##op((val), TRCSSCSRn(6))		\
	CASE_##op((val), TRCSSCSRn(7))		\
	CASE_##op((val), TRCSSPCICRn(0))	\
	CASE_##op((val), TRCSSPCICRn(1))	\
	CASE_##op((val), TRCSSPCICRn(2))	\
	CASE_##op((val), TRCSSPCICRn(3))	\
	CASE_##op((val), TRCSSPCICRn(4))	\
	CASE_##op((val), TRCSSPCICRn(5))	\
	CASE_##op((val), TRCSSPCICRn(6))	\
	CASE_##op((val), TRCSSPCICRn(7))	\
	CASE_##op((val), TRCOSLSR)		\
	CASE_##op((val), TRCACVRn(0))		\
	CASE_##op((val), TRCACVRn(1))		\
	CASE_##op((val), TRCACVRn(2))		\
	CASE_##op((val), TRCACVRn(3))		\
	CASE_##op((val), TRCACVRn(4))		\
	CASE_##op((val), TRCACVRn(5))		\
	CASE_##op((val), TRCACVRn(6))		\
	CASE_##op((val), TRCACVRn(7))		\
	CASE_##op((val), TRCACVRn(8))		\
	CASE_##op((val), TRCACVRn(9))		\
	CASE_##op((val), TRCACVRn(10))		\
	CASE_##op((val), TRCACVRn(11))		\
	CASE_##op((val), TRCACVRn(12))		\
	CASE_##op((val), TRCACVRn(13))		\
	CASE_##op((val), TRCACVRn(14))		\
	CASE_##op((val), TRCACVRn(15))		\
	CASE_##op((val), TRCACATRn(0))		\
	CASE_##op((val), TRCACATRn(1))		\
	CASE_##op((val), TRCACATRn(2))		\
	CASE_##op((val), TRCACATRn(3))		\
	CASE_##op((val), TRCACATRn(4))		\
	CASE_##op((val), TRCACATRn(5))		\
	CASE_##op((val), TRCACATRn(6))		\
	CASE_##op((val), TRCACATRn(7))		\
	CASE_##op((val), TRCACATRn(8))		\
	CASE_##op((val), TRCACATRn(9))		\
	CASE_##op((val), TRCACATRn(10))		\
	CASE_##op((val), TRCACATRn(11))		\
	CASE_##op((val), TRCACATRn(12))		\
	CASE_##op((val), TRCACATRn(13))		\
	CASE_##op((val), TRCACATRn(14))		\
	CASE_##op((val), TRCACATRn(15))		\
	CASE_##op((val), TRCDVCVRn(0))		\
	CASE_##op((val), TRCDVCVRn(1))		\
	CASE_##op((val), TRCDVCVRn(2))		\
	CASE_##op((val), TRCDVCVRn(3))		\
	CASE_##op((val), TRCDVCVRn(4))		\
	CASE_##op((val), TRCDVCVRn(5))		\
	CASE_##op((val), TRCDVCVRn(6))		\
	CASE_##op((val), TRCDVCVRn(7))		\
	CASE_##op((val), TRCDVCMRn(0))		\
	CASE_##op((val), TRCDVCMRn(1))		\
	CASE_##op((val), TRCDVCMRn(2))		\
	CASE_##op((val), TRCDVCMRn(3))		\
	CASE_##op((val), TRCDVCMRn(4))		\
	CASE_##op((val), TRCDVCMRn(5))		\
	CASE_##op((val), TRCDVCMRn(6))		\
	CASE_##op((val), TRCDVCMRn(7))		\
	CASE_##op((val), TRCCIDCVRn(0))		\
	CASE_##op((val), TRCCIDCVRn(1))		\
	CASE_##op((val), TRCCIDCVRn(2))		\
	CASE_##op((val), TRCCIDCVRn(3))		\
	CASE_##op((val), TRCCIDCVRn(4))		\
	CASE_##op((val), TRCCIDCVRn(5))		\
	CASE_##op((val), TRCCIDCVRn(6))		\
	CASE_##op((val), TRCCIDCVRn(7))		\
	CASE_##op((val), TRCVMIDCVRn(0))	\
	CASE_##op((val), TRCVMIDCVRn(1))	\
	CASE_##op((val), TRCVMIDCVRn(2))	\
	CASE_##op((val), TRCVMIDCVRn(3))	\
	CASE_##op((val), TRCVMIDCVRn(4))	\
	CASE_##op((val), TRCVMIDCVRn(5))	\
	CASE_##op((val), TRCVMIDCVRn(6))	\
	CASE_##op((val), TRCVMIDCVRn(7))	\
	CASE_##op((val), TRCCIDCCTLR0)		\
	CASE_##op((val), TRCCIDCCTLR1)		\
	CASE_##op((val), TRCVMIDCCTLR0)		\
	CASE_##op((val), TRCVMIDCCTLR1)		\
	CASE_##op((val), TRCCLAIMSET)		\
	CASE_##op((val), TRCCLAIMCLR)		\
	CASE_##op((val), TRCAUTHSTATUS)		\
	CASE_##op((val), TRCDEVARCH)		\
	CASE_##op((val), TRCDEVID)

/* List of रेजिस्टरs only accessible via memory-mapped पूर्णांकerface */
#घोषणा ETM_MMAP_LIST(op, val)			\
	CASE_##op((val), TRCDEVTYPE)		\
	CASE_##op((val), TRCPDCR)		\
	CASE_##op((val), TRCPDSR)		\
	CASE_##op((val), TRCDEVAFF0)		\
	CASE_##op((val), TRCDEVAFF1)		\
	CASE_##op((val), TRCLAR)		\
	CASE_##op((val), TRCLSR)		\
	CASE_##op((val), TRCITCTRL)		\
	CASE_##op((val), TRCPIDR4)		\
	CASE_##op((val), TRCPIDR0)		\
	CASE_##op((val), TRCPIDR1)		\
	CASE_##op((val), TRCPIDR2)		\
	CASE_##op((val), TRCPIDR3)

#घोषणा ETM4x_READ_SYSREG_CASES(res)		\
	ETM_COMMON_SYSREG_LIST(READ, (res))	\
	ETM4x_ONLY_SYSREG_LIST(READ, (res))

#घोषणा ETM4x_WRITE_SYSREG_CASES(val)		\
	ETM_COMMON_SYSREG_LIST(WRITE, (val))	\
	ETM4x_ONLY_SYSREG_LIST(WRITE, (val))

#घोषणा ETM_COMMON_SYSREG_LIST_CASES		\
	ETM_COMMON_SYSREG_LIST(NOP, __unused)

#घोषणा ETM4x_ONLY_SYSREG_LIST_CASES		\
	ETM4x_ONLY_SYSREG_LIST(NOP, __unused)

#घोषणा ETM4x_SYSREG_LIST_CASES			\
	ETM_COMMON_SYSREG_LIST_CASES		\
	ETM4x_ONLY_SYSREG_LIST(NOP, __unused)

#घोषणा ETM4x_MMAP_LIST_CASES		ETM_MMAP_LIST(NOP, __unused)

/* ETE only supports प्रणाली रेजिस्टर access */
#घोषणा ETE_READ_CASES(res)			\
	ETM_COMMON_SYSREG_LIST(READ, (res))	\
	ETE_ONLY_SYSREG_LIST(READ, (res))

#घोषणा ETE_WRITE_CASES(val)			\
	ETM_COMMON_SYSREG_LIST(WRITE, (val))	\
	ETE_ONLY_SYSREG_LIST(WRITE, (val))

#घोषणा ETE_ONLY_SYSREG_LIST_CASES		\
	ETE_ONLY_SYSREG_LIST(NOP, __unused)

#घोषणा पढ़ो_eपंचांग4x_sysreg_offset(offset, _64bit)				\
	(अणु									\
		u64 __val;							\
										\
		अगर (__builtin_स्थिरant_p((offset)))				\
			__val = पढ़ो_eपंचांग4x_sysreg_स्थिर_offset((offset));	\
		अन्यथा								\
			__val = eपंचांग4x_sysreg_पढ़ो((offset), true, (_64bit));	\
		__val;								\
	 पूर्ण)

#घोषणा ग_लिखो_eपंचांग4x_sysreg_offset(val, offset, _64bit)			\
	करो अणु								\
		अगर (__builtin_स्थिरant_p((offset)))			\
			ग_लिखो_eपंचांग4x_sysreg_स्थिर_offset((val),		\
							(offset));	\
		अन्यथा							\
			eपंचांग4x_sysreg_ग_लिखो((val), (offset), true,	\
					   (_64bit));			\
	पूर्ण जबतक (0)


#घोषणा eपंचांग4x_relaxed_पढ़ो32(csa, offset)				\
	((u32)((csa)->io_mem ?						\
		 पढ़ोl_relaxed((csa)->base + (offset)) :		\
		 पढ़ो_eपंचांग4x_sysreg_offset((offset), false)))

#घोषणा eपंचांग4x_relaxed_पढ़ो64(csa, offset)				\
	((u64)((csa)->io_mem ?						\
		 पढ़ोq_relaxed((csa)->base + (offset)) :		\
		 पढ़ो_eपंचांग4x_sysreg_offset((offset), true)))

#घोषणा eपंचांग4x_पढ़ो32(csa, offset)					\
	(अणु								\
		u32 __val = eपंचांग4x_relaxed_पढ़ो32((csa), (offset));	\
		__iormb(__val);						\
		__val;							\
	 पूर्ण)

#घोषणा eपंचांग4x_पढ़ो64(csa, offset)					\
	(अणु								\
		u64 __val = eपंचांग4x_relaxed_पढ़ो64((csa), (offset));	\
		__iormb(__val);						\
		__val;							\
	 पूर्ण)

#घोषणा eपंचांग4x_relaxed_ग_लिखो32(csa, val, offset)				\
	करो अणु								\
		अगर ((csa)->io_mem)					\
			ग_लिखोl_relaxed((val), (csa)->base + (offset));	\
		अन्यथा							\
			ग_लिखो_eपंचांग4x_sysreg_offset((val), (offset),	\
						  false);		\
	पूर्ण जबतक (0)

#घोषणा eपंचांग4x_relaxed_ग_लिखो64(csa, val, offset)				\
	करो अणु								\
		अगर ((csa)->io_mem)					\
			ग_लिखोq_relaxed((val), (csa)->base + (offset));	\
		अन्यथा							\
			ग_लिखो_eपंचांग4x_sysreg_offset((val), (offset),	\
						  true);		\
	पूर्ण जबतक (0)

#घोषणा eपंचांग4x_ग_लिखो32(csa, val, offset)					\
	करो अणु								\
		__iowmb();						\
		eपंचांग4x_relaxed_ग_लिखो32((csa), (val), (offset));		\
	पूर्ण जबतक (0)

#घोषणा eपंचांग4x_ग_लिखो64(csa, val, offset)					\
	करो अणु								\
		__iowmb();						\
		eपंचांग4x_relaxed_ग_लिखो64((csa), (val), (offset));		\
	पूर्ण जबतक (0)


/* ETMv4 resources */
#घोषणा ETM_MAX_NR_PE			8
#घोषणा ETMv4_MAX_CNTR			4
#घोषणा ETM_MAX_SEQ_STATES		4
#घोषणा ETM_MAX_EXT_INP_SEL		4
#घोषणा ETM_MAX_EXT_INP			256
#घोषणा ETM_MAX_EXT_OUT			4
#घोषणा ETM_MAX_SINGLE_ADDR_CMP		16
#घोषणा ETM_MAX_ADDR_RANGE_CMP		(ETM_MAX_SINGLE_ADDR_CMP / 2)
#घोषणा ETM_MAX_DATA_VAL_CMP		8
#घोषणा ETMv4_MAX_CTXID_CMP		8
#घोषणा ETM_MAX_VMID_CMP		8
#घोषणा ETM_MAX_PE_CMP			8
#घोषणा ETM_MAX_RES_SEL			32
#घोषणा ETM_MAX_SS_CMP			8

#घोषणा ETMv4_SYNC_MASK			0x1F
#घोषणा ETM_CYC_THRESHOLD_MASK		0xFFF
#घोषणा ETM_CYC_THRESHOLD_DEFAULT       0x100
#घोषणा ETMv4_EVENT_MASK		0xFF
#घोषणा ETM_CNTR_MAX_VAL		0xFFFF
#घोषणा ETM_TRACEID_MASK		0x3f

/* ETMv4 programming modes */
#घोषणा ETM_MODE_EXCLUDE		BIT(0)
#घोषणा ETM_MODE_LOAD			BIT(1)
#घोषणा ETM_MODE_STORE			BIT(2)
#घोषणा ETM_MODE_LOAD_STORE		BIT(3)
#घोषणा ETM_MODE_BB			BIT(4)
#घोषणा ETMv4_MODE_CYCACC		BIT(5)
#घोषणा ETMv4_MODE_CTXID		BIT(6)
#घोषणा ETM_MODE_VMID			BIT(7)
#घोषणा ETM_MODE_COND(val)		BMVAL(val, 8, 10)
#घोषणा ETMv4_MODE_TIMESTAMP		BIT(11)
#घोषणा ETM_MODE_RETURNSTACK		BIT(12)
#घोषणा ETM_MODE_QELEM(val)		BMVAL(val, 13, 14)
#घोषणा ETM_MODE_DATA_TRACE_ADDR	BIT(15)
#घोषणा ETM_MODE_DATA_TRACE_VAL		BIT(16)
#घोषणा ETM_MODE_ISTALL			BIT(17)
#घोषणा ETM_MODE_DSTALL			BIT(18)
#घोषणा ETM_MODE_ATB_TRIGGER		BIT(19)
#घोषणा ETM_MODE_LPOVERRIDE		BIT(20)
#घोषणा ETM_MODE_ISTALL_EN		BIT(21)
#घोषणा ETM_MODE_DSTALL_EN		BIT(22)
#घोषणा ETM_MODE_INSTPRIO		BIT(23)
#घोषणा ETM_MODE_NOOVERFLOW		BIT(24)
#घोषणा ETM_MODE_TRACE_RESET		BIT(25)
#घोषणा ETM_MODE_TRACE_ERR		BIT(26)
#घोषणा ETM_MODE_VIEWINST_STARTSTOP	BIT(27)
#घोषणा ETMv4_MODE_ALL			(GENMASK(27, 0) | \
					 ETM_MODE_EXCL_KERN | \
					 ETM_MODE_EXCL_USER)

/*
 * TRCOSLSR.OSLM advertises the OS Lock model.
 * OSLM[2:0] = TRCOSLSR[4:3,0]
 *
 *	0b000 - Trace OS Lock is not implemented.
 *	0b010 - Trace OS Lock is implemented.
 *	0b100 - Trace OS Lock is not implemented, unit is controlled by PE OS Lock.
 */
#घोषणा ETM_OSLOCK_NI		0b000
#घोषणा ETM_OSLOCK_PRESENT	0b010
#घोषणा ETM_OSLOCK_PE		0b100

#घोषणा ETM_OSLSR_OSLM(oslsr)	((((oslsr) & GENMASK(4, 3)) >> 2) | (oslsr & 0x1))

/*
 * TRCDEVARCH Bit field definitions
 * Bits[31:21]	- ARCHITECT = Always Arm Ltd.
 *                * Bits[31:28] = 0x4
 *                * Bits[27:21] = 0b0111011
 * Bit[20]	- PRESENT,  Indicates the presence of this रेजिस्टर.
 *
 * Bit[19:16]	- REVISION, Revision of the architecture.
 *
 * Bit[15:0]	- ARCHID, Identअगरies this component as an ETM
 *                * Bits[15:12] - architecture version of ETM
 *                *             = 4 क्रम ETMv4
 *                * Bits[11:0] = 0xA13, architecture part number क्रम ETM.
 */
#घोषणा ETM_DEVARCH_ARCHITECT_MASK		GENMASK(31, 21)
#घोषणा ETM_DEVARCH_ARCHITECT_ARM		((0x4 << 28) | (0b0111011 << 21))
#घोषणा ETM_DEVARCH_PRESENT			BIT(20)
#घोषणा ETM_DEVARCH_REVISION_SHIFT		16
#घोषणा ETM_DEVARCH_REVISION_MASK		GENMASK(19, 16)
#घोषणा ETM_DEVARCH_REVISION(x)			\
	(((x) & ETM_DEVARCH_REVISION_MASK) >> ETM_DEVARCH_REVISION_SHIFT)
#घोषणा ETM_DEVARCH_ARCHID_MASK			GENMASK(15, 0)
#घोषणा ETM_DEVARCH_ARCHID_ARCH_VER_SHIFT	12
#घोषणा ETM_DEVARCH_ARCHID_ARCH_VER_MASK	GENMASK(15, 12)
#घोषणा ETM_DEVARCH_ARCHID_ARCH_VER(x)		\
	(((x) & ETM_DEVARCH_ARCHID_ARCH_VER_MASK) >> ETM_DEVARCH_ARCHID_ARCH_VER_SHIFT)

#घोषणा ETM_DEVARCH_MAKE_ARCHID_ARCH_VER(ver)			\
	(((ver) << ETM_DEVARCH_ARCHID_ARCH_VER_SHIFT) & ETM_DEVARCH_ARCHID_ARCH_VER_MASK)

#घोषणा ETM_DEVARCH_ARCHID_ARCH_PART(x)		((x) & 0xfffUL)

#घोषणा ETM_DEVARCH_MAKE_ARCHID(major)			\
	((ETM_DEVARCH_MAKE_ARCHID_ARCH_VER(major)) | ETM_DEVARCH_ARCHID_ARCH_PART(0xA13))

#घोषणा ETM_DEVARCH_ARCHID_ETMv4x		ETM_DEVARCH_MAKE_ARCHID(0x4)
#घोषणा ETM_DEVARCH_ARCHID_ETE			ETM_DEVARCH_MAKE_ARCHID(0x5)

#घोषणा ETM_DEVARCH_ID_MASK						\
	(ETM_DEVARCH_ARCHITECT_MASK | ETM_DEVARCH_ARCHID_MASK | ETM_DEVARCH_PRESENT)
#घोषणा ETM_DEVARCH_ETMv4x_ARCH						\
	(ETM_DEVARCH_ARCHITECT_ARM | ETM_DEVARCH_ARCHID_ETMv4x | ETM_DEVARCH_PRESENT)
#घोषणा ETM_DEVARCH_ETE_ARCH						\
	(ETM_DEVARCH_ARCHITECT_ARM | ETM_DEVARCH_ARCHID_ETE | ETM_DEVARCH_PRESENT)

#घोषणा TRCSTATR_IDLE_BIT		0
#घोषणा TRCSTATR_PMSTABLE_BIT		1
#घोषणा ETM_DEFAULT_ADDR_COMP		0

#घोषणा TRCSSCSRn_PC			BIT(3)

/* PowerDown Control Register bits */
#घोषणा TRCPDCR_PU			BIT(3)

#घोषणा TRCACATR_EXLEVEL_SHIFT		8

/*
 * Exception level mask क्रम Secure and Non-Secure ELs.
 * ETM defines the bits क्रम EL control (e.g, TRVICTLR, TRCACTRn).
 * The Secure and Non-Secure ELs are always to gether.
 * Non-secure EL3 is never implemented.
 * We use the following generic mask as they appear in dअगरferent
 * रेजिस्टरs and this can be shअगरted क्रम the appropriate
 * fields.
 */
#घोषणा ETM_EXLEVEL_S_APP		BIT(0)	/* Secure EL0		*/
#घोषणा ETM_EXLEVEL_S_OS		BIT(1)	/* Secure EL1		*/
#घोषणा ETM_EXLEVEL_S_HYP		BIT(2)	/* Secure EL2		*/
#घोषणा ETM_EXLEVEL_S_MON		BIT(3)	/* Secure EL3/Monitor	*/
#घोषणा ETM_EXLEVEL_NS_APP		BIT(4)	/* NonSecure EL0	*/
#घोषणा ETM_EXLEVEL_NS_OS		BIT(5)	/* NonSecure EL1	*/
#घोषणा ETM_EXLEVEL_NS_HYP		BIT(6)	/* NonSecure EL2	*/

#घोषणा ETM_EXLEVEL_MASK		(GENMASK(6, 0))
#घोषणा ETM_EXLEVEL_S_MASK		(GENMASK(3, 0))
#घोषणा ETM_EXLEVEL_NS_MASK		(GENMASK(6, 4))

/* access level controls in TRCACATRn */
#घोषणा TRCACATR_EXLEVEL_SHIFT		8

/* access level control in TRCVICTLR */
#घोषणा TRCVICTLR_EXLEVEL_SHIFT		16
#घोषणा TRCVICTLR_EXLEVEL_S_SHIFT	16
#घोषणा TRCVICTLR_EXLEVEL_NS_SHIFT	20

/* secure / non secure masks - TRCVICTLR, IDR3 */
#घोषणा TRCVICTLR_EXLEVEL_MASK		(ETM_EXLEVEL_MASK << TRCVICTLR_EXLEVEL_SHIFT)
#घोषणा TRCVICTLR_EXLEVEL_S_MASK	(ETM_EXLEVEL_S_MASK << TRCVICTLR_EXLEVEL_SHIFT)
#घोषणा TRCVICTLR_EXLEVEL_NS_MASK	(ETM_EXLEVEL_NS_MASK << TRCVICTLR_EXLEVEL_SHIFT)

#घोषणा ETM_TRCIDR1_ARCH_MAJOR_SHIFT	8
#घोषणा ETM_TRCIDR1_ARCH_MAJOR_MASK	(0xfU << ETM_TRCIDR1_ARCH_MAJOR_SHIFT)
#घोषणा ETM_TRCIDR1_ARCH_MAJOR(x)	\
	(((x) & ETM_TRCIDR1_ARCH_MAJOR_MASK) >> ETM_TRCIDR1_ARCH_MAJOR_SHIFT)
#घोषणा ETM_TRCIDR1_ARCH_MINOR_SHIFT	4
#घोषणा ETM_TRCIDR1_ARCH_MINOR_MASK	(0xfU << ETM_TRCIDR1_ARCH_MINOR_SHIFT)
#घोषणा ETM_TRCIDR1_ARCH_MINOR(x)	\
	(((x) & ETM_TRCIDR1_ARCH_MINOR_MASK) >> ETM_TRCIDR1_ARCH_MINOR_SHIFT)
#घोषणा ETM_TRCIDR1_ARCH_SHIFT		ETM_TRCIDR1_ARCH_MINOR_SHIFT
#घोषणा ETM_TRCIDR1_ARCH_MASK		\
	(ETM_TRCIDR1_ARCH_MAJOR_MASK | ETM_TRCIDR1_ARCH_MINOR_MASK)

#घोषणा ETM_TRCIDR1_ARCH_ETMv4		0x4

/*
 * Driver representation of the ETM architecture.
 * The version of an ETM component can be detected from
 *
 * TRCDEVARCH	- CoreSight architected रेजिस्टर
 *                - Bits[15:12] - Major version
 *                - Bits[19:16] - Minor version
 * TRCIDR1	- ETM architected रेजिस्टर
 *                - Bits[11:8] - Major version
 *                - Bits[7:4]  - Minor version
 * We must rely on TRCDEVARCH क्रम the version inक्रमmation,
 * however we करोn't want to अवरोध the support क्रम potential
 * old implementations which might not implement it. Thus
 * we fall back to TRCIDR1 अगर TRCDEVARCH is not implemented
 * क्रम memory mapped components.
 * Now to make certain decisions easier based on the version
 * we use an पूर्णांकernal representation of the version in the
 * driver, as follows :
 *
 * ETM_ARCH_VERSION[7:0], where :
 *      Bits[7:4] - Major version
 *      Bits[3:0] - Minro version
 */
#घोषणा ETM_ARCH_VERSION(major, minor)		\
	((((major) & 0xfU) << 4) | (((minor) & 0xfU)))
#घोषणा ETM_ARCH_MAJOR_VERSION(arch)	(((arch) >> 4) & 0xfU)
#घोषणा ETM_ARCH_MINOR_VERSION(arch)	((arch) & 0xfU)

#घोषणा ETM_ARCH_V4	ETM_ARCH_VERSION(4, 0)
#घोषणा ETM_ARCH_ETE	ETM_ARCH_VERSION(5, 0)

/* Interpretation of resource numbers change at ETM v4.3 architecture */
#घोषणा ETM_ARCH_V4_3	ETM_ARCH_VERSION(4, 3)

अटल अंतरभूत u8 eपंचांग_devarch_to_arch(u32 devarch)
अणु
	वापस ETM_ARCH_VERSION(ETM_DEVARCH_ARCHID_ARCH_VER(devarch),
				ETM_DEVARCH_REVISION(devarch));
पूर्ण

अटल अंतरभूत u8 eपंचांग_trcidr_to_arch(u32 trcidr1)
अणु
	वापस ETM_ARCH_VERSION(ETM_TRCIDR1_ARCH_MAJOR(trcidr1),
				ETM_TRCIDR1_ARCH_MINOR(trcidr1));
पूर्ण

क्रमागत eपंचांग_impdef_type अणु
	ETM4_IMPDEF_HISI_CORE_COMMIT,
	ETM4_IMPDEF_FEATURE_MAX,
पूर्ण;

/**
 * काष्ठा eपंचांगv4_config - configuration inक्रमmation related to an ETMv4
 * @mode:	Controls various modes supported by this ETM.
 * @pe_sel:	Controls which PE to trace.
 * @cfg:	Controls the tracing options.
 * @eventctrl0: Controls the tracing of arbitrary events.
 * @eventctrl1: Controls the behavior of the events that @event_ctrl0 selects.
 * @stallctl:	If functionality that prevents trace unit buffer overflows
 *		is available.
 * @ts_ctrl:	Controls the insertion of global बारtamps in the
 *		trace streams.
 * @syncfreq:	Controls how often trace synchronization requests occur.
 *		the TRCCCCTLR रेजिस्टर.
 * @ccctlr:	Sets the threshold value क्रम cycle counting.
 * @vinst_ctrl:	Controls inकाष्ठाion trace filtering.
 * @viiectlr:	Set or पढ़ो, the address range comparators.
 * @vissctlr:	Set, or पढ़ो, the single address comparators that control the
 *		ViewInst start-stop logic.
 * @vipcssctlr:	Set, or पढ़ो, which PE comparator inमाला_दो can control the
 *		ViewInst start-stop logic.
 * @seq_idx:	Sequencor index selector.
 * @seq_ctrl:	Control क्रम the sequencer state transition control रेजिस्टर.
 * @seq_rst:	Moves the sequencer to state 0 when a programmed event occurs.
 * @seq_state:	Set, or पढ़ो the sequencer state.
 * @cntr_idx:	Counter index seletor.
 * @cntrldvr:	Sets or वापसs the reload count value क्रम a counter.
 * @cntr_ctrl:	Controls the operation of a counter.
 * @cntr_val:	Sets or वापसs the value क्रम a counter.
 * @res_idx:	Resource index selector.
 * @res_ctrl:	Controls the selection of the resources in the trace unit.
 * @ss_idx:	Single-shot index selector.
 * @ss_ctrl:	Controls the corresponding single-shot comparator resource.
 * @ss_status:	The status of the corresponding single-shot comparator.
 * @ss_pe_cmp:	Selects the PE comparator inमाला_दो क्रम Single-shot control.
 * @addr_idx:	Address comparator index selector.
 * @addr_val:	Value क्रम address comparator.
 * @addr_acc:	Address comparator access type.
 * @addr_type:	Current status of the comparator रेजिस्टर.
 * @ctxid_idx:	Context ID index selector.
 * @ctxid_pid:	Value of the context ID comparator.
 * @ctxid_mask0:Context ID comparator mask क्रम comparator 0-3.
 * @ctxid_mask1:Context ID comparator mask क्रम comparator 4-7.
 * @vmid_idx:	VM ID index selector.
 * @vmid_val:	Value of the VM ID comparator.
 * @vmid_mask0:	VM ID comparator mask क्रम comparator 0-3.
 * @vmid_mask1:	VM ID comparator mask क्रम comparator 4-7.
 * @ext_inp:	External input selection.
 * @s_ex_level: Secure ELs where tracing is supported.
 */
काष्ठा eपंचांगv4_config अणु
	u32				mode;
	u32				pe_sel;
	u32				cfg;
	u32				eventctrl0;
	u32				eventctrl1;
	u32				stall_ctrl;
	u32				ts_ctrl;
	u32				syncfreq;
	u32				ccctlr;
	u32				bb_ctrl;
	u32				vinst_ctrl;
	u32				viiectlr;
	u32				vissctlr;
	u32				vipcssctlr;
	u8				seq_idx;
	u32				seq_ctrl[ETM_MAX_SEQ_STATES];
	u32				seq_rst;
	u32				seq_state;
	u8				cntr_idx;
	u32				cntrldvr[ETMv4_MAX_CNTR];
	u32				cntr_ctrl[ETMv4_MAX_CNTR];
	u32				cntr_val[ETMv4_MAX_CNTR];
	u8				res_idx;
	u32				res_ctrl[ETM_MAX_RES_SEL];
	u8				ss_idx;
	u32				ss_ctrl[ETM_MAX_SS_CMP];
	u32				ss_status[ETM_MAX_SS_CMP];
	u32				ss_pe_cmp[ETM_MAX_SS_CMP];
	u8				addr_idx;
	u64				addr_val[ETM_MAX_SINGLE_ADDR_CMP];
	u64				addr_acc[ETM_MAX_SINGLE_ADDR_CMP];
	u8				addr_type[ETM_MAX_SINGLE_ADDR_CMP];
	u8				ctxid_idx;
	u64				ctxid_pid[ETMv4_MAX_CTXID_CMP];
	u32				ctxid_mask0;
	u32				ctxid_mask1;
	u8				vmid_idx;
	u64				vmid_val[ETM_MAX_VMID_CMP];
	u32				vmid_mask0;
	u32				vmid_mask1;
	u32				ext_inp;
	u8				s_ex_level;
पूर्ण;

/**
 * काष्ठा eपंचांग4_save_state - state to be preserved when ETM is without घातer
 */
काष्ठा eपंचांगv4_save_state अणु
	u32	trcprgctlr;
	u32	trcprocselr;
	u32	trcconfigr;
	u32	trcauxctlr;
	u32	trceventctl0r;
	u32	trceventctl1r;
	u32	trcstallctlr;
	u32	trctsctlr;
	u32	trcsyncpr;
	u32	trcccctlr;
	u32	trcbbctlr;
	u32	trctraceidr;
	u32	trcqctlr;

	u32	trcvictlr;
	u32	trcviiectlr;
	u32	trcvissctlr;
	u32	trcvipcssctlr;
	u32	trcvdctlr;
	u32	trcvdsacctlr;
	u32	trcvdarcctlr;

	u32	trcseqevr[ETM_MAX_SEQ_STATES];
	u32	trcseqrstevr;
	u32	trcseqstr;
	u32	trcextinselr;
	u32	trccntrldvr[ETMv4_MAX_CNTR];
	u32	trccntctlr[ETMv4_MAX_CNTR];
	u32	trccntvr[ETMv4_MAX_CNTR];

	u32	trcrsctlr[ETM_MAX_RES_SEL];

	u32	trcssccr[ETM_MAX_SS_CMP];
	u32	trcsscsr[ETM_MAX_SS_CMP];
	u32	trcsspcicr[ETM_MAX_SS_CMP];

	u64	trcacvr[ETM_MAX_SINGLE_ADDR_CMP];
	u64	trcacatr[ETM_MAX_SINGLE_ADDR_CMP];
	u64	trccidcvr[ETMv4_MAX_CTXID_CMP];
	u64	trcvmidcvr[ETM_MAX_VMID_CMP];
	u32	trccidcctlr0;
	u32	trccidcctlr1;
	u32	trcvmidcctlr0;
	u32	trcvmidcctlr1;

	u32	trcclaimset;

	u32	cntr_val[ETMv4_MAX_CNTR];
	u32	seq_state;
	u32	vinst_ctrl;
	u32	ss_status[ETM_MAX_SS_CMP];

	u32	trcpdcr;
पूर्ण;

/**
 * काष्ठा eपंचांग4_drvdata - specअगरics associated to an ETM component
 * @base:       Memory mapped base address क्रम this component.
 * @csdev:      Component vitals needed by the framework.
 * @spinlock:   Only one at a समय pls.
 * @mode:	This tracer's mode, i.e sysFS, Perf or disabled.
 * @cpu:        The cpu this component is affined to.
 * @arch:       ETM architecture version.
 * @nr_pe:	The number of processing entity available क्रम tracing.
 * @nr_pe_cmp:	The number of processing entity comparator inमाला_दो that are
 *		available क्रम tracing.
 * @nr_addr_cmp:Number of pairs of address comparators available
 *		as found in ETMIDR4 0-3.
 * @nr_cntr:    Number of counters as found in ETMIDR5 bit 28-30.
 * @nr_ext_inp: Number of बाह्यal input.
 * @numcidc:	Number of contextID comparators.
 * @numvmidc:	Number of VMID comparators.
 * @nrseqstate: The number of sequencer states that are implemented.
 * @nr_event:	Indicates how many events the trace unit support.
 * @nr_resource:The number of resource selection pairs available क्रम tracing.
 * @nr_ss_cmp:	Number of single-shot comparator controls that are available.
 * @trcid:	value of the current ID क्रम this component.
 * @trcid_size: Indicates the trace ID width.
 * @ts_size:	Global बारtamp size field.
 * @ctxid_size:	Size of the context ID field to consider.
 * @vmid_size:	Size of the VM ID comparator to consider.
 * @ccsize:	Indicates the size of the cycle counter in bits.
 * @cciपंचांगin:	minimum value that can be programmed in
 * @s_ex_level:	In secure state, indicates whether inकाष्ठाion tracing is
 *		supported क्रम the corresponding Exception level.
 * @ns_ex_level:In non-secure state, indicates whether inकाष्ठाion tracing is
 *		supported क्रम the corresponding Exception level.
 * @sticky_enable: true अगर ETM base configuration has been करोne.
 * @boot_enable:True अगर we should start tracing at boot समय.
 * @os_unlock:  True अगर access to management रेजिस्टरs is allowed.
 * @instrp0:	Tracing of load and store inकाष्ठाions
 *		as P0 elements is supported.
 * @trcbb:	Indicates अगर the trace unit supports branch broadcast tracing.
 * @trccond:	If the trace unit supports conditional
 *		inकाष्ठाion tracing.
 * @retstack:	Indicates अगर the implementation supports a वापस stack.
 * @trccci:	Indicates अगर the trace unit supports cycle counting
 *		क्रम inकाष्ठाion.
 * @q_support:	Q element support अक्षरacteristics.
 * @trc_error:	Whether a trace unit can trace a प्रणाली
 *		error exception.
 * @syncpr:	Indicates अगर an implementation has a fixed
 *		synchronization period.
 * @stall_ctrl:	Enables trace unit functionality that prevents trace
 *		unit buffer overflows.
 * @sysstall:	Does the प्रणाली support stall control of the PE?
 * @nooverflow:	Indicate अगर overflow prevention is supported.
 * @atbtrig:	If the implementation can support ATB triggers
 * @lpoverride:	If the implementation can support low-घातer state over.
 * @trfc:	If the implementation supports Arm v8.4 trace filter controls.
 * @config:	काष्ठाure holding configuration parameters.
 * @save_state:	State to be preserved across घातer loss
 * @state_needs_restore: True when there is context to restore after PM निकास
 * @skip_घातer_up: Indicates अगर an implementation can skip घातering up
 *		   the trace unit.
 * @arch_features: Biपंचांगap of arch features of eपंचांगv4 devices.
 */
काष्ठा eपंचांगv4_drvdata अणु
	व्योम __iomem			*base;
	काष्ठा coresight_device		*csdev;
	spinlock_t			spinlock;
	local_t				mode;
	पूर्णांक				cpu;
	u8				arch;
	u8				nr_pe;
	u8				nr_pe_cmp;
	u8				nr_addr_cmp;
	u8				nr_cntr;
	u8				nr_ext_inp;
	u8				numcidc;
	u8				numvmidc;
	u8				nrseqstate;
	u8				nr_event;
	u8				nr_resource;
	u8				nr_ss_cmp;
	u8				trcid;
	u8				trcid_size;
	u8				ts_size;
	u8				ctxid_size;
	u8				vmid_size;
	u8				ccsize;
	u8				cciपंचांगin;
	u8				s_ex_level;
	u8				ns_ex_level;
	u8				q_support;
	u8				os_lock_model;
	bool				sticky_enable;
	bool				boot_enable;
	bool				os_unlock;
	bool				instrp0;
	bool				trcbb;
	bool				trccond;
	bool				retstack;
	bool				trccci;
	bool				trc_error;
	bool				syncpr;
	bool				stallctl;
	bool				sysstall;
	bool				nooverflow;
	bool				atbtrig;
	bool				lpoverride;
	bool				trfc;
	काष्ठा eपंचांगv4_config		config;
	काष्ठा eपंचांगv4_save_state		*save_state;
	bool				state_needs_restore;
	bool				skip_घातer_up;
	DECLARE_BITMAP(arch_features, ETM4_IMPDEF_FEATURE_MAX);
पूर्ण;

/* Address comparator access types */
क्रमागत eपंचांग_addr_acctype अणु
	ETM_INSTR_ADDR,
	ETM_DATA_LOAD_ADDR,
	ETM_DATA_STORE_ADDR,
	ETM_DATA_LOAD_STORE_ADDR,
पूर्ण;

/* Address comparator context types */
क्रमागत eपंचांग_addr_ctxtype अणु
	ETM_CTX_NONE,
	ETM_CTX_CTXID,
	ETM_CTX_VMID,
	ETM_CTX_CTXID_VMID,
पूर्ण;

बाह्य स्थिर काष्ठा attribute_group *coresight_eपंचांगv4_groups[];
व्योम eपंचांग4_config_trace_mode(काष्ठा eपंचांगv4_config *config);

u64 eपंचांग4x_sysreg_पढ़ो(u32 offset, bool _relaxed, bool _64bit);
व्योम eपंचांग4x_sysreg_ग_लिखो(u64 val, u32 offset, bool _relaxed, bool _64bit);

अटल अंतरभूत bool eपंचांग4x_is_ete(काष्ठा eपंचांगv4_drvdata *drvdata)
अणु
	वापस drvdata->arch >= ETM_ARCH_ETE;
पूर्ण
#पूर्ण_अगर
