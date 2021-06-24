<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MICROCODE_H
#घोषणा _ASM_X86_MICROCODE_H

#समावेश <यंत्र/cpu.h>
#समावेश <linux/earlycpपन.स>
#समावेश <linux/initrd.h>

काष्ठा ucode_patch अणु
	काष्ठा list_head plist;
	व्योम *data;		/* Intel uses only this one */
	u32 patch_id;
	u16 equiv_cpu;
पूर्ण;

बाह्य काष्ठा list_head microcode_cache;

काष्ठा cpu_signature अणु
	अचिन्हित पूर्णांक sig;
	अचिन्हित पूर्णांक pf;
	अचिन्हित पूर्णांक rev;
पूर्ण;

काष्ठा device;

क्रमागत ucode_state अणु
	UCODE_OK	= 0,
	UCODE_NEW,
	UCODE_UPDATED,
	UCODE_NFOUND,
	UCODE_ERROR,
पूर्ण;

काष्ठा microcode_ops अणु
	क्रमागत ucode_state (*request_microcode_user) (पूर्णांक cpu,
				स्थिर व्योम __user *buf, माप_प्रकार size);

	क्रमागत ucode_state (*request_microcode_fw) (पूर्णांक cpu, काष्ठा device *,
						  bool refresh_fw);

	व्योम (*microcode_fini_cpu) (पूर्णांक cpu);

	/*
	 * The generic 'microcode_core' part guarantees that
	 * the callbacks below run on a target cpu when they
	 * are being called.
	 * See also the "Synchronization" section in microcode_core.c.
	 */
	क्रमागत ucode_state (*apply_microcode) (पूर्णांक cpu);
	पूर्णांक (*collect_cpu_info) (पूर्णांक cpu, काष्ठा cpu_signature *csig);
पूर्ण;

काष्ठा ucode_cpu_info अणु
	काष्ठा cpu_signature	cpu_sig;
	पूर्णांक			valid;
	व्योम			*mc;
पूर्ण;
बाह्य काष्ठा ucode_cpu_info ucode_cpu_info[];
काष्ठा cpio_data find_microcode_in_initrd(स्थिर अक्षर *path, bool use_pa);

#अगर_घोषित CONFIG_MICROCODE_INTEL
बाह्य काष्ठा microcode_ops * __init init_पूर्णांकel_microcode(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा microcode_ops * __init init_पूर्णांकel_microcode(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_MICROCODE_INTEL */

#अगर_घोषित CONFIG_MICROCODE_AMD
बाह्य काष्ठा microcode_ops * __init init_amd_microcode(व्योम);
बाह्य व्योम __निकास निकास_amd_microcode(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा microcode_ops * __init init_amd_microcode(व्योम)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम __निकास निकास_amd_microcode(व्योम) अणुपूर्ण
#पूर्ण_अगर

#घोषणा MAX_UCODE_COUNT 128

#घोषणा QCHAR(a, b, c, d) ((a) + ((b) << 8) + ((c) << 16) + ((d) << 24))
#घोषणा CPUID_INTEL1 QCHAR('G', 'e', 'n', 'u')
#घोषणा CPUID_INTEL2 QCHAR('i', 'n', 'e', 'I')
#घोषणा CPUID_INTEL3 QCHAR('n', 't', 'e', 'l')
#घोषणा CPUID_AMD1 QCHAR('A', 'u', 't', 'h')
#घोषणा CPUID_AMD2 QCHAR('e', 'n', 't', 'i')
#घोषणा CPUID_AMD3 QCHAR('c', 'A', 'M', 'D')

#घोषणा CPUID_IS(a, b, c, ebx, ecx, edx)	\
		(!((ebx ^ (a))|(edx ^ (b))|(ecx ^ (c))))

/*
 * In early loading microcode phase on BSP, boot_cpu_data is not set up yet.
 * x86_cpuid_venकरोr() माला_लो venकरोr id क्रम BSP.
 *
 * In 32 bit AP हाल, accessing boot_cpu_data needs linear address. To simplअगरy
 * coding, we still use x86_cpuid_venकरोr() to get venकरोr id क्रम AP.
 *
 * x86_cpuid_venकरोr() माला_लो venकरोr inक्रमmation directly from CPUID.
 */
अटल अंतरभूत पूर्णांक x86_cpuid_venकरोr(व्योम)
अणु
	u32 eax = 0x00000000;
	u32 ebx, ecx = 0, edx;

	native_cpuid(&eax, &ebx, &ecx, &edx);

	अगर (CPUID_IS(CPUID_INTEL1, CPUID_INTEL2, CPUID_INTEL3, ebx, ecx, edx))
		वापस X86_VENDOR_INTEL;

	अगर (CPUID_IS(CPUID_AMD1, CPUID_AMD2, CPUID_AMD3, ebx, ecx, edx))
		वापस X86_VENDOR_AMD;

	वापस X86_VENDOR_UNKNOWN;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक x86_cpuid_family(व्योम)
अणु
	u32 eax = 0x00000001;
	u32 ebx, ecx = 0, edx;

	native_cpuid(&eax, &ebx, &ecx, &edx);

	वापस x86_family(eax);
पूर्ण

#अगर_घोषित CONFIG_MICROCODE
बाह्य व्योम __init load_ucode_bsp(व्योम);
बाह्य व्योम load_ucode_ap(व्योम);
व्योम reload_early_microcode(व्योम);
बाह्य bool get_builtin_firmware(काष्ठा cpio_data *cd, स्थिर अक्षर *name);
बाह्य bool initrd_gone;
#अन्यथा
अटल अंतरभूत व्योम __init load_ucode_bsp(व्योम)			अणु पूर्ण
अटल अंतरभूत व्योम load_ucode_ap(व्योम)				अणु पूर्ण
अटल अंतरभूत व्योम reload_early_microcode(व्योम)			अणु पूर्ण
अटल अंतरभूत bool
get_builtin_firmware(काष्ठा cpio_data *cd, स्थिर अक्षर *name)	अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_MICROCODE_H */
