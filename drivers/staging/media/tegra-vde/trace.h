<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM tegra_vde

#अगर !defined(TEGRA_VDE_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा TEGRA_VDE_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

#समावेश "vde.h"

DECLARE_EVENT_CLASS(रेजिस्टर_access,
	TP_PROTO(काष्ठा tegra_vde *vde, व्योम __iomem *base,
		 u32 offset, u32 value),
	TP_ARGS(vde, base, offset, value),
	TP_STRUCT__entry(
		__string(hw_name, tegra_vde_reg_base_name(vde, base))
		__field(u32, offset)
		__field(u32, value)
	),
	TP_fast_assign(
		__assign_str(hw_name, tegra_vde_reg_base_name(vde, base));
		__entry->offset = offset;
		__entry->value = value;
	),
	TP_prपूर्णांकk("%s:0x%03x 0x%08x", __get_str(hw_name), __entry->offset,
		  __entry->value)
);

DEFINE_EVENT(रेजिस्टर_access, vde_ग_लिखोl,
	TP_PROTO(काष्ठा tegra_vde *vde, व्योम __iomem *base,
		 u32 offset, u32 value),
	TP_ARGS(vde, base, offset, value));
DEFINE_EVENT(रेजिस्टर_access, vde_पढ़ोl,
	TP_PROTO(काष्ठा tegra_vde *vde, व्योम __iomem *base,
		 u32 offset, u32 value),
	TP_ARGS(vde, base, offset, value));

TRACE_EVENT(vde_setup_iram_entry,
	TP_PROTO(अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक row, u32 value, u32 aux_addr),
	TP_ARGS(table, row, value, aux_addr),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, table)
		__field(अचिन्हित पूर्णांक, row)
		__field(u32, value)
		__field(u32, aux_addr)
	),
	TP_fast_assign(
		__entry->table = table;
		__entry->row = row;
		__entry->value = value;
		__entry->aux_addr = aux_addr;
	),
	TP_prपूर्णांकk("[%u][%u] = { 0x%08x (flags = \"%s\", frame_num = %u); 0x%08x }",
		  __entry->table, __entry->row, __entry->value,
		  __prपूर्णांक_flags(__entry->value, " ", अणु (1 << 25), "B" पूर्ण),
		  __entry->value & 0x7FFFFF, __entry->aux_addr)
);

TRACE_EVENT(vde_ref_l0,
	TP_PROTO(अचिन्हित पूर्णांक frame_num),
	TP_ARGS(frame_num),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, frame_num)
	),
	TP_fast_assign(
		__entry->frame_num = frame_num;
	),
	TP_prपूर्णांकk("REF L0: DPB: Frame 0: frame_num = %u", __entry->frame_num)
);

TRACE_EVENT(vde_ref_l1,
	TP_PROTO(अचिन्हित पूर्णांक with_later_poc_nb,
		 अचिन्हित पूर्णांक with_earlier_poc_nb),
	TP_ARGS(with_later_poc_nb, with_earlier_poc_nb),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, with_later_poc_nb)
		__field(अचिन्हित पूर्णांक, with_earlier_poc_nb)
	),
	TP_fast_assign(
		__entry->with_later_poc_nb = with_later_poc_nb;
		__entry->with_earlier_poc_nb = with_earlier_poc_nb;
	),
	TP_prपूर्णांकk("REF L1: with_later_poc_nb %u, with_earlier_poc_nb %u",
		  __entry->with_later_poc_nb, __entry->with_earlier_poc_nb)
);

#पूर्ण_अगर /* TEGRA_VDE_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/staging/media/tegra-vde
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
