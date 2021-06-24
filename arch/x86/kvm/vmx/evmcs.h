<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_EVMCS_H
#घोषणा __KVM_X86_VMX_EVMCS_H

#समावेश <linux/jump_label.h>

#समावेश <यंत्र/hyperv-tlfs.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/vmx.h>

#समावेश "capabilities.h"
#समावेश "vmcs.h"
#समावेश "vmcs12.h"

काष्ठा vmcs_config;

DECLARE_STATIC_KEY_FALSE(enable_evmcs);

#घोषणा current_evmcs ((काष्ठा hv_enlightened_vmcs *)this_cpu_पढ़ो(current_vmcs))

#घोषणा KVM_EVMCS_VERSION 1

/*
 * Enlightened VMCSv1 करोesn't support these:
 *
 *	POSTED_INTR_NV                  = 0x00000002,
 *	GUEST_INTR_STATUS               = 0x00000810,
 *	APIC_ACCESS_ADDR		= 0x00002014,
 *	POSTED_INTR_DESC_ADDR           = 0x00002016,
 *	EOI_EXIT_BITMAP0                = 0x0000201c,
 *	EOI_EXIT_BITMAP1                = 0x0000201e,
 *	EOI_EXIT_BITMAP2                = 0x00002020,
 *	EOI_EXIT_BITMAP3                = 0x00002022,
 *	GUEST_PML_INDEX			= 0x00000812,
 *	PML_ADDRESS			= 0x0000200e,
 *	VM_FUNCTION_CONTROL             = 0x00002018,
 *	EPTP_LIST_ADDRESS               = 0x00002024,
 *	VMREAD_BITMAP                   = 0x00002026,
 *	VMWRITE_BITMAP                  = 0x00002028,
 *
 *	TSC_MULTIPLIER                  = 0x00002032,
 *	PLE_GAP                         = 0x00004020,
 *	PLE_WINDOW                      = 0x00004022,
 *	VMX_PREEMPTION_TIMER_VALUE      = 0x0000482E,
 *      GUEST_IA32_PERF_GLOBAL_CTRL     = 0x00002808,
 *      HOST_IA32_PERF_GLOBAL_CTRL      = 0x00002c04,
 *
 * Currently unsupported in KVM:
 *	GUEST_IA32_RTIT_CTL		= 0x00002814,
 */
#घोषणा EVMCS1_UNSUPPORTED_PINCTRL (PIN_BASED_POSTED_INTR | \
				    PIN_BASED_VMX_PREEMPTION_TIMER)
#घोषणा EVMCS1_UNSUPPORTED_2NDEXEC					\
	(SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY |				\
	 SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |			\
	 SECONDARY_EXEC_APIC_REGISTER_VIRT |				\
	 SECONDARY_EXEC_ENABLE_PML |					\
	 SECONDARY_EXEC_ENABLE_VMFUNC |					\
	 SECONDARY_EXEC_SHADOW_VMCS |					\
	 SECONDARY_EXEC_TSC_SCALING |					\
	 SECONDARY_EXEC_PAUSE_LOOP_EXITING)
#घोषणा EVMCS1_UNSUPPORTED_VMEXIT_CTRL (VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL)
#घोषणा EVMCS1_UNSUPPORTED_VMENTRY_CTRL (VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL)
#घोषणा EVMCS1_UNSUPPORTED_VMFUNC (VMX_VMFUNC_EPTP_SWITCHING)

#अगर IS_ENABLED(CONFIG_HYPERV)

काष्ठा evmcs_field अणु
	u16 offset;
	u16 clean_field;
पूर्ण;

बाह्य स्थिर काष्ठा evmcs_field vmcs_field_to_evmcs_1[];
बाह्य स्थिर अचिन्हित पूर्णांक nr_evmcs_1_fields;

#घोषणा ROL16(val, n) ((u16)(((u16)(val) << (n)) | ((u16)(val) >> (16 - (n)))))

अटल __always_अंतरभूत पूर्णांक get_evmcs_offset(अचिन्हित दीर्घ field,
					    u16 *clean_field)
अणु
	अचिन्हित पूर्णांक index = ROL16(field, 6);
	स्थिर काष्ठा evmcs_field *evmcs_field;

	अगर (unlikely(index >= nr_evmcs_1_fields)) अणु
		WARN_ONCE(1, "KVM: accessing unsupported EVMCS field %lx\n",
			  field);
		वापस -ENOENT;
	पूर्ण

	evmcs_field = &vmcs_field_to_evmcs_1[index];

	अगर (clean_field)
		*clean_field = evmcs_field->clean_field;

	वापस evmcs_field->offset;
पूर्ण

#अघोषित ROL16

अटल अंतरभूत व्योम evmcs_ग_लिखो64(अचिन्हित दीर्घ field, u64 value)
अणु
	u16 clean_field;
	पूर्णांक offset = get_evmcs_offset(field, &clean_field);

	अगर (offset < 0)
		वापस;

	*(u64 *)((अक्षर *)current_evmcs + offset) = value;

	current_evmcs->hv_clean_fields &= ~clean_field;
