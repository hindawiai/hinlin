<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_CPUTYPE_H
#घोषणा __ASM_ARM_CPUTYPE_H

#घोषणा CPUID_ID	0
#घोषणा CPUID_CACHETYPE	1
#घोषणा CPUID_TCM	2
#घोषणा CPUID_TLBTYPE	3
#घोषणा CPUID_MPUIR	4
#घोषणा CPUID_MPIDR	5
#घोषणा CPUID_REVIDR	6

#अगर_घोषित CONFIG_CPU_V7M
#घोषणा CPUID_EXT_PFR0	0x40
#घोषणा CPUID_EXT_PFR1	0x44
#घोषणा CPUID_EXT_DFR0	0x48
#घोषणा CPUID_EXT_AFR0	0x4c
#घोषणा CPUID_EXT_MMFR0	0x50
#घोषणा CPUID_EXT_MMFR1	0x54
#घोषणा CPUID_EXT_MMFR2	0x58
#घोषणा CPUID_EXT_MMFR3	0x5c
#घोषणा CPUID_EXT_ISAR0	0x60
#घोषणा CPUID_EXT_ISAR1	0x64
#घोषणा CPUID_EXT_ISAR2	0x68
#घोषणा CPUID_EXT_ISAR3	0x6c
#घोषणा CPUID_EXT_ISAR4	0x70
#घोषणा CPUID_EXT_ISAR5	0x74
#अन्यथा
#घोषणा CPUID_EXT_PFR0	"c1, 0"
#घोषणा CPUID_EXT_PFR1	"c1, 1"
#घोषणा CPUID_EXT_DFR0	"c1, 2"
#घोषणा CPUID_EXT_AFR0	"c1, 3"
#घोषणा CPUID_EXT_MMFR0	"c1, 4"
#घोषणा CPUID_EXT_MMFR1	"c1, 5"
#घोषणा CPUID_EXT_MMFR2	"c1, 6"
#घोषणा CPUID_EXT_MMFR3	"c1, 7"
#घोषणा CPUID_EXT_ISAR0	"c2, 0"
#घोषणा CPUID_EXT_ISAR1	"c2, 1"
#घोषणा CPUID_EXT_ISAR2	"c2, 2"
#घोषणा CPUID_EXT_ISAR3	"c2, 3"
#घोषणा CPUID_EXT_ISAR4	"c2, 4"
#घोषणा CPUID_EXT_ISAR5	"c2, 5"
#पूर्ण_अगर

#घोषणा MPIDR_SMP_BITMASK (0x3 << 30)
#घोषणा MPIDR_SMP_VALUE (0x2 << 30)

#घोषणा MPIDR_MT_BITMASK (0x1 << 24)

#घोषणा MPIDR_HWID_BITMASK 0xFFFFFF

#घोषणा MPIDR_INVALID (~MPIDR_HWID_BITMASK)

#घोषणा MPIDR_LEVEL_BITS 8
#घोषणा MPIDR_LEVEL_MASK ((1 << MPIDR_LEVEL_BITS) - 1)
#घोषणा MPIDR_LEVEL_SHIFT(level) (MPIDR_LEVEL_BITS * level)

#घोषणा MPIDR_AFFINITY_LEVEL(mpidr, level) \
	((mpidr >> (MPIDR_LEVEL_BITS * level)) & MPIDR_LEVEL_MASK)

#घोषणा ARM_CPU_IMP_ARM			0x41
#घोषणा ARM_CPU_IMP_BRCM		0x42
#घोषणा ARM_CPU_IMP_DEC			0x44
#घोषणा ARM_CPU_IMP_INTEL		0x69

/* ARM implemented processors */
#घोषणा ARM_CPU_PART_ARM1136		0x4100b360
#घोषणा ARM_CPU_PART_ARM1156		0x4100b560
#घोषणा ARM_CPU_PART_ARM1176		0x4100b760
#घोषणा ARM_CPU_PART_ARM11MPCORE	0x4100b020
#घोषणा ARM_CPU_PART_CORTEX_A8		0x4100c080
#घोषणा ARM_CPU_PART_CORTEX_A9		0x4100c090
#घोषणा ARM_CPU_PART_CORTEX_A5		0x4100c050
#घोषणा ARM_CPU_PART_CORTEX_A7		0x4100c070
#घोषणा ARM_CPU_PART_CORTEX_A12		0x4100c0d0
#घोषणा ARM_CPU_PART_CORTEX_A17		0x4100c0e0
#घोषणा ARM_CPU_PART_CORTEX_A15		0x4100c0f0
#घोषणा ARM_CPU_PART_CORTEX_A53		0x4100d030
#घोषणा ARM_CPU_PART_CORTEX_A57		0x4100d070
#घोषणा ARM_CPU_PART_CORTEX_A72		0x4100d080
#घोषणा ARM_CPU_PART_CORTEX_A73		0x4100d090
#घोषणा ARM_CPU_PART_CORTEX_A75		0x4100d0a0
#घोषणा ARM_CPU_PART_MASK		0xff00fff0

