<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_ARM_ARM64_KVM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_ARM_ARM64_KVM_H

#समावेश <kvm/arm_arch_समयr.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm

/*
 * Tracepoपूर्णांकs क्रम entry/निकास to guest
 */
TRACE_EVENT(kvm_entry,
	TP_PROTO(अचिन्हित दीर्घ vcpu_pc),
	TP_ARGS(vcpu_pc),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	vcpu_pc		)
	),

	TP_fast_assign(
		__entry->vcpu_pc		= vcpu_pc;
	),

	TP_prपूर्णांकk("PC: 0x%016lx", __entry->vcpu_pc)
);

TRACE_EVENT(kvm_निकास,
	TP_PROTO(पूर्णांक ret, अचिन्हित पूर्णांक esr_ec, अचिन्हित दीर्घ vcpu_pc),
	TP_ARGS(ret, esr_ec, vcpu_pc),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		ret		)
		__field(	अचिन्हित पूर्णांक,	esr_ec		)
		__field(	अचिन्हित दीर्घ,	vcpu_pc		)
	),

	TP_fast_assign(
		__entry->ret			= ARM_EXCEPTION_CODE(ret);
		__entry->esr_ec = ARM_EXCEPTION_IS_TRAP(ret) ? esr_ec : 0;
		__entry->vcpu_pc		= vcpu_pc;
	),

	TP_prपूर्णांकk("%s: HSR_EC: 0x%04x (%s), PC: 0x%016lx",
		  __prपूर्णांक_symbolic(__entry->ret, kvm_arm_exception_type),
		  __entry->esr_ec,
		  __prपूर्णांक_symbolic(__entry->esr_ec, kvm_arm_exception_class),
		  __entry->vcpu_pc)
);

TRACE_EVENT(kvm_guest_fault,
	TP_PROTO(अचिन्हित दीर्घ vcpu_pc, अचिन्हित दीर्घ hsr,
		 अचिन्हित दीर्घ hxfar,
		 अचिन्हित दीर्घ दीर्घ ipa),
	TP_ARGS(vcpu_pc, hsr, hxfar, ipa),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	vcpu_pc		)
		__field(	अचिन्हित दीर्घ,	hsr		)
		__field(	अचिन्हित दीर्घ,	hxfar		)
		__field(   अचिन्हित दीर्घ दीर्घ,	ipa		)
	),

	TP_fast_assign(
		__entry->vcpu_pc		= vcpu_pc;
		__entry->hsr			= hsr;
		__entry->hxfar			= hxfar;
		__entry->ipa			= ipa;
	),

	TP_prपूर्णांकk("ipa %#llx, hsr %#08lx, hxfar %#08lx, pc %#016lx",
		  __entry->ipa, __entry->hsr,
		  __entry->hxfar, __entry->vcpu_pc)
);

TRACE_EVENT(kvm_access_fault,
	TP_PROTO(अचिन्हित दीर्घ ipa),
	TP_ARGS(ipa),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	ipa		)
	),

	TP_fast_assign(
		__entry->ipa		= ipa;
	),

	TP_prपूर्णांकk("IPA: %lx", __entry->ipa)
);

TRACE_EVENT(kvm_irq_line,
	TP_PROTO(अचिन्हित पूर्णांक type, पूर्णांक vcpu_idx, पूर्णांक irq_num, पूर्णांक level),
	TP_ARGS(type, vcpu_idx, irq_num, level),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	type		)
		__field(	पूर्णांक,		vcpu_idx	)
		__field(	पूर्णांक,		irq_num		)
		__field(	पूर्णांक,		level		)
	),

	TP_fast_assign(
		__entry->type		= type;
		__entry->vcpu_idx	= vcpu_idx;
		__entry->irq_num	= irq_num;
		__entry->level		= level;
	),

	TP_prपूर्णांकk("Inject %s interrupt (%d), vcpu->idx: %d, num: %d, level: %d",
		  (__entry->type == KVM_ARM_IRQ_TYPE_CPU) ? "CPU" :
		  (__entry->type == KVM_ARM_IRQ_TYPE_PPI) ? "VGIC PPI" :
		  (__entry->type == KVM_ARM_IRQ_TYPE_SPI) ? "VGIC SPI" : "UNKNOWN",
		  __entry->type, __entry->vcpu_idx, __entry->irq_num, __entry->level)
);

TRACE_EVENT(kvm_mmio_emulate,
	TP_PROTO(अचिन्हित दीर्घ vcpu_pc, अचिन्हित दीर्घ instr,
		 अचिन्हित दीर्घ cpsr),
	TP_ARGS(vcpu_pc, instr, cpsr),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	vcpu_pc		)
		__field(	अचिन्हित दीर्घ,	instr		)
		__field(	अचिन्हित दीर्घ,	cpsr		)
	),

	TP_fast_assign(
		__entry->vcpu_pc		= vcpu_pc;
		__entry->instr			= instr;
		__entry->cpsr			= cpsr;
	),

	TP_prपूर्णांकk("Emulate MMIO at: 0x%016lx (instr: %08lx, cpsr: %08lx)",
		  __entry->vcpu_pc, __entry->instr, __entry->cpsr)
);

TRACE_EVENT(kvm_set_way_flush,
	    TP_PROTO(अचिन्हित दीर्घ vcpu_pc, bool cache),
	    TP_ARGS(vcpu_pc, cache),

	    TP_STRUCT__entry(
		    __field(	अचिन्हित दीर्घ,	vcpu_pc		)
		    __field(	bool,		cache		)
	    ),

	    TP_fast_assign(
		    __entry->vcpu_pc		= vcpu_pc;
		    __entry->cache		= cache;
	    ),

	    TP_prपूर्णांकk("S/W flush at 0x%016lx (cache %s)",
		      __entry->vcpu_pc, __entry->cache ? "on" : "off")
);

