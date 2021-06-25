<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc.
 *
 * Miscellaneous helpers which करो not fit or are worth
 * to put पूर्णांकo separate headers
 */

#अगर_अघोषित __CPUPOWERUTILS_HELPERS__
#घोषणा __CPUPOWERUTILS_HELPERS__

#समावेश <libपूर्णांकl.h>
#समावेश <क्षेत्र.स>

#समावेश "helpers/bitmask.h"
#समावेश <cpuघातer.h>

/* Internationalization ****************************/
#अगर_घोषित NLS

#घोषणा _(String) gettext(String)
#अगर_अघोषित gettext_noop
#घोषणा gettext_noop(String) String
#पूर्ण_अगर
#घोषणा N_(String) gettext_noop(String)

#अन्यथा /* !NLS */

#घोषणा _(String) String
#घोषणा N_(String) String

#पूर्ण_अगर
/* Internationalization ****************************/

बाह्य पूर्णांक run_as_root;
बाह्य पूर्णांक base_cpu;
बाह्य काष्ठा biपंचांगask *cpus_chosen;

/* Global verbose (-d) stuff *********************************/
/*
 * define DEBUG via global Makefile variable
 * Debug output is sent to मानक_त्रुटि, करो:
 * cpuघातer monitor 2>/पंचांगp/debug
 * to split debug output away from normal output
*/
#अगर_घोषित DEBUG
बाह्य पूर्णांक be_verbose;

