<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common header file क्रम probe-based Dynamic events.
 *
 * This code was copied from kernel/trace/trace_kprobe.h written by
 * Masami Hiramatsu <masami.hiramatsu.pt@hitachi.com>
 *
 * Updates to make this generic:
 * Copyright (C) IBM Corporation, 2010-2011
 * Author:     Srikar Dronamraju
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/tracefs.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/bitsperदीर्घ.h>

#समावेश "trace.h"
#समावेश "trace_output.h"

#घोषणा MAX_TRACE_ARGS		128
#घोषणा MAX_ARGSTR_LEN		63
#घोषणा MAX_ARRAY_LEN		64
#घोषणा MAX_ARG_NAME_LEN	32
#घोषणा MAX_STRING_SIZE		PATH_MAX

/* Reserved field names */
#घोषणा FIELD_STRING_IP		"__probe_ip"
#घोषणा FIELD_STRING_RETIP	"__probe_ret_ip"
#घोषणा FIELD_STRING_FUNC	"__probe_func"

#अघोषित DEFINE_FIELD
#घोषणा DEFINE_FIELD(type, item, name, is_चिन्हित)			\
	करो अणु								\
		ret = trace_define_field(event_call, #type, name,	\
					 दुरत्व(typeof(field), item),	\
					 माप(field.item), is_चिन्हित, \
					 FILTER_OTHER);			\
		अगर (ret)						\
			वापस ret;					\
	पूर्ण जबतक (0)


/* Flags क्रम trace_probe */
#घोषणा TP_FLAG_TRACE		1
#घोषणा TP_FLAG_PROखाता		2

/* data_loc: data location, compatible with u32 */
#घोषणा make_data_loc(len, offs)	\
	(((u32)(len) << 16) | ((u32)(offs) & 0xffff))
#घोषणा get_loc_len(dl)		((u32)(dl) >> 16)
#घोषणा get_loc_offs(dl)	((u32)(dl) & 0xffff)

अटल nokprobe_अंतरभूत व्योम *get_loc_data(u32 *dl, व्योम *ent)
अणु
	वापस (u8 *)ent + get_loc_offs(*dl);
पूर्ण

अटल nokprobe_अंतरभूत u32 update_data_loc(u32 loc, पूर्णांक consumed)
अणु
	u32 maxlen = get_loc_len(loc);
	u32 offset = get_loc_offs(loc);

	वापस make_data_loc(maxlen - consumed, offset + consumed);
पूर्ण

/* Prपूर्णांकing function type */
प्रकार पूर्णांक (*prपूर्णांक_type_func_t)(काष्ठा trace_seq *, व्योम *, व्योम *);

क्रमागत fetch_op अणु
	FETCH_OP_NOP = 0,
	// Stage 1 (load) ops
	FETCH_OP_REG,		/* Register : .param = offset */
	FETCH_OP_STACK,		/* Stack : .param = index */
	FETCH_OP_STACKP,	/* Stack poपूर्णांकer */
	FETCH_OP_RETVAL,	/* Return value */
	FETCH_OP_IMM,		/* Immediate : .immediate */
	FETCH_OP_COMM,		/* Current comm */
	FETCH_OP_ARG,		/* Function argument : .param */
	FETCH_OP_FOFFS,		/* File offset: .immediate */
	FETCH_OP_DATA,		/* Allocated data: .data */
	// Stage 2 (dereference) op
	FETCH_OP_DEREF,		/* Dereference: .offset */
	FETCH_OP_UDEREF,	/* User-space Dereference: .offset */
	// Stage 3 (store) ops
	FETCH_OP_ST_RAW,	/* Raw: .size */
	FETCH_OP_ST_MEM,	/* Mem: .offset, .size */
	FETCH_OP_ST_UMEM,	/* Mem: .offset, .size */
	FETCH_OP_ST_STRING,	/* String: .offset, .size */
	FETCH_OP_ST_USTRING,	/* User String: .offset, .size */
	// Stage 4 (modअगरy) op
	FETCH_OP_MOD_BF,	/* Bitfield: .basesize, .lshअगरt, .rshअगरt */
	// Stage 5 (loop) op
	FETCH_OP_LP_ARRAY,	/* Array: .param = loop count */
	FETCH_OP_END,
	FETCH_NOP_SYMBOL,	/* Unresolved Symbol holder */
