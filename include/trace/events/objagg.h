<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM objagg

#अगर !defined(__TRACE_OBJAGG_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __TRACE_OBJAGG_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा objagg;
काष्ठा objagg_obj;

TRACE_EVENT(objagg_create,
	TP_PROTO(स्थिर काष्ठा objagg *objagg),

	TP_ARGS(objagg),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
	),

	TP_prपूर्णांकk("objagg %p", __entry->objagg)
);

TRACE_EVENT(objagg_destroy,
	TP_PROTO(स्थिर काष्ठा objagg *objagg),

	TP_ARGS(objagg),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
	),

	TP_prपूर्णांकk("objagg %p", __entry->objagg)
);

TRACE_EVENT(objagg_obj_create,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj),

	TP_ARGS(objagg, obj),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
	),

	TP_prपूर्णांकk("objagg %p, obj %p", __entry->objagg, __entry->obj)
);

TRACE_EVENT(objagg_obj_destroy,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj),

	TP_ARGS(objagg, obj),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
	),

	TP_prपूर्णांकk("objagg %p, obj %p", __entry->objagg, __entry->obj)
);

TRACE_EVENT(objagg_obj_get,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj,
		 अचिन्हित पूर्णांक refcount),

	TP_ARGS(objagg, obj, refcount),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
		__field(अचिन्हित पूर्णांक, refcount)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
		__entry->refcount = refcount;
	),

	TP_prपूर्णांकk("objagg %p, obj %p, refcount %u",
		  __entry->objagg, __entry->obj, __entry->refcount)
);

TRACE_EVENT(objagg_obj_put,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj,
		 अचिन्हित पूर्णांक refcount),

	TP_ARGS(objagg, obj, refcount),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
		__field(अचिन्हित पूर्णांक, refcount)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
		__entry->refcount = refcount;
	),

	TP_prपूर्णांकk("objagg %p, obj %p, refcount %u",
		  __entry->objagg, __entry->obj, __entry->refcount)
);

TRACE_EVENT(objagg_obj_parent_assign,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj,
		 स्थिर काष्ठा objagg_obj *parent,
		 अचिन्हित पूर्णांक parent_refcount),

	TP_ARGS(objagg, obj, parent, parent_refcount),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
		__field(स्थिर व्योम *, parent)
		__field(अचिन्हित पूर्णांक, parent_refcount)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
		__entry->parent = parent;
		__entry->parent_refcount = parent_refcount;
	),

	TP_prपूर्णांकk("objagg %p, obj %p, parent %p, parent_refcount %u",
		  __entry->objagg, __entry->obj,
		  __entry->parent, __entry->parent_refcount)
);

TRACE_EVENT(objagg_obj_parent_unassign,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj,
		 स्थिर काष्ठा objagg_obj *parent,
		 अचिन्हित पूर्णांक parent_refcount),

	TP_ARGS(objagg, obj, parent, parent_refcount),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
		__field(स्थिर व्योम *, parent)
		__field(अचिन्हित पूर्णांक, parent_refcount)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
		__entry->parent = parent;
		__entry->parent_refcount = parent_refcount;
	),

	TP_prपूर्णांकk("objagg %p, obj %p, parent %p, parent_refcount %u",
		  __entry->objagg, __entry->obj,
		  __entry->parent, __entry->parent_refcount)
);

TRACE_EVENT(objagg_obj_root_create,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj),

	TP_ARGS(objagg, obj),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
	),

	TP_prपूर्णांकk("objagg %p, obj %p",
		  __entry->objagg, __entry->obj)
);

TRACE_EVENT(objagg_obj_root_destroy,
	TP_PROTO(स्थिर काष्ठा objagg *objagg,
		 स्थिर काष्ठा objagg_obj *obj),

	TP_ARGS(objagg, obj),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, objagg)
		__field(स्थिर व्योम *, obj)
	),

	TP_fast_assign(
		__entry->objagg = objagg;
		__entry->obj = obj;
	),

	TP_prपूर्णांकk("objagg %p, obj %p",
		  __entry->objagg, __entry->obj)
);

#पूर्ण_अगर /* __TRACE_OBJAGG_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