/* Broadcom implemented processors */
#घोषणा ARM_CPU_PART_BRAHMA_B15		0x420000f0
#घोषणा ARM_CPU_PART_BRAHMA_B53		0x42001000

/* DEC implemented cores */
#घोषणा ARM_CPU_PART_SA1100		0x4400a110

/* Intel implemented cores */
#घोषणा ARM_CPU_PART_SA1110		0x6900b110
#घोषणा ARM_CPU_REV_SA1110_A0		0
#घोषणा ARM_CPU_REV_SA1110_B0		4
#घोषणा ARM_CPU_REV_SA1110_B1		5
#घोषणा ARM_CPU_REV_SA1110_B2		6
#घोषणा ARM_CPU_REV_SA1110_B4		8

#घोषणा ARM_CPU_XSCALE_ARCH_MASK	0xe000
#घोषणा ARM_CPU_XSCALE_ARCH_V1		0x2000
#घोषणा ARM_CPU_XSCALE_ARCH_V2		0x4000
#घोषणा ARM_CPU_XSCALE_ARCH_V3		0x6000

/* Qualcomm implemented cores */
#घोषणा ARM_CPU_PART_SCORPION		0x510002d0

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/stringअगरy.h>
#समावेश <linux/kernel.h>

बाह्य अचिन्हित पूर्णांक processor_id;
काष्ठा proc_info_list *lookup_processor(u32 midr);

#अगर_घोषित CONFIG_CPU_CP15
#घोषणा पढ़ो_cpuid(reg)							\
	(अणु								\
		अचिन्हित पूर्णांक __val;					\
		यंत्र("mrc	p15, 0, %0, c0, c0, " __stringअगरy(reg)	\
		    : "=r" (__val)					\
		    :							\
		    : "cc");						\
		__val;							\
	पूर्ण)

/*
 * The memory clobber prevents gcc 4.5 from reordering the mrc beक्रमe
 * any is_smp() tests, which can cause undefined inकाष्ठाion पातs on
 * ARM1136 r0 due to the missing extended CP15 रेजिस्टरs.
 */
#घोषणा पढ़ो_cpuid_ext(ext_reg)						\
	(अणु								\
		अचिन्हित पूर्णांक __val;					\
		यंत्र("mrc	p15, 0, %0, c0, " ext_reg		\
		    : "=r" (__val)					\
		    :							\
		    : "memory");					\
		__val;							\
	पूर्ण)

#या_अगर defined(CONFIG_CPU_V7M)

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/v7m.h>

#घोषणा पढ़ो_cpuid(reg)							\
	(अणु								\
		WARN_ON_ONCE(1);					\
		0;							\
	पूर्ण)

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_ext(अचिन्हित offset)
अणु
	वापस पढ़ोl(BASEADDR_V7M_SCB + offset);
पूर्ण

#अन्यथा /* अगरdef CONFIG_CPU_CP15 / elअगर defined (CONFIG_CPU_V7M) */

/*
 * पढ़ो_cpuid and पढ़ो_cpuid_ext should only ever be called on machines that
 * have cp15 so warn on other usages.
 */
#घोषणा पढ़ो_cpuid(reg)							\
	(अणु								\
		WARN_ON_ONCE(1);					\
		0;							\
	पूर्ण)

#घोषणा पढ़ो_cpuid_ext(reg) पढ़ो_cpuid(reg)

#पूर्ण_अगर /* अगरdef CONFIG_CPU_CP15 / अन्यथा */

#अगर_घोषित CONFIG_CPU_CP15
/*
 * The CPU ID never changes at run समय, so we might as well tell the
 * compiler that it's स्थिरant.  Use this function to पढ़ो the CPU ID
 * rather than directly पढ़ोing processor_id or पढ़ो_cpuid() directly.
 */
अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_id(व्योम)
अणु
	वापस पढ़ो_cpuid(CPUID_ID);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_cachetype(व्योम)
अणु
	वापस पढ़ो_cpuid(CPUID_CACHETYPE);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_mputype(व्योम)
अणु
	वापस पढ़ो_cpuid(CPUID_MPUIR);
पूर्ण

#या_अगर defined(CONFIG_CPU_V7M)

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_id(व्योम)
अणु
	वापस पढ़ोl(BASEADDR_V7M_SCB + V7M_SCB_CPUID);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_cachetype(व्योम)
