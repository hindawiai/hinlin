<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM x86_fpu

#अगर !defined(_TRACE_FPU_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FPU_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(x86_fpu,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu),

	TP_STRUCT__entry(
		__field(काष्ठा fpu *, fpu)
		__field(bool, load_fpu)
		__field(u64, xfeatures)
		__field(u64, xcomp_bv)
		),

	TP_fast_assign(
		__entry->fpu		= fpu;
		__entry->load_fpu	= test_thपढ़ो_flag(TIF_NEED_FPU_LOAD);
		अगर (boot_cpu_has(X86_FEATURE_OSXSAVE)) अणु
			__entry->xfeatures = fpu->state.xsave.header.xfeatures;
			__entry->xcomp_bv  = fpu->state.xsave.header.xcomp_bv;
		पूर्ण
	),
	TP_prपूर्णांकk("x86/fpu: %p load: %d xfeatures: %llx xcomp_bv: %llx",
			__entry->fpu,
			__entry->load_fpu,
			__entry->xfeatures,
			__entry->xcomp_bv
	)
);

DEFINE_EVENT(x86_fpu, x86_fpu_beक्रमe_save,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_after_save,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_beक्रमe_restore,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_after_restore,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_regs_activated,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_regs_deactivated,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_init_state,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_dropped,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_copy_src,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_copy_dst,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_xstate_check_failed,
	TP_PROTO(काष्ठा fpu *fpu),
	TP_ARGS(fpu)
);

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH यंत्र/trace/
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता fpu
#पूर्ण_अगर /* _TRACE_FPU_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