पूर्ण;

काष्ठा fetch_insn अणु
	क्रमागत fetch_op op;
	जोड़ अणु
		अचिन्हित पूर्णांक param;
		काष्ठा अणु
			अचिन्हित पूर्णांक size;
			पूर्णांक offset;
		पूर्ण;
		काष्ठा अणु
			अचिन्हित अक्षर basesize;
			अचिन्हित अक्षर lshअगरt;
			अचिन्हित अक्षर rshअगरt;
		पूर्ण;
		अचिन्हित दीर्घ immediate;
		व्योम *data;
	पूर्ण;
पूर्ण;

/* fetch + deref*N + store + mod + end <= 16, this allows N=12, enough */
#घोषणा FETCH_INSN_MAX	16
#घोषणा FETCH_TOKEN_COMM	(-ECOMM)

/* Fetch type inक्रमmation table */
काष्ठा fetch_type अणु
	स्थिर अक्षर		*name;		/* Name of type */
	माप_प्रकार			size;		/* Byte size of type */
	पूर्णांक			is_चिन्हित;	/* Signed flag */
	prपूर्णांक_type_func_t	prपूर्णांक;		/* Prपूर्णांक functions */
	स्थिर अक्षर		*fmt;		/* Format string */
	स्थिर अक्षर		*fmttype;	/* Name in क्रमmat file */
पूर्ण;

/* For defining macros, define string/string_size types */
प्रकार u32 string;
प्रकार u32 string_size;

#घोषणा PRINT_TYPE_FUNC_NAME(type)	prपूर्णांक_type_##type
#घोषणा PRINT_TYPE_FMT_NAME(type)	prपूर्णांक_type_क्रमmat_##type

/* Prपूर्णांकing  in basic type function ढाँचा */
#घोषणा DECLARE_BASIC_PRINT_TYPE_FUNC(type)				\
पूर्णांक PRINT_TYPE_FUNC_NAME(type)(काष्ठा trace_seq *s, व्योम *data, व्योम *ent);\
बाह्य स्थिर अक्षर PRINT_TYPE_FMT_NAME(type)[]

DECLARE_BASIC_PRINT_TYPE_FUNC(u8);
DECLARE_BASIC_PRINT_TYPE_FUNC(u16);
DECLARE_BASIC_PRINT_TYPE_FUNC(u32);
DECLARE_BASIC_PRINT_TYPE_FUNC(u64);
DECLARE_BASIC_PRINT_TYPE_FUNC(s8);
DECLARE_BASIC_PRINT_TYPE_FUNC(s16);
DECLARE_BASIC_PRINT_TYPE_FUNC(s32);
DECLARE_BASIC_PRINT_TYPE_FUNC(s64);
DECLARE_BASIC_PRINT_TYPE_FUNC(x8);
DECLARE_BASIC_PRINT_TYPE_FUNC(x16);
DECLARE_BASIC_PRINT_TYPE_FUNC(x32);
DECLARE_BASIC_PRINT_TYPE_FUNC(x64);

DECLARE_BASIC_PRINT_TYPE_FUNC(string);
DECLARE_BASIC_PRINT_TYPE_FUNC(symbol);

/* Default (अचिन्हित दीर्घ) fetch type */
#घोषणा __DEFAULT_FETCH_TYPE(t) x##t
#घोषणा _DEFAULT_FETCH_TYPE(t) __DEFAULT_FETCH_TYPE(t)
#घोषणा DEFAULT_FETCH_TYPE _DEFAULT_FETCH_TYPE(BITS_PER_LONG)
#घोषणा DEFAULT_FETCH_TYPE_STR __stringअगरy(DEFAULT_FETCH_TYPE)

