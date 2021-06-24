<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * x86 TSC related functions
 */
#अगर_अघोषित _ASM_X86_TSC_H
#घोषणा _ASM_X86_TSC_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpufeature.h>

/*
 * Standard way to access the cycle counter.
 */
प्रकार अचिन्हित दीर्घ दीर्घ cycles_t;

बाह्य अचिन्हित पूर्णांक cpu_khz;
बाह्य अचिन्हित पूर्णांक tsc_khz;

बाह्य व्योम disable_TSC(व्योम);

अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
#अगर_अघोषित CONFIG_X86_TSC
	अगर (!boot_cpu_has(X86_FEATURE_TSC))
		वापस 0;
#पूर्ण_अगर

	वापस rdtsc();
पूर्ण

बाह्य काष्ठा प्रणाली_counterval_t convert_art_to_tsc(u64 art);
बाह्य काष्ठा प्रणाली_counterval_t convert_art_ns_to_tsc(u64 art_ns);

बाह्य व्योम tsc_early_init(व्योम);
बाह्य व्योम tsc_init(व्योम);
बाह्य अचिन्हित दीर्घ calibrate_delay_is_known(व्योम);
बाह्य व्योम mark_tsc_unstable(अक्षर *reason);
बाह्य पूर्णांक unsynchronized_tsc(व्योम);
बाह्य पूर्णांक check_tsc_unstable(व्योम);
बाह्य व्योम mark_tsc_async_resets(अक्षर *reason);
बाह्य अचिन्हित दीर्घ native_calibrate_cpu_early(व्योम);
बाह्य अचिन्हित दीर्घ native_calibrate_tsc(व्योम);
बाह्य अचिन्हित दीर्घ दीर्घ native_sched_घड़ी_from_tsc(u64 tsc);

बाह्य पूर्णांक tsc_घड़ीsource_reliable;
#अगर_घोषित CONFIG_X86_TSC
बाह्य bool tsc_async_resets;
#अन्यथा
# define tsc_async_resets	false
#पूर्ण_अगर

/*
 * Boot-समय check whether the TSCs are synchronized across
 * all CPUs/cores:
 */
#अगर_घोषित CONFIG_X86_TSC
बाह्य bool tsc_store_and_check_tsc_adjust(bool bootcpu);
बाह्य व्योम tsc_verअगरy_tsc_adjust(bool resume);
बाह्य व्योम check_tsc_sync_source(पूर्णांक cpu);
बाह्य व्योम check_tsc_sync_target(व्योम);
#अन्यथा
अटल अंतरभूत bool tsc_store_and_check_tsc_adjust(bool bootcpu) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम tsc_verअगरy_tsc_adjust(bool resume) अणु पूर्ण
अटल अंतरभूत व्योम check_tsc_sync_source(पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम check_tsc_sync_target(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक notsc_setup(अक्षर *);
बाह्य व्योम tsc_save_sched_घड़ी_state(व्योम);
बाह्य व्योम tsc_restore_sched_घड़ी_state(व्योम);

अचिन्हित दीर्घ cpu_khz_from_msr(व्योम);

#पूर्ण_अगर /* _ASM_X86_TSC_H */
