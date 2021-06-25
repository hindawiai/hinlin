<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM regmap

#अगर !defined(_TRACE_REGMAP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_REGMAP_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश "internal.h"

/*
 * Log रेजिस्टर events
 */
DECLARE_EVENT_CLASS(regmap_reg,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		 अचिन्हित पूर्णांक val),

	TP_ARGS(map, reg, val),

	TP_STRUCT__entry(
		__string(	name,		regmap_name(map)	)
		__field(	अचिन्हित पूर्णांक,	reg			)
		__field(	अचिन्हित पूर्णांक,	val			)
	),

	TP_fast_assign(
		__assign_str(name, regmap_name(map));
		__entry->reg = reg;
		__entry->val = val;
	),

	TP_prपूर्णांकk("%s reg=%x val=%x", __get_str(name),
		  (अचिन्हित पूर्णांक)__entry->reg,
		  (अचिन्हित पूर्णांक)__entry->val)
);

DEFINE_EVENT(regmap_reg, regmap_reg_ग_लिखो,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		 अचिन्हित पूर्णांक val),

	TP_ARGS(map, reg, val)

);

DEFINE_EVENT(regmap_reg, regmap_reg_पढ़ो,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		 अचिन्हित पूर्णांक val),

	TP_ARGS(map, reg, val)

);

DEFINE_EVENT(regmap_reg, regmap_reg_पढ़ो_cache,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
		 अचिन्हित पूर्णांक val),

	TP_ARGS(map, reg, val)

);

DECLARE_EVENT_CLASS(regmap_block,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक count),

	TP_ARGS(map, reg, count),

	TP_STRUCT__entry(
		__string(	name,		regmap_name(map)	)
		__field(	अचिन्हित पूर्णांक,	reg			)
		__field(	पूर्णांक,		count			)
	),

	TP_fast_assign(
		__assign_str(name, regmap_name(map));
		__entry->reg = reg;
		__entry->count = count;
	),

	TP_prपूर्णांकk("%s reg=%x count=%d", __get_str(name),
		  (अचिन्हित पूर्णांक)__entry->reg,
		  (पूर्णांक)__entry->count)
);

DEFINE_EVENT(regmap_block, regmap_hw_पढ़ो_start,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक count),

	TP_ARGS(map, reg, count)
);

DEFINE_EVENT(regmap_block, regmap_hw_पढ़ो_करोne,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक count),

	TP_ARGS(map, reg, count)
);

DEFINE_EVENT(regmap_block, regmap_hw_ग_लिखो_start,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक count),

	TP_ARGS(map, reg, count)
);

DEFINE_EVENT(regmap_block, regmap_hw_ग_लिखो_करोne,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक count),

	TP_ARGS(map, reg, count)
);

TRACE_EVENT(regcache_sync,

	TP_PROTO(काष्ठा regmap *map, स्थिर अक्षर *type,
		 स्थिर अक्षर *status),

	TP_ARGS(map, type, status),

	TP_STRUCT__entry(
		__string(       name,           regmap_name(map)	)
		__string(	status,		status			)
		__string(	type,		type			)
	),

	TP_fast_assign(
		__assign_str(name, regmap_name(map));
		__assign_str(status, status);
		__assign_str(type, type);
	),

	TP_prपूर्णांकk("%s type=%s status=%s", __get_str(name),
		  __get_str(type), __get_str(status))
);

DECLARE_EVENT_CLASS(regmap_bool,

	TP_PROTO(काष्ठा regmap *map, bool flag),

	TP_ARGS(map, flag),

	TP_STRUCT__entry(
		__string(	name,		regmap_name(map)	)
		__field(	पूर्णांक,		flag			)
	),

	TP_fast_assign(
		__assign_str(name, regmap_name(map));
		__entry->flag = flag;
	),

	TP_prपूर्णांकk("%s flag=%d", __get_str(name),
		  (पूर्णांक)__entry->flag)
);

DEFINE_EVENT(regmap_bool, regmap_cache_only,

	TP_PROTO(काष्ठा regmap *map, bool flag),

	TP_ARGS(map, flag)

);

DEFINE_EVENT(regmap_bool, regmap_cache_bypass,

	TP_PROTO(काष्ठा regmap *map, bool flag),

	TP_ARGS(map, flag)

);

DECLARE_EVENT_CLASS(regmap_async,

	TP_PROTO(काष्ठा regmap *map),

	TP_ARGS(map),

	TP_STRUCT__entry(
		__string(	name,		regmap_name(map)	)
	),

	TP_fast_assign(
		__assign_str(name, regmap_name(map));
	),

	TP_prपूर्णांकk("%s", __get_str(name))
);

DEFINE_EVENT(regmap_block, regmap_async_ग_लिखो_start,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक count),

	TP_ARGS(map, reg, count)
);

DEFINE_EVENT(regmap_async, regmap_async_io_complete,

	TP_PROTO(काष्ठा regmap *map),

	TP_ARGS(map)

);

DEFINE_EVENT(regmap_async, regmap_async_complete_start,

	TP_PROTO(काष्ठा regmap *map),

	TP_ARGS(map)

);

DEFINE_EVENT(regmap_async, regmap_async_complete_करोne,

	TP_PROTO(काष्ठा regmap *map),

	TP_ARGS(map)

);

TRACE_EVENT(regcache_drop_region,

	TP_PROTO(काष्ठा regmap *map, अचिन्हित पूर्णांक from,
		 अचिन्हित पूर्णांक to),

	TP_ARGS(map, from, to),

	TP_STRUCT__entry(
		__string(       name,           regmap_name(map)	)
		__field(	अचिन्हित पूर्णांक,	from			)
		__field(	अचिन्हित पूर्णांक,	to			)
	),

	TP_fast_assign(
		__assign_str(name, regmap_name(map));
		__entry->from = from;
		__entry->to = to;
	),

	TP_prपूर्णांकk("%s %u-%u", __get_str(name), (अचिन्हित पूर्णांक)__entry->from,
		  (अचिन्हित पूर्णांक)__entry->to)
);

#पूर्ण_अगर /* _TRACE_REGMAP_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
