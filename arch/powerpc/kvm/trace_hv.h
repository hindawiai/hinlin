<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_KVM_HV_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KVM_HV_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "trace_book3s.h"
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/kvm_यंत्र.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm_hv

#घोषणा kvm_trace_symbol_hcall \
	अणुH_REMOVE,			"H_REMOVE"पूर्ण, \
	अणुH_ENTER,			"H_ENTER"पूर्ण, \
	अणुH_READ,			"H_READ"पूर्ण, \
	अणुH_CLEAR_MOD,			"H_CLEAR_MOD"पूर्ण, \
	अणुH_CLEAR_REF,			"H_CLEAR_REF"पूर्ण, \
	अणुH_PROTECT,			"H_PROTECT"पूर्ण, \
	अणुH_GET_TCE,			"H_GET_TCE"पूर्ण, \
	अणुH_PUT_TCE,			"H_PUT_TCE"पूर्ण, \
	अणुH_SET_SPRG0,			"H_SET_SPRG0"पूर्ण, \
	अणुH_SET_DABR,			"H_SET_DABR"पूर्ण, \
	अणुH_PAGE_INIT,			"H_PAGE_INIT"पूर्ण, \
	अणुH_SET_ASR,			"H_SET_ASR"पूर्ण, \
	अणुH_ASR_ON,			"H_ASR_ON"पूर्ण, \
	अणुH_ASR_OFF,			"H_ASR_OFF"पूर्ण, \
	अणुH_LOGICAL_CI_LOAD,		"H_LOGICAL_CI_LOAD"पूर्ण, \
	अणुH_LOGICAL_CI_STORE,		"H_LOGICAL_CI_STORE"पूर्ण, \
	अणुH_LOGICAL_CACHE_LOAD,		"H_LOGICAL_CACHE_LOAD"पूर्ण, \
	अणुH_LOGICAL_CACHE_STORE,		"H_LOGICAL_CACHE_STORE"पूर्ण, \
	अणुH_LOGICAL_ICBI,		"H_LOGICAL_ICBI"पूर्ण, \
	अणुH_LOGICAL_DCBF,		"H_LOGICAL_DCBF"पूर्ण, \
	अणुH_GET_TERM_CHAR,		"H_GET_TERM_CHAR"पूर्ण, \
	अणुH_PUT_TERM_CHAR,		"H_PUT_TERM_CHAR"पूर्ण, \
	अणुH_REAL_TO_LOGICAL,		"H_REAL_TO_LOGICAL"पूर्ण, \
	अणुH_HYPERVISOR_DATA,		"H_HYPERVISOR_DATA"पूर्ण, \
	अणुH_EOI,				"H_EOI"पूर्ण, \
	अणुH_CPPR,			"H_CPPR"पूर्ण, \
	अणुH_IPI,				"H_IPI"पूर्ण, \
	अणुH_IPOLL,			"H_IPOLL"पूर्ण, \
	अणुH_XIRR,			"H_XIRR"पूर्ण, \
	अणुH_PERFMON,			"H_PERFMON"पूर्ण, \
	अणुH_MIGRATE_DMA,			"H_MIGRATE_DMA"पूर्ण, \
	अणुH_REGISTER_VPA,		"H_REGISTER_VPA"पूर्ण, \
	अणुH_CEDE,			"H_CEDE"पूर्ण, \
	अणुH_CONFER,			"H_CONFER"पूर्ण, \
	अणुH_PROD,			"H_PROD"पूर्ण, \
	अणुH_GET_PPP,			"H_GET_PPP"पूर्ण, \
	अणुH_SET_PPP,			"H_SET_PPP"पूर्ण, \
	अणुH_PURR,			"H_PURR"पूर्ण, \
	अणुH_PIC,				"H_PIC"पूर्ण, \
	अणुH_REG_CRQ,			"H_REG_CRQ"पूर्ण, \
	अणुH_FREE_CRQ,			"H_FREE_CRQ"पूर्ण, \
	अणुH_VIO_SIGNAL,			"H_VIO_SIGNAL"पूर्ण, \
	अणुH_SEND_CRQ,			"H_SEND_CRQ"पूर्ण, \
	अणुH_COPY_RDMA,			"H_COPY_RDMA"पूर्ण, \
	अणुH_REGISTER_LOGICAL_LAN,	"H_REGISTER_LOGICAL_LAN"पूर्ण, \
	अणुH_FREE_LOGICAL_LAN,		"H_FREE_LOGICAL_LAN"पूर्ण, \
	अणुH_ADD_LOGICAL_LAN_BUFFER,	"H_ADD_LOGICAL_LAN_BUFFER"पूर्ण, \
	अणुH_SEND_LOGICAL_LAN,		"H_SEND_LOGICAL_LAN"पूर्ण, \
	अणुH_BULK_REMOVE,			"H_BULK_REMOVE"पूर्ण, \
	अणुH_MULTICAST_CTRL,		"H_MULTICAST_CTRL"पूर्ण, \
	अणुH_SET_XDABR,			"H_SET_XDABR"पूर्ण, \
	अणुH_STUFF_TCE,			"H_STUFF_TCE"पूर्ण, \
	अणुH_PUT_TCE_INसूचीECT,		"H_PUT_TCE_INDIRECT"पूर्ण, \
	अणुH_CHANGE_LOGICAL_LAN_MAC,	"H_CHANGE_LOGICAL_LAN_MAC"पूर्ण, \
	अणुH_VTERM_PARTNER_INFO,		"H_VTERM_PARTNER_INFO"पूर्ण, \
	अणुH_REGISTER_VTERM,		"H_REGISTER_VTERM"पूर्ण, \
	अणुH_FREE_VTERM,			"H_FREE_VTERM"पूर्ण, \
	अणुH_RESET_EVENTS,		"H_RESET_EVENTS"पूर्ण, \
	अणुH_ALLOC_RESOURCE,		"H_ALLOC_RESOURCE"पूर्ण, \
	अणुH_FREE_RESOURCE,		"H_FREE_RESOURCE"पूर्ण, \
	अणुH_MODIFY_QP,			"H_MODIFY_QP"पूर्ण, \
	अणुH_QUERY_QP,			"H_QUERY_QP"पूर्ण, \
	अणुH_REREGISTER_PMR,		"H_REREGISTER_PMR"पूर्ण, \
	अणुH_REGISTER_SMR,		"H_REGISTER_SMR"पूर्ण, \
	अणुH_QUERY_MR,			"H_QUERY_MR"पूर्ण, \
	अणुH_QUERY_MW,			"H_QUERY_MW"पूर्ण, \
	अणुH_QUERY_HCA,			"H_QUERY_HCA"पूर्ण, \
	अणुH_QUERY_PORT,			"H_QUERY_PORT"पूर्ण, \
	अणुH_MODIFY_PORT,			"H_MODIFY_PORT"पूर्ण, \
	अणुH_DEFINE_AQP1,			"H_DEFINE_AQP1"पूर्ण, \
	अणुH_GET_TRACE_BUFFER,		"H_GET_TRACE_BUFFER"पूर्ण, \
	अणुH_DEFINE_AQP0,			"H_DEFINE_AQP0"पूर्ण, \
	अणुH_RESIZE_MR,			"H_RESIZE_MR"पूर्ण, \
	अणुH_ATTACH_MCQP,			"H_ATTACH_MCQP"पूर्ण, \
	अणुH_DETACH_MCQP,			"H_DETACH_MCQP"पूर्ण, \
	अणुH_CREATE_RPT,			"H_CREATE_RPT"पूर्ण, \
	अणुH_REMOVE_RPT,			"H_REMOVE_RPT"पूर्ण, \
	अणुH_REGISTER_RPAGES,		"H_REGISTER_RPAGES"पूर्ण, \
	अणुH_DISABLE_AND_GET,		"H_DISABLE_AND_GET"पूर्ण, \
	अणुH_ERROR_DATA,			"H_ERROR_DATA"पूर्ण, \
	अणुH_GET_HCA_INFO,		"H_GET_HCA_INFO"पूर्ण, \
	अणुH_GET_PERF_COUNT,		"H_GET_PERF_COUNT"पूर्ण, \
	अणुH_MANAGE_TRACE,		"H_MANAGE_TRACE"पूर्ण, \
	अणुH_FREE_LOGICAL_LAN_BUFFER,	"H_FREE_LOGICAL_LAN_BUFFER"पूर्ण, \
	अणुH_QUERY_INT_STATE,		"H_QUERY_INT_STATE"पूर्ण, \
	अणुH_POLL_PENDING,		"H_POLL_PENDING"पूर्ण, \
	अणुH_ILLAN_ATTRIBUTES,		"H_ILLAN_ATTRIBUTES"पूर्ण, \
	अणुH_MODIFY_HEA_QP,		"H_MODIFY_HEA_QP"पूर्ण, \
	अणुH_QUERY_HEA_QP,		"H_QUERY_HEA_QP"पूर्ण, \
	अणुH_QUERY_HEA,			"H_QUERY_HEA"पूर्ण, \
	अणुH_QUERY_HEA_PORT,		"H_QUERY_HEA_PORT"पूर्ण, \
	अणुH_MODIFY_HEA_PORT,		"H_MODIFY_HEA_PORT"पूर्ण, \
	अणुH_REG_BCMC,			"H_REG_BCMC"पूर्ण, \
	अणुH_DEREG_BCMC,			"H_DEREG_BCMC"पूर्ण, \
	अणुH_REGISTER_HEA_RPAGES,		"H_REGISTER_HEA_RPAGES"पूर्ण, \
	अणुH_DISABLE_AND_GET_HEA,		"H_DISABLE_AND_GET_HEA"पूर्ण, \
	अणुH_GET_HEA_INFO,		"H_GET_HEA_INFO"पूर्ण, \
	अणुH_ALLOC_HEA_RESOURCE,		"H_ALLOC_HEA_RESOURCE"पूर्ण, \
	अणुH_ADD_CONN,			"H_ADD_CONN"पूर्ण, \
	अणुH_DEL_CONN,			"H_DEL_CONN"पूर्ण, \
	अणुH_JOIN,			"H_JOIN"पूर्ण, \
	अणुH_VASI_STATE,			"H_VASI_STATE"पूर्ण, \
	अणुH_ENABLE_CRQ,			"H_ENABLE_CRQ"पूर्ण, \
	अणुH_GET_EM_PARMS,		"H_GET_EM_PARMS"पूर्ण, \
	अणुH_SET_MPP,			"H_SET_MPP"पूर्ण, \
	अणुH_GET_MPP,			"H_GET_MPP"पूर्ण, \
	अणुH_HOME_NODE_ASSOCIATIVITY,	"H_HOME_NODE_ASSOCIATIVITY"पूर्ण, \
	अणुH_BEST_ENERGY,			"H_BEST_ENERGY"पूर्ण, \
	अणुH_XIRR_X,			"H_XIRR_X"पूर्ण, \
	अणुH_RANDOM,			"H_RANDOM"पूर्ण, \
	अणुH_COP,				"H_COP"पूर्ण, \
	अणुH_GET_MPP_X,			"H_GET_MPP_X"पूर्ण, \
	अणुH_SET_MODE,			"H_SET_MODE"पूर्ण, \
	अणुH_RTAS,			"H_RTAS"पूर्ण