#घोषणा __ADDR_FETCH_TYPE(t) u##t
#घोषणा _ADDR_FETCH_TYPE(t) __ADDR_FETCH_TYPE(t)
#घोषणा ADDR_FETCH_TYPE _ADDR_FETCH_TYPE(BITS_PER_LONG)

#घोषणा __ASSIGN_FETCH_TYPE(_name, ptype, ftype, _size, sign, _fmttype)	\
	अणु.name = _name,				\
	 .size = _size,					\
	 .is_चिन्हित = sign,				\
	 .prपूर्णांक = PRINT_TYPE_FUNC_NAME(ptype),		\
	 .fmt = PRINT_TYPE_FMT_NAME(ptype),		\
	 .fmttype = _fmttype,				\
	पूर्ण
#घोषणा _ASSIGN_FETCH_TYPE(_name, ptype, ftype, _size, sign, _fmttype)	\
	__ASSIGN_FETCH_TYPE(_name, ptype, ftype, _size, sign, #_fmttype)
#घोषणा ASSIGN_FETCH_TYPE(ptype, ftype, sign)			\
	_ASSIGN_FETCH_TYPE(#ptype, ptype, ftype, माप(ftype), sign, ptype)

/* If ptype is an alias of atype, use this macro (show atype in क्रमmat) */
#घोषणा ASSIGN_FETCH_TYPE_ALIAS(ptype, atype, ftype, sign)		\
	_ASSIGN_FETCH_TYPE(#ptype, ptype, ftype, माप(ftype), sign, atype)

#घोषणा ASSIGN_FETCH_TYPE_END अणुपूर्ण
#घोषणा MAX_ARRAY_LEN	64

#अगर_घोषित CONFIG_KPROBE_EVENTS
bool trace_kprobe_on_func_entry(काष्ठा trace_event_call *call);
bool trace_kprobe_error_injectable(काष्ठा trace_event_call *call);
#अन्यथा
अटल अंतरभूत bool trace_kprobe_on_func_entry(काष्ठा trace_event_call *call)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool trace_kprobe_error_injectable(काष्ठा trace_event_call *call)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_KPROBE_EVENTS */

काष्ठा probe_arg अणु
	काष्ठा fetch_insn	*code;
	bool			dynamic;/* Dynamic array (string) is used */
	अचिन्हित पूर्णांक		offset;	/* Offset from argument entry */
	अचिन्हित पूर्णांक		count;	/* Array count */
	स्थिर अक्षर		*name;	/* Name of this argument */
	स्थिर अक्षर		*comm;	/* Command of this argument */
	अक्षर			*fmt;	/* Format string अगर needed */
	स्थिर काष्ठा fetch_type	*type;	/* Type of this argument */
पूर्ण;

काष्ठा trace_uprobe_filter अणु
	rwlock_t		rwlock;
	पूर्णांक			nr_प्रणालीwide;
	काष्ठा list_head	perf_events;
पूर्ण;

/* Event call and class holder */
काष्ठा trace_probe_event अणु
	अचिन्हित पूर्णांक			flags;	/* For TP_FLAG_* */
	काष्ठा trace_event_class	class;
	काष्ठा trace_event_call		call;
	काष्ठा list_head 		files;
	काष्ठा list_head		probes;
	काष्ठा trace_uprobe_filter	filter[];
पूर्ण;

काष्ठा trace_probe अणु
	काष्ठा list_head		list;
	काष्ठा trace_probe_event	*event;
	sमाप_प्रकार				size;	/* trace entry size */
	अचिन्हित पूर्णांक			nr_args;
	काष्ठा probe_arg		args[];
पूर्ण;

काष्ठा event_file_link अणु
	काष्ठा trace_event_file		*file;
	काष्ठा list_head		list;
पूर्ण;

अटल अंतरभूत bool trace_probe_test_flag(काष्ठा trace_probe *tp,
					 अचिन्हित पूर्णांक flag)
अणु
	वापस !!(tp->event->flags & flag);
पूर्ण

अटल अंतरभूत व्योम trace_probe_set_flag(काष्ठा trace_probe *tp,
					अचिन्हित पूर्णांक flag)
अणु
	tp->event->flags |= flag;
पूर्ण

अटल अंतरभूत व्योम trace_probe_clear_flag(काष्ठा trace_probe *tp,
					  अचिन्हित पूर्णांक flag)
अणु
	tp->event->flags &= ~flag;
पूर्ण

अटल अंतरभूत bool trace_probe_is_enabled(काष्ठा trace_probe *tp)
अणु
	वापस trace_probe_test_flag(tp, TP_FLAG_TRACE | TP_FLAG_PROखाता);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *trace_probe_name(काष्ठा trace_probe *tp)
अणु
	वापस trace_event_name(&tp->event->call);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *trace_probe_group_name(काष्ठा trace_probe *tp)
अणु
	वापस tp->event->call.class->प्रणाली;
पूर्ण

अटल अंतरभूत काष्ठा trace_event_call *
	trace_probe_event_call(काष्ठा trace_probe *tp)
अणु
	वापस &tp->event->call;
पूर्ण

अटल अंतरभूत काष्ठा trace_probe_event *
trace_probe_event_from_call(काष्ठा trace_event_call *event_call)
अणु
	वापस container_of(event_call, काष्ठा trace_probe_event, call);
पूर्ण

अटल अंतरभूत काष्ठा trace_probe *
trace_probe_primary_from_call(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_probe_event *tpe = trace_probe_event_from_call(call);

	वापस list_first_entry(&tpe->probes, काष्ठा trace_probe, list);
पूर्ण

अटल अंतरभूत काष्ठा list_head *trace_probe_probe_list(काष्ठा trace_probe *tp)
अणु
	वापस &tp->event->probes;
पूर्ण

अटल अंतरभूत bool trace_probe_has_sibling(काष्ठा trace_probe *tp)
अणु
	काष्ठा list_head *list = trace_probe_probe_list(tp);

	वापस !list_empty(list) && !list_is_singular(list);
पूर्ण

अटल अंतरभूत पूर्णांक trace_probe_unरेजिस्टर_event_call(काष्ठा trace_probe *tp)
अणु
	/* tp->event is unरेजिस्टरed in trace_हटाओ_event_call() */
	वापस trace_हटाओ_event_call(&tp->event->call);
पूर्ण

अटल अंतरभूत bool trace_probe_has_single_file(काष्ठा trace_probe *tp)
अणु
	वापस !!list_is_singular(&tp->event->files);
पूर्ण

पूर्णांक trace_probe_init(काष्ठा trace_probe *tp, स्थिर अक्षर *event,
		     स्थिर अक्षर *group, bool alloc_filter);
व्योम trace_probe_cleanup(काष्ठा trace_probe *tp);
पूर्णांक trace_probe_append(काष्ठा trace_probe *tp, काष्ठा trace_probe *to);
व्योम trace_probe_unlink(काष्ठा trace_probe *tp);
पूर्णांक trace_probe_रेजिस्टर_event_call(काष्ठा trace_probe *tp);
पूर्णांक trace_probe_add_file(काष्ठा trace_probe *tp, काष्ठा trace_event_file *file);
पूर्णांक trace_probe_हटाओ_file(काष्ठा trace_probe *tp,
			    काष्ठा trace_event_file *file);
काष्ठा event_file_link *trace_probe_get_file_link(काष्ठा trace_probe *tp,
						काष्ठा trace_event_file *file);
पूर्णांक trace_probe_compare_arg_type(काष्ठा trace_probe *a, काष्ठा trace_probe *b);
bool trace_probe_match_command_args(काष्ठा trace_probe *tp,
				    पूर्णांक argc, स्थिर अक्षर **argv);
पूर्णांक trace_probe_create(स्थिर अक्षर *raw_command, पूर्णांक (*createfn)(पूर्णांक, स्थिर अक्षर **));

#घोषणा trace_probe_क्रम_each_link(pos, tp)	\
	list_क्रम_each_entry(pos, &(tp)->event->files, list)
#घोषणा trace_probe_क्रम_each_link_rcu(pos, tp)	\
	list_क्रम_each_entry_rcu(pos, &(tp)->event->files, list)

#घोषणा TPARG_FL_RETURN BIT(0)
#घोषणा TPARG_FL_KERNEL BIT(1)
#घोषणा TPARG_FL_FENTRY BIT(2)
#घोषणा TPARG_FL_MASK	GENMASK(2, 0)

बाह्य पूर्णांक traceprobe_parse_probe_arg(काष्ठा trace_probe *tp, पूर्णांक i,
				अक्षर *arg, अचिन्हित पूर्णांक flags);

बाह्य पूर्णांक traceprobe_update_arg(काष्ठा probe_arg *arg);
बाह्य व्योम traceprobe_मुक्त_probe_arg(काष्ठा probe_arg *arg);

बाह्य पूर्णांक traceprobe_split_symbol_offset(अक्षर *symbol, दीर्घ *offset);
पूर्णांक traceprobe_parse_event_name(स्थिर अक्षर **pevent, स्थिर अक्षर **pgroup,
				अक्षर *buf, पूर्णांक offset);

बाह्य पूर्णांक traceprobe_set_prपूर्णांक_fmt(काष्ठा trace_probe *tp, bool is_वापस);

#अगर_घोषित CONFIG_PERF_EVENTS
बाह्य काष्ठा trace_event_call *
create_local_trace_kprobe(अक्षर *func, व्योम *addr, अचिन्हित दीर्घ offs,
			  bool is_वापस);
बाह्य व्योम destroy_local_trace_kprobe(काष्ठा trace_event_call *event_call);

बाह्य काष्ठा trace_event_call *
create_local_trace_uprobe(अक्षर *name, अचिन्हित दीर्घ offs,
			  अचिन्हित दीर्घ ref_ctr_offset, bool is_वापस);
बाह्य व्योम destroy_local_trace_uprobe(काष्ठा trace_event_call *event_call);
#पूर्ण_अगर
बाह्य पूर्णांक traceprobe_define_arg_fields(काष्ठा trace_event_call *event_call,
					माप_प्रकार offset, काष्ठा trace_probe *tp);

#अघोषित ERRORS
#घोषणा ERRORS	\
	C(खाता_NOT_FOUND,	"Failed to find the given file"),	\
	C(NO_REGULAR_खाता,	"Not a regular file"),			\
	C(BAD_REFCNT,		"Invalid reference counter offset"),	\
	C(REFCNT_OPEN_BRACE,	"Reference counter brace is not closed"), \
	C(BAD_REFCNT_SUFFIX,	"Reference counter has wrong suffix"),	\
	C(BAD_UPROBE_OFFS,	"Invalid uprobe offset"),		\
	C(MAXACT_NO_KPROBE,	"Maxactive is not for kprobe"),		\
	C(BAD_MAXACT,		"Invalid maxactive number"),		\
	C(MAXACT_TOO_BIG,	"Maxactive is too big"),		\
	C(BAD_PROBE_ADDR,	"Invalid probed address or symbol"),	\
	C(BAD_RETPROBE,		"Retprobe address must be an function entry"), \
	C(BAD_ADDR_SUFFIX,	"Invalid probed address suffix"), \
	C(NO_GROUP_NAME,	"Group name is not specified"),		\
	C(GROUP_TOO_LONG,	"Group name is too long"),		\
	C(BAD_GROUP_NAME,	"Group name must follow the same rules as C identifiers"), \
	C(NO_EVENT_NAME,	"Event name is not specified"),		\
	C(EVENT_TOO_LONG,	"Event name is too long"),		\
	C(BAD_EVENT_NAME,	"Event name must follow the same rules as C identifiers"), \
	C(RETVAL_ON_PROBE,	"$retval is not available on probe"),	\
	C(BAD_STACK_NUM,	"Invalid stack number"),		\
	C(BAD_ARG_NUM,		"Invalid argument number"),		\
	C(BAD_VAR,		"Invalid $-valiable specified"),	\
	C(BAD_REG_NAME,		"Invalid register name"),		\
	C(BAD_MEM_ADDR,		"Invalid memory address"),		\
	C(BAD_IMM,		"Invalid immediate value"),		\
	C(IMMSTR_NO_CLOSE,	"String is not closed with '\"'"),	\
	C(खाता_ON_KPROBE,	"File offset is not available with kprobe"), \
	C(BAD_खाता_OFFS,	"Invalid file offset value"),		\
	C(SYM_ON_UPROBE,	"Symbol is not available with uprobe"),	\
	C(TOO_MANY_OPS,		"Dereference is too much nested"), 	\
	C(DEREF_NEED_BRACE,	"Dereference needs a brace"),		\
	C(BAD_DEREF_OFFS,	"Invalid dereference offset"),		\
	C(DEREF_OPEN_BRACE,	"Dereference brace is not closed"),	\
	C(COMM_CANT_DEREF,	"$comm can not be dereferenced"),	\
	C(BAD_FETCH_ARG,	"Invalid fetch argument"),		\
	C(ARRAY_NO_CLOSE,	"Array is not closed"),			\
	C(BAD_ARRAY_SUFFIX,	"Array has wrong suffix"),		\
	C(BAD_ARRAY_NUM,	"Invalid array size"),			\
	C(ARRAY_TOO_BIG,	"Array number is too big"),		\
	C(BAD_TYPE,		"Unknown type is specified"),		\
	C(BAD_STRING,		"String accepts only memory argument"),	\
	C(BAD_BITFIELD,		"Invalid bitfield"),			\
	C(ARG_NAME_TOO_LONG,	"Argument name is too long"),		\
	C(NO_ARG_NAME,		"Argument name is not specified"),	\
	C(BAD_ARG_NAME,		"Argument name must follow the same rules as C identifiers"), \
	C(USED_ARG_NAME,	"This argument name is already used"),	\
	C(ARG_TOO_LONG,		"Argument expression is too long"),	\
	C(NO_ARG_BODY,		"No argument expression"),		\
	C(BAD_INSN_BNDRY,	"Probe point is not an instruction boundary"),\
	C(FAIL_REG_PROBE,	"Failed to register probe event"),\
	C(DIFF_PROBE_TYPE,	"Probe type is different from existing probe"),\
	C(DIFF_ARG_TYPE,	"Argument type or name is different from existing probe"),\
	C(SAME_PROBE,		"There is already the exact same probe event"),

#अघोषित C
#घोषणा C(a, b)		TP_ERR_##a

/* Define TP_ERR_ */
क्रमागत अणु ERRORS पूर्ण;

/* Error text is defined in trace_probe.c */

काष्ठा trace_probe_log अणु
	स्थिर अक्षर	*subप्रणाली;
	स्थिर अक्षर	**argv;
	पूर्णांक		argc;
	पूर्णांक		index;
पूर्ण;

व्योम trace_probe_log_init(स्थिर अक्षर *subप्रणाली, पूर्णांक argc, स्थिर अक्षर **argv);
व्योम trace_probe_log_set_index(पूर्णांक index);
व्योम trace_probe_log_clear(व्योम);
व्योम __trace_probe_log_err(पूर्णांक offset, पूर्णांक err);

#घोषणा trace_probe_log_err(offs, err)	\
	__trace_probe_log_err(offs, TP_ERR_##err)