अणु
	वापस पढ़ोl(BASEADDR_V7M_SCB + V7M_SCB_CTR);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_mputype(व्योम)
अणु
	वापस पढ़ोl(BASEADDR_V7M_SCB + MPU_TYPE);
पूर्ण

#अन्यथा /* अगरdef CONFIG_CPU_CP15 / elअगर defined(CONFIG_CPU_V7M) */

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_id(व्योम)
अणु
	वापस processor_id;
पूर्ण

#पूर्ण_अगर /* अगरdef CONFIG_CPU_CP15 / अन्यथा */

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_implementor(व्योम)
अणु
	वापस (पढ़ो_cpuid_id() & 0xFF000000) >> 24;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_revision(व्योम)
अणु
	वापस पढ़ो_cpuid_id() & 0x0000000f;
पूर्ण

/*
 * The CPU part number is meaningless without referring to the CPU
 * implementer: implementers are मुक्त to define their own part numbers
 * which are permitted to clash with other implementer part numbers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_part(व्योम)
अणु
	वापस पढ़ो_cpuid_id() & ARM_CPU_PART_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ __deprecated पढ़ो_cpuid_part_number(व्योम)
अणु
	वापस पढ़ो_cpuid_id() & 0xFFF0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ xscale_cpu_arch_version(व्योम)
अणु
	वापस पढ़ो_cpuid_id() & ARM_CPU_XSCALE_ARCH_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_tcmstatus(व्योम)
अणु
	वापस पढ़ो_cpuid(CPUID_TCM);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_mpidr(व्योम)
अणु
	वापस पढ़ो_cpuid(CPUID_MPIDR);
पूर्ण

/* StrongARM-11x0 CPUs */
#घोषणा cpu_is_sa1100() (पढ़ो_cpuid_part() == ARM_CPU_PART_SA1100)
#घोषणा cpu_is_sa1110() (पढ़ो_cpuid_part() == ARM_CPU_PART_SA1110)

/*
 * Intel's XScale3 core supports some v6 features (supersections, L2)
 * but advertises itself as v5 as it करोes not support the v6 ISA.  For
 * this reason, we need a way to explicitly test क्रम this type of CPU.
 */
#अगर_अघोषित CONFIG_CPU_XSC3
#घोषणा cpu_is_xsc3()	0
#अन्यथा
अटल अंतरभूत पूर्णांक cpu_is_xsc3(व्योम)
अणु
	अचिन्हित पूर्णांक id;
	id = पढ़ो_cpuid_id() & 0xffffe000;
	/* It covers both Intel ID and Marvell ID */
	अगर ((id == 0x69056000) || (id == 0x56056000))
		वापस 1;

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर !defined(CONFIG_CPU_XSCALE) && !defined(CONFIG_CPU_XSC3) && \
    !defined(CONFIG_CPU_MOHAWK)
#घोषणा	cpu_is_xscale_family() 0
#अन्यथा
अटल अंतरभूत पूर्णांक cpu_is_xscale_family(व्योम)
अणु
	अचिन्हित पूर्णांक id;
	id = पढ़ो_cpuid_id() & 0xffffe000;

	चयन (id) अणु
	हाल 0x69052000: /* Intel XScale 1 */
	हाल 0x69054000: /* Intel XScale 2 */
	हाल 0x69056000: /* Intel XScale 3 */
	हाल 0x56056000: /* Marvell XScale 3 */
	हाल 0x56158000: /* Marvell Mohawk */
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Marvell's PJ4 and PJ4B cores are based on V7 version,
 * but require a specical sequence क्रम enabling coprocessors.
 * For this reason, we need a way to distinguish them.
 */
#अगर defined(CONFIG_CPU_PJ4) || defined(CONFIG_CPU_PJ4B)
अटल अंतरभूत पूर्णांक cpu_is_pj4(व्योम)
अणु
	अचिन्हित पूर्णांक id;

	id = पढ़ो_cpuid_id();
	अगर ((id & 0xff0fff00) == 0x560f5800)
		वापस 1;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा cpu_is_pj4()	0
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक __attribute_स्थिर__ cpuid_feature_extract_field(u32 features,
								  पूर्णांक field)
अणु
	पूर्णांक feature = (features >> field) & 15;

	/* feature रेजिस्टरs are चिन्हित values */
	अगर (feature > 7)
		feature -= 16;

	वापस feature;
पूर्ण

#घोषणा cpuid_feature_extract(reg, field) \
	cpuid_feature_extract_field(पढ़ो_cpuid_ext(reg), field)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