#घोषणा kvm_trace_symbol_kvmret \
	अणुRESUME_GUEST,			"RESUME_GUEST"पूर्ण, \
	अणुRESUME_GUEST_NV,		"RESUME_GUEST_NV"पूर्ण, \
	अणुRESUME_HOST,			"RESUME_HOST"पूर्ण, \
	अणुRESUME_HOST_NV,		"RESUME_HOST_NV"पूर्ण

#घोषणा kvm_trace_symbol_hcall_rc \
	अणुH_SUCCESS,			"H_SUCCESS"पूर्ण, \
	अणुH_BUSY,			"H_BUSY"पूर्ण, \
	अणुH_CLOSED,			"H_CLOSED"पूर्ण, \
	अणुH_NOT_AVAILABLE,		"H_NOT_AVAILABLE"पूर्ण, \
	अणुH_CONSTRAINED,			"H_CONSTRAINED"पूर्ण, \
	अणुH_PARTIAL,			"H_PARTIAL"पूर्ण, \
	अणुH_IN_PROGRESS,			"H_IN_PROGRESS"पूर्ण, \
	अणुH_PAGE_REGISTERED,		"H_PAGE_REGISTERED"पूर्ण, \
	अणुH_PARTIAL_STORE,		"H_PARTIAL_STORE"पूर्ण, \
	अणुH_PENDING,			"H_PENDING"पूर्ण, \
	अणुH_CONTINUE,			"H_CONTINUE"पूर्ण, \
	अणुH_LONG_BUSY_START_RANGE,	"H_LONG_BUSY_START_RANGE"पूर्ण, \
	अणुH_LONG_BUSY_ORDER_1_MSEC,	"H_LONG_BUSY_ORDER_1_MSEC"पूर्ण, \
	अणुH_LONG_BUSY_ORDER_10_MSEC,	"H_LONG_BUSY_ORDER_10_MSEC"पूर्ण, \
	अणुH_LONG_BUSY_ORDER_100_MSEC,	"H_LONG_BUSY_ORDER_100_MSEC"पूर्ण, \
	अणुH_LONG_BUSY_ORDER_1_SEC,	"H_LONG_BUSY_ORDER_1_SEC"पूर्ण, \
	अणुH_LONG_BUSY_ORDER_10_SEC,	"H_LONG_BUSY_ORDER_10_SEC"पूर्ण, \
	अणुH_LONG_BUSY_ORDER_100_SEC,	"H_LONG_BUSY_ORDER_100_SEC"पूर्ण, \
	अणुH_LONG_BUSY_END_RANGE,		"H_LONG_BUSY_END_RANGE"पूर्ण, \
	अणुH_TOO_HARD,			"H_TOO_HARD"पूर्ण, \
	अणुH_HARDWARE,			"H_HARDWARE"पूर्ण, \
	अणुH_FUNCTION,			"H_FUNCTION"पूर्ण, \
	अणुH_PRIVILEGE,			"H_PRIVILEGE"पूर्ण, \
	अणुH_PARAMETER,			"H_PARAMETER"पूर्ण, \
	अणुH_BAD_MODE,			"H_BAD_MODE"पूर्ण, \
	अणुH_PTEG_FULL,			"H_PTEG_FULL"पूर्ण, \
	अणुH_NOT_FOUND,			"H_NOT_FOUND"पूर्ण, \
	अणुH_RESERVED_DABR,		"H_RESERVED_DABR"पूर्ण, \
	अणुH_NO_MEM,			"H_NO_MEM"पूर्ण, \
	अणुH_AUTHORITY,			"H_AUTHORITY"पूर्ण, \
	अणुH_PERMISSION,			"H_PERMISSION"पूर्ण, \
	अणुH_DROPPED,			"H_DROPPED"पूर्ण, \
	अणुH_SOURCE_PARM,			"H_SOURCE_PARM"पूर्ण, \
	अणुH_DEST_PARM,			"H_DEST_PARM"पूर्ण, \
	अणुH_REMOTE_PARM,			"H_REMOTE_PARM"पूर्ण, \
	अणुH_RESOURCE,			"H_RESOURCE"पूर्ण, \
	अणुH_ADAPTER_PARM,		"H_ADAPTER_PARM"पूर्ण, \
	अणुH_RH_PARM,			"H_RH_PARM"पूर्ण, \
	अणुH_RCQ_PARM,			"H_RCQ_PARM"पूर्ण, \
	अणुH_SCQ_PARM,			"H_SCQ_PARM"पूर्ण, \
	अणुH_EQ_PARM,			"H_EQ_PARM"पूर्ण, \
	अणुH_RT_PARM,			"H_RT_PARM"पूर्ण, \
	अणुH_ST_PARM,			"H_ST_PARM"पूर्ण, \
	अणुH_SIGT_PARM,			"H_SIGT_PARM"पूर्ण, \
	अणुH_TOKEN_PARM,			"H_TOKEN_PARM"पूर्ण, \
	अणुH_MLENGTH_PARM,		"H_MLENGTH_PARM"पूर्ण, \
	अणुH_MEM_PARM,			"H_MEM_PARM"पूर्ण, \
	अणुH_MEM_ACCESS_PARM,		"H_MEM_ACCESS_PARM"पूर्ण, \
	अणुH_ATTR_PARM,			"H_ATTR_PARM"पूर्ण, \
	अणुH_PORT_PARM,			"H_PORT_PARM"पूर्ण, \
	अणुH_MCG_PARM,			"H_MCG_PARM"पूर्ण, \
	अणुH_VL_PARM,			"H_VL_PARM"पूर्ण, \
	अणुH_TSIZE_PARM,			"H_TSIZE_PARM"पूर्ण, \
	अणुH_TRACE_PARM,			"H_TRACE_PARM"पूर्ण, \
	अणुH_MASK_PARM,			"H_MASK_PARM"पूर्ण, \
	अणुH_MCG_FULL,			"H_MCG_FULL"पूर्ण, \
	अणुH_ALIAS_EXIST,			"H_ALIAS_EXIST"पूर्ण, \
	अणुH_P_COUNTER,			"H_P_COUNTER"पूर्ण, \
	अणुH_TABLE_FULL,			"H_TABLE_FULL"पूर्ण, \
	अणुH_ALT_TABLE,			"H_ALT_TABLE"पूर्ण, \
	अणुH_MR_CONDITION,		"H_MR_CONDITION"पूर्ण, \
	अणुH_NOT_ENOUGH_RESOURCES,	"H_NOT_ENOUGH_RESOURCES"पूर्ण, \
	अणुH_R_STATE,			"H_R_STATE"पूर्ण, \
	अणुH_RESCINDED,			"H_RESCINDED"पूर्ण, \
	अणुH_P2,				"H_P2"पूर्ण, \
	अणुH_P3,				"H_P3"पूर्ण, \
	अणुH_P4,				"H_P4"पूर्ण, \
	अणुH_P5,				"H_P5"पूर्ण, \
	अणुH_P6,				"H_P6"पूर्ण, \
	अणुH_P7,				"H_P7"पूर्ण, \
	अणुH_P8,				"H_P8"पूर्ण, \
	अणुH_P9,				"H_P9"पूर्ण, \
	अणुH_TOO_BIG,			"H_TOO_BIG"पूर्ण, \
	अणुH_OVERLAP,			"H_OVERLAP"पूर्ण, \
	अणुH_INTERRUPT,			"H_INTERRUPT"पूर्ण, \
	अणुH_BAD_DATA,			"H_BAD_DATA"पूर्ण, \
	अणुH_NOT_ACTIVE,			"H_NOT_ACTIVE"पूर्ण, \
	अणुH_SG_LIST,			"H_SG_LIST"पूर्ण, \
	अणुH_OP_MODE,			"H_OP_MODE"पूर्ण, \
	अणुH_COP_HW,			"H_COP_HW"पूर्ण, \
	अणुH_UNSUPPORTED_FLAG_START,	"H_UNSUPPORTED_FLAG_START"पूर्ण, \
	अणुH_UNSUPPORTED_FLAG_END,	"H_UNSUPPORTED_FLAG_END"पूर्ण, \
	अणुH_MULTI_THREADS_ACTIVE,	"H_MULTI_THREADS_ACTIVE"पूर्ण, \
	अणुH_OUTSTANDING_COP_OPS,		"H_OUTSTANDING_COP_OPS"पूर्ण

