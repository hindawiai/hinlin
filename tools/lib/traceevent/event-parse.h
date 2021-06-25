<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 */
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#अगर_अघोषित _PARSE_EVENTS_H
#घोषणा _PARSE_EVENTS_H

#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <regex.h>
#समावेश <माला.स>

#समावेश "trace-seq.h"

#अगर_अघोषित __maybe_unused
#घोषणा __maybe_unused __attribute__((unused))
#पूर्ण_अगर

#अगर_अघोषित DEBUG_RECORD
#घोषणा DEBUG_RECORD 0
#पूर्ण_अगर

काष्ठा tep_record अणु
	अचिन्हित दीर्घ दीर्घ	ts;
	अचिन्हित दीर्घ दीर्घ	offset;
	दीर्घ दीर्घ		missed_events;	/* buffer dropped events beक्रमe */
	पूर्णांक			record_size;	/* size of binary record */
	पूर्णांक			size;		/* size of data */
	व्योम			*data;
	पूर्णांक			cpu;
	पूर्णांक			ref_count;
	पूर्णांक			locked;		/* Do not मुक्त, even अगर ref_count is zero */
	व्योम			*priv;
#अगर DEBUG_RECORD
	काष्ठा tep_record	*prev;
	काष्ठा tep_record	*next;
	दीर्घ			alloc_addr;
#पूर्ण_अगर
पूर्ण;

/* ----------------------- tep ----------------------- */

काष्ठा tep_handle;
काष्ठा tep_event;

प्रकार पूर्णांक (*tep_event_handler_func)(काष्ठा trace_seq *s,
				      काष्ठा tep_record *record,
				      काष्ठा tep_event *event,
				      व्योम *context);

प्रकार पूर्णांक (*tep_plugin_load_func)(काष्ठा tep_handle *tep);
प्रकार पूर्णांक (*tep_plugin_unload_func)(काष्ठा tep_handle *tep);

काष्ठा tep_plugin_option अणु
	काष्ठा tep_plugin_option	*next;
	व्योम				*handle;
	अक्षर				*file;
	अक्षर				*name;
	अक्षर				*plugin_alias;
	अक्षर				*description;
	स्थिर अक्षर			*value;
	व्योम				*priv;
	पूर्णांक				set;
पूर्ण;

/*
 * Plugin hooks that can be called:
 *
 * TEP_PLUGIN_LOADER:  (required)
 *   The function name to initialized the plugin.
 *
 *   पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
 *
 * TEP_PLUGIN_UNLOADER:  (optional)
 *   The function called just beक्रमe unloading
 *
 *   पूर्णांक TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
 *
 * TEP_PLUGIN_OPTIONS:  (optional)
 *   Plugin options that can be set beक्रमe loading
 *
 *   काष्ठा tep_plugin_option TEP_PLUGIN_OPTIONS[] = अणु
 *	अणु
 *		.name = "option-name",
 *		.plugin_alias = "override-file-name", (optional)
 *		.description = "description of option to show users",
 *	पूर्ण,
 *	अणु
 *		.name = शून्य,
 *	पूर्ण,
 *   पूर्ण;
 *
 *   Array must end with .name = शून्य;
 *
 *
 *   .plugin_alias is used to give a लघुer name to access
 *   the vairable. Useful अगर a plugin handles more than one event.
 *
 *   If .value is not set, then it is considered a boolean and only
 *   .set will be processed. If .value is defined, then it is considered
 *   a string option and .set will be ignored.
 *
 * TEP_PLUGIN_ALIAS: (optional)
 *   The name to use क्रम finding options (uses filename अगर not defined)
 */
#घोषणा TEP_PLUGIN_LOADER tep_plugin_loader
#घोषणा TEP_PLUGIN_UNLOADER tep_plugin_unloader
#घोषणा TEP_PLUGIN_OPTIONS tep_plugin_options
#घोषणा TEP_PLUGIN_ALIAS tep_plugin_alias
#घोषणा _MAKE_STR(x)	#x
#घोषणा MAKE_STR(x)	_MAKE_STR(x)
#घोषणा TEP_PLUGIN_LOADER_NAME MAKE_STR(TEP_PLUGIN_LOADER)
#घोषणा TEP_PLUGIN_UNLOADER_NAME MAKE_STR(TEP_PLUGIN_UNLOADER)
#घोषणा TEP_PLUGIN_OPTIONS_NAME MAKE_STR(TEP_PLUGIN_OPTIONS)
#घोषणा TEP_PLUGIN_ALIAS_NAME MAKE_STR(TEP_PLUGIN_ALIAS)

