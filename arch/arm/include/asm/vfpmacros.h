<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/include/यंत्र/vfpmacros.h
 *
 * Assembler-only file containing VFP macros and रेजिस्टर definitions.
 */
#समावेश <यंत्र/hwcap.h>

#समावेश <यंत्र/vfp.h>

#अगर_घोषित CONFIG_AS_VFP_VMRS_FPINST
	.macro	VFPFMRX, rd, sysreg, cond
	vmrs\cond	\लd, \sysreg
	.endm

	.macro	VFPFMXR, sysreg, rd, cond
	vmsr\cond	\sysreg, \लd
	.endm
#अन्यथा
	@ Macros to allow building with old toolkits (with no VFP support)
	.macro	VFPFMRX, rd, sysreg, cond
	MRC\cond	p10, 7, \लd, \sysreg, cr0, 0	@ FMRX	\लd, \sysreg
	.endm

	.macro	VFPFMXR, sysreg, rd, cond
	MCR\cond	p10, 7, \लd, \sysreg, cr0, 0	@ FMXR	\sysreg, \लd
	.endm
#पूर्ण_अगर

	@ पढ़ो all the working रेजिस्टरs back पूर्णांकo the VFP
	.macro	VFPFLDMIA, base, पंचांगp
	.fpu	vfpv2
#अगर __LINUX_ARM_ARCH__ < 6
	fldmiax	\मase!, अणुd0-d15पूर्ण
#अन्यथा
	vldmia	\मase!, अणुd0-d15पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_VFPv3
	.fpu	vfpv3
#अगर __LINUX_ARM_ARCH__ <= 6
	ldr	\टmp, =elf_hwcap		    @ may not have MVFR regs
	ldr	\टmp, [\टmp, #0]
	tst	\टmp, #HWCAP_VFPD32
	vldmiane \मase!, अणुd16-d31पूर्ण
	addeq	\मase, \मase, #32*4		    @ step over unused रेजिस्टर space
#अन्यथा
	VFPFMRX	\टmp, MVFR0			    @ Media and VFP Feature Register 0
	and	\टmp, \टmp, #MVFR0_A_SIMD_MASK	    @ A_SIMD field
	cmp	\टmp, #2			    @ 32 x 64bit रेजिस्टरs?
	vldmiaeq \मase!, अणुd16-d31पूर्ण
	addne	\मase, \मase, #32*4		    @ step over unused रेजिस्टर space
#पूर्ण_अगर
#पूर्ण_अगर
	.endm

	@ ग_लिखो all the working रेजिस्टरs out of the VFP
	.macro	VFPFSTMIA, base, पंचांगp
#अगर __LINUX_ARM_ARCH__ < 6
	fsपंचांगiax	\मase!, अणुd0-d15पूर्ण
#अन्यथा
	vsपंचांगia	\मase!, अणुd0-d15पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_VFPv3
	.fpu	vfpv3
#अगर __LINUX_ARM_ARCH__ <= 6
	ldr	\टmp, =elf_hwcap		    @ may not have MVFR regs
	ldr	\टmp, [\टmp, #0]
	tst	\टmp, #HWCAP_VFPD32
	vsपंचांगiane \मase!, अणुd16-d31पूर्ण
	addeq	\मase, \मase, #32*4		    @ step over unused रेजिस्टर space
#अन्यथा
	VFPFMRX	\टmp, MVFR0			    @ Media and VFP Feature Register 0
	and	\टmp, \टmp, #MVFR0_A_SIMD_MASK	    @ A_SIMD field
	cmp	\टmp, #2			    @ 32 x 64bit रेजिस्टरs?
	vsपंचांगiaeq \मase!, अणुd16-d31पूर्ण
	addne	\मase, \मase, #32*4		    @ step over unused रेजिस्टर space
#पूर्ण_अगर
#पूर्ण_अगर
	.endm
