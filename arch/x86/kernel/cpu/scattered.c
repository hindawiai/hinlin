<शैली गुरु>
/*
 *	Routines to identअगरy additional cpu features that are scattered in
 *	cpuid space.
 */
#समावेश <linux/cpu.h>

#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/processor.h>

#समावेश "cpu.h"

काष्ठा cpuid_bit अणु
	u16 feature;
	u8 reg;
	u8 bit;
	u32 level;
	u32 sub_leaf;
पूर्ण;

/*
 * Please keep the leaf sorted by cpuid_bit.level क्रम faster search.
 * X86_FEATURE_MBA is supported by both Intel and AMD. But the CPUID
 * levels are dअगरferent and there is a separate entry क्रम each.
 */
अटल स्थिर काष्ठा cpuid_bit cpuid_bits[] = अणु
	अणु X86_FEATURE_APERFMPERF,       CPUID_ECX,  0, 0x00000006, 0 पूर्ण,
	अणु X86_FEATURE_EPB,		CPUID_ECX,  3, 0x00000006, 0 पूर्ण,
	अणु X86_FEATURE_CQM_LLC,		CPUID_EDX,  1, 0x0000000f, 0 पूर्ण,
	अणु X86_FEATURE_CQM_OCCUP_LLC,	CPUID_EDX,  0, 0x0000000f, 1 पूर्ण,
	अणु X86_FEATURE_CQM_MBM_TOTAL,	CPUID_EDX,  1, 0x0000000f, 1 पूर्ण,
	अणु X86_FEATURE_CQM_MBM_LOCAL,	CPUID_EDX,  2, 0x0000000f, 1 पूर्ण,
	अणु X86_FEATURE_CAT_L3,		CPUID_EBX,  1, 0x00000010, 0 पूर्ण,
	अणु X86_FEATURE_CAT_L2,		CPUID_EBX,  2, 0x00000010, 0 पूर्ण,
	अणु X86_FEATURE_CDP_L3,		CPUID_ECX,  2, 0x00000010, 1 पूर्ण,
	अणु X86_FEATURE_CDP_L2,		CPUID_ECX,  2, 0x00000010, 2 पूर्ण,
	अणु X86_FEATURE_MBA,		CPUID_EBX,  3, 0x00000010, 0 पूर्ण,
	अणु X86_FEATURE_PER_THREAD_MBA,	CPUID_ECX,  0, 0x00000010, 3 पूर्ण,
	अणु X86_FEATURE_SGX1,		CPUID_EAX,  0, 0x00000012, 0 पूर्ण,
	अणु X86_FEATURE_SGX2,		CPUID_EAX,  1, 0x00000012, 0 पूर्ण,
	अणु X86_FEATURE_HW_PSTATE,	CPUID_EDX,  7, 0x80000007, 0 पूर्ण,
	अणु X86_FEATURE_CPB,		CPUID_EDX,  9, 0x80000007, 0 पूर्ण,
	अणु X86_FEATURE_PROC_FEEDBACK,    CPUID_EDX, 11, 0x80000007, 0 पूर्ण,
	अणु X86_FEATURE_MBA,		CPUID_EBX,  6, 0x80000008, 0 पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण
पूर्ण;

व्योम init_scattered_cpuid_features(काष्ठा cpuinfo_x86 *c)
अणु
	u32 max_level;
	u32 regs[4];
	स्थिर काष्ठा cpuid_bit *cb;

	क्रम (cb = cpuid_bits; cb->feature; cb++) अणु

		/* Verअगरy that the level is valid */
		max_level = cpuid_eax(cb->level & 0xffff0000);
		अगर (max_level < cb->level ||
		    max_level > (cb->level | 0xffff))
			जारी;

		cpuid_count(cb->level, cb->sub_leaf, &regs[CPUID_EAX],
			    &regs[CPUID_EBX], &regs[CPUID_ECX],
			    &regs[CPUID_EDX]);

		अगर (regs[cb->reg] & (1 << cb->bit))
			set_cpu_cap(c, cb->feature);
	पूर्ण
पूर्ण