क्रमागत tep_क्रमmat_flags अणु
	TEP_FIELD_IS_ARRAY	= 1,
	TEP_FIELD_IS_POINTER	= 2,
	TEP_FIELD_IS_SIGNED	= 4,
	TEP_FIELD_IS_STRING	= 8,
	TEP_FIELD_IS_DYNAMIC	= 16,
	TEP_FIELD_IS_LONG	= 32,
	TEP_FIELD_IS_FLAG	= 64,
	TEP_FIELD_IS_SYMBOLIC	= 128,
पूर्ण;

काष्ठा tep_क्रमmat_field अणु
	काष्ठा tep_क्रमmat_field	*next;
	काष्ठा tep_event	*event;
	अक्षर			*type;
	अक्षर			*name;
	अक्षर			*alias;
	पूर्णांक			offset;
	पूर्णांक			size;
	अचिन्हित पूर्णांक		arraylen;
	अचिन्हित पूर्णांक		elementsize;
	अचिन्हित दीर्घ		flags;
पूर्ण;

काष्ठा tep_क्रमmat अणु
	पूर्णांक			nr_common;
	पूर्णांक			nr_fields;
	काष्ठा tep_क्रमmat_field	*common_fields;
	काष्ठा tep_क्रमmat_field	*fields;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_atom अणु
	अक्षर			*atom;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_string अणु
	अक्षर			*string;
	पूर्णांक			offset;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_biपंचांगask अणु
	अक्षर			*biपंचांगask;
	पूर्णांक			offset;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_field अणु
	अक्षर			*name;
	काष्ठा tep_क्रमmat_field	*field;
पूर्ण;

काष्ठा tep_prपूर्णांक_flag_sym अणु
	काष्ठा tep_prपूर्णांक_flag_sym	*next;
	अक्षर				*value;
	अक्षर				*str;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_typecast अणु
	अक्षर 			*type;
	काष्ठा tep_prपूर्णांक_arg	*item;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_flags अणु
	काष्ठा tep_prपूर्णांक_arg		*field;
	अक्षर				*delim;
	काष्ठा tep_prपूर्णांक_flag_sym	*flags;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_symbol अणु
	काष्ठा tep_prपूर्णांक_arg		*field;
	काष्ठा tep_prपूर्णांक_flag_sym	*symbols;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_hex अणु
	काष्ठा tep_prपूर्णांक_arg	*field;
	काष्ठा tep_prपूर्णांक_arg	*size;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_पूर्णांक_array अणु
	काष्ठा tep_prपूर्णांक_arg	*field;
	काष्ठा tep_prपूर्णांक_arg	*count;
	काष्ठा tep_prपूर्णांक_arg	*el_size;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg_dynarray अणु
	काष्ठा tep_क्रमmat_field	*field;
	काष्ठा tep_prपूर्णांक_arg	*index;
पूर्ण;

काष्ठा tep_prपूर्णांक_arg;

काष्ठा tep_prपूर्णांक_arg_op अणु
	अक्षर			*op;
	पूर्णांक			prio;
	काष्ठा tep_prपूर्णांक_arg	*left;
	काष्ठा tep_prपूर्णांक_arg	*right;
पूर्ण;

काष्ठा tep_function_handler;

काष्ठा tep_prपूर्णांक_arg_func अणु
	काष्ठा tep_function_handler	*func;
	काष्ठा tep_prपूर्णांक_arg		*args;
पूर्ण;

क्रमागत tep_prपूर्णांक_arg_type अणु
	TEP_PRINT_शून्य,
	TEP_PRINT_ATOM,
	TEP_PRINT_FIELD,
	TEP_PRINT_FLAGS,
	TEP_PRINT_SYMBOL,
	TEP_PRINT_HEX,
	TEP_PRINT_INT_ARRAY,
	TEP_PRINT_TYPE,
	TEP_PRINT_STRING,
	TEP_PRINT_BSTRING,
	TEP_PRINT_DYNAMIC_ARRAY,
	TEP_PRINT_OP,
	TEP_PRINT_FUNC,
	TEP_PRINT_BITMASK,
	TEP_PRINT_DYNAMIC_ARRAY_LEN,
	TEP_PRINT_HEX_STR,
पूर्ण;

