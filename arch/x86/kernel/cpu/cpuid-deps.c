<शैली गुरु>
/* Declare dependencies between CPUIDs */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cpufeature.h>

काष्ठा cpuid_dep अणु
	अचिन्हित पूर्णांक	feature;
	अचिन्हित पूर्णांक	depends;
पूर्ण;

/*
 * Table of CPUID features that depend on others.
 *
 * This only includes dependencies that can be usefully disabled, not
 * features part of the base set (like FPU).
 *
 * Note this all is not __init / __initdata because it can be
 * called from cpu hotplug. It shouldn't करो anything in this हाल,
 * but it's dअगरficult to tell that to the init reference checker.
 */
अटल स्थिर काष्ठा cpuid_dep cpuid_deps[] = अणु
	अणु X86_FEATURE_FXSR,			X86_FEATURE_FPU	      पूर्ण,
	अणु X86_FEATURE_XSAVEOPT,			X86_FEATURE_XSAVE     पूर्ण,
	अणु X86_FEATURE_XSAVEC,			X86_FEATURE_XSAVE     पूर्ण,
	अणु X86_FEATURE_XSAVES,			X86_FEATURE_XSAVE     पूर्ण,
	अणु X86_FEATURE_AVX,			X86_FEATURE_XSAVE     पूर्ण,
	अणु X86_FEATURE_PKU,			X86_FEATURE_XSAVE     पूर्ण,
	अणु X86_FEATURE_MPX,			X86_FEATURE_XSAVE     पूर्ण,
	अणु X86_FEATURE_XGETBV1,			X86_FEATURE_XSAVE     पूर्ण,
	अणु X86_FEATURE_CMOV,			X86_FEATURE_FXSR      पूर्ण,
	अणु X86_FEATURE_MMX,			X86_FEATURE_FXSR      पूर्ण,
	अणु X86_FEATURE_MMXEXT,			X86_FEATURE_MMX       पूर्ण,
	अणु X86_FEATURE_FXSR_OPT,			X86_FEATURE_FXSR      पूर्ण,
	अणु X86_FEATURE_XSAVE,			X86_FEATURE_FXSR      पूर्ण,
	अणु X86_FEATURE_XMM,			X86_FEATURE_FXSR      पूर्ण,
	अणु X86_FEATURE_XMM2,			X86_FEATURE_XMM       पूर्ण,
	अणु X86_FEATURE_XMM3,			X86_FEATURE_XMM2      पूर्ण,
	अणु X86_FEATURE_XMM4_1,			X86_FEATURE_XMM2      पूर्ण,
	अणु X86_FEATURE_XMM4_2,			X86_FEATURE_XMM2      पूर्ण,
	अणु X86_FEATURE_XMM3,			X86_FEATURE_XMM2      पूर्ण,
	अणु X86_FEATURE_PCLMULQDQ,		X86_FEATURE_XMM2      पूर्ण,
	अणु X86_FEATURE_SSSE3,			X86_FEATURE_XMM2,     पूर्ण,
	अणु X86_FEATURE_F16C,			X86_FEATURE_XMM2,     पूर्ण,
	अणु X86_FEATURE_AES,			X86_FEATURE_XMM2      पूर्ण,
	अणु X86_FEATURE_SHA_NI,			X86_FEATURE_XMM2      पूर्ण,
	अणु X86_FEATURE_FMA,			X86_FEATURE_AVX       पूर्ण,
	अणु X86_FEATURE_AVX2,			X86_FEATURE_AVX,      पूर्ण,
	अणु X86_FEATURE_AVX512F,			X86_FEATURE_AVX,      पूर्ण,
	अणु X86_FEATURE_AVX512IFMA,		X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512PF,			X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512ER,			X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512CD,			X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512DQ,			X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512BW,			X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512VL,			X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512VBMI,		X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512_VBMI2,		X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_GFNI,			X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_VAES,			X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_VPCLMULQDQ,		X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_AVX512_VNNI,		X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_AVX512_BITALG,		X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_AVX512_4VNNIW,		X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512_4FMAPS,		X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512_VPOPCNTDQ,		X86_FEATURE_AVX512F   पूर्ण,
	अणु X86_FEATURE_AVX512_VP2INTERSECT,	X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_CQM_OCCUP_LLC,		X86_FEATURE_CQM_LLC   पूर्ण,
	अणु X86_FEATURE_CQM_MBM_TOTAL,		X86_FEATURE_CQM_LLC   पूर्ण,
	अणु X86_FEATURE_CQM_MBM_LOCAL,		X86_FEATURE_CQM_LLC   पूर्ण,
	अणु X86_FEATURE_AVX512_BF16,		X86_FEATURE_AVX512VL  पूर्ण,
	अणु X86_FEATURE_AVX512_FP16,		X86_FEATURE_AVX512BW  पूर्ण,
	अणु X86_FEATURE_ENQCMD,			X86_FEATURE_XSAVES    पूर्ण,
	अणु X86_FEATURE_PER_THREAD_MBA,		X86_FEATURE_MBA       पूर्ण,
	अणु X86_FEATURE_SGX_LC,			X86_FEATURE_SGX	      पूर्ण,
	अणु X86_FEATURE_SGX1,			X86_FEATURE_SGX       पूर्ण,
	अणु X86_FEATURE_SGX2,			X86_FEATURE_SGX1      पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत व्योम clear_feature(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक feature)
अणु
	/*
	 * Note: This could use the non atomic __*_bit() variants, but the
	 * rest of the cpufeature code uses atomics as well, so keep it क्रम
	 * consistency. Cleanup all of it separately.
	 */
	अगर (!c) अणु
		clear_cpu_cap(&boot_cpu_data, feature);
		set_bit(feature, (अचिन्हित दीर्घ *)cpu_caps_cleared);
	पूर्ण अन्यथा अणु
		clear_bit(feature, (अचिन्हित दीर्घ *)c->x86_capability);
	पूर्ण
पूर्ण

/* Take the capabilities and the BUG bits पूर्णांकo account */
#घोषणा MAX_FEATURE_BITS ((NCAPINTS + NBUGINTS) * माप(u32) * 8)

अटल व्योम करो_clear_cpu_cap(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक feature)
अणु
	DECLARE_BITMAP(disable, MAX_FEATURE_BITS);
	स्थिर काष्ठा cpuid_dep *d;
	bool changed;

	अगर (WARN_ON(feature >= MAX_FEATURE_BITS))
		वापस;

	clear_feature(c, feature);

	/* Collect all features to disable, handling dependencies */
	स_रखो(disable, 0, माप(disable));
	__set_bit(feature, disable);

	/* Loop until we get a stable state. */
	करो अणु
		changed = false;
		क्रम (d = cpuid_deps; d->feature; d++) अणु
			अगर (!test_bit(d->depends, disable))
				जारी;
			अगर (__test_and_set_bit(d->feature, disable))
				जारी;

			changed = true;
			clear_feature(c, d->feature);
		पूर्ण
	पूर्ण जबतक (changed);
पूर्ण

व्योम clear_cpu_cap(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक feature)
अणु
	करो_clear_cpu_cap(c, feature);
पूर्ण

व्योम setup_clear_cpu_cap(अचिन्हित पूर्णांक feature)
अणु
	करो_clear_cpu_cap(शून्य, feature);
पूर्ण