#घोषणा dprपूर्णांक(fmt, ...) अणु					\
		अगर (be_verbose) अणु				\
			ख_लिखो(मानक_त्रुटि, "%s: " fmt,		\
				__func__, ##__VA_ARGS__);	\
		पूर्ण						\
	पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dprपूर्णांक(स्थिर अक्षर *fmt, ...) अणु पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक be_verbose;
/* Global verbose (-v) stuff *********************************/

/* cpuid and cpuinfo helpers  **************************/
क्रमागत cpuघातer_cpu_venकरोr अणुX86_VENDOR_UNKNOWN = 0, X86_VENDOR_INTEL,
			  X86_VENDOR_AMD, X86_VENDOR_HYGON, X86_VENDOR_MAXपूर्ण;

#घोषणा CPUPOWER_CAP_INV_TSC		0x00000001
#घोषणा CPUPOWER_CAP_APERF		0x00000002
#घोषणा CPUPOWER_CAP_AMD_CPB		0x00000004
#घोषणा CPUPOWER_CAP_PERF_BIAS		0x00000008
#घोषणा CPUPOWER_CAP_HAS_TURBO_RATIO	0x00000010
#घोषणा CPUPOWER_CAP_IS_SNB		0x00000020
#घोषणा CPUPOWER_CAP_INTEL_IDA		0x00000040
#घोषणा CPUPOWER_CAP_AMD_RDPRU		0x00000080
#घोषणा CPUPOWER_CAP_AMD_HW_PSTATE	0x00000100
#घोषणा CPUPOWER_CAP_AMD_PSTATEDEF	0x00000200
#घोषणा CPUPOWER_CAP_AMD_CPB_MSR	0x00000400

#घोषणा CPUPOWER_AMD_CPBDIS		0x02000000

#घोषणा MAX_HW_PSTATES 10

काष्ठा cpuघातer_cpu_info अणु
	क्रमागत cpuघातer_cpu_venकरोr venकरोr;
	अचिन्हित पूर्णांक family;
	अचिन्हित पूर्णांक model;
	अचिन्हित पूर्णांक stepping;
	/* CPU capabilities पढ़ो out from cpuid */
	अचिन्हित दीर्घ दीर्घ caps;
पूर्ण;

/* get_cpu_info
 *
 * Extract CPU venकरोr, family, model, stepping info from /proc/cpuinfo
 *
 * Returns 0 on success or a negative error code
 * Only used on x86, below global's काष्ठा values are zero/unknown on
 * other archs
 */
बाह्य पूर्णांक get_cpu_info(काष्ठा cpuघातer_cpu_info *cpu_info);
बाह्य काष्ठा cpuघातer_cpu_info cpuघातer_cpu_info;


/* cpuid and cpuinfo helpers  **************************/

/* X86 ONLY ****************************************/
#अगर defined(__i386__) || defined(__x86_64__)

#समावेश <pci/pci.h>

/* Read/Write msr ****************************/
बाह्य पूर्णांक पढ़ो_msr(पूर्णांक cpu, अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ दीर्घ *val);
बाह्य पूर्णांक ग_लिखो_msr(पूर्णांक cpu, अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ दीर्घ val);

बाह्य पूर्णांक cpuघातer_पूर्णांकel_set_perf_bias(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक val);
बाह्य पूर्णांक cpuघातer_पूर्णांकel_get_perf_bias(अचिन्हित पूर्णांक cpu);
बाह्य अचिन्हित दीर्घ दीर्घ msr_पूर्णांकel_get_turbo_ratio(अचिन्हित पूर्णांक cpu);

/* Read/Write msr ****************************/

/* PCI stuff ****************************/
बाह्य पूर्णांक amd_pci_get_num_boost_states(पूर्णांक *active, पूर्णांक *states);
बाह्य काष्ठा pci_dev *pci_acc_init(काष्ठा pci_access **pacc, पूर्णांक करोमुख्य,
				    पूर्णांक bus, पूर्णांक slot, पूर्णांक func, पूर्णांक venकरोr,
				    पूर्णांक dev);
बाह्य काष्ठा pci_dev *pci_slot_func_init(काष्ठा pci_access **pacc,
					      पूर्णांक slot, पूर्णांक func);

/* PCI stuff ****************************/

/* AMD HW pstate decoding **************************/

बाह्य पूर्णांक decode_pstates(अचिन्हित पूर्णांक cpu, पूर्णांक boost_states,
			  अचिन्हित दीर्घ *pstates, पूर्णांक *no);

/* AMD HW pstate decoding **************************/

बाह्य पूर्णांक cpufreq_has_boost_support(अचिन्हित पूर्णांक cpu, पूर्णांक *support,
				     पूर्णांक *active, पूर्णांक * states);
/*
 * CPUID functions वापसing a single datum
 */
अचिन्हित पूर्णांक cpuid_eax(अचिन्हित पूर्णांक op);
अचिन्हित पूर्णांक cpuid_ebx(अचिन्हित पूर्णांक op);
अचिन्हित पूर्णांक cpuid_ecx(अचिन्हित पूर्णांक op);
अचिन्हित पूर्णांक cpuid_edx(अचिन्हित पूर्णांक op);

/* cpuid and cpuinfo helpers  **************************/
/* X86 ONLY ********************************************/
#अन्यथा
अटल अंतरभूत पूर्णांक decode_pstates(अचिन्हित पूर्णांक cpu, पूर्णांक boost_states,
				 अचिन्हित दीर्घ *pstates, पूर्णांक *no)
अणु वापस -1; पूर्ण;

अटल अंतरभूत पूर्णांक पढ़ो_msr(पूर्णांक cpu, अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ दीर्घ *val)
अणु वापस -1; पूर्ण;
अटल अंतरभूत पूर्णांक ग_लिखो_msr(पूर्णांक cpu, अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ दीर्घ val)
अणु वापस -1; पूर्ण;
अटल अंतरभूत पूर्णांक cpuघातer_पूर्णांकel_set_perf_bias(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक val)
अणु वापस -1; पूर्ण;
अटल अंतरभूत पूर्णांक cpuघातer_पूर्णांकel_get_perf_bias(अचिन्हित पूर्णांक cpu)
अणु वापस -1; पूर्ण;
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ msr_पूर्णांकel_get_turbo_ratio(अचिन्हित पूर्णांक cpu)
अणु वापस 0; पूर्ण;

/* Read/Write msr ****************************/

अटल अंतरभूत पूर्णांक cpufreq_has_boost_support(अचिन्हित पूर्णांक cpu, पूर्णांक *support,
					    पूर्णांक *active, पूर्णांक * states)
अणु वापस -1; पूर्ण

/* cpuid and cpuinfo helpers  **************************/

अटल अंतरभूत अचिन्हित पूर्णांक cpuid_eax(अचिन्हित पूर्णांक op) अणु वापस 0; पूर्ण;
अटल अंतरभूत अचिन्हित पूर्णांक cpuid_ebx(अचिन्हित पूर्णांक op) अणु वापस 0; पूर्ण;
अटल अंतरभूत अचिन्हित पूर्णांक cpuid_ecx(अचिन्हित पूर्णांक op) अणु वापस 0; पूर्ण;
अटल अंतरभूत अचिन्हित पूर्णांक cpuid_edx(अचिन्हित पूर्णांक op) अणु वापस 0; पूर्ण;
#पूर्ण_अगर /* defined(__i386__) || defined(__x86_64__) */

/*
 * CPU State related functions
 */
बाह्य काष्ठा biपंचांगask *online_cpus;
बाह्य काष्ठा biपंचांगask *offline_cpus;

व्योम get_cpustate(व्योम);
व्योम prपूर्णांक_online_cpus(व्योम);
व्योम prपूर्णांक_offline_cpus(व्योम);

#पूर्ण_अगर /* __CPUPOWERUTILS_HELPERS__ */
