<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common code क्रम probe-based Dynamic events.
 *
 * This code was copied from kernel/trace/trace_kprobe.c written by
 * Masami Hiramatsu <masami.hiramatsu.pt@hitachi.com>
 *
 * Updates to make this generic:
 * Copyright (C) IBM Corporation, 2010-2011
 * Author:     Srikar Dronamraju
 */
#घोषणा pr_fmt(fmt)	"trace_probe: " fmt

#समावेश "trace_probe.h"

#अघोषित C
#घोषणा C(a, b)		b

अटल स्थिर अक्षर *trace_probe_err_text[] = अणु ERRORS पूर्ण;

अटल स्थिर अक्षर *reserved_field_names[] = अणु
	"common_type",
	"common_flags",
	"common_preempt_count",
	"common_pid",
	"common_tgid",
	FIELD_STRING_IP,
	FIELD_STRING_RETIP,
	FIELD_STRING_FUNC,
पूर्ण;

/* Prपूर्णांकing  in basic type function ढाँचा */
#घोषणा DEFINE_BASIC_PRINT_TYPE_FUNC(tname, type, fmt)			\
पूर्णांक PRINT_TYPE_FUNC_NAME(tname)(काष्ठा trace_seq *s, व्योम *data, व्योम *ent)\
अणु									\
	trace_seq_म_लिखो(s, fmt, *(type *)data);			\
	वापस !trace_seq_has_overflowed(s);				\
पूर्ण									\
स्थिर अक्षर PRINT_TYPE_FMT_NAME(tname)[] = fmt;

DEFINE_BASIC_PRINT_TYPE_FUNC(u8,  u8,  "%u")
DEFINE_BASIC_PRINT_TYPE_FUNC(u16, u16, "%u")
DEFINE_BASIC_PRINT_TYPE_FUNC(u32, u32, "%u")
DEFINE_BASIC_PRINT_TYPE_FUNC(u64, u64, "%Lu")
DEFINE_BASIC_PRINT_TYPE_FUNC(s8,  s8,  "%d")
DEFINE_BASIC_PRINT_TYPE_FUNC(s16, s16, "%d")
DEFINE_BASIC_PRINT_TYPE_FUNC(s32, s32, "%d")
DEFINE_BASIC_PRINT_TYPE_FUNC(s64, s64, "%Ld")
DEFINE_BASIC_PRINT_TYPE_FUNC(x8,  u8,  "0x%x")
DEFINE_BASIC_PRINT_TYPE_FUNC(x16, u16, "0x%x")
DEFINE_BASIC_PRINT_TYPE_FUNC(x32, u32, "0x%x")
DEFINE_BASIC_PRINT_TYPE_FUNC(x64, u64, "0x%Lx")

पूर्णांक PRINT_TYPE_FUNC_NAME(symbol)(काष्ठा trace_seq *s, व्योम *data, व्योम *ent)
अणु
	trace_seq_म_लिखो(s, "%pS", (व्योम *)*(अचिन्हित दीर्घ *)data);
	वापस !trace_seq_has_overflowed(s);
पूर्ण
स्थिर अक्षर PRINT_TYPE_FMT_NAME(symbol)[] = "%pS";

/* Prपूर्णांक type function क्रम string type */
पूर्णांक PRINT_TYPE_FUNC_NAME(string)(काष्ठा trace_seq *s, व्योम *data, व्योम *ent)
अणु
	पूर्णांक len = *(u32 *)data >> 16;

	अगर (!len)
		trace_seq_माला_दो(s, "(fault)");
	अन्यथा
		trace_seq_म_लिखो(s, "\"%s\"",
				 (स्थिर अक्षर *)get_loc_data(data, ent));
	वापस !trace_seq_has_overflowed(s);
पूर्ण

स्थिर अक्षर PRINT_TYPE_FMT_NAME(string)[] = "\\\"%s\\\"";

/* Fetch type inक्रमmation table */
अटल स्थिर काष्ठा fetch_type probe_fetch_types[] = अणु
	/* Special types */
	__ASSIGN_FETCH_TYPE("string", string, string, माप(u32), 1,
			    "__data_loc char[]"),
	__ASSIGN_FETCH_TYPE("ustring", string, string, माप(u32), 1,
			    "__data_loc char[]"),
	/* Basic types */
	ASSIGN_FETCH_TYPE(u8,  u8,  0),
	ASSIGN_FETCH_TYPE(u16, u16, 0),
	ASSIGN_FETCH_TYPE(u32, u32, 0),
	ASSIGN_FETCH_TYPE(u64, u64, 0),
	ASSIGN_FETCH_TYPE(s8,  u8,  1),
	ASSIGN_FETCH_TYPE(s16, u16, 1),
	ASSIGN_FETCH_TYPE(s32, u32, 1),
	ASSIGN_FETCH_TYPE(s64, u64, 1),
	ASSIGN_FETCH_TYPE_ALIAS(x8,  u8,  u8,  0),
	ASSIGN_FETCH_TYPE_ALIAS(x16, u16, u16, 0),
	ASSIGN_FETCH_TYPE_ALIAS(x32, u32, u32, 0),
	ASSIGN_FETCH_TYPE_ALIAS(x64, u64, u64, 0),
	ASSIGN_FETCH_TYPE_ALIAS(symbol, ADDR_FETCH_TYPE, ADDR_FETCH_TYPE, 0),

	ASSIGN_FETCH_TYPE_END
