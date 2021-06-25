<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_events_hist - trace event hist triggers
 *
 * Copyright (C) 2015 Tom Zanussi <tom.zanussi@linux.पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/security.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/rculist.h>
#समावेश <linux/tracefs.h>

/* क्रम gfp flag names */
#समावेश <linux/trace_events.h>
#समावेश <trace/events/mmflags.h>

#समावेश "tracing_map.h"
#समावेश "trace_synth.h"

#घोषणा ERRORS								\
	C(NONE,			"No error"),				\
	C(DUPLICATE_VAR,	"Variable already defined"),		\
	C(VAR_NOT_UNIQUE,	"Variable name not unique, need to use fully qualified name (subsys.event.var) for variable"), \
	C(TOO_MANY_VARS,	"Too many variables defined"),		\
	C(MALFORMED_ASSIGNMENT,	"Malformed assignment"),		\
	C(NAMED_MISMATCH,	"Named hist trigger doesn't match existing named trigger (includes variables)"), \
	C(TRIGGER_EEXIST,	"Hist trigger already exists"),		\
	C(TRIGGER_ENOENT_CLEAR,	"Can't clear or continue a nonexistent hist trigger"), \
	C(SET_CLOCK_FAIL,	"Couldn't set trace_clock"),		\
	C(BAD_FIELD_MODIFIER,	"Invalid field modifier"),		\
	C(TOO_MANY_SUBEXPR,	"Too many subexpressions (3 max)"),	\
	C(TIMESTAMP_MISMATCH,	"Timestamp units in expression don't match"), \
	C(TOO_MANY_FIELD_VARS,	"Too many field variables defined"),	\
	C(EVENT_खाता_NOT_FOUND,	"Event file not found"),		\
	C(HIST_NOT_FOUND,	"Matching event histogram not found"),	\
	C(HIST_CREATE_FAIL,	"Couldn't create histogram for field"),	\
	C(SYNTH_VAR_NOT_FOUND,	"Couldn't find synthetic variable"),	\
	C(SYNTH_EVENT_NOT_FOUND,"Couldn't find synthetic event"),	\
	C(SYNTH_TYPE_MISMATCH,	"Param type doesn't match synthetic event field type"), \
	C(SYNTH_COUNT_MISMATCH,	"Param count doesn't match synthetic event field count"), \
	C(FIELD_VAR_PARSE_FAIL,	"Couldn't parse field variable"),	\
	C(VAR_CREATE_FIND_FAIL,	"Couldn't create or find variable"),	\
	C(ONX_NOT_VAR,		"For onmax(x) or onchange(x), x must be a variable"), \
	C(ONX_VAR_NOT_FOUND,	"Couldn't find onmax or onchange variable"), \
	C(ONX_VAR_CREATE_FAIL,	"Couldn't create onmax or onchange variable"), \
	C(FIELD_VAR_CREATE_FAIL,"Couldn't create field variable"),	\
	C(TOO_MANY_PARAMS,	"Too many action params"),		\
	C(PARAM_NOT_FOUND,	"Couldn't find param"),			\
	C(INVALID_PARAM,	"Invalid action param"),		\
	C(ACTION_NOT_FOUND,	"No action found"),			\
	C(NO_SAVE_PARAMS,	"No params found for save()"),		\
	C(TOO_MANY_SAVE_ACTIONS,"Can't have more than one save() action per hist"), \
	C(ACTION_MISMATCH,	"Handler doesn't support action"),	\
	C(NO_CLOSING_PAREN,	"No closing paren found"),		\
	C(SUBSYS_NOT_FOUND,	"Missing subsystem"),			\
	C(INVALID_SUBSYS_EVENT,	"Invalid subsystem or event name"),	\
	C(INVALID_REF_KEY,	"Using variable references in keys not supported"), \
	C(VAR_NOT_FOUND,	"Couldn't find variable"),		\
	C(FIELD_NOT_FOUND,	"Couldn't find field"),			\
	C(EMPTY_ASSIGNMENT,	"Empty assignment"),			\
	C(INVALID_SORT_MODIFIER,"Invalid sort modifier"),		\
	C(EMPTY_SORT_FIELD,	"Empty sort field"),			\
	C(TOO_MANY_SORT_FIELDS,	"Too many sort fields (Max = 2)"),	\
	C(INVALID_SORT_FIELD,	"Sort field must be a key or a val"),

#अघोषित C
#घोषणा C(a, b)		HIST_ERR_##a

क्रमागत अणु ERRORS पूर्ण;

#अघोषित C
#घोषणा C(a, b)		b

अटल स्थिर अक्षर *err_text[] = अणु ERRORS पूर्ण;

काष्ठा hist_field;

प्रकार u64 (*hist_field_fn_t) (काष्ठा hist_field *field,
				काष्ठा tracing_map_elt *elt,
				काष्ठा trace_buffer *buffer,
				काष्ठा ring_buffer_event *rbe,
				व्योम *event);

#घोषणा HIST_FIELD_OPERANDS_MAX	2
#घोषणा HIST_FIELDS_MAX		(TRACING_MAP_FIELDS_MAX + TRACING_MAP_VARS_MAX)
#घोषणा HIST_ACTIONS_MAX	8

क्रमागत field_op_id अणु
	FIELD_OP_NONE,
	FIELD_OP_PLUS,
	FIELD_OP_MINUS,
	FIELD_OP_UNARY_MINUS,
पूर्ण;

/*
 * A hist_var (histogram variable) contains variable inक्रमmation क्रम
 * hist_fields having the HIST_FIELD_FL_VAR or HIST_FIELD_FL_VAR_REF
 * flag set.  A hist_var has a variable name e.g. ts0, and is
 * associated with a given histogram trigger, as specअगरied by
 * hist_data.  The hist_var idx is the unique index asचिन्हित to the
 * variable by the hist trigger's tracing_map.  The idx is what is
 * used to set a variable's value and, by a variable reference, to
 * retrieve it.
 */
काष्ठा hist_var अणु
	अक्षर				*name;
	काष्ठा hist_trigger_data	*hist_data;
	अचिन्हित पूर्णांक			idx;
पूर्ण;

काष्ठा hist_field अणु
	काष्ठा ftrace_event_field	*field;
	अचिन्हित दीर्घ			flags;
	hist_field_fn_t			fn;
	अचिन्हित पूर्णांक			ref;
	अचिन्हित पूर्णांक			size;
	अचिन्हित पूर्णांक			offset;
	अचिन्हित पूर्णांक                    is_चिन्हित;
	स्थिर अक्षर			*type;
	काष्ठा hist_field		*opeअक्रमs[HIST_FIELD_OPERANDS_MAX];
	काष्ठा hist_trigger_data	*hist_data;

	/*
	 * Variable fields contain variable-specअगरic info in var.
	 */
	काष्ठा hist_var			var;
	क्रमागत field_op_id		चालक;
	अक्षर				*प्रणाली;
	अक्षर				*event_name;

	/*
	 * The name field is used क्रम EXPR and VAR_REF fields.  VAR
	 * fields contain the variable name in var.name.
	 */
	अक्षर				*name;

	/*
	 * When a histogram trigger is hit, अगर it has any references
	 * to variables, the values of those variables are collected
	 * पूर्णांकo a var_ref_vals array by resolve_var_refs().  The
	 * current value of each variable is पढ़ो from the tracing_map
	 * using the hist field's hist_var.idx and entered पूर्णांकo the
	 * var_ref_idx entry i.e. var_ref_vals[var_ref_idx].
	 */
	अचिन्हित पूर्णांक			var_ref_idx;
	bool                            पढ़ो_once;

	अचिन्हित पूर्णांक			var_str_idx;
पूर्ण;

अटल u64 hist_field_none(काष्ठा hist_field *field,
			   काष्ठा tracing_map_elt *elt,
			   काष्ठा trace_buffer *buffer,
			   काष्ठा ring_buffer_event *rbe,
			   व्योम *event)
अणु
	वापस 0;
पूर्ण

अटल u64 hist_field_counter(काष्ठा hist_field *field,
			      काष्ठा tracing_map_elt *elt,
			      काष्ठा trace_buffer *buffer,
			      काष्ठा ring_buffer_event *rbe,
			      व्योम *event)
अणु
	वापस 1;
पूर्ण

अटल u64 hist_field_string(काष्ठा hist_field *hist_field,
			     काष्ठा tracing_map_elt *elt,
			     काष्ठा trace_buffer *buffer,
			     काष्ठा ring_buffer_event *rbe,
			     व्योम *event)
अणु
	अक्षर *addr = (अक्षर *)(event + hist_field->field->offset);

	वापस (u64)(अचिन्हित दीर्घ)addr;
पूर्ण

अटल u64 hist_field_dynstring(काष्ठा hist_field *hist_field,
				काष्ठा tracing_map_elt *elt,
				काष्ठा trace_buffer *buffer,
				काष्ठा ring_buffer_event *rbe,
				व्योम *event)
अणु
	u32 str_item = *(u32 *)(event + hist_field->field->offset);
	पूर्णांक str_loc = str_item & 0xffff;
	अक्षर *addr = (अक्षर *)(event + str_loc);

	वापस (u64)(अचिन्हित दीर्घ)addr;
पूर्ण

अटल u64 hist_field_pstring(काष्ठा hist_field *hist_field,
			      काष्ठा tracing_map_elt *elt,
			      काष्ठा trace_buffer *buffer,
			      काष्ठा ring_buffer_event *rbe,
			      व्योम *event)
अणु
	अक्षर **addr = (अक्षर **)(event + hist_field->field->offset);

	वापस (u64)(अचिन्हित दीर्घ)*addr;
पूर्ण

अटल u64 hist_field_log2(काष्ठा hist_field *hist_field,
			   काष्ठा tracing_map_elt *elt,
			   काष्ठा trace_buffer *buffer,
			   काष्ठा ring_buffer_event *rbe,
			   व्योम *event)
अणु
	काष्ठा hist_field *opeअक्रम = hist_field->opeअक्रमs[0];

	u64 val = opeअक्रम->fn(opeअक्रम, elt, buffer, rbe, event);

	वापस (u64) ilog2(roundup_घात_of_two(val));
पूर्ण

अटल u64 hist_field_plus(काष्ठा hist_field *hist_field,
			   काष्ठा tracing_map_elt *elt,
			   काष्ठा trace_buffer *buffer,
			   काष्ठा ring_buffer_event *rbe,
			   व्योम *event)
अणु
	काष्ठा hist_field *opeअक्रम1 = hist_field->opeअक्रमs[0];
	काष्ठा hist_field *opeअक्रम2 = hist_field->opeअक्रमs[1];

	u64 val1 = opeअक्रम1->fn(opeअक्रम1, elt, buffer, rbe, event);
	u64 val2 = opeअक्रम2->fn(opeअक्रम2, elt, buffer, rbe, event);

	वापस val1 + val2;
पूर्ण

अटल u64 hist_field_minus(काष्ठा hist_field *hist_field,
			    काष्ठा tracing_map_elt *elt,
			    काष्ठा trace_buffer *buffer,
			    काष्ठा ring_buffer_event *rbe,
			    व्योम *event)
अणु
	काष्ठा hist_field *opeअक्रम1 = hist_field->opeअक्रमs[0];
	काष्ठा hist_field *opeअक्रम2 = hist_field->opeअक्रमs[1];

	u64 val1 = opeअक्रम1->fn(opeअक्रम1, elt, buffer, rbe, event);
	u64 val2 = opeअक्रम2->fn(opeअक्रम2, elt, buffer, rbe, event);

	वापस val1 - val2;
पूर्ण

अटल u64 hist_field_unary_minus(काष्ठा hist_field *hist_field,
				  काष्ठा tracing_map_elt *elt,
				  काष्ठा trace_buffer *buffer,
				  काष्ठा ring_buffer_event *rbe,
				  व्योम *event)
अणु
	काष्ठा hist_field *opeअक्रम = hist_field->opeअक्रमs[0];

	s64 sval = (s64)opeअक्रम->fn(opeअक्रम, elt, buffer, rbe, event);
	u64 val = (u64)-sval;

	वापस val;
पूर्ण

#घोषणा DEFINE_HIST_FIELD_FN(type)					\
	अटल u64 hist_field_##type(काष्ठा hist_field *hist_field,	\
				     काष्ठा tracing_map_elt *elt,	\
				     काष्ठा trace_buffer *buffer,	\
				     काष्ठा ring_buffer_event *rbe,	\
				     व्योम *event)			\
अणु									\
	type *addr = (type *)(event + hist_field->field->offset);	\
									\
	वापस (u64)(अचिन्हित दीर्घ)*addr;				\
पूर्ण

DEFINE_HIST_FIELD_FN(s64);
DEFINE_HIST_FIELD_FN(u64);
DEFINE_HIST_FIELD_FN(s32);
DEFINE_HIST_FIELD_FN(u32);
DEFINE_HIST_FIELD_FN(s16);
DEFINE_HIST_FIELD_FN(u16);
DEFINE_HIST_FIELD_FN(s8);
DEFINE_HIST_FIELD_FN(u8);

#घोषणा क्रम_each_hist_field(i, hist_data)	\
	क्रम ((i) = 0; (i) < (hist_data)->n_fields; (i)++)

#घोषणा क्रम_each_hist_val_field(i, hist_data)	\
	क्रम ((i) = 0; (i) < (hist_data)->n_vals; (i)++)

#घोषणा क्रम_each_hist_key_field(i, hist_data)	\
	क्रम ((i) = (hist_data)->n_vals; (i) < (hist_data)->n_fields; (i)++)

#घोषणा HIST_STACKTRACE_DEPTH	16
#घोषणा HIST_STACKTRACE_SIZE	(HIST_STACKTRACE_DEPTH * माप(अचिन्हित दीर्घ))
#घोषणा HIST_STACKTRACE_SKIP	5

#घोषणा HITCOUNT_IDX		0
#घोषणा HIST_KEY_SIZE_MAX	(MAX_FILTER_STR_VAL + HIST_STACKTRACE_SIZE)

क्रमागत hist_field_flags अणु
	HIST_FIELD_FL_HITCOUNT		= 1 << 0,
	HIST_FIELD_FL_KEY		= 1 << 1,
	HIST_FIELD_FL_STRING		= 1 << 2,
	HIST_FIELD_FL_HEX		= 1 << 3,
	HIST_FIELD_FL_SYM		= 1 << 4,
	HIST_FIELD_FL_SYM_OFFSET	= 1 << 5,
	HIST_FIELD_FL_EXECNAME		= 1 << 6,
	HIST_FIELD_FL_SYSCALL		= 1 << 7,
	HIST_FIELD_FL_STACKTRACE	= 1 << 8,
	HIST_FIELD_FL_LOG2		= 1 << 9,
	HIST_FIELD_FL_TIMESTAMP		= 1 << 10,
	HIST_FIELD_FL_TIMESTAMP_USECS	= 1 << 11,
	HIST_FIELD_FL_VAR		= 1 << 12,
	HIST_FIELD_FL_EXPR		= 1 << 13,
	HIST_FIELD_FL_VAR_REF		= 1 << 14,
	HIST_FIELD_FL_CPU		= 1 << 15,
	HIST_FIELD_FL_ALIAS		= 1 << 16,
पूर्ण;

काष्ठा var_defs अणु
	अचिन्हित पूर्णांक	n_vars;
	अक्षर		*name[TRACING_MAP_VARS_MAX];
	अक्षर		*expr[TRACING_MAP_VARS_MAX];
पूर्ण;

काष्ठा hist_trigger_attrs अणु
	अक्षर		*keys_str;
	अक्षर		*vals_str;
	अक्षर		*sort_key_str;
	अक्षर		*name;
	अक्षर		*घड़ी;
	bool		छोड़ो;
	bool		cont;
	bool		clear;
	bool		ts_in_usecs;
	अचिन्हित पूर्णांक	map_bits;

	अक्षर		*assignment_str[TRACING_MAP_VARS_MAX];
	अचिन्हित पूर्णांक	n_assignments;

	अक्षर		*action_str[HIST_ACTIONS_MAX];
	अचिन्हित पूर्णांक	n_actions;

	काष्ठा var_defs	var_defs;
पूर्ण;

काष्ठा field_var अणु
	काष्ठा hist_field	*var;
	काष्ठा hist_field	*val;
पूर्ण;

काष्ठा field_var_hist अणु
	काष्ठा hist_trigger_data	*hist_data;
	अक्षर				*cmd;
पूर्ण;

काष्ठा hist_trigger_data अणु
	काष्ठा hist_field               *fields[HIST_FIELDS_MAX];
	अचिन्हित पूर्णांक			n_vals;
	अचिन्हित पूर्णांक			n_keys;
	अचिन्हित पूर्णांक			n_fields;
	अचिन्हित पूर्णांक			n_vars;
	अचिन्हित पूर्णांक			n_var_str;
	अचिन्हित पूर्णांक			key_size;
	काष्ठा tracing_map_sort_key	sort_keys[TRACING_MAP_SORT_KEYS_MAX];
	अचिन्हित पूर्णांक			n_sort_keys;
	काष्ठा trace_event_file		*event_file;
	काष्ठा hist_trigger_attrs	*attrs;
	काष्ठा tracing_map		*map;
	bool				enable_बारtamps;
	bool				हटाओ;
	काष्ठा hist_field               *var_refs[TRACING_MAP_VARS_MAX];
	अचिन्हित पूर्णांक			n_var_refs;

	काष्ठा action_data		*actions[HIST_ACTIONS_MAX];
	अचिन्हित पूर्णांक			n_actions;

	काष्ठा field_var		*field_vars[SYNTH_FIELDS_MAX];
	अचिन्हित पूर्णांक			n_field_vars;
	अचिन्हित पूर्णांक			n_field_var_str;
	काष्ठा field_var_hist		*field_var_hists[SYNTH_FIELDS_MAX];
	अचिन्हित पूर्णांक			n_field_var_hists;

	काष्ठा field_var		*save_vars[SYNTH_FIELDS_MAX];
	अचिन्हित पूर्णांक			n_save_vars;
	अचिन्हित पूर्णांक			n_save_var_str;
पूर्ण;

काष्ठा action_data;

प्रकार व्योम (*action_fn_t) (काष्ठा hist_trigger_data *hist_data,
			     काष्ठा tracing_map_elt *elt,
			     काष्ठा trace_buffer *buffer, व्योम *rec,
			     काष्ठा ring_buffer_event *rbe, व्योम *key,
			     काष्ठा action_data *data, u64 *var_ref_vals);

प्रकार bool (*check_track_val_fn_t) (u64 track_val, u64 var_val);

क्रमागत handler_id अणु
	HANDLER_ONMATCH = 1,
	HANDLER_ONMAX,
	HANDLER_ONCHANGE,
पूर्ण;

क्रमागत action_id अणु
	ACTION_SAVE = 1,
	ACTION_TRACE,
	ACTION_SNAPSHOT,
पूर्ण;

काष्ठा action_data अणु
	क्रमागत handler_id		handler;
	क्रमागत action_id		action;
	अक्षर			*action_name;
	action_fn_t		fn;

	अचिन्हित पूर्णांक		n_params;
	अक्षर			*params[SYNTH_FIELDS_MAX];

	/*
	 * When a histogram trigger is hit, the values of any
	 * references to variables, including variables being passed
	 * as parameters to synthetic events, are collected पूर्णांकo a
	 * var_ref_vals array.  This var_ref_idx array is an array of
	 * indices पूर्णांकo the var_ref_vals array, one क्रम each synthetic
	 * event param, and is passed to the synthetic event
	 * invocation.
	 */
	अचिन्हित पूर्णांक		var_ref_idx[TRACING_MAP_VARS_MAX];
	काष्ठा synth_event	*synth_event;
	bool			use_trace_keyword;
	अक्षर			*synth_event_name;

	जोड़ अणु
		काष्ठा अणु
			अक्षर			*event;
			अक्षर			*event_प्रणाली;
		पूर्ण match_data;

		काष्ठा अणु
			/*
			 * var_str contains the $-unstripped variable
			 * name referenced by var_ref, and used when
			 * prपूर्णांकing the action.  Because var_ref
			 * creation is deferred to create_actions(),
			 * we need a per-action way to save it until
			 * then, thus var_str.
			 */
			अक्षर			*var_str;

			/*
			 * var_ref refers to the variable being
			 * tracked e.g onmax($var).
			 */
			काष्ठा hist_field	*var_ref;

			/*
			 * track_var contains the 'invisible' tracking
			 * variable created to keep the current
			 * e.g. max value.
			 */
			काष्ठा hist_field	*track_var;

			check_track_val_fn_t	check_val;
			action_fn_t		save_data;
		पूर्ण track_data;
	पूर्ण;
पूर्ण;

काष्ठा track_data अणु
	u64				track_val;
	bool				updated;

	अचिन्हित पूर्णांक			key_len;
	व्योम				*key;
	काष्ठा tracing_map_elt		elt;

	काष्ठा action_data		*action_data;
	काष्ठा hist_trigger_data	*hist_data;
पूर्ण;

काष्ठा hist_elt_data अणु
	अक्षर *comm;
	u64 *var_ref_vals;
	अक्षर *field_var_str[SYNTH_FIELDS_MAX];
पूर्ण;

काष्ठा snapshot_context अणु
	काष्ठा tracing_map_elt	*elt;
	व्योम			*key;
पूर्ण;

अटल व्योम track_data_मुक्त(काष्ठा track_data *track_data)
अणु
	काष्ठा hist_elt_data *elt_data;

	अगर (!track_data)
		वापस;

	kमुक्त(track_data->key);

	elt_data = track_data->elt.निजी_data;
	अगर (elt_data) अणु
		kमुक्त(elt_data->comm);
		kमुक्त(elt_data);
	पूर्ण

	kमुक्त(track_data);
पूर्ण