काष्ठा tep_prपूर्णांक_arg अणु
	काष्ठा tep_prपूर्णांक_arg		*next;
	क्रमागत tep_prपूर्णांक_arg_type		type;
	जोड़ अणु
		काष्ठा tep_prपूर्णांक_arg_atom	atom;
		काष्ठा tep_prपूर्णांक_arg_field	field;
		काष्ठा tep_prपूर्णांक_arg_typecast	typecast;
		काष्ठा tep_prपूर्णांक_arg_flags	flags;
		काष्ठा tep_prपूर्णांक_arg_symbol	symbol;
		काष्ठा tep_prपूर्णांक_arg_hex	hex;
		काष्ठा tep_prपूर्णांक_arg_पूर्णांक_array	पूर्णांक_array;
		काष्ठा tep_prपूर्णांक_arg_func	func;
		काष्ठा tep_prपूर्णांक_arg_string	string;
		काष्ठा tep_prपूर्णांक_arg_biपंचांगask	biपंचांगask;
		काष्ठा tep_prपूर्णांक_arg_op		op;
		काष्ठा tep_prपूर्णांक_arg_dynarray	dynarray;
	पूर्ण;
पूर्ण;

काष्ठा tep_prपूर्णांक_parse;

काष्ठा tep_prपूर्णांक_fmt अणु
	अक्षर			*क्रमmat;
	काष्ठा tep_prपूर्णांक_arg	*args;
	काष्ठा tep_prपूर्णांक_parse	*prपूर्णांक_cache;
पूर्ण;

काष्ठा tep_event अणु
	काष्ठा tep_handle	*tep;
	अक्षर			*name;
	पूर्णांक			id;
	पूर्णांक			flags;
	काष्ठा tep_क्रमmat	क्रमmat;
	काष्ठा tep_prपूर्णांक_fmt	prपूर्णांक_fmt;
	अक्षर			*प्रणाली;
	tep_event_handler_func	handler;
	व्योम			*context;
पूर्ण;

क्रमागत अणु
	TEP_EVENT_FL_ISFTRACE	= 0x01,
	TEP_EVENT_FL_ISPRINT	= 0x02,
	TEP_EVENT_FL_ISBPRINT	= 0x04,
	TEP_EVENT_FL_ISFUNCENT	= 0x10,
	TEP_EVENT_FL_ISFUNCRET	= 0x20,
	TEP_EVENT_FL_NOHANDLE	= 0x40,
	TEP_EVENT_FL_PRINTRAW	= 0x80,

	TEP_EVENT_FL_FAILED	= 0x80000000
पूर्ण;

क्रमागत tep_event_sort_type अणु
	TEP_EVENT_SORT_ID,
	TEP_EVENT_SORT_NAME,
	TEP_EVENT_SORT_SYSTEM,
पूर्ण;

क्रमागत tep_event_type अणु
	TEP_EVENT_ERROR,
	TEP_EVENT_NONE,
	TEP_EVENT_SPACE,
	TEP_EVENT_NEWLINE,
	TEP_EVENT_OP,
	TEP_EVENT_DELIM,
	TEP_EVENT_ITEM,
	TEP_EVENT_DQUOTE,
	TEP_EVENT_SQUOTE,
पूर्ण;

प्रकार अचिन्हित दीर्घ दीर्घ (*tep_func_handler)(काष्ठा trace_seq *s,
					       अचिन्हित दीर्घ दीर्घ *args);

क्रमागत tep_func_arg_type अणु
	TEP_FUNC_ARG_VOID,
	TEP_FUNC_ARG_INT,
	TEP_FUNC_ARG_LONG,
	TEP_FUNC_ARG_STRING,
	TEP_FUNC_ARG_PTR,
	TEP_FUNC_ARG_MAX_TYPES
पूर्ण;

क्रमागत tep_flag अणु
	TEP_NSEC_OUTPUT		= 1,	/* output in NSECS */
	TEP_DISABLE_SYS_PLUGINS	= 1 << 1,
	TEP_DISABLE_PLUGINS	= 1 << 2,
पूर्ण;

