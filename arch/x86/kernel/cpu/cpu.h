<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_X86_CPU_H
#घोषणा ARCH_X86_CPU_H

/* attempt to consolidate cpu attributes */
काष्ठा cpu_dev अणु
	स्थिर अक्षर	*c_venकरोr;

	/* some have two possibilities क्रम cpuid string */
	स्थिर अक्षर	*c_ident[2];

	व्योम            (*c_early_init)(काष्ठा cpuinfo_x86 *);
	व्योम		(*c_bsp_init)(काष्ठा cpuinfo_x86 *);
	व्योम		(*c_init)(काष्ठा cpuinfo_x86 *);
	व्योम		(*c_identअगरy)(काष्ठा cpuinfo_x86 *);
	व्योम		(*c_detect_tlb)(काष्ठा cpuinfo_x86 *);
	पूर्णांक		c_x86_venकरोr;
#अगर_घोषित CONFIG_X86_32
	/* Optional venकरोr specअगरic routine to obtain the cache size. */
	अचिन्हित पूर्णांक	(*legacy_cache_size)(काष्ठा cpuinfo_x86 *,
					     अचिन्हित पूर्णांक);

	/* Family/stepping-based lookup table क्रम model names. */
	काष्ठा legacy_cpu_model_info अणु
		पूर्णांक		family;
		स्थिर अक्षर	*model_names[16];
	पूर्ण		legacy_models[5];
#पूर्ण_अगर
पूर्ण;

काष्ठा _tlb_table अणु
	अचिन्हित अक्षर descriptor;
	अक्षर tlb_type;
	अचिन्हित पूर्णांक entries;
	/* अचिन्हित पूर्णांक ways; */
	अक्षर info[128];
पूर्ण;

#घोषणा cpu_dev_रेजिस्टर(cpu_devX) \
	अटल स्थिर काष्ठा cpu_dev *स्थिर __cpu_dev_##cpu_devX __used \
	__section(".x86_cpu_dev.init") = \
	&cpu_devX;

बाह्य स्थिर काष्ठा cpu_dev *स्थिर __x86_cpu_dev_start[],
			    *स्थिर __x86_cpu_dev_end[];

#अगर_घोषित CONFIG_CPU_SUP_INTEL
क्रमागत tsx_ctrl_states अणु
	TSX_CTRL_ENABLE,
	TSX_CTRL_DISABLE,
	TSX_CTRL_NOT_SUPPORTED,
पूर्ण;

बाह्य __ro_after_init क्रमागत tsx_ctrl_states tsx_ctrl_state;

बाह्य व्योम __init tsx_init(व्योम);
बाह्य व्योम tsx_enable(व्योम);
बाह्य व्योम tsx_disable(व्योम);
#अन्यथा
अटल अंतरभूत व्योम tsx_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_SUP_INTEL */

बाह्य व्योम get_cpu_cap(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम get_cpu_address_sizes(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम cpu_detect_cache_sizes(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम init_scattered_cpuid_features(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम init_पूर्णांकel_cacheinfo(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम init_amd_cacheinfo(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम init_hygon_cacheinfo(काष्ठा cpuinfo_x86 *c);

बाह्य व्योम detect_num_cpu_cores(काष्ठा cpuinfo_x86 *c);
बाह्य पूर्णांक detect_extended_topology_early(काष्ठा cpuinfo_x86 *c);
बाह्य पूर्णांक detect_extended_topology(काष्ठा cpuinfo_x86 *c);
बाह्य पूर्णांक detect_ht_early(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम detect_ht(काष्ठा cpuinfo_x86 *c);

अचिन्हित पूर्णांक aperfmperf_get_khz(पूर्णांक cpu);

बाह्य व्योम x86_spec_ctrl_setup_ap(व्योम);
बाह्य व्योम update_srbds_msr(व्योम);

बाह्य u64 x86_पढ़ो_arch_cap_msr(व्योम);

#पूर्ण_अगर /* ARCH_X86_CPU_H */
