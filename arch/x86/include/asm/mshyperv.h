<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MSHYPER_H
#घोषणा _ASM_X86_MSHYPER_H

#समावेश <linux/types.h>
#समावेश <linux/nmi.h>
#समावेश <linux/msi.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hyperv-tlfs.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/mshyperv.h>

प्रकार पूर्णांक (*hyperv_fill_flush_list_func)(
		काष्ठा hv_guest_mapping_flush_list *flush,
		व्योम *data);

अटल अंतरभूत व्योम hv_set_रेजिस्टर(अचिन्हित पूर्णांक reg, u64 value)
अणु
	wrmsrl(reg, value);
पूर्ण

अटल अंतरभूत u64 hv_get_रेजिस्टर(अचिन्हित पूर्णांक reg)
अणु
	u64 value;

	rdmsrl(reg, value);
	वापस value;
पूर्ण

#घोषणा hv_get_raw_समयr() rdtsc_ordered()

व्योम hyperv_vector_handler(काष्ठा pt_regs *regs);

#अगर IS_ENABLED(CONFIG_HYPERV)
बाह्य पूर्णांक hyperv_init_cpuhp;

बाह्य व्योम *hv_hypercall_pg;
बाह्य व्योम  __percpu  **hyperv_pcpu_input_arg;
बाह्य व्योम  __percpu  **hyperv_pcpu_output_arg;

बाह्य u64 hv_current_partition_id;

पूर्णांक hv_call_deposit_pages(पूर्णांक node, u64 partition_id, u32 num_pages);
पूर्णांक hv_call_add_logical_proc(पूर्णांक node, u32 lp_index, u32 acpi_id);
पूर्णांक hv_call_create_vp(पूर्णांक node, u64 partition_id, u32 vp_index, u32 flags);

अटल अंतरभूत u64 hv_करो_hypercall(u64 control, व्योम *input, व्योम *output)
अणु
	u64 input_address = input ? virt_to_phys(input) : 0;
	u64 output_address = output ? virt_to_phys(output) : 0;
	u64 hv_status;

#अगर_घोषित CONFIG_X86_64
	अगर (!hv_hypercall_pg)
		वापस U64_MAX;

	__यंत्र__ __अस्थिर__("mov %4, %%r8\n"
			     CALL_NOSPEC
			     : "=a" (hv_status), ASM_CALL_CONSTRAINT,
			       "+c" (control), "+d" (input_address)
			     :  "r" (output_address),
				THUNK_TARGET(hv_hypercall_pg)
			     : "cc", "memory", "r8", "r9", "r10", "r11");
#अन्यथा
	u32 input_address_hi = upper_32_bits(input_address);
	u32 input_address_lo = lower_32_bits(input_address);
	u32 output_address_hi = upper_32_bits(output_address);
	u32 output_address_lo = lower_32_bits(output_address);

	अगर (!hv_hypercall_pg)
		वापस U64_MAX;

	__यंत्र__ __अस्थिर__(CALL_NOSPEC
			     : "=A" (hv_status),
			       "+c" (input_address_lo), ASM_CALL_CONSTRAINT
			     : "A" (control),
			       "b" (input_address_hi),
			       "D"(output_address_hi), "S"(output_address_lo),
			       THUNK_TARGET(hv_hypercall_pg)
			     : "cc", "memory");
#पूर्ण_अगर /* !x86_64 */
	वापस hv_status;
पूर्ण

/* Fast hypercall with 8 bytes of input and no output */
अटल अंतरभूत u64 hv_करो_fast_hypercall8(u16 code, u64 input1)
अणु
	u64 hv_status, control = (u64)code | HV_HYPERCALL_FAST_BIT;

#अगर_घोषित CONFIG_X86_64
	अणु
		__यंत्र__ __अस्थिर__(CALL_NOSPEC
				     : "=a" (hv_status), ASM_CALL_CONSTRAINT,
				       "+c" (control), "+d" (input1)
				     : THUNK_TARGET(hv_hypercall_pg)
				     : "cc", "r8", "r9", "r10", "r11");
	पूर्ण
#अन्यथा
	अणु
		u32 input1_hi = upper_32_bits(input1);
		u32 input1_lo = lower_32_bits(input1);

		__यंत्र__ __अस्थिर__ (CALL_NOSPEC
				      : "=A"(hv_status),
					"+c"(input1_lo),
					ASM_CALL_CONSTRAINT
				      :	"A" (control),
					"b" (input1_hi),
					THUNK_TARGET(hv_hypercall_pg)
				      : "cc", "edi", "esi");
	पूर्ण
#पूर्ण_अगर
		वापस hv_status;