#घोषणा TEP_ERRORS 							      \
	_PE(MEM_ALLOC_FAILED,	"failed to allocate memory"),		      \
	_PE(PARSE_EVENT_FAILED,	"failed to parse event"),		      \
	_PE(READ_ID_FAILED,	"failed to read event id"),		      \
	_PE(READ_FORMAT_FAILED,	"failed to read event format"),		      \
	_PE(READ_PRINT_FAILED,	"failed to read event print fmt"), 	      \
	_PE(OLD_FTRACE_ARG_FAILED,"failed to allocate field name for ftrace"),\
	_PE(INVALID_ARG_TYPE,	"invalid argument type"),		      \
	_PE(INVALID_EXP_TYPE,	"invalid expression type"),		      \
	_PE(INVALID_OP_TYPE,	"invalid operator type"),		      \
	_PE(INVALID_EVENT_NAME,	"invalid event name"),			      \
	_PE(EVENT_NOT_FOUND,	"no event found"),			      \
	_PE(SYNTAX_ERROR,	"syntax error"),			      \
	_PE(ILLEGAL_RVALUE,	"illegal rvalue"),			      \
	_PE(ILLEGAL_LVALUE,	"illegal lvalue for string comparison"),      \
	_PE(INVALID_REGEX,	"regex did not compute"),		      \
	_PE(ILLEGAL_STRING_CMP,	"illegal comparison for string"), 	      \
	_PE(ILLEGAL_INTEGER_CMP,"illegal comparison for integer"), 	      \
	_PE(REPARENT_NOT_OP,	"cannot reparent other than OP"),	      \
	_PE(REPARENT_FAILED,	"failed to reparent filter OP"),	      \
	_PE(BAD_FILTER_ARG,	"bad arg in filter tree"),		      \
	_PE(UNEXPECTED_TYPE,	"unexpected type (not a value)"),	      \
	_PE(ILLEGAL_TOKEN,	"illegal token"),			      \
	_PE(INVALID_PAREN,	"open parenthesis cannot come here"), 	      \
	_PE(UNBALANCED_PAREN,	"unbalanced number of parenthesis"),	      \
	_PE(UNKNOWN_TOKEN,	"unknown token"),			      \
	_PE(FILTER_NOT_FOUND,	"no filter found"),			      \
	_PE(NOT_A_NUMBER,	"must have number field"),		      \
	_PE(NO_FILTER,		"no filters exists"),			      \
	_PE(FILTER_MISS,	"record does not match to filter")

#अघोषित _PE
#घोषणा _PE(__code, __str) TEP_ERRNO__ ## __code
क्रमागत tep_त्रुटि_सं अणु
	TEP_ERRNO__SUCCESS			= 0,
	TEP_ERRNO__FILTER_MATCH			= TEP_ERRNO__SUCCESS,

	/*
	 * Choose an arbitrary negative big number not to clash with standard
	 * त्रुटि_सं since SUS requires the त्रुटि_सं has distinct positive values.
	 * See 'Issue 6' in the link below.
	 *
	 * https://pubs.खोलोgroup.org/onlinepubs/9699919799/basedefs/त्रुटिसं.स.hपंचांगl
	 */
	__TEP_ERRNO__START			= -100000,

	TEP_ERRORS,

	__TEP_ERRNO__END,
पूर्ण;
#अघोषित _PE

काष्ठा tep_plugin_list;

#घोषणा INVALID_PLUGIN_LIST_OPTION	((अक्षर **)((अचिन्हित दीर्घ)-1))

क्रमागत tep_plugin_load_priority अणु
	TEP_PLUGIN_FIRST,
	TEP_PLUGIN_LAST,
पूर्ण;

पूर्णांक tep_add_plugin_path(काष्ठा tep_handle *tep, अक्षर *path,
			क्रमागत tep_plugin_load_priority prio);
काष्ठा tep_plugin_list *tep_load_plugins(काष्ठा tep_handle *tep);
व्योम tep_unload_plugins(काष्ठा tep_plugin_list *plugin_list,
			काष्ठा tep_handle *tep);
व्योम tep_load_plugins_hook(काष्ठा tep_handle *tep, स्थिर अक्षर *suffix,
			   व्योम (*load_plugin)(काष्ठा tep_handle *tep,
					       स्थिर अक्षर *path,
					       स्थिर अक्षर *name,
					       व्योम *data),
			   व्योम *data);
अक्षर **tep_plugin_list_options(व्योम);
व्योम tep_plugin_मुक्त_options_list(अक्षर **list);
पूर्णांक tep_plugin_add_options(स्थिर अक्षर *name,
			   काष्ठा tep_plugin_option *options);
पूर्णांक tep_plugin_add_option(स्थिर अक्षर *name, स्थिर अक्षर *val);
व्योम tep_plugin_हटाओ_options(काष्ठा tep_plugin_option *options);
व्योम tep_plugin_prपूर्णांक_options(काष्ठा trace_seq *s);
व्योम tep_prपूर्णांक_plugins(काष्ठा trace_seq *s,
			स्थिर अक्षर *prefix, स्थिर अक्षर *suffix,
			स्थिर काष्ठा tep_plugin_list *list);

/* tep_handle */
प्रकार अक्षर *(tep_func_resolver_t)(व्योम *priv,
				    अचिन्हित दीर्घ दीर्घ *addrp, अक्षर **modp);
व्योम tep_set_flag(काष्ठा tep_handle *tep, पूर्णांक flag);
व्योम tep_clear_flag(काष्ठा tep_handle *tep, क्रमागत tep_flag flag);
bool tep_test_flag(काष्ठा tep_handle *tep, क्रमागत tep_flag flags);