पूर्ण;

अटल स्थिर काष्ठा fetch_type *find_fetch_type(स्थिर अक्षर *type)
अणु
	पूर्णांक i;

	अगर (!type)
		type = DEFAULT_FETCH_TYPE_STR;

	/* Special हाल: bitfield */
	अगर (*type == 'b') अणु
		अचिन्हित दीर्घ bs;

		type = म_अक्षर(type, '/');
		अगर (!type)
			जाओ fail;

		type++;
		अगर (kम_से_अदीर्घ(type, 0, &bs))
			जाओ fail;

		चयन (bs) अणु
		हाल 8:
			वापस find_fetch_type("u8");
		हाल 16:
			वापस find_fetch_type("u16");
		हाल 32:
			वापस find_fetch_type("u32");
		हाल 64:
			वापस find_fetch_type("u64");
		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; probe_fetch_types[i].name; i++) अणु
		अगर (म_भेद(type, probe_fetch_types[i].name) == 0)
			वापस &probe_fetch_types[i];
	पूर्ण

fail:
	वापस शून्य;
पूर्ण

अटल काष्ठा trace_probe_log trace_probe_log;

व्योम trace_probe_log_init(स्थिर अक्षर *subप्रणाली, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	trace_probe_log.subप्रणाली = subप्रणाली;
	trace_probe_log.argc = argc;
	trace_probe_log.argv = argv;
	trace_probe_log.index = 0;
पूर्ण

व्योम trace_probe_log_clear(व्योम)
अणु
	स_रखो(&trace_probe_log, 0, माप(trace_probe_log));
पूर्ण

व्योम trace_probe_log_set_index(पूर्णांक index)
अणु
	trace_probe_log.index = index;
पूर्ण

व्योम __trace_probe_log_err(पूर्णांक offset, पूर्णांक err_type)
अणु
	अक्षर *command, *p;
	पूर्णांक i, len = 0, pos = 0;

	अगर (!trace_probe_log.argv)
		वापस;

	/* Recalculate the length and allocate buffer */
	क्रम (i = 0; i < trace_probe_log.argc; i++) अणु
		अगर (i == trace_probe_log.index)
			pos = len;
		len += म_माप(trace_probe_log.argv[i]) + 1;
	पूर्ण
	command = kzalloc(len, GFP_KERNEL);
	अगर (!command)
		वापस;

	अगर (trace_probe_log.index >= trace_probe_log.argc) अणु
		/**
		 * Set the error position is next to the last arg + space.
		 * Note that len includes the terminal null and the cursor
		 * appears at pos + 1.
		 */
		pos = len;
		offset = 0;
	पूर्ण

	/* And make a command string from argv array */
	p = command;
	क्रम (i = 0; i < trace_probe_log.argc; i++) अणु
		len = म_माप(trace_probe_log.argv[i]);
		म_नकल(p, trace_probe_log.argv[i]);
		p[len] = ' ';
		p += len + 1;
	पूर्ण
	*(p - 1) = '\0';

	tracing_log_err(शून्य, trace_probe_log.subप्रणाली, command,
			trace_probe_err_text, err_type, pos + offset);

	kमुक्त(command);
पूर्ण

/* Split symbol and offset. */
पूर्णांक traceprobe_split_symbol_offset(अक्षर *symbol, दीर्घ *offset)
अणु
	अक्षर *पंचांगp;
	पूर्णांक ret;

	अगर (!offset)
		वापस -EINVAL;

	पंचांगp = strpbrk(symbol, "+-");
	अगर (पंचांगp) अणु
		ret = kम_से_दीर्घ(पंचांगp, 0, offset);
		अगर (ret)
			वापस ret;
		*पंचांगp = '\0';
	पूर्ण अन्यथा
		*offset = 0;

	वापस 0;
पूर्ण

/* @buf must has MAX_EVENT_NAME_LEN size */
पूर्णांक traceprobe_parse_event_name(स्थिर अक्षर **pevent, स्थिर अक्षर **pgroup,
				अक्षर *buf, पूर्णांक offset)
अणु
	स्थिर अक्षर *slash, *event = *pevent;
	पूर्णांक len;

	slash = म_अक्षर(event, '/');
	अगर (slash) अणु
		अगर (slash == event) अणु
			trace_probe_log_err(offset, NO_GROUP_NAME);
			वापस -EINVAL;
		पूर्ण
		अगर (slash - event + 1 > MAX_EVENT_NAME_LEN) अणु
			trace_probe_log_err(offset, GROUP_TOO_LONG);
			वापस -EINVAL;
		पूर्ण
		strlcpy(buf, event, slash - event + 1);
		अगर (!is_good_name(buf)) अणु
			trace_probe_log_err(offset, BAD_GROUP_NAME);
			वापस -EINVAL;
		पूर्ण
		*pgroup = buf;
		*pevent = slash + 1;
		offset += slash - event + 1;
		event = *pevent;
	पूर्ण
	len = म_माप(event);
	अगर (len == 0) अणु
		trace_probe_log_err(offset, NO_EVENT_NAME);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (len > MAX_EVENT_NAME_LEN) अणु
		trace_probe_log_err(offset, EVENT_TOO_LONG);
		वापस -EINVAL;
	पूर्ण
	अगर (!is_good_name(event)) अणु
		trace_probe_log_err(offset, BAD_EVENT_NAME);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा PARAM_MAX_STACK (THREAD_SIZE / माप(अचिन्हित दीर्घ))

अटल पूर्णांक parse_probe_vars(अक्षर *arg, स्थिर काष्ठा fetch_type *t,
			काष्ठा fetch_insn *code, अचिन्हित पूर्णांक flags, पूर्णांक offs)
अणु
	अचिन्हित दीर्घ param;
	पूर्णांक ret = 0;
	पूर्णांक len;

	अगर (म_भेद(arg, "retval") == 0) अणु
		अगर (flags & TPARG_FL_RETURN) अणु
			code->op = FETCH_OP_RETVAL;
		पूर्ण अन्यथा अणु
			trace_probe_log_err(offs, RETVAL_ON_PROBE);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर ((len = str_has_prefix(arg, "stack"))) अणु
		अगर (arg[len] == '\0') अणु
			code->op = FETCH_OP_STACKP;
		पूर्ण अन्यथा अगर (है_अंक(arg[len])) अणु
			ret = kम_से_अदीर्घ(arg + len, 10, &param);
			अगर (ret) अणु
				जाओ inval_var;
			पूर्ण अन्यथा अगर ((flags & TPARG_FL_KERNEL) &&
				    param > PARAM_MAX_STACK) अणु
				trace_probe_log_err(offs, BAD_STACK_NUM);
				ret = -EINVAL;
			पूर्ण अन्यथा अणु
				code->op = FETCH_OP_STACK;
				code->param = (अचिन्हित पूर्णांक)param;
			पूर्ण
		पूर्ण अन्यथा
			जाओ inval_var;
	पूर्ण अन्यथा अगर (म_भेद(arg, "comm") == 0) अणु
		code->op = FETCH_OP_COMM;
#अगर_घोषित CONFIG_HAVE_FUNCTION_ARG_ACCESS_API
	पूर्ण अन्यथा अगर (((flags & TPARG_FL_MASK) ==
		    (TPARG_FL_KERNEL | TPARG_FL_FENTRY)) &&
		   (len = str_has_prefix(arg, "arg"))) अणु
		ret = kम_से_अदीर्घ(arg + len, 10, &param);
		अगर (ret) अणु
			जाओ inval_var;
		पूर्ण अन्यथा अगर (!param || param > PARAM_MAX_STACK) अणु
			trace_probe_log_err(offs, BAD_ARG_NUM);
			वापस -EINVAL;
		पूर्ण
		code->op = FETCH_OP_ARG;
		code->param = (अचिन्हित पूर्णांक)param - 1;
#पूर्ण_अगर
	पूर्ण अन्यथा
		जाओ inval_var;

	वापस ret;

inval_var:
	trace_probe_log_err(offs, BAD_VAR);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक str_to_immediate(अक्षर *str, अचिन्हित दीर्घ *imm)
अणु
	अगर (है_अंक(str[0]))
		वापस kम_से_अदीर्घ(str, 0, imm);
	अन्यथा अगर (str[0] == '-')
		वापस kम_से_दीर्घ(str, 0, (दीर्घ *)imm);
	अन्यथा अगर (str[0] == '+')
		वापस kम_से_दीर्घ(str + 1, 0, (दीर्घ *)imm);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __parse_imm_string(अक्षर *str, अक्षर **pbuf, पूर्णांक offs)
अणु
	माप_प्रकार len = म_माप(str);

	अगर (str[len - 1] != '"') अणु
		trace_probe_log_err(offs + len, IMMSTR_NO_CLOSE);
		वापस -EINVAL;
	पूर्ण
	*pbuf = kstrndup(str, len - 1, GFP_KERNEL);
	वापस 0;
पूर्ण

/* Recursive argument parser */
अटल पूर्णांक
parse_probe_arg(अक्षर *arg, स्थिर काष्ठा fetch_type *type,
		काष्ठा fetch_insn **pcode, काष्ठा fetch_insn *end,
		अचिन्हित पूर्णांक flags, पूर्णांक offs)
अणु
	काष्ठा fetch_insn *code = *pcode;
	अचिन्हित दीर्घ param;
	पूर्णांक deref = FETCH_OP_DEREF;
	दीर्घ offset = 0;
	अक्षर *पंचांगp;
	पूर्णांक ret = 0;

	चयन (arg[0]) अणु
	हाल '$':
		ret = parse_probe_vars(arg + 1, type, code, flags, offs);
		अवरोध;

	हाल '%':	/* named रेजिस्टर */
		ret = regs_query_रेजिस्टर_offset(arg + 1);
		अगर (ret >= 0) अणु
			code->op = FETCH_OP_REG;
			code->param = (अचिन्हित पूर्णांक)ret;
			ret = 0;
		पूर्ण अन्यथा
			trace_probe_log_err(offs, BAD_REG_NAME);
		अवरोध;

	हाल '@':	/* memory, file-offset or symbol */
		अगर (है_अंक(arg[1])) अणु
			ret = kम_से_अदीर्घ(arg + 1, 0, &param);
			अगर (ret) अणु
				trace_probe_log_err(offs, BAD_MEM_ADDR);
				अवरोध;
			पूर्ण
			/* load address */
			code->op = FETCH_OP_IMM;
			code->immediate = param;
		पूर्ण अन्यथा अगर (arg[1] == '+') अणु
			/* kprobes करोn't support file offsets */
			अगर (flags & TPARG_FL_KERNEL) अणु
				trace_probe_log_err(offs, खाता_ON_KPROBE);
				वापस -EINVAL;
			पूर्ण
			ret = kम_से_दीर्घ(arg + 2, 0, &offset);
			अगर (ret) अणु
				trace_probe_log_err(offs, BAD_खाता_OFFS);
				अवरोध;
			पूर्ण

			code->op = FETCH_OP_FOFFS;
			code->immediate = (अचिन्हित दीर्घ)offset;  // imm64?
		पूर्ण अन्यथा अणु
			/* uprobes करोn't support symbols */
			अगर (!(flags & TPARG_FL_KERNEL)) अणु
				trace_probe_log_err(offs, SYM_ON_UPROBE);
				वापस -EINVAL;
			पूर्ण
			/* Preserve symbol क्रम updating */
			code->op = FETCH_NOP_SYMBOL;
			code->data = kstrdup(arg + 1, GFP_KERNEL);
			अगर (!code->data)
				वापस -ENOMEM;
			अगर (++code == end) अणु
				trace_probe_log_err(offs, TOO_MANY_OPS);
				वापस -EINVAL;
			पूर्ण
			code->op = FETCH_OP_IMM;
			code->immediate = 0;
		पूर्ण
		/* These are fetching from memory */
		अगर (++code == end) अणु
			trace_probe_log_err(offs, TOO_MANY_OPS);
			वापस -EINVAL;
		पूर्ण
		*pcode = code;
		code->op = FETCH_OP_DEREF;
		code->offset = offset;
		अवरोध;

	हाल '+':	/* deref memory */
	हाल '-':
		अगर (arg[1] == 'u') अणु
			deref = FETCH_OP_UDEREF;
			arg[1] = arg[0];
			arg++;
		पूर्ण
		अगर (arg[0] == '+')
			arg++;	/* Skip '+', because kम_से_दीर्घ() rejects it. */
		पंचांगp = म_अक्षर(arg, '(');
		अगर (!पंचांगp) अणु
			trace_probe_log_err(offs, DEREF_NEED_BRACE);
			वापस -EINVAL;
		पूर्ण
		*पंचांगp = '\0';
		ret = kम_से_दीर्घ(arg, 0, &offset);
		अगर (ret) अणु
			trace_probe_log_err(offs, BAD_DEREF_OFFS);
			अवरोध;
		पूर्ण
		offs += (पंचांगp + 1 - arg) + (arg[0] != '-' ? 1 : 0);
		arg = पंचांगp + 1;
		पंचांगp = म_खोजप(arg, ')');
		अगर (!पंचांगp) अणु
			trace_probe_log_err(offs + म_माप(arg),
					    DEREF_OPEN_BRACE);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा fetch_type *t2 = find_fetch_type(शून्य);

			*पंचांगp = '\0';
			ret = parse_probe_arg(arg, t2, &code, end, flags, offs);
			अगर (ret)
				अवरोध;
			अगर (code->op == FETCH_OP_COMM ||
			    code->op == FETCH_OP_DATA) अणु
				trace_probe_log_err(offs, COMM_CANT_DEREF);
				वापस -EINVAL;
			पूर्ण
			अगर (++code == end) अणु
				trace_probe_log_err(offs, TOO_MANY_OPS);
				वापस -EINVAL;
			पूर्ण
			*pcode = code;

			code->op = deref;
			code->offset = offset;
		पूर्ण
		अवरोध;
	हाल '\\':	/* Immediate value */
		अगर (arg[1] == '"') अणु	/* Immediate string */
			ret = __parse_imm_string(arg + 2, &पंचांगp, offs + 2);
			अगर (ret)
				अवरोध;
			code->op = FETCH_OP_DATA;
			code->data = पंचांगp;
		पूर्ण अन्यथा अणु
			ret = str_to_immediate(arg + 1, &code->immediate);
			अगर (ret)
				trace_probe_log_err(offs + 1, BAD_IMM);
			अन्यथा
				code->op = FETCH_OP_IMM;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (!ret && code->op == FETCH_OP_NOP) अणु
		/* Parsed, but करो not find fetch method */
		trace_probe_log_err(offs, BAD_FETCH_ARG);
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा BYTES_TO_BITS(nb)	((BITS_PER_LONG * (nb)) / माप(दीर्घ))

/* Bitfield type needs to be parsed पूर्णांकo a fetch function */
अटल पूर्णांक __parse_bitfield_probe_arg(स्थिर अक्षर *bf,
				      स्थिर काष्ठा fetch_type *t,
				      काष्ठा fetch_insn **pcode)
अणु
	काष्ठा fetch_insn *code = *pcode;
	अचिन्हित दीर्घ bw, bo;
	अक्षर *tail;

	अगर (*bf != 'b')
		वापस 0;

	bw = simple_म_से_अदीर्घ(bf + 1, &tail, 0);	/* Use simple one */

	अगर (bw == 0 || *tail != '@')
		वापस -EINVAL;

	bf = tail + 1;
	bo = simple_म_से_अदीर्घ(bf, &tail, 0);

	अगर (tail == bf || *tail != '/')
		वापस -EINVAL;
	code++;
	अगर (code->op != FETCH_OP_NOP)
		वापस -EINVAL;
	*pcode = code;

	code->op = FETCH_OP_MOD_BF;
	code->lshअगरt = BYTES_TO_BITS(t->size) - (bw + bo);
	code->rshअगरt = BYTES_TO_BITS(t->size) - bw;
	code->basesize = t->size;

	वापस (BYTES_TO_BITS(t->size) < (bw + bo)) ? -EINVAL : 0;
पूर्ण

/* String length checking wrapper */
अटल पूर्णांक traceprobe_parse_probe_arg_body(अक्षर *arg, sमाप_प्रकार *size,
		काष्ठा probe_arg *parg, अचिन्हित पूर्णांक flags, पूर्णांक offset)
अणु
	काष्ठा fetch_insn *code, *scode, *पंचांगp = शून्य;
	अक्षर *t, *t2, *t3;
	पूर्णांक ret, len;

	len = म_माप(arg);
	अगर (len > MAX_ARGSTR_LEN) अणु
		trace_probe_log_err(offset, ARG_TOO_LONG);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (len == 0) अणु
		trace_probe_log_err(offset, NO_ARG_BODY);
		वापस -EINVAL;
	पूर्ण

	parg->comm = kstrdup(arg, GFP_KERNEL);
	अगर (!parg->comm)
		वापस -ENOMEM;

	t = म_अक्षर(arg, ':');
	अगर (t) अणु
		*t = '\0';
		t2 = म_अक्षर(++t, '[');
		अगर (t2) अणु
			*t2++ = '\0';
			t3 = म_अक्षर(t2, ']');
			अगर (!t3) अणु
				offset += t2 + म_माप(t2) - arg;
				trace_probe_log_err(offset,
						    ARRAY_NO_CLOSE);
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (t3[1] != '\0') अणु
				trace_probe_log_err(offset + t3 + 1 - arg,
						    BAD_ARRAY_SUFFIX);
				वापस -EINVAL;
			पूर्ण
			*t3 = '\0';
			अगर (kstrtouपूर्णांक(t2, 0, &parg->count) || !parg->count) अणु
				trace_probe_log_err(offset + t2 - arg,
						    BAD_ARRAY_NUM);
				वापस -EINVAL;
			पूर्ण
			अगर (parg->count > MAX_ARRAY_LEN) अणु
				trace_probe_log_err(offset + t2 - arg,
						    ARRAY_TOO_BIG);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Since $comm and immediate string can not be dereferenced,
	 * we can find those by म_भेद.
	 */
	अगर (म_भेद(arg, "$comm") == 0 || म_भेदन(arg, "\\\"", 2) == 0) अणु
		/* The type of $comm must be "string", and not an array. */
		अगर (parg->count || (t && म_भेद(t, "string")))
			वापस -EINVAL;
		parg->type = find_fetch_type("string");
	पूर्ण अन्यथा
		parg->type = find_fetch_type(t);
	अगर (!parg->type) अणु
		trace_probe_log_err(offset + (t ? (t - arg) : 0), BAD_TYPE);
		वापस -EINVAL;
	पूर्ण
	parg->offset = *size;
	*size += parg->type->size * (parg->count ?: 1);

	अगर (parg->count) अणु
		len = म_माप(parg->type->fmttype) + 6;
		parg->fmt = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!parg->fmt)
			वापस -ENOMEM;
		snम_लिखो(parg->fmt, len, "%s[%d]", parg->type->fmttype,
			 parg->count);
	पूर्ण

	code = पंचांगp = kसुस्मृति(FETCH_INSN_MAX, माप(*code), GFP_KERNEL);
	अगर (!code)
		वापस -ENOMEM;
	code[FETCH_INSN_MAX - 1].op = FETCH_OP_END;

	ret = parse_probe_arg(arg, parg->type, &code, &code[FETCH_INSN_MAX - 1],
			      flags, offset);
	अगर (ret)
		जाओ fail;

	/* Store operation */
	अगर (!म_भेद(parg->type->name, "string") ||
	    !म_भेद(parg->type->name, "ustring")) अणु
		अगर (code->op != FETCH_OP_DEREF && code->op != FETCH_OP_UDEREF &&
		    code->op != FETCH_OP_IMM && code->op != FETCH_OP_COMM &&
		    code->op != FETCH_OP_DATA) अणु
			trace_probe_log_err(offset + (t ? (t - arg) : 0),
					    BAD_STRING);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
		अगर ((code->op == FETCH_OP_IMM || code->op == FETCH_OP_COMM ||
		     code->op == FETCH_OP_DATA) || parg->count) अणु
			/*
			 * IMM, DATA and COMM is poपूर्णांकing actual address, those
			 * must be kept, and अगर parg->count != 0, this is an
			 * array of string poपूर्णांकers instead of string address
			 * itself.
			 */
			code++;
			अगर (code->op != FETCH_OP_NOP) अणु
				trace_probe_log_err(offset, TOO_MANY_OPS);
				ret = -EINVAL;
				जाओ fail;
			पूर्ण
		पूर्ण
		/* If op == DEREF, replace it with STRING */
		अगर (!म_भेद(parg->type->name, "ustring") ||
		    code->op == FETCH_OP_UDEREF)
			code->op = FETCH_OP_ST_USTRING;
		अन्यथा
			code->op = FETCH_OP_ST_STRING;
		code->size = parg->type->size;
		parg->dynamic = true;
	पूर्ण अन्यथा अगर (code->op == FETCH_OP_DEREF) अणु
		code->op = FETCH_OP_ST_MEM;
		code->size = parg->type->size;
	पूर्ण अन्यथा अगर (code->op == FETCH_OP_UDEREF) अणु
		code->op = FETCH_OP_ST_UMEM;
		code->size = parg->type->size;
	पूर्ण अन्यथा अणु
		code++;
		अगर (code->op != FETCH_OP_NOP) अणु
			trace_probe_log_err(offset, TOO_MANY_OPS);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
		code->op = FETCH_OP_ST_RAW;
		code->size = parg->type->size;
	पूर्ण
	scode = code;
	/* Modअगरy operation */
	अगर (t != शून्य) अणु
		ret = __parse_bitfield_probe_arg(t, parg->type, &code);
		अगर (ret) अणु
			trace_probe_log_err(offset + t - arg, BAD_BITFIELD);
			जाओ fail;
		पूर्ण
	पूर्ण
	/* Loop(Array) operation */
	अगर (parg->count) अणु
		अगर (scode->op != FETCH_OP_ST_MEM &&
		    scode->op != FETCH_OP_ST_STRING &&
		    scode->op != FETCH_OP_ST_USTRING) अणु
			trace_probe_log_err(offset + (t ? (t - arg) : 0),
					    BAD_STRING);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
		code++;
		अगर (code->op != FETCH_OP_NOP) अणु
			trace_probe_log_err(offset, TOO_MANY_OPS);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
		code->op = FETCH_OP_LP_ARRAY;
		code->param = parg->count;
	पूर्ण
	code++;
	code->op = FETCH_OP_END;

	/* Shrink करोwn the code buffer */
	parg->code = kसुस्मृति(code - पंचांगp + 1, माप(*code), GFP_KERNEL);
	अगर (!parg->code)
		ret = -ENOMEM;
	अन्यथा
		स_नकल(parg->code, पंचांगp, माप(*code) * (code - पंचांगp + 1));

