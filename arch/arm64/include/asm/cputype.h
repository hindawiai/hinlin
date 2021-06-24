<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_CPUTYPE_H
#घोषणा __ASM_CPUTYPE_H

#घोषणा INVALID_HWID		अच_दीर्घ_उच्च

#घोषणा MPIDR_UP_BITMASK	(0x1 << 30)
#घोषणा MPIDR_MT_BITMASK	(0x1 << 24)
#घोषणा MPIDR_HWID_BITMASK	UL(0xff00ffffff)

#घोषणा MPIDR_LEVEL_BITS_SHIFT	3
#घोषणा MPIDR_LEVEL_BITS	(1 << MPIDR_LEVEL_BITS_SHIFT)
#घोषणा MPIDR_LEVEL_MASK	((1 << MPIDR_LEVEL_BITS) - 1)

#घोषणा MPIDR_LEVEL_SHIFT(level) \
	(((1 << level) >> 1) << MPIDR_LEVEL_BITS_SHIFT)

#घोषणा MPIDR_AFFINITY_LEVEL(mpidr, level) \
	((mpidr >> MPIDR_LEVEL_SHIFT(level)) & MPIDR_LEVEL_MASK)

#घोषणा MIDR_REVISION_MASK	0xf
#घोषणा MIDR_REVISION(midr)	((midr) & MIDR_REVISION_MASK)
#घोषणा MIDR_PARTNUM_SHIFT	4
#घोषणा MIDR_PARTNUM_MASK	(0xfff << MIDR_PARTNUM_SHIFT)
#घोषणा MIDR_PARTNUM(midr)	\
	(((midr) & MIDR_PARTNUM_MASK) >> MIDR_PARTNUM_SHIFT)
#घोषणा MIDR_ARCHITECTURE_SHIFT	16
#घोषणा MIDR_ARCHITECTURE_MASK	(0xf << MIDR_ARCHITECTURE_SHIFT)
#घोषणा MIDR_ARCHITECTURE(midr)	\
	(((midr) & MIDR_ARCHITECTURE_MASK) >> MIDR_ARCHITECTURE_SHIFT)
#घोषणा MIDR_VARIANT_SHIFT	20
#घोषणा MIDR_VARIANT_MASK	(0xf << MIDR_VARIANT_SHIFT)
#घोषणा MIDR_VARIANT(midr)	\
	(((midr) & MIDR_VARIANT_MASK) >> MIDR_VARIANT_SHIFT)
#घोषणा MIDR_IMPLEMENTOR_SHIFT	24
#घोषणा MIDR_IMPLEMENTOR_MASK	(0xff << MIDR_IMPLEMENTOR_SHIFT)
#घोषणा MIDR_IMPLEMENTOR(midr)	\
	(((midr) & MIDR_IMPLEMENTOR_MASK) >> MIDR_IMPLEMENTOR_SHIFT)

#घोषणा MIDR_CPU_MODEL(imp, partnum) \
	(((imp)			<< MIDR_IMPLEMENTOR_SHIFT) | \
	(0xf			<< MIDR_ARCHITECTURE_SHIFT) | \
	((partnum)		<< MIDR_PARTNUM_SHIFT))

#घोषणा MIDR_CPU_VAR_REV(var, rev) \
	(((var)	<< MIDR_VARIANT_SHIFT) | (rev))

#घोषणा MIDR_CPU_MODEL_MASK (MIDR_IMPLEMENTOR_MASK | MIDR_PARTNUM_MASK | \
			     MIDR_ARCHITECTURE_MASK)

#घोषणा ARM_CPU_IMP_ARM			0x41
#घोषणा ARM_CPU_IMP_APM			0x50
#घोषणा ARM_CPU_IMP_CAVIUM		0x43
#घोषणा ARM_CPU_IMP_BRCM		0x42
#घोषणा ARM_CPU_IMP_QCOM		0x51
#घोषणा ARM_CPU_IMP_NVIDIA		0x4E
#घोषणा ARM_CPU_IMP_FUJITSU		0x46
#घोषणा ARM_CPU_IMP_HISI		0x48
#घोषणा ARM_CPU_IMP_APPLE		0x61

#घोषणा ARM_CPU_PART_AEM_V8		0xD0F
#घोषणा ARM_CPU_PART_FOUNDATION		0xD00
#घोषणा ARM_CPU_PART_CORTEX_A57		0xD07
#घोषणा ARM_CPU_PART_CORTEX_A72		0xD08
#घोषणा ARM_CPU_PART_CORTEX_A53		0xD03
#घोषणा ARM_CPU_PART_CORTEX_A73		0xD09
#घोषणा ARM_CPU_PART_CORTEX_A75		0xD0A
#घोषणा ARM_CPU_PART_CORTEX_A35		0xD04
#घोषणा ARM_CPU_PART_CORTEX_A55		0xD05
#घोषणा ARM_CPU_PART_CORTEX_A76		0xD0B
#घोषणा ARM_CPU_PART_NEOVERSE_N1	0xD0C
#घोषणा ARM_CPU_PART_CORTEX_A77		0xD0D

