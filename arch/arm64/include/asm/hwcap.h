<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_HWCAP_H
#घोषणा __ASM_HWCAP_H

#समावेश <uapi/यंत्र/hwcap.h>
#समावेश <यंत्र/cpufeature.h>

#घोषणा COMPAT_HWCAP_SWP	(1 << 0)
#घोषणा COMPAT_HWCAP_HALF	(1 << 1)
#घोषणा COMPAT_HWCAP_THUMB	(1 << 2)
#घोषणा COMPAT_HWCAP_26BIT	(1 << 3)
#घोषणा COMPAT_HWCAP_FAST_MULT	(1 << 4)
#घोषणा COMPAT_HWCAP_FPA	(1 << 5)
#घोषणा COMPAT_HWCAP_VFP	(1 << 6)
#घोषणा COMPAT_HWCAP_EDSP	(1 << 7)
#घोषणा COMPAT_HWCAP_JAVA	(1 << 8)
#घोषणा COMPAT_HWCAP_IWMMXT	(1 << 9)
#घोषणा COMPAT_HWCAP_CRUNCH	(1 << 10)
#घोषणा COMPAT_HWCAP_THUMBEE	(1 << 11)
#घोषणा COMPAT_HWCAP_NEON	(1 << 12)
#घोषणा COMPAT_HWCAP_VFPv3	(1 << 13)
#घोषणा COMPAT_HWCAP_VFPV3D16	(1 << 14)
#घोषणा COMPAT_HWCAP_TLS	(1 << 15)
#घोषणा COMPAT_HWCAP_VFPv4	(1 << 16)
#घोषणा COMPAT_HWCAP_IDIVA	(1 << 17)
#घोषणा COMPAT_HWCAP_IDIVT	(1 << 18)
#घोषणा COMPAT_HWCAP_IDIV	(COMPAT_HWCAP_IDIVA|COMPAT_HWCAP_IDIVT)
#घोषणा COMPAT_HWCAP_VFPD32	(1 << 19)
#घोषणा COMPAT_HWCAP_LPAE	(1 << 20)
#घोषणा COMPAT_HWCAP_EVTSTRM	(1 << 21)

#घोषणा COMPAT_HWCAP2_AES	(1 << 0)
#घोषणा COMPAT_HWCAP2_PMULL	(1 << 1)
#घोषणा COMPAT_HWCAP2_SHA1	(1 << 2)
#घोषणा COMPAT_HWCAP2_SHA2	(1 << 3)
#घोषणा COMPAT_HWCAP2_CRC32	(1 << 4)

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/log2.h>

/*
 * For userspace we represent hwcaps as a collection of HWCAPअणु,2पूर्ण_x bitfields
 * as described in uapi/यंत्र/hwcap.h. For the kernel we represent hwcaps as
 * natural numbers (in a single range of size MAX_CPU_FEATURES) defined here
 * with prefix KERNEL_HWCAP_ mapped to their HWCAPअणु,2पूर्ण_x counterpart.
 *
 * Hwcaps should be set and tested within the kernel via the
 * cpu_अणुset,haveपूर्ण_named_feature(feature) where feature is the unique suffix
 * of KERNEL_HWCAP_अणुfeatureपूर्ण.
 */