fail:
	अगर (ret) अणु
		क्रम (code = पंचांगp; code < पंचांगp + FETCH_INSN_MAX; code++)
			अगर (code->op == FETCH_NOP_SYMBOL ||
			    code->op == FETCH_OP_DATA)
				kमुक्त(code->data);
	पूर्ण
	kमुक्त(पंचांगp);

	वापस ret;
पूर्ण

/* Return 1 अगर name is reserved or alपढ़ोy used by another argument */
अटल पूर्णांक traceprobe_conflict_field_name(स्थिर अक्षर *name,
					  काष्ठा probe_arg *args, पूर्णांक narg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reserved_field_names); i++)
		अगर (म_भेद(reserved_field_names[i], name) == 0)
			वापस 1;

	क्रम (i = 0; i < narg; i++)
		अगर (म_भेद(args[i].name, name) == 0)
			वापस 1;

	वापस 0;
पूर्ण

पूर्णांक traceprobe_parse_probe_arg(काष्ठा trace_probe *tp, पूर्णांक i, अक्षर *arg,
				अचिन्हित पूर्णांक flags)
अणु
	काष्ठा probe_arg *parg = &tp->args[i];
	अक्षर *body;

	/* Increment count क्रम मुक्तing args in error हाल */
	tp->nr_args++;

	body = म_अक्षर(arg, '=');
	अगर (body) अणु
		अगर (body - arg > MAX_ARG_NAME_LEN) अणु
			trace_probe_log_err(0, ARG_NAME_TOO_LONG);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (body == arg) अणु
			trace_probe_log_err(0, NO_ARG_NAME);
			वापस -EINVAL;
		पूर्ण
		parg->name = kmemdup_nul(arg, body - arg, GFP_KERNEL);
		body++;
	पूर्ण अन्यथा अणु
		/* If argument name is omitted, set "argN" */
		parg->name = kaप्र_लिखो(GFP_KERNEL, "arg%d", i + 1);
		body = arg;
	पूर्ण
	अगर (!parg->name)
		वापस -ENOMEM;

	अगर (!is_good_name(parg->name)) अणु
		trace_probe_log_err(0, BAD_ARG_NAME);
		वापस -EINVAL;
	पूर्ण
	अगर (traceprobe_conflict_field_name(parg->name, tp->args, i)) अणु
		trace_probe_log_err(0, USED_ARG_NAME);
		वापस -EINVAL;
	पूर्ण
	/* Parse fetch argument */
	वापस traceprobe_parse_probe_arg_body(body, &tp->size, parg, flags,
					       body - arg);
