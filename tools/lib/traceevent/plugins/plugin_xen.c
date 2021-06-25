<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "event-parse.h"
#समावेश "trace-seq.h"

#घोषणा __HYPERVISOR_set_trap_table			0
#घोषणा __HYPERVISOR_mmu_update				1
#घोषणा __HYPERVISOR_set_gdt				2
#घोषणा __HYPERVISOR_stack_चयन			3
#घोषणा __HYPERVISOR_set_callbacks			4
#घोषणा __HYPERVISOR_fpu_taskचयन			5
#घोषणा __HYPERVISOR_sched_op_compat			6
#घोषणा __HYPERVISOR_करोm0_op				7
#घोषणा __HYPERVISOR_set_debugreg			8
#घोषणा __HYPERVISOR_get_debugreg			9
#घोषणा __HYPERVISOR_update_descriptor			10
#घोषणा __HYPERVISOR_memory_op				12
#घोषणा __HYPERVISOR_multicall				13
#घोषणा __HYPERVISOR_update_va_mapping			14
#घोषणा __HYPERVISOR_set_समयr_op			15
#घोषणा __HYPERVISOR_event_channel_op_compat		16
#घोषणा __HYPERVISOR_xen_version			17
#घोषणा __HYPERVISOR_console_io				18
#घोषणा __HYPERVISOR_physdev_op_compat			19
#घोषणा __HYPERVISOR_grant_table_op			20
#घोषणा __HYPERVISOR_vm_assist				21
#घोषणा __HYPERVISOR_update_va_mapping_otherकरोमुख्य	22
#घोषणा __HYPERVISOR_iret				23 /* x86 only */
#घोषणा __HYPERVISOR_vcpu_op				24
#घोषणा __HYPERVISOR_set_segment_base			25 /* x86/64 only */
#घोषणा __HYPERVISOR_mmuext_op				26
#घोषणा __HYPERVISOR_acm_op				27
#घोषणा __HYPERVISOR_nmi_op				28
#घोषणा __HYPERVISOR_sched_op				29
#घोषणा __HYPERVISOR_callback_op			30
#घोषणा __HYPERVISOR_xenoprof_op			31
#घोषणा __HYPERVISOR_event_channel_op			32
#घोषणा __HYPERVISOR_physdev_op				33
#घोषणा __HYPERVISOR_hvm_op				34
#घोषणा __HYPERVISOR_पंचांगem_op				38

/* Architecture-specअगरic hypercall definitions. */
#घोषणा __HYPERVISOR_arch_0				48
#घोषणा __HYPERVISOR_arch_1				49
#घोषणा __HYPERVISOR_arch_2				50
#घोषणा __HYPERVISOR_arch_3				51
#घोषणा __HYPERVISOR_arch_4				52
#घोषणा __HYPERVISOR_arch_5				53
#घोषणा __HYPERVISOR_arch_6				54
#घोषणा __HYPERVISOR_arch_7				55

#घोषणा N(x)	[__HYPERVISOR_##x] = "("#x")"
अटल स्थिर अक्षर *xen_hypercall_names[] = अणु
	N(set_trap_table),
	N(mmu_update),
	N(set_gdt),
	N(stack_चयन),
	N(set_callbacks),
	N(fpu_taskचयन),
	N(sched_op_compat),
	N(करोm0_op),
	N(set_debugreg),
	N(get_debugreg),
	N(update_descriptor),
	N(memory_op),
	N(multicall),
	N(update_va_mapping),
	N(set_समयr_op),
	N(event_channel_op_compat),
	N(xen_version),
	N(console_io),
	N(physdev_op_compat),
	N(grant_table_op),
	N(vm_assist),
	N(update_va_mapping_otherकरोमुख्य),
	N(iret),
	N(vcpu_op),
	N(set_segment_base),
	N(mmuext_op),
	N(acm_op),
	N(nmi_op),
	N(sched_op),
	N(callback_op),
	N(xenoprof_op),
	N(event_channel_op),
	N(physdev_op),
	N(hvm_op),

/* Architecture-specअगरic hypercall definitions. */
	N(arch_0),
	N(arch_1),
	N(arch_2),
	N(arch_3),
	N(arch_4),
	N(arch_5),
	N(arch_6),
	N(arch_7),
पूर्ण;
#अघोषित N

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

अटल स्थिर अक्षर *xen_hypercall_name(अचिन्हित op)
अणु
	अगर (op < ARRAY_SIZE(xen_hypercall_names) &&
	    xen_hypercall_names[op] != शून्य)
		वापस xen_hypercall_names[op];

	वापस "";
पूर्ण

अचिन्हित दीर्घ दीर्घ process_xen_hypercall_name(काष्ठा trace_seq *s,
					      अचिन्हित दीर्घ दीर्घ *args)
अणु
	अचिन्हित पूर्णांक op = args[0];

	trace_seq_म_लिखो(s, "%s", xen_hypercall_name(op));
	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_prपूर्णांक_function(tep,
				    process_xen_hypercall_name,
				    TEP_FUNC_ARG_STRING,
				    "xen_hypercall_name",
				    TEP_FUNC_ARG_INT,
				    TEP_FUNC_ARG_VOID);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_prपूर्णांक_function(tep, process_xen_hypercall_name,
				      "xen_hypercall_name");
पूर्ण