TRACE_EVENT(kvm_guest_enter,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	TP_ARGS(vcpu),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(अचिन्हित दीर्घ,	pc)
		__field(अचिन्हित दीर्घ,  pending_exceptions)
		__field(u8,		ceded)
	),

	TP_fast_assign(
		__entry->vcpu_id	= vcpu->vcpu_id;
		__entry->pc		= kvmppc_get_pc(vcpu);
		__entry->ceded		= vcpu->arch.ceded;
		__entry->pending_exceptions  = vcpu->arch.pending_exceptions;
	),

	TP_prपूर्णांकk("VCPU %d: pc=0x%lx pexcp=0x%lx ceded=%d",
			__entry->vcpu_id,
			__entry->pc,
			__entry->pending_exceptions, __entry->ceded)
);

TRACE_EVENT(kvm_guest_निकास,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	TP_ARGS(vcpu),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(पूर्णांक,		trap)
		__field(अचिन्हित दीर्घ,	pc)
		__field(अचिन्हित दीर्घ,	msr)
		__field(u8,		ceded)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu->vcpu_id;
		__entry->trap	 = vcpu->arch.trap;
		__entry->ceded	 = vcpu->arch.ceded;
		__entry->pc	 = kvmppc_get_pc(vcpu);
		__entry->msr	 = vcpu->arch.shregs.msr;
	),

	TP_prपूर्णांकk("VCPU %d: trap=%s pc=0x%lx msr=0x%lx, ceded=%d",
		__entry->vcpu_id,
		__prपूर्णांक_symbolic(__entry->trap, kvm_trace_symbol_निकास),
		__entry->pc, __entry->msr, __entry->ceded
	)
);

