<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_KVMS390_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KVMS390_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm-s390
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace-s390

/*
 * The TRACE_SYSTEM_VAR शेषs to TRACE_SYSTEM, but must be a
 * legitimate C variable. It is not exported to user space.
 */
#अघोषित TRACE_SYSTEM_VAR
#घोषणा TRACE_SYSTEM_VAR kvm_s390

/*
 * Trace poपूर्णांक क्रम the creation of the kvm instance.
 */
TRACE_EVENT(kvm_s390_create_vm,
	    TP_PROTO(अचिन्हित दीर्घ type),
	    TP_ARGS(type),

	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, type)
		    ),

	    TP_fast_assign(
		    __entry->type = type;
		    ),

	    TP_prपूर्णांकk("create vm%s",
		      __entry->type & KVM_VM_S390_UCONTROL ? " (UCONTROL)" : "")
	);

/*
 * Trace poपूर्णांकs क्रम creation and deकाष्ठाion of vpcus.
 */
TRACE_EVENT(kvm_s390_create_vcpu,
	    TP_PROTO(अचिन्हित पूर्णांक id, काष्ठा kvm_vcpu *vcpu,
		     काष्ठा kvm_s390_sie_block *sie_block),
	    TP_ARGS(id, vcpu, sie_block),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, id)
		    __field(काष्ठा kvm_vcpu *, vcpu)
		    __field(काष्ठा kvm_s390_sie_block *, sie_block)
		    ),

	    TP_fast_assign(
		    __entry->id = id;
		    __entry->vcpu = vcpu;
		    __entry->sie_block = sie_block;
		    ),

	    TP_prपूर्णांकk("create cpu %d at 0x%pK, sie block at 0x%pK",
		      __entry->id, __entry->vcpu, __entry->sie_block)
	);

TRACE_EVENT(kvm_s390_destroy_vcpu,
	    TP_PROTO(अचिन्हित पूर्णांक id),
	    TP_ARGS(id),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, id)
		    ),

	    TP_fast_assign(
		    __entry->id = id;
		    ),

	    TP_prपूर्णांकk("destroy cpu %d", __entry->id)
	);

/*
 * Trace poपूर्णांक क्रम start and stop of vpcus.
 */
TRACE_EVENT(kvm_s390_vcpu_start_stop,
	    TP_PROTO(अचिन्हित पूर्णांक id, पूर्णांक state),
	    TP_ARGS(id, state),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, id)
		    __field(पूर्णांक, state)
		    ),

	    TP_fast_assign(
		    __entry->id = id;
		    __entry->state = state;
		    ),

	    TP_prपूर्णांकk("%s cpu %d", __entry->state ? "starting" : "stopping",
		      __entry->id)
	);

/*
 * Trace poपूर्णांकs क्रम injection of पूर्णांकerrupts, either per machine or
 * per vcpu.
 */

#घोषणा kvm_s390_पूर्णांक_type						\
	अणुKVM_S390_SIGP_STOP, "sigp stop"पूर्ण,				\
	अणुKVM_S390_PROGRAM_INT, "program interrupt"पूर्ण,			\
	अणुKVM_S390_SIGP_SET_PREFIX, "sigp set prefix"पूर्ण,			\
	अणुKVM_S390_RESTART, "sigp restart"पूर्ण,				\
	अणुKVM_S390_INT_PFAULT_INIT, "pfault init"पूर्ण,			\
	अणुKVM_S390_INT_PFAULT_DONE, "pfault done"पूर्ण,			\
	अणुKVM_S390_MCHK, "machine check"पूर्ण,				\
	अणुKVM_S390_INT_CLOCK_COMP, "clock comparator"पूर्ण,			\
	अणुKVM_S390_INT_CPU_TIMER, "cpu timer"पूर्ण,				\
	अणुKVM_S390_INT_VIRTIO, "virtio interrupt"पूर्ण,			\
	अणुKVM_S390_INT_SERVICE, "sclp interrupt"पूर्ण,			\
	अणुKVM_S390_INT_EMERGENCY, "sigp emergency"पूर्ण,			\
	अणुKVM_S390_INT_EXTERNAL_CALL, "sigp ext call"पूर्ण