पूर्ण

व्योम traceprobe_मुक्त_probe_arg(काष्ठा probe_arg *arg)
अणु
	काष्ठा fetch_insn *code = arg->code;

	जबतक (code && code->op != FETCH_OP_END) अणु
		अगर (code->op == FETCH_NOP_SYMBOL ||
		    code->op == FETCH_OP_DATA)
			kमुक्त(code->data);
		code++;
	पूर्ण
	kमुक्त(arg->code);
	kमुक्त(arg->name);
	kमुक्त(arg->comm);
	kमुक्त(arg->fmt);
पूर्ण

पूर्णांक traceprobe_update_arg(काष्ठा probe_arg *arg)
अणु
	काष्ठा fetch_insn *code = arg->code;
	दीर्घ offset;
	अक्षर *पंचांगp;
	अक्षर c;
	पूर्णांक ret = 0;

	जबतक (code && code->op != FETCH_OP_END) अणु
		अगर (code->op == FETCH_NOP_SYMBOL) अणु
			अगर (code[1].op != FETCH_OP_IMM)
				वापस -EINVAL;

			पंचांगp = strpbrk(code->data, "+-");
			अगर (पंचांगp)
				c = *पंचांगp;
			ret = traceprobe_split_symbol_offset(code->data,
							     &offset);
			अगर (ret)
				वापस ret;

			code[1].immediate =
				(अचिन्हित दीर्घ)kallsyms_lookup_name(code->data);
			अगर (पंचांगp)
				*पंचांगp = c;
			अगर (!code[1].immediate)
				वापस -ENOENT;
			code[1].immediate += offset;
		पूर्ण
		code++;
	पूर्ण
	वापस 0;