#घोषणा APM_CPU_PART_POTENZA		0x000

#घोषणा CAVIUM_CPU_PART_THUNDERX	0x0A1
#घोषणा CAVIUM_CPU_PART_THUNDERX_81XX	0x0A2
#घोषणा CAVIUM_CPU_PART_THUNDERX_83XX	0x0A3
#घोषणा CAVIUM_CPU_PART_THUNDERX2	0x0AF

#घोषणा BRCM_CPU_PART_BRAHMA_B53	0x100
#घोषणा BRCM_CPU_PART_VULCAN		0x516

#घोषणा QCOM_CPU_PART_FALKOR_V1		0x800
#घोषणा QCOM_CPU_PART_FALKOR		0xC00
#घोषणा QCOM_CPU_PART_KRYO		0x200
#घोषणा QCOM_CPU_PART_KRYO_2XX_GOLD	0x800
#घोषणा QCOM_CPU_PART_KRYO_2XX_SILVER	0x801
#घोषणा QCOM_CPU_PART_KRYO_3XX_SILVER	0x803
#घोषणा QCOM_CPU_PART_KRYO_4XX_GOLD	0x804
#घोषणा QCOM_CPU_PART_KRYO_4XX_SILVER	0x805

#घोषणा NVIDIA_CPU_PART_DENVER		0x003
#घोषणा NVIDIA_CPU_PART_CARMEL		0x004

#घोषणा FUJITSU_CPU_PART_A64FX		0x001

#घोषणा HISI_CPU_PART_TSV110		0xD01

#घोषणा APPLE_CPU_PART_M1_ICESTORM	0x022
#घोषणा APPLE_CPU_PART_M1_FIRESTORM	0x023

#घोषणा MIDR_CORTEX_A53 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A53)
#घोषणा MIDR_CORTEX_A57 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A57)
#घोषणा MIDR_CORTEX_A72 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A72)
#घोषणा MIDR_CORTEX_A73 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A73)
#घोषणा MIDR_CORTEX_A75 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A75)
#घोषणा MIDR_CORTEX_A35 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A35)
#घोषणा MIDR_CORTEX_A55 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A55)
#घोषणा MIDR_CORTEX_A76	MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A76)
#घोषणा MIDR_NEOVERSE_N1 MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_NEOVERSE_N1)
#घोषणा MIDR_CORTEX_A77	MIDR_CPU_MODEL(ARM_CPU_IMP_ARM, ARM_CPU_PART_CORTEX_A77)
#घोषणा MIDR_THUNDERX	MIDR_CPU_MODEL(ARM_CPU_IMP_CAVIUM, CAVIUM_CPU_PART_THUNDERX)
#घोषणा MIDR_THUNDERX_81XX MIDR_CPU_MODEL(ARM_CPU_IMP_CAVIUM, CAVIUM_CPU_PART_THUNDERX_81XX)
#घोषणा MIDR_THUNDERX_83XX MIDR_CPU_MODEL(ARM_CPU_IMP_CAVIUM, CAVIUM_CPU_PART_THUNDERX_83XX)
#घोषणा MIDR_CAVIUM_THUNDERX2 MIDR_CPU_MODEL(ARM_CPU_IMP_CAVIUM, CAVIUM_CPU_PART_THUNDERX2)
#घोषणा MIDR_BRAHMA_B53 MIDR_CPU_MODEL(ARM_CPU_IMP_BRCM, BRCM_CPU_PART_BRAHMA_B53)
#घोषणा MIDR_BRCM_VULCAN MIDR_CPU_MODEL(ARM_CPU_IMP_BRCM, BRCM_CPU_PART_VULCAN)
#घोषणा MIDR_QCOM_FALKOR_V1 MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_FALKOR_V1)
#घोषणा MIDR_QCOM_FALKOR MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_FALKOR)
#घोषणा MIDR_QCOM_KRYO MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_KRYO)
#घोषणा MIDR_QCOM_KRYO_2XX_GOLD MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_KRYO_2XX_GOLD)
#घोषणा MIDR_QCOM_KRYO_2XX_SILVER MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_KRYO_2XX_SILVER)
#घोषणा MIDR_QCOM_KRYO_3XX_SILVER MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_KRYO_3XX_SILVER)
#घोषणा MIDR_QCOM_KRYO_4XX_GOLD MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_KRYO_4XX_GOLD)
#घोषणा MIDR_QCOM_KRYO_4XX_SILVER MIDR_CPU_MODEL(ARM_CPU_IMP_QCOM, QCOM_CPU_PART_KRYO_4XX_SILVER)
#घोषणा MIDR_NVIDIA_DENVER MIDR_CPU_MODEL(ARM_CPU_IMP_NVIDIA, NVIDIA_CPU_PART_DENVER)
#घोषणा MIDR_NVIDIA_CARMEL MIDR_CPU_MODEL(ARM_CPU_IMP_NVIDIA, NVIDIA_CPU_PART_CARMEL)
#घोषणा MIDR_FUJITSU_A64FX MIDR_CPU_MODEL(ARM_CPU_IMP_FUJITSU, FUJITSU_CPU_PART_A64FX)
#घोषणा MIDR_HISI_TSV110 MIDR_CPU_MODEL(ARM_CPU_IMP_HISI, HISI_CPU_PART_TSV110)
#घोषणा MIDR_APPLE_M1_ICESTORM MIDR_CPU_MODEL(ARM_CPU_IMP_APPLE, APPLE_CPU_PART_M1_ICESTORM)
#घोषणा MIDR_APPLE_M1_FIRESTORM MIDR_CPU_MODEL(ARM_CPU_IMP_APPLE, APPLE_CPU_PART_M1_FIRESTORM)