#घोषणा __khwcap_feature(x)		स्थिर_ilog2(HWCAP_ ## x)
#घोषणा KERNEL_HWCAP_FP			__khwcap_feature(FP)
#घोषणा KERNEL_HWCAP_ASIMD		__khwcap_feature(ASIMD)
#घोषणा KERNEL_HWCAP_EVTSTRM		__khwcap_feature(EVTSTRM)
#घोषणा KERNEL_HWCAP_AES		__khwcap_feature(AES)
#घोषणा KERNEL_HWCAP_PMULL		__khwcap_feature(PMULL)
#घोषणा KERNEL_HWCAP_SHA1		__khwcap_feature(SHA1)
#घोषणा KERNEL_HWCAP_SHA2		__khwcap_feature(SHA2)
#घोषणा KERNEL_HWCAP_CRC32		__khwcap_feature(CRC32)
#घोषणा KERNEL_HWCAP_ATOMICS		__khwcap_feature(ATOMICS)
#घोषणा KERNEL_HWCAP_FPHP		__khwcap_feature(FPHP)
#घोषणा KERNEL_HWCAP_ASIMDHP		__khwcap_feature(ASIMDHP)
#घोषणा KERNEL_HWCAP_CPUID		__khwcap_feature(CPUID)
#घोषणा KERNEL_HWCAP_ASIMDRDM		__khwcap_feature(ASIMDRDM)
#घोषणा KERNEL_HWCAP_JSCVT		__khwcap_feature(JSCVT)
#घोषणा KERNEL_HWCAP_FCMA		__khwcap_feature(FCMA)
#घोषणा KERNEL_HWCAP_LRCPC		__khwcap_feature(LRCPC)
#घोषणा KERNEL_HWCAP_DCPOP		__khwcap_feature(DCPOP)
#घोषणा KERNEL_HWCAP_SHA3		__khwcap_feature(SHA3)
#घोषणा KERNEL_HWCAP_SM3		__khwcap_feature(SM3)
#घोषणा KERNEL_HWCAP_SM4		__khwcap_feature(SM4)
#घोषणा KERNEL_HWCAP_ASIMDDP		__khwcap_feature(ASIMDDP)
#घोषणा KERNEL_HWCAP_SHA512		__khwcap_feature(SHA512)
#घोषणा KERNEL_HWCAP_SVE		__khwcap_feature(SVE)
#घोषणा KERNEL_HWCAP_ASIMDFHM		__khwcap_feature(ASIMDFHM)
#घोषणा KERNEL_HWCAP_DIT		__khwcap_feature(DIT)
#घोषणा KERNEL_HWCAP_USCAT		__khwcap_feature(USCAT)
#घोषणा KERNEL_HWCAP_ILRCPC		__khwcap_feature(ILRCPC)
#घोषणा KERNEL_HWCAP_FLAGM		__khwcap_feature(FLAGM)
#घोषणा KERNEL_HWCAP_SSBS		__khwcap_feature(SSBS)
#घोषणा KERNEL_HWCAP_SB			__khwcap_feature(SB)
#घोषणा KERNEL_HWCAP_PACA		__khwcap_feature(PACA)
#घोषणा KERNEL_HWCAP_PACG		__khwcap_feature(PACG)

#घोषणा __khwcap2_feature(x)		(स्थिर_ilog2(HWCAP2_ ## x) + 32)
#घोषणा KERNEL_HWCAP_DCPODP		__khwcap2_feature(DCPODP)
#घोषणा KERNEL_HWCAP_SVE2		__khwcap2_feature(SVE2)
#घोषणा KERNEL_HWCAP_SVEAES		__khwcap2_feature(SVEAES)
#घोषणा KERNEL_HWCAP_SVEPMULL		__khwcap2_feature(SVEPMULL)
#घोषणा KERNEL_HWCAP_SVEBITPERM		__khwcap2_feature(SVEBITPERM)
#घोषणा KERNEL_HWCAP_SVESHA3		__khwcap2_feature(SVESHA3)
#घोषणा KERNEL_HWCAP_SVESM4		__khwcap2_feature(SVESM4)
#घोषणा KERNEL_HWCAP_FLAGM2		__khwcap2_feature(FLAGM2)
#घोषणा KERNEL_HWCAP_FRINT		__khwcap2_feature(FRINT)
#घोषणा KERNEL_HWCAP_SVEI8MM		__khwcap2_feature(SVEI8MM)
#घोषणा KERNEL_HWCAP_SVEF32MM		__khwcap2_feature(SVEF32MM)
#घोषणा KERNEL_HWCAP_SVEF64MM		__khwcap2_feature(SVEF64MM)
#घोषणा KERNEL_HWCAP_SVEBF16		__khwcap2_feature(SVEBF16)
#घोषणा KERNEL_HWCAP_I8MM		__khwcap2_feature(I8MM)
#घोषणा KERNEL_HWCAP_BF16		__khwcap2_feature(BF16)
#घोषणा KERNEL_HWCAP_DGH		__khwcap2_feature(DGH)
#घोषणा KERNEL_HWCAP_RNG		__khwcap2_feature(RNG)
#घोषणा KERNEL_HWCAP_BTI		__khwcap2_feature(BTI)
#घोषणा KERNEL_HWCAP_MTE		__khwcap2_feature(MTE)

/*
 * This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this cpu supports.
 */
#घोषणा ELF_HWCAP		cpu_get_elf_hwcap()
#घोषणा ELF_HWCAP2		cpu_get_elf_hwcap2()

#अगर_घोषित CONFIG_COMPAT
#घोषणा COMPAT_ELF_HWCAP	(compat_elf_hwcap)
#घोषणा COMPAT_ELF_HWCAP2	(compat_elf_hwcap2)
बाह्य अचिन्हित पूर्णांक compat_elf_hwcap, compat_elf_hwcap2;
#पूर्ण_अगर

क्रमागत अणु
	CAP_HWCAP = 1,
#अगर_घोषित CONFIG_COMPAT
	CAP_COMPAT_HWCAP,
	CAP_COMPAT_HWCAP2,
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर
