<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ACPI_PROCESSOR_H
#घोषणा __ACPI_PROCESSOR_H

#समावेश <linux/kernel.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/thermal.h>
#समावेश <यंत्र/acpi.h>

#घोषणा ACPI_PROCESSOR_CLASS		"processor"
#घोषणा ACPI_PROCESSOR_DEVICE_NAME	"Processor"
#घोषणा ACPI_PROCESSOR_DEVICE_HID	"ACPI0007"
#घोषणा ACPI_PROCESSOR_CONTAINER_HID	"ACPI0010"

#घोषणा ACPI_PROCESSOR_BUSY_METRIC	10

#घोषणा ACPI_PROCESSOR_MAX_POWER	8
#घोषणा ACPI_PROCESSOR_MAX_C2_LATENCY	100
#घोषणा ACPI_PROCESSOR_MAX_C3_LATENCY	1000

#घोषणा ACPI_PROCESSOR_MAX_THROTTLING	16
#घोषणा ACPI_PROCESSOR_MAX_THROTTLE	250	/* 25% */
#घोषणा ACPI_PROCESSOR_MAX_DUTY_WIDTH	4

#घोषणा ACPI_PDC_REVISION_ID		0x1

#घोषणा ACPI_PSD_REV0_REVISION		0	/* Support क्रम _PSD as in ACPI 3.0 */
#घोषणा ACPI_PSD_REV0_ENTRIES		5

#घोषणा ACPI_TSD_REV0_REVISION		0	/* Support क्रम _PSD as in ACPI 3.0 */
#घोषणा ACPI_TSD_REV0_ENTRIES		5
/*
 * Types of coordination defined in ACPI 3.0. Same macros can be used across
 * P, C and T states
 */
#घोषणा DOMAIN_COORD_TYPE_SW_ALL	0xfc
#घोषणा DOMAIN_COORD_TYPE_SW_ANY	0xfd
#घोषणा DOMAIN_COORD_TYPE_HW_ALL	0xfe

#घोषणा ACPI_CSTATE_SYSTEMIO	0
#घोषणा ACPI_CSTATE_FFH		1
#घोषणा ACPI_CSTATE_HALT	2
#घोषणा ACPI_CSTATE_INTEGER	3

#घोषणा ACPI_CX_DESC_LEN	32

/* Power Management */

काष्ठा acpi_processor_cx;

काष्ठा acpi_घातer_रेजिस्टर अणु
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;
	u64 address;
पूर्ण __packed;

काष्ठा acpi_processor_cx अणु
	u8 valid;
	u8 type;
	u32 address;
	u8 entry_method;
	u8 index;
	u32 latency;
	u8 bm_sts_skip;
	अक्षर desc[ACPI_CX_DESC_LEN];
पूर्ण;

काष्ठा acpi_lpi_state अणु
	u32 min_residency;
	u32 wake_latency; /* worst हाल */
	u32 flags;
	u32 arch_flags;
	u32 res_cnt_freq;
	u32 enable_parent_state;
	u64 address;
	u8 index;
	u8 entry_method;
	अक्षर desc[ACPI_CX_DESC_LEN];
पूर्ण;

काष्ठा acpi_processor_घातer अणु
	पूर्णांक count;
	जोड़ अणु
		काष्ठा acpi_processor_cx states[ACPI_PROCESSOR_MAX_POWER];
		काष्ठा acpi_lpi_state lpi_states[ACPI_PROCESSOR_MAX_POWER];
	पूर्ण;
	पूर्णांक समयr_broadcast_on_state;
पूर्ण;

/* Perक्रमmance Management */

काष्ठा acpi_psd_package अणु
	u64 num_entries;
	u64 revision;
	u64 करोमुख्य;
	u64 coord_type;
	u64 num_processors;
पूर्ण __packed;

काष्ठा acpi_pct_रेजिस्टर अणु
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 reserved;
	u64 address;
पूर्ण __packed;

काष्ठा acpi_processor_px अणु
	u64 core_frequency;	/* megahertz */
	u64 घातer;	/* milliWatts */
	u64 transition_latency;	/* microseconds */
	u64 bus_master_latency;	/* microseconds */
	u64 control;	/* control value */
	u64 status;	/* success indicator */
पूर्ण;

काष्ठा acpi_processor_perक्रमmance अणु
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक platक्रमm_limit;
	काष्ठा acpi_pct_रेजिस्टर control_रेजिस्टर;
	काष्ठा acpi_pct_रेजिस्टर status_रेजिस्टर;
	अचिन्हित पूर्णांक state_count;
	काष्ठा acpi_processor_px *states;
	काष्ठा acpi_psd_package करोमुख्य_info;
	cpumask_var_t shared_cpu_map;
	अचिन्हित पूर्णांक shared_type;
पूर्ण;

/* Throttling Control */

काष्ठा acpi_tsd_package अणु
	u64 num_entries;
	u64 revision;
	u64 करोमुख्य;
	u64 coord_type;
	u64 num_processors;
पूर्ण __packed;

काष्ठा acpi_ptc_रेजिस्टर अणु
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 reserved;
	u64 address;
पूर्ण __packed;

काष्ठा acpi_processor_tx_tss अणु
	u64 freqpercentage;	/* */
	u64 घातer;	/* milliWatts */
	u64 transition_latency;	/* microseconds */
	u64 control;	/* control value */
	u64 status;	/* success indicator */
पूर्ण;
काष्ठा acpi_processor_tx अणु
	u16 घातer;
	u16 perक्रमmance;
पूर्ण;

काष्ठा acpi_processor;
काष्ठा acpi_processor_throttling अणु
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक platक्रमm_limit;
	काष्ठा acpi_pct_रेजिस्टर control_रेजिस्टर;
	काष्ठा acpi_pct_रेजिस्टर status_रेजिस्टर;
	अचिन्हित पूर्णांक state_count;
	काष्ठा acpi_processor_tx_tss *states_tss;
	काष्ठा acpi_tsd_package करोमुख्य_info;
	cpumask_var_t shared_cpu_map;
	पूर्णांक (*acpi_processor_get_throttling) (काष्ठा acpi_processor * pr);
	पूर्णांक (*acpi_processor_set_throttling) (काष्ठा acpi_processor * pr,
					      पूर्णांक state, bool क्रमce);

	u32 address;
	u8 duty_offset;
	u8 duty_width;
	u8 tsd_valid_flag;
	अचिन्हित पूर्णांक shared_type;
	काष्ठा acpi_processor_tx states[ACPI_PROCESSOR_MAX_THROTTLING];
पूर्ण;

/* Limit Interface */

काष्ठा acpi_processor_lx अणु
	पूर्णांक px;			/* perक्रमmance state */
	पूर्णांक tx;			/* throttle level */
पूर्ण;

काष्ठा acpi_processor_limit अणु
	काष्ठा acpi_processor_lx state;	/* current limit */
	काष्ठा acpi_processor_lx thermal;	/* thermal limit */
	काष्ठा acpi_processor_lx user;	/* user limit */
पूर्ण;

काष्ठा acpi_processor_flags अणु
	u8 घातer:1;
	u8 perक्रमmance:1;
	u8 throttling:1;
	u8 limit:1;
	u8 bm_control:1;
	u8 bm_check:1;
	u8 has_cst:1;
	u8 has_lpi:1;
	u8 घातer_setup_करोne:1;
	u8 bm_rld_set:1;
	u8 need_hotplug_init:1;
पूर्ण;

काष्ठा acpi_processor अणु
	acpi_handle handle;
	u32 acpi_id;
	phys_cpuid_t phys_id;	/* CPU hardware ID such as APIC ID क्रम x86 */
	u32 id;		/* CPU logical ID allocated by OS */
	u32 pblk;
	पूर्णांक perक्रमmance_platक्रमm_limit;
	पूर्णांक throttling_platक्रमm_limit;
	/* 0 - states 0..n-th state available */

	काष्ठा acpi_processor_flags flags;
	काष्ठा acpi_processor_घातer घातer;
	काष्ठा acpi_processor_perक्रमmance *perक्रमmance;
	काष्ठा acpi_processor_throttling throttling;
	काष्ठा acpi_processor_limit limit;
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *dev; /* Processor device. */
	काष्ठा freq_qos_request perflib_req;
	काष्ठा freq_qos_request thermal_req;
पूर्ण;

काष्ठा acpi_processor_errata अणु
	u8 smp;
	काष्ठा अणु
		u8 throttle:1;
		u8 fdma:1;
		u8 reserved:6;
		u32 bmisx;
	पूर्ण piix4;
पूर्ण;

बाह्य पूर्णांक acpi_processor_preरेजिस्टर_perक्रमmance(काष्ठा
						  acpi_processor_perक्रमmance
						  __percpu *perक्रमmance);

बाह्य पूर्णांक acpi_processor_रेजिस्टर_perक्रमmance(काष्ठा acpi_processor_perक्रमmance
					       *perक्रमmance, अचिन्हित पूर्णांक cpu);
बाह्य व्योम acpi_processor_unरेजिस्टर_perक्रमmance(अचिन्हित पूर्णांक cpu);

पूर्णांक acpi_processor_pstate_control(व्योम);
/* note: this locks both the calling module and the processor module
         अगर a _PPC object exists, rmmod is disallowed then */
पूर्णांक acpi_processor_notअगरy_smm(काष्ठा module *calling_module);
पूर्णांक acpi_processor_get_psd(acpi_handle handle,
			   काष्ठा acpi_psd_package *pकरोमुख्य);

/* parsing the _P* objects. */
बाह्य पूर्णांक acpi_processor_get_perक्रमmance_info(काष्ठा acpi_processor *pr);

/* क्रम communication between multiple parts of the processor kernel module */
DECLARE_PER_CPU(काष्ठा acpi_processor *, processors);
बाह्य काष्ठा acpi_processor_errata errata;

#अगर defined(ARCH_HAS_POWER_INIT) && defined(CONFIG_ACPI_PROCESSOR_CSTATE)
व्योम acpi_processor_घातer_init_bm_check(काष्ठा acpi_processor_flags *flags,
					अचिन्हित पूर्णांक cpu);
पूर्णांक acpi_processor_ffh_cstate_probe(अचिन्हित पूर्णांक cpu,
				    काष्ठा acpi_processor_cx *cx,
				    काष्ठा acpi_घातer_रेजिस्टर *reg);
व्योम acpi_processor_ffh_cstate_enter(काष्ठा acpi_processor_cx *cstate);
#अन्यथा
अटल अंतरभूत व्योम acpi_processor_घातer_init_bm_check(काष्ठा
						      acpi_processor_flags
						      *flags, अचिन्हित पूर्णांक cpu)
अणु
	flags->bm_check = 1;
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_processor_ffh_cstate_probe(अचिन्हित पूर्णांक cpu,
						  काष्ठा acpi_processor_cx *cx,
						  काष्ठा acpi_घातer_रेजिस्टर
						  *reg)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत व्योम acpi_processor_ffh_cstate_enter(काष्ठा acpi_processor_cx
						   *cstate)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक call_on_cpu(पूर्णांक cpu, दीर्घ (*fn)(व्योम *), व्योम *arg,
			      bool direct)
अणु
	अगर (direct || (is_percpu_thपढ़ो() && cpu == smp_processor_id()))
		वापस fn(arg);
	वापस work_on_cpu(cpu, fn, arg);
पूर्ण

/* in processor_perflib.c */

#अगर_घोषित CONFIG_CPU_FREQ
बाह्य bool acpi_processor_cpufreq_init;
व्योम acpi_processor_ignore_ppc_init(व्योम);
व्योम acpi_processor_ppc_init(काष्ठा cpufreq_policy *policy);
व्योम acpi_processor_ppc_निकास(काष्ठा cpufreq_policy *policy);
व्योम acpi_processor_ppc_has_changed(काष्ठा acpi_processor *pr, पूर्णांक event_flag);
बाह्य पूर्णांक acpi_processor_get_bios_limit(पूर्णांक cpu, अचिन्हित पूर्णांक *limit);
#अन्यथा
अटल अंतरभूत व्योम acpi_processor_ignore_ppc_init(व्योम)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम acpi_processor_ppc_init(काष्ठा cpufreq_policy *policy)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम acpi_processor_ppc_निकास(काष्ठा cpufreq_policy *policy)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम acpi_processor_ppc_has_changed(काष्ठा acpi_processor *pr,
								पूर्णांक event_flag)
अणु
	अटल अचिन्हित पूर्णांक prपूर्णांकout = 1;
	अगर (prपूर्णांकout) अणु
		prपूर्णांकk(KERN_WARNING
		       "Warning: Processor Platform Limit event detected, but not handled.\n");
		prपूर्णांकk(KERN_WARNING
		       "Consider compiling CPUfreq support into your kernel.\n");
		prपूर्णांकout = 0;
	पूर्ण
पूर्ण
अटल अंतरभूत पूर्णांक acpi_processor_get_bios_limit(पूर्णांक cpu, अचिन्हित पूर्णांक *limit)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर				/* CONFIG_CPU_FREQ */

/* in processor_core.c */
phys_cpuid_t acpi_get_phys_id(acpi_handle, पूर्णांक type, u32 acpi_id);
phys_cpuid_t acpi_map_madt_entry(u32 acpi_id);
पूर्णांक acpi_map_cpuid(phys_cpuid_t phys_id, u32 acpi_id);
पूर्णांक acpi_get_cpuid(acpi_handle, पूर्णांक type, u32 acpi_id);

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
बाह्य पूर्णांक acpi_cppc_processor_probe(काष्ठा acpi_processor *pr);
बाह्य व्योम acpi_cppc_processor_निकास(काष्ठा acpi_processor *pr);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_cppc_processor_probe(काष्ठा acpi_processor *pr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम acpi_cppc_processor_निकास(काष्ठा acpi_processor *pr)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर	/* CONFIG_ACPI_CPPC_LIB */

/* in processor_pdc.c */
व्योम acpi_processor_set_pdc(acpi_handle handle);

/* in processor_throttling.c */
#अगर_घोषित CONFIG_ACPI_CPU_FREQ_PSS
पूर्णांक acpi_processor_tstate_has_changed(काष्ठा acpi_processor *pr);
पूर्णांक acpi_processor_get_throttling_info(काष्ठा acpi_processor *pr);
बाह्य पूर्णांक acpi_processor_set_throttling(काष्ठा acpi_processor *pr,
					 पूर्णांक state, bool क्रमce);
/*
 * Reevaluate whether the T-state is invalid after one cpu is
 * onlined/offlined. In such हाल the flags.throttling will be updated.
 */
बाह्य व्योम acpi_processor_reevaluate_tstate(काष्ठा acpi_processor *pr,
			bool is_dead);
बाह्य स्थिर काष्ठा file_operations acpi_processor_throttling_fops;
बाह्य व्योम acpi_processor_throttling_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_processor_tstate_has_changed(काष्ठा acpi_processor *pr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_processor_get_throttling_info(काष्ठा acpi_processor *pr)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_processor_set_throttling(काष्ठा acpi_processor *pr,
					 पूर्णांक state, bool क्रमce)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम acpi_processor_reevaluate_tstate(काष्ठा acpi_processor *pr,
			bool is_dead) अणुपूर्ण

अटल अंतरभूत व्योम acpi_processor_throttling_init(व्योम) अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_ACPI_CPU_FREQ_PSS */

/* in processor_idle.c */
बाह्य काष्ठा cpuidle_driver acpi_idle_driver;
#अगर_घोषित CONFIG_ACPI_PROCESSOR_IDLE
पूर्णांक acpi_processor_घातer_init(काष्ठा acpi_processor *pr);
पूर्णांक acpi_processor_घातer_निकास(काष्ठा acpi_processor *pr);
पूर्णांक acpi_processor_घातer_state_has_changed(काष्ठा acpi_processor *pr);
पूर्णांक acpi_processor_hotplug(काष्ठा acpi_processor *pr);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_processor_घातer_init(काष्ठा acpi_processor *pr)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_processor_घातer_निकास(काष्ठा acpi_processor *pr)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_processor_घातer_state_has_changed(काष्ठा acpi_processor *pr)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_processor_hotplug(काष्ठा acpi_processor *pr)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_PROCESSOR_IDLE */

/* in processor_thermal.c */
पूर्णांक acpi_processor_get_limit_info(काष्ठा acpi_processor *pr);
बाह्य स्थिर काष्ठा thermal_cooling_device_ops processor_cooling_ops;
#अगर defined(CONFIG_ACPI_CPU_FREQ_PSS) & defined(CONFIG_CPU_FREQ)
व्योम acpi_thermal_cpufreq_init(काष्ठा cpufreq_policy *policy);
व्योम acpi_thermal_cpufreq_निकास(काष्ठा cpufreq_policy *policy);
#अन्यथा
अटल अंतरभूत व्योम acpi_thermal_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम acpi_thermal_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर	/* CONFIG_ACPI_CPU_FREQ_PSS */

#पूर्ण_अगर