TRACE_EVENT(kvm_page_fault_enter,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ *hptep,
		 काष्ठा kvm_memory_slot *memslot, अचिन्हित दीर्घ ea,
		 अचिन्हित दीर्घ dsisr),

	TP_ARGS(vcpu, hptep, memslot, ea, dsisr),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(अचिन्हित दीर्घ,	hpte_v)
		__field(अचिन्हित दीर्घ,	hpte_r)
		__field(अचिन्हित दीर्घ,	gpte_r)
		__field(अचिन्हित दीर्घ,	ea)
		__field(u64,		base_gfn)
		__field(u32,		slot_flags)
		__field(u32,		dsisr)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu->vcpu_id;
		__entry->hpte_v	  = hptep[0];
		__entry->hpte_r	  = hptep[1];
		__entry->gpte_r	  = hptep[2];
		__entry->ea	  = ea;
		__entry->dsisr	  = dsisr;
		__entry->base_gfn = memslot ? memslot->base_gfn : -1UL;
		__entry->slot_flags = memslot ? memslot->flags : 0;
	),

	TP_prपूर्णांकk("VCPU %d: hpte=0x%lx:0x%lx guest=0x%lx ea=0x%lx,%x slot=0x%llx,0x%x",
		   __entry->vcpu_id,
		   __entry->hpte_v, __entry->hpte_r, __entry->gpte_r,
		   __entry->ea, __entry->dsisr,
		   __entry->base_gfn, __entry->slot_flags)
);