पूर्ण

/* When len=0, we just calculate the needed length */
#घोषणा LEN_OR_ZERO (len ? len - pos : 0)
अटल पूर्णांक __set_prपूर्णांक_fmt(काष्ठा trace_probe *tp, अक्षर *buf, पूर्णांक len,
			   bool is_वापस)
अणु
	काष्ठा probe_arg *parg;
	पूर्णांक i, j;
	पूर्णांक pos = 0;
	स्थिर अक्षर *fmt, *arg;

	अगर (!is_वापस) अणु
		fmt = "(%lx)";
		arg = "REC->" FIELD_STRING_IP;
	पूर्ण अन्यथा अणु
		fmt = "(%lx <- %lx)";
		arg = "REC->" FIELD_STRING_FUNC ", REC->" FIELD_STRING_RETIP;
	पूर्ण

	pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "\"%s", fmt);

	क्रम (i = 0; i < tp->nr_args; i++) अणु
		parg = tp->args + i;
		pos += snम_लिखो(buf + pos, LEN_OR_ZERO, " %s=", parg->name);
		अगर (parg->count) अणु
			pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "{%s",
					parg->type->fmt);
			क्रम (j = 1; j < parg->count; j++)
				pos += snम_लिखो(buf + pos, LEN_OR_ZERO, ",%s",
						parg->type->fmt);
			pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "}");
		पूर्ण अन्यथा
			pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "%s",
					parg->type->fmt);
	पूर्ण

	pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "\", %s", arg);

	क्रम (i = 0; i < tp->nr_args; i++) अणु
		parg = tp->args + i;
		अगर (parg->count) अणु
			अगर ((म_भेद(parg->type->name, "string") == 0) ||
			    (म_भेद(parg->type->name, "ustring") == 0))
				fmt = ", __get_str(%s[%d])";
			अन्यथा
				fmt = ", REC->%s[%d]";
			क्रम (j = 0; j < parg->count; j++)
				pos += snम_लिखो(buf + pos, LEN_OR_ZERO,
						fmt, parg->name, j);
		पूर्ण अन्यथा अणु
			अगर ((म_भेद(parg->type->name, "string") == 0) ||
			    (म_भेद(parg->type->name, "ustring") == 0))
				fmt = ", __get_str(%s)";
			अन्यथा
				fmt = ", REC->%s";
			pos += snम_लिखो(buf + pos, LEN_OR_ZERO,
					fmt, parg->name);
		पूर्ण
	पूर्ण

	/* वापस the length of prपूर्णांक_fmt */
	वापस pos;