अटल अंतरभूत पूर्णांक tep_is_bigendian(व्योम)
अणु
	अचिन्हित अक्षर str[] = अणु 0x1, 0x2, 0x3, 0x4 पूर्ण;
	अचिन्हित पूर्णांक val;

	स_नकल(&val, str, 4);
	वापस val == 0x01020304;
पूर्ण

/* taken from kernel/trace/trace.h */
क्रमागत trace_flag_type अणु
	TRACE_FLAG_IRQS_OFF		= 0x01,
	TRACE_FLAG_IRQS_NOSUPPORT	= 0x02,
	TRACE_FLAG_NEED_RESCHED		= 0x04,
	TRACE_FLAG_HARसूचीQ		= 0x08,
	TRACE_FLAG_SOFTIRQ		= 0x10,
पूर्ण;

पूर्णांक tep_set_function_resolver(काष्ठा tep_handle *tep,
			      tep_func_resolver_t *func, व्योम *priv);
व्योम tep_reset_function_resolver(काष्ठा tep_handle *tep);
पूर्णांक tep_रेजिस्टर_comm(काष्ठा tep_handle *tep, स्थिर अक्षर *comm, पूर्णांक pid);
पूर्णांक tep_override_comm(काष्ठा tep_handle *tep, स्थिर अक्षर *comm, पूर्णांक pid);
पूर्णांक tep_रेजिस्टर_function(काष्ठा tep_handle *tep, अक्षर *name,
			  अचिन्हित दीर्घ दीर्घ addr, अक्षर *mod);
पूर्णांक tep_रेजिस्टर_prपूर्णांक_string(काष्ठा tep_handle *tep, स्थिर अक्षर *fmt,
			      अचिन्हित दीर्घ दीर्घ addr);
bool tep_is_pid_रेजिस्टरed(काष्ठा tep_handle *tep, पूर्णांक pid);

काष्ठा tep_event *tep_get_event(काष्ठा tep_handle *tep, पूर्णांक index);

#घोषणा TEP_PRINT_INFO		"INFO"
#घोषणा TEP_PRINT_INFO_RAW	"INFO_RAW"
#घोषणा TEP_PRINT_COMM		"COMM"
#घोषणा TEP_PRINT_LATENCY	"LATENCY"
#घोषणा TEP_PRINT_NAME		"NAME"
#घोषणा TEP_PRINT_PID		1U
#घोषणा TEP_PRINT_TIME		2U
#घोषणा TEP_PRINT_CPU		3U

व्योम tep_prपूर्णांक_event(काष्ठा tep_handle *tep, काष्ठा trace_seq *s,
		     काष्ठा tep_record *record, स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 4, 5)));

पूर्णांक tep_parse_header_page(काष्ठा tep_handle *tep, अक्षर *buf, अचिन्हित दीर्घ size,
			  पूर्णांक दीर्घ_size);

क्रमागत tep_त्रुटि_सं tep_parse_event(काष्ठा tep_handle *tep, स्थिर अक्षर *buf,
			       अचिन्हित दीर्घ size, स्थिर अक्षर *sys);
क्रमागत tep_त्रुटि_सं tep_parse_क्रमmat(काष्ठा tep_handle *tep,
				काष्ठा tep_event **eventp,
				स्थिर अक्षर *buf,
				अचिन्हित दीर्घ size, स्थिर अक्षर *sys);

व्योम *tep_get_field_raw(काष्ठा trace_seq *s, काष्ठा tep_event *event,
			स्थिर अक्षर *name, काष्ठा tep_record *record,
			पूर्णांक *len, पूर्णांक err);

पूर्णांक tep_get_field_val(काष्ठा trace_seq *s, काष्ठा tep_event *event,
		      स्थिर अक्षर *name, काष्ठा tep_record *record,
		      अचिन्हित दीर्घ दीर्घ *val, पूर्णांक err);
पूर्णांक tep_get_common_field_val(काष्ठा trace_seq *s, काष्ठा tep_event *event,
			     स्थिर अक्षर *name, काष्ठा tep_record *record,
			     अचिन्हित दीर्घ दीर्घ *val, पूर्णांक err);
पूर्णांक tep_get_any_field_val(काष्ठा trace_seq *s, काष्ठा tep_event *event,
			  स्थिर अक्षर *name, काष्ठा tep_record *record,
			  अचिन्हित दीर्घ दीर्घ *val, पूर्णांक err);

