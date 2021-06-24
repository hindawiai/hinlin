<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/include/यंत्र/vfp.h
 *
 * VFP रेजिस्टर definitions.
 * First, the standard VFP set.
 */

#अगर_अघोषित __ASM_VFP_H
#घोषणा __ASM_VFP_H

#अगर_अघोषित CONFIG_AS_VFP_VMRS_FPINST
#घोषणा FPSID			cr0
#घोषणा FPSCR			cr1
#घोषणा MVFR1			cr6
#घोषणा MVFR0			cr7
#घोषणा FPEXC			cr8
#घोषणा FPINST			cr9
#घोषणा FPINST2			cr10
#पूर्ण_अगर

/* FPSID bits */
#घोषणा FPSID_IMPLEMENTER_BIT	(24)
#घोषणा FPSID_IMPLEMENTER_MASK	(0xff << FPSID_IMPLEMENTER_BIT)
#घोषणा FPSID_SOFTWARE		(1<<23)
#घोषणा FPSID_FORMAT_BIT	(21)
#घोषणा FPSID_FORMAT_MASK	(0x3  << FPSID_FORMAT_BIT)
#घोषणा FPSID_NODOUBLE		(1<<20)
#घोषणा FPSID_ARCH_BIT		(16)
#घोषणा FPSID_ARCH_MASK		(0xF  << FPSID_ARCH_BIT)
#घोषणा FPSID_CPUID_ARCH_MASK	(0x7F  << FPSID_ARCH_BIT)
#घोषणा FPSID_PART_BIT		(8)
#घोषणा FPSID_PART_MASK		(0xFF << FPSID_PART_BIT)
#घोषणा FPSID_VARIANT_BIT	(4)
#घोषणा FPSID_VARIANT_MASK	(0xF  << FPSID_VARIANT_BIT)
#घोषणा FPSID_REV_BIT		(0)
#घोषणा FPSID_REV_MASK		(0xF  << FPSID_REV_BIT)

/* FPEXC bits */
#घोषणा FPEXC_EX		(1 << 31)
#घोषणा FPEXC_EN		(1 << 30)
#घोषणा FPEXC_DEX		(1 << 29)
#घोषणा FPEXC_FP2V		(1 << 28)
#घोषणा FPEXC_VV		(1 << 27)
#घोषणा FPEXC_TFV		(1 << 26)
#घोषणा FPEXC_LENGTH_BIT	(8)
#घोषणा FPEXC_LENGTH_MASK	(7 << FPEXC_LENGTH_BIT)
#घोषणा FPEXC_IDF		(1 << 7)
#घोषणा FPEXC_IXF		(1 << 4)
#घोषणा FPEXC_UFF		(1 << 3)
#घोषणा FPEXC_OFF		(1 << 2)
#घोषणा FPEXC_DZF		(1 << 1)
#घोषणा FPEXC_IOF		(1 << 0)
#घोषणा FPEXC_TRAP_MASK		(FPEXC_IDF|FPEXC_IXF|FPEXC_UFF|FPEXC_OFF|FPEXC_DZF|FPEXC_IOF)

/* FPSCR bits */
#घोषणा FPSCR_DEFAULT_न_अंक	(1<<25)
#घोषणा FPSCR_FLUSHTOZERO	(1<<24)
#घोषणा FPSCR_ROUND_NEAREST	(0<<22)
#घोषणा FPSCR_ROUND_PLUSINF	(1<<22)
#घोषणा FPSCR_ROUND_MINUSINF	(2<<22)
#घोषणा FPSCR_ROUND_TOZERO	(3<<22)
#घोषणा FPSCR_RMODE_BIT		(22)
#घोषणा FPSCR_RMODE_MASK	(3 << FPSCR_RMODE_BIT)
#घोषणा FPSCR_STRIDE_BIT	(20)
#घोषणा FPSCR_STRIDE_MASK	(3 << FPSCR_STRIDE_BIT)
#घोषणा FPSCR_LENGTH_BIT	(16)
#घोषणा FPSCR_LENGTH_MASK	(7 << FPSCR_LENGTH_BIT)
#घोषणा FPSCR_IOE		(1<<8)
#घोषणा FPSCR_DZE		(1<<9)
#घोषणा FPSCR_OFE		(1<<10)
#घोषणा FPSCR_UFE		(1<<11)
#घोषणा FPSCR_IXE		(1<<12)
#घोषणा FPSCR_IDE		(1<<15)
#घोषणा FPSCR_IOC		(1<<0)
#घोषणा FPSCR_DZC		(1<<1)
#घोषणा FPSCR_OFC		(1<<2)
#घोषणा FPSCR_UFC		(1<<3)
#घोषणा FPSCR_IXC		(1<<4)
#घोषणा FPSCR_IDC		(1<<7)

/* MVFR0 bits */
#घोषणा MVFR0_A_SIMD_BIT	(0)
#घोषणा MVFR0_A_SIMD_MASK	(0xf << MVFR0_A_SIMD_BIT)
#घोषणा MVFR0_SP_BIT		(4)
#घोषणा MVFR0_SP_MASK		(0xf << MVFR0_SP_BIT)
#घोषणा MVFR0_DP_BIT		(8)
#घोषणा MVFR0_DP_MASK		(0xf << MVFR0_DP_BIT)

/* Bit patterns क्रम decoding the packaged operation descriptors */
#घोषणा VFPOPDESC_LENGTH_BIT	(9)
#घोषणा VFPOPDESC_LENGTH_MASK	(0x07 << VFPOPDESC_LENGTH_BIT)
#घोषणा VFPOPDESC_UNUSED_BIT	(24)
#घोषणा VFPOPDESC_UNUSED_MASK	(0xFF << VFPOPDESC_UNUSED_BIT)
#घोषणा VFPOPDESC_OPDESC_MASK	(~(VFPOPDESC_LENGTH_MASK | VFPOPDESC_UNUSED_MASK))

#अगर_अघोषित __ASSEMBLY__
व्योम vfp_disable(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_VFP_H */
