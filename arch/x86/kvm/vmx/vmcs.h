<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_VMCS_H
#घोषणा __KVM_X86_VMX_VMCS_H

#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/nospec.h>

#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/vmx.h>

#समावेश "capabilities.h"

काष्ठा vmcs_hdr अणु
	u32 revision_id:31;
	u32 shaकरोw_vmcs:1;
पूर्ण;

काष्ठा vmcs अणु
	काष्ठा vmcs_hdr hdr;
	u32 पात;
	अक्षर data[];
पूर्ण;

DECLARE_PER_CPU(काष्ठा vmcs *, current_vmcs);

/*
 * vmcs_host_state tracks रेजिस्टरs that are loaded from the VMCS on VMEXIT
 * and whose values change infrequently, but are not स्थिरant.  I.e. this is
 * used as a ग_लिखो-through cache of the corresponding VMCS fields.
 */
काष्ठा vmcs_host_state अणु
	अचिन्हित दीर्घ cr3;	/* May not match real cr3 */
	अचिन्हित दीर्घ cr4;	/* May not match real cr4 */
	अचिन्हित दीर्घ gs_base;
	अचिन्हित दीर्घ fs_base;
	अचिन्हित दीर्घ rsp;

	u16           fs_sel, gs_sel, ldt_sel;
#अगर_घोषित CONFIG_X86_64
	u16           ds_sel, es_sel;
#पूर्ण_अगर
पूर्ण;

काष्ठा vmcs_controls_shaकरोw अणु
	u32 vm_entry;
	u32 vm_निकास;
	u32 pin;
	u32 exec;
	u32 secondary_exec;
पूर्ण;

/*
 * Track a VMCS that may be loaded on a certain CPU. If it is (cpu!=-1), also
 * remember whether it was VMLAUNCHed, and मुख्यtain a linked list of all VMCSs
 * loaded on this CPU (so we can clear them अगर the CPU goes करोwn).
 */
काष्ठा loaded_vmcs अणु
	काष्ठा vmcs *vmcs;
	काष्ठा vmcs *shaकरोw_vmcs;
	पूर्णांक cpu;
	bool launched;
	bool nmi_known_unmasked;
	bool hv_समयr_soft_disabled;
	/* Support क्रम vnmi-less CPUs */
	पूर्णांक soft_vnmi_blocked;
	kसमय_प्रकार entry_समय;
	s64 vnmi_blocked_समय;
	अचिन्हित दीर्घ *msr_biपंचांगap;
	काष्ठा list_head loaded_vmcss_on_cpu_link;
	काष्ठा vmcs_host_state host_state;
	काष्ठा vmcs_controls_shaकरोw controls_shaकरोw;
पूर्ण;

अटल अंतरभूत bool is_पूर्णांकr_type(u32 पूर्णांकr_info, u32 type)
अणु
	स्थिर u32 mask = INTR_INFO_VALID_MASK | INTR_INFO_INTR_TYPE_MASK;

	वापस (पूर्णांकr_info & mask) == (INTR_INFO_VALID_MASK | type);
पूर्ण

अटल अंतरभूत bool is_पूर्णांकr_type_n(u32 पूर्णांकr_info, u32 type, u8 vector)
अणु
	स्थिर u32 mask = INTR_INFO_VALID_MASK | INTR_INFO_INTR_TYPE_MASK |
			 INTR_INFO_VECTOR_MASK;

	वापस (पूर्णांकr_info & mask) == (INTR_INFO_VALID_MASK | type | vector);
पूर्ण

अटल अंतरभूत bool is_exception_n(u32 पूर्णांकr_info, u8 vector)
अणु
	वापस is_पूर्णांकr_type_n(पूर्णांकr_info, INTR_TYPE_HARD_EXCEPTION, vector);
पूर्ण

अटल अंतरभूत bool is_debug(u32 पूर्णांकr_info)
अणु
	वापस is_exception_n(पूर्णांकr_info, DB_VECTOR);
पूर्ण

अटल अंतरभूत bool is_अवरोधpoपूर्णांक(u32 पूर्णांकr_info)
अणु
	वापस is_exception_n(पूर्णांकr_info, BP_VECTOR);
पूर्ण

अटल अंतरभूत bool is_page_fault(u32 पूर्णांकr_info)
अणु
	वापस is_exception_n(पूर्णांकr_info, PF_VECTOR);
पूर्ण

अटल अंतरभूत bool is_invalid_opcode(u32 पूर्णांकr_info)
अणु
	वापस is_exception_n(पूर्णांकr_info, UD_VECTOR);
पूर्ण

अटल अंतरभूत bool is_gp_fault(u32 पूर्णांकr_info)
अणु
	वापस is_exception_n(पूर्णांकr_info, GP_VECTOR);
पूर्ण

अटल अंतरभूत bool is_machine_check(u32 पूर्णांकr_info)
अणु
	वापस is_exception_n(पूर्णांकr_info, MC_VECTOR);
पूर्ण

/* Unकरोcumented: icebp/पूर्णांक1 */
अटल अंतरभूत bool is_icebp(u32 पूर्णांकr_info)
अणु
	वापस is_पूर्णांकr_type(पूर्णांकr_info, INTR_TYPE_PRIV_SW_EXCEPTION);
पूर्ण

अटल अंतरभूत bool is_nmi(u32 पूर्णांकr_info)
अणु
	वापस is_पूर्णांकr_type(पूर्णांकr_info, INTR_TYPE_NMI_INTR);
पूर्ण

अटल अंतरभूत bool is_बाह्यal_पूर्णांकr(u32 पूर्णांकr_info)
अणु
	वापस is_पूर्णांकr_type(पूर्णांकr_info, INTR_TYPE_EXT_INTR);
पूर्ण

अटल अंतरभूत bool is_exception_with_error_code(u32 पूर्णांकr_info)
अणु
	स्थिर u32 mask = INTR_INFO_VALID_MASK | INTR_INFO_DELIVER_CODE_MASK;

	वापस (पूर्णांकr_info & mask) == mask;
पूर्ण

क्रमागत vmcs_field_width अणु
	VMCS_FIELD_WIDTH_U16 = 0,
	VMCS_FIELD_WIDTH_U64 = 1,
	VMCS_FIELD_WIDTH_U32 = 2,
	VMCS_FIELD_WIDTH_NATURAL_WIDTH = 3
पूर्ण;

अटल अंतरभूत पूर्णांक vmcs_field_width(अचिन्हित दीर्घ field)
अणु
	अगर (0x1 & field)	/* the *_HIGH fields are all 32 bit */
		वापस VMCS_FIELD_WIDTH_U32;
	वापस (field >> 13) & 0x3;
पूर्ण

अटल अंतरभूत पूर्णांक vmcs_field_पढ़ोonly(अचिन्हित दीर्घ field)
अणु
	वापस (((field >> 10) & 0x3) == 1);
पूर्ण

#पूर्ण_अगर /* __KVM_X86_VMX_VMCS_H */