TRACE_EVENT(kvm_page_fault_निकास,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ *hptep, दीर्घ ret),

	TP_ARGS(vcpu, hptep, ret),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(अचिन्हित दीर्घ,	hpte_v)
		__field(अचिन्हित दीर्घ,	hpte_r)
		__field(दीर्घ,		ret)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu->vcpu_id;
		__entry->hpte_v	= hptep[0];
		__entry->hpte_r	= hptep[1];
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("VCPU %d: hpte=0x%lx:0x%lx ret=0x%lx",
		   __entry->vcpu_id,
		   __entry->hpte_v, __entry->hpte_r, __entry->ret)
);

TRACE_EVENT(kvm_hcall_enter,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),

	TP_ARGS(vcpu),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(अचिन्हित दीर्घ,	req)
		__field(अचिन्हित दीर्घ,	gpr4)
		__field(अचिन्हित दीर्घ,	gpr5)
		__field(अचिन्हित दीर्घ,	gpr6)
		__field(अचिन्हित दीर्घ,	gpr7)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu->vcpu_id;
		__entry->req   = kvmppc_get_gpr(vcpu, 3);
		__entry->gpr4  = kvmppc_get_gpr(vcpu, 4);
		__entry->gpr5  = kvmppc_get_gpr(vcpu, 5);
		__entry->gpr6  = kvmppc_get_gpr(vcpu, 6);
		__entry->gpr7  = kvmppc_get_gpr(vcpu, 7);
	),

	TP_prपूर्णांकk("VCPU %d: hcall=%s GPR4-7=0x%lx,0x%lx,0x%lx,0x%lx",
		   __entry->vcpu_id,
		   __prपूर्णांक_symbolic(__entry->req, kvm_trace_symbol_hcall),
		   __entry->gpr4, __entry->gpr5, __entry->gpr6, __entry->gpr7)
);

