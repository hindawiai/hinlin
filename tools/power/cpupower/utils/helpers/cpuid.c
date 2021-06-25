<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>

#समावेश "helpers/helpers.h"

अटल स्थिर अक्षर *cpu_venकरोr_table[X86_VENDOR_MAX] = अणु
	"Unknown", "GenuineIntel", "AuthenticAMD", "HygonGenuine",
पूर्ण;

#अगर defined(__i386__) || defined(__x86_64__)

/* from gcc */
#समावेश <cpuid.h>

/*
 * CPUID functions वापसing a single datum
 *
 * Define अचिन्हित पूर्णांक cpuid_e[abcd]x(अचिन्हित पूर्णांक op)
 */
#घोषणा cpuid_func(reg)					\
	अचिन्हित पूर्णांक cpuid_##reg(अचिन्हित पूर्णांक op)	\
	अणु						\
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;		\
	__cpuid(op, eax, ebx, ecx, edx);		\
	वापस reg;					\
	पूर्ण
cpuid_func(eax);
cpuid_func(ebx);
cpuid_func(ecx);
cpuid_func(edx);

#पूर्ण_अगर /* defined(__i386__) || defined(__x86_64__) */

/* get_cpu_info
 *
 * Extract CPU venकरोr, family, model, stepping info from /proc/cpuinfo
 *
 * Returns 0 on success or a negativ error code
 *
 * TBD: Should there be a cpuid alternative क्रम this अगर /proc is not mounted?
 */
पूर्णांक get_cpu_info(काष्ठा cpuघातer_cpu_info *cpu_info)
अणु
	खाता *fp;
	अक्षर value[64];
	अचिन्हित पूर्णांक proc, x;
	अचिन्हित पूर्णांक unknown = 0xffffff;
	अचिन्हित पूर्णांक cpuid_level, ext_cpuid_level;

	पूर्णांक ret = -EINVAL;

	cpu_info->venकरोr		= X86_VENDOR_UNKNOWN;
	cpu_info->family		= unknown;
	cpu_info->model			= unknown;
	cpu_info->stepping		= unknown;
	cpu_info->caps			= 0;

	fp = ख_खोलो("/proc/cpuinfo", "r");
	अगर (!fp)
		वापस -EIO;

	जबतक (!ख_पूर्ण(fp)) अणु
		अगर (!ख_माला_लो(value, 64, fp))
			जारी;
		value[63 - 1] = '\0';

		अगर (!म_भेदन(value, "processor\t: ", 12))
			माला_पूछो(value, "processor\t: %u", &proc);

		अगर (proc != (अचिन्हित पूर्णांक)base_cpu)
			जारी;

		/* Get CPU venकरोr */
		अगर (!म_भेदन(value, "vendor_id", 9)) अणु
			क्रम (x = 1; x < X86_VENDOR_MAX; x++) अणु
				अगर (म_माला(value, cpu_venकरोr_table[x]))
					cpu_info->venकरोr = x;
			पूर्ण
		/* Get CPU family, etc. */
		पूर्ण अन्यथा अगर (!म_भेदन(value, "cpu family\t: ", 13)) अणु
			माला_पूछो(value, "cpu family\t: %u",
			       &cpu_info->family);
		पूर्ण अन्यथा अगर (!म_भेदन(value, "model\t\t: ", 9)) अणु
			माला_पूछो(value, "model\t\t: %u",
			       &cpu_info->model);
		पूर्ण अन्यथा अगर (!म_भेदन(value, "stepping\t: ", 10)) अणु
			माला_पूछो(value, "stepping\t: %u",
			       &cpu_info->stepping);

			/* Exit -> all values must have been set */
			अगर (cpu_info->venकरोr == X86_VENDOR_UNKNOWN ||
			    cpu_info->family == unknown ||
			    cpu_info->model == unknown ||
			    cpu_info->stepping == unknown) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	ret = -ENODEV;
