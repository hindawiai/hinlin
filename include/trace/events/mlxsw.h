<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2019 Mellanox Technologies. All rights reserved */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mlxsw

#अगर !defined(_MLXSW_TRACEPOINT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _MLXSW_TRACEPOINT_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा mlxsw_sp;
काष्ठा mlxsw_sp_acl_atcam_region;
काष्ठा mlxsw_sp_acl_tcam_vregion;

TRACE_EVENT(mlxsw_sp_acl_atcam_entry_add_ctcam_spill,
	TP_PROTO(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
		 स्थिर काष्ठा mlxsw_sp_acl_atcam_region *aregion),

	TP_ARGS(mlxsw_sp, aregion),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, mlxsw_sp)
		__field(स्थिर व्योम *, aregion)
	),

	TP_fast_assign(
		__entry->mlxsw_sp = mlxsw_sp;
		__entry->aregion = aregion;
	),

	TP_prपूर्णांकk("mlxsw_sp %p, aregion %p",
		  __entry->mlxsw_sp, __entry->aregion)
);

TRACE_EVENT(mlxsw_sp_acl_tcam_vregion_rehash,
	TP_PROTO(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
		 स्थिर काष्ठा mlxsw_sp_acl_tcam_vregion *vregion),

	TP_ARGS(mlxsw_sp, vregion),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, mlxsw_sp)
		__field(स्थिर व्योम *, vregion)
	),

	TP_fast_assign(
		__entry->mlxsw_sp = mlxsw_sp;
		__entry->vregion = vregion;
	),

	TP_prपूर्णांकk("mlxsw_sp %p, vregion %p",
		  __entry->mlxsw_sp, __entry->vregion)
);

TRACE_EVENT(mlxsw_sp_acl_tcam_vregion_migrate,
	TP_PROTO(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
		 स्थिर काष्ठा mlxsw_sp_acl_tcam_vregion *vregion),

	TP_ARGS(mlxsw_sp, vregion),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, mlxsw_sp)
		__field(स्थिर व्योम *, vregion)
	),

	TP_fast_assign(
		__entry->mlxsw_sp = mlxsw_sp;
		__entry->vregion = vregion;
	),

	TP_prपूर्णांकk("mlxsw_sp %p, vregion %p",
		  __entry->mlxsw_sp, __entry->vregion)
);

TRACE_EVENT(mlxsw_sp_acl_tcam_vregion_migrate_end,
	TP_PROTO(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
		 स्थिर काष्ठा mlxsw_sp_acl_tcam_vregion *vregion),

	TP_ARGS(mlxsw_sp, vregion),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, mlxsw_sp)
		__field(स्थिर व्योम *, vregion)
	),

	TP_fast_assign(
		__entry->mlxsw_sp = mlxsw_sp;
		__entry->vregion = vregion;
	),

	TP_prपूर्णांकk("mlxsw_sp %p, vregion %p",
		  __entry->mlxsw_sp, __entry->vregion)
);

TRACE_EVENT(mlxsw_sp_acl_tcam_vregion_rehash_rollback_failed,
	TP_PROTO(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
		 स्थिर काष्ठा mlxsw_sp_acl_tcam_vregion *vregion),

	TP_ARGS(mlxsw_sp, vregion),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, mlxsw_sp)
		__field(स्थिर व्योम *, vregion)
	),

	TP_fast_assign(
		__entry->mlxsw_sp = mlxsw_sp;
		__entry->vregion = vregion;
	),

	TP_prपूर्णांकk("mlxsw_sp %p, vregion %p",
		  __entry->mlxsw_sp, __entry->vregion)
);

#पूर्ण_अगर /* _MLXSW_TRACEPOINT_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