पूर्णांक tep_prपूर्णांक_num_field(काष्ठा trace_seq *s, स्थिर अक्षर *fmt,
			काष्ठा tep_event *event, स्थिर अक्षर *name,
			काष्ठा tep_record *record, पूर्णांक err);

पूर्णांक tep_prपूर्णांक_func_field(काष्ठा trace_seq *s, स्थिर अक्षर *fmt,
			 काष्ठा tep_event *event, स्थिर अक्षर *name,
			 काष्ठा tep_record *record, पूर्णांक err);

क्रमागत tep_reg_handler अणु
	TEP_REGISTER_SUCCESS = 0,
	TEP_REGISTER_SUCCESS_OVERWRITE,
पूर्ण;

पूर्णांक tep_रेजिस्टर_event_handler(काष्ठा tep_handle *tep, पूर्णांक id,
			       स्थिर अक्षर *sys_name, स्थिर अक्षर *event_name,
			       tep_event_handler_func func, व्योम *context);
पूर्णांक tep_unरेजिस्टर_event_handler(काष्ठा tep_handle *tep, पूर्णांक id,
				 स्थिर अक्षर *sys_name, स्थिर अक्षर *event_name,
				 tep_event_handler_func func, व्योम *context);
पूर्णांक tep_रेजिस्टर_prपूर्णांक_function(काष्ठा tep_handle *tep,
				tep_func_handler func,
				क्रमागत tep_func_arg_type ret_type,
				अक्षर *name, ...);
पूर्णांक tep_unरेजिस्टर_prपूर्णांक_function(काष्ठा tep_handle *tep,
				  tep_func_handler func, अक्षर *name);

काष्ठा tep_क्रमmat_field *tep_find_common_field(काष्ठा tep_event *event, स्थिर अक्षर *name);
काष्ठा tep_क्रमmat_field *tep_find_field(काष्ठा tep_event *event, स्थिर अक्षर *name);
काष्ठा tep_क्रमmat_field *tep_find_any_field(काष्ठा tep_event *event, स्थिर अक्षर *name);

स्थिर अक्षर *tep_find_function(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ addr);
अचिन्हित दीर्घ दीर्घ
tep_find_function_address(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ addr);
अचिन्हित दीर्घ दीर्घ tep_पढ़ो_number(काष्ठा tep_handle *tep, स्थिर व्योम *ptr, पूर्णांक size);
पूर्णांक tep_पढ़ो_number_field(काष्ठा tep_क्रमmat_field *field, स्थिर व्योम *data,
			  अचिन्हित दीर्घ दीर्घ *value);

काष्ठा tep_event *tep_get_first_event(काष्ठा tep_handle *tep);
पूर्णांक tep_get_events_count(काष्ठा tep_handle *tep);
काष्ठा tep_event *tep_find_event(काष्ठा tep_handle *tep, पूर्णांक id);

काष्ठा tep_event *
tep_find_event_by_name(काष्ठा tep_handle *tep, स्थिर अक्षर *sys, स्थिर अक्षर *name);
काष्ठा tep_event *
tep_find_event_by_record(काष्ठा tep_handle *tep, काष्ठा tep_record *record);

पूर्णांक tep_data_type(काष्ठा tep_handle *tep, काष्ठा tep_record *rec);
पूर्णांक tep_data_pid(काष्ठा tep_handle *tep, काष्ठा tep_record *rec);
पूर्णांक tep_data_preempt_count(काष्ठा tep_handle *tep, काष्ठा tep_record *rec);
पूर्णांक tep_data_flags(काष्ठा tep_handle *tep, काष्ठा tep_record *rec);
स्थिर अक्षर *tep_data_comm_from_pid(काष्ठा tep_handle *tep, पूर्णांक pid);
काष्ठा tep_cmdline;
काष्ठा tep_cmdline *tep_data_pid_from_comm(काष्ठा tep_handle *tep, स्थिर अक्षर *comm,
					   काष्ठा tep_cmdline *next);
पूर्णांक tep_cmdline_pid(काष्ठा tep_handle *tep, काष्ठा tep_cmdline *cmdline);

व्योम tep_prपूर्णांक_field(काष्ठा trace_seq *s, व्योम *data,
		     काष्ठा tep_क्रमmat_field *field);
व्योम tep_prपूर्णांक_fields(काष्ठा trace_seq *s, व्योम *data,
		      पूर्णांक size __maybe_unused, काष्ठा tep_event *event);
पूर्णांक tep_म_त्रुटि(काष्ठा tep_handle *tep, क्रमागत tep_त्रुटि_सं errnum,
		 अक्षर *buf, माप_प्रकार buflen);

