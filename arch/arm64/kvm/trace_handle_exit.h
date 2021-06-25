<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_HANDLE_EXIT_ARM64_KVM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_HANDLE_EXIT_ARM64_KVM_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "sys_regs.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm

TRACE_EVENT(kvm_wfx_arm64,
	TP_PROTO(अचिन्हित दीर्घ vcpu_pc, bool is_wfe),
	TP_ARGS(vcpu_pc, is_wfe),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ,	vcpu_pc)
		__field(bool,		is_wfe)
	),

	TP_fast_assign(
		__entry->vcpu_pc = vcpu_pc;
		__entry->is_wfe  = is_wfe;
	),

	TP_prपूर्णांकk("guest executed wf%c at: 0x%016lx",
		  __entry->is_wfe ? 'e' : 'i', __entry->vcpu_pc)
);

TRACE_EVENT(kvm_hvc_arm64,
	TP_PROTO(अचिन्हित दीर्घ vcpu_pc, अचिन्हित दीर्घ r0, अचिन्हित दीर्घ imm),
	TP_ARGS(vcpu_pc, r0, imm),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, vcpu_pc)
		__field(अचिन्हित दीर्घ, r0)
		__field(अचिन्हित दीर्घ, imm)
	),

	TP_fast_assign(
		__entry->vcpu_pc = vcpu_pc;
		__entry->r0 = r0;
		__entry->imm = imm;
	),

	TP_prपूर्णांकk("HVC at 0x%016lx (r0: 0x%016lx, imm: 0x%lx)",
		  __entry->vcpu_pc, __entry->r0, __entry->imm)
);

TRACE_EVENT(kvm_arm_setup_debug,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu, __u32 guest_debug),
	TP_ARGS(vcpu, guest_debug),

	TP_STRUCT__entry(
		__field(काष्ठा kvm_vcpu *, vcpu)
		__field(__u32, guest_debug)
	),

	TP_fast_assign(
		__entry->vcpu = vcpu;
		__entry->guest_debug = guest_debug;
	),

	TP_prपूर्णांकk("vcpu: %p, flags: 0x%08x", __entry->vcpu, __entry->guest_debug)
);

TRACE_EVENT(kvm_arm_clear_debug,
	TP_PROTO(__u32 guest_debug),
	TP_ARGS(guest_debug),

	TP_STRUCT__entry(
		__field(__u32, guest_debug)
	),

	TP_fast_assign(
		__entry->guest_debug = guest_debug;
	),

	TP_prपूर्णांकk("flags: 0x%08x", __entry->guest_debug)
);

TRACE_EVENT(kvm_arm_set_dreg32,
	TP_PROTO(स्थिर अक्षर *name, __u32 value),
	TP_ARGS(name, value),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, name)
		__field(__u32, value)
	),

	TP_fast_assign(
		__entry->name = name;
		__entry->value = value;
	),

	TP_prपूर्णांकk("%s: 0x%08x", __entry->name, __entry->value)
);

TRACE_DEFINE_SIZखातापूर्ण(__u64);

TRACE_EVENT(kvm_arm_set_regset,
	TP_PROTO(स्थिर अक्षर *type, पूर्णांक len, __u64 *control, __u64 *value),
	TP_ARGS(type, len, control, value),
	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, name)
		__field(पूर्णांक, len)
		__array(u64, ctrls, 16)
		__array(u64, values, 16)
	),
	TP_fast_assign(
		__entry->name = type;
		__entry->len = len;
		स_नकल(__entry->ctrls, control, len << 3);
		स_नकल(__entry->values, value, len << 3);
	),
	TP_prपूर्णांकk("%d %s CTRL:%s VALUE:%s", __entry->len, __entry->name,
		__prपूर्णांक_array(__entry->ctrls, __entry->len, माप(__u64)),
		__prपूर्णांक_array(__entry->values, __entry->len, माप(__u64)))
);

TRACE_EVENT(trap_reg,
	TP_PROTO(स्थिर अक्षर *fn, पूर्णांक reg, bool is_ग_लिखो, u64 ग_लिखो_value),
	TP_ARGS(fn, reg, is_ग_लिखो, ग_लिखो_value),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, fn)
		__field(पूर्णांक, reg)
		__field(bool, is_ग_लिखो)
		__field(u64, ग_लिखो_value)
	),

	TP_fast_assign(
		__entry->fn = fn;
		__entry->reg = reg;
		__entry->is_ग_लिखो = is_ग_लिखो;
		__entry->ग_लिखो_value = ग_लिखो_value;
	),

	TP_prपूर्णांकk("%s %s reg %d (0x%016llx)", __entry->fn,  __entry->is_ग_लिखो?"write to":"read from", __entry->reg, __entry->ग_लिखो_value)
);

TRACE_EVENT(kvm_handle_sys_reg,
	TP_PROTO(अचिन्हित दीर्घ hsr),
	TP_ARGS(hsr),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ,	hsr)
	),

	TP_fast_assign(
		__entry->hsr = hsr;
	),

	TP_prपूर्णांकk("HSR 0x%08lx", __entry->hsr)
);

TRACE_EVENT(kvm_sys_access,
	TP_PROTO(अचिन्हित दीर्घ vcpu_pc, काष्ठा sys_reg_params *params, स्थिर काष्ठा sys_reg_desc *reg),
	TP_ARGS(vcpu_pc, params, reg),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ,			vcpu_pc)
		__field(bool,				is_ग_लिखो)
		__field(स्थिर अक्षर *,			name)
		__field(u8,				Op0)
		__field(u8,				Op1)
		__field(u8,				CRn)
		__field(u8,				CRm)
		__field(u8,				Op2)
	),

	TP_fast_assign(
		__entry->vcpu_pc = vcpu_pc;
		__entry->is_ग_लिखो = params->is_ग_लिखो;
		__entry->name = reg->name;
		__entry->Op0 = reg->Op0;
		__entry->Op0 = reg->Op0;
		__entry->Op1 = reg->Op1;
		__entry->CRn = reg->CRn;
		__entry->CRm = reg->CRm;
		__entry->Op2 = reg->Op2;
	),

	TP_prपूर्णांकk("PC: %lx %s (%d,%d,%d,%d,%d) %s",
		  __entry->vcpu_pc, __entry->name ?: "UNKN",
		  __entry->Op0, __entry->Op1, __entry->CRn,
		  __entry->CRm, __entry->Op2,
		  __entry->is_ग_लिखो ? "write" : "read")
);

TRACE_EVENT(kvm_set_guest_debug,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu, __u32 guest_debug),
	TP_ARGS(vcpu, guest_debug),

	TP_STRUCT__entry(
		__field(काष्ठा kvm_vcpu *, vcpu)
		__field(__u32, guest_debug)
	),

	TP_fast_assign(
		__entry->vcpu = vcpu;
		__entry->guest_debug = guest_debug;
	),

	TP_prपूर्णांकk("vcpu: %p, flags: 0x%08x", __entry->vcpu, __entry->guest_debug)
);

#पूर्ण_अगर /* _TRACE_HANDLE_EXIT_ARM64_KVM_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace_handle_निकास

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