#घोषणा get_irq_name(__type) \
	(__type > KVM_S390_INT_IO_MAX ? \
	__prपूर्णांक_symbolic(__type, kvm_s390_पूर्णांक_type) : \
		(__type & KVM_S390_INT_IO_AI_MASK ? \
		 "adapter I/O interrupt" : "subchannel I/O interrupt"))

TRACE_EVENT(kvm_s390_inject_vm,
	    TP_PROTO(__u64 type, __u32 parm, __u64 parm64, पूर्णांक who),
	    TP_ARGS(type, parm, parm64, who),

	    TP_STRUCT__entry(
		    __field(__u32, पूर्णांकtype)
		    __field(__u32, parm)
		    __field(__u64, parm64)
		    __field(पूर्णांक, who)
		    ),

	    TP_fast_assign(
		    __entry->पूर्णांकtype = type & 0x00000000ffffffff;
		    __entry->parm = parm;
		    __entry->parm64 = parm64;
		    __entry->who = who;
		    ),

	    TP_prपूर्णांकk("inject%s: type:%x (%s) parm:%x parm64:%llx",
		      (__entry->who == 1) ? " (from kernel)" :
		      (__entry->who == 2) ? " (from user)" : "",
		      __entry->पूर्णांकtype, get_irq_name(__entry->पूर्णांकtype),
		      __entry->parm, __entry->parm64)
	);

TRACE_EVENT(kvm_s390_inject_vcpu,
	    TP_PROTO(अचिन्हित पूर्णांक id, __u64 type, __u32 parm, __u64 parm64),
	    TP_ARGS(id, type, parm, parm64),

	    TP_STRUCT__entry(
		    __field(पूर्णांक, id)
		    __field(__u32, पूर्णांकtype)
		    __field(__u32, parm)
		    __field(__u64, parm64)
		    ),

	    TP_fast_assign(
		    __entry->id = id;
		    __entry->पूर्णांकtype = type & 0x00000000ffffffff;
		    __entry->parm = parm;
		    __entry->parm64 = parm64;
		    ),

	    TP_prपूर्णांकk("inject (vcpu %d): type:%x (%s) parm:%x parm64:%llx",
		      __entry->id, __entry->पूर्णांकtype,
		      get_irq_name(__entry->पूर्णांकtype), __entry->parm,
		      __entry->parm64)
	);

/*
 * Trace poपूर्णांक क्रम the actual delivery of पूर्णांकerrupts.
 */
TRACE_EVENT(kvm_s390_deliver_पूर्णांकerrupt,
	    TP_PROTO(अचिन्हित पूर्णांक id, __u64 type, __u64 data0, __u64 data1),
	    TP_ARGS(id, type, data0, data1),

	    TP_STRUCT__entry(
		    __field(पूर्णांक, id)
		    __field(__u32, पूर्णांकtype)
		    __field(__u64, data0)
		    __field(__u64, data1)
		    ),

	    TP_fast_assign(
		    __entry->id = id;
		    __entry->पूर्णांकtype = type & 0x00000000ffffffff;
		    __entry->data0 = data0;
		    __entry->data1 = data1;
		    ),

	    TP_prपूर्णांकk("deliver interrupt (vcpu %d): type:%x (%s) "	\
		      "data:%08llx %016llx",
		      __entry->id, __entry->पूर्णांकtype,
		      get_irq_name(__entry->पूर्णांकtype), __entry->data0,
		      __entry->data1)
	);

/*
 * Trace poपूर्णांक क्रम resets that may be requested from userspace.
 */
TRACE_EVENT(kvm_s390_request_resets,
	    TP_PROTO(__u64 resets),
	    TP_ARGS(resets),

	    TP_STRUCT__entry(
		    __field(__u64, resets)
		    ),

	    TP_fast_assign(
		    __entry->resets = resets;
		    ),

	    TP_prपूर्णांकk("requesting userspace resets %llx",
		      __entry->resets)
	);