TRACE_EVENT(kvm_toggle_cache,
	    TP_PROTO(अचिन्हित दीर्घ vcpu_pc, bool was, bool now),
	    TP_ARGS(vcpu_pc, was, now),

	    TP_STRUCT__entry(
		    __field(	अचिन्हित दीर्घ,	vcpu_pc		)
		    __field(	bool,		was		)
		    __field(	bool,		now		)
	    ),

	    TP_fast_assign(
		    __entry->vcpu_pc		= vcpu_pc;
		    __entry->was		= was;
		    __entry->now		= now;
	    ),

	    TP_prपूर्णांकk("VM op at 0x%016lx (cache was %s, now %s)",
		      __entry->vcpu_pc, __entry->was ? "on" : "off",
		      __entry->now ? "on" : "off")
);

/*
 * Tracepoपूर्णांकs क्रम arch_समयr
 */
TRACE_EVENT(kvm_समयr_update_irq,
	TP_PROTO(अचिन्हित दीर्घ vcpu_id, __u32 irq, पूर्णांक level),
	TP_ARGS(vcpu_id, irq, level),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	vcpu_id	)
		__field(	__u32,		irq	)
		__field(	पूर्णांक,		level	)
	),

	TP_fast_assign(
		__entry->vcpu_id	= vcpu_id;
		__entry->irq		= irq;
		__entry->level		= level;
	),

	TP_prपूर्णांकk("VCPU: %ld, IRQ %d, level %d",
		  __entry->vcpu_id, __entry->irq, __entry->level)
);

TRACE_EVENT(kvm_get_समयr_map,
	TP_PROTO(अचिन्हित दीर्घ vcpu_id, काष्ठा समयr_map *map),
	TP_ARGS(vcpu_id, map),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,		vcpu_id	)
		__field(	पूर्णांक,			direct_vसमयr	)
		__field(	पूर्णांक,			direct_pसमयr	)
		__field(	पूर्णांक,			emul_pसमयr	)
	),

	TP_fast_assign(
		__entry->vcpu_id		= vcpu_id;
		__entry->direct_vसमयr		= arch_समयr_ctx_index(map->direct_vसमयr);
		__entry->direct_pसमयr =
			(map->direct_pसमयr) ? arch_समयr_ctx_index(map->direct_pसमयr) : -1;
		__entry->emul_pसमयr =
			(map->emul_pसमयr) ? arch_समयr_ctx_index(map->emul_pसमयr) : -1;
	),

	TP_prपूर्णांकk("VCPU: %ld, dv: %d, dp: %d, ep: %d",
		  __entry->vcpu_id,
		  __entry->direct_vसमयr,
		  __entry->direct_pसमयr,
		  __entry->emul_pसमयr)
);

TRACE_EVENT(kvm_समयr_save_state,
	TP_PROTO(काष्ठा arch_समयr_context *ctx),
	TP_ARGS(ctx),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,		ctl		)
		__field(	अचिन्हित दीर्घ दीर्घ,	cval		)
		__field(	पूर्णांक,			समयr_idx	)
	),

	TP_fast_assign(
		__entry->ctl			= समयr_get_ctl(ctx);
		__entry->cval			= समयr_get_cval(ctx);
		__entry->समयr_idx		= arch_समयr_ctx_index(ctx);
	),

	TP_prपूर्णांकk("   CTL: %#08lx CVAL: %#16llx arch_timer_ctx_index: %d",
		  __entry->ctl,
		  __entry->cval,
		  __entry->समयr_idx)
);

TRACE_EVENT(kvm_समयr_restore_state,
	TP_PROTO(काष्ठा arch_समयr_context *ctx),
	TP_ARGS(ctx),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,		ctl		)
		__field(	अचिन्हित दीर्घ दीर्घ,	cval		)
		__field(	पूर्णांक,			समयr_idx	)
	),

	TP_fast_assign(
		__entry->ctl			= समयr_get_ctl(ctx);
		__entry->cval			= समयr_get_cval(ctx);
		__entry->समयr_idx		= arch_समयr_ctx_index(ctx);
	),

	TP_prपूर्णांकk("CTL: %#08lx CVAL: %#16llx arch_timer_ctx_index: %d",
		  __entry->ctl,
		  __entry->cval,
		  __entry->समयr_idx)
);

TRACE_EVENT(kvm_समयr_hrसमयr_expire,
	TP_PROTO(काष्ठा arch_समयr_context *ctx),
	TP_ARGS(ctx),

	TP_STRUCT__entry(
		__field(	पूर्णांक,			समयr_idx	)
	),

	TP_fast_assign(
		__entry->समयr_idx		= arch_समयr_ctx_index(ctx);
	),

	TP_prपूर्णांकk("arch_timer_ctx_index: %d", __entry->समयr_idx)
);

TRACE_EVENT(kvm_समयr_emulate,
	TP_PROTO(काष्ठा arch_समयr_context *ctx, bool should_fire),
	TP_ARGS(ctx, should_fire),

	TP_STRUCT__entry(
		__field(	पूर्णांक,			समयr_idx	)
		__field(	bool,			should_fire	)
	),

	TP_fast_assign(
		__entry->समयr_idx		= arch_समयr_ctx_index(ctx);
		__entry->should_fire		= should_fire;
	),

	TP_prपूर्णांकk("arch_timer_ctx_index: %d (should_fire: %d)",
		  __entry->समयr_idx, __entry->should_fire)
);

#पूर्ण_अगर /* _TRACE_ARM_ARM64_KVM_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace_arm

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