काष्ठा tep_event **tep_list_events(काष्ठा tep_handle *tep, क्रमागत tep_event_sort_type);
काष्ठा tep_event **tep_list_events_copy(काष्ठा tep_handle *tep,
					क्रमागत tep_event_sort_type);
काष्ठा tep_क्रमmat_field **tep_event_common_fields(काष्ठा tep_event *event);
काष्ठा tep_क्रमmat_field **tep_event_fields(काष्ठा tep_event *event);

क्रमागत tep_endian अणु
        TEP_LITTLE_ENDIAN = 0,
        TEP_BIG_ENDIAN
पूर्ण;
पूर्णांक tep_get_cpus(काष्ठा tep_handle *tep);
व्योम tep_set_cpus(काष्ठा tep_handle *tep, पूर्णांक cpus);
पूर्णांक tep_get_दीर्घ_size(काष्ठा tep_handle *tep);
व्योम tep_set_दीर्घ_size(काष्ठा tep_handle *tep, पूर्णांक दीर्घ_size);
पूर्णांक tep_get_page_size(काष्ठा tep_handle *tep);
व्योम tep_set_page_size(काष्ठा tep_handle *tep, पूर्णांक _page_size);
bool tep_is_file_bigendian(काष्ठा tep_handle *tep);
व्योम tep_set_file_bigendian(काष्ठा tep_handle *tep, क्रमागत tep_endian endian);
bool tep_is_local_bigendian(काष्ठा tep_handle *tep);
व्योम tep_set_local_bigendian(काष्ठा tep_handle *tep, क्रमागत tep_endian endian);
पूर्णांक tep_get_header_page_size(काष्ठा tep_handle *tep);
पूर्णांक tep_get_header_बारtamp_size(काष्ठा tep_handle *tep);
bool tep_is_old_क्रमmat(काष्ठा tep_handle *tep);
व्योम tep_set_test_filters(काष्ठा tep_handle *tep, पूर्णांक test_filters);

काष्ठा tep_handle *tep_alloc(व्योम);
व्योम tep_मुक्त(काष्ठा tep_handle *tep);
व्योम tep_ref(काष्ठा tep_handle *tep);
व्योम tep_unref(काष्ठा tep_handle *tep);
पूर्णांक tep_get_ref(काष्ठा tep_handle *tep);

/* क्रम debugging */
व्योम tep_prपूर्णांक_funcs(काष्ठा tep_handle *tep);
व्योम tep_prपूर्णांक_prपूर्णांकk(काष्ठा tep_handle *tep);

/* ----------------------- filtering ----------------------- */

क्रमागत tep_filter_boolean_type अणु
	TEP_FILTER_FALSE,
	TEP_FILTER_TRUE,
पूर्ण;

क्रमागत tep_filter_op_type अणु
	TEP_FILTER_OP_AND = 1,
	TEP_FILTER_OP_OR,
	TEP_FILTER_OP_NOT,
पूर्ण;

क्रमागत tep_filter_cmp_type अणु
	TEP_FILTER_CMP_NONE,
	TEP_FILTER_CMP_EQ,
	TEP_FILTER_CMP_NE,
	TEP_FILTER_CMP_GT,
	TEP_FILTER_CMP_LT,
	TEP_FILTER_CMP_GE,
	TEP_FILTER_CMP_LE,
	TEP_FILTER_CMP_MATCH,
	TEP_FILTER_CMP_NOT_MATCH,
	TEP_FILTER_CMP_REGEX,
	TEP_FILTER_CMP_NOT_REGEX,
पूर्ण;

क्रमागत tep_filter_exp_type अणु
	TEP_FILTER_EXP_NONE,
	TEP_FILTER_EXP_ADD,
	TEP_FILTER_EXP_SUB,
	TEP_FILTER_EXP_MUL,
	TEP_FILTER_EXP_DIV,
	TEP_FILTER_EXP_MOD,
	TEP_FILTER_EXP_RSHIFT,
	TEP_FILTER_EXP_LSHIFT,
	TEP_FILTER_EXP_AND,
	TEP_FILTER_EXP_OR,
	TEP_FILTER_EXP_XOR,
	TEP_FILTER_EXP_NOT,
पूर्ण;

क्रमागत tep_filter_arg_type अणु
	TEP_FILTER_ARG_NONE,
	TEP_FILTER_ARG_BOOLEAN,
	TEP_FILTER_ARG_VALUE,
	TEP_FILTER_ARG_FIELD,
	TEP_FILTER_ARG_EXP,
	TEP_FILTER_ARG_OP,
	TEP_FILTER_ARG_NUM,
	TEP_FILTER_ARG_STR,
पूर्ण;