/* Fujitsu Erratum 010001 affects A64FX 1.0 and 1.1, (v0r0 and v1r0) */
#घोषणा MIDR_FUJITSU_ERRATUM_010001		MIDR_FUJITSU_A64FX
#घोषणा MIDR_FUJITSU_ERRATUM_010001_MASK	(~MIDR_CPU_VAR_REV(1, 0))
#घोषणा TCR_CLEAR_FUJITSU_ERRATUM_010001	(TCR_NFD1 | TCR_NFD0)

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/sysreg.h>

#घोषणा पढ़ो_cpuid(reg)			पढ़ो_sysreg_s(SYS_ ## reg)

/*
 * Represent a range of MIDR values क्रम a given CPU model and a
 * range of variant/revision values.
 *
 * @model	- CPU model as defined by MIDR_CPU_MODEL
 * @rv_min	- Minimum value क्रम the revision/variant as defined by
 *		  MIDR_CPU_VAR_REV
 * @rv_max	- Maximum value क्रम the variant/revision क्रम the range.
 */
काष्ठा midr_range अणु
	u32 model;
	u32 rv_min;
	u32 rv_max;
पूर्ण;

#घोषणा MIDR_RANGE(m, v_min, r_min, v_max, r_max)		\
	अणु							\
		.model = m,					\
		.rv_min = MIDR_CPU_VAR_REV(v_min, r_min),	\
		.rv_max = MIDR_CPU_VAR_REV(v_max, r_max),	\
	पूर्ण

#घोषणा MIDR_REV_RANGE(m, v, r_min, r_max) MIDR_RANGE(m, v, r_min, v, r_max)
#घोषणा MIDR_REV(m, v, r) MIDR_RANGE(m, v, r, v, r)
#घोषणा MIDR_ALL_VERSIONS(m) MIDR_RANGE(m, 0, 0, 0xf, 0xf)

अटल अंतरभूत bool midr_is_cpu_model_range(u32 midr, u32 model, u32 rv_min,
					   u32 rv_max)
अणु
	u32 _model = midr & MIDR_CPU_MODEL_MASK;
	u32 rv = midr & (MIDR_REVISION_MASK | MIDR_VARIANT_MASK);

	वापस _model == model && rv >= rv_min && rv <= rv_max;
पूर्ण

अटल अंतरभूत bool is_midr_in_range(u32 midr, काष्ठा midr_range स्थिर *range)
अणु
	वापस midr_is_cpu_model_range(midr, range->model,
				       range->rv_min, range->rv_max);
पूर्ण

अटल अंतरभूत bool
is_midr_in_range_list(u32 midr, काष्ठा midr_range स्थिर *ranges)
अणु
	जबतक (ranges->model)
		अगर (is_midr_in_range(midr, ranges++))
			वापस true;
	वापस false;
पूर्ण

/*
 * The CPU ID never changes at run समय, so we might as well tell the
 * compiler that it's स्थिरant.  Use this function to पढ़ो the CPU ID
 * rather than directly पढ़ोing processor_id or पढ़ो_cpuid() directly.
 */
अटल अंतरभूत u32 __attribute_स्थिर__ पढ़ो_cpuid_id(व्योम)
अणु
	वापस पढ़ो_cpuid(MIDR_EL1);
पूर्ण

अटल अंतरभूत u64 __attribute_स्थिर__ पढ़ो_cpuid_mpidr(व्योम)
अणु
	वापस पढ़ो_cpuid(MPIDR_EL1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_implementor(व्योम)
अणु
	वापस MIDR_IMPLEMENTOR(पढ़ो_cpuid_id());
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__ पढ़ो_cpuid_part_number(व्योम)
अणु
	वापस MIDR_PARTNUM(पढ़ो_cpuid_id());
पूर्ण

अटल अंतरभूत u32 __attribute_स्थिर__ पढ़ो_cpuid_cachetype(व्योम)
अणु
	वापस पढ़ो_cpuid(CTR_EL0);
पूर्ण
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