पूर्ण
#अघोषित LEN_OR_ZERO

पूर्णांक traceprobe_set_prपूर्णांक_fmt(काष्ठा trace_probe *tp, bool is_वापस)
अणु
	काष्ठा trace_event_call *call = trace_probe_event_call(tp);
	पूर्णांक len;
	अक्षर *prपूर्णांक_fmt;

	/* First: called with 0 length to calculate the needed length */
	len = __set_prपूर्णांक_fmt(tp, शून्य, 0, is_वापस);
	prपूर्णांक_fmt = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!prपूर्णांक_fmt)
		वापस -ENOMEM;

	/* Second: actually ग_लिखो the @prपूर्णांक_fmt */
	__set_prपूर्णांक_fmt(tp, prपूर्णांक_fmt, len + 1, is_वापस);
	call->prपूर्णांक_fmt = prपूर्णांक_fmt;

	वापस 0;
पूर्ण

पूर्णांक traceprobe_define_arg_fields(काष्ठा trace_event_call *event_call,
				 माप_प्रकार offset, काष्ठा trace_probe *tp)
अणु
	पूर्णांक ret, i;

	/* Set argument names as fields */
	क्रम (i = 0; i < tp->nr_args; i++) अणु
		काष्ठा probe_arg *parg = &tp->args[i];
		स्थिर अक्षर *fmt = parg->type->fmttype;
		पूर्णांक size = parg->type->size;

		अगर (parg->fmt)
			fmt = parg->fmt;
		अगर (parg->count)
			size *= parg->count;
		ret = trace_define_field(event_call, fmt, parg->name,
					 offset + parg->offset, size,
					 parg->type->is_चिन्हित,
					 FILTER_OTHER);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम trace_probe_event_मुक्त(काष्ठा trace_probe_event *tpe)