/*
 * Trace poपूर्णांक क्रम a vcpu's stop requests.
 */
TRACE_EVENT(kvm_s390_stop_request,
	    TP_PROTO(अचिन्हित अक्षर stop_irq, अचिन्हित अक्षर flags),
	    TP_ARGS(stop_irq, flags),

	    TP_STRUCT__entry(
		    __field(अचिन्हित अक्षर, stop_irq)
		    __field(अचिन्हित अक्षर, flags)
		    ),

	    TP_fast_assign(
		    __entry->stop_irq = stop_irq;
		    __entry->flags = flags;
		    ),

	    TP_prपूर्णांकk("stop request, stop irq = %u, flags = %08x",
		      __entry->stop_irq, __entry->flags)
	);


/*
 * Trace poपूर्णांक क्रम enabling channel I/O inकाष्ठाion support.
 */
TRACE_EVENT(kvm_s390_enable_css,
	    TP_PROTO(व्योम *kvm),
	    TP_ARGS(kvm),

	    TP_STRUCT__entry(
		    __field(व्योम *, kvm)
		    ),

	    TP_fast_assign(
		    __entry->kvm = kvm;
		    ),

	    TP_prपूर्णांकk("enabling channel I/O support (kvm @ %pK)\n",
		      __entry->kvm)
	);

/*
 * Trace poपूर्णांक क्रम enabling and disabling पूर्णांकerlocking-and-broadcasting
 * suppression.
 */
TRACE_EVENT(kvm_s390_enable_disable_ibs,
	    TP_PROTO(अचिन्हित पूर्णांक id, पूर्णांक state),
	    TP_ARGS(id, state),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक, id)
		    __field(पूर्णांक, state)
		    ),

	    TP_fast_assign(
		    __entry->id = id;
		    __entry->state = state;
		    ),

	    TP_prपूर्णांकk("%s ibs on cpu %d",
		      __entry->state ? "enabling" : "disabling", __entry->id)
	);

/*
 * Trace poपूर्णांक क्रम modअगरying ais mode क्रम a given isc.
 */
TRACE_EVENT(kvm_s390_modअगरy_ais_mode,
	    TP_PROTO(__u8 isc, __u16 from, __u16 to),
	    TP_ARGS(isc, from, to),

	    TP_STRUCT__entry(
		    __field(__u8, isc)
		    __field(__u16, from)
		    __field(__u16, to)
		    ),

	    TP_fast_assign(
		    __entry->isc = isc;
		    __entry->from = from;
		    __entry->to = to;
		    ),

	    TP_prपूर्णांकk("for isc %x, modifying interruption mode from %s to %s",
		      __entry->isc,
		      (__entry->from == KVM_S390_AIS_MODE_ALL) ?
		      "ALL-Interruptions Mode" :
		      (__entry->from == KVM_S390_AIS_MODE_SINGLE) ?
		      "Single-Interruption Mode" : "No-Interruptions Mode",
		      (__entry->to == KVM_S390_AIS_MODE_ALL) ?
		      "ALL-Interruptions Mode" :
		      (__entry->to == KVM_S390_AIS_MODE_SINGLE) ?
		      "Single-Interruption Mode" : "No-Interruptions Mode")
	);

/*
 * Trace poपूर्णांक क्रम suppressed adapter I/O पूर्णांकerrupt.
 */
TRACE_EVENT(kvm_s390_airq_suppressed,
	    TP_PROTO(__u32 id, __u8 isc),
	    TP_ARGS(id, isc),

	    TP_STRUCT__entry(
		    __field(__u32, id)
		    __field(__u8, isc)
		    ),

	    TP_fast_assign(
		    __entry->id = id;
		    __entry->isc = isc;
		    ),

	    TP_prपूर्णांकk("adapter I/O interrupt suppressed (id:%x isc:%x)",
		      __entry->id, __entry->isc)
	);


#पूर्ण_अगर /* _TRACE_KVMS390_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