TRACE_EVENT(kvm_hcall_निकास,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu, पूर्णांक ret),

	TP_ARGS(vcpu, ret),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(अचिन्हित दीर्घ,	ret)
		__field(अचिन्हित दीर्घ,	hcall_rc)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu->vcpu_id;
		__entry->ret	  = ret;
		__entry->hcall_rc = kvmppc_get_gpr(vcpu, 3);
	),

	TP_prपूर्णांकk("VCPU %d: ret=%s hcall_rc=%s",
		   __entry->vcpu_id,
		   __prपूर्णांक_symbolic(__entry->ret, kvm_trace_symbol_kvmret),
		   __prपूर्णांक_symbolic(__entry->ret & RESUME_FLAG_HOST ?
					H_TOO_HARD : __entry->hcall_rc,
					kvm_trace_symbol_hcall_rc))
);

TRACE_EVENT(kvmppc_run_core,
	TP_PROTO(काष्ठा kvmppc_vcore *vc, पूर्णांक where),

	TP_ARGS(vc, where),

	TP_STRUCT__entry(
		__field(पूर्णांक,	n_runnable)
		__field(पूर्णांक,	runner_vcpu)
		__field(पूर्णांक,	where)
		__field(pid_t,	tgid)
	),

	TP_fast_assign(
		__entry->runner_vcpu	= vc->runner->vcpu_id;
		__entry->n_runnable	= vc->n_runnable;
		__entry->where		= where;
		__entry->tgid		= current->tgid;
	),

	TP_prपूर्णांकk("%s runner_vcpu==%d runnable=%d tgid=%d",
		    __entry->where ? "Exit" : "Enter",
		    __entry->runner_vcpu, __entry->n_runnable, __entry->tgid)
);

