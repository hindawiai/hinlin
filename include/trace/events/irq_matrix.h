<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM irq_matrix

#अगर !defined(_TRACE_IRQ_MATRIX_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_IRQ_MATRIX_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा irq_matrix;
काष्ठा cpumap;

DECLARE_EVENT_CLASS(irq_matrix_global,

	TP_PROTO(काष्ठा irq_matrix *matrix),

	TP_ARGS(matrix),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	online_maps		)
		__field(	अचिन्हित पूर्णांक,	global_available	)
		__field(	अचिन्हित पूर्णांक,	global_reserved		)
		__field(	अचिन्हित पूर्णांक,	total_allocated		)
	),

	TP_fast_assign(
		__entry->online_maps		= matrix->online_maps;
		__entry->global_available	= matrix->global_available;
		__entry->global_reserved	= matrix->global_reserved;
		__entry->total_allocated	= matrix->total_allocated;
	),

	TP_prपूर्णांकk("online_maps=%d global_avl=%u, global_rsvd=%u, total_alloc=%u",
		  __entry->online_maps, __entry->global_available,
		  __entry->global_reserved, __entry->total_allocated)
);

DECLARE_EVENT_CLASS(irq_matrix_global_update,

	TP_PROTO(पूर्णांक bit, काष्ठा irq_matrix *matrix),

	TP_ARGS(bit, matrix),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		bit			)
		__field(	अचिन्हित पूर्णांक,	online_maps		)
		__field(	अचिन्हित पूर्णांक,	global_available	)
		__field(	अचिन्हित पूर्णांक,	global_reserved		)
		__field(	अचिन्हित पूर्णांक,	total_allocated		)
	),

	TP_fast_assign(
		__entry->bit			= bit;
		__entry->online_maps		= matrix->online_maps;
		__entry->global_available	= matrix->global_available;
		__entry->global_reserved	= matrix->global_reserved;
		__entry->total_allocated	= matrix->total_allocated;
	),

	TP_prपूर्णांकk("bit=%d online_maps=%d global_avl=%u, global_rsvd=%u, total_alloc=%u",
		  __entry->bit, __entry->online_maps,
		  __entry->global_available, __entry->global_reserved,
		  __entry->total_allocated)
);

DECLARE_EVENT_CLASS(irq_matrix_cpu,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu, काष्ठा irq_matrix *matrix,
		 काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		bit			)
		__field(	अचिन्हित पूर्णांक,	cpu			)
		__field(	bool,		online			)
		__field(	अचिन्हित पूर्णांक,	available		)
		__field(	अचिन्हित पूर्णांक,	allocated		)
		__field(	अचिन्हित पूर्णांक,	managed			)
		__field(	अचिन्हित पूर्णांक,	online_maps		)
		__field(	अचिन्हित पूर्णांक,	global_available	)
		__field(	अचिन्हित पूर्णांक,	global_reserved		)
		__field(	अचिन्हित पूर्णांक,	total_allocated		)
	),

	TP_fast_assign(
		__entry->bit			= bit;
		__entry->cpu			= cpu;
		__entry->online			= cmap->online;
		__entry->available		= cmap->available;
		__entry->allocated		= cmap->allocated;
		__entry->managed		= cmap->managed;
		__entry->online_maps		= matrix->online_maps;
		__entry->global_available	= matrix->global_available;
		__entry->global_reserved	= matrix->global_reserved;
		__entry->total_allocated	= matrix->total_allocated;
	),

	TP_prपूर्णांकk("bit=%d cpu=%u online=%d avl=%u alloc=%u managed=%u online_maps=%u global_avl=%u, global_rsvd=%u, total_alloc=%u",
		  __entry->bit, __entry->cpu, __entry->online,
		  __entry->available, __entry->allocated,
		  __entry->managed, __entry->online_maps,
		  __entry->global_available, __entry->global_reserved,
		  __entry->total_allocated)
);

DEFINE_EVENT(irq_matrix_global, irq_matrix_online,

	TP_PROTO(काष्ठा irq_matrix *matrix),

	TP_ARGS(matrix)
);

DEFINE_EVENT(irq_matrix_global, irq_matrix_offline,

	TP_PROTO(काष्ठा irq_matrix *matrix),

	TP_ARGS(matrix)
);

DEFINE_EVENT(irq_matrix_global, irq_matrix_reserve,

	TP_PROTO(काष्ठा irq_matrix *matrix),

	TP_ARGS(matrix)
);

DEFINE_EVENT(irq_matrix_global, irq_matrix_हटाओ_reserved,

	TP_PROTO(काष्ठा irq_matrix *matrix),

	TP_ARGS(matrix)
);

DEFINE_EVENT(irq_matrix_global_update, irq_matrix_assign_प्रणाली,

	TP_PROTO(पूर्णांक bit, काष्ठा irq_matrix *matrix),

	TP_ARGS(bit, matrix)
);

DEFINE_EVENT(irq_matrix_cpu, irq_matrix_alloc_reserved,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu,
		 काष्ठा irq_matrix *matrix, काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap)
);

DEFINE_EVENT(irq_matrix_cpu, irq_matrix_reserve_managed,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu,
		 काष्ठा irq_matrix *matrix, काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap)
);

DEFINE_EVENT(irq_matrix_cpu, irq_matrix_हटाओ_managed,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu,
		 काष्ठा irq_matrix *matrix, काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap)
);

DEFINE_EVENT(irq_matrix_cpu, irq_matrix_alloc_managed,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu,
		 काष्ठा irq_matrix *matrix, काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap)
);

DEFINE_EVENT(irq_matrix_cpu, irq_matrix_assign,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu,
		 काष्ठा irq_matrix *matrix, काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap)
);

DEFINE_EVENT(irq_matrix_cpu, irq_matrix_alloc,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu,
		 काष्ठा irq_matrix *matrix, काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap)
);

DEFINE_EVENT(irq_matrix_cpu, irq_matrix_मुक्त,

	TP_PROTO(पूर्णांक bit, अचिन्हित पूर्णांक cpu,
		 काष्ठा irq_matrix *matrix, काष्ठा cpumap *cmap),

	TP_ARGS(bit, cpu, matrix, cmap)
);


#पूर्ण_अगर /*  _TRACE_IRQ_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
