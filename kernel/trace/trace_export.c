<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_export.c - export basic ftrace utilities to user space
 *
 * Copyright (C) 2009 Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <linux/stringअगरy.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश "trace_output.h"

/* Stub function क्रम events with triggers */
अटल पूर्णांक ftrace_event_रेजिस्टर(काष्ठा trace_event_call *call,
				 क्रमागत trace_reg type, व्योम *data)
अणु
	वापस 0;
पूर्ण

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM	ftrace

/*
 * The FTRACE_ENTRY_REG macro allows ftrace entry to define रेजिस्टर
 * function and thus become accessible via perf.
 */
#अघोषित FTRACE_ENTRY_REG
#घोषणा FTRACE_ENTRY_REG(name, काष्ठा_name, id, tकाष्ठा, prपूर्णांक, regfn) \
	FTRACE_ENTRY(name, काष्ठा_name, id, PARAMS(tकाष्ठा), PARAMS(prपूर्णांक))

/* not needed क्रम this file */
#अघोषित __field_काष्ठा
#घोषणा __field_काष्ठा(type, item)

#अघोषित __field
#घोषणा __field(type, item)				type item;

#अघोषित __field_fn
#घोषणा __field_fn(type, item)				type item;

#अघोषित __field_desc
#घोषणा __field_desc(type, container, item)		type item;

#अघोषित __field_packed
#घोषणा __field_packed(type, container, item)		type item;

#अघोषित __array
#घोषणा __array(type, item, size)			type item[size];

#अघोषित __array_desc
#घोषणा __array_desc(type, container, item, size)	type item[size];

#अघोषित __dynamic_array
#घोषणा __dynamic_array(type, item)			type item[];

#अघोषित F_STRUCT
#घोषणा F_STRUCT(args...)				args

#अघोषित F_prपूर्णांकk
#घोषणा F_prपूर्णांकk(fmt, args...) fmt, args

#अघोषित FTRACE_ENTRY
#घोषणा FTRACE_ENTRY(name, काष्ठा_name, id, tकाष्ठा, prपूर्णांक)		\
काष्ठा ____ftrace_##name अणु						\
	tकाष्ठा								\
पूर्ण;									\
अटल व्योम __always_unused ____ftrace_check_##name(व्योम)		\
अणु									\
	काष्ठा ____ftrace_##name *__entry = शून्य;			\
									\
	/* क्रमce compile-समय check on F_prपूर्णांकk() */			\
	prपूर्णांकk(prपूर्णांक);							\
पूर्ण

#अघोषित FTRACE_ENTRY_DUP
#घोषणा FTRACE_ENTRY_DUP(name, काष्ठा_name, id, tकाष्ठा, prपूर्णांक)		\
	FTRACE_ENTRY(name, काष्ठा_name, id, PARAMS(tकाष्ठा), PARAMS(prपूर्णांक))

#समावेश "trace_entries.h"

#अघोषित __field_ext
#घोषणा __field_ext(_type, _item, _filter_type) अणु			\
	.type = #_type, .name = #_item,					\
	.size = माप(_type), .align = __alignof__(_type),		\
	is_चिन्हित_type(_type), .filter_type = _filter_type पूर्ण,


#अघोषित __field_ext_packed
#घोषणा __field_ext_packed(_type, _item, _filter_type) अणु	\
	.type = #_type, .name = #_item,				\
	.size = माप(_type), .align = 1,			\
	is_चिन्हित_type(_type), .filter_type = _filter_type पूर्ण,

#अघोषित __field
#घोषणा __field(_type, _item) __field_ext(_type, _item, FILTER_OTHER)

#अघोषित __field_fn
#घोषणा __field_fn(_type, _item) __field_ext(_type, _item, FILTER_TRACE_FN)

#अघोषित __field_desc
#घोषणा __field_desc(_type, _container, _item) __field_ext(_type, _item, FILTER_OTHER)

#अघोषित __field_packed
#घोषणा __field_packed(_type, _container, _item) __field_ext_packed(_type, _item, FILTER_OTHER)

#अघोषित __array
#घोषणा __array(_type, _item, _len) अणु					\
	.type = #_type"["__stringअगरy(_len)"]", .name = #_item,		\
	.size = माप(_type[_len]), .align = __alignof__(_type),	\
	is_चिन्हित_type(_type), .filter_type = FILTER_OTHER पूर्ण,

#अघोषित __array_desc
#घोषणा __array_desc(_type, _container, _item, _len) __array(_type, _item, _len)

#अघोषित __dynamic_array
#घोषणा __dynamic_array(_type, _item) अणु					\
	.type = #_type "[]", .name = #_item,				\
	.size = 0, .align = __alignof__(_type),				\
	is_चिन्हित_type(_type), .filter_type = FILTER_OTHER पूर्ण,

#अघोषित FTRACE_ENTRY
#घोषणा FTRACE_ENTRY(name, काष्ठा_name, id, tकाष्ठा, prपूर्णांक)		\
अटल काष्ठा trace_event_fields ftrace_event_fields_##name[] = अणु	\
	tकाष्ठा								\
	अणुपूर्ण पूर्ण;

#समावेश "trace_entries.h"

#अघोषित __entry
#घोषणा __entry REC

#अघोषित __field
#घोषणा __field(type, item)

#अघोषित __field_fn
#घोषणा __field_fn(type, item)

#अघोषित __field_desc
#घोषणा __field_desc(type, container, item)

#अघोषित __field_packed
#घोषणा __field_packed(type, container, item)

#अघोषित __array
#घोषणा __array(type, item, len)

#अघोषित __array_desc
#घोषणा __array_desc(type, container, item, len)

#अघोषित __dynamic_array
#घोषणा __dynamic_array(type, item)

#अघोषित F_prपूर्णांकk
#घोषणा F_prपूर्णांकk(fmt, args...) __stringअगरy(fmt) ", "  __stringअगरy(args)

#अघोषित FTRACE_ENTRY_REG
#घोषणा FTRACE_ENTRY_REG(call, काष्ठा_name, etype, tकाष्ठा, prपूर्णांक, regfn) \
अटल काष्ठा trace_event_class __refdata event_class_ftrace_##call = अणु	\
	.प्रणाली			= __stringअगरy(TRACE_SYSTEM),		\
	.fields_array		= ftrace_event_fields_##call,		\
	.fields			= LIST_HEAD_INIT(event_class_ftrace_##call.fields),\
	.reg			= regfn,				\
पूर्ण;									\
									\
काष्ठा trace_event_call __used event_##call = अणु				\
	.class			= &event_class_ftrace_##call,		\
	अणु								\
		.name			= #call,			\
	पूर्ण,								\
	.event.type		= etype,				\
	.prपूर्णांक_fmt		= prपूर्णांक,				\
	.flags			= TRACE_EVENT_FL_IGNORE_ENABLE,		\
पूर्ण;									\
अटल काष्ठा trace_event_call __used						\
__section("_ftrace_events") *__event_##call = &event_##call;

#अघोषित FTRACE_ENTRY
#घोषणा FTRACE_ENTRY(call, काष्ठा_name, etype, tकाष्ठा, prपूर्णांक)		\
	FTRACE_ENTRY_REG(call, काष्ठा_name, etype,			\
			 PARAMS(tकाष्ठा), PARAMS(prपूर्णांक), शून्य)

bool ftrace_event_is_function(काष्ठा trace_event_call *call)
अणु
	वापस call == &event_function;
पूर्ण

#समावेश "trace_entries.h"
