<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_VMCS12_H
#घोषणा __KVM_X86_VMX_VMCS12_H

#समावेश <linux/build_bug.h>

#समावेश "vmcs.h"

/*
 * काष्ठा vmcs12 describes the state that our guest hypervisor (L1) keeps क्रम a
 * single nested guest (L2), hence the name vmcs12. Any VMX implementation has
 * a VMCS काष्ठाure, and vmcs12 is our emulated VMX's VMCS. This काष्ठाure is
 * stored in guest memory specअगरied by VMPTRLD, but is opaque to the guest,
 * which must access it using VMREAD/VMWRITE/VMCLEAR inकाष्ठाions.
 * More than one of these काष्ठाures may exist, अगर L1 runs multiple L2 guests.
 * nested_vmx_run() will use the data here to build the vmcs02: a VMCS क्रम the
 * underlying hardware which will be used to run L2.
 * This काष्ठाure is packed to ensure that its layout is identical across
 * machines (necessary क्रम live migration).
 *
 * IMPORTANT: Changing the layout of existing fields in this काष्ठाure
 * will अवरोध save/restore compatibility with older kvm releases. When
 * adding new fields, either use space in the reserved padding* arrays
 * or add the new fields to the end of the काष्ठाure.
 */
प्रकार u64 natural_width;
काष्ठा __packed vmcs12 अणु
	/* According to the Intel spec, a VMCS region must start with the
	 * following two fields. Then follow implementation-specअगरic data.
	 */
	काष्ठा vmcs_hdr hdr;
	u32 पात;

	u32 launch_state; /* set to 0 by VMCLEAR, to 1 by VMLAUNCH */
	u32 padding[7]; /* room क्रम future expansion */

	u64 io_biपंचांगap_a;
	u64 io_biपंचांगap_b;
	u64 msr_biपंचांगap;
	u64 vm_निकास_msr_store_addr;
	u64 vm_निकास_msr_load_addr;
	u64 vm_entry_msr_load_addr;
	u64 tsc_offset;
	u64 भव_apic_page_addr;
	u64 apic_access_addr;
	u64 posted_पूर्णांकr_desc_addr;
	u64 ept_poपूर्णांकer;
	u64 eoi_निकास_biपंचांगap0;
	u64 eoi_निकास_biपंचांगap1;
	u64 eoi_निकास_biपंचांगap2;
	u64 eoi_निकास_biपंचांगap3;
	u64 xss_निकास_biपंचांगap;
	u64 guest_physical_address;
	u64 vmcs_link_poपूर्णांकer;
	u64 guest_ia32_debugctl;
	u64 guest_ia32_pat;
	u64 guest_ia32_efer;
	u64 guest_ia32_perf_global_ctrl;
	u64 guest_pdptr0;
	u64 guest_pdptr1;
	u64 guest_pdptr2;
	u64 guest_pdptr3;
	u64 guest_bndcfgs;
	u64 host_ia32_pat;
	u64 host_ia32_efer;
	u64 host_ia32_perf_global_ctrl;
	u64 vmपढ़ो_biपंचांगap;
	u64 vmग_लिखो_biपंचांगap;
	u64 vm_function_control;
	u64 eptp_list_address;
	u64 pml_address;
	u64 encls_निकासing_biपंचांगap;
	u64 padding64[2]; /* room क्रम future expansion */
	/*
	 * To allow migration of L1 (complete with its L2 guests) between
	 * machines of dअगरferent natural widths (32 or 64 bit), we cannot have
	 * अचिन्हित दीर्घ fields with no explicit size. We use u64 (aliased
	 * natural_width) instead. Luckily, x86 is little-endian.
	 */
	natural_width cr0_guest_host_mask;
	natural_width cr4_guest_host_mask;
	natural_width cr0_पढ़ो_shaकरोw;
	natural_width cr4_पढ़ो_shaकरोw;
	natural_width dead_space[4]; /* Last remnants of cr3_target_value[0-3]. */
	natural_width निकास_qualअगरication;
	natural_width guest_linear_address;
	natural_width guest_cr0;
	natural_width guest_cr3;
	natural_width guest_cr4;
	natural_width guest_es_base;
	natural_width guest_cs_base;
	natural_width guest_ss_base;
	natural_width guest_ds_base;
	natural_width guest_fs_base;
	natural_width guest_gs_base;
	natural_width guest_ldtr_base;
	natural_width guest_tr_base;
	natural_width guest_gdtr_base;
	natural_width guest_idtr_base;
	natural_width guest_dr7;
	natural_width guest_rsp;
	natural_width guest_rip;
	natural_width guest_rflags;
	natural_width guest_pending_dbg_exceptions;
	natural_width guest_sysenter_esp;
	natural_width guest_sysenter_eip;
	natural_width host_cr0;
	natural_width host_cr3;
	natural_width host_cr4;
	natural_width host_fs_base;
	natural_width host_gs_base;
	natural_width host_tr_base;
	natural_width host_gdtr_base;
	natural_width host_idtr_base;
	natural_width host_ia32_sysenter_esp;
	natural_width host_ia32_sysenter_eip;
	natural_width host_rsp;
	natural_width host_rip;
	natural_width paddingl[8]; /* room क्रम future expansion */
	u32 pin_based_vm_exec_control;
	u32 cpu_based_vm_exec_control;
	u32 exception_biपंचांगap;
	u32 page_fault_error_code_mask;
	u32 page_fault_error_code_match;
	u32 cr3_target_count;
	u32 vm_निकास_controls;
	u32 vm_निकास_msr_store_count;
	u32 vm_निकास_msr_load_count;
	u32 vm_entry_controls;
	u32 vm_entry_msr_load_count;
	u32 vm_entry_पूर्णांकr_info_field;
	u32 vm_entry_exception_error_code;
	u32 vm_entry_inकाष्ठाion_len;
	u32 tpr_threshold;
	u32 secondary_vm_exec_control;
	u32 vm_inकाष्ठाion_error;
	u32 vm_निकास_reason;
	u32 vm_निकास_पूर्णांकr_info;
	u32 vm_निकास_पूर्णांकr_error_code;
	u32 idt_vectoring_info_field;
	u32 idt_vectoring_error_code;
	u32 vm_निकास_inकाष्ठाion_len;
	u32 vmx_inकाष्ठाion_info;
	u32 guest_es_limit;
	u32 guest_cs_limit;
	u32 guest_ss_limit;
	u32 guest_ds_limit;
	u32 guest_fs_limit;
	u32 guest_gs_limit;
	u32 guest_ldtr_limit;
	u32 guest_tr_limit;
	u32 guest_gdtr_limit;
	u32 guest_idtr_limit;
	u32 guest_es_ar_bytes;
	u32 guest_cs_ar_bytes;
	u32 guest_ss_ar_bytes;
	u32 guest_ds_ar_bytes;
	u32 guest_fs_ar_bytes;
	u32 guest_gs_ar_bytes;
	u32 guest_ldtr_ar_bytes;
	u32 guest_tr_ar_bytes;
	u32 guest_पूर्णांकerruptibility_info;
	u32 guest_activity_state;
	u32 guest_sysenter_cs;
	u32 host_ia32_sysenter_cs;
	u32 vmx_preemption_समयr_value;
	u32 padding32[7]; /* room क्रम future expansion */
	u16 भव_processor_id;
	u16 posted_पूर्णांकr_nv;
	u16 guest_es_selector;
	u16 guest_cs_selector;
	u16 guest_ss_selector;
	u16 guest_ds_selector;
	u16 guest_fs_selector;
	u16 guest_gs_selector;
	u16 guest_ldtr_selector;
	u16 guest_tr_selector;
	u16 guest_पूर्णांकr_status;
	u16 host_es_selector;
	u16 host_cs_selector;
	u16 host_ss_selector;
	u16 host_ds_selector;
	u16 host_fs_selector;
	u16 host_gs_selector;
	u16 host_tr_selector;
	u16 guest_pml_index;