अटल काष्ठा track_data *track_data_alloc(अचिन्हित पूर्णांक key_len,
					   काष्ठा action_data *action_data,
					   काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा track_data *data = kzalloc(माप(*data), GFP_KERNEL);
	काष्ठा hist_elt_data *elt_data;

	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	data->key = kzalloc(key_len, GFP_KERNEL);
	अगर (!data->key) अणु
		track_data_मुक्त(data);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	data->key_len = key_len;
	data->action_data = action_data;
	data->hist_data = hist_data;

	elt_data = kzalloc(माप(*elt_data), GFP_KERNEL);
	अगर (!elt_data) अणु
		track_data_मुक्त(data);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	data->elt.निजी_data = elt_data;

	elt_data->comm = kzalloc(TASK_COMM_LEN, GFP_KERNEL);
	अगर (!elt_data->comm) अणु
		track_data_मुक्त(data);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस data;
पूर्ण

अटल अक्षर last_cmd[MAX_FILTER_STR_VAL];
अटल अक्षर last_cmd_loc[MAX_FILTER_STR_VAL];

अटल पूर्णांक errpos(अक्षर *str)
अणु
	वापस err_pos(last_cmd, str);
पूर्ण

अटल व्योम last_cmd_set(काष्ठा trace_event_file *file, अक्षर *str)
अणु
	स्थिर अक्षर *प्रणाली = शून्य, *name = शून्य;
	काष्ठा trace_event_call *call;

	अगर (!str)
		वापस;

	म_नकल(last_cmd, "hist:");
	म_जोड़न(last_cmd, str, MAX_FILTER_STR_VAL - 1 - माप("hist:"));

	अगर (file) अणु
		call = file->event_call;
		प्रणाली = call->class->प्रणाली;
		अगर (प्रणाली) अणु
			name = trace_event_name(call);
			अगर (!name)
				प्रणाली = शून्य;
		पूर्ण
	पूर्ण

	अगर (प्रणाली)
		snम_लिखो(last_cmd_loc, MAX_FILTER_STR_VAL, "hist:%s:%s", प्रणाली, name);
पूर्ण

अटल व्योम hist_err(काष्ठा trace_array *tr, u8 err_type, u8 err_pos)
अणु
	tracing_log_err(tr, last_cmd_loc, last_cmd, err_text,
			err_type, err_pos);
पूर्ण

अटल व्योम hist_err_clear(व्योम)
अणु
	last_cmd[0] = '\0';
	last_cmd_loc[0] = '\0';
पूर्ण

प्रकार व्योम (*synth_probe_func_t) (व्योम *__data, u64 *var_ref_vals,
				    अचिन्हित पूर्णांक *var_ref_idx);

अटल अंतरभूत व्योम trace_synth(काष्ठा synth_event *event, u64 *var_ref_vals,
			       अचिन्हित पूर्णांक *var_ref_idx)
अणु
	काष्ठा tracepoपूर्णांक *tp = event->tp;

	अगर (unlikely(atomic_पढ़ो(&tp->key.enabled) > 0)) अणु
		काष्ठा tracepoपूर्णांक_func *probe_func_ptr;
		synth_probe_func_t probe_func;
		व्योम *__data;

		अगर (!(cpu_online(raw_smp_processor_id())))
			वापस;

		probe_func_ptr = rcu_dereference_sched((tp)->funcs);
		अगर (probe_func_ptr) अणु
			करो अणु
				probe_func = probe_func_ptr->func;
				__data = probe_func_ptr->data;
				probe_func(__data, var_ref_vals, var_ref_idx);
			पूर्ण जबतक ((++probe_func_ptr)->func);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम action_trace(काष्ठा hist_trigger_data *hist_data,
			 काष्ठा tracing_map_elt *elt,
			 काष्ठा trace_buffer *buffer, व्योम *rec,
			 काष्ठा ring_buffer_event *rbe, व्योम *key,
			 काष्ठा action_data *data, u64 *var_ref_vals)
अणु
	काष्ठा synth_event *event = data->synth_event;

	trace_synth(event, var_ref_vals, data->var_ref_idx);
पूर्ण

काष्ठा hist_var_data अणु
	काष्ठा list_head list;
	काष्ठा hist_trigger_data *hist_data;
पूर्ण;

अटल u64 hist_field_बारtamp(काष्ठा hist_field *hist_field,
				काष्ठा tracing_map_elt *elt,
				काष्ठा trace_buffer *buffer,
				काष्ठा ring_buffer_event *rbe,
				व्योम *event)
अणु
	काष्ठा hist_trigger_data *hist_data = hist_field->hist_data;
	काष्ठा trace_array *tr = hist_data->event_file->tr;

	u64 ts = ring_buffer_event_समय_stamp(buffer, rbe);

	अगर (hist_data->attrs->ts_in_usecs && trace_घड़ी_in_ns(tr))
		ts = ns2usecs(ts);

	वापस ts;
पूर्ण

अटल u64 hist_field_cpu(काष्ठा hist_field *hist_field,
			  काष्ठा tracing_map_elt *elt,
			  काष्ठा trace_buffer *buffer,
			  काष्ठा ring_buffer_event *rbe,
			  व्योम *event)
अणु
	पूर्णांक cpu = smp_processor_id();

	वापस cpu;
पूर्ण

/**
 * check_field_क्रम_var_ref - Check अगर a VAR_REF field references a variable
 * @hist_field: The VAR_REF field to check
 * @var_data: The hist trigger that owns the variable
 * @var_idx: The trigger variable identअगरier
 *
 * Check the given VAR_REF field to see whether or not it references
 * the given variable associated with the given trigger.
 *
 * Return: The VAR_REF field अगर it करोes reference the variable, शून्य अगर not
 */
अटल काष्ठा hist_field *
check_field_क्रम_var_ref(काष्ठा hist_field *hist_field,
			काष्ठा hist_trigger_data *var_data,
			अचिन्हित पूर्णांक var_idx)
अणु
	WARN_ON(!(hist_field && hist_field->flags & HIST_FIELD_FL_VAR_REF));

	अगर (hist_field && hist_field->var.idx == var_idx &&
	    hist_field->var.hist_data == var_data)
		वापस hist_field;

	वापस शून्य;
पूर्ण

/**
 * find_var_ref - Check अगर a trigger has a reference to a trigger variable
 * @hist_data: The hist trigger that might have a reference to the variable
 * @var_data: The hist trigger that owns the variable
 * @var_idx: The trigger variable identअगरier
 *
 * Check the list of var_refs[] on the first hist trigger to see
 * whether any of them are references to the variable on the second
 * trigger.
 *
 * Return: The VAR_REF field referencing the variable अगर so, शून्य अगर not
 */
अटल काष्ठा hist_field *find_var_ref(काष्ठा hist_trigger_data *hist_data,
				       काष्ठा hist_trigger_data *var_data,
				       अचिन्हित पूर्णांक var_idx)
अणु
	काष्ठा hist_field *hist_field;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_var_refs; i++) अणु
		hist_field = hist_data->var_refs[i];
		अगर (check_field_क्रम_var_ref(hist_field, var_data, var_idx))
			वापस hist_field;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * find_any_var_ref - Check अगर there is a reference to a given trigger variable
 * @hist_data: The hist trigger
 * @var_idx: The trigger variable identअगरier
 *
 * Check to see whether the given variable is currently referenced by
 * any other trigger.
 *
 * The trigger the variable is defined on is explicitly excluded - the
 * assumption being that a self-reference करोesn't prevent a trigger
 * from being हटाओd.
 *
 * Return: The VAR_REF field referencing the variable अगर so, शून्य अगर not
 */
अटल काष्ठा hist_field *find_any_var_ref(काष्ठा hist_trigger_data *hist_data,
					   अचिन्हित पूर्णांक var_idx)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_field *found = शून्य;
	काष्ठा hist_var_data *var_data;

	list_क्रम_each_entry(var_data, &tr->hist_vars, list) अणु
		अगर (var_data->hist_data == hist_data)
			जारी;
		found = find_var_ref(var_data->hist_data, hist_data, var_idx);
		अगर (found)
			अवरोध;
	पूर्ण

	वापस found;
पूर्ण

/**
 * check_var_refs - Check अगर there is a reference to any of trigger's variables
 * @hist_data: The hist trigger
 *
 * A trigger can define one or more variables.  If any one of them is
 * currently referenced by any other trigger, this function will
 * determine that.

 * Typically used to determine whether or not a trigger can be हटाओd
 * - अगर there are any references to a trigger's variables, it cannot.
 *
 * Return: True अगर there is a reference to any of trigger's variables
 */