अणु
	kमुक्त(tpe->class.प्रणाली);
	kमुक्त(tpe->call.name);
	kमुक्त(tpe->call.prपूर्णांक_fmt);
	kमुक्त(tpe);
पूर्ण

पूर्णांक trace_probe_append(काष्ठा trace_probe *tp, काष्ठा trace_probe *to)
अणु
	अगर (trace_probe_has_sibling(tp))
		वापस -EBUSY;

	list_del_init(&tp->list);
	trace_probe_event_मुक्त(tp->event);

	tp->event = to->event;
	list_add_tail(&tp->list, trace_probe_probe_list(to));

	वापस 0;
पूर्ण

व्योम trace_probe_unlink(काष्ठा trace_probe *tp)
अणु
	list_del_init(&tp->list);
	अगर (list_empty(trace_probe_probe_list(tp)))
		trace_probe_event_मुक्त(tp->event);
	tp->event = शून्य;
पूर्ण

व्योम trace_probe_cleanup(काष्ठा trace_probe *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tp->nr_args; i++)
		traceprobe_मुक्त_probe_arg(&tp->args[i]);

	अगर (tp->event)
		trace_probe_unlink(tp);
पूर्ण

पूर्णांक trace_probe_init(काष्ठा trace_probe *tp, स्थिर अक्षर *event,
		     स्थिर अक्षर *group, bool alloc_filter)
