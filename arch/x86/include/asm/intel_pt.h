<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_INTEL_PT_H
#घोषणा _ASM_X86_INTEL_PT_H

#घोषणा PT_CPUID_LEAVES		2
#घोषणा PT_CPUID_REGS_NUM	4 /* number of रेजिस्टरs (eax, ebx, ecx, edx) */

क्रमागत pt_capabilities अणु
	PT_CAP_max_subleaf = 0,
	PT_CAP_cr3_filtering,
	PT_CAP_psb_cyc,
	PT_CAP_ip_filtering,
	PT_CAP_mtc,
	PT_CAP_ptग_लिखो,
	PT_CAP_घातer_event_trace,
	PT_CAP_topa_output,
	PT_CAP_topa_multiple_entries,
	PT_CAP_single_range_output,
	PT_CAP_output_subsys,
	PT_CAP_payloads_lip,
	PT_CAP_num_address_ranges,
	PT_CAP_mtc_periods,
	PT_CAP_cycle_thresholds,
	PT_CAP_psb_periods,
पूर्ण;

#अगर defined(CONFIG_PERF_EVENTS) && defined(CONFIG_CPU_SUP_INTEL)
व्योम cpu_emergency_stop_pt(व्योम);
बाह्य u32 पूर्णांकel_pt_validate_hw_cap(क्रमागत pt_capabilities cap);
बाह्य u32 पूर्णांकel_pt_validate_cap(u32 *caps, क्रमागत pt_capabilities cap);
बाह्य पूर्णांक is_पूर्णांकel_pt_event(काष्ठा perf_event *event);
#अन्यथा
अटल अंतरभूत व्योम cpu_emergency_stop_pt(व्योम) अणुपूर्ण
अटल अंतरभूत u32 पूर्णांकel_pt_validate_hw_cap(क्रमागत pt_capabilities cap) अणु वापस 0; पूर्ण
अटल अंतरभूत u32 पूर्णांकel_pt_validate_cap(u32 *caps, क्रमागत pt_capabilities capability) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक is_पूर्णांकel_pt_event(काष्ठा perf_event *event) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_INTEL_PT_H */