क्रमागत tep_filter_value_type अणु
	TEP_FILTER_NUMBER,
	TEP_FILTER_STRING,
	TEP_FILTER_CHAR
पूर्ण;

काष्ठा tep_filter_arg;

काष्ठा tep_filter_arg_boolean अणु
	क्रमागत tep_filter_boolean_type	value;
पूर्ण;

काष्ठा tep_filter_arg_field अणु
	काष्ठा tep_क्रमmat_field		*field;
पूर्ण;

काष्ठा tep_filter_arg_value अणु
	क्रमागत tep_filter_value_type	type;
	जोड़ अणु
		अक्षर			*str;
		अचिन्हित दीर्घ दीर्घ	val;
	पूर्ण;
पूर्ण;

काष्ठा tep_filter_arg_op अणु
	क्रमागत tep_filter_op_type		type;
	काष्ठा tep_filter_arg		*left;
	काष्ठा tep_filter_arg		*right;
पूर्ण;

काष्ठा tep_filter_arg_exp अणु
	क्रमागत tep_filter_exp_type	type;
	काष्ठा tep_filter_arg		*left;
	काष्ठा tep_filter_arg		*right;
पूर्ण;

काष्ठा tep_filter_arg_num अणु
	क्रमागत tep_filter_cmp_type	type;
	काष्ठा tep_filter_arg		*left;
	काष्ठा tep_filter_arg		*right;
पूर्ण;

काष्ठा tep_filter_arg_str अणु
	क्रमागत tep_filter_cmp_type	type;
	काष्ठा tep_क्रमmat_field		*field;
	अक्षर				*val;
	अक्षर				*buffer;
	regex_t				reg;
पूर्ण;

काष्ठा tep_filter_arg अणु
	क्रमागत tep_filter_arg_type		type;
	जोड़ अणु
		काष्ठा tep_filter_arg_boolean	boolean;
		काष्ठा tep_filter_arg_field	field;
		काष्ठा tep_filter_arg_value	value;
		काष्ठा tep_filter_arg_op	op;
		काष्ठा tep_filter_arg_exp	exp;
		काष्ठा tep_filter_arg_num	num;
		काष्ठा tep_filter_arg_str	str;
	पूर्ण;
पूर्ण;

काष्ठा tep_filter_type अणु
	पूर्णांक			event_id;
	काष्ठा tep_event	*event;
	काष्ठा tep_filter_arg	*filter;
पूर्ण;

#घोषणा TEP_FILTER_ERROR_BUFSZ  1024

काष्ठा tep_event_filter अणु
	काष्ठा tep_handle	*tep;
	पूर्णांक			filters;
	काष्ठा tep_filter_type	*event_filters;
	अक्षर			error_buffer[TEP_FILTER_ERROR_BUFSZ];
पूर्ण;

काष्ठा tep_event_filter *tep_filter_alloc(काष्ठा tep_handle *tep);

/* क्रम backward compatibility */
#घोषणा FILTER_NONE		TEP_ERRNO__NO_FILTER
#घोषणा FILTER_NOEXIST		TEP_ERRNO__FILTER_NOT_FOUND
#घोषणा FILTER_MISS		TEP_ERRNO__FILTER_MISS
#घोषणा FILTER_MATCH		TEP_ERRNO__FILTER_MATCH

क्रमागत tep_त्रुटि_सं tep_filter_add_filter_str(काष्ठा tep_event_filter *filter,
					 स्थिर अक्षर *filter_str);

क्रमागत tep_त्रुटि_सं tep_filter_match(काष्ठा tep_event_filter *filter,
				काष्ठा tep_record *record);

पूर्णांक tep_filter_म_त्रुटि(काष्ठा tep_event_filter *filter, क्रमागत tep_त्रुटि_सं err,
			अक्षर *buf, माप_प्रकार buflen);

पूर्णांक tep_event_filtered(काष्ठा tep_event_filter *filter,
		       पूर्णांक event_id);

व्योम tep_filter_reset(काष्ठा tep_event_filter *filter);

व्योम tep_filter_मुक्त(काष्ठा tep_event_filter *filter);

अक्षर *tep_filter_make_string(काष्ठा tep_event_filter *filter, पूर्णांक event_id);

पूर्णांक tep_filter_हटाओ_event(काष्ठा tep_event_filter *filter,
			    पूर्णांक event_id);

पूर्णांक tep_filter_copy(काष्ठा tep_event_filter *dest, काष्ठा tep_event_filter *source);

पूर्णांक tep_filter_compare(काष्ठा tep_event_filter *filter1, काष्ठा tep_event_filter *filter2);

#पूर्ण_अगर /* _PARSE_EVENTS_H */