अणु
	काष्ठा trace_event_call *call;
	माप_प्रकार size = माप(काष्ठा trace_probe_event);
	पूर्णांक ret = 0;

	अगर (!event || !group)
		वापस -EINVAL;

	अगर (alloc_filter)
		size += माप(काष्ठा trace_uprobe_filter);

	tp->event = kzalloc(size, GFP_KERNEL);
	अगर (!tp->event)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&tp->event->files);
	INIT_LIST_HEAD(&tp->event->class.fields);
	INIT_LIST_HEAD(&tp->event->probes);
	INIT_LIST_HEAD(&tp->list);
	list_add(&tp->list, &tp->event->probes);

	call = trace_probe_event_call(tp);
	call->class = &tp->event->class;
	call->name = kstrdup(event, GFP_KERNEL);
	अगर (!call->name) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	tp->event->class.प्रणाली = kstrdup(group, GFP_KERNEL);
	अगर (!tp->event->class.प्रणाली) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	वापस 0;

error:
	trace_probe_cleanup(tp);
	वापस ret;
पूर्ण

पूर्णांक trace_probe_रेजिस्टर_event_call(काष्ठा trace_probe *tp)
अणु
	काष्ठा trace_event_call *call = trace_probe_event_call(tp);
	पूर्णांक ret;

	ret = रेजिस्टर_trace_event(&call->event);
	अगर (!ret)
		वापस -ENODEV;

	ret = trace_add_event_call(call);
	अगर (ret)
		unरेजिस्टर_trace_event(&call->event);

	वापस ret;
पूर्ण

पूर्णांक trace_probe_add_file(काष्ठा trace_probe *tp, काष्ठा trace_event_file *file)
अणु
	काष्ठा event_file_link *link;

	link = kदो_स्मृति(माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	link->file = file;
	INIT_LIST_HEAD(&link->list);
	list_add_tail_rcu(&link->list, &tp->event->files);
	trace_probe_set_flag(tp, TP_FLAG_TRACE);
	वापस 0;
पूर्ण

काष्ठा event_file_link *trace_probe_get_file_link(काष्ठा trace_probe *tp,
						  काष्ठा trace_event_file *file)
अणु
	काष्ठा event_file_link *link;

	trace_probe_क्रम_each_link(link, tp) अणु
		अगर (link->file == file)
			वापस link;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक trace_probe_हटाओ_file(काष्ठा trace_probe *tp,
			    काष्ठा trace_event_file *file)
अणु
	काष्ठा event_file_link *link;

	link = trace_probe_get_file_link(tp, file);
	अगर (!link)
		वापस -ENOENT;

	list_del_rcu(&link->list);
	synchronize_rcu();
	kमुक्त(link);

	अगर (list_empty(&tp->event->files))
		trace_probe_clear_flag(tp, TP_FLAG_TRACE);

	वापस 0;
पूर्ण

/*
 * Return the smallest index of dअगरferent type argument (start from 1).
 * If all argument types and name are same, वापस 0.
 */
पूर्णांक trace_probe_compare_arg_type(काष्ठा trace_probe *a, काष्ठा trace_probe *b)
अणु
	पूर्णांक i;

	/* In हाल of more arguments */
	अगर (a->nr_args < b->nr_args)
		वापस a->nr_args + 1;
	अगर (a->nr_args > b->nr_args)
		वापस b->nr_args + 1;

	क्रम (i = 0; i < a->nr_args; i++) अणु
		अगर ((b->nr_args <= i) ||
		    ((a->args[i].type != b->args[i].type) ||
		     (a->args[i].count != b->args[i].count) ||
		     म_भेद(a->args[i].name, b->args[i].name)))
			वापस i + 1;
	पूर्ण

	वापस 0;
पूर्ण

bool trace_probe_match_command_args(काष्ठा trace_probe *tp,
				    पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर buf[MAX_ARGSTR_LEN + 1];
	पूर्णांक i;

	अगर (tp->nr_args < argc)
		वापस false;

	क्रम (i = 0; i < argc; i++) अणु
		snम_लिखो(buf, माप(buf), "%s=%s",
			 tp->args[i].name, tp->args[i].comm);
		अगर (म_भेद(buf, argv[i]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक trace_probe_create(स्थिर अक्षर *raw_command, पूर्णांक (*createfn)(पूर्णांक, स्थिर अक्षर **))
अणु
	पूर्णांक argc = 0, ret = 0;
	अक्षर **argv;

	argv = argv_split(GFP_KERNEL, raw_command, &argc);
	अगर (!argv)
		वापस -ENOMEM;

	अगर (argc)
		ret = createfn(argc, (स्थिर अक्षर **)argv);

	argv_मुक्त(argv);

	वापस ret;
पूर्ण