पूर्ण

अटल अंतरभूत व्योम evmcs_ग_लिखो32(अचिन्हित दीर्घ field, u32 value)
अणु
	u16 clean_field;
	पूर्णांक offset = get_evmcs_offset(field, &clean_field);

	अगर (offset < 0)
		वापस;

	*(u32 *)((अक्षर *)current_evmcs + offset) = value;
	current_evmcs->hv_clean_fields &= ~clean_field;
पूर्ण

अटल अंतरभूत व्योम evmcs_ग_लिखो16(अचिन्हित दीर्घ field, u16 value)
अणु
	u16 clean_field;
	पूर्णांक offset = get_evmcs_offset(field, &clean_field);

	अगर (offset < 0)
		वापस;

	*(u16 *)((अक्षर *)current_evmcs + offset) = value;
	current_evmcs->hv_clean_fields &= ~clean_field;
पूर्ण

अटल अंतरभूत u64 evmcs_पढ़ो64(अचिन्हित दीर्घ field)
अणु
	पूर्णांक offset = get_evmcs_offset(field, शून्य);

	अगर (offset < 0)
		वापस 0;

	वापस *(u64 *)((अक्षर *)current_evmcs + offset);
पूर्ण

अटल अंतरभूत u32 evmcs_पढ़ो32(अचिन्हित दीर्घ field)
अणु
	पूर्णांक offset = get_evmcs_offset(field, शून्य);

	अगर (offset < 0)
		वापस 0;

	वापस *(u32 *)((अक्षर *)current_evmcs + offset);
पूर्ण

अटल अंतरभूत u16 evmcs_पढ़ो16(अचिन्हित दीर्घ field)
अणु
	पूर्णांक offset = get_evmcs_offset(field, शून्य);

	अगर (offset < 0)
		वापस 0;

	वापस *(u16 *)((अक्षर *)current_evmcs + offset);
पूर्ण

अटल अंतरभूत व्योम evmcs_touch_msr_biपंचांगap(व्योम)
अणु
	अगर (unlikely(!current_evmcs))
		वापस;

	अगर (current_evmcs->hv_enlightenments_control.msr_biपंचांगap)
		current_evmcs->hv_clean_fields &=
			~HV_VMX_ENLIGHTENED_CLEAN_FIELD_MSR_BITMAP;
पूर्ण

अटल अंतरभूत व्योम evmcs_load(u64 phys_addr)
अणु
	काष्ठा hv_vp_assist_page *vp_ap =
		hv_get_vp_assist_page(smp_processor_id());

	अगर (current_evmcs->hv_enlightenments_control.nested_flush_hypercall)
		vp_ap->nested_control.features.directhypercall = 1;
	vp_ap->current_nested_vmcs = phys_addr;
	vp_ap->enlighten_vmentry = 1;
पूर्ण

__init व्योम evmcs_sanitize_exec_ctrls(काष्ठा vmcs_config *vmcs_conf);
#अन्यथा /* !IS_ENABLED(CONFIG_HYPERV) */
अटल अंतरभूत व्योम evmcs_ग_लिखो64(अचिन्हित दीर्घ field, u64 value) अणुपूर्ण
अटल अंतरभूत व्योम evmcs_ग_लिखो32(अचिन्हित दीर्घ field, u32 value) अणुपूर्ण
अटल अंतरभूत व्योम evmcs_ग_लिखो16(अचिन्हित दीर्घ field, u16 value) अणुपूर्ण
अटल अंतरभूत u64 evmcs_पढ़ो64(अचिन्हित दीर्घ field) अणु वापस 0; पूर्ण
अटल अंतरभूत u32 evmcs_पढ़ो32(अचिन्हित दीर्घ field) अणु वापस 0; पूर्ण
अटल अंतरभूत u16 evmcs_पढ़ो16(अचिन्हित दीर्घ field) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम evmcs_load(u64 phys_addr) अणुपूर्ण
अटल अंतरभूत व्योम evmcs_touch_msr_biपंचांगap(व्योम) अणुपूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_HYPERV) */

क्रमागत nested_evmptrld_status अणु
	EVMPTRLD_DISABLED,
	EVMPTRLD_SUCCEEDED,
	EVMPTRLD_VMFAIL,
	EVMPTRLD_ERROR,
पूर्ण;

bool nested_enlightened_vmentry(काष्ठा kvm_vcpu *vcpu, u64 *evmcs_gpa);
uपूर्णांक16_t nested_get_evmcs_version(काष्ठा kvm_vcpu *vcpu);
पूर्णांक nested_enable_evmcs(काष्ठा kvm_vcpu *vcpu,
			uपूर्णांक16_t *vmcs_version);
व्योम nested_evmcs_filter_control_msr(u32 msr_index, u64 *pdata);
पूर्णांक nested_evmcs_check_controls(काष्ठा vmcs12 *vmcs12);

#पूर्ण_अगर /* __KVM_X86_VMX_EVMCS_H */
