<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Because linux/module.h has tracepoपूर्णांकs in the header, and ftrace.h
 * used to include this file, define_trace.h includes linux/module.h
 * But we करो not want the module.h to override the TRACE_SYSTEM macro
 * variable that define_trace.h is processing, so we only set it
 * when module events are being processed, which would happen when
 * CREATE_TRACE_POINTS is defined.
 */
#अगर_घोषित CREATE_TRACE_POINTS
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM module
#पूर्ण_अगर

#अगर !defined(_TRACE_MODULE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_MODULE_H

#समावेश <linux/tracepoपूर्णांक.h>

#अगर_घोषित CONFIG_MODULES

काष्ठा module;

#घोषणा show_module_flags(flags) __prपूर्णांक_flags(flags, "",	\
	अणु (1UL << TAINT_PROPRIETARY_MODULE),	"P" पूर्ण,		\
	अणु (1UL << TAINT_OOT_MODULE),		"O" पूर्ण,		\
	अणु (1UL << TAINT_FORCED_MODULE),		"F" पूर्ण,		\
	अणु (1UL << TAINT_CRAP),			"C" पूर्ण,		\
	अणु (1UL << TAINT_UNSIGNED_MODULE),	"E" पूर्ण)

TRACE_EVENT(module_load,

	TP_PROTO(काष्ठा module *mod),

	TP_ARGS(mod),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	taपूर्णांकs		)
		__string(	name,		mod->name	)
	),

	TP_fast_assign(
		__entry->taपूर्णांकs = mod->taपूर्णांकs;
		__assign_str(name, mod->name);
	),

	TP_prपूर्णांकk("%s %s", __get_str(name), show_module_flags(__entry->taपूर्णांकs))
);

TRACE_EVENT(module_मुक्त,

	TP_PROTO(काष्ठा module *mod),

	TP_ARGS(mod),

	TP_STRUCT__entry(
		__string(	name,		mod->name	)
	),

	TP_fast_assign(
		__assign_str(name, mod->name);
	),

	TP_prपूर्णांकk("%s", __get_str(name))
);

#अगर_घोषित CONFIG_MODULE_UNLOAD
/* trace_module_get/put are only used अगर CONFIG_MODULE_UNLOAD is defined */

DECLARE_EVENT_CLASS(module_refcnt,

	TP_PROTO(काष्ठा module *mod, अचिन्हित दीर्घ ip),

	TP_ARGS(mod, ip),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	ip		)
		__field(	पूर्णांक,		refcnt		)
		__string(	name,		mod->name	)
	),

	TP_fast_assign(
		__entry->ip	= ip;
		__entry->refcnt	= atomic_पढ़ो(&mod->refcnt);
		__assign_str(name, mod->name);
	),

	TP_prपूर्णांकk("%s call_site=%ps refcnt=%d",
		  __get_str(name), (व्योम *)__entry->ip, __entry->refcnt)
);

DEFINE_EVENT(module_refcnt, module_get,

	TP_PROTO(काष्ठा module *mod, अचिन्हित दीर्घ ip),

	TP_ARGS(mod, ip)
);

DEFINE_EVENT(module_refcnt, module_put,

	TP_PROTO(काष्ठा module *mod, अचिन्हित दीर्घ ip),

	TP_ARGS(mod, ip)
);
#पूर्ण_अगर /* CONFIG_MODULE_UNLOAD */

TRACE_EVENT(module_request,

	TP_PROTO(अक्षर *name, bool रुको, अचिन्हित दीर्घ ip),

	TP_ARGS(name, रुको, ip),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	ip		)
		__field(	bool,		रुको		)
		__string(	name,		name		)
	),

	TP_fast_assign(
		__entry->ip	= ip;
		__entry->रुको	= रुको;
		__assign_str(name, name);
	),

	TP_prपूर्णांकk("%s wait=%d call_site=%ps",
		  __get_str(name), (पूर्णांक)__entry->रुको, (व्योम *)__entry->ip)
);

#पूर्ण_अगर /* CONFIG_MODULES */

#पूर्ण_अगर /* _TRACE_MODULE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