अटल bool check_var_refs(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा hist_field *field;
	bool found = false;
	पूर्णांक i;

	क्रम_each_hist_field(i, hist_data) अणु
		field = hist_data->fields[i];
		अगर (field && field->flags & HIST_FIELD_FL_VAR) अणु
			अगर (find_any_var_ref(hist_data, field->var.idx)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा hist_var_data *find_hist_vars(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_var_data *var_data, *found = शून्य;

	list_क्रम_each_entry(var_data, &tr->hist_vars, list) अणु
		अगर (var_data->hist_data == hist_data) अणु
			found = var_data;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल bool field_has_hist_vars(काष्ठा hist_field *hist_field,
				अचिन्हित पूर्णांक level)
अणु
	पूर्णांक i;

	अगर (level > 3)
		वापस false;

	अगर (!hist_field)
		वापस false;

	अगर (hist_field->flags & HIST_FIELD_FL_VAR ||
	    hist_field->flags & HIST_FIELD_FL_VAR_REF)
		वापस true;

	क्रम (i = 0; i < HIST_FIELD_OPERANDS_MAX; i++) अणु
		काष्ठा hist_field *opeअक्रम;

		opeअक्रम = hist_field->opeअक्रमs[i];
		अगर (field_has_hist_vars(opeअक्रम, level + 1))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool has_hist_vars(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा hist_field *hist_field;
	पूर्णांक i;

	क्रम_each_hist_field(i, hist_data) अणु
		hist_field = hist_data->fields[i];
		अगर (field_has_hist_vars(hist_field, 0))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक save_hist_vars(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_var_data *var_data;

	var_data = find_hist_vars(hist_data);
	अगर (var_data)
		वापस 0;

	अगर (tracing_check_खोलो_get_tr(tr))
		वापस -ENODEV;

	var_data = kzalloc(माप(*var_data), GFP_KERNEL);
	अगर (!var_data) अणु
		trace_array_put(tr);
		वापस -ENOMEM;
	पूर्ण

	var_data->hist_data = hist_data;
	list_add(&var_data->list, &tr->hist_vars);

	वापस 0;
पूर्ण

अटल व्योम हटाओ_hist_vars(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_var_data *var_data;

	var_data = find_hist_vars(hist_data);
	अगर (!var_data)
		वापस;

	अगर (WARN_ON(check_var_refs(hist_data)))
		वापस;

	list_del(&var_data->list);

	kमुक्त(var_data);

	trace_array_put(tr);
पूर्ण

अटल काष्ठा hist_field *find_var_field(काष्ठा hist_trigger_data *hist_data,
					 स्थिर अक्षर *var_name)
अणु
	काष्ठा hist_field *hist_field, *found = शून्य;
	पूर्णांक i;

	क्रम_each_hist_field(i, hist_data) अणु
		hist_field = hist_data->fields[i];
		अगर (hist_field && hist_field->flags & HIST_FIELD_FL_VAR &&
		    म_भेद(hist_field->var.name, var_name) == 0) अणु
			found = hist_field;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा hist_field *find_var(काष्ठा hist_trigger_data *hist_data,
				   काष्ठा trace_event_file *file,
				   स्थिर अक्षर *var_name)
अणु
	काष्ठा hist_trigger_data *test_data;
	काष्ठा event_trigger_data *test;
	काष्ठा hist_field *hist_field;

	lockdep_निश्चित_held(&event_mutex);

	hist_field = find_var_field(hist_data, var_name);
	अगर (hist_field)
		वापस hist_field;

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			test_data = test->निजी_data;
			hist_field = find_var_field(test_data, var_name);
			अगर (hist_field)
				वापस hist_field;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा trace_event_file *find_var_file(काष्ठा trace_array *tr,
					      अक्षर *प्रणाली,
					      अक्षर *event_name,
					      अक्षर *var_name)
अणु
	काष्ठा hist_trigger_data *var_hist_data;
	काष्ठा hist_var_data *var_data;
	काष्ठा trace_event_file *file, *found = शून्य;

	अगर (प्रणाली)
		वापस find_event_file(tr, प्रणाली, event_name);

	list_क्रम_each_entry(var_data, &tr->hist_vars, list) अणु
		var_hist_data = var_data->hist_data;
		file = var_hist_data->event_file;
		अगर (file == found)
			जारी;

		अगर (find_var_field(var_hist_data, var_name)) अणु
			अगर (found) अणु
				hist_err(tr, HIST_ERR_VAR_NOT_UNIQUE, errpos(var_name));
				वापस शून्य;
			पूर्ण

			found = file;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा hist_field *find_file_var(काष्ठा trace_event_file *file,
					स्थिर अक्षर *var_name)
अणु
	काष्ठा hist_trigger_data *test_data;
	काष्ठा event_trigger_data *test;
	काष्ठा hist_field *hist_field;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			test_data = test->निजी_data;
			hist_field = find_var_field(test_data, var_name);
			अगर (hist_field)
				वापस hist_field;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hist_field *
find_match_var(काष्ठा hist_trigger_data *hist_data, अक्षर *var_name)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_field *hist_field, *found = शून्य;
	काष्ठा trace_event_file *file;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		काष्ठा action_data *data = hist_data->actions[i];

		अगर (data->handler == HANDLER_ONMATCH) अणु
			अक्षर *प्रणाली = data->match_data.event_प्रणाली;
			अक्षर *event_name = data->match_data.event;

			file = find_var_file(tr, प्रणाली, event_name, var_name);
			अगर (!file)
				जारी;
			hist_field = find_file_var(file, var_name);
			अगर (hist_field) अणु
				अगर (found) अणु
					hist_err(tr, HIST_ERR_VAR_NOT_UNIQUE,
						 errpos(var_name));
					वापस ERR_PTR(-EINVAL);
				पूर्ण

				found = hist_field;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

अटल काष्ठा hist_field *find_event_var(काष्ठा hist_trigger_data *hist_data,
					 अक्षर *प्रणाली,
					 अक्षर *event_name,
					 अक्षर *var_name)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_field *hist_field = शून्य;
	काष्ठा trace_event_file *file;

	अगर (!प्रणाली || !event_name) अणु
		hist_field = find_match_var(hist_data, var_name);
		अगर (IS_ERR(hist_field))
			वापस शून्य;
		अगर (hist_field)
			वापस hist_field;
	पूर्ण

	file = find_var_file(tr, प्रणाली, event_name, var_name);
	अगर (!file)
		वापस शून्य;

	hist_field = find_file_var(file, var_name);

	वापस hist_field;
पूर्ण

अटल u64 hist_field_var_ref(काष्ठा hist_field *hist_field,
			      काष्ठा tracing_map_elt *elt,
			      काष्ठा trace_buffer *buffer,
			      काष्ठा ring_buffer_event *rbe,
			      व्योम *event)
अणु
	काष्ठा hist_elt_data *elt_data;
	u64 var_val = 0;

	अगर (WARN_ON_ONCE(!elt))
		वापस var_val;

	elt_data = elt->निजी_data;
	var_val = elt_data->var_ref_vals[hist_field->var_ref_idx];

	वापस var_val;
पूर्ण

अटल bool resolve_var_refs(काष्ठा hist_trigger_data *hist_data, व्योम *key,
			     u64 *var_ref_vals, bool self)
अणु
	काष्ठा hist_trigger_data *var_data;
	काष्ठा tracing_map_elt *var_elt;
	काष्ठा hist_field *hist_field;
	अचिन्हित पूर्णांक i, var_idx;
	bool resolved = true;
	u64 var_val = 0;

	क्रम (i = 0; i < hist_data->n_var_refs; i++) अणु
		hist_field = hist_data->var_refs[i];
		var_idx = hist_field->var.idx;
		var_data = hist_field->var.hist_data;

		अगर (var_data == शून्य) अणु
			resolved = false;
			अवरोध;
		पूर्ण

		अगर ((self && var_data != hist_data) ||
		    (!self && var_data == hist_data))
			जारी;

		var_elt = tracing_map_lookup(var_data->map, key);
		अगर (!var_elt) अणु
			resolved = false;
			अवरोध;
		पूर्ण

		अगर (!tracing_map_var_set(var_elt, var_idx)) अणु
			resolved = false;
			अवरोध;
		पूर्ण

		अगर (self || !hist_field->पढ़ो_once)
			var_val = tracing_map_पढ़ो_var(var_elt, var_idx);
		अन्यथा
			var_val = tracing_map_पढ़ो_var_once(var_elt, var_idx);

		var_ref_vals[i] = var_val;
	पूर्ण

	वापस resolved;
पूर्ण

अटल स्थिर अक्षर *hist_field_name(काष्ठा hist_field *field,
				   अचिन्हित पूर्णांक level)
अणु
	स्थिर अक्षर *field_name = "";

	अगर (level > 1)
		वापस field_name;

	अगर (field->field)
		field_name = field->field->name;
	अन्यथा अगर (field->flags & HIST_FIELD_FL_LOG2 ||
		 field->flags & HIST_FIELD_FL_ALIAS)
		field_name = hist_field_name(field->opeअक्रमs[0], ++level);
	अन्यथा अगर (field->flags & HIST_FIELD_FL_CPU)
		field_name = "cpu";
	अन्यथा अगर (field->flags & HIST_FIELD_FL_EXPR ||
		 field->flags & HIST_FIELD_FL_VAR_REF) अणु
		अगर (field->प्रणाली) अणु
			अटल अक्षर full_name[MAX_FILTER_STR_VAL];

			म_जोड़ो(full_name, field->प्रणाली);
			म_जोड़ो(full_name, ".");
			म_जोड़ो(full_name, field->event_name);
			म_जोड़ो(full_name, ".");
			म_जोड़ो(full_name, field->name);
			field_name = full_name;
		पूर्ण अन्यथा
			field_name = field->name;
	पूर्ण अन्यथा अगर (field->flags & HIST_FIELD_FL_TIMESTAMP)
		field_name = "common_timestamp";

	अगर (field_name == शून्य)
		field_name = "";

	वापस field_name;
पूर्ण

अटल hist_field_fn_t select_value_fn(पूर्णांक field_size, पूर्णांक field_is_चिन्हित)
अणु
	hist_field_fn_t fn = शून्य;

	चयन (field_size) अणु
	हाल 8:
		अगर (field_is_चिन्हित)
			fn = hist_field_s64;
		अन्यथा
			fn = hist_field_u64;
		अवरोध;
	हाल 4:
		अगर (field_is_चिन्हित)
			fn = hist_field_s32;
		अन्यथा
			fn = hist_field_u32;
		अवरोध;
	हाल 2:
		अगर (field_is_चिन्हित)
			fn = hist_field_s16;
		अन्यथा
			fn = hist_field_u16;
		अवरोध;
	हाल 1:
		अगर (field_is_चिन्हित)
			fn = hist_field_s8;
		अन्यथा
			fn = hist_field_u8;
		अवरोध;
	पूर्ण

	वापस fn;
पूर्ण

अटल पूर्णांक parse_map_size(अक्षर *str)
अणु
	अचिन्हित दीर्घ size, map_bits;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(str, 0, &size);
	अगर (ret)
		जाओ out;

	map_bits = ilog2(roundup_घात_of_two(size));
	अगर (map_bits < TRACING_MAP_BITS_MIN ||
	    map_bits > TRACING_MAP_BITS_MAX)
		ret = -EINVAL;
	अन्यथा
		ret = map_bits;
 out:
	वापस ret;
पूर्ण

अटल व्योम destroy_hist_trigger_attrs(काष्ठा hist_trigger_attrs *attrs)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!attrs)
		वापस;

	क्रम (i = 0; i < attrs->n_assignments; i++)
		kमुक्त(attrs->assignment_str[i]);

	क्रम (i = 0; i < attrs->n_actions; i++)
		kमुक्त(attrs->action_str[i]);

	kमुक्त(attrs->name);
	kमुक्त(attrs->sort_key_str);
	kमुक्त(attrs->keys_str);
	kमुक्त(attrs->vals_str);
	kमुक्त(attrs->घड़ी);
	kमुक्त(attrs);
पूर्ण

अटल पूर्णांक parse_action(अक्षर *str, काष्ठा hist_trigger_attrs *attrs)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (attrs->n_actions >= HIST_ACTIONS_MAX)
		वापस ret;

	अगर ((str_has_prefix(str, "onmatch(")) ||
	    (str_has_prefix(str, "onmax(")) ||
	    (str_has_prefix(str, "onchange("))) अणु
		attrs->action_str[attrs->n_actions] = kstrdup(str, GFP_KERNEL);
		अगर (!attrs->action_str[attrs->n_actions]) अणु
			ret = -ENOMEM;
			वापस ret;
		पूर्ण
		attrs->n_actions++;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक parse_assignment(काष्ठा trace_array *tr,
			    अक्षर *str, काष्ठा hist_trigger_attrs *attrs)
अणु
	पूर्णांक len, ret = 0;

	अगर ((len = str_has_prefix(str, "key=")) ||
	    (len = str_has_prefix(str, "keys="))) अणु
		attrs->keys_str = kstrdup(str + len, GFP_KERNEL);
		अगर (!attrs->keys_str) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((len = str_has_prefix(str, "val=")) ||
		   (len = str_has_prefix(str, "vals=")) ||
		   (len = str_has_prefix(str, "values="))) अणु
		attrs->vals_str = kstrdup(str + len, GFP_KERNEL);
		अगर (!attrs->vals_str) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((len = str_has_prefix(str, "sort="))) अणु
		attrs->sort_key_str = kstrdup(str + len, GFP_KERNEL);
		अगर (!attrs->sort_key_str) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (str_has_prefix(str, "name=")) अणु
		attrs->name = kstrdup(str, GFP_KERNEL);
		अगर (!attrs->name) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((len = str_has_prefix(str, "clock="))) अणु
		str += len;

		str = म_मालाip(str);
		attrs->घड़ी = kstrdup(str, GFP_KERNEL);
		अगर (!attrs->घड़ी) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((len = str_has_prefix(str, "size="))) अणु
		पूर्णांक map_bits = parse_map_size(str + len);

		अगर (map_bits < 0) अणु
			ret = map_bits;
			जाओ out;
		पूर्ण
		attrs->map_bits = map_bits;
	पूर्ण अन्यथा अणु
		अक्षर *assignment;

		अगर (attrs->n_assignments == TRACING_MAP_VARS_MAX) अणु
			hist_err(tr, HIST_ERR_TOO_MANY_VARS, errpos(str));
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		assignment = kstrdup(str, GFP_KERNEL);
		अगर (!assignment) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		attrs->assignment_str[attrs->n_assignments++] = assignment;
	पूर्ण
 out:
	वापस ret;
पूर्ण

अटल काष्ठा hist_trigger_attrs *
parse_hist_trigger_attrs(काष्ठा trace_array *tr, अक्षर *trigger_str)
अणु
	काष्ठा hist_trigger_attrs *attrs;
	पूर्णांक ret = 0;

	attrs = kzalloc(माप(*attrs), GFP_KERNEL);
	अगर (!attrs)
		वापस ERR_PTR(-ENOMEM);

	जबतक (trigger_str) अणु
		अक्षर *str = strsep(&trigger_str, ":");
		अक्षर *rhs;

		rhs = म_अक्षर(str, '=');
		अगर (rhs) अणु
			अगर (!म_माप(++rhs)) अणु
				ret = -EINVAL;
				hist_err(tr, HIST_ERR_EMPTY_ASSIGNMENT, errpos(str));
				जाओ मुक्त;
			पूर्ण
			ret = parse_assignment(tr, str, attrs);
			अगर (ret)
				जाओ मुक्त;
		पूर्ण अन्यथा अगर (म_भेद(str, "pause") == 0)
			attrs->छोड़ो = true;
		अन्यथा अगर ((म_भेद(str, "cont") == 0) ||
			 (म_भेद(str, "continue") == 0))
			attrs->cont = true;
		अन्यथा अगर (म_भेद(str, "clear") == 0)
			attrs->clear = true;
		अन्यथा अणु
			ret = parse_action(str, attrs);
			अगर (ret)
				जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर (!attrs->keys_str) अणु
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	अगर (!attrs->घड़ी) अणु
		attrs->घड़ी = kstrdup("global", GFP_KERNEL);
		अगर (!attrs->घड़ी) अणु
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	वापस attrs;
 मुक्त:
	destroy_hist_trigger_attrs(attrs);

	वापस ERR_PTR(ret);
पूर्ण

अटल अंतरभूत व्योम save_comm(अक्षर *comm, काष्ठा task_काष्ठा *task)
अणु
	अगर (!task->pid) अणु
		म_नकल(comm, "<idle>");
		वापस;
	पूर्ण

	अगर (WARN_ON_ONCE(task->pid < 0)) अणु
		म_नकल(comm, "<XXX>");
		वापस;
	पूर्ण

	म_नकलन(comm, task->comm, TASK_COMM_LEN);
पूर्ण

अटल व्योम hist_elt_data_मुक्त(काष्ठा hist_elt_data *elt_data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < SYNTH_FIELDS_MAX; i++)
		kमुक्त(elt_data->field_var_str[i]);

	kमुक्त(elt_data->comm);
	kमुक्त(elt_data);
पूर्ण

अटल व्योम hist_trigger_elt_data_मुक्त(काष्ठा tracing_map_elt *elt)
अणु
	काष्ठा hist_elt_data *elt_data = elt->निजी_data;

	hist_elt_data_मुक्त(elt_data);
पूर्ण

अटल पूर्णांक hist_trigger_elt_data_alloc(काष्ठा tracing_map_elt *elt)
अणु
	काष्ठा hist_trigger_data *hist_data = elt->map->निजी_data;
	अचिन्हित पूर्णांक size = TASK_COMM_LEN;
	काष्ठा hist_elt_data *elt_data;
	काष्ठा hist_field *key_field;
	अचिन्हित पूर्णांक i, n_str;

	elt_data = kzalloc(माप(*elt_data), GFP_KERNEL);
	अगर (!elt_data)
		वापस -ENOMEM;

	क्रम_each_hist_key_field(i, hist_data) अणु
		key_field = hist_data->fields[i];

		अगर (key_field->flags & HIST_FIELD_FL_EXECNAME) अणु
			elt_data->comm = kzalloc(size, GFP_KERNEL);
			अगर (!elt_data->comm) अणु
				kमुक्त(elt_data);
				वापस -ENOMEM;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	n_str = hist_data->n_field_var_str + hist_data->n_save_var_str +
		hist_data->n_var_str;
	अगर (n_str > SYNTH_FIELDS_MAX) अणु
		hist_elt_data_मुक्त(elt_data);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(STR_VAR_LEN_MAX & (माप(u64) - 1));

	size = STR_VAR_LEN_MAX;

	क्रम (i = 0; i < n_str; i++) अणु
		elt_data->field_var_str[i] = kzalloc(size, GFP_KERNEL);
		अगर (!elt_data->field_var_str[i]) अणु
			hist_elt_data_मुक्त(elt_data);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	elt->निजी_data = elt_data;

	वापस 0;
पूर्ण

अटल व्योम hist_trigger_elt_data_init(काष्ठा tracing_map_elt *elt)
अणु
	काष्ठा hist_elt_data *elt_data = elt->निजी_data;

	अगर (elt_data->comm)
		save_comm(elt_data->comm, current);
पूर्ण

अटल स्थिर काष्ठा tracing_map_ops hist_trigger_elt_data_ops = अणु
	.elt_alloc	= hist_trigger_elt_data_alloc,
	.elt_मुक्त	= hist_trigger_elt_data_मुक्त,
	.elt_init	= hist_trigger_elt_data_init,
पूर्ण;

अटल स्थिर अक्षर *get_hist_field_flags(काष्ठा hist_field *hist_field)
अणु
	स्थिर अक्षर *flags_str = शून्य;

	अगर (hist_field->flags & HIST_FIELD_FL_HEX)
		flags_str = "hex";
	अन्यथा अगर (hist_field->flags & HIST_FIELD_FL_SYM)
		flags_str = "sym";
	अन्यथा अगर (hist_field->flags & HIST_FIELD_FL_SYM_OFFSET)
		flags_str = "sym-offset";
	अन्यथा अगर (hist_field->flags & HIST_FIELD_FL_EXECNAME)
		flags_str = "execname";
	अन्यथा अगर (hist_field->flags & HIST_FIELD_FL_SYSCALL)
		flags_str = "syscall";
	अन्यथा अगर (hist_field->flags & HIST_FIELD_FL_LOG2)
		flags_str = "log2";
	अन्यथा अगर (hist_field->flags & HIST_FIELD_FL_TIMESTAMP_USECS)
		flags_str = "usecs";

	वापस flags_str;
पूर्ण

अटल व्योम expr_field_str(काष्ठा hist_field *field, अक्षर *expr)
अणु
	अगर (field->flags & HIST_FIELD_FL_VAR_REF)
		म_जोड़ो(expr, "$");

	म_जोड़ो(expr, hist_field_name(field, 0));

	अगर (field->flags && !(field->flags & HIST_FIELD_FL_VAR_REF)) अणु
		स्थिर अक्षर *flags_str = get_hist_field_flags(field);

		अगर (flags_str) अणु
			म_जोड़ो(expr, ".");
			म_जोड़ो(expr, flags_str);
		पूर्ण
	पूर्ण
पूर्ण

अटल अक्षर *expr_str(काष्ठा hist_field *field, अचिन्हित पूर्णांक level)
अणु
	अक्षर *expr;

	अगर (level > 1)
		वापस शून्य;

	expr = kzalloc(MAX_FILTER_STR_VAL, GFP_KERNEL);
	अगर (!expr)
		वापस शून्य;

	अगर (!field->opeअक्रमs[0]) अणु
		expr_field_str(field, expr);
		वापस expr;
	पूर्ण

	अगर (field->चालक == FIELD_OP_UNARY_MINUS) अणु
		अक्षर *subexpr;

		म_जोड़ो(expr, "-(");
		subexpr = expr_str(field->opeअक्रमs[0], ++level);
		अगर (!subexpr) अणु
			kमुक्त(expr);
			वापस शून्य;
		पूर्ण
		म_जोड़ो(expr, subexpr);
		म_जोड़ो(expr, ")");

		kमुक्त(subexpr);

		वापस expr;
	पूर्ण

	expr_field_str(field->opeअक्रमs[0], expr);

	चयन (field->चालक) अणु
	हाल FIELD_OP_MINUS:
		म_जोड़ो(expr, "-");
		अवरोध;
	हाल FIELD_OP_PLUS:
		म_जोड़ो(expr, "+");
		अवरोध;
	शेष:
		kमुक्त(expr);
		वापस शून्य;
	पूर्ण

	expr_field_str(field->opeअक्रमs[1], expr);

	वापस expr;
पूर्ण

अटल पूर्णांक contains_चालक(अक्षर *str)
अणु
	क्रमागत field_op_id field_op = FIELD_OP_NONE;
	अक्षर *op;

	op = strpbrk(str, "+-");
	अगर (!op)
		वापस FIELD_OP_NONE;

	चयन (*op) अणु
	हाल '-':
		अगर (*str == '-')
			field_op = FIELD_OP_UNARY_MINUS;
		अन्यथा
			field_op = FIELD_OP_MINUS;
		अवरोध;
	हाल '+':
		field_op = FIELD_OP_PLUS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस field_op;
पूर्ण

अटल व्योम get_hist_field(काष्ठा hist_field *hist_field)
अणु
	hist_field->ref++;
पूर्ण

अटल व्योम __destroy_hist_field(काष्ठा hist_field *hist_field)
अणु
	अगर (--hist_field->ref > 1)
		वापस;

	kमुक्त(hist_field->var.name);
	kमुक्त(hist_field->name);
	kमुक्त(hist_field->type);

	kमुक्त(hist_field->प्रणाली);
	kमुक्त(hist_field->event_name);

	kमुक्त(hist_field);
पूर्ण

अटल व्योम destroy_hist_field(काष्ठा hist_field *hist_field,
			       अचिन्हित पूर्णांक level)
अणु
	अचिन्हित पूर्णांक i;

	अगर (level > 3)
		वापस;

	अगर (!hist_field)
		वापस;

	अगर (hist_field->flags & HIST_FIELD_FL_VAR_REF)
		वापस; /* var refs will be destroyed separately */

	क्रम (i = 0; i < HIST_FIELD_OPERANDS_MAX; i++)
		destroy_hist_field(hist_field->opeअक्रमs[i], level + 1);

	__destroy_hist_field(hist_field);
पूर्ण

अटल काष्ठा hist_field *create_hist_field(काष्ठा hist_trigger_data *hist_data,
					    काष्ठा ftrace_event_field *field,
					    अचिन्हित दीर्घ flags,
					    अक्षर *var_name)
अणु
	काष्ठा hist_field *hist_field;

	अगर (field && is_function_field(field))
		वापस शून्य;

	hist_field = kzalloc(माप(काष्ठा hist_field), GFP_KERNEL);
	अगर (!hist_field)
		वापस शून्य;

	hist_field->ref = 1;

	hist_field->hist_data = hist_data;

	अगर (flags & HIST_FIELD_FL_EXPR || flags & HIST_FIELD_FL_ALIAS)
		जाओ out; /* caller will populate */

	अगर (flags & HIST_FIELD_FL_VAR_REF) अणु
		hist_field->fn = hist_field_var_ref;
		जाओ out;
	पूर्ण

	अगर (flags & HIST_FIELD_FL_HITCOUNT) अणु
		hist_field->fn = hist_field_counter;
		hist_field->size = माप(u64);
		hist_field->type = kstrdup("u64", GFP_KERNEL);
		अगर (!hist_field->type)
			जाओ मुक्त;
		जाओ out;
	पूर्ण

	अगर (flags & HIST_FIELD_FL_STACKTRACE) अणु
		hist_field->fn = hist_field_none;
		जाओ out;
	पूर्ण

	अगर (flags & HIST_FIELD_FL_LOG2) अणु
		अचिन्हित दीर्घ fl = flags & ~HIST_FIELD_FL_LOG2;
		hist_field->fn = hist_field_log2;
		hist_field->opeअक्रमs[0] = create_hist_field(hist_data, field, fl, शून्य);
		hist_field->size = hist_field->opeअक्रमs[0]->size;
		hist_field->type = kstrdup(hist_field->opeअक्रमs[0]->type, GFP_KERNEL);
		अगर (!hist_field->type)
			जाओ मुक्त;
		जाओ out;
	पूर्ण

	अगर (flags & HIST_FIELD_FL_TIMESTAMP) अणु
		hist_field->fn = hist_field_बारtamp;
		hist_field->size = माप(u64);
		hist_field->type = kstrdup("u64", GFP_KERNEL);
		अगर (!hist_field->type)
			जाओ मुक्त;
		जाओ out;
	पूर्ण

	अगर (flags & HIST_FIELD_FL_CPU) अणु
		hist_field->fn = hist_field_cpu;
		hist_field->size = माप(पूर्णांक);
		hist_field->type = kstrdup("unsigned int", GFP_KERNEL);
		अगर (!hist_field->type)
			जाओ मुक्त;
		जाओ out;
	पूर्ण

	अगर (WARN_ON_ONCE(!field))
		जाओ out;

	अगर (is_string_field(field)) अणु
		flags |= HIST_FIELD_FL_STRING;

		hist_field->size = MAX_FILTER_STR_VAL;
		hist_field->type = kstrdup(field->type, GFP_KERNEL);
		अगर (!hist_field->type)
			जाओ मुक्त;

		अगर (field->filter_type == FILTER_STATIC_STRING)
			hist_field->fn = hist_field_string;
		अन्यथा अगर (field->filter_type == FILTER_DYN_STRING)
			hist_field->fn = hist_field_dynstring;
		अन्यथा
			hist_field->fn = hist_field_pstring;
	पूर्ण अन्यथा अणु
		hist_field->size = field->size;
		hist_field->is_चिन्हित = field->is_चिन्हित;
		hist_field->type = kstrdup(field->type, GFP_KERNEL);
		अगर (!hist_field->type)
			जाओ मुक्त;

		hist_field->fn = select_value_fn(field->size,
						 field->is_चिन्हित);
		अगर (!hist_field->fn) अणु
			destroy_hist_field(hist_field, 0);
			वापस शून्य;
		पूर्ण
	पूर्ण
 out:
	hist_field->field = field;
	hist_field->flags = flags;

	अगर (var_name) अणु
		hist_field->var.name = kstrdup(var_name, GFP_KERNEL);
		अगर (!hist_field->var.name)
			जाओ मुक्त;
	पूर्ण

	वापस hist_field;
 मुक्त:
	destroy_hist_field(hist_field, 0);
	वापस शून्य;
पूर्ण

अटल व्योम destroy_hist_fields(काष्ठा hist_trigger_data *hist_data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < HIST_FIELDS_MAX; i++) अणु
		अगर (hist_data->fields[i]) अणु
			destroy_hist_field(hist_data->fields[i], 0);
			hist_data->fields[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < hist_data->n_var_refs; i++) अणु
		WARN_ON(!(hist_data->var_refs[i]->flags & HIST_FIELD_FL_VAR_REF));
		__destroy_hist_field(hist_data->var_refs[i]);
		hist_data->var_refs[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक init_var_ref(काष्ठा hist_field *ref_field,
			काष्ठा hist_field *var_field,
			अक्षर *प्रणाली, अक्षर *event_name)
अणु
	पूर्णांक err = 0;

	ref_field->var.idx = var_field->var.idx;
	ref_field->var.hist_data = var_field->hist_data;
	ref_field->size = var_field->size;
	ref_field->is_चिन्हित = var_field->is_चिन्हित;
	ref_field->flags |= var_field->flags &
		(HIST_FIELD_FL_TIMESTAMP | HIST_FIELD_FL_TIMESTAMP_USECS);

	अगर (प्रणाली) अणु
		ref_field->प्रणाली = kstrdup(प्रणाली, GFP_KERNEL);
		अगर (!ref_field->प्रणाली)
			वापस -ENOMEM;
	पूर्ण

	अगर (event_name) अणु
		ref_field->event_name = kstrdup(event_name, GFP_KERNEL);
		अगर (!ref_field->event_name) अणु
			err = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर (var_field->var.name) अणु
		ref_field->name = kstrdup(var_field->var.name, GFP_KERNEL);
		अगर (!ref_field->name) अणु
			err = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण अन्यथा अगर (var_field->name) अणु
		ref_field->name = kstrdup(var_field->name, GFP_KERNEL);
		अगर (!ref_field->name) अणु
			err = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	ref_field->type = kstrdup(var_field->type, GFP_KERNEL);
	अगर (!ref_field->type) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण
 out:
	वापस err;
 मुक्त:
	kमुक्त(ref_field->प्रणाली);
	kमुक्त(ref_field->event_name);
	kमुक्त(ref_field->name);

	जाओ out;
पूर्ण

अटल पूर्णांक find_var_ref_idx(काष्ठा hist_trigger_data *hist_data,
			    काष्ठा hist_field *var_field)
अणु
	काष्ठा hist_field *ref_field;
	पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_var_refs; i++) अणु
		ref_field = hist_data->var_refs[i];
		अगर (ref_field->var.idx == var_field->var.idx &&
		    ref_field->var.hist_data == var_field->hist_data)
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * create_var_ref - Create a variable reference and attach it to trigger
 * @hist_data: The trigger that will be referencing the variable
 * @var_field: The VAR field to create a reference to
 * @प्रणाली: The optional प्रणाली string
 * @event_name: The optional event_name string
 *
 * Given a variable hist_field, create a VAR_REF hist_field that
 * represents a reference to it.
 *
 * This function also adds the reference to the trigger that
 * now references the variable.
 *
 * Return: The VAR_REF field अगर successful, शून्य अगर not
 */
अटल काष्ठा hist_field *create_var_ref(काष्ठा hist_trigger_data *hist_data,
					 काष्ठा hist_field *var_field,
					 अक्षर *प्रणाली, अक्षर *event_name)
अणु
	अचिन्हित दीर्घ flags = HIST_FIELD_FL_VAR_REF;
	काष्ठा hist_field *ref_field;
	पूर्णांक i;

	/* Check अगर the variable alपढ़ोy exists */
	क्रम (i = 0; i < hist_data->n_var_refs; i++) अणु
		ref_field = hist_data->var_refs[i];
		अगर (ref_field->var.idx == var_field->var.idx &&
		    ref_field->var.hist_data == var_field->hist_data) अणु
			get_hist_field(ref_field);
			वापस ref_field;
		पूर्ण
	पूर्ण

	ref_field = create_hist_field(var_field->hist_data, शून्य, flags, शून्य);
	अगर (ref_field) अणु
		अगर (init_var_ref(ref_field, var_field, प्रणाली, event_name)) अणु
			destroy_hist_field(ref_field, 0);
			वापस शून्य;
		पूर्ण

		hist_data->var_refs[hist_data->n_var_refs] = ref_field;
		ref_field->var_ref_idx = hist_data->n_var_refs++;
	पूर्ण

	वापस ref_field;
पूर्ण

अटल bool is_var_ref(अक्षर *var_name)
अणु
	अगर (!var_name || म_माप(var_name) < 2 || var_name[0] != '$')
		वापस false;

	वापस true;
पूर्ण

अटल अक्षर *field_name_from_var(काष्ठा hist_trigger_data *hist_data,
				 अक्षर *var_name)
अणु
	अक्षर *name, *field;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->attrs->var_defs.n_vars; i++) अणु
		name = hist_data->attrs->var_defs.name[i];

		अगर (म_भेद(var_name, name) == 0) अणु
			field = hist_data->attrs->var_defs.expr[i];
			अगर (contains_चालक(field) || is_var_ref(field))
				जारी;
			वापस field;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अक्षर *local_field_var_ref(काष्ठा hist_trigger_data *hist_data,
				 अक्षर *प्रणाली, अक्षर *event_name,
				 अक्षर *var_name)
अणु
	काष्ठा trace_event_call *call;

	अगर (प्रणाली && event_name) अणु
		call = hist_data->event_file->event_call;

		अगर (म_भेद(प्रणाली, call->class->प्रणाली) != 0)
			वापस शून्य;

		अगर (म_भेद(event_name, trace_event_name(call)) != 0)
			वापस शून्य;
	पूर्ण

	अगर (!!प्रणाली != !!event_name)
		वापस शून्य;

	अगर (!is_var_ref(var_name))
		वापस शून्य;

	var_name++;

	वापस field_name_from_var(hist_data, var_name);
पूर्ण

अटल काष्ठा hist_field *parse_var_ref(काष्ठा hist_trigger_data *hist_data,
					अक्षर *प्रणाली, अक्षर *event_name,
					अक्षर *var_name)
अणु
	काष्ठा hist_field *var_field = शून्य, *ref_field = शून्य;
	काष्ठा trace_array *tr = hist_data->event_file->tr;

	अगर (!is_var_ref(var_name))
		वापस शून्य;

	var_name++;

	var_field = find_event_var(hist_data, प्रणाली, event_name, var_name);
	अगर (var_field)
		ref_field = create_var_ref(hist_data, var_field,
					   प्रणाली, event_name);

	अगर (!ref_field)
		hist_err(tr, HIST_ERR_VAR_NOT_FOUND, errpos(var_name));

	वापस ref_field;
पूर्ण

अटल काष्ठा ftrace_event_field *
parse_field(काष्ठा hist_trigger_data *hist_data, काष्ठा trace_event_file *file,
	    अक्षर *field_str, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ftrace_event_field *field = शून्य;
	अक्षर *field_name, *modअगरier, *str;
	काष्ठा trace_array *tr = file->tr;

	modअगरier = str = kstrdup(field_str, GFP_KERNEL);
	अगर (!modअगरier)
		वापस ERR_PTR(-ENOMEM);

	field_name = strsep(&modअगरier, ".");
	अगर (modअगरier) अणु
		अगर (म_भेद(modअगरier, "hex") == 0)
			*flags |= HIST_FIELD_FL_HEX;
		अन्यथा अगर (म_भेद(modअगरier, "sym") == 0)
			*flags |= HIST_FIELD_FL_SYM;
		अन्यथा अगर (म_भेद(modअगरier, "sym-offset") == 0)
			*flags |= HIST_FIELD_FL_SYM_OFFSET;
		अन्यथा अगर ((म_भेद(modअगरier, "execname") == 0) &&
			 (म_भेद(field_name, "common_pid") == 0))
			*flags |= HIST_FIELD_FL_EXECNAME;
		अन्यथा अगर (म_भेद(modअगरier, "syscall") == 0)
			*flags |= HIST_FIELD_FL_SYSCALL;
		अन्यथा अगर (म_भेद(modअगरier, "log2") == 0)
			*flags |= HIST_FIELD_FL_LOG2;
		अन्यथा अगर (म_भेद(modअगरier, "usecs") == 0)
			*flags |= HIST_FIELD_FL_TIMESTAMP_USECS;
		अन्यथा अणु
			hist_err(tr, HIST_ERR_BAD_FIELD_MODIFIER, errpos(modअगरier));
			field = ERR_PTR(-EINVAL);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (म_भेद(field_name, "common_timestamp") == 0) अणु
		*flags |= HIST_FIELD_FL_TIMESTAMP;
		hist_data->enable_बारtamps = true;
		अगर (*flags & HIST_FIELD_FL_TIMESTAMP_USECS)
			hist_data->attrs->ts_in_usecs = true;
	पूर्ण अन्यथा अगर (म_भेद(field_name, "cpu") == 0)
		*flags |= HIST_FIELD_FL_CPU;
	अन्यथा अणु
		field = trace_find_event_field(file->event_call, field_name);
		अगर (!field || !field->size) अणु
			hist_err(tr, HIST_ERR_FIELD_NOT_FOUND, errpos(field_name));
			field = ERR_PTR(-EINVAL);
			जाओ out;
		पूर्ण
	पूर्ण
 out:
	kमुक्त(str);

	वापस field;
पूर्ण

अटल काष्ठा hist_field *create_alias(काष्ठा hist_trigger_data *hist_data,
				       काष्ठा hist_field *var_ref,
				       अक्षर *var_name)
अणु
	काष्ठा hist_field *alias = शून्य;
	अचिन्हित दीर्घ flags = HIST_FIELD_FL_ALIAS | HIST_FIELD_FL_VAR;

	alias = create_hist_field(hist_data, शून्य, flags, var_name);
	अगर (!alias)
		वापस शून्य;

	alias->fn = var_ref->fn;
	alias->opeअक्रमs[0] = var_ref;

	अगर (init_var_ref(alias, var_ref, var_ref->प्रणाली, var_ref->event_name)) अणु
		destroy_hist_field(alias, 0);
		वापस शून्य;
	पूर्ण

	alias->var_ref_idx = var_ref->var_ref_idx;

	वापस alias;
पूर्ण

अटल काष्ठा hist_field *parse_atom(काष्ठा hist_trigger_data *hist_data,
				     काष्ठा trace_event_file *file, अक्षर *str,
				     अचिन्हित दीर्घ *flags, अक्षर *var_name)
अणु
	अक्षर *s, *ref_प्रणाली = शून्य, *ref_event = शून्य, *ref_var = str;
	काष्ठा ftrace_event_field *field = शून्य;
	काष्ठा hist_field *hist_field = शून्य;
	पूर्णांक ret = 0;

	s = म_अक्षर(str, '.');
	अगर (s) अणु
		s = म_अक्षर(++s, '.');
		अगर (s) अणु
			ref_प्रणाली = strsep(&str, ".");
			अगर (!str) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ref_event = strsep(&str, ".");
			अगर (!str) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ref_var = str;
		पूर्ण
	पूर्ण

	s = local_field_var_ref(hist_data, ref_प्रणाली, ref_event, ref_var);
	अगर (!s) अणु
		hist_field = parse_var_ref(hist_data, ref_प्रणाली,
					   ref_event, ref_var);
		अगर (hist_field) अणु
			अगर (var_name) अणु
				hist_field = create_alias(hist_data, hist_field, var_name);
				अगर (!hist_field) अणु
					ret = -ENOMEM;
					जाओ out;
				पूर्ण
			पूर्ण
			वापस hist_field;
		पूर्ण
	पूर्ण अन्यथा
		str = s;

	field = parse_field(hist_data, file, str, flags);
	अगर (IS_ERR(field)) अणु
		ret = PTR_ERR(field);
		जाओ out;
	पूर्ण

	hist_field = create_hist_field(hist_data, field, *flags, var_name);
	अगर (!hist_field) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	वापस hist_field;
 out:
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा hist_field *parse_expr(काष्ठा hist_trigger_data *hist_data,
				     काष्ठा trace_event_file *file,
				     अक्षर *str, अचिन्हित दीर्घ flags,
				     अक्षर *var_name, अचिन्हित पूर्णांक level);

अटल काष्ठा hist_field *parse_unary(काष्ठा hist_trigger_data *hist_data,
				      काष्ठा trace_event_file *file,
				      अक्षर *str, अचिन्हित दीर्घ flags,
				      अक्षर *var_name, अचिन्हित पूर्णांक level)
अणु
	काष्ठा hist_field *opeअक्रम1, *expr = शून्य;
	अचिन्हित दीर्घ opeअक्रम_flags;
	पूर्णांक ret = 0;
	अक्षर *s;

	/* we support only -(xxx) i.e. explicit parens required */

	अगर (level > 3) अणु
		hist_err(file->tr, HIST_ERR_TOO_MANY_SUBEXPR, errpos(str));
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	str++; /* skip leading '-' */

	s = म_अक्षर(str, '(');
	अगर (s)
		str++;
	अन्यथा अणु
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	s = म_खोजप(str, ')');
	अगर (s)
		*s = '\0';
	अन्यथा अणु
		ret = -EINVAL; /* no closing ')' */
		जाओ मुक्त;
	पूर्ण

	flags |= HIST_FIELD_FL_EXPR;
	expr = create_hist_field(hist_data, शून्य, flags, var_name);
	अगर (!expr) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	opeअक्रम_flags = 0;
	opeअक्रम1 = parse_expr(hist_data, file, str, opeअक्रम_flags, शून्य, ++level);
	अगर (IS_ERR(opeअक्रम1)) अणु
		ret = PTR_ERR(opeअक्रम1);
		जाओ मुक्त;
	पूर्ण

	expr->flags |= opeअक्रम1->flags &
		(HIST_FIELD_FL_TIMESTAMP | HIST_FIELD_FL_TIMESTAMP_USECS);
	expr->fn = hist_field_unary_minus;
	expr->opeअक्रमs[0] = opeअक्रम1;
	expr->चालक = FIELD_OP_UNARY_MINUS;
	expr->name = expr_str(expr, 0);
	expr->type = kstrdup(opeअक्रम1->type, GFP_KERNEL);
	अगर (!expr->type) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	वापस expr;
 मुक्त:
	destroy_hist_field(expr, 0);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक check_expr_opeअक्रमs(काष्ठा trace_array *tr,
			       काष्ठा hist_field *opeअक्रम1,
			       काष्ठा hist_field *opeअक्रम2)
अणु
	अचिन्हित दीर्घ opeअक्रम1_flags = opeअक्रम1->flags;
	अचिन्हित दीर्घ opeअक्रम2_flags = opeअक्रम2->flags;

	अगर ((opeअक्रम1_flags & HIST_FIELD_FL_VAR_REF) ||
	    (opeअक्रम1_flags & HIST_FIELD_FL_ALIAS)) अणु
		काष्ठा hist_field *var;

		var = find_var_field(opeअक्रम1->var.hist_data, opeअक्रम1->name);
		अगर (!var)
			वापस -EINVAL;
		opeअक्रम1_flags = var->flags;
	पूर्ण

	अगर ((opeअक्रम2_flags & HIST_FIELD_FL_VAR_REF) ||
	    (opeअक्रम2_flags & HIST_FIELD_FL_ALIAS)) अणु
		काष्ठा hist_field *var;

		var = find_var_field(opeअक्रम2->var.hist_data, opeअक्रम2->name);
		अगर (!var)
			वापस -EINVAL;
		opeअक्रम2_flags = var->flags;
	पूर्ण

	अगर ((opeअक्रम1_flags & HIST_FIELD_FL_TIMESTAMP_USECS) !=
	    (opeअक्रम2_flags & HIST_FIELD_FL_TIMESTAMP_USECS)) अणु
		hist_err(tr, HIST_ERR_TIMESTAMP_MISMATCH, 0);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा hist_field *parse_expr(काष्ठा hist_trigger_data *hist_data,
				     काष्ठा trace_event_file *file,
				     अक्षर *str, अचिन्हित दीर्घ flags,
				     अक्षर *var_name, अचिन्हित पूर्णांक level)
अणु
	काष्ठा hist_field *opeअक्रम1 = शून्य, *opeअक्रम2 = शून्य, *expr = शून्य;
	अचिन्हित दीर्घ opeअक्रम_flags;
	पूर्णांक field_op, ret = -EINVAL;
	अक्षर *sep, *opeअक्रम1_str;

	अगर (level > 3) अणु
		hist_err(file->tr, HIST_ERR_TOO_MANY_SUBEXPR, errpos(str));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	field_op = contains_चालक(str);

	अगर (field_op == FIELD_OP_NONE)
		वापस parse_atom(hist_data, file, str, &flags, var_name);

	अगर (field_op == FIELD_OP_UNARY_MINUS)
		वापस parse_unary(hist_data, file, str, flags, var_name, ++level);

	चयन (field_op) अणु
	हाल FIELD_OP_MINUS:
		sep = "-";
		अवरोध;
	हाल FIELD_OP_PLUS:
		sep = "+";
		अवरोध;
	शेष:
		जाओ मुक्त;
	पूर्ण

	opeअक्रम1_str = strsep(&str, sep);
	अगर (!opeअक्रम1_str || !str)
		जाओ मुक्त;

	opeअक्रम_flags = 0;
	opeअक्रम1 = parse_atom(hist_data, file, opeअक्रम1_str,
			      &opeअक्रम_flags, शून्य);
	अगर (IS_ERR(opeअक्रम1)) अणु
		ret = PTR_ERR(opeअक्रम1);
		opeअक्रम1 = शून्य;
		जाओ मुक्त;
	पूर्ण

	/* rest of string could be another expression e.g. b+c in a+b+c */
	opeअक्रम_flags = 0;
	opeअक्रम2 = parse_expr(hist_data, file, str, opeअक्रम_flags, शून्य, ++level);
	अगर (IS_ERR(opeअक्रम2)) अणु
		ret = PTR_ERR(opeअक्रम2);
		opeअक्रम2 = शून्य;
		जाओ मुक्त;
	पूर्ण

	ret = check_expr_opeअक्रमs(file->tr, opeअक्रम1, opeअक्रम2);
	अगर (ret)
		जाओ मुक्त;

	flags |= HIST_FIELD_FL_EXPR;

	flags |= opeअक्रम1->flags &
		(HIST_FIELD_FL_TIMESTAMP | HIST_FIELD_FL_TIMESTAMP_USECS);

	expr = create_hist_field(hist_data, शून्य, flags, var_name);
	अगर (!expr) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	opeअक्रम1->पढ़ो_once = true;
	opeअक्रम2->पढ़ो_once = true;

	expr->opeअक्रमs[0] = opeअक्रम1;
	expr->opeअक्रमs[1] = opeअक्रम2;
	expr->चालक = field_op;
	expr->name = expr_str(expr, 0);
	expr->type = kstrdup(opeअक्रम1->type, GFP_KERNEL);
	अगर (!expr->type) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	चयन (field_op) अणु
	हाल FIELD_OP_MINUS:
		expr->fn = hist_field_minus;
		अवरोध;
	हाल FIELD_OP_PLUS:
		expr->fn = hist_field_plus;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	वापस expr;
 मुक्त:
	destroy_hist_field(opeअक्रम1, 0);
	destroy_hist_field(opeअक्रम2, 0);
	destroy_hist_field(expr, 0);

	वापस ERR_PTR(ret);
पूर्ण

अटल अक्षर *find_trigger_filter(काष्ठा hist_trigger_data *hist_data,
				 काष्ठा trace_event_file *file)
अणु
	काष्ठा event_trigger_data *test;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			अगर (test->निजी_data == hist_data)
				वापस test->filter_str;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा event_command trigger_hist_cmd;
अटल पूर्णांक event_hist_trigger_func(काष्ठा event_command *cmd_ops,
				   काष्ठा trace_event_file *file,
				   अक्षर *glob, अक्षर *cmd, अक्षर *param);

अटल bool compatible_keys(काष्ठा hist_trigger_data *target_hist_data,
			    काष्ठा hist_trigger_data *hist_data,
			    अचिन्हित पूर्णांक n_keys)
अणु
	काष्ठा hist_field *target_hist_field, *hist_field;
	अचिन्हित पूर्णांक n, i, j;

	अगर (hist_data->n_fields - hist_data->n_vals != n_keys)
		वापस false;

	i = hist_data->n_vals;
	j = target_hist_data->n_vals;

	क्रम (n = 0; n < n_keys; n++) अणु
		hist_field = hist_data->fields[i + n];
		target_hist_field = target_hist_data->fields[j + n];

		अगर (म_भेद(hist_field->type, target_hist_field->type) != 0)
			वापस false;
		अगर (hist_field->size != target_hist_field->size)
			वापस false;
		अगर (hist_field->is_चिन्हित != target_hist_field->is_चिन्हित)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा hist_trigger_data *
find_compatible_hist(काष्ठा hist_trigger_data *target_hist_data,
		     काष्ठा trace_event_file *file)
अणु
	काष्ठा hist_trigger_data *hist_data;
	काष्ठा event_trigger_data *test;
	अचिन्हित पूर्णांक n_keys;

	lockdep_निश्चित_held(&event_mutex);

	n_keys = target_hist_data->n_fields - target_hist_data->n_vals;

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			hist_data = test->निजी_data;

			अगर (compatible_keys(target_hist_data, hist_data, n_keys))
				वापस hist_data;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा trace_event_file *event_file(काष्ठा trace_array *tr,
					   अक्षर *प्रणाली, अक्षर *event_name)
अणु
	काष्ठा trace_event_file *file;

	file = __find_event_file(tr, प्रणाली, event_name);
	अगर (!file)
		वापस ERR_PTR(-EINVAL);

	वापस file;
पूर्ण

अटल काष्ठा hist_field *
find_synthetic_field_var(काष्ठा hist_trigger_data *target_hist_data,
			 अक्षर *प्रणाली, अक्षर *event_name, अक्षर *field_name)
अणु
	काष्ठा hist_field *event_var;
	अक्षर *synthetic_name;

	synthetic_name = kzalloc(MAX_FILTER_STR_VAL, GFP_KERNEL);
	अगर (!synthetic_name)
		वापस ERR_PTR(-ENOMEM);

	म_नकल(synthetic_name, "synthetic_");
	म_जोड़ो(synthetic_name, field_name);

	event_var = find_event_var(target_hist_data, प्रणाली, event_name, synthetic_name);

	kमुक्त(synthetic_name);

	वापस event_var;
पूर्ण

/**
 * create_field_var_hist - Automatically create a histogram and var क्रम a field
 * @target_hist_data: The target hist trigger
 * @subsys_name: Optional subप्रणाली name
 * @event_name: Optional event name
 * @field_name: The name of the field (and the resulting variable)
 *
 * Hist trigger actions fetch data from variables, not directly from
 * events.  However, क्रम convenience, users are allowed to directly
 * specअगरy an event field in an action, which will be स्वतःmatically
 * converted पूर्णांकo a variable on their behalf.

 * If a user specअगरies a field on an event that isn't the event the
 * histogram currently being defined (the target event histogram), the
 * only way that can be accomplished is अगर a new hist trigger is
 * created and the field variable defined on that.
 *
 * This function creates a new histogram compatible with the target
 * event (meaning a histogram with the same key as the target
 * histogram), and creates a variable क्रम the specअगरied field, but
 * with 'synthetic_' prepended to the variable name in order to aव्योम
 * collision with normal field variables.
 *
 * Return: The variable created क्रम the field.
 */
अटल काष्ठा hist_field *
create_field_var_hist(काष्ठा hist_trigger_data *target_hist_data,
		      अक्षर *subsys_name, अक्षर *event_name, अक्षर *field_name)
अणु
	काष्ठा trace_array *tr = target_hist_data->event_file->tr;
	काष्ठा hist_field *event_var = ERR_PTR(-EINVAL);
	काष्ठा hist_trigger_data *hist_data;
	अचिन्हित पूर्णांक i, n, first = true;
	काष्ठा field_var_hist *var_hist;
	काष्ठा trace_event_file *file;
	काष्ठा hist_field *key_field;
	अक्षर *saved_filter;
	अक्षर *cmd;
	पूर्णांक ret;

	अगर (target_hist_data->n_field_var_hists >= SYNTH_FIELDS_MAX) अणु
		hist_err(tr, HIST_ERR_TOO_MANY_FIELD_VARS, errpos(field_name));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	file = event_file(tr, subsys_name, event_name);

	अगर (IS_ERR(file)) अणु
		hist_err(tr, HIST_ERR_EVENT_खाता_NOT_FOUND, errpos(field_name));
		ret = PTR_ERR(file);
		वापस ERR_PTR(ret);
	पूर्ण

	/*
	 * Look क्रम a histogram compatible with target.  We'll use the
	 * found histogram specअगरication to create a new matching
	 * histogram with our variable on it.  target_hist_data is not
	 * yet a रेजिस्टरed histogram so we can't use that.
	 */
	hist_data = find_compatible_hist(target_hist_data, file);
	अगर (!hist_data) अणु
		hist_err(tr, HIST_ERR_HIST_NOT_FOUND, errpos(field_name));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* See अगर a synthetic field variable has alपढ़ोy been created */
	event_var = find_synthetic_field_var(target_hist_data, subsys_name,
					     event_name, field_name);
	अगर (!IS_ERR_OR_शून्य(event_var))
		वापस event_var;

	var_hist = kzalloc(माप(*var_hist), GFP_KERNEL);
	अगर (!var_hist)
		वापस ERR_PTR(-ENOMEM);

	cmd = kzalloc(MAX_FILTER_STR_VAL, GFP_KERNEL);
	अगर (!cmd) अणु
		kमुक्त(var_hist);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Use the same keys as the compatible histogram */
	म_जोड़ो(cmd, "keys=");

	क्रम_each_hist_key_field(i, hist_data) अणु
		key_field = hist_data->fields[i];
		अगर (!first)
			म_जोड़ो(cmd, ",");
		म_जोड़ो(cmd, key_field->field->name);
		first = false;
	पूर्ण

	/* Create the synthetic field variable specअगरication */
	म_जोड़ो(cmd, ":synthetic_");
	म_जोड़ो(cmd, field_name);
	म_जोड़ो(cmd, "=");
	म_जोड़ो(cmd, field_name);

	/* Use the same filter as the compatible histogram */
	saved_filter = find_trigger_filter(hist_data, file);
	अगर (saved_filter) अणु
		म_जोड़ो(cmd, " if ");
		म_जोड़ो(cmd, saved_filter);
	पूर्ण

	var_hist->cmd = kstrdup(cmd, GFP_KERNEL);
	अगर (!var_hist->cmd) अणु
		kमुक्त(cmd);
		kमुक्त(var_hist);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Save the compatible histogram inक्रमmation */
	var_hist->hist_data = hist_data;

	/* Create the new histogram with our variable */
	ret = event_hist_trigger_func(&trigger_hist_cmd, file,
				      "", "hist", cmd);
	अगर (ret) अणु
		kमुक्त(cmd);
		kमुक्त(var_hist->cmd);
		kमुक्त(var_hist);
		hist_err(tr, HIST_ERR_HIST_CREATE_FAIL, errpos(field_name));
		वापस ERR_PTR(ret);
	पूर्ण

	kमुक्त(cmd);

	/* If we can't find the variable, something went wrong */
	event_var = find_synthetic_field_var(target_hist_data, subsys_name,
					     event_name, field_name);
	अगर (IS_ERR_OR_शून्य(event_var)) अणु
		kमुक्त(var_hist->cmd);
		kमुक्त(var_hist);
		hist_err(tr, HIST_ERR_SYNTH_VAR_NOT_FOUND, errpos(field_name));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	n = target_hist_data->n_field_var_hists;
	target_hist_data->field_var_hists[n] = var_hist;
	target_hist_data->n_field_var_hists++;

	वापस event_var;
पूर्ण

अटल काष्ठा hist_field *
find_target_event_var(काष्ठा hist_trigger_data *hist_data,
		      अक्षर *subsys_name, अक्षर *event_name, अक्षर *var_name)
अणु
	काष्ठा trace_event_file *file = hist_data->event_file;
	काष्ठा hist_field *hist_field = शून्य;

	अगर (subsys_name) अणु
		काष्ठा trace_event_call *call;

		अगर (!event_name)
			वापस शून्य;

		call = file->event_call;

		अगर (म_भेद(subsys_name, call->class->प्रणाली) != 0)
			वापस शून्य;

		अगर (म_भेद(event_name, trace_event_name(call)) != 0)
			वापस शून्य;
	पूर्ण

	hist_field = find_var_field(hist_data, var_name);

	वापस hist_field;
पूर्ण

अटल अंतरभूत व्योम __update_field_vars(काष्ठा tracing_map_elt *elt,
				       काष्ठा trace_buffer *buffer,
				       काष्ठा ring_buffer_event *rbe,
				       व्योम *rec,
				       काष्ठा field_var **field_vars,
				       अचिन्हित पूर्णांक n_field_vars,
				       अचिन्हित पूर्णांक field_var_str_start)
अणु
	काष्ठा hist_elt_data *elt_data = elt->निजी_data;
	अचिन्हित पूर्णांक i, j, var_idx;
	u64 var_val;

	क्रम (i = 0, j = field_var_str_start; i < n_field_vars; i++) अणु
		काष्ठा field_var *field_var = field_vars[i];
		काष्ठा hist_field *var = field_var->var;
		काष्ठा hist_field *val = field_var->val;

		var_val = val->fn(val, elt, buffer, rbe, rec);
		var_idx = var->var.idx;

		अगर (val->flags & HIST_FIELD_FL_STRING) अणु
			अक्षर *str = elt_data->field_var_str[j++];
			अक्षर *val_str = (अक्षर *)(uपूर्णांकptr_t)var_val;

			strscpy(str, val_str, STR_VAR_LEN_MAX);
			var_val = (u64)(uपूर्णांकptr_t)str;
		पूर्ण
		tracing_map_set_var(elt, var_idx, var_val);
	पूर्ण
पूर्ण

अटल व्योम update_field_vars(काष्ठा hist_trigger_data *hist_data,
			      काष्ठा tracing_map_elt *elt,
			      काष्ठा trace_buffer *buffer,
			      काष्ठा ring_buffer_event *rbe,
			      व्योम *rec)
अणु
	__update_field_vars(elt, buffer, rbe, rec, hist_data->field_vars,
			    hist_data->n_field_vars, 0);
पूर्ण

अटल व्योम save_track_data_vars(काष्ठा hist_trigger_data *hist_data,
				 काष्ठा tracing_map_elt *elt,
				 काष्ठा trace_buffer *buffer,  व्योम *rec,
				 काष्ठा ring_buffer_event *rbe, व्योम *key,
				 काष्ठा action_data *data, u64 *var_ref_vals)
अणु
	__update_field_vars(elt, buffer, rbe, rec, hist_data->save_vars,
			    hist_data->n_save_vars, hist_data->n_field_var_str);
पूर्ण

अटल काष्ठा hist_field *create_var(काष्ठा hist_trigger_data *hist_data,
				     काष्ठा trace_event_file *file,
				     अक्षर *name, पूर्णांक size, स्थिर अक्षर *type)
अणु
	काष्ठा hist_field *var;
	पूर्णांक idx;

	अगर (find_var(hist_data, file, name) && !hist_data->हटाओ) अणु
		var = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	var = kzalloc(माप(काष्ठा hist_field), GFP_KERNEL);
	अगर (!var) अणु
		var = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	idx = tracing_map_add_var(hist_data->map);
	अगर (idx < 0) अणु
		kमुक्त(var);
		var = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	var->ref = 1;
	var->flags = HIST_FIELD_FL_VAR;
	var->var.idx = idx;
	var->var.hist_data = var->hist_data = hist_data;
	var->size = size;
	var->var.name = kstrdup(name, GFP_KERNEL);
	var->type = kstrdup(type, GFP_KERNEL);
	अगर (!var->var.name || !var->type) अणु
		kमुक्त(var->var.name);
		kमुक्त(var->type);
		kमुक्त(var);
		var = ERR_PTR(-ENOMEM);
	पूर्ण
 out:
	वापस var;
पूर्ण

अटल काष्ठा field_var *create_field_var(काष्ठा hist_trigger_data *hist_data,
					  काष्ठा trace_event_file *file,
					  अक्षर *field_name)
अणु
	काष्ठा hist_field *val = शून्य, *var = शून्य;
	अचिन्हित दीर्घ flags = HIST_FIELD_FL_VAR;
	काष्ठा trace_array *tr = file->tr;
	काष्ठा field_var *field_var;
	पूर्णांक ret = 0;

	अगर (hist_data->n_field_vars >= SYNTH_FIELDS_MAX) अणु
		hist_err(tr, HIST_ERR_TOO_MANY_FIELD_VARS, errpos(field_name));
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	val = parse_atom(hist_data, file, field_name, &flags, शून्य);
	अगर (IS_ERR(val)) अणु
		hist_err(tr, HIST_ERR_FIELD_VAR_PARSE_FAIL, errpos(field_name));
		ret = PTR_ERR(val);
		जाओ err;
	पूर्ण

	var = create_var(hist_data, file, field_name, val->size, val->type);
	अगर (IS_ERR(var)) अणु
		hist_err(tr, HIST_ERR_VAR_CREATE_FIND_FAIL, errpos(field_name));
		kमुक्त(val);
		ret = PTR_ERR(var);
		जाओ err;
	पूर्ण

	field_var = kzalloc(माप(काष्ठा field_var), GFP_KERNEL);
	अगर (!field_var) अणु
		kमुक्त(val);
		kमुक्त(var);
		ret =  -ENOMEM;
		जाओ err;
	पूर्ण

	field_var->var = var;
	field_var->val = val;
 out:
	वापस field_var;
 err:
	field_var = ERR_PTR(ret);
	जाओ out;
पूर्ण

/**
 * create_target_field_var - Automatically create a variable क्रम a field
 * @target_hist_data: The target hist trigger
 * @subsys_name: Optional subप्रणाली name
 * @event_name: Optional event name
 * @var_name: The name of the field (and the resulting variable)
 *
 * Hist trigger actions fetch data from variables, not directly from
 * events.  However, क्रम convenience, users are allowed to directly
 * specअगरy an event field in an action, which will be स्वतःmatically
 * converted पूर्णांकo a variable on their behalf.

 * This function creates a field variable with the name var_name on
 * the hist trigger currently being defined on the target event.  If
 * subsys_name and event_name are specअगरied, this function simply
 * verअगरies that they करो in fact match the target event subप्रणाली and
 * event name.
 *
 * Return: The variable created क्रम the field.
 */
अटल काष्ठा field_var *
create_target_field_var(काष्ठा hist_trigger_data *target_hist_data,
			अक्षर *subsys_name, अक्षर *event_name, अक्षर *var_name)
अणु
	काष्ठा trace_event_file *file = target_hist_data->event_file;

	अगर (subsys_name) अणु
		काष्ठा trace_event_call *call;

		अगर (!event_name)
			वापस शून्य;

		call = file->event_call;

		अगर (म_भेद(subsys_name, call->class->प्रणाली) != 0)
			वापस शून्य;

		अगर (म_भेद(event_name, trace_event_name(call)) != 0)
			वापस शून्य;
	पूर्ण

	वापस create_field_var(target_hist_data, file, var_name);
पूर्ण

अटल bool check_track_val_max(u64 track_val, u64 var_val)
अणु
	अगर (var_val <= track_val)
		वापस false;

	वापस true;
पूर्ण

अटल bool check_track_val_changed(u64 track_val, u64 var_val)
अणु
	अगर (var_val == track_val)
		वापस false;

	वापस true;
पूर्ण

अटल u64 get_track_val(काष्ठा hist_trigger_data *hist_data,
			 काष्ठा tracing_map_elt *elt,
			 काष्ठा action_data *data)
अणु
	अचिन्हित पूर्णांक track_var_idx = data->track_data.track_var->var.idx;
	u64 track_val;

	track_val = tracing_map_पढ़ो_var(elt, track_var_idx);

	वापस track_val;
पूर्ण

अटल व्योम save_track_val(काष्ठा hist_trigger_data *hist_data,
			   काष्ठा tracing_map_elt *elt,
			   काष्ठा action_data *data, u64 var_val)
अणु
	अचिन्हित पूर्णांक track_var_idx = data->track_data.track_var->var.idx;

	tracing_map_set_var(elt, track_var_idx, var_val);
पूर्ण

अटल व्योम save_track_data(काष्ठा hist_trigger_data *hist_data,
			    काष्ठा tracing_map_elt *elt,
			    काष्ठा trace_buffer *buffer, व्योम *rec,
			    काष्ठा ring_buffer_event *rbe, व्योम *key,
			    काष्ठा action_data *data, u64 *var_ref_vals)
अणु
	अगर (data->track_data.save_data)
		data->track_data.save_data(hist_data, elt, buffer, rec, rbe,
					   key, data, var_ref_vals);
पूर्ण

अटल bool check_track_val(काष्ठा tracing_map_elt *elt,
			    काष्ठा action_data *data,
			    u64 var_val)
अणु
	काष्ठा hist_trigger_data *hist_data;
	u64 track_val;

	hist_data = data->track_data.track_var->hist_data;
	track_val = get_track_val(hist_data, elt, data);

	वापस data->track_data.check_val(track_val, var_val);
पूर्ण

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
अटल bool cond_snapshot_update(काष्ठा trace_array *tr, व्योम *cond_data)
अणु
	/* called with tr->max_lock held */
	काष्ठा track_data *track_data = tr->cond_snapshot->cond_data;
	काष्ठा hist_elt_data *elt_data, *track_elt_data;
	काष्ठा snapshot_context *context = cond_data;
	काष्ठा action_data *action;
	u64 track_val;

	अगर (!track_data)
		वापस false;

	action = track_data->action_data;

	track_val = get_track_val(track_data->hist_data, context->elt,
				  track_data->action_data);

	अगर (!action->track_data.check_val(track_data->track_val, track_val))
		वापस false;

	track_data->track_val = track_val;
	स_नकल(track_data->key, context->key, track_data->key_len);

	elt_data = context->elt->निजी_data;
	track_elt_data = track_data->elt.निजी_data;
	अगर (elt_data->comm)
		म_नकलन(track_elt_data->comm, elt_data->comm, TASK_COMM_LEN);

	track_data->updated = true;

	वापस true;
पूर्ण

अटल व्योम save_track_data_snapshot(काष्ठा hist_trigger_data *hist_data,
				     काष्ठा tracing_map_elt *elt,
				     काष्ठा trace_buffer *buffer, व्योम *rec,
				     काष्ठा ring_buffer_event *rbe, व्योम *key,
				     काष्ठा action_data *data,
				     u64 *var_ref_vals)
अणु
	काष्ठा trace_event_file *file = hist_data->event_file;
	काष्ठा snapshot_context context;

	context.elt = elt;
	context.key = key;

	tracing_snapshot_cond(file->tr, &context);
पूर्ण

अटल व्योम hist_trigger_prपूर्णांक_key(काष्ठा seq_file *m,
				   काष्ठा hist_trigger_data *hist_data,
				   व्योम *key,
				   काष्ठा tracing_map_elt *elt);

अटल काष्ठा action_data *snapshot_action(काष्ठा hist_trigger_data *hist_data)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!hist_data->n_actions)
		वापस शून्य;

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		काष्ठा action_data *data = hist_data->actions[i];

		अगर (data->action == ACTION_SNAPSHOT)
			वापस data;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम track_data_snapshot_prपूर्णांक(काष्ठा seq_file *m,
				      काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_event_file *file = hist_data->event_file;
	काष्ठा track_data *track_data;
	काष्ठा action_data *action;

	track_data = tracing_cond_snapshot_data(file->tr);
	अगर (!track_data)
		वापस;

	अगर (!track_data->updated)
		वापस;

	action = snapshot_action(hist_data);
	अगर (!action)
		वापस;

	seq_माला_दो(m, "\nSnapshot taken (see tracing/snapshot).  Details:\n");
	seq_म_लिखो(m, "\ttriggering value { %s(%s) }: %10llu",
		   action->handler == HANDLER_ONMAX ? "onmax" : "onchange",
		   action->track_data.var_str, track_data->track_val);

	seq_माला_दो(m, "\ttriggered by event with key: ");
	hist_trigger_prपूर्णांक_key(m, hist_data, track_data->key, &track_data->elt);
	seq_अ_दो(m, '\n');
पूर्ण
#अन्यथा
अटल bool cond_snapshot_update(काष्ठा trace_array *tr, व्योम *cond_data)
अणु
	वापस false;
पूर्ण
अटल व्योम save_track_data_snapshot(काष्ठा hist_trigger_data *hist_data,
				     काष्ठा tracing_map_elt *elt,
				     काष्ठा trace_buffer *buffer, व्योम *rec,
				     काष्ठा ring_buffer_event *rbe, व्योम *key,
				     काष्ठा action_data *data,
				     u64 *var_ref_vals) अणुपूर्ण
अटल व्योम track_data_snapshot_prपूर्णांक(काष्ठा seq_file *m,
				      काष्ठा hist_trigger_data *hist_data) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_TRACER_SNAPSHOT */

अटल व्योम track_data_prपूर्णांक(काष्ठा seq_file *m,
			     काष्ठा hist_trigger_data *hist_data,
			     काष्ठा tracing_map_elt *elt,
			     काष्ठा action_data *data)
अणु
	u64 track_val = get_track_val(hist_data, elt, data);
	अचिन्हित पूर्णांक i, save_var_idx;

	अगर (data->handler == HANDLER_ONMAX)
		seq_म_लिखो(m, "\n\tmax: %10llu", track_val);
	अन्यथा अगर (data->handler == HANDLER_ONCHANGE)
		seq_म_लिखो(m, "\n\tchanged: %10llu", track_val);

	अगर (data->action == ACTION_SNAPSHOT)
		वापस;

	क्रम (i = 0; i < hist_data->n_save_vars; i++) अणु
		काष्ठा hist_field *save_val = hist_data->save_vars[i]->val;
		काष्ठा hist_field *save_var = hist_data->save_vars[i]->var;
		u64 val;

		save_var_idx = save_var->var.idx;

		val = tracing_map_पढ़ो_var(elt, save_var_idx);

		अगर (save_val->flags & HIST_FIELD_FL_STRING) अणु
			seq_म_लिखो(m, "  %s: %-32s", save_var->var.name,
				   (अक्षर *)(uपूर्णांकptr_t)(val));
		पूर्ण अन्यथा
			seq_म_लिखो(m, "  %s: %10llu", save_var->var.name, val);
	पूर्ण
पूर्ण

अटल व्योम ontrack_action(काष्ठा hist_trigger_data *hist_data,
			   काष्ठा tracing_map_elt *elt,
			   काष्ठा trace_buffer *buffer, व्योम *rec,
			   काष्ठा ring_buffer_event *rbe, व्योम *key,
			   काष्ठा action_data *data, u64 *var_ref_vals)
अणु
	u64 var_val = var_ref_vals[data->track_data.var_ref->var_ref_idx];

	अगर (check_track_val(elt, data, var_val)) अणु
		save_track_val(hist_data, elt, data, var_val);
		save_track_data(hist_data, elt, buffer, rec, rbe,
				key, data, var_ref_vals);
	पूर्ण
पूर्ण

अटल व्योम action_data_destroy(काष्ठा action_data *data)
अणु
	अचिन्हित पूर्णांक i;

	lockdep_निश्चित_held(&event_mutex);

	kमुक्त(data->action_name);

	क्रम (i = 0; i < data->n_params; i++)
		kमुक्त(data->params[i]);

	अगर (data->synth_event)
		data->synth_event->ref--;

	kमुक्त(data->synth_event_name);

	kमुक्त(data);
पूर्ण

अटल व्योम track_data_destroy(काष्ठा hist_trigger_data *hist_data,
			       काष्ठा action_data *data)
अणु
	काष्ठा trace_event_file *file = hist_data->event_file;

	destroy_hist_field(data->track_data.track_var, 0);

	अगर (data->action == ACTION_SNAPSHOT) अणु
		काष्ठा track_data *track_data;

		track_data = tracing_cond_snapshot_data(file->tr);
		अगर (track_data && track_data->hist_data == hist_data) अणु
			tracing_snapshot_cond_disable(file->tr);
			track_data_मुक्त(track_data);
		पूर्ण
	पूर्ण

	kमुक्त(data->track_data.var_str);

	action_data_destroy(data);
पूर्ण

अटल पूर्णांक action_create(काष्ठा hist_trigger_data *hist_data,
			 काष्ठा action_data *data);

अटल पूर्णांक track_data_create(काष्ठा hist_trigger_data *hist_data,
			     काष्ठा action_data *data)
अणु
	काष्ठा hist_field *var_field, *ref_field, *track_var = शून्य;
	काष्ठा trace_event_file *file = hist_data->event_file;
	काष्ठा trace_array *tr = file->tr;
	अक्षर *track_data_var_str;
	पूर्णांक ret = 0;

	track_data_var_str = data->track_data.var_str;
	अगर (track_data_var_str[0] != '$') अणु
		hist_err(tr, HIST_ERR_ONX_NOT_VAR, errpos(track_data_var_str));
		वापस -EINVAL;
	पूर्ण
	track_data_var_str++;

	var_field = find_target_event_var(hist_data, शून्य, शून्य, track_data_var_str);
	अगर (!var_field) अणु
		hist_err(tr, HIST_ERR_ONX_VAR_NOT_FOUND, errpos(track_data_var_str));
		वापस -EINVAL;
	पूर्ण

	ref_field = create_var_ref(hist_data, var_field, शून्य, शून्य);
	अगर (!ref_field)
		वापस -ENOMEM;

	data->track_data.var_ref = ref_field;

	अगर (data->handler == HANDLER_ONMAX)
		track_var = create_var(hist_data, file, "__max", माप(u64), "u64");
	अगर (IS_ERR(track_var)) अणु
		hist_err(tr, HIST_ERR_ONX_VAR_CREATE_FAIL, 0);
		ret = PTR_ERR(track_var);
		जाओ out;
	पूर्ण

	अगर (data->handler == HANDLER_ONCHANGE)
		track_var = create_var(hist_data, file, "__change", माप(u64), "u64");
	अगर (IS_ERR(track_var)) अणु
		hist_err(tr, HIST_ERR_ONX_VAR_CREATE_FAIL, 0);
		ret = PTR_ERR(track_var);
		जाओ out;
	पूर्ण
	data->track_data.track_var = track_var;

	ret = action_create(hist_data, data);
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक parse_action_params(काष्ठा trace_array *tr, अक्षर *params,
			       काष्ठा action_data *data)
अणु
	अक्षर *param, *saved_param;
	bool first_param = true;
	पूर्णांक ret = 0;

	जबतक (params) अणु
		अगर (data->n_params >= SYNTH_FIELDS_MAX) अणु
			hist_err(tr, HIST_ERR_TOO_MANY_PARAMS, 0);
			जाओ out;
		पूर्ण

		param = strsep(&params, ",");
		अगर (!param) अणु
			hist_err(tr, HIST_ERR_PARAM_NOT_FOUND, 0);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		param = म_मालाip(param);
		अगर (म_माप(param) < 2) अणु
			hist_err(tr, HIST_ERR_INVALID_PARAM, errpos(param));
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		saved_param = kstrdup(param, GFP_KERNEL);
		अगर (!saved_param) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (first_param && data->use_trace_keyword) अणु
			data->synth_event_name = saved_param;
			first_param = false;
			जारी;
		पूर्ण
		first_param = false;

		data->params[data->n_params++] = saved_param;
	पूर्ण
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक action_parse(काष्ठा trace_array *tr, अक्षर *str, काष्ठा action_data *data,
			क्रमागत handler_id handler)
अणु
	अक्षर *action_name;
	पूर्णांक ret = 0;

	strsep(&str, ".");
	अगर (!str) अणु
		hist_err(tr, HIST_ERR_ACTION_NOT_FOUND, 0);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	action_name = strsep(&str, "(");
	अगर (!action_name || !str) अणु
		hist_err(tr, HIST_ERR_ACTION_NOT_FOUND, 0);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (str_has_prefix(action_name, "save")) अणु
		अक्षर *params = strsep(&str, ")");

		अगर (!params) अणु
			hist_err(tr, HIST_ERR_NO_SAVE_PARAMS, 0);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ret = parse_action_params(tr, params, data);
		अगर (ret)
			जाओ out;

		अगर (handler == HANDLER_ONMAX)
			data->track_data.check_val = check_track_val_max;
		अन्यथा अगर (handler == HANDLER_ONCHANGE)
			data->track_data.check_val = check_track_val_changed;
		अन्यथा अणु
			hist_err(tr, HIST_ERR_ACTION_MISMATCH, errpos(action_name));
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		data->track_data.save_data = save_track_data_vars;
		data->fn = ontrack_action;
		data->action = ACTION_SAVE;
	पूर्ण अन्यथा अगर (str_has_prefix(action_name, "snapshot")) अणु
		अक्षर *params = strsep(&str, ")");

		अगर (!str) अणु
			hist_err(tr, HIST_ERR_NO_CLOSING_PAREN, errpos(params));
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (handler == HANDLER_ONMAX)
			data->track_data.check_val = check_track_val_max;
		अन्यथा अगर (handler == HANDLER_ONCHANGE)
			data->track_data.check_val = check_track_val_changed;
		अन्यथा अणु
			hist_err(tr, HIST_ERR_ACTION_MISMATCH, errpos(action_name));
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		data->track_data.save_data = save_track_data_snapshot;
		data->fn = ontrack_action;
		data->action = ACTION_SNAPSHOT;
	पूर्ण अन्यथा अणु
		अक्षर *params = strsep(&str, ")");

		अगर (str_has_prefix(action_name, "trace"))
			data->use_trace_keyword = true;

		अगर (params) अणु
			ret = parse_action_params(tr, params, data);
			अगर (ret)
				जाओ out;
		पूर्ण

		अगर (handler == HANDLER_ONMAX)
			data->track_data.check_val = check_track_val_max;
		अन्यथा अगर (handler == HANDLER_ONCHANGE)
			data->track_data.check_val = check_track_val_changed;

		अगर (handler != HANDLER_ONMATCH) अणु
			data->track_data.save_data = action_trace;
			data->fn = ontrack_action;
		पूर्ण अन्यथा
			data->fn = action_trace;

		data->action = ACTION_TRACE;
	पूर्ण

	data->action_name = kstrdup(action_name, GFP_KERNEL);
	अगर (!data->action_name) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	data->handler = handler;
 out:
	वापस ret;
पूर्ण

अटल काष्ठा action_data *track_data_parse(काष्ठा hist_trigger_data *hist_data,
					    अक्षर *str, क्रमागत handler_id handler)
अणु
	काष्ठा action_data *data;
	पूर्णांक ret = -EINVAL;
	अक्षर *var_str;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	var_str = strsep(&str, ")");
	अगर (!var_str || !str) अणु
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	data->track_data.var_str = kstrdup(var_str, GFP_KERNEL);
	अगर (!data->track_data.var_str) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	ret = action_parse(hist_data->event_file->tr, str, data, handler);
	अगर (ret)
		जाओ मुक्त;
 out:
	वापस data;
 मुक्त:
	track_data_destroy(hist_data, data);
	data = ERR_PTR(ret);
	जाओ out;
पूर्ण

अटल व्योम onmatch_destroy(काष्ठा action_data *data)
अणु
	kमुक्त(data->match_data.event);
	kमुक्त(data->match_data.event_प्रणाली);

	action_data_destroy(data);
पूर्ण

अटल व्योम destroy_field_var(काष्ठा field_var *field_var)
अणु
	अगर (!field_var)
		वापस;

	destroy_hist_field(field_var->var, 0);
	destroy_hist_field(field_var->val, 0);

	kमुक्त(field_var);
पूर्ण

अटल व्योम destroy_field_vars(काष्ठा hist_trigger_data *hist_data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_field_vars; i++)
		destroy_field_var(hist_data->field_vars[i]);

	क्रम (i = 0; i < hist_data->n_save_vars; i++)
		destroy_field_var(hist_data->save_vars[i]);
पूर्ण

अटल व्योम save_field_var(काष्ठा hist_trigger_data *hist_data,
			   काष्ठा field_var *field_var)
अणु
	hist_data->field_vars[hist_data->n_field_vars++] = field_var;

	अगर (field_var->val->flags & HIST_FIELD_FL_STRING)
		hist_data->n_field_var_str++;
पूर्ण


अटल पूर्णांक check_synth_field(काष्ठा synth_event *event,
			     काष्ठा hist_field *hist_field,
			     अचिन्हित पूर्णांक field_pos)
अणु
	काष्ठा synth_field *field;

	अगर (field_pos >= event->n_fields)
		वापस -EINVAL;

	field = event->fields[field_pos];

	/*
	 * A dynamic string synth field can accept अटल or
	 * dynamic. A अटल string synth field can only accept a
	 * same-sized अटल string, which is checked क्रम later.
	 */
	अगर (म_माला(hist_field->type, "char[") && field->is_string
	    && field->is_dynamic)
		वापस 0;

	अगर (म_भेद(field->type, hist_field->type) != 0) अणु
		अगर (field->size != hist_field->size ||
		    field->is_चिन्हित != hist_field->is_चिन्हित)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा hist_field *
trace_action_find_var(काष्ठा hist_trigger_data *hist_data,
		      काष्ठा action_data *data,
		      अक्षर *प्रणाली, अक्षर *event, अक्षर *var)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_field *hist_field;

	var++; /* skip '$' */

	hist_field = find_target_event_var(hist_data, प्रणाली, event, var);
	अगर (!hist_field) अणु
		अगर (!प्रणाली && data->handler == HANDLER_ONMATCH) अणु
			प्रणाली = data->match_data.event_प्रणाली;
			event = data->match_data.event;
		पूर्ण

		hist_field = find_event_var(hist_data, प्रणाली, event, var);
	पूर्ण

	अगर (!hist_field)
		hist_err(tr, HIST_ERR_PARAM_NOT_FOUND, errpos(var));

	वापस hist_field;
पूर्ण

अटल काष्ठा hist_field *
trace_action_create_field_var(काष्ठा hist_trigger_data *hist_data,
			      काष्ठा action_data *data, अक्षर *प्रणाली,
			      अक्षर *event, अक्षर *var)
अणु
	काष्ठा hist_field *hist_field = शून्य;
	काष्ठा field_var *field_var;

	/*
	 * First try to create a field var on the target event (the
	 * currently being defined).  This will create a variable क्रम
	 * unqualअगरied fields on the target event, or अगर qualअगरied,
	 * target fields that have qualअगरied names matching the target.
	 */
	field_var = create_target_field_var(hist_data, प्रणाली, event, var);

	अगर (field_var && !IS_ERR(field_var)) अणु
		save_field_var(hist_data, field_var);
		hist_field = field_var->var;
	पूर्ण अन्यथा अणु
		field_var = शून्य;
		/*
		 * If no explicit प्रणाली.event is specअगरied, शेष to
		 * looking क्रम fields on the onmatch(प्रणाली.event.xxx)
		 * event.
		 */
		अगर (!प्रणाली && data->handler == HANDLER_ONMATCH) अणु
			प्रणाली = data->match_data.event_प्रणाली;
			event = data->match_data.event;
		पूर्ण

		/*
		 * At this poपूर्णांक, we're looking at a field on another
		 * event.  Because we can't modअगरy a hist trigger on
		 * another event to add a variable क्रम a field, we need
		 * to create a new trigger on that event and create the
		 * variable at the same समय.
		 */
		hist_field = create_field_var_hist(hist_data, प्रणाली, event, var);
		अगर (IS_ERR(hist_field))
			जाओ मुक्त;
	पूर्ण
 out:
	वापस hist_field;
 मुक्त:
	destroy_field_var(field_var);
	hist_field = शून्य;
	जाओ out;
पूर्ण

अटल पूर्णांक trace_action_create(काष्ठा hist_trigger_data *hist_data,
			       काष्ठा action_data *data)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	अक्षर *event_name, *param, *प्रणाली = शून्य;
	काष्ठा hist_field *hist_field, *var_ref;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक field_pos = 0;
	काष्ठा synth_event *event;
	अक्षर *synth_event_name;
	पूर्णांक var_ref_idx, ret = 0;

	lockdep_निश्चित_held(&event_mutex);

	अगर (data->use_trace_keyword)
		synth_event_name = data->synth_event_name;
	अन्यथा
		synth_event_name = data->action_name;

	event = find_synth_event(synth_event_name);
	अगर (!event) अणु
		hist_err(tr, HIST_ERR_SYNTH_EVENT_NOT_FOUND, errpos(synth_event_name));
		वापस -EINVAL;
	पूर्ण

	event->ref++;

	क्रम (i = 0; i < data->n_params; i++) अणु
		अक्षर *p;

		p = param = kstrdup(data->params[i], GFP_KERNEL);
		अगर (!param) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		प्रणाली = strsep(&param, ".");
		अगर (!param) अणु
			param = (अक्षर *)प्रणाली;
			प्रणाली = event_name = शून्य;
		पूर्ण अन्यथा अणु
			event_name = strsep(&param, ".");
			अगर (!param) अणु
				kमुक्त(p);
				ret = -EINVAL;
				जाओ err;
			पूर्ण
		पूर्ण

		अगर (param[0] == '$')
			hist_field = trace_action_find_var(hist_data, data,
							   प्रणाली, event_name,
							   param);
		अन्यथा
			hist_field = trace_action_create_field_var(hist_data,
								   data,
								   प्रणाली,
								   event_name,
								   param);

		अगर (!hist_field) अणु
			kमुक्त(p);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (check_synth_field(event, hist_field, field_pos) == 0) अणु
			var_ref = create_var_ref(hist_data, hist_field,
						 प्रणाली, event_name);
			अगर (!var_ref) अणु
				kमुक्त(p);
				ret = -ENOMEM;
				जाओ err;
			पूर्ण

			var_ref_idx = find_var_ref_idx(hist_data, var_ref);
			अगर (WARN_ON(var_ref_idx < 0)) अणु
				ret = var_ref_idx;
				जाओ err;
			पूर्ण

			data->var_ref_idx[i] = var_ref_idx;

			field_pos++;
			kमुक्त(p);
			जारी;
		पूर्ण

		hist_err(tr, HIST_ERR_SYNTH_TYPE_MISMATCH, errpos(param));
		kमुक्त(p);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (field_pos != event->n_fields) अणु
		hist_err(tr, HIST_ERR_SYNTH_COUNT_MISMATCH, errpos(event->name));
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	data->synth_event = event;
 out:
	वापस ret;
 err:
	event->ref--;

	जाओ out;
पूर्ण

अटल पूर्णांक action_create(काष्ठा hist_trigger_data *hist_data,
			 काष्ठा action_data *data)
अणु
	काष्ठा trace_event_file *file = hist_data->event_file;
	काष्ठा trace_array *tr = file->tr;
	काष्ठा track_data *track_data;
	काष्ठा field_var *field_var;
	अचिन्हित पूर्णांक i;
	अक्षर *param;
	पूर्णांक ret = 0;

	अगर (data->action == ACTION_TRACE)
		वापस trace_action_create(hist_data, data);

	अगर (data->action == ACTION_SNAPSHOT) अणु
		track_data = track_data_alloc(hist_data->key_size, data, hist_data);
		अगर (IS_ERR(track_data)) अणु
			ret = PTR_ERR(track_data);
			जाओ out;
		पूर्ण

		ret = tracing_snapshot_cond_enable(file->tr, track_data,
						   cond_snapshot_update);
		अगर (ret)
			track_data_मुक्त(track_data);

		जाओ out;
	पूर्ण

	अगर (data->action == ACTION_SAVE) अणु
		अगर (hist_data->n_save_vars) अणु
			ret = -EEXIST;
			hist_err(tr, HIST_ERR_TOO_MANY_SAVE_ACTIONS, 0);
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < data->n_params; i++) अणु
			param = kstrdup(data->params[i], GFP_KERNEL);
			अगर (!param) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			field_var = create_target_field_var(hist_data, शून्य, शून्य, param);
			अगर (IS_ERR(field_var)) अणु
				hist_err(tr, HIST_ERR_FIELD_VAR_CREATE_FAIL,
					 errpos(param));
				ret = PTR_ERR(field_var);
				kमुक्त(param);
				जाओ out;
			पूर्ण

			hist_data->save_vars[hist_data->n_save_vars++] = field_var;
			अगर (field_var->val->flags & HIST_FIELD_FL_STRING)
				hist_data->n_save_var_str++;
			kमुक्त(param);
		पूर्ण
	पूर्ण
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक onmatch_create(काष्ठा hist_trigger_data *hist_data,
			  काष्ठा action_data *data)
अणु
	वापस action_create(hist_data, data);
पूर्ण

अटल काष्ठा action_data *onmatch_parse(काष्ठा trace_array *tr, अक्षर *str)
अणु
	अक्षर *match_event, *match_event_प्रणाली;
	काष्ठा action_data *data;
	पूर्णांक ret = -EINVAL;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	match_event = strsep(&str, ")");
	अगर (!match_event || !str) अणु
		hist_err(tr, HIST_ERR_NO_CLOSING_PAREN, errpos(match_event));
		जाओ मुक्त;
	पूर्ण

	match_event_प्रणाली = strsep(&match_event, ".");
	अगर (!match_event) अणु
		hist_err(tr, HIST_ERR_SUBSYS_NOT_FOUND, errpos(match_event_प्रणाली));
		जाओ मुक्त;
	पूर्ण

	अगर (IS_ERR(event_file(tr, match_event_प्रणाली, match_event))) अणु
		hist_err(tr, HIST_ERR_INVALID_SUBSYS_EVENT, errpos(match_event));
		जाओ मुक्त;
	पूर्ण

	data->match_data.event = kstrdup(match_event, GFP_KERNEL);
	अगर (!data->match_data.event) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	data->match_data.event_प्रणाली = kstrdup(match_event_प्रणाली, GFP_KERNEL);
	अगर (!data->match_data.event_प्रणाली) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	ret = action_parse(tr, str, data, HANDLER_ONMATCH);
	अगर (ret)
		जाओ मुक्त;
 out:
	वापस data;
 मुक्त:
	onmatch_destroy(data);
	data = ERR_PTR(ret);
	जाओ out;
पूर्ण

अटल पूर्णांक create_hitcount_val(काष्ठा hist_trigger_data *hist_data)
अणु
	hist_data->fields[HITCOUNT_IDX] =
		create_hist_field(hist_data, शून्य, HIST_FIELD_FL_HITCOUNT, शून्य);
	अगर (!hist_data->fields[HITCOUNT_IDX])
		वापस -ENOMEM;

	hist_data->n_vals++;
	hist_data->n_fields++;

	अगर (WARN_ON(hist_data->n_vals > TRACING_MAP_VALS_MAX))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __create_val_field(काष्ठा hist_trigger_data *hist_data,
			      अचिन्हित पूर्णांक val_idx,
			      काष्ठा trace_event_file *file,
			      अक्षर *var_name, अक्षर *field_str,
			      अचिन्हित दीर्घ flags)
अणु
	काष्ठा hist_field *hist_field;
	पूर्णांक ret = 0;

	hist_field = parse_expr(hist_data, file, field_str, flags, var_name, 0);
	अगर (IS_ERR(hist_field)) अणु
		ret = PTR_ERR(hist_field);
		जाओ out;
	पूर्ण

	hist_data->fields[val_idx] = hist_field;

	++hist_data->n_vals;
	++hist_data->n_fields;

	अगर (WARN_ON(hist_data->n_vals > TRACING_MAP_VALS_MAX + TRACING_MAP_VARS_MAX))
		ret = -EINVAL;
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक create_val_field(काष्ठा hist_trigger_data *hist_data,
			    अचिन्हित पूर्णांक val_idx,
			    काष्ठा trace_event_file *file,
			    अक्षर *field_str)
अणु
	अगर (WARN_ON(val_idx >= TRACING_MAP_VALS_MAX))
		वापस -EINVAL;

	वापस __create_val_field(hist_data, val_idx, file, शून्य, field_str, 0);
पूर्ण

अटल पूर्णांक create_var_field(काष्ठा hist_trigger_data *hist_data,
			    अचिन्हित पूर्णांक val_idx,
			    काष्ठा trace_event_file *file,
			    अक्षर *var_name, अक्षर *expr_str)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	अगर (WARN_ON(val_idx >= TRACING_MAP_VALS_MAX + TRACING_MAP_VARS_MAX))
		वापस -EINVAL;

	अगर (find_var(hist_data, file, var_name) && !hist_data->हटाओ) अणु
		hist_err(tr, HIST_ERR_DUPLICATE_VAR, errpos(var_name));
		वापस -EINVAL;
	पूर्ण

	flags |= HIST_FIELD_FL_VAR;
	hist_data->n_vars++;
	अगर (WARN_ON(hist_data->n_vars > TRACING_MAP_VARS_MAX))
		वापस -EINVAL;

	ret = __create_val_field(hist_data, val_idx, file, var_name, expr_str, flags);

	अगर (!ret && hist_data->fields[val_idx]->flags & HIST_FIELD_FL_STRING)
		hist_data->fields[val_idx]->var_str_idx = hist_data->n_var_str++;

	वापस ret;
पूर्ण

अटल पूर्णांक create_val_fields(काष्ठा hist_trigger_data *hist_data,
			     काष्ठा trace_event_file *file)
अणु
	अक्षर *fields_str, *field_str;
	अचिन्हित पूर्णांक i, j = 1;
	पूर्णांक ret;

	ret = create_hitcount_val(hist_data);
	अगर (ret)
		जाओ out;

	fields_str = hist_data->attrs->vals_str;
	अगर (!fields_str)
		जाओ out;

	क्रम (i = 0, j = 1; i < TRACING_MAP_VALS_MAX &&
		     j < TRACING_MAP_VALS_MAX; i++) अणु
		field_str = strsep(&fields_str, ",");
		अगर (!field_str)
			अवरोध;

		अगर (म_भेद(field_str, "hitcount") == 0)
			जारी;

		ret = create_val_field(hist_data, j++, file, field_str);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (fields_str && (म_भेद(fields_str, "hitcount") != 0))
		ret = -EINVAL;
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक create_key_field(काष्ठा hist_trigger_data *hist_data,
			    अचिन्हित पूर्णांक key_idx,
			    अचिन्हित पूर्णांक key_offset,
			    काष्ठा trace_event_file *file,
			    अक्षर *field_str)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा hist_field *hist_field = शून्य;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक key_size;
	पूर्णांक ret = 0;

	अगर (WARN_ON(key_idx >= HIST_FIELDS_MAX))
		वापस -EINVAL;

	flags |= HIST_FIELD_FL_KEY;

	अगर (म_भेद(field_str, "stacktrace") == 0) अणु
		flags |= HIST_FIELD_FL_STACKTRACE;
		key_size = माप(अचिन्हित दीर्घ) * HIST_STACKTRACE_DEPTH;
		hist_field = create_hist_field(hist_data, शून्य, flags, शून्य);
	पूर्ण अन्यथा अणु
		hist_field = parse_expr(hist_data, file, field_str, flags,
					शून्य, 0);
		अगर (IS_ERR(hist_field)) अणु
			ret = PTR_ERR(hist_field);
			जाओ out;
		पूर्ण

		अगर (field_has_hist_vars(hist_field, 0))	अणु
			hist_err(tr, HIST_ERR_INVALID_REF_KEY, errpos(field_str));
			destroy_hist_field(hist_field, 0);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		key_size = hist_field->size;
	पूर्ण

	hist_data->fields[key_idx] = hist_field;

	key_size = ALIGN(key_size, माप(u64));
	hist_data->fields[key_idx]->size = key_size;
	hist_data->fields[key_idx]->offset = key_offset;

	hist_data->key_size += key_size;

	अगर (hist_data->key_size > HIST_KEY_SIZE_MAX) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hist_data->n_keys++;
	hist_data->n_fields++;

	अगर (WARN_ON(hist_data->n_keys > TRACING_MAP_KEYS_MAX))
		वापस -EINVAL;

	ret = key_size;
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक create_key_fields(काष्ठा hist_trigger_data *hist_data,
			     काष्ठा trace_event_file *file)
अणु
	अचिन्हित पूर्णांक i, key_offset = 0, n_vals = hist_data->n_vals;
	अक्षर *fields_str, *field_str;
	पूर्णांक ret = -EINVAL;

	fields_str = hist_data->attrs->keys_str;
	अगर (!fields_str)
		जाओ out;

	क्रम (i = n_vals; i < n_vals + TRACING_MAP_KEYS_MAX; i++) अणु
		field_str = strsep(&fields_str, ",");
		अगर (!field_str)
			अवरोध;
		ret = create_key_field(hist_data, i, key_offset,
				       file, field_str);
		अगर (ret < 0)
			जाओ out;
		key_offset += ret;
	पूर्ण
	अगर (fields_str) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = 0;
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक create_var_fields(काष्ठा hist_trigger_data *hist_data,
			     काष्ठा trace_event_file *file)
अणु
	अचिन्हित पूर्णांक i, j = hist_data->n_vals;
	पूर्णांक ret = 0;

	अचिन्हित पूर्णांक n_vars = hist_data->attrs->var_defs.n_vars;

	क्रम (i = 0; i < n_vars; i++) अणु
		अक्षर *var_name = hist_data->attrs->var_defs.name[i];
		अक्षर *expr = hist_data->attrs->var_defs.expr[i];

		ret = create_var_field(hist_data, j++, file, var_name, expr);
		अगर (ret)
			जाओ out;
	पूर्ण
 out:
	वापस ret;
पूर्ण

अटल व्योम मुक्त_var_defs(काष्ठा hist_trigger_data *hist_data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->attrs->var_defs.n_vars; i++) अणु
		kमुक्त(hist_data->attrs->var_defs.name[i]);
		kमुक्त(hist_data->attrs->var_defs.expr[i]);
	पूर्ण

	hist_data->attrs->var_defs.n_vars = 0;
पूर्ण

अटल पूर्णांक parse_var_defs(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	अक्षर *s, *str, *var_name, *field_str;
	अचिन्हित पूर्णांक i, j, n_vars = 0;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < hist_data->attrs->n_assignments; i++) अणु
		str = hist_data->attrs->assignment_str[i];
		क्रम (j = 0; j < TRACING_MAP_VARS_MAX; j++) अणु
			field_str = strsep(&str, ",");
			अगर (!field_str)
				अवरोध;

			var_name = strsep(&field_str, "=");
			अगर (!var_name || !field_str) अणु
				hist_err(tr, HIST_ERR_MALFORMED_ASSIGNMENT,
					 errpos(var_name));
				ret = -EINVAL;
				जाओ मुक्त;
			पूर्ण

			अगर (n_vars == TRACING_MAP_VARS_MAX) अणु
				hist_err(tr, HIST_ERR_TOO_MANY_VARS, errpos(var_name));
				ret = -EINVAL;
				जाओ मुक्त;
			पूर्ण

			s = kstrdup(var_name, GFP_KERNEL);
			अगर (!s) अणु
				ret = -ENOMEM;
				जाओ मुक्त;
			पूर्ण
			hist_data->attrs->var_defs.name[n_vars] = s;

			s = kstrdup(field_str, GFP_KERNEL);
			अगर (!s) अणु
				ret = -ENOMEM;
				जाओ मुक्त;
			पूर्ण
			hist_data->attrs->var_defs.expr[n_vars++] = s;

			hist_data->attrs->var_defs.n_vars = n_vars;
		पूर्ण
	पूर्ण

	वापस ret;
 मुक्त:
	मुक्त_var_defs(hist_data);

	वापस ret;
पूर्ण

अटल पूर्णांक create_hist_fields(काष्ठा hist_trigger_data *hist_data,
			      काष्ठा trace_event_file *file)
अणु
	पूर्णांक ret;

	ret = parse_var_defs(hist_data);
	अगर (ret)
		जाओ out;

	ret = create_val_fields(hist_data, file);
	अगर (ret)
		जाओ out;

	ret = create_var_fields(hist_data, file);
	अगर (ret)
		जाओ out;

	ret = create_key_fields(hist_data, file);
	अगर (ret)
		जाओ out;
 out:
	मुक्त_var_defs(hist_data);

	वापस ret;
पूर्ण

अटल पूर्णांक is_descending(काष्ठा trace_array *tr, स्थिर अक्षर *str)
अणु
	अगर (!str)
		वापस 0;

	अगर (म_भेद(str, "descending") == 0)
		वापस 1;

	अगर (म_भेद(str, "ascending") == 0)
		वापस 0;

	hist_err(tr, HIST_ERR_INVALID_SORT_MODIFIER, errpos((अक्षर *)str));

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक create_sort_keys(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	अक्षर *fields_str = hist_data->attrs->sort_key_str;
	काष्ठा tracing_map_sort_key *sort_key;
	पूर्णांक descending, ret = 0;
	अचिन्हित पूर्णांक i, j, k;

	hist_data->n_sort_keys = 1; /* we always have at least one, hitcount */

	अगर (!fields_str)
		जाओ out;

	क्रम (i = 0; i < TRACING_MAP_SORT_KEYS_MAX; i++) अणु
		काष्ठा hist_field *hist_field;
		अक्षर *field_str, *field_name;
		स्थिर अक्षर *test_name;

		sort_key = &hist_data->sort_keys[i];

		field_str = strsep(&fields_str, ",");
		अगर (!field_str)
			अवरोध;

		अगर (!*field_str) अणु
			ret = -EINVAL;
			hist_err(tr, HIST_ERR_EMPTY_SORT_FIELD, errpos("sort="));
			अवरोध;
		पूर्ण

		अगर ((i == TRACING_MAP_SORT_KEYS_MAX - 1) && fields_str) अणु
			hist_err(tr, HIST_ERR_TOO_MANY_SORT_FIELDS, errpos("sort="));
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		field_name = strsep(&field_str, ".");
		अगर (!field_name || !*field_name) अणु
			ret = -EINVAL;
			hist_err(tr, HIST_ERR_EMPTY_SORT_FIELD, errpos("sort="));
			अवरोध;
		पूर्ण

		अगर (म_भेद(field_name, "hitcount") == 0) अणु
			descending = is_descending(tr, field_str);
			अगर (descending < 0) अणु
				ret = descending;
				अवरोध;
			पूर्ण
			sort_key->descending = descending;
			जारी;
		पूर्ण

		क्रम (j = 1, k = 1; j < hist_data->n_fields; j++) अणु
			अचिन्हित पूर्णांक idx;

			hist_field = hist_data->fields[j];
			अगर (hist_field->flags & HIST_FIELD_FL_VAR)
				जारी;

			idx = k++;

			test_name = hist_field_name(hist_field, 0);

			अगर (म_भेद(field_name, test_name) == 0) अणु
				sort_key->field_idx = idx;
				descending = is_descending(tr, field_str);
				अगर (descending < 0) अणु
					ret = descending;
					जाओ out;
				पूर्ण
				sort_key->descending = descending;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (j == hist_data->n_fields) अणु
			ret = -EINVAL;
			hist_err(tr, HIST_ERR_INVALID_SORT_FIELD, errpos(field_name));
			अवरोध;
		पूर्ण
	पूर्ण

	hist_data->n_sort_keys = i;
 out:
	वापस ret;
पूर्ण

अटल व्योम destroy_actions(काष्ठा hist_trigger_data *hist_data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		काष्ठा action_data *data = hist_data->actions[i];

		अगर (data->handler == HANDLER_ONMATCH)
			onmatch_destroy(data);
		अन्यथा अगर (data->handler == HANDLER_ONMAX ||
			 data->handler == HANDLER_ONCHANGE)
			track_data_destroy(hist_data, data);
		अन्यथा
			kमुक्त(data);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_actions(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_array *tr = hist_data->event_file->tr;
	काष्ठा action_data *data;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;
	अक्षर *str;
	पूर्णांक len;

	क्रम (i = 0; i < hist_data->attrs->n_actions; i++) अणु
		str = hist_data->attrs->action_str[i];

		अगर ((len = str_has_prefix(str, "onmatch("))) अणु
			अक्षर *action_str = str + len;

			data = onmatch_parse(tr, action_str);
			अगर (IS_ERR(data)) अणु
				ret = PTR_ERR(data);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((len = str_has_prefix(str, "onmax("))) अणु
			अक्षर *action_str = str + len;

			data = track_data_parse(hist_data, action_str,
						HANDLER_ONMAX);
			अगर (IS_ERR(data)) अणु
				ret = PTR_ERR(data);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((len = str_has_prefix(str, "onchange("))) अणु
			अक्षर *action_str = str + len;

			data = track_data_parse(hist_data, action_str,
						HANDLER_ONCHANGE);
			अगर (IS_ERR(data)) अणु
				ret = PTR_ERR(data);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		hist_data->actions[hist_data->n_actions++] = data;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक create_actions(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा action_data *data;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < hist_data->attrs->n_actions; i++) अणु
		data = hist_data->actions[i];

		अगर (data->handler == HANDLER_ONMATCH) अणु
			ret = onmatch_create(hist_data, data);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अगर (data->handler == HANDLER_ONMAX ||
			   data->handler == HANDLER_ONCHANGE) अणु
			ret = track_data_create(hist_data, data);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम prपूर्णांक_actions(काष्ठा seq_file *m,
			  काष्ठा hist_trigger_data *hist_data,
			  काष्ठा tracing_map_elt *elt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		काष्ठा action_data *data = hist_data->actions[i];

		अगर (data->action == ACTION_SNAPSHOT)
			जारी;

		अगर (data->handler == HANDLER_ONMAX ||
		    data->handler == HANDLER_ONCHANGE)
			track_data_prपूर्णांक(m, hist_data, elt, data);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_action_spec(काष्ठा seq_file *m,
			      काष्ठा hist_trigger_data *hist_data,
			      काष्ठा action_data *data)
अणु
	अचिन्हित पूर्णांक i;

	अगर (data->action == ACTION_SAVE) अणु
		क्रम (i = 0; i < hist_data->n_save_vars; i++) अणु
			seq_म_लिखो(m, "%s", hist_data->save_vars[i]->var->var.name);
			अगर (i < hist_data->n_save_vars - 1)
				seq_माला_दो(m, ",");
		पूर्ण
	पूर्ण अन्यथा अगर (data->action == ACTION_TRACE) अणु
		अगर (data->use_trace_keyword)
			seq_म_लिखो(m, "%s", data->synth_event_name);
		क्रम (i = 0; i < data->n_params; i++) अणु
			अगर (i || data->use_trace_keyword)
				seq_माला_दो(m, ",");
			seq_म_लिखो(m, "%s", data->params[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_track_data_spec(काष्ठा seq_file *m,
				  काष्ठा hist_trigger_data *hist_data,
				  काष्ठा action_data *data)
अणु
	अगर (data->handler == HANDLER_ONMAX)
		seq_माला_दो(m, ":onmax(");
	अन्यथा अगर (data->handler == HANDLER_ONCHANGE)
		seq_माला_दो(m, ":onchange(");
	seq_म_लिखो(m, "%s", data->track_data.var_str);
	seq_म_लिखो(m, ").%s(", data->action_name);

	prपूर्णांक_action_spec(m, hist_data, data);

	seq_माला_दो(m, ")");
पूर्ण

अटल व्योम prपूर्णांक_onmatch_spec(काष्ठा seq_file *m,
			       काष्ठा hist_trigger_data *hist_data,
			       काष्ठा action_data *data)
अणु
	seq_म_लिखो(m, ":onmatch(%s.%s).", data->match_data.event_प्रणाली,
		   data->match_data.event);

	seq_म_लिखो(m, "%s(", data->action_name);

	prपूर्णांक_action_spec(m, hist_data, data);

	seq_माला_दो(m, ")");
पूर्ण

अटल bool actions_match(काष्ठा hist_trigger_data *hist_data,
			  काष्ठा hist_trigger_data *hist_data_test)
अणु
	अचिन्हित पूर्णांक i, j;

	अगर (hist_data->n_actions != hist_data_test->n_actions)
		वापस false;

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		काष्ठा action_data *data = hist_data->actions[i];
		काष्ठा action_data *data_test = hist_data_test->actions[i];
		अक्षर *action_name, *action_name_test;

		अगर (data->handler != data_test->handler)
			वापस false;
		अगर (data->action != data_test->action)
			वापस false;

		अगर (data->n_params != data_test->n_params)
			वापस false;

		क्रम (j = 0; j < data->n_params; j++) अणु
			अगर (म_भेद(data->params[j], data_test->params[j]) != 0)
				वापस false;
		पूर्ण

		अगर (data->use_trace_keyword)
			action_name = data->synth_event_name;
		अन्यथा
			action_name = data->action_name;

		अगर (data_test->use_trace_keyword)
			action_name_test = data_test->synth_event_name;
		अन्यथा
			action_name_test = data_test->action_name;

		अगर (म_भेद(action_name, action_name_test) != 0)
			वापस false;

		अगर (data->handler == HANDLER_ONMATCH) अणु
			अगर (म_भेद(data->match_data.event_प्रणाली,
				   data_test->match_data.event_प्रणाली) != 0)
				वापस false;
			अगर (म_भेद(data->match_data.event,
				   data_test->match_data.event) != 0)
				वापस false;
		पूर्ण अन्यथा अगर (data->handler == HANDLER_ONMAX ||
			   data->handler == HANDLER_ONCHANGE) अणु
			अगर (म_भेद(data->track_data.var_str,
				   data_test->track_data.var_str) != 0)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण


अटल व्योम prपूर्णांक_actions_spec(काष्ठा seq_file *m,
			       काष्ठा hist_trigger_data *hist_data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		काष्ठा action_data *data = hist_data->actions[i];

		अगर (data->handler == HANDLER_ONMATCH)
			prपूर्णांक_onmatch_spec(m, hist_data, data);
		अन्यथा अगर (data->handler == HANDLER_ONMAX ||
			 data->handler == HANDLER_ONCHANGE)
			prपूर्णांक_track_data_spec(m, hist_data, data);
	पूर्ण
पूर्ण

अटल व्योम destroy_field_var_hists(काष्ठा hist_trigger_data *hist_data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_field_var_hists; i++) अणु
		kमुक्त(hist_data->field_var_hists[i]->cmd);
		kमुक्त(hist_data->field_var_hists[i]);
	पूर्ण
पूर्ण

अटल व्योम destroy_hist_data(काष्ठा hist_trigger_data *hist_data)
अणु
	अगर (!hist_data)
		वापस;

	destroy_hist_trigger_attrs(hist_data->attrs);
	destroy_hist_fields(hist_data);
	tracing_map_destroy(hist_data->map);

	destroy_actions(hist_data);
	destroy_field_vars(hist_data);
	destroy_field_var_hists(hist_data);

	kमुक्त(hist_data);
पूर्ण

अटल पूर्णांक create_tracing_map_fields(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा tracing_map *map = hist_data->map;
	काष्ठा ftrace_event_field *field;
	काष्ठा hist_field *hist_field;
	पूर्णांक i, idx = 0;

	क्रम_each_hist_field(i, hist_data) अणु
		hist_field = hist_data->fields[i];
		अगर (hist_field->flags & HIST_FIELD_FL_KEY) अणु
			tracing_map_cmp_fn_t cmp_fn;

			field = hist_field->field;

			अगर (hist_field->flags & HIST_FIELD_FL_STACKTRACE)
				cmp_fn = tracing_map_cmp_none;
			अन्यथा अगर (!field)
				cmp_fn = tracing_map_cmp_num(hist_field->size,
							     hist_field->is_चिन्हित);
			अन्यथा अगर (is_string_field(field))
				cmp_fn = tracing_map_cmp_string;
			अन्यथा
				cmp_fn = tracing_map_cmp_num(field->size,
							     field->is_चिन्हित);
			idx = tracing_map_add_key_field(map,
							hist_field->offset,
							cmp_fn);
		पूर्ण अन्यथा अगर (!(hist_field->flags & HIST_FIELD_FL_VAR))
			idx = tracing_map_add_sum_field(map);

		अगर (idx < 0)
			वापस idx;

		अगर (hist_field->flags & HIST_FIELD_FL_VAR) अणु
			idx = tracing_map_add_var(map);
			अगर (idx < 0)
				वापस idx;
			hist_field->var.idx = idx;
			hist_field->var.hist_data = hist_data;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा hist_trigger_data *
create_hist_data(अचिन्हित पूर्णांक map_bits,
		 काष्ठा hist_trigger_attrs *attrs,
		 काष्ठा trace_event_file *file,
		 bool हटाओ)
अणु
	स्थिर काष्ठा tracing_map_ops *map_ops = शून्य;
	काष्ठा hist_trigger_data *hist_data;
	पूर्णांक ret = 0;

	hist_data = kzalloc(माप(*hist_data), GFP_KERNEL);
	अगर (!hist_data)
		वापस ERR_PTR(-ENOMEM);

	hist_data->attrs = attrs;
	hist_data->हटाओ = हटाओ;
	hist_data->event_file = file;

	ret = parse_actions(hist_data);
	अगर (ret)
		जाओ मुक्त;

	ret = create_hist_fields(hist_data, file);
	अगर (ret)
		जाओ मुक्त;

	ret = create_sort_keys(hist_data);
	अगर (ret)
		जाओ मुक्त;

	map_ops = &hist_trigger_elt_data_ops;

	hist_data->map = tracing_map_create(map_bits, hist_data->key_size,
					    map_ops, hist_data);
	अगर (IS_ERR(hist_data->map)) अणु
		ret = PTR_ERR(hist_data->map);
		hist_data->map = शून्य;
		जाओ मुक्त;
	पूर्ण

	ret = create_tracing_map_fields(hist_data);
	अगर (ret)
		जाओ मुक्त;
 out:
	वापस hist_data;
 मुक्त:
	hist_data->attrs = शून्य;

	destroy_hist_data(hist_data);

	hist_data = ERR_PTR(ret);

	जाओ out;
पूर्ण

अटल व्योम hist_trigger_elt_update(काष्ठा hist_trigger_data *hist_data,
				    काष्ठा tracing_map_elt *elt,
				    काष्ठा trace_buffer *buffer, व्योम *rec,
				    काष्ठा ring_buffer_event *rbe,
				    u64 *var_ref_vals)
अणु
	काष्ठा hist_elt_data *elt_data;
	काष्ठा hist_field *hist_field;
	अचिन्हित पूर्णांक i, var_idx;
	u64 hist_val;

	elt_data = elt->निजी_data;
	elt_data->var_ref_vals = var_ref_vals;

	क्रम_each_hist_val_field(i, hist_data) अणु
		hist_field = hist_data->fields[i];
		hist_val = hist_field->fn(hist_field, elt, buffer, rbe, rec);
		अगर (hist_field->flags & HIST_FIELD_FL_VAR) अणु
			var_idx = hist_field->var.idx;

			अगर (hist_field->flags & HIST_FIELD_FL_STRING) अणु
				अचिन्हित पूर्णांक str_start, var_str_idx, idx;
				अक्षर *str, *val_str;

				str_start = hist_data->n_field_var_str +
					hist_data->n_save_var_str;
				var_str_idx = hist_field->var_str_idx;
				idx = str_start + var_str_idx;

				str = elt_data->field_var_str[idx];
				val_str = (अक्षर *)(uपूर्णांकptr_t)hist_val;
				strscpy(str, val_str, STR_VAR_LEN_MAX);

				hist_val = (u64)(uपूर्णांकptr_t)str;
			पूर्ण
			tracing_map_set_var(elt, var_idx, hist_val);
			जारी;
		पूर्ण
		tracing_map_update_sum(elt, i, hist_val);
	पूर्ण

	क्रम_each_hist_key_field(i, hist_data) अणु
		hist_field = hist_data->fields[i];
		अगर (hist_field->flags & HIST_FIELD_FL_VAR) अणु
			hist_val = hist_field->fn(hist_field, elt, buffer, rbe, rec);
			var_idx = hist_field->var.idx;
			tracing_map_set_var(elt, var_idx, hist_val);
		पूर्ण
	पूर्ण

	update_field_vars(hist_data, elt, buffer, rbe, rec);
पूर्ण

अटल अंतरभूत व्योम add_to_key(अक्षर *compound_key, व्योम *key,
			      काष्ठा hist_field *key_field, व्योम *rec)
अणु
	माप_प्रकार size = key_field->size;

	अगर (key_field->flags & HIST_FIELD_FL_STRING) अणु
		काष्ठा ftrace_event_field *field;

		field = key_field->field;
		अगर (field->filter_type == FILTER_DYN_STRING)
			size = *(u32 *)(rec + field->offset) >> 16;
		अन्यथा अगर (field->filter_type == FILTER_PTR_STRING)
			size = म_माप(key);
		अन्यथा अगर (field->filter_type == FILTER_STATIC_STRING)
			size = field->size;

		/* ensure शून्य-termination */
		अगर (size > key_field->size - 1)
			size = key_field->size - 1;

		म_नकलन(compound_key + key_field->offset, (अक्षर *)key, size);
	पूर्ण अन्यथा
		स_नकल(compound_key + key_field->offset, key, size);
पूर्ण

अटल व्योम
hist_trigger_actions(काष्ठा hist_trigger_data *hist_data,
		     काष्ठा tracing_map_elt *elt,
		     काष्ठा trace_buffer *buffer, व्योम *rec,
		     काष्ठा ring_buffer_event *rbe, व्योम *key,
		     u64 *var_ref_vals)
अणु
	काष्ठा action_data *data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		data = hist_data->actions[i];
		data->fn(hist_data, elt, buffer, rec, rbe, key, data, var_ref_vals);
	पूर्ण
पूर्ण

अटल व्योम event_hist_trigger(काष्ठा event_trigger_data *data,
			       काष्ठा trace_buffer *buffer, व्योम *rec,
			       काष्ठा ring_buffer_event *rbe)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;
	bool use_compound_key = (hist_data->n_keys > 1);
	अचिन्हित दीर्घ entries[HIST_STACKTRACE_DEPTH];
	u64 var_ref_vals[TRACING_MAP_VARS_MAX];
	अक्षर compound_key[HIST_KEY_SIZE_MAX];
	काष्ठा tracing_map_elt *elt = शून्य;
	काष्ठा hist_field *key_field;
	u64 field_contents;
	व्योम *key = शून्य;
	अचिन्हित पूर्णांक i;

	स_रखो(compound_key, 0, hist_data->key_size);

	क्रम_each_hist_key_field(i, hist_data) अणु
		key_field = hist_data->fields[i];

		अगर (key_field->flags & HIST_FIELD_FL_STACKTRACE) अणु
			स_रखो(entries, 0, HIST_STACKTRACE_SIZE);
			stack_trace_save(entries, HIST_STACKTRACE_DEPTH,
					 HIST_STACKTRACE_SKIP);
			key = entries;
		पूर्ण अन्यथा अणु
			field_contents = key_field->fn(key_field, elt, buffer, rbe, rec);
			अगर (key_field->flags & HIST_FIELD_FL_STRING) अणु
				key = (व्योम *)(अचिन्हित दीर्घ)field_contents;
				use_compound_key = true;
			पूर्ण अन्यथा
				key = (व्योम *)&field_contents;
		पूर्ण

		अगर (use_compound_key)
			add_to_key(compound_key, key, key_field, rec);
	पूर्ण

	अगर (use_compound_key)
		key = compound_key;

	अगर (hist_data->n_var_refs &&
	    !resolve_var_refs(hist_data, key, var_ref_vals, false))
		वापस;

	elt = tracing_map_insert(hist_data->map, key);
	अगर (!elt)
		वापस;

	hist_trigger_elt_update(hist_data, elt, buffer, rec, rbe, var_ref_vals);

	अगर (resolve_var_refs(hist_data, key, var_ref_vals, true))
		hist_trigger_actions(hist_data, elt, buffer, rec, rbe, key, var_ref_vals);
पूर्ण

अटल व्योम hist_trigger_stacktrace_prपूर्णांक(काष्ठा seq_file *m,
					  अचिन्हित दीर्घ *stacktrace_entries,
					  अचिन्हित पूर्णांक max_entries)
अणु
	अक्षर str[KSYM_SYMBOL_LEN];
	अचिन्हित पूर्णांक spaces = 8;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < max_entries; i++) अणु
		अगर (!stacktrace_entries[i])
			वापस;

		seq_म_लिखो(m, "%*c", 1 + spaces, ' ');
		sprपूर्णांक_symbol(str, stacktrace_entries[i]);
		seq_म_लिखो(m, "%s\n", str);
	पूर्ण
पूर्ण

अटल व्योम hist_trigger_prपूर्णांक_key(काष्ठा seq_file *m,
				   काष्ठा hist_trigger_data *hist_data,
				   व्योम *key,
				   काष्ठा tracing_map_elt *elt)
अणु
	काष्ठा hist_field *key_field;
	अक्षर str[KSYM_SYMBOL_LEN];
	bool multiline = false;
	स्थिर अक्षर *field_name;
	अचिन्हित पूर्णांक i;
	u64 uval;

	seq_माला_दो(m, "{ ");

	क्रम_each_hist_key_field(i, hist_data) अणु
		key_field = hist_data->fields[i];

		अगर (i > hist_data->n_vals)
			seq_माला_दो(m, ", ");

		field_name = hist_field_name(key_field, 0);

		अगर (key_field->flags & HIST_FIELD_FL_HEX) अणु
			uval = *(u64 *)(key + key_field->offset);
			seq_म_लिखो(m, "%s: %llx", field_name, uval);
		पूर्ण अन्यथा अगर (key_field->flags & HIST_FIELD_FL_SYM) अणु
			uval = *(u64 *)(key + key_field->offset);
			sprपूर्णांक_symbol_no_offset(str, uval);
			seq_म_लिखो(m, "%s: [%llx] %-45s", field_name,
				   uval, str);
		पूर्ण अन्यथा अगर (key_field->flags & HIST_FIELD_FL_SYM_OFFSET) अणु
			uval = *(u64 *)(key + key_field->offset);
			sprपूर्णांक_symbol(str, uval);
			seq_म_लिखो(m, "%s: [%llx] %-55s", field_name,
				   uval, str);
		पूर्ण अन्यथा अगर (key_field->flags & HIST_FIELD_FL_EXECNAME) अणु
			काष्ठा hist_elt_data *elt_data = elt->निजी_data;
			अक्षर *comm;

			अगर (WARN_ON_ONCE(!elt_data))
				वापस;

			comm = elt_data->comm;

			uval = *(u64 *)(key + key_field->offset);
			seq_म_लिखो(m, "%s: %-16s[%10llu]", field_name,
				   comm, uval);
		पूर्ण अन्यथा अगर (key_field->flags & HIST_FIELD_FL_SYSCALL) अणु
			स्थिर अक्षर *syscall_name;

			uval = *(u64 *)(key + key_field->offset);
			syscall_name = get_syscall_name(uval);
			अगर (!syscall_name)
				syscall_name = "unknown_syscall";

			seq_म_लिखो(m, "%s: %-30s[%3llu]", field_name,
				   syscall_name, uval);
		पूर्ण अन्यथा अगर (key_field->flags & HIST_FIELD_FL_STACKTRACE) अणु
			seq_माला_दो(m, "stacktrace:\n");
			hist_trigger_stacktrace_prपूर्णांक(m,
						      key + key_field->offset,
						      HIST_STACKTRACE_DEPTH);
			multiline = true;
		पूर्ण अन्यथा अगर (key_field->flags & HIST_FIELD_FL_LOG2) अणु
			seq_म_लिखो(m, "%s: ~ 2^%-2llu", field_name,
				   *(u64 *)(key + key_field->offset));
		पूर्ण अन्यथा अगर (key_field->flags & HIST_FIELD_FL_STRING) अणु
			seq_म_लिखो(m, "%s: %-50s", field_name,
				   (अक्षर *)(key + key_field->offset));
		पूर्ण अन्यथा अणु
			uval = *(u64 *)(key + key_field->offset);
			seq_म_लिखो(m, "%s: %10llu", field_name, uval);
		पूर्ण
	पूर्ण

	अगर (!multiline)
		seq_माला_दो(m, " ");

	seq_माला_दो(m, "}");
पूर्ण

अटल व्योम hist_trigger_entry_prपूर्णांक(काष्ठा seq_file *m,
				     काष्ठा hist_trigger_data *hist_data,
				     व्योम *key,
				     काष्ठा tracing_map_elt *elt)
अणु
	स्थिर अक्षर *field_name;
	अचिन्हित पूर्णांक i;

	hist_trigger_prपूर्णांक_key(m, hist_data, key, elt);

	seq_म_लिखो(m, " hitcount: %10llu",
		   tracing_map_पढ़ो_sum(elt, HITCOUNT_IDX));

	क्रम (i = 1; i < hist_data->n_vals; i++) अणु
		field_name = hist_field_name(hist_data->fields[i], 0);

		अगर (hist_data->fields[i]->flags & HIST_FIELD_FL_VAR ||
		    hist_data->fields[i]->flags & HIST_FIELD_FL_EXPR)
			जारी;

		अगर (hist_data->fields[i]->flags & HIST_FIELD_FL_HEX) अणु
			seq_म_लिखो(m, "  %s: %10llx", field_name,
				   tracing_map_पढ़ो_sum(elt, i));
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m, "  %s: %10llu", field_name,
				   tracing_map_पढ़ो_sum(elt, i));
		पूर्ण
	पूर्ण

	prपूर्णांक_actions(m, hist_data, elt);

	seq_माला_दो(m, "\n");
पूर्ण

अटल पूर्णांक prपूर्णांक_entries(काष्ठा seq_file *m,
			 काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा tracing_map_sort_entry **sort_entries = शून्य;
	काष्ठा tracing_map *map = hist_data->map;
	पूर्णांक i, n_entries;

	n_entries = tracing_map_sort_entries(map, hist_data->sort_keys,
					     hist_data->n_sort_keys,
					     &sort_entries);
	अगर (n_entries < 0)
		वापस n_entries;

	क्रम (i = 0; i < n_entries; i++)
		hist_trigger_entry_prपूर्णांक(m, hist_data,
					 sort_entries[i]->key,
					 sort_entries[i]->elt);

	tracing_map_destroy_sort_entries(sort_entries, n_entries);

	वापस n_entries;
पूर्ण

अटल व्योम hist_trigger_show(काष्ठा seq_file *m,
			      काष्ठा event_trigger_data *data, पूर्णांक n)
अणु
	काष्ठा hist_trigger_data *hist_data;
	पूर्णांक n_entries;

	अगर (n > 0)
		seq_माला_दो(m, "\n\n");

	seq_माला_दो(m, "# event histogram\n#\n# trigger info: ");
	data->ops->prपूर्णांक(m, data->ops, data);
	seq_माला_दो(m, "#\n\n");

	hist_data = data->निजी_data;
	n_entries = prपूर्णांक_entries(m, hist_data);
	अगर (n_entries < 0)
		n_entries = 0;

	track_data_snapshot_prपूर्णांक(m, hist_data);

	seq_म_लिखो(m, "\nTotals:\n    Hits: %llu\n    Entries: %u\n    Dropped: %llu\n",
		   (u64)atomic64_पढ़ो(&hist_data->map->hits),
		   n_entries, (u64)atomic64_पढ़ो(&hist_data->map->drops));
पूर्ण

अटल पूर्णांक hist_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा event_trigger_data *data;
	काष्ठा trace_event_file *event_file;
	पूर्णांक n = 0, ret = 0;

	mutex_lock(&event_mutex);

	event_file = event_file_data(m->निजी);
	अगर (unlikely(!event_file)) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	list_क्रम_each_entry(data, &event_file->triggers, list) अणु
		अगर (data->cmd_ops->trigger_type == ETT_EVENT_HIST)
			hist_trigger_show(m, data, n++);
	पूर्ण

 out_unlock:
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक event_hist_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	वापस single_खोलो(file, hist_show, file);
पूर्ण

स्थिर काष्ठा file_operations event_hist_fops = अणु
	.खोलो = event_hist_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

#अगर_घोषित CONFIG_HIST_TRIGGERS_DEBUG
अटल व्योम hist_field_debug_show_flags(काष्ठा seq_file *m,
					अचिन्हित दीर्घ flags)
अणु
	seq_माला_दो(m, "      flags:\n");

	अगर (flags & HIST_FIELD_FL_KEY)
		seq_माला_दो(m, "        HIST_FIELD_FL_KEY\n");
	अन्यथा अगर (flags & HIST_FIELD_FL_HITCOUNT)
		seq_माला_दो(m, "        VAL: HIST_FIELD_FL_HITCOUNT\n");
	अन्यथा अगर (flags & HIST_FIELD_FL_VAR)
		seq_माला_दो(m, "        HIST_FIELD_FL_VAR\n");
	अन्यथा अगर (flags & HIST_FIELD_FL_VAR_REF)
		seq_माला_दो(m, "        HIST_FIELD_FL_VAR_REF\n");
	अन्यथा
		seq_माला_दो(m, "        VAL: normal u64 value\n");

	अगर (flags & HIST_FIELD_FL_ALIAS)
		seq_माला_दो(m, "        HIST_FIELD_FL_ALIAS\n");
पूर्ण

अटल पूर्णांक hist_field_debug_show(काष्ठा seq_file *m,
				 काष्ठा hist_field *field, अचिन्हित दीर्घ flags)
अणु
	अगर ((field->flags & flags) != flags) अणु
		seq_म_लिखो(m, "ERROR: bad flags - %lx\n", flags);
		वापस -EINVAL;
	पूर्ण

	hist_field_debug_show_flags(m, field->flags);
	अगर (field->field)
		seq_म_लिखो(m, "      ftrace_event_field name: %s\n",
			   field->field->name);

	अगर (field->flags & HIST_FIELD_FL_VAR) अणु
		seq_म_लिखो(m, "      var.name: %s\n", field->var.name);
		seq_म_लिखो(m, "      var.idx (into tracing_map_elt.vars[]): %u\n",
			   field->var.idx);
	पूर्ण

	अगर (field->flags & HIST_FIELD_FL_ALIAS)
		seq_म_लिखो(m, "      var_ref_idx (into hist_data->var_refs[]): %u\n",
			   field->var_ref_idx);

	अगर (field->flags & HIST_FIELD_FL_VAR_REF) अणु
		seq_म_लिखो(m, "      name: %s\n", field->name);
		seq_म_लिखो(m, "      var.idx (into tracing_map_elt.vars[]): %u\n",
			   field->var.idx);
		seq_म_लिखो(m, "      var.hist_data: %p\n", field->var.hist_data);
		seq_म_लिखो(m, "      var_ref_idx (into hist_data->var_refs[]): %u\n",
			   field->var_ref_idx);
		अगर (field->प्रणाली)
			seq_म_लिखो(m, "      system: %s\n", field->प्रणाली);
		अगर (field->event_name)
			seq_म_लिखो(m, "      event_name: %s\n", field->event_name);
	पूर्ण

	seq_म_लिखो(m, "      type: %s\n", field->type);
	seq_म_लिखो(m, "      size: %u\n", field->size);
	seq_म_लिखो(m, "      is_signed: %u\n", field->is_चिन्हित);

	वापस 0;
पूर्ण

अटल पूर्णांक field_var_debug_show(काष्ठा seq_file *m,
				काष्ठा field_var *field_var, अचिन्हित पूर्णांक i,
				bool save_vars)
अणु
	स्थिर अक्षर *vars_name = save_vars ? "save_vars" : "field_vars";
	काष्ठा hist_field *field;
	पूर्णांक ret = 0;

	seq_म_लिखो(m, "\n    hist_data->%s[%d]:\n", vars_name, i);

	field = field_var->var;

	seq_म_लिखो(m, "\n      %s[%d].var:\n", vars_name, i);

	hist_field_debug_show_flags(m, field->flags);
	seq_म_लिखो(m, "      var.name: %s\n", field->var.name);
	seq_म_लिखो(m, "      var.idx (into tracing_map_elt.vars[]): %u\n",
		   field->var.idx);

	field = field_var->val;

	seq_म_लिखो(m, "\n      %s[%d].val:\n", vars_name, i);
	अगर (field->field)
		seq_म_लिखो(m, "      ftrace_event_field name: %s\n",
			   field->field->name);
	अन्यथा अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	seq_म_लिखो(m, "      type: %s\n", field->type);
	seq_म_लिखो(m, "      size: %u\n", field->size);
	seq_म_लिखो(m, "      is_signed: %u\n", field->is_चिन्हित);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hist_action_debug_show(काष्ठा seq_file *m,
				  काष्ठा action_data *data, पूर्णांक i)
अणु
	पूर्णांक ret = 0;

	अगर (data->handler == HANDLER_ONMAX ||
	    data->handler == HANDLER_ONCHANGE) अणु
		seq_म_लिखो(m, "\n    hist_data->actions[%d].track_data.var_ref:\n", i);
		ret = hist_field_debug_show(m, data->track_data.var_ref,
					    HIST_FIELD_FL_VAR_REF);
		अगर (ret)
			जाओ out;

		seq_म_लिखो(m, "\n    hist_data->actions[%d].track_data.track_var:\n", i);
		ret = hist_field_debug_show(m, data->track_data.track_var,
					    HIST_FIELD_FL_VAR);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (data->handler == HANDLER_ONMATCH) अणु
		seq_म_लिखो(m, "\n    hist_data->actions[%d].match_data.event_system: %s\n",
			   i, data->match_data.event_प्रणाली);
		seq_म_लिखो(m, "    hist_data->actions[%d].match_data.event: %s\n",
			   i, data->match_data.event);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hist_actions_debug_show(काष्ठा seq_file *m,
				   काष्ठा hist_trigger_data *hist_data)
अणु
	पूर्णांक i, ret = 0;

	अगर (hist_data->n_actions)
		seq_माला_दो(m, "\n  action tracking variables (for onmax()/onchange()/onmatch()):\n");

	क्रम (i = 0; i < hist_data->n_actions; i++) अणु
		काष्ठा action_data *action = hist_data->actions[i];

		ret = hist_action_debug_show(m, action, i);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (hist_data->n_save_vars)
		seq_माला_दो(m, "\n  save action variables (save() params):\n");

	क्रम (i = 0; i < hist_data->n_save_vars; i++) अणु
		ret = field_var_debug_show(m, hist_data->save_vars[i], i, true);
		अगर (ret)
			जाओ out;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम hist_trigger_debug_show(काष्ठा seq_file *m,
				    काष्ठा event_trigger_data *data, पूर्णांक n)
अणु
	काष्ठा hist_trigger_data *hist_data;
	पूर्णांक i, ret;

	अगर (n > 0)
		seq_माला_दो(m, "\n\n");

	seq_माला_दो(m, "# event histogram\n#\n# trigger info: ");
	data->ops->prपूर्णांक(m, data->ops, data);
	seq_माला_दो(m, "#\n\n");

	hist_data = data->निजी_data;

	seq_म_लिखो(m, "hist_data: %p\n\n", hist_data);
	seq_म_लिखो(m, "  n_vals: %u\n", hist_data->n_vals);
	seq_म_लिखो(m, "  n_keys: %u\n", hist_data->n_keys);
	seq_म_लिखो(m, "  n_fields: %u\n", hist_data->n_fields);

	seq_माला_दो(m, "\n  val fields:\n\n");

	seq_माला_दो(m, "    hist_data->fields[0]:\n");
	ret = hist_field_debug_show(m, hist_data->fields[0],
				    HIST_FIELD_FL_HITCOUNT);
	अगर (ret)
		वापस;

	क्रम (i = 1; i < hist_data->n_vals; i++) अणु
		seq_म_लिखो(m, "\n    hist_data->fields[%d]:\n", i);
		ret = hist_field_debug_show(m, hist_data->fields[i], 0);
		अगर (ret)
			वापस;
	पूर्ण

	seq_माला_दो(m, "\n  key fields:\n");

	क्रम (i = hist_data->n_vals; i < hist_data->n_fields; i++) अणु
		seq_म_लिखो(m, "\n    hist_data->fields[%d]:\n", i);
		ret = hist_field_debug_show(m, hist_data->fields[i],
					    HIST_FIELD_FL_KEY);
		अगर (ret)
			वापस;
	पूर्ण

	अगर (hist_data->n_var_refs)
		seq_माला_दो(m, "\n  variable reference fields:\n");

	क्रम (i = 0; i < hist_data->n_var_refs; i++) अणु
		seq_म_लिखो(m, "\n    hist_data->var_refs[%d]:\n", i);
		ret = hist_field_debug_show(m, hist_data->var_refs[i],
					    HIST_FIELD_FL_VAR_REF);
		अगर (ret)
			वापस;
	पूर्ण

	अगर (hist_data->n_field_vars)
		seq_माला_दो(m, "\n  field variables:\n");

	क्रम (i = 0; i < hist_data->n_field_vars; i++) अणु
		ret = field_var_debug_show(m, hist_data->field_vars[i], i, false);
		अगर (ret)
			वापस;
	पूर्ण

	ret = hist_actions_debug_show(m, hist_data);
	अगर (ret)
		वापस;
पूर्ण

अटल पूर्णांक hist_debug_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा event_trigger_data *data;
	काष्ठा trace_event_file *event_file;
	पूर्णांक n = 0, ret = 0;

	mutex_lock(&event_mutex);

	event_file = event_file_data(m->निजी);
	अगर (unlikely(!event_file)) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	list_क्रम_each_entry(data, &event_file->triggers, list) अणु
		अगर (data->cmd_ops->trigger_type == ETT_EVENT_HIST)
			hist_trigger_debug_show(m, data, n++);
	पूर्ण

 out_unlock:
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक event_hist_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	वापस single_खोलो(file, hist_debug_show, file);
पूर्ण

स्थिर काष्ठा file_operations event_hist_debug_fops = अणु
	.खोलो = event_hist_debug_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;
#पूर्ण_अगर

अटल व्योम hist_field_prपूर्णांक(काष्ठा seq_file *m, काष्ठा hist_field *hist_field)
अणु
	स्थिर अक्षर *field_name = hist_field_name(hist_field, 0);

	अगर (hist_field->var.name)
		seq_म_लिखो(m, "%s=", hist_field->var.name);

	अगर (hist_field->flags & HIST_FIELD_FL_CPU)
		seq_माला_दो(m, "cpu");
	अन्यथा अगर (field_name) अणु
		अगर (hist_field->flags & HIST_FIELD_FL_VAR_REF ||
		    hist_field->flags & HIST_FIELD_FL_ALIAS)
			seq_अ_दो(m, '$');
		seq_म_लिखो(m, "%s", field_name);
	पूर्ण अन्यथा अगर (hist_field->flags & HIST_FIELD_FL_TIMESTAMP)
		seq_माला_दो(m, "common_timestamp");

	अगर (hist_field->flags) अणु
		अगर (!(hist_field->flags & HIST_FIELD_FL_VAR_REF) &&
		    !(hist_field->flags & HIST_FIELD_FL_EXPR)) अणु
			स्थिर अक्षर *flags = get_hist_field_flags(hist_field);

			अगर (flags)
				seq_म_लिखो(m, ".%s", flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक event_hist_trigger_prपूर्णांक(काष्ठा seq_file *m,
				    काष्ठा event_trigger_ops *ops,
				    काष्ठा event_trigger_data *data)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;
	काष्ठा hist_field *field;
	bool have_var = false;
	अचिन्हित पूर्णांक i;

	seq_माला_दो(m, "hist:");

	अगर (data->name)
		seq_म_लिखो(m, "%s:", data->name);

	seq_माला_दो(m, "keys=");

	क्रम_each_hist_key_field(i, hist_data) अणु
		field = hist_data->fields[i];

		अगर (i > hist_data->n_vals)
			seq_माला_दो(m, ",");

		अगर (field->flags & HIST_FIELD_FL_STACKTRACE)
			seq_माला_दो(m, "stacktrace");
		अन्यथा
			hist_field_prपूर्णांक(m, field);
	पूर्ण

	seq_माला_दो(m, ":vals=");

	क्रम_each_hist_val_field(i, hist_data) अणु
		field = hist_data->fields[i];
		अगर (field->flags & HIST_FIELD_FL_VAR) अणु
			have_var = true;
			जारी;
		पूर्ण

		अगर (i == HITCOUNT_IDX)
			seq_माला_दो(m, "hitcount");
		अन्यथा अणु
			seq_माला_दो(m, ",");
			hist_field_prपूर्णांक(m, field);
		पूर्ण
	पूर्ण

	अगर (have_var) अणु
		अचिन्हित पूर्णांक n = 0;

		seq_माला_दो(m, ":");

		क्रम_each_hist_val_field(i, hist_data) अणु
			field = hist_data->fields[i];

			अगर (field->flags & HIST_FIELD_FL_VAR) अणु
				अगर (n++)
					seq_माला_दो(m, ",");
				hist_field_prपूर्णांक(m, field);
			पूर्ण
		पूर्ण
	पूर्ण

	seq_माला_दो(m, ":sort=");

	क्रम (i = 0; i < hist_data->n_sort_keys; i++) अणु
		काष्ठा tracing_map_sort_key *sort_key;
		अचिन्हित पूर्णांक idx, first_key_idx;

		/* skip VAR vals */
		first_key_idx = hist_data->n_vals - hist_data->n_vars;

		sort_key = &hist_data->sort_keys[i];
		idx = sort_key->field_idx;

		अगर (WARN_ON(idx >= HIST_FIELDS_MAX))
			वापस -EINVAL;

		अगर (i > 0)
			seq_माला_दो(m, ",");

		अगर (idx == HITCOUNT_IDX)
			seq_माला_दो(m, "hitcount");
		अन्यथा अणु
			अगर (idx >= first_key_idx)
				idx += hist_data->n_vars;
			hist_field_prपूर्णांक(m, hist_data->fields[idx]);
		पूर्ण

		अगर (sort_key->descending)
			seq_माला_दो(m, ".descending");
	पूर्ण
	seq_म_लिखो(m, ":size=%u", (1 << hist_data->map->map_bits));
	अगर (hist_data->enable_बारtamps)
		seq_म_लिखो(m, ":clock=%s", hist_data->attrs->घड़ी);

	prपूर्णांक_actions_spec(m, hist_data);

	अगर (data->filter_str)
		seq_म_लिखो(m, " if %s", data->filter_str);

	अगर (data->छोड़ोd)
		seq_माला_दो(m, " [paused]");
	अन्यथा
		seq_माला_दो(m, " [active]");

	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

अटल पूर्णांक event_hist_trigger_init(काष्ठा event_trigger_ops *ops,
				   काष्ठा event_trigger_data *data)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;

	अगर (!data->ref && hist_data->attrs->name)
		save_named_trigger(hist_data->attrs->name, data);

	data->ref++;

	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_field_var_hists(काष्ठा hist_trigger_data *hist_data)
अणु
	काष्ठा trace_event_file *file;
	अचिन्हित पूर्णांक i;
	अक्षर *cmd;
	पूर्णांक ret;

	क्रम (i = 0; i < hist_data->n_field_var_hists; i++) अणु
		file = hist_data->field_var_hists[i]->hist_data->event_file;
		cmd = hist_data->field_var_hists[i]->cmd;
		ret = event_hist_trigger_func(&trigger_hist_cmd, file,
					      "!hist", "hist", cmd);
	पूर्ण
पूर्ण

अटल व्योम event_hist_trigger_मुक्त(काष्ठा event_trigger_ops *ops,
				    काष्ठा event_trigger_data *data)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;

	अगर (WARN_ON_ONCE(data->ref <= 0))
		वापस;

	data->ref--;
	अगर (!data->ref) अणु
		अगर (data->name)
			del_named_trigger(data);

		trigger_data_मुक्त(data);

		हटाओ_hist_vars(hist_data);

		unरेजिस्टर_field_var_hists(hist_data);

		destroy_hist_data(hist_data);
	पूर्ण
पूर्ण

अटल काष्ठा event_trigger_ops event_hist_trigger_ops = अणु
	.func			= event_hist_trigger,
	.prपूर्णांक			= event_hist_trigger_prपूर्णांक,
	.init			= event_hist_trigger_init,
	.मुक्त			= event_hist_trigger_मुक्त,
पूर्ण;

अटल पूर्णांक event_hist_trigger_named_init(काष्ठा event_trigger_ops *ops,
					 काष्ठा event_trigger_data *data)
अणु
	data->ref++;

	save_named_trigger(data->named_data->name, data);

	event_hist_trigger_init(ops, data->named_data);

	वापस 0;
पूर्ण

अटल व्योम event_hist_trigger_named_मुक्त(काष्ठा event_trigger_ops *ops,
					  काष्ठा event_trigger_data *data)
अणु
	अगर (WARN_ON_ONCE(data->ref <= 0))
		वापस;

	event_hist_trigger_मुक्त(ops, data->named_data);

	data->ref--;
	अगर (!data->ref) अणु
		del_named_trigger(data);
		trigger_data_मुक्त(data);
	पूर्ण
पूर्ण

अटल काष्ठा event_trigger_ops event_hist_trigger_named_ops = अणु
	.func			= event_hist_trigger,
	.prपूर्णांक			= event_hist_trigger_prपूर्णांक,
	.init			= event_hist_trigger_named_init,
	.मुक्त			= event_hist_trigger_named_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops *event_hist_get_trigger_ops(अक्षर *cmd,
							    अक्षर *param)
अणु
	वापस &event_hist_trigger_ops;
पूर्ण

अटल व्योम hist_clear(काष्ठा event_trigger_data *data)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;

	अगर (data->name)
		छोड़ो_named_trigger(data);

	tracepoपूर्णांक_synchronize_unरेजिस्टर();

	tracing_map_clear(hist_data->map);

	अगर (data->name)
		unछोड़ो_named_trigger(data);
पूर्ण

अटल bool compatible_field(काष्ठा ftrace_event_field *field,
			     काष्ठा ftrace_event_field *test_field)
अणु
	अगर (field == test_field)
		वापस true;
	अगर (field == शून्य || test_field == शून्य)
		वापस false;
	अगर (म_भेद(field->name, test_field->name) != 0)
		वापस false;
	अगर (म_भेद(field->type, test_field->type) != 0)
		वापस false;
	अगर (field->size != test_field->size)
		वापस false;
	अगर (field->is_चिन्हित != test_field->is_चिन्हित)
		वापस false;

	वापस true;
पूर्ण

अटल bool hist_trigger_match(काष्ठा event_trigger_data *data,
			       काष्ठा event_trigger_data *data_test,
			       काष्ठा event_trigger_data *named_data,
			       bool ignore_filter)
अणु
	काष्ठा tracing_map_sort_key *sort_key, *sort_key_test;
	काष्ठा hist_trigger_data *hist_data, *hist_data_test;
	काष्ठा hist_field *key_field, *key_field_test;
	अचिन्हित पूर्णांक i;

	अगर (named_data && (named_data != data_test) &&
	    (named_data != data_test->named_data))
		वापस false;

	अगर (!named_data && is_named_trigger(data_test))
		वापस false;

	hist_data = data->निजी_data;
	hist_data_test = data_test->निजी_data;

	अगर (hist_data->n_vals != hist_data_test->n_vals ||
	    hist_data->n_fields != hist_data_test->n_fields ||
	    hist_data->n_sort_keys != hist_data_test->n_sort_keys)
		वापस false;

	अगर (!ignore_filter) अणु
		अगर ((data->filter_str && !data_test->filter_str) ||
		   (!data->filter_str && data_test->filter_str))
			वापस false;
	पूर्ण

	क्रम_each_hist_field(i, hist_data) अणु
		key_field = hist_data->fields[i];
		key_field_test = hist_data_test->fields[i];

		अगर (key_field->flags != key_field_test->flags)
			वापस false;
		अगर (!compatible_field(key_field->field, key_field_test->field))
			वापस false;
		अगर (key_field->offset != key_field_test->offset)
			वापस false;
		अगर (key_field->size != key_field_test->size)
			वापस false;
		अगर (key_field->is_चिन्हित != key_field_test->is_चिन्हित)
			वापस false;
		अगर (!!key_field->var.name != !!key_field_test->var.name)
			वापस false;
		अगर (key_field->var.name &&
		    म_भेद(key_field->var.name, key_field_test->var.name) != 0)
			वापस false;
	पूर्ण

	क्रम (i = 0; i < hist_data->n_sort_keys; i++) अणु
		sort_key = &hist_data->sort_keys[i];
		sort_key_test = &hist_data_test->sort_keys[i];

		अगर (sort_key->field_idx != sort_key_test->field_idx ||
		    sort_key->descending != sort_key_test->descending)
			वापस false;
	पूर्ण

	अगर (!ignore_filter && data->filter_str &&
	    (म_भेद(data->filter_str, data_test->filter_str) != 0))
		वापस false;

	अगर (!actions_match(hist_data, hist_data_test))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hist_रेजिस्टर_trigger(अक्षर *glob, काष्ठा event_trigger_ops *ops,
				 काष्ठा event_trigger_data *data,
				 काष्ठा trace_event_file *file)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;
	काष्ठा event_trigger_data *test, *named_data = शून्य;
	काष्ठा trace_array *tr = file->tr;
	पूर्णांक ret = 0;

	अगर (hist_data->attrs->name) अणु
		named_data = find_named_trigger(hist_data->attrs->name);
		अगर (named_data) अणु
			अगर (!hist_trigger_match(data, named_data, named_data,
						true)) अणु
				hist_err(tr, HIST_ERR_NAMED_MISMATCH, errpos(hist_data->attrs->name));
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hist_data->attrs->name && !named_data)
		जाओ new;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			अगर (!hist_trigger_match(data, test, named_data, false))
				जारी;
			अगर (hist_data->attrs->छोड़ो)
				test->छोड़ोd = true;
			अन्यथा अगर (hist_data->attrs->cont)
				test->छोड़ोd = false;
			अन्यथा अगर (hist_data->attrs->clear)
				hist_clear(test);
			अन्यथा अणु
				hist_err(tr, HIST_ERR_TRIGGER_EEXIST, 0);
				ret = -EEXIST;
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण
 new:
	अगर (hist_data->attrs->cont || hist_data->attrs->clear) अणु
		hist_err(tr, HIST_ERR_TRIGGER_ENOENT_CLEAR, 0);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (hist_data->attrs->छोड़ो)
		data->छोड़ोd = true;

	अगर (named_data) अणु
		data->निजी_data = named_data->निजी_data;
		set_named_trigger_data(data, named_data);
		data->ops = &event_hist_trigger_named_ops;
	पूर्ण

	अगर (data->ops->init) अणु
		ret = data->ops->init(data->ops, data);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (hist_data->enable_बारtamps) अणु
		अक्षर *घड़ी = hist_data->attrs->घड़ी;

		ret = tracing_set_घड़ी(file->tr, hist_data->attrs->घड़ी);
		अगर (ret) अणु
			hist_err(tr, HIST_ERR_SET_CLOCK_FAIL, errpos(घड़ी));
			जाओ out;
		पूर्ण

		tracing_set_filter_buffering(file->tr, true);
	पूर्ण

	अगर (named_data)
		destroy_hist_data(hist_data);

	ret++;
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक hist_trigger_enable(काष्ठा event_trigger_data *data,
			       काष्ठा trace_event_file *file)
अणु
	पूर्णांक ret = 0;

	list_add_tail_rcu(&data->list, &file->triggers);

	update_cond_flag(file);

	अगर (trace_event_trigger_enable_disable(file, 1) < 0) अणु
		list_del_rcu(&data->list);
		update_cond_flag(file);
		ret--;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool have_hist_trigger_match(काष्ठा event_trigger_data *data,
				    काष्ठा trace_event_file *file)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;
	काष्ठा event_trigger_data *test, *named_data = शून्य;
	bool match = false;

	lockdep_निश्चित_held(&event_mutex);

	अगर (hist_data->attrs->name)
		named_data = find_named_trigger(hist_data->attrs->name);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			अगर (hist_trigger_match(data, test, named_data, false)) अणु
				match = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस match;
पूर्ण

अटल bool hist_trigger_check_refs(काष्ठा event_trigger_data *data,
				    काष्ठा trace_event_file *file)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;
	काष्ठा event_trigger_data *test, *named_data = शून्य;

	lockdep_निश्चित_held(&event_mutex);

	अगर (hist_data->attrs->name)
		named_data = find_named_trigger(hist_data->attrs->name);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			अगर (!hist_trigger_match(data, test, named_data, false))
				जारी;
			hist_data = test->निजी_data;
			अगर (check_var_refs(hist_data))
				वापस true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hist_unरेजिस्टर_trigger(अक्षर *glob, काष्ठा event_trigger_ops *ops,
				    काष्ठा event_trigger_data *data,
				    काष्ठा trace_event_file *file)
अणु
	काष्ठा hist_trigger_data *hist_data = data->निजी_data;
	काष्ठा event_trigger_data *test, *named_data = शून्य;
	bool unरेजिस्टरed = false;

	lockdep_निश्चित_held(&event_mutex);

	अगर (hist_data->attrs->name)
		named_data = find_named_trigger(hist_data->attrs->name);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			अगर (!hist_trigger_match(data, test, named_data, false))
				जारी;
			unरेजिस्टरed = true;
			list_del_rcu(&test->list);
			trace_event_trigger_enable_disable(file, 0);
			update_cond_flag(file);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (unरेजिस्टरed && test->ops->मुक्त)
		test->ops->मुक्त(test->ops, test);

	अगर (hist_data->enable_बारtamps) अणु
		अगर (!hist_data->हटाओ || unरेजिस्टरed)
			tracing_set_filter_buffering(file->tr, false);
	पूर्ण
पूर्ण

अटल bool hist_file_check_refs(काष्ठा trace_event_file *file)
अणु
	काष्ठा hist_trigger_data *hist_data;
	काष्ठा event_trigger_data *test;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			hist_data = test->निजी_data;
			अगर (check_var_refs(hist_data))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hist_unreg_all(काष्ठा trace_event_file *file)
अणु
	काष्ठा event_trigger_data *test, *n;
	काष्ठा hist_trigger_data *hist_data;
	काष्ठा synth_event *se;
	स्थिर अक्षर *se_name;

	lockdep_निश्चित_held(&event_mutex);

	अगर (hist_file_check_refs(file))
		वापस;

	list_क्रम_each_entry_safe(test, n, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			hist_data = test->निजी_data;
			list_del_rcu(&test->list);
			trace_event_trigger_enable_disable(file, 0);

			se_name = trace_event_name(file->event_call);
			se = find_synth_event(se_name);
			अगर (se)
				se->ref--;

			update_cond_flag(file);
			अगर (hist_data->enable_बारtamps)
				tracing_set_filter_buffering(file->tr, false);
			अगर (test->ops->मुक्त)
				test->ops->मुक्त(test->ops, test);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक event_hist_trigger_func(काष्ठा event_command *cmd_ops,
				   काष्ठा trace_event_file *file,
				   अक्षर *glob, अक्षर *cmd, अक्षर *param)
अणु
	अचिन्हित पूर्णांक hist_trigger_bits = TRACING_MAP_BITS_DEFAULT;
	काष्ठा event_trigger_data *trigger_data;
	काष्ठा hist_trigger_attrs *attrs;
	काष्ठा event_trigger_ops *trigger_ops;
	काष्ठा hist_trigger_data *hist_data;
	काष्ठा synth_event *se;
	स्थिर अक्षर *se_name;
	bool हटाओ = false;
	अक्षर *trigger, *p;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&event_mutex);

	अगर (glob && म_माप(glob)) अणु
		hist_err_clear();
		last_cmd_set(file, param);
	पूर्ण

	अगर (!param)
		वापस -EINVAL;

	अगर (glob[0] == '!')
		हटाओ = true;

	/*
	 * separate the trigger from the filter (k:v [अगर filter])
	 * allowing क्रम whitespace in the trigger
	 */
	p = trigger = param;
	करो अणु
		p = म_माला(p, "if");
		अगर (!p)
			अवरोध;
		अगर (p == param)
			वापस -EINVAL;
		अगर (*(p - 1) != ' ' && *(p - 1) != '\t') अणु
			p++;
			जारी;
		पूर्ण
		अगर (p >= param + म_माप(param) - (माप("if") - 1) - 1)
			वापस -EINVAL;
		अगर (*(p + माप("if") - 1) != ' ' && *(p + sizeof("if") - 1) != '\t') अणु
			p++;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण जबतक (p);

	अगर (!p)
		param = शून्य;
	अन्यथा अणु
		*(p - 1) = '\0';
		param = म_मालाip(p);
		trigger = म_मालाip(trigger);
	पूर्ण

	attrs = parse_hist_trigger_attrs(file->tr, trigger);
	अगर (IS_ERR(attrs))
		वापस PTR_ERR(attrs);

	अगर (attrs->map_bits)
		hist_trigger_bits = attrs->map_bits;

	hist_data = create_hist_data(hist_trigger_bits, attrs, file, हटाओ);
	अगर (IS_ERR(hist_data)) अणु
		destroy_hist_trigger_attrs(attrs);
		वापस PTR_ERR(hist_data);
	पूर्ण

	trigger_ops = cmd_ops->get_trigger_ops(cmd, trigger);

	trigger_data = kzalloc(माप(*trigger_data), GFP_KERNEL);
	अगर (!trigger_data) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	trigger_data->count = -1;
	trigger_data->ops = trigger_ops;
	trigger_data->cmd_ops = cmd_ops;

	INIT_LIST_HEAD(&trigger_data->list);
	RCU_INIT_POINTER(trigger_data->filter, शून्य);

	trigger_data->निजी_data = hist_data;

	/* अगर param is non-empty, it's supposed to be a filter */
	अगर (param && cmd_ops->set_filter) अणु
		ret = cmd_ops->set_filter(param, trigger_data, file);
		अगर (ret < 0)
			जाओ out_मुक्त;
	पूर्ण

	अगर (हटाओ) अणु
		अगर (!have_hist_trigger_match(trigger_data, file))
			जाओ out_मुक्त;

		अगर (hist_trigger_check_refs(trigger_data, file)) अणु
			ret = -EBUSY;
			जाओ out_मुक्त;
		पूर्ण

		cmd_ops->unreg(glob+1, trigger_ops, trigger_data, file);
		se_name = trace_event_name(file->event_call);
		se = find_synth_event(se_name);
		अगर (se)
			se->ref--;
		ret = 0;
		जाओ out_मुक्त;
	पूर्ण

	ret = cmd_ops->reg(glob, trigger_ops, trigger_data, file);
	/*
	 * The above वापसs on success the # of triggers रेजिस्टरed,
	 * but अगर it didn't रेजिस्टर any it वापसs zero.  Consider no
	 * triggers रेजिस्टरed a failure too.
	 */
	अगर (!ret) अणु
		अगर (!(attrs->छोड़ो || attrs->cont || attrs->clear))
			ret = -ENOENT;
		जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (ret < 0)
		जाओ out_मुक्त;

	अगर (get_named_trigger_data(trigger_data))
		जाओ enable;

	अगर (has_hist_vars(hist_data))
		save_hist_vars(hist_data);

	ret = create_actions(hist_data);
	अगर (ret)
		जाओ out_unreg;

	ret = tracing_map_init(hist_data->map);
	अगर (ret)
		जाओ out_unreg;
enable:
	ret = hist_trigger_enable(trigger_data, file);
	अगर (ret)
		जाओ out_unreg;

	se_name = trace_event_name(file->event_call);
	se = find_synth_event(se_name);
	अगर (se)
		se->ref++;
	/* Just वापस zero, not the number of रेजिस्टरed triggers */
	ret = 0;
 out:
	अगर (ret == 0)
		hist_err_clear();

	वापस ret;
 out_unreg:
	cmd_ops->unreg(glob+1, trigger_ops, trigger_data, file);
 out_मुक्त:
	अगर (cmd_ops->set_filter)
		cmd_ops->set_filter(शून्य, trigger_data, शून्य);

	हटाओ_hist_vars(hist_data);

	kमुक्त(trigger_data);

	destroy_hist_data(hist_data);
	जाओ out;
पूर्ण

अटल काष्ठा event_command trigger_hist_cmd = अणु
	.name			= "hist",
	.trigger_type		= ETT_EVENT_HIST,
	.flags			= EVENT_CMD_FL_NEEDS_REC,
	.func			= event_hist_trigger_func,
	.reg			= hist_रेजिस्टर_trigger,
	.unreg			= hist_unरेजिस्टर_trigger,
	.unreg_all		= hist_unreg_all,
	.get_trigger_ops	= event_hist_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

__init पूर्णांक रेजिस्टर_trigger_hist_cmd(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_event_command(&trigger_hist_cmd);
	WARN_ON(ret < 0);

	वापस ret;
पूर्ण

अटल व्योम
hist_enable_trigger(काष्ठा event_trigger_data *data,
		    काष्ठा trace_buffer *buffer,  व्योम *rec,
		    काष्ठा ring_buffer_event *event)
अणु
	काष्ठा enable_trigger_data *enable_data = data->निजी_data;
	काष्ठा event_trigger_data *test;

	list_क्रम_each_entry_rcu(test, &enable_data->file->triggers, list,
				lockdep_is_held(&event_mutex)) अणु
		अगर (test->cmd_ops->trigger_type == ETT_EVENT_HIST) अणु
			अगर (enable_data->enable)
				test->छोड़ोd = false;
			अन्यथा
				test->छोड़ोd = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
hist_enable_count_trigger(काष्ठा event_trigger_data *data,
			  काष्ठा trace_buffer *buffer,  व्योम *rec,
			  काष्ठा ring_buffer_event *event)
अणु
	अगर (!data->count)
		वापस;

	अगर (data->count != -1)
		(data->count)--;

	hist_enable_trigger(data, buffer, rec, event);
पूर्ण

अटल काष्ठा event_trigger_ops hist_enable_trigger_ops = अणु
	.func			= hist_enable_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops hist_enable_count_trigger_ops = अणु
	.func			= hist_enable_count_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops hist_disable_trigger_ops = अणु
	.func			= hist_enable_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops hist_disable_count_trigger_ops = अणु
	.func			= hist_enable_count_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops *
hist_enable_get_trigger_ops(अक्षर *cmd, अक्षर *param)
अणु
	काष्ठा event_trigger_ops *ops;
	bool enable;

	enable = (म_भेद(cmd, ENABLE_HIST_STR) == 0);

	अगर (enable)
		ops = param ? &hist_enable_count_trigger_ops :
			&hist_enable_trigger_ops;
	अन्यथा
		ops = param ? &hist_disable_count_trigger_ops :
			&hist_disable_trigger_ops;

	वापस ops;
पूर्ण

अटल व्योम hist_enable_unreg_all(काष्ठा trace_event_file *file)
अणु
	काष्ठा event_trigger_data *test, *n;

	list_क्रम_each_entry_safe(test, n, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == ETT_HIST_ENABLE) अणु
			list_del_rcu(&test->list);
			update_cond_flag(file);
			trace_event_trigger_enable_disable(file, 0);
			अगर (test->ops->मुक्त)
				test->ops->मुक्त(test->ops, test);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा event_command trigger_hist_enable_cmd = अणु
	.name			= ENABLE_HIST_STR,
	.trigger_type		= ETT_HIST_ENABLE,
	.func			= event_enable_trigger_func,
	.reg			= event_enable_रेजिस्टर_trigger,
	.unreg			= event_enable_unरेजिस्टर_trigger,
	.unreg_all		= hist_enable_unreg_all,
	.get_trigger_ops	= hist_enable_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

अटल काष्ठा event_command trigger_hist_disable_cmd = अणु
	.name			= DISABLE_HIST_STR,
	.trigger_type		= ETT_HIST_ENABLE,
	.func			= event_enable_trigger_func,
	.reg			= event_enable_रेजिस्टर_trigger,
	.unreg			= event_enable_unरेजिस्टर_trigger,
	.unreg_all		= hist_enable_unreg_all,
	.get_trigger_ops	= hist_enable_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

अटल __init व्योम unरेजिस्टर_trigger_hist_enable_disable_cmds(व्योम)
अणु
	unरेजिस्टर_event_command(&trigger_hist_enable_cmd);
	unरेजिस्टर_event_command(&trigger_hist_disable_cmd);
पूर्ण

__init पूर्णांक रेजिस्टर_trigger_hist_enable_disable_cmds(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_event_command(&trigger_hist_enable_cmd);
	अगर (WARN_ON(ret < 0))
		वापस ret;
	ret = रेजिस्टर_event_command(&trigger_hist_disable_cmd);
	अगर (WARN_ON(ret < 0))
		unरेजिस्टर_trigger_hist_enable_disable_cmds();

	वापस ret;
पूर्ण