TRACE_EVENT(kvmppc_vcore_blocked,
	TP_PROTO(काष्ठा kvmppc_vcore *vc, पूर्णांक where),

	TP_ARGS(vc, where),

	TP_STRUCT__entry(
		__field(पूर्णांक,	n_runnable)
		__field(पूर्णांक,	runner_vcpu)
		__field(पूर्णांक,	where)
		__field(pid_t,	tgid)
	),

	TP_fast_assign(
		__entry->runner_vcpu = vc->runner->vcpu_id;
		__entry->n_runnable  = vc->n_runnable;
		__entry->where       = where;
		__entry->tgid	     = current->tgid;
	),

	TP_prपूर्णांकk("%s runner_vcpu=%d runnable=%d tgid=%d",
		   __entry->where ? "Exit" : "Enter",
		   __entry->runner_vcpu, __entry->n_runnable, __entry->tgid)
);

TRACE_EVENT(kvmppc_vcore_wakeup,
	TP_PROTO(पूर्णांक करो_sleep, __u64 ns),

	TP_ARGS(करो_sleep, ns),

	TP_STRUCT__entry(
		__field(__u64,  ns)
		__field(पूर्णांक,    रुकोed)
		__field(pid_t,  tgid)
	),

	TP_fast_assign(
		__entry->ns     = ns;
		__entry->रुकोed = करो_sleep;
		__entry->tgid   = current->tgid;
	),

	TP_prपूर्णांकk("%s time %llu ns, tgid=%d",
		__entry->रुकोed ? "wait" : "poll",
		__entry->ns, __entry->tgid)
);

TRACE_EVENT(kvmppc_run_vcpu_enter,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),

	TP_ARGS(vcpu),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(pid_t,		tgid)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu->vcpu_id;
		__entry->tgid	  = current->tgid;
	),

	TP_prपूर्णांकk("VCPU %d: tgid=%d", __entry->vcpu_id, __entry->tgid)
);

TRACE_EVENT(kvmppc_run_vcpu_निकास,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),

	TP_ARGS(vcpu),

	TP_STRUCT__entry(
		__field(पूर्णांक,		vcpu_id)
		__field(पूर्णांक,		निकास)
		__field(पूर्णांक,		ret)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu->vcpu_id;
		__entry->निकास     = vcpu->run->निकास_reason;
		__entry->ret      = vcpu->arch.ret;
	),

	TP_prपूर्णांकk("VCPU %d: exit=%d, ret=%d",
			__entry->vcpu_id, __entry->निकास, __entry->ret)
);

#पूर्ण_अगर /* _TRACE_KVM_HV_H */

/* This part must be outside protection */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता

#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_hv

#समावेश <trace/define_trace.h>