पूर्ण

/* Fast hypercall with 16 bytes of input */
अटल अंतरभूत u64 hv_करो_fast_hypercall16(u16 code, u64 input1, u64 input2)
अणु
	u64 hv_status, control = (u64)code | HV_HYPERCALL_FAST_BIT;

#अगर_घोषित CONFIG_X86_64
	अणु
		__यंत्र__ __अस्थिर__("mov %4, %%r8\n"
				     CALL_NOSPEC
				     : "=a" (hv_status), ASM_CALL_CONSTRAINT,
				       "+c" (control), "+d" (input1)
				     : "r" (input2),
				       THUNK_TARGET(hv_hypercall_pg)
				     : "cc", "r8", "r9", "r10", "r11");
	पूर्ण
#अन्यथा
	अणु
		u32 input1_hi = upper_32_bits(input1);
		u32 input1_lo = lower_32_bits(input1);
		u32 input2_hi = upper_32_bits(input2);
		u32 input2_lo = lower_32_bits(input2);

		__यंत्र__ __अस्थिर__ (CALL_NOSPEC
				      : "=A"(hv_status),
					"+c"(input1_lo), ASM_CALL_CONSTRAINT
				      :	"A" (control), "b" (input1_hi),
					"D"(input2_hi), "S"(input2_lo),
					THUNK_TARGET(hv_hypercall_pg)
				      : "cc");
	पूर्ण
#पूर्ण_अगर
	वापस hv_status;
पूर्ण

बाह्य काष्ठा hv_vp_assist_page **hv_vp_assist_page;

अटल अंतरभूत काष्ठा hv_vp_assist_page *hv_get_vp_assist_page(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!hv_vp_assist_page)
		वापस शून्य;

	वापस hv_vp_assist_page[cpu];
पूर्ण

व्योम __init hyperv_init(व्योम);
व्योम hyperv_setup_mmu_ops(व्योम);
व्योम set_hv_tscchange_cb(व्योम (*cb)(व्योम));
व्योम clear_hv_tscchange_cb(व्योम);
व्योम hyperv_stop_tsc_emulation(व्योम);
पूर्णांक hyperv_flush_guest_mapping(u64 as);
पूर्णांक hyperv_flush_guest_mapping_range(u64 as,
		hyperv_fill_flush_list_func fill_func, व्योम *data);
पूर्णांक hyperv_fill_flush_guest_mapping_list(
		काष्ठा hv_guest_mapping_flush_list *flush,
		u64 start_gfn, u64 end_gfn);

बाह्य bool hv_root_partition;

#अगर_घोषित CONFIG_X86_64
व्योम hv_apic_init(व्योम);
व्योम __init hv_init_spinlocks(व्योम);
bool hv_vcpu_is_preempted(पूर्णांक vcpu);
#अन्यथा
अटल अंतरभूत व्योम hv_apic_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम hv_set_msi_entry_from_desc(जोड़ hv_msi_entry *msi_entry,
					      काष्ठा msi_desc *msi_desc)
अणु
	msi_entry->address.as_uपूर्णांक32 = msi_desc->msg.address_lo;
	msi_entry->data.as_uपूर्णांक32 = msi_desc->msg.data;
पूर्ण

काष्ठा irq_करोमुख्य *hv_create_pci_msi_करोमुख्य(व्योम);

पूर्णांक hv_map_ioapic_पूर्णांकerrupt(पूर्णांक ioapic_id, bool level, पूर्णांक vcpu, पूर्णांक vector,
		काष्ठा hv_पूर्णांकerrupt_entry *entry);
पूर्णांक hv_unmap_ioapic_पूर्णांकerrupt(पूर्णांक ioapic_id, काष्ठा hv_पूर्णांकerrupt_entry *entry);

#अन्यथा /* CONFIG_HYPERV */
अटल अंतरभूत व्योम hyperv_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम hyperv_setup_mmu_ops(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम set_hv_tscchange_cb(व्योम (*cb)(व्योम)) अणुपूर्ण
अटल अंतरभूत व्योम clear_hv_tscchange_cb(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम hyperv_stop_tsc_emulation(व्योम) अणुपूर्ण;
अटल अंतरभूत काष्ठा hv_vp_assist_page *hv_get_vp_assist_page(अचिन्हित पूर्णांक cpu)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक hyperv_flush_guest_mapping(u64 as) अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक hyperv_flush_guest_mapping_range(u64 as,
		hyperv_fill_flush_list_func fill_func, व्योम *data)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर /* CONFIG_HYPERV */


#समावेश <यंत्र-generic/mshyperv.h>

#पूर्ण_अगर