out:
	ख_बंद(fp);
	/* Get some useful CPU capabilities from cpuid */
	अगर (cpu_info->venकरोr != X86_VENDOR_AMD &&
	    cpu_info->venकरोr != X86_VENDOR_HYGON &&
	    cpu_info->venकरोr != X86_VENDOR_INTEL)
		वापस ret;

	cpuid_level	= cpuid_eax(0);
	ext_cpuid_level	= cpuid_eax(0x80000000);

	/* Invariant TSC */
	अगर (ext_cpuid_level >= 0x80000007 &&
	    (cpuid_edx(0x80000007) & (1 << 8)))
		cpu_info->caps |= CPUPOWER_CAP_INV_TSC;

	/* Aperf/Mperf रेजिस्टरs support */
	अगर (cpuid_level >= 6 && (cpuid_ecx(6) & 0x1))
		cpu_info->caps |= CPUPOWER_CAP_APERF;

	/* AMD or Hygon Boost state enable/disable रेजिस्टर */
	अगर (cpu_info->venकरोr == X86_VENDOR_AMD ||
	    cpu_info->venकरोr == X86_VENDOR_HYGON) अणु
		अगर (ext_cpuid_level >= 0x80000007) अणु
			अगर (cpuid_edx(0x80000007) & (1 << 9)) अणु
				cpu_info->caps |= CPUPOWER_CAP_AMD_CPB;

				अगर (cpu_info->family >= 0x17)
					cpu_info->caps |= CPUPOWER_CAP_AMD_CPB_MSR;
			पूर्ण

			अगर ((cpuid_edx(0x80000007) & (1 << 7)) &&
			    cpu_info->family != 0x14) अणु
				/* HW pstate was not implemented in family 0x14 */
				cpu_info->caps |= CPUPOWER_CAP_AMD_HW_PSTATE;

				अगर (cpu_info->family >= 0x17)
					cpu_info->caps |= CPUPOWER_CAP_AMD_PSTATEDEF;
			पूर्ण
		पूर्ण

		अगर (ext_cpuid_level >= 0x80000008 &&
		    cpuid_ebx(0x80000008) & (1 << 4))
			cpu_info->caps |= CPUPOWER_CAP_AMD_RDPRU;
	पूर्ण

	अगर (cpu_info->venकरोr == X86_VENDOR_INTEL) अणु
		अगर (cpuid_level >= 6 &&
		    (cpuid_eax(6) & (1 << 1)))
			cpu_info->caps |= CPUPOWER_CAP_INTEL_IDA;
	पूर्ण

	अगर (cpu_info->venकरोr == X86_VENDOR_INTEL) अणु
		/* Intel's perf-bias MSR support */
		अगर (cpuid_level >= 6 && (cpuid_ecx(6) & (1 << 3)))
			cpu_info->caps |= CPUPOWER_CAP_PERF_BIAS;

		/* Intel's Turbo Ratio Limit support */
		अगर (cpu_info->family == 6) अणु
			चयन (cpu_info->model) अणु
			हाल 0x1A:	/* Core i7, Xeon 5500 series
					 * Bloomfield, Gainstown NHM-EP
					 */
			हाल 0x1E:	/* Core i7 and i5 Processor
					 * Clarksfield, Lynnfield, Jasper Forest
					 */
			हाल 0x1F:	/* Core i7 and i5 Processor - Nehalem */
			हाल 0x25:	/* Wesपंचांगere Client
					 * Clarkdale, Arअक्रमale
					 */
			हाल 0x2C:	/* Wesपंचांगere EP - Gulftown */
				cpu_info->caps |= CPUPOWER_CAP_HAS_TURBO_RATIO;
				अवरोध;
			हाल 0x2A:	/* SNB */
			हाल 0x2D:	/* SNB Xeon */
			हाल 0x3A:	/* IVB */
			हाल 0x3E:	/* IVB Xeon */
				cpu_info->caps |= CPUPOWER_CAP_HAS_TURBO_RATIO;
				cpu_info->caps |= CPUPOWER_CAP_IS_SNB;
				अवरोध;
			हाल 0x2E:	/* Nehalem-EX Xeon - Beckton */
			हाल 0x2F:	/* Wesपंचांगere-EX Xeon - Eagleton */
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*	म_लिखो("ID: %u - Extid: 0x%x - Caps: 0x%llx\n",
		cpuid_level, ext_cpuid_level, cpu_info->caps);
	*/
	वापस ret;
पूर्ण