पूर्ण;

/*
 * VMCS12_REVISION is an arbitrary id that should be changed अगर the content or
 * layout of काष्ठा vmcs12 is changed. MSR_IA32_VMX_BASIC वापसs this id, and
 * VMPTRLD verअगरies that the VMCS region that L1 is loading contains this id.
 *
 * IMPORTANT: Changing this value will अवरोध save/restore compatibility with
 * older kvm releases.
 */
#घोषणा VMCS12_REVISION 0x11e57ed0

/*
 * VMCS12_SIZE is the number of bytes L1 should allocate क्रम the VMXON region
 * and any VMCS region. Although only माप(काष्ठा vmcs12) are used by the
 * current implementation, 4K are reserved to aव्योम future complications and
 * to preserve userspace ABI.
 */
#घोषणा VMCS12_SIZE		KVM_STATE_NESTED_VMX_VMCS_SIZE

/*
 * VMCS12_MAX_FIELD_INDEX is the highest index value used in any
 * supported VMCS12 field encoding.
 */
#घोषणा VMCS12_MAX_FIELD_INDEX 0x17

/*
 * For save/restore compatibility, the vmcs12 field offsets must not change.
 */
#घोषणा CHECK_OFFSET(field, loc)				\
	BUILD_BUG_ON_MSG(दुरत्व(काष्ठा vmcs12, field) != (loc),	\
		"Offset of " #field " in struct vmcs12 has changed.")

अटल अंतरभूत व्योम vmx_check_vmcs12_offsets(व्योम)
अणु
	CHECK_OFFSET(hdr, 0);
	CHECK_OFFSET(पात, 4);
	CHECK_OFFSET(launch_state, 8);
	CHECK_OFFSET(io_biपंचांगap_a, 40);
	CHECK_OFFSET(io_biपंचांगap_b, 48);
	CHECK_OFFSET(msr_biपंचांगap, 56);
	CHECK_OFFSET(vm_निकास_msr_store_addr, 64);
	CHECK_OFFSET(vm_निकास_msr_load_addr, 72);
	CHECK_OFFSET(vm_entry_msr_load_addr, 80);
	CHECK_OFFSET(tsc_offset, 88);
	CHECK_OFFSET(भव_apic_page_addr, 96);
	CHECK_OFFSET(apic_access_addr, 104);
	CHECK_OFFSET(posted_पूर्णांकr_desc_addr, 112);
	CHECK_OFFSET(ept_poपूर्णांकer, 120);
	CHECK_OFFSET(eoi_निकास_biपंचांगap0, 128);
	CHECK_OFFSET(eoi_निकास_biपंचांगap1, 136);
	CHECK_OFFSET(eoi_निकास_biपंचांगap2, 144);
	CHECK_OFFSET(eoi_निकास_biपंचांगap3, 152);
	CHECK_OFFSET(xss_निकास_biपंचांगap, 160);
	CHECK_OFFSET(guest_physical_address, 168);
	CHECK_OFFSET(vmcs_link_poपूर्णांकer, 176);
	CHECK_OFFSET(guest_ia32_debugctl, 184);
	CHECK_OFFSET(guest_ia32_pat, 192);
	CHECK_OFFSET(guest_ia32_efer, 200);
	CHECK_OFFSET(guest_ia32_perf_global_ctrl, 208);
	CHECK_OFFSET(guest_pdptr0, 216);
	CHECK_OFFSET(guest_pdptr1, 224);
	CHECK_OFFSET(guest_pdptr2, 232);
	CHECK_OFFSET(guest_pdptr3, 240);
	CHECK_OFFSET(guest_bndcfgs, 248);
	CHECK_OFFSET(host_ia32_pat, 256);
	CHECK_OFFSET(host_ia32_efer, 264);
	CHECK_OFFSET(host_ia32_perf_global_ctrl, 272);
	CHECK_OFFSET(vmपढ़ो_biपंचांगap, 280);
	CHECK_OFFSET(vmग_लिखो_biपंचांगap, 288);
	CHECK_OFFSET(vm_function_control, 296);
	CHECK_OFFSET(eptp_list_address, 304);
	CHECK_OFFSET(pml_address, 312);
	CHECK_OFFSET(encls_निकासing_biपंचांगap, 320);
	CHECK_OFFSET(cr0_guest_host_mask, 344);
	CHECK_OFFSET(cr4_guest_host_mask, 352);
	CHECK_OFFSET(cr0_पढ़ो_shaकरोw, 360);
	CHECK_OFFSET(cr4_पढ़ो_shaकरोw, 368);
	CHECK_OFFSET(dead_space, 376);
	CHECK_OFFSET(निकास_qualअगरication, 408);
	CHECK_OFFSET(guest_linear_address, 416);
	CHECK_OFFSET(guest_cr0, 424);
	CHECK_OFFSET(guest_cr3, 432);
	CHECK_OFFSET(guest_cr4, 440);
	CHECK_OFFSET(guest_es_base, 448);
	CHECK_OFFSET(guest_cs_base, 456);
	CHECK_OFFSET(guest_ss_base, 464);
	CHECK_OFFSET(guest_ds_base, 472);
	CHECK_OFFSET(guest_fs_base, 480);
	CHECK_OFFSET(guest_gs_base, 488);
	CHECK_OFFSET(guest_ldtr_base, 496);
	CHECK_OFFSET(guest_tr_base, 504);
	CHECK_OFFSET(guest_gdtr_base, 512);
	CHECK_OFFSET(guest_idtr_base, 520);
	CHECK_OFFSET(guest_dr7, 528);
	CHECK_OFFSET(guest_rsp, 536);
	CHECK_OFFSET(guest_rip, 544);
	CHECK_OFFSET(guest_rflags, 552);
	CHECK_OFFSET(guest_pending_dbg_exceptions, 560);
	CHECK_OFFSET(guest_sysenter_esp, 568);
	CHECK_OFFSET(guest_sysenter_eip, 576);
	CHECK_OFFSET(host_cr0, 584);
	CHECK_OFFSET(host_cr3, 592);
	CHECK_OFFSET(host_cr4, 600);
	CHECK_OFFSET(host_fs_base, 608);
	CHECK_OFFSET(host_gs_base, 616);
	CHECK_OFFSET(host_tr_base, 624);
	CHECK_OFFSET(host_gdtr_base, 632);
	CHECK_OFFSET(host_idtr_base, 640);
	CHECK_OFFSET(host_ia32_sysenter_esp, 648);
	CHECK_OFFSET(host_ia32_sysenter_eip, 656);
	CHECK_OFFSET(host_rsp, 664);
	CHECK_OFFSET(host_rip, 672);
	CHECK_OFFSET(pin_based_vm_exec_control, 744);
	CHECK_OFFSET(cpu_based_vm_exec_control, 748);
	CHECK_OFFSET(exception_biपंचांगap, 752);
	CHECK_OFFSET(page_fault_error_code_mask, 756);
	CHECK_OFFSET(page_fault_error_code_match, 760);
	CHECK_OFFSET(cr3_target_count, 764);
	CHECK_OFFSET(vm_निकास_controls, 768);
	CHECK_OFFSET(vm_निकास_msr_store_count, 772);
	CHECK_OFFSET(vm_निकास_msr_load_count, 776);
	CHECK_OFFSET(vm_entry_controls, 780);
	CHECK_OFFSET(vm_entry_msr_load_count, 784);
	CHECK_OFFSET(vm_entry_पूर्णांकr_info_field, 788);
	CHECK_OFFSET(vm_entry_exception_error_code, 792);
	CHECK_OFFSET(vm_entry_inकाष्ठाion_len, 796);
	CHECK_OFFSET(tpr_threshold, 800);
	CHECK_OFFSET(secondary_vm_exec_control, 804);
	CHECK_OFFSET(vm_inकाष्ठाion_error, 808);
	CHECK_OFFSET(vm_निकास_reason, 812);
	CHECK_OFFSET(vm_निकास_पूर्णांकr_info, 816);
	CHECK_OFFSET(vm_निकास_पूर्णांकr_error_code, 820);
	CHECK_OFFSET(idt_vectoring_info_field, 824);
	CHECK_OFFSET(idt_vectoring_error_code, 828);
	CHECK_OFFSET(vm_निकास_inकाष्ठाion_len, 832);
	CHECK_OFFSET(vmx_inकाष्ठाion_info, 836);
	CHECK_OFFSET(guest_es_limit, 840);
	CHECK_OFFSET(guest_cs_limit, 844);
	CHECK_OFFSET(guest_ss_limit, 848);
	CHECK_OFFSET(guest_ds_limit, 852);
	CHECK_OFFSET(guest_fs_limit, 856);
	CHECK_OFFSET(guest_gs_limit, 860);
	CHECK_OFFSET(guest_ldtr_limit, 864);
	CHECK_OFFSET(guest_tr_limit, 868);
	CHECK_OFFSET(guest_gdtr_limit, 872);
	CHECK_OFFSET(guest_idtr_limit, 876);
	CHECK_OFFSET(guest_es_ar_bytes, 880);
	CHECK_OFFSET(guest_cs_ar_bytes, 884);
	CHECK_OFFSET(guest_ss_ar_bytes, 888);
	CHECK_OFFSET(guest_ds_ar_bytes, 892);
	CHECK_OFFSET(guest_fs_ar_bytes, 896);
	CHECK_OFFSET(guest_gs_ar_bytes, 900);
	CHECK_OFFSET(guest_ldtr_ar_bytes, 904);
	CHECK_OFFSET(guest_tr_ar_bytes, 908);
	CHECK_OFFSET(guest_पूर्णांकerruptibility_info, 912);
	CHECK_OFFSET(guest_activity_state, 916);
	CHECK_OFFSET(guest_sysenter_cs, 920);
	CHECK_OFFSET(host_ia32_sysenter_cs, 924);
	CHECK_OFFSET(vmx_preemption_समयr_value, 928);
	CHECK_OFFSET(भव_processor_id, 960);
	CHECK_OFFSET(posted_पूर्णांकr_nv, 962);
	CHECK_OFFSET(guest_es_selector, 964);
	CHECK_OFFSET(guest_cs_selector, 966);
	CHECK_OFFSET(guest_ss_selector, 968);
	CHECK_OFFSET(guest_ds_selector, 970);
	CHECK_OFFSET(guest_fs_selector, 972);
	CHECK_OFFSET(guest_gs_selector, 974);
	CHECK_OFFSET(guest_ldtr_selector, 976);
	CHECK_OFFSET(guest_tr_selector, 978);
	CHECK_OFFSET(guest_पूर्णांकr_status, 980);
	CHECK_OFFSET(host_es_selector, 982);
	CHECK_OFFSET(host_cs_selector, 984);
	CHECK_OFFSET(host_ss_selector, 986);
	CHECK_OFFSET(host_ds_selector, 988);
	CHECK_OFFSET(host_fs_selector, 990);
	CHECK_OFFSET(host_gs_selector, 992);
	CHECK_OFFSET(host_tr_selector, 994);
	CHECK_OFFSET(guest_pml_index, 996);
पूर्ण

बाह्य स्थिर अचिन्हित लघु vmcs_field_to_offset_table[];
बाह्य स्थिर अचिन्हित पूर्णांक nr_vmcs12_fields;

#घोषणा ROL16(val, n) ((u16)(((u16)(val) << (n)) | ((u16)(val) >> (16 - (n)))))

अटल अंतरभूत लघु vmcs_field_to_offset(अचिन्हित दीर्घ field)
अणु
	अचिन्हित लघु offset;
	अचिन्हित पूर्णांक index;

	अगर (field >> 15)
		वापस -ENOENT;

	index = ROL16(field, 6);
	अगर (index >= nr_vmcs12_fields)
		वापस -ENOENT;

	index = array_index_nospec(index, nr_vmcs12_fields);
	offset = vmcs_field_to_offset_table[index];
	अगर (offset == 0)
		वापस -ENOENT;
	वापस offset;
पूर्ण

#अघोषित ROL16

अटल अंतरभूत u64 vmcs12_पढ़ो_any(काष्ठा vmcs12 *vmcs12, अचिन्हित दीर्घ field,
				  u16 offset)
अणु
	अक्षर *p = (अक्षर *)vmcs12 + offset;

	चयन (vmcs_field_width(field)) अणु
	हाल VMCS_FIELD_WIDTH_NATURAL_WIDTH:
		वापस *((natural_width *)p);
	हाल VMCS_FIELD_WIDTH_U16:
		वापस *((u16 *)p);
	हाल VMCS_FIELD_WIDTH_U32:
		वापस *((u32 *)p);
	हाल VMCS_FIELD_WIDTH_U64:
		वापस *((u64 *)p);
	शेष:
		WARN_ON_ONCE(1);
		वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम vmcs12_ग_लिखो_any(काष्ठा vmcs12 *vmcs12, अचिन्हित दीर्घ field,
				    u16 offset, u64 field_value)
अणु
	अक्षर *p = (अक्षर *)vmcs12 + offset;

	चयन (vmcs_field_width(field)) अणु
	हाल VMCS_FIELD_WIDTH_U16:
		*(u16 *)p = field_value;
		अवरोध;
	हाल VMCS_FIELD_WIDTH_U32:
		*(u32 *)p = field_value;
		अवरोध;
	हाल VMCS_FIELD_WIDTH_U64:
		*(u64 *)p = field_value;
		अवरोध;
	हाल VMCS_FIELD_WIDTH_NATURAL_WIDTH:
		*(natural_width *)p = field_value;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __KVM_X86_VMX_VMCS12_H */
