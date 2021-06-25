<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>

#समावेश "event-parse.h"
#समावेश "event-parse-local.h"
#समावेश "event-utils.h"

#घोषणा COMM "COMM"
#घोषणा CPU "CPU"

अटल काष्ठा tep_क्रमmat_field comm = अणु
	.name = "COMM",
पूर्ण;

अटल काष्ठा tep_क्रमmat_field cpu = अणु
	.name = "CPU",
पूर्ण;

काष्ठा event_list अणु
	काष्ठा event_list	*next;
	काष्ठा tep_event	*event;
पूर्ण;

अटल व्योम show_error(अक्षर *error_buf, स्थिर अक्षर *fmt, ...)
अणु
	अचिन्हित दीर्घ दीर्घ index;
	स्थिर अक्षर *input;
	बहु_सूची ap;
	पूर्णांक len;
	पूर्णांक i;

	input = get_input_buf();
	index = get_input_buf_ptr();
	len = input ? म_माप(input) : 0;

	अगर (len) अणु
		म_नकल(error_buf, input);
		error_buf[len] = '\n';
		क्रम (i = 1; i < len && i < index; i++)
			error_buf[len+i] = ' ';
		error_buf[len + i] = '^';
		error_buf[len + i + 1] = '\n';
		len += i+2;
	पूर्ण

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(error_buf + len, TEP_FILTER_ERROR_BUFSZ - len, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल क्रमागत tep_event_type filter_पढ़ो_token(अक्षर **tok)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token = शून्य;

	करो अणु
		मुक्त_token(token);
		type = पढ़ो_token(&token);
	पूर्ण जबतक (type == TEP_EVENT_NEWLINE || type == TEP_EVENT_SPACE);

	/* If token is = or ! check to see अगर the next अक्षर is ~ */
	अगर (token &&
	    (म_भेद(token, "=") == 0 || म_भेद(token, "!") == 0) &&
	    peek_अक्षर() == '~') अणु
		/* append it */
		*tok = दो_स्मृति(3);
		अगर (*tok == शून्य) अणु
			मुक्त_token(token);
			वापस TEP_EVENT_ERROR;
		पूर्ण
		प्र_लिखो(*tok, "%c%c", *token, '~');
		मुक्त_token(token);
		/* Now हटाओ the '~' from the buffer */
		पढ़ो_token(&token);
		मुक्त_token(token);
	पूर्ण अन्यथा
		*tok = token;

	वापस type;
पूर्ण

अटल पूर्णांक filter_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा tep_filter_type *ea = a;
	स्थिर काष्ठा tep_filter_type *eb = b;

	अगर (ea->event_id < eb->event_id)
		वापस -1;

	अगर (ea->event_id > eb->event_id)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा tep_filter_type *
find_filter_type(काष्ठा tep_event_filter *filter, पूर्णांक id)
अणु
	काष्ठा tep_filter_type *filter_type;
	काष्ठा tep_filter_type key;

	key.event_id = id;

	filter_type = द्वा_खोज(&key, filter->event_filters,
			      filter->filters,
			      माप(*filter->event_filters),
			      filter_cmp);

	वापस filter_type;
पूर्ण

अटल काष्ठा tep_filter_type *
add_filter_type(काष्ठा tep_event_filter *filter, पूर्णांक id)
अणु
	काष्ठा tep_filter_type *filter_type;
	पूर्णांक i;

	filter_type = find_filter_type(filter, id);
	अगर (filter_type)
		वापस filter_type;

	filter_type = पुनः_स्मृति(filter->event_filters,
			      माप(*filter->event_filters) *
			      (filter->filters + 1));
	अगर (!filter_type)
		वापस शून्य;

	filter->event_filters = filter_type;

	क्रम (i = 0; i < filter->filters; i++) अणु
		अगर (filter->event_filters[i].event_id > id)
			अवरोध;
	पूर्ण

	अगर (i < filter->filters)
		स_हटाओ(&filter->event_filters[i+1],
			&filter->event_filters[i],
			माप(*filter->event_filters) *
			(filter->filters - i));

	filter_type = &filter->event_filters[i];
	filter_type->event_id = id;
	filter_type->event = tep_find_event(filter->tep, id);
	filter_type->filter = शून्य;

	filter->filters++;

	वापस filter_type;
पूर्ण

/**
 * tep_filter_alloc - create a new event filter
 * @tep: The tep that this filter is associated with
 */
काष्ठा tep_event_filter *tep_filter_alloc(काष्ठा tep_handle *tep)
अणु
	काष्ठा tep_event_filter *filter;

	filter = दो_स्मृति(माप(*filter));
	अगर (filter == शून्य)
		वापस शून्य;

	स_रखो(filter, 0, माप(*filter));
	filter->tep = tep;
	tep_ref(tep);

	वापस filter;
पूर्ण

अटल काष्ठा tep_filter_arg *allocate_arg(व्योम)
अणु
	वापस सुस्मृति(1, माप(काष्ठा tep_filter_arg));
पूर्ण

अटल व्योम मुक्त_arg(काष्ठा tep_filter_arg *arg)
अणु
	अगर (!arg)
		वापस;

	चयन (arg->type) अणु
	हाल TEP_FILTER_ARG_NONE:
	हाल TEP_FILTER_ARG_BOOLEAN:
		अवरोध;

	हाल TEP_FILTER_ARG_NUM:
		मुक्त_arg(arg->num.left);
		मुक्त_arg(arg->num.right);
		अवरोध;

	हाल TEP_FILTER_ARG_EXP:
		मुक्त_arg(arg->exp.left);
		मुक्त_arg(arg->exp.right);
		अवरोध;

	हाल TEP_FILTER_ARG_STR:
		मुक्त(arg->str.val);
		regमुक्त(&arg->str.reg);
		मुक्त(arg->str.buffer);
		अवरोध;

	हाल TEP_FILTER_ARG_VALUE:
		अगर (arg->value.type == TEP_FILTER_STRING ||
		    arg->value.type == TEP_FILTER_CHAR)
			मुक्त(arg->value.str);
		अवरोध;

	हाल TEP_FILTER_ARG_OP:
		मुक्त_arg(arg->op.left);
		मुक्त_arg(arg->op.right);
	शेष:
		अवरोध;
	पूर्ण

	मुक्त(arg);
पूर्ण

अटल पूर्णांक add_event(काष्ठा event_list **events,
		     काष्ठा tep_event *event)
अणु
	काष्ठा event_list *list;

	list = दो_स्मृति(माप(*list));
	अगर (list == शून्य)
		वापस -1;

	list->next = *events;
	*events = list;
	list->event = event;
	वापस 0;
पूर्ण

अटल पूर्णांक event_match(काष्ठा tep_event *event,
		       regex_t *sreg, regex_t *ereg)
अणु
	अगर (sreg) अणु
		वापस !regexec(sreg, event->प्रणाली, 0, शून्य, 0) &&
			!regexec(ereg, event->name, 0, शून्य, 0);
	पूर्ण

	वापस !regexec(ereg, event->प्रणाली, 0, शून्य, 0) ||
		!regexec(ereg, event->name, 0, शून्य, 0);
पूर्ण

अटल क्रमागत tep_त्रुटि_सं
find_event(काष्ठा tep_handle *tep, काष्ठा event_list **events,
	   अक्षर *sys_name, अक्षर *event_name)
अणु
	काष्ठा tep_event *event;
	regex_t ereg;
	regex_t sreg;
	पूर्णांक match = 0;
	पूर्णांक fail = 0;
	अक्षर *reg;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!event_name) अणु
		/* अगर no name is given, then swap sys and name */
		event_name = sys_name;
		sys_name = शून्य;
	पूर्ण

	ret = aप्र_लिखो(&reg, "^%s$", event_name);
	अगर (ret < 0)
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;

	ret = regcomp(&ereg, reg, REG_ICASE|REG_NOSUB);
	मुक्त(reg);

	अगर (ret)
		वापस TEP_ERRNO__INVALID_EVENT_NAME;

	अगर (sys_name) अणु
		ret = aप्र_लिखो(&reg, "^%s$", sys_name);
		अगर (ret < 0) अणु
			regमुक्त(&ereg);
			वापस TEP_ERRNO__MEM_ALLOC_FAILED;
		पूर्ण

		ret = regcomp(&sreg, reg, REG_ICASE|REG_NOSUB);
		मुक्त(reg);
		अगर (ret) अणु
			regमुक्त(&ereg);
			वापस TEP_ERRNO__INVALID_EVENT_NAME;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < tep->nr_events; i++) अणु
		event = tep->events[i];
		अगर (event_match(event, sys_name ? &sreg : शून्य, &ereg)) अणु
			match = 1;
			अगर (add_event(events, event) < 0) अणु
				fail = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	regमुक्त(&ereg);
	अगर (sys_name)
		regमुक्त(&sreg);

	अगर (!match)
		वापस TEP_ERRNO__EVENT_NOT_FOUND;
	अगर (fail)
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_events(काष्ठा event_list *events)
अणु
	काष्ठा event_list *event;

	जबतक (events) अणु
		event = events;
		events = events->next;
		मुक्त(event);
	पूर्ण
पूर्ण

अटल क्रमागत tep_त्रुटि_सं
create_arg_item(काष्ठा tep_event *event, स्थिर अक्षर *token,
		क्रमागत tep_event_type type, काष्ठा tep_filter_arg **parg, अक्षर *error_str)
अणु
	काष्ठा tep_क्रमmat_field *field;
	काष्ठा tep_filter_arg *arg;

	arg = allocate_arg();
	अगर (arg == शून्य) अणु
		show_error(error_str, "failed to allocate filter arg");
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;
	पूर्ण

	चयन (type) अणु

	हाल TEP_EVENT_SQUOTE:
	हाल TEP_EVENT_DQUOTE:
		arg->type = TEP_FILTER_ARG_VALUE;
		arg->value.type =
			type == TEP_EVENT_DQUOTE ? TEP_FILTER_STRING : TEP_FILTER_CHAR;
		arg->value.str = strdup(token);
		अगर (!arg->value.str) अणु
			मुक्त_arg(arg);
			show_error(error_str, "failed to allocate string filter arg");
			वापस TEP_ERRNO__MEM_ALLOC_FAILED;
		पूर्ण
		अवरोध;
	हाल TEP_EVENT_ITEM:
		/* अगर it is a number, then convert it */
		अगर (है_अंक(token[0])) अणु
			arg->type = TEP_FILTER_ARG_VALUE;
			arg->value.type = TEP_FILTER_NUMBER;
			arg->value.val = म_से_अदीर्घl(token, शून्य, 0);
			अवरोध;
		पूर्ण
		/* Consider this a field */
		field = tep_find_any_field(event, token);
		अगर (!field) अणु
			/* If token is 'COMM' or 'CPU' then it is special */
			अगर (म_भेद(token, COMM) == 0) अणु
				field = &comm;
			पूर्ण अन्यथा अगर (म_भेद(token, CPU) == 0) अणु
				field = &cpu;
			पूर्ण अन्यथा अणु
				/* not a field, Make it false */
				arg->type = TEP_FILTER_ARG_BOOLEAN;
				arg->boolean.value = TEP_FILTER_FALSE;
				अवरोध;
			पूर्ण
		पूर्ण
		arg->type = TEP_FILTER_ARG_FIELD;
		arg->field.field = field;
		अवरोध;
	शेष:
		मुक्त_arg(arg);
		show_error(error_str, "expected a value but found %s", token);
		वापस TEP_ERRNO__UNEXPECTED_TYPE;
	पूर्ण
	*parg = arg;
	वापस 0;
पूर्ण

अटल काष्ठा tep_filter_arg *
create_arg_op(क्रमागत tep_filter_op_type btype)
अणु
	काष्ठा tep_filter_arg *arg;

	arg = allocate_arg();
	अगर (!arg)
		वापस शून्य;

	arg->type = TEP_FILTER_ARG_OP;
	arg->op.type = btype;

	वापस arg;
पूर्ण

अटल काष्ठा tep_filter_arg *
create_arg_exp(क्रमागत tep_filter_exp_type etype)
अणु
	काष्ठा tep_filter_arg *arg;

	arg = allocate_arg();
	अगर (!arg)
		वापस शून्य;

	arg->type = TEP_FILTER_ARG_EXP;
	arg->exp.type = etype;

	वापस arg;
पूर्ण

अटल काष्ठा tep_filter_arg *
create_arg_cmp(क्रमागत tep_filter_cmp_type ctype)
अणु
	काष्ठा tep_filter_arg *arg;

	arg = allocate_arg();
	अगर (!arg)
		वापस शून्य;

	/* Use NUM and change अगर necessary */
	arg->type = TEP_FILTER_ARG_NUM;
	arg->num.type = ctype;

	वापस arg;
पूर्ण

अटल क्रमागत tep_त्रुटि_सं
add_right(काष्ठा tep_filter_arg *op, काष्ठा tep_filter_arg *arg, अक्षर *error_str)
अणु
	काष्ठा tep_filter_arg *left;
	अक्षर *str;
	पूर्णांक op_type;
	पूर्णांक ret;

	चयन (op->type) अणु
	हाल TEP_FILTER_ARG_EXP:
		अगर (op->exp.right)
			जाओ out_fail;
		op->exp.right = arg;
		अवरोध;

	हाल TEP_FILTER_ARG_OP:
		अगर (op->op.right)
			जाओ out_fail;
		op->op.right = arg;
		अवरोध;

	हाल TEP_FILTER_ARG_NUM:
		अगर (op->op.right)
			जाओ out_fail;
		/*
		 * The arg must be num, str, or field
		 */
		चयन (arg->type) अणु
		हाल TEP_FILTER_ARG_VALUE:
		हाल TEP_FILTER_ARG_FIELD:
			अवरोध;
		शेष:
			show_error(error_str, "Illegal rvalue");
			वापस TEP_ERRNO__ILLEGAL_RVALUE;
		पूर्ण

		/*
		 * Depending on the type, we may need to
		 * convert this to a string or regex.
		 */
		चयन (arg->value.type) अणु
		हाल TEP_FILTER_CHAR:
			/*
			 * A अक्षर should be converted to number अगर
			 * the string is 1 byte, and the compare
			 * is not a REGEX.
			 */
			अगर (म_माप(arg->value.str) == 1 &&
			    op->num.type != TEP_FILTER_CMP_REGEX &&
			    op->num.type != TEP_FILTER_CMP_NOT_REGEX) अणु
				arg->value.type = TEP_FILTER_NUMBER;
				जाओ करो_पूर्णांक;
			पूर्ण
			/* fall through */
		हाल TEP_FILTER_STRING:

			/* convert op to a string arg */
			op_type = op->num.type;
			left = op->num.left;
			str = arg->value.str;

			/* reset the op क्रम the new field */
			स_रखो(op, 0, माप(*op));

			/*
			 * If left arg was a field not found then
			 * शून्य the entire op.
			 */
			अगर (left->type == TEP_FILTER_ARG_BOOLEAN) अणु
				मुक्त_arg(left);
				मुक्त_arg(arg);
				op->type = TEP_FILTER_ARG_BOOLEAN;
				op->boolean.value = TEP_FILTER_FALSE;
				अवरोध;
			पूर्ण

			/* Left arg must be a field */
			अगर (left->type != TEP_FILTER_ARG_FIELD) अणु
				show_error(error_str,
					   "Illegal lvalue for string comparison");
				वापस TEP_ERRNO__ILLEGAL_LVALUE;
			पूर्ण

			/* Make sure this is a valid string compare */
			चयन (op_type) अणु
			हाल TEP_FILTER_CMP_EQ:
				op_type = TEP_FILTER_CMP_MATCH;
				अवरोध;
			हाल TEP_FILTER_CMP_NE:
				op_type = TEP_FILTER_CMP_NOT_MATCH;
				अवरोध;

			हाल TEP_FILTER_CMP_REGEX:
			हाल TEP_FILTER_CMP_NOT_REGEX:
				ret = regcomp(&op->str.reg, str, REG_ICASE|REG_NOSUB);
				अगर (ret) अणु
					show_error(error_str,
						   "RegEx '%s' did not compute",
						   str);
					वापस TEP_ERRNO__INVALID_REGEX;
				पूर्ण
				अवरोध;
			शेष:
				show_error(error_str,
					   "Illegal comparison for string");
				वापस TEP_ERRNO__ILLEGAL_STRING_CMP;
			पूर्ण

			op->type = TEP_FILTER_ARG_STR;
			op->str.type = op_type;
			op->str.field = left->field.field;
			op->str.val = strdup(str);
			अगर (!op->str.val) अणु
				show_error(error_str, "Failed to allocate string filter");
				वापस TEP_ERRNO__MEM_ALLOC_FAILED;
			पूर्ण
			/*
			 * Need a buffer to copy data क्रम tests
			 */
			op->str.buffer = दो_स्मृति(op->str.field->size + 1);
			अगर (!op->str.buffer) अणु
				show_error(error_str, "Failed to allocate string filter");
				वापस TEP_ERRNO__MEM_ALLOC_FAILED;
			पूर्ण
			/* Null terminate this buffer */
			op->str.buffer[op->str.field->size] = 0;

			/* We no दीर्घer have left or right args */
			मुक्त_arg(arg);
			मुक्त_arg(left);

			अवरोध;

		हाल TEP_FILTER_NUMBER:

 करो_पूर्णांक:
			चयन (op->num.type) अणु
			हाल TEP_FILTER_CMP_REGEX:
			हाल TEP_FILTER_CMP_NOT_REGEX:
				show_error(error_str,
					   "Op not allowed with integers");
				वापस TEP_ERRNO__ILLEGAL_INTEGER_CMP;

			शेष:
				अवरोध;
			पूर्ण

			/* numeric compare */
			op->num.right = arg;
			अवरोध;
		शेष:
			जाओ out_fail;
		पूर्ण
		अवरोध;
	शेष:
		जाओ out_fail;
	पूर्ण

	वापस 0;

 out_fail:
	show_error(error_str, "Syntax error");
	वापस TEP_ERRNO__SYNTAX_ERROR;
पूर्ण

अटल काष्ठा tep_filter_arg *
rotate_op_right(काष्ठा tep_filter_arg *a, काष्ठा tep_filter_arg *b)
अणु
	काष्ठा tep_filter_arg *arg;

	arg = a->op.right;
	a->op.right = b;
	वापस arg;
पूर्ण

अटल क्रमागत tep_त्रुटि_सं add_left(काष्ठा tep_filter_arg *op, काष्ठा tep_filter_arg *arg)
अणु
	चयन (op->type) अणु
	हाल TEP_FILTER_ARG_EXP:
		अगर (arg->type == TEP_FILTER_ARG_OP)
			arg = rotate_op_right(arg, op);
		op->exp.left = arg;
		अवरोध;

	हाल TEP_FILTER_ARG_OP:
		op->op.left = arg;
		अवरोध;
	हाल TEP_FILTER_ARG_NUM:
		अगर (arg->type == TEP_FILTER_ARG_OP)
			arg = rotate_op_right(arg, op);

		/* left arg of compares must be a field */
		अगर (arg->type != TEP_FILTER_ARG_FIELD &&
		    arg->type != TEP_FILTER_ARG_BOOLEAN)
			वापस TEP_ERRNO__INVALID_ARG_TYPE;
		op->num.left = arg;
		अवरोध;
	शेष:
		वापस TEP_ERRNO__INVALID_ARG_TYPE;
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत op_type अणु
	OP_NONE,
	OP_BOOL,
	OP_NOT,
	OP_EXP,
	OP_CMP,
पूर्ण;

अटल क्रमागत op_type process_op(स्थिर अक्षर *token,
			       क्रमागत tep_filter_op_type *btype,
			       क्रमागत tep_filter_cmp_type *ctype,
			       क्रमागत tep_filter_exp_type *etype)
अणु
	*btype = TEP_FILTER_OP_NOT;
	*etype = TEP_FILTER_EXP_NONE;
	*ctype = TEP_FILTER_CMP_NONE;

	अगर (म_भेद(token, "&&") == 0)
		*btype = TEP_FILTER_OP_AND;
	अन्यथा अगर (म_भेद(token, "||") == 0)
		*btype = TEP_FILTER_OP_OR;
	अन्यथा अगर (म_भेद(token, "!") == 0)
		वापस OP_NOT;

	अगर (*btype != TEP_FILTER_OP_NOT)
		वापस OP_BOOL;

	/* Check क्रम value expressions */
	अगर (म_भेद(token, "+") == 0) अणु
		*etype = TEP_FILTER_EXP_ADD;
	पूर्ण अन्यथा अगर (म_भेद(token, "-") == 0) अणु
		*etype = TEP_FILTER_EXP_SUB;
	पूर्ण अन्यथा अगर (म_भेद(token, "*") == 0) अणु
		*etype = TEP_FILTER_EXP_MUL;
	पूर्ण अन्यथा अगर (म_भेद(token, "/") == 0) अणु
		*etype = TEP_FILTER_EXP_DIV;
	पूर्ण अन्यथा अगर (म_भेद(token, "%") == 0) अणु
		*etype = TEP_FILTER_EXP_MOD;
	पूर्ण अन्यथा अगर (म_भेद(token, ">>") == 0) अणु
		*etype = TEP_FILTER_EXP_RSHIFT;
	पूर्ण अन्यथा अगर (म_भेद(token, "<<") == 0) अणु
		*etype = TEP_FILTER_EXP_LSHIFT;
	पूर्ण अन्यथा अगर (म_भेद(token, "&") == 0) अणु
		*etype = TEP_FILTER_EXP_AND;
	पूर्ण अन्यथा अगर (म_भेद(token, "|") == 0) अणु
		*etype = TEP_FILTER_EXP_OR;
	पूर्ण अन्यथा अगर (म_भेद(token, "^") == 0) अणु
		*etype = TEP_FILTER_EXP_XOR;
	पूर्ण अन्यथा अगर (म_भेद(token, "~") == 0)
		*etype = TEP_FILTER_EXP_NOT;

	अगर (*etype != TEP_FILTER_EXP_NONE)
		वापस OP_EXP;

	/* Check क्रम compares */
	अगर (म_भेद(token, "==") == 0)
		*ctype = TEP_FILTER_CMP_EQ;
	अन्यथा अगर (म_भेद(token, "!=") == 0)
		*ctype = TEP_FILTER_CMP_NE;
	अन्यथा अगर (म_भेद(token, "<") == 0)
		*ctype = TEP_FILTER_CMP_LT;
	अन्यथा अगर (म_भेद(token, ">") == 0)
		*ctype = TEP_FILTER_CMP_GT;
	अन्यथा अगर (म_भेद(token, "<=") == 0)
		*ctype = TEP_FILTER_CMP_LE;
	अन्यथा अगर (म_भेद(token, ">=") == 0)
		*ctype = TEP_FILTER_CMP_GE;
	अन्यथा अगर (म_भेद(token, "=~") == 0)
		*ctype = TEP_FILTER_CMP_REGEX;
	अन्यथा अगर (म_भेद(token, "!~") == 0)
		*ctype = TEP_FILTER_CMP_NOT_REGEX;
	अन्यथा
		वापस OP_NONE;

	वापस OP_CMP;
पूर्ण

अटल पूर्णांक check_op_करोne(काष्ठा tep_filter_arg *arg)
अणु
	चयन (arg->type) अणु
	हाल TEP_FILTER_ARG_EXP:
		वापस arg->exp.right != शून्य;

	हाल TEP_FILTER_ARG_OP:
		वापस arg->op.right != शून्य;

	हाल TEP_FILTER_ARG_NUM:
		वापस arg->num.right != शून्य;

	हाल TEP_FILTER_ARG_STR:
		/* A string conversion is always करोne */
		वापस 1;

	हाल TEP_FILTER_ARG_BOOLEAN:
		/* field not found, is ok */
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

क्रमागत filter_vals अणु
	FILTER_VAL_NORM,
	FILTER_VAL_FALSE,
	FILTER_VAL_TRUE,
पूर्ण;

अटल क्रमागत tep_त्रुटि_सं
reparent_op_arg(काष्ठा tep_filter_arg *parent, काष्ठा tep_filter_arg *old_child,
		काष्ठा tep_filter_arg *arg, अक्षर *error_str)
अणु
	काष्ठा tep_filter_arg *other_child;
	काष्ठा tep_filter_arg **ptr;

	अगर (parent->type != TEP_FILTER_ARG_OP &&
	    arg->type != TEP_FILTER_ARG_OP) अणु
		show_error(error_str, "can not reparent other than OP");
		वापस TEP_ERRNO__REPARENT_NOT_OP;
	पूर्ण

	/* Get the sibling */
	अगर (old_child->op.right == arg) अणु
		ptr = &old_child->op.right;
		other_child = old_child->op.left;
	पूर्ण अन्यथा अगर (old_child->op.left == arg) अणु
		ptr = &old_child->op.left;
		other_child = old_child->op.right;
	पूर्ण अन्यथा अणु
		show_error(error_str, "Error in reparent op, find other child");
		वापस TEP_ERRNO__REPARENT_FAILED;
	पूर्ण

	/* Detach arg from old_child */
	*ptr = शून्य;

	/* Check क्रम root */
	अगर (parent == old_child) अणु
		मुक्त_arg(other_child);
		*parent = *arg;
		/* Free arg without recussion */
		मुक्त(arg);
		वापस 0;
	पूर्ण

	अगर (parent->op.right == old_child)
		ptr = &parent->op.right;
	अन्यथा अगर (parent->op.left == old_child)
		ptr = &parent->op.left;
	अन्यथा अणु
		show_error(error_str, "Error in reparent op");
		वापस TEP_ERRNO__REPARENT_FAILED;
	पूर्ण

	*ptr = arg;

	मुक्त_arg(old_child);
	वापस 0;
पूर्ण

/* Returns either filter_vals (success) or tep_त्रुटि_सं (failfure) */
अटल पूर्णांक test_arg(काष्ठा tep_filter_arg *parent, काष्ठा tep_filter_arg *arg,
		    अक्षर *error_str)
अणु
	पूर्णांक lval, rval;

	चयन (arg->type) अणु

		/* bad हाल */
	हाल TEP_FILTER_ARG_BOOLEAN:
		वापस FILTER_VAL_FALSE + arg->boolean.value;

		/* good हालs: */
	हाल TEP_FILTER_ARG_STR:
	हाल TEP_FILTER_ARG_VALUE:
	हाल TEP_FILTER_ARG_FIELD:
		वापस FILTER_VAL_NORM;

	हाल TEP_FILTER_ARG_EXP:
		lval = test_arg(arg, arg->exp.left, error_str);
		अगर (lval != FILTER_VAL_NORM)
			वापस lval;
		rval = test_arg(arg, arg->exp.right, error_str);
		अगर (rval != FILTER_VAL_NORM)
			वापस rval;
		वापस FILTER_VAL_NORM;

	हाल TEP_FILTER_ARG_NUM:
		lval = test_arg(arg, arg->num.left, error_str);
		अगर (lval != FILTER_VAL_NORM)
			वापस lval;
		rval = test_arg(arg, arg->num.right, error_str);
		अगर (rval != FILTER_VAL_NORM)
			वापस rval;
		वापस FILTER_VAL_NORM;

	हाल TEP_FILTER_ARG_OP:
		अगर (arg->op.type != TEP_FILTER_OP_NOT) अणु
			lval = test_arg(arg, arg->op.left, error_str);
			चयन (lval) अणु
			हाल FILTER_VAL_NORM:
				अवरोध;
			हाल FILTER_VAL_TRUE:
				अगर (arg->op.type == TEP_FILTER_OP_OR)
					वापस FILTER_VAL_TRUE;
				rval = test_arg(arg, arg->op.right, error_str);
				अगर (rval != FILTER_VAL_NORM)
					वापस rval;

				वापस reparent_op_arg(parent, arg, arg->op.right,
						       error_str);

			हाल FILTER_VAL_FALSE:
				अगर (arg->op.type == TEP_FILTER_OP_AND)
					वापस FILTER_VAL_FALSE;
				rval = test_arg(arg, arg->op.right, error_str);
				अगर (rval != FILTER_VAL_NORM)
					वापस rval;

				वापस reparent_op_arg(parent, arg, arg->op.right,
						       error_str);

			शेष:
				वापस lval;
			पूर्ण
		पूर्ण

		rval = test_arg(arg, arg->op.right, error_str);
		चयन (rval) अणु
		हाल FILTER_VAL_NORM:
		शेष:
			अवरोध;

		हाल FILTER_VAL_TRUE:
			अगर (arg->op.type == TEP_FILTER_OP_OR)
				वापस FILTER_VAL_TRUE;
			अगर (arg->op.type == TEP_FILTER_OP_NOT)
				वापस FILTER_VAL_FALSE;

			वापस reparent_op_arg(parent, arg, arg->op.left,
					       error_str);

		हाल FILTER_VAL_FALSE:
			अगर (arg->op.type == TEP_FILTER_OP_AND)
				वापस FILTER_VAL_FALSE;
			अगर (arg->op.type == TEP_FILTER_OP_NOT)
				वापस FILTER_VAL_TRUE;

			वापस reparent_op_arg(parent, arg, arg->op.left,
					       error_str);
		पूर्ण

		वापस rval;
	शेष:
		show_error(error_str, "bad arg in filter tree");
		वापस TEP_ERRNO__BAD_FILTER_ARG;
	पूर्ण
	वापस FILTER_VAL_NORM;
पूर्ण

/* Remove any unknown event fields */
अटल पूर्णांक collapse_tree(काष्ठा tep_filter_arg *arg,
			 काष्ठा tep_filter_arg **arg_collapsed, अक्षर *error_str)
अणु
	पूर्णांक ret;

	ret = test_arg(arg, arg, error_str);
	चयन (ret) अणु
	हाल FILTER_VAL_NORM:
		अवरोध;

	हाल FILTER_VAL_TRUE:
	हाल FILTER_VAL_FALSE:
		मुक्त_arg(arg);
		arg = allocate_arg();
		अगर (arg) अणु
			arg->type = TEP_FILTER_ARG_BOOLEAN;
			arg->boolean.value = ret == FILTER_VAL_TRUE;
		पूर्ण अन्यथा अणु
			show_error(error_str, "Failed to allocate filter arg");
			ret = TEP_ERRNO__MEM_ALLOC_FAILED;
		पूर्ण
		अवरोध;

	शेष:
		/* test_arg() alपढ़ोy set the error_str */
		मुक्त_arg(arg);
		arg = शून्य;
		अवरोध;
	पूर्ण

	*arg_collapsed = arg;
	वापस ret;
पूर्ण

अटल क्रमागत tep_त्रुटि_सं
process_filter(काष्ठा tep_event *event, काष्ठा tep_filter_arg **parg,
	       अक्षर *error_str, पूर्णांक not)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token = शून्य;
	काष्ठा tep_filter_arg *current_op = शून्य;
	काष्ठा tep_filter_arg *current_exp = शून्य;
	काष्ठा tep_filter_arg *left_item = शून्य;
	काष्ठा tep_filter_arg *arg = शून्य;
	क्रमागत op_type op_type;
	क्रमागत tep_filter_op_type btype;
	क्रमागत tep_filter_exp_type etype;
	क्रमागत tep_filter_cmp_type ctype;
	क्रमागत tep_त्रुटि_सं ret;

	*parg = शून्य;

	करो अणु
		मुक्त(token);
		type = filter_पढ़ो_token(&token);
		चयन (type) अणु
		हाल TEP_EVENT_SQUOTE:
		हाल TEP_EVENT_DQUOTE:
		हाल TEP_EVENT_ITEM:
			ret = create_arg_item(event, token, type, &arg, error_str);
			अगर (ret < 0)
				जाओ fail;
			अगर (!left_item)
				left_item = arg;
			अन्यथा अगर (current_exp) अणु
				ret = add_right(current_exp, arg, error_str);
				अगर (ret < 0)
					जाओ fail;
				left_item = शून्य;
				/* Not's only one one expression */
				अगर (not) अणु
					arg = शून्य;
					अगर (current_op)
						जाओ fail_syntax;
					मुक्त(token);
					*parg = current_exp;
					वापस 0;
				पूर्ण
			पूर्ण अन्यथा
				जाओ fail_syntax;
			arg = शून्य;
			अवरोध;

		हाल TEP_EVENT_DELIM:
			अगर (*token == ',') अणु
				show_error(error_str, "Illegal token ','");
				ret = TEP_ERRNO__ILLEGAL_TOKEN;
				जाओ fail;
			पूर्ण

			अगर (*token == '(') अणु
				अगर (left_item) अणु
					show_error(error_str,
						   "Open paren can not come after item");
					ret = TEP_ERRNO__INVALID_PAREN;
					जाओ fail;
				पूर्ण
				अगर (current_exp) अणु
					show_error(error_str,
						   "Open paren can not come after expression");
					ret = TEP_ERRNO__INVALID_PAREN;
					जाओ fail;
				पूर्ण

				ret = process_filter(event, &arg, error_str, 0);
				अगर (ret != TEP_ERRNO__UNBALANCED_PAREN) अणु
					अगर (ret == 0) अणु
						show_error(error_str,
							   "Unbalanced number of '('");
						ret = TEP_ERRNO__UNBALANCED_PAREN;
					पूर्ण
					जाओ fail;
				पूर्ण
				ret = 0;

				/* A not wants just one expression */
				अगर (not) अणु
					अगर (current_op)
						जाओ fail_syntax;
					*parg = arg;
					वापस 0;
				पूर्ण

				अगर (current_op)
					ret = add_right(current_op, arg, error_str);
				अन्यथा
					current_exp = arg;

				अगर (ret < 0)
					जाओ fail;

			पूर्ण अन्यथा अणु /* ')' */
				अगर (!current_op && !current_exp)
					जाओ fail_syntax;

				/* Make sure everything is finished at this level */
				अगर (current_exp && !check_op_करोne(current_exp))
					जाओ fail_syntax;
				अगर (current_op && !check_op_करोne(current_op))
					जाओ fail_syntax;

				अगर (current_op)
					*parg = current_op;
				अन्यथा
					*parg = current_exp;
				मुक्त(token);
				वापस TEP_ERRNO__UNBALANCED_PAREN;
			पूर्ण
			अवरोध;

		हाल TEP_EVENT_OP:
			op_type = process_op(token, &btype, &ctype, &etype);

			/* All expect a left arg except क्रम NOT */
			चयन (op_type) अणु
			हाल OP_BOOL:
				/* Logic ops need a left expression */
				अगर (!current_exp && !current_op)
					जाओ fail_syntax;
				/* fall through */
			हाल OP_NOT:
				/* logic only processes ops and exp */
				अगर (left_item)
					जाओ fail_syntax;
				अवरोध;
			हाल OP_EXP:
			हाल OP_CMP:
				अगर (!left_item)
					जाओ fail_syntax;
				अवरोध;
			हाल OP_NONE:
				show_error(error_str,
					   "Unknown op token %s", token);
				ret = TEP_ERRNO__UNKNOWN_TOKEN;
				जाओ fail;
			पूर्ण

			ret = 0;
			चयन (op_type) अणु
			हाल OP_BOOL:
				arg = create_arg_op(btype);
				अगर (arg == शून्य)
					जाओ fail_alloc;
				अगर (current_op)
					ret = add_left(arg, current_op);
				अन्यथा
					ret = add_left(arg, current_exp);
				current_op = arg;
				current_exp = शून्य;
				अवरोध;

			हाल OP_NOT:
				arg = create_arg_op(btype);
				अगर (arg == शून्य)
					जाओ fail_alloc;
				अगर (current_op)
					ret = add_right(current_op, arg, error_str);
				अगर (ret < 0)
					जाओ fail;
				current_exp = arg;
				ret = process_filter(event, &arg, error_str, 1);
				अगर (ret < 0)
					जाओ fail;
				ret = add_right(current_exp, arg, error_str);
				अगर (ret < 0)
					जाओ fail;
				अवरोध;

			हाल OP_EXP:
			हाल OP_CMP:
				अगर (op_type == OP_EXP)
					arg = create_arg_exp(etype);
				अन्यथा
					arg = create_arg_cmp(ctype);
				अगर (arg == शून्य)
					जाओ fail_alloc;

				अगर (current_op)
					ret = add_right(current_op, arg, error_str);
				अगर (ret < 0)
					जाओ fail;
				ret = add_left(arg, left_item);
				अगर (ret < 0) अणु
					arg = शून्य;
					जाओ fail_syntax;
				पूर्ण
				current_exp = arg;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			arg = शून्य;
			अगर (ret < 0)
				जाओ fail_syntax;
			अवरोध;
		हाल TEP_EVENT_NONE:
			अवरोध;
		हाल TEP_EVENT_ERROR:
			जाओ fail_alloc;
		शेष:
			जाओ fail_syntax;
		पूर्ण
	पूर्ण जबतक (type != TEP_EVENT_NONE);

	अगर (!current_op && !current_exp)
		जाओ fail_syntax;

	अगर (!current_op)
		current_op = current_exp;

	ret = collapse_tree(current_op, parg, error_str);
	/* collapse_tree() may मुक्त current_op, and updates parg accordingly */
	current_op = शून्य;
	अगर (ret < 0)
		जाओ fail;

	मुक्त(token);
	वापस 0;

 fail_alloc:
	show_error(error_str, "failed to allocate filter arg");
	ret = TEP_ERRNO__MEM_ALLOC_FAILED;
	जाओ fail;
 fail_syntax:
	show_error(error_str, "Syntax error");
	ret = TEP_ERRNO__SYNTAX_ERROR;
 fail:
	मुक्त_arg(current_op);
	मुक्त_arg(current_exp);
	मुक्त_arg(arg);
	मुक्त(token);
	वापस ret;
पूर्ण

अटल क्रमागत tep_त्रुटि_सं
process_event(काष्ठा tep_event *event, स्थिर अक्षर *filter_str,
	      काष्ठा tep_filter_arg **parg, अक्षर *error_str)
अणु
	पूर्णांक ret;

	init_input_buf(filter_str, म_माप(filter_str));

	ret = process_filter(event, parg, error_str, 0);
	अगर (ret < 0)
		वापस ret;

	/* If parg is शून्य, then make it पूर्णांकo FALSE */
	अगर (!*parg) अणु
		*parg = allocate_arg();
		अगर (*parg == शून्य)
			वापस TEP_ERRNO__MEM_ALLOC_FAILED;

		(*parg)->type = TEP_FILTER_ARG_BOOLEAN;
		(*parg)->boolean.value = TEP_FILTER_FALSE;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत tep_त्रुटि_सं
filter_event(काष्ठा tep_event_filter *filter, काष्ठा tep_event *event,
	     स्थिर अक्षर *filter_str, अक्षर *error_str)
अणु
	काष्ठा tep_filter_type *filter_type;
	काष्ठा tep_filter_arg *arg;
	क्रमागत tep_त्रुटि_सं ret;

	अगर (filter_str) अणु
		ret = process_event(event, filter_str, &arg, error_str);
		अगर (ret < 0)
			वापस ret;

	पूर्ण अन्यथा अणु
		/* just add a TRUE arg */
		arg = allocate_arg();
		अगर (arg == शून्य)
			वापस TEP_ERRNO__MEM_ALLOC_FAILED;

		arg->type = TEP_FILTER_ARG_BOOLEAN;
		arg->boolean.value = TEP_FILTER_TRUE;
	पूर्ण

	filter_type = add_filter_type(filter, event->id);
	अगर (filter_type == शून्य) अणु
		मुक्त_arg(arg);
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;
	पूर्ण

	अगर (filter_type->filter)
		मुक्त_arg(filter_type->filter);
	filter_type->filter = arg;

	वापस 0;
पूर्ण

अटल व्योम filter_init_error_buf(काष्ठा tep_event_filter *filter)
अणु
	/* clear buffer to reset show error */
	init_input_buf("", 0);
	filter->error_buffer[0] = '\0';
पूर्ण

/**
 * tep_filter_add_filter_str - add a new filter
 * @filter: the event filter to add to
 * @filter_str: the filter string that contains the filter
 *
 * Returns 0 अगर the filter was successfully added or a
 * negative error code.  Use tep_filter_म_त्रुटि() to see
 * actual error message in हाल of error.
 */
क्रमागत tep_त्रुटि_सं tep_filter_add_filter_str(काष्ठा tep_event_filter *filter,
					 स्थिर अक्षर *filter_str)
अणु
	काष्ठा tep_handle *tep = filter->tep;
	काष्ठा event_list *event;
	काष्ठा event_list *events = शून्य;
	स्थिर अक्षर *filter_start;
	स्थिर अक्षर *next_event;
	अक्षर *this_event;
	अक्षर *event_name = शून्य;
	अक्षर *sys_name = शून्य;
	अक्षर *sp;
	क्रमागत tep_त्रुटि_सं rtn = 0; /* TEP_ERRNO__SUCCESS */
	पूर्णांक len;
	पूर्णांक ret;

	filter_init_error_buf(filter);

	filter_start = म_अक्षर(filter_str, ':');
	अगर (filter_start)
		len = filter_start - filter_str;
	अन्यथा
		len = म_माप(filter_str);

	करो अणु
		next_event = म_अक्षर(filter_str, ',');
		अगर (next_event &&
		    (!filter_start || next_event < filter_start))
			len = next_event - filter_str;
		अन्यथा अगर (filter_start)
			len = filter_start - filter_str;
		अन्यथा
			len = म_माप(filter_str);

		this_event = दो_स्मृति(len + 1);
		अगर (this_event == शून्य) अणु
			/* This can only happen when events is शून्य, but still */
			मुक्त_events(events);
			वापस TEP_ERRNO__MEM_ALLOC_FAILED;
		पूर्ण
		स_नकल(this_event, filter_str, len);
		this_event[len] = 0;

		अगर (next_event)
			next_event++;

		filter_str = next_event;

		sys_name = म_मोहर_r(this_event, "/", &sp);
		event_name = म_मोहर_r(शून्य, "/", &sp);

		अगर (!sys_name) अणु
			/* This can only happen when events is शून्य, but still */
			मुक्त_events(events);
			मुक्त(this_event);
			वापस TEP_ERRNO__FILTER_NOT_FOUND;
		पूर्ण

		/* Find this event */
		ret = find_event(tep, &events, strim(sys_name), strim(event_name));
		अगर (ret < 0) अणु
			मुक्त_events(events);
			मुक्त(this_event);
			वापस ret;
		पूर्ण
		मुक्त(this_event);
	पूर्ण जबतक (filter_str);

	/* Skip the ':' */
	अगर (filter_start)
		filter_start++;

	/* filter starts here */
	क्रम (event = events; event; event = event->next) अणु
		ret = filter_event(filter, event->event, filter_start,
				   filter->error_buffer);
		/* Failures are वापसed अगर a parse error happened */
		अगर (ret < 0)
			rtn = ret;

		अगर (ret >= 0 && tep->test_filters) अणु
			अक्षर *test;
			test = tep_filter_make_string(filter, event->event->id);
			अगर (test) अणु
				म_लिखो(" '%s: %s'\n", event->event->name, test);
				मुक्त(test);
			पूर्ण
		पूर्ण
	पूर्ण

	मुक्त_events(events);

	वापस rtn;
पूर्ण

अटल व्योम मुक्त_filter_type(काष्ठा tep_filter_type *filter_type)
अणु
	मुक्त_arg(filter_type->filter);
पूर्ण

/**
 * tep_filter_म_त्रुटि - fill error message in a buffer
 * @filter: the event filter contains error
 * @err: the error code
 * @buf: the buffer to be filled in
 * @buflen: the size of the buffer
 *
 * Returns 0 अगर message was filled successfully, -1 अगर error
 */
पूर्णांक tep_filter_म_त्रुटि(काष्ठा tep_event_filter *filter, क्रमागत tep_त्रुटि_सं err,
			अक्षर *buf, माप_प्रकार buflen)
अणु
	अगर (err <= __TEP_ERRNO__START || err >= __TEP_ERRNO__END)
		वापस -1;

	अगर (म_माप(filter->error_buffer) > 0) अणु
		माप_प्रकार len = snम_लिखो(buf, buflen, "%s", filter->error_buffer);

		अगर (len > buflen)
			वापस -1;
		वापस 0;
	पूर्ण

	वापस tep_म_त्रुटि(filter->tep, err, buf, buflen);
पूर्ण

/**
 * tep_filter_हटाओ_event - हटाओ a filter क्रम an event
 * @filter: the event filter to हटाओ from
 * @event_id: the event to हटाओ a filter क्रम
 *
 * Removes the filter saved क्रम an event defined by @event_id
 * from the @filter.
 *
 * Returns 1: अगर an event was हटाओd
 *   0: अगर the event was not found
 */
पूर्णांक tep_filter_हटाओ_event(काष्ठा tep_event_filter *filter,
			    पूर्णांक event_id)
अणु
	काष्ठा tep_filter_type *filter_type;
	अचिन्हित दीर्घ len;

	अगर (!filter->filters)
		वापस 0;

	filter_type = find_filter_type(filter, event_id);

	अगर (!filter_type)
		वापस 0;

	मुक्त_filter_type(filter_type);

	/* The filter_type poपूर्णांकs पूर्णांकo the event_filters array */
	len = (अचिन्हित दीर्घ)(filter->event_filters + filter->filters) -
		(अचिन्हित दीर्घ)(filter_type + 1);

	स_हटाओ(filter_type, filter_type + 1, len);
	filter->filters--;

	स_रखो(&filter->event_filters[filter->filters], 0,
	       माप(*filter_type));

	वापस 1;
पूर्ण

/**
 * tep_filter_reset - clear all filters in a filter
 * @filter: the event filter to reset
 *
 * Removes all filters from a filter and resets it.
 */
व्योम tep_filter_reset(काष्ठा tep_event_filter *filter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < filter->filters; i++)
		मुक्त_filter_type(&filter->event_filters[i]);

	मुक्त(filter->event_filters);
	filter->filters = 0;
	filter->event_filters = शून्य;
पूर्ण

व्योम tep_filter_मुक्त(काष्ठा tep_event_filter *filter)
अणु
	tep_unref(filter->tep);

	tep_filter_reset(filter);

	मुक्त(filter);
पूर्ण

अटल अक्षर *arg_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg);

अटल पूर्णांक copy_filter_type(काष्ठा tep_event_filter *filter,
			    काष्ठा tep_event_filter *source,
			    काष्ठा tep_filter_type *filter_type)
अणु
	काष्ठा tep_filter_arg *arg;
	काष्ठा tep_event *event;
	स्थिर अक्षर *sys;
	स्थिर अक्षर *name;
	अक्षर *str;

	/* Can't assume that the tep's are the same */
	sys = filter_type->event->प्रणाली;
	name = filter_type->event->name;
	event = tep_find_event_by_name(filter->tep, sys, name);
	अगर (!event)
		वापस -1;

	str = arg_to_str(source, filter_type->filter);
	अगर (!str)
		वापस -1;

	अगर (म_भेद(str, "TRUE") == 0 || म_भेद(str, "FALSE") == 0) अणु
		/* Add trivial event */
		arg = allocate_arg();
		अगर (arg == शून्य) अणु
			मुक्त(str);
			वापस -1;
		पूर्ण

		arg->type = TEP_FILTER_ARG_BOOLEAN;
		अगर (म_भेद(str, "TRUE") == 0)
			arg->boolean.value = 1;
		अन्यथा
			arg->boolean.value = 0;

		filter_type = add_filter_type(filter, event->id);
		अगर (filter_type == शून्य) अणु
			मुक्त(str);
			मुक्त_arg(arg);
			वापस -1;
		पूर्ण

		filter_type->filter = arg;

		मुक्त(str);
		वापस 0;
	पूर्ण

	filter_event(filter, event, str, शून्य);
	मुक्त(str);

	वापस 0;
पूर्ण

/**
 * tep_filter_copy - copy a filter using another filter
 * @dest - the filter to copy to
 * @source - the filter to copy from
 *
 * Returns 0 on success and -1 अगर not all filters were copied
 */
पूर्णांक tep_filter_copy(काष्ठा tep_event_filter *dest, काष्ठा tep_event_filter *source)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	tep_filter_reset(dest);

	क्रम (i = 0; i < source->filters; i++) अणु
		अगर (copy_filter_type(dest, source, &source->event_filters[i]))
			ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक test_filter(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
		       काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err);

अटल स्थिर अक्षर *
get_comm(काष्ठा tep_event *event, काष्ठा tep_record *record)
अणु
	स्थिर अक्षर *comm;
	पूर्णांक pid;

	pid = tep_data_pid(event->tep, record);
	comm = tep_data_comm_from_pid(event->tep, pid);
	वापस comm;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
get_value(काष्ठा tep_event *event,
	  काष्ठा tep_क्रमmat_field *field, काष्ठा tep_record *record)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	/* Handle our dummy "comm" field */
	अगर (field == &comm) अणु
		स्थिर अक्षर *name;

		name = get_comm(event, record);
		वापस (अचिन्हित दीर्घ)name;
	पूर्ण

	/* Handle our dummy "cpu" field */
	अगर (field == &cpu)
		वापस record->cpu;

	tep_पढ़ो_number_field(field, record->data, &val);

	अगर (!(field->flags & TEP_FIELD_IS_SIGNED))
		वापस val;

	चयन (field->size) अणु
	हाल 1:
		वापस (अक्षर)val;
	हाल 2:
		वापस (लघु)val;
	हाल 4:
		वापस (पूर्णांक)val;
	हाल 8:
		वापस (दीर्घ दीर्घ)val;
	पूर्ण
	वापस val;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
get_arg_value(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
	      काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err);

अटल अचिन्हित दीर्घ दीर्घ
get_exp_value(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
	      काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err)
अणु
	अचिन्हित दीर्घ दीर्घ lval, rval;

	lval = get_arg_value(event, arg->exp.left, record, err);
	rval = get_arg_value(event, arg->exp.right, record, err);

	अगर (*err) अणु
		/*
		 * There was an error, no need to process anymore.
		 */
		वापस 0;
	पूर्ण

	चयन (arg->exp.type) अणु
	हाल TEP_FILTER_EXP_ADD:
		वापस lval + rval;

	हाल TEP_FILTER_EXP_SUB:
		वापस lval - rval;

	हाल TEP_FILTER_EXP_MUL:
		वापस lval * rval;

	हाल TEP_FILTER_EXP_DIV:
		वापस lval / rval;

	हाल TEP_FILTER_EXP_MOD:
		वापस lval % rval;

	हाल TEP_FILTER_EXP_RSHIFT:
		वापस lval >> rval;

	हाल TEP_FILTER_EXP_LSHIFT:
		वापस lval << rval;

	हाल TEP_FILTER_EXP_AND:
		वापस lval & rval;

	हाल TEP_FILTER_EXP_OR:
		वापस lval | rval;

	हाल TEP_FILTER_EXP_XOR:
		वापस lval ^ rval;

	हाल TEP_FILTER_EXP_NOT:
	शेष:
		अगर (!*err)
			*err = TEP_ERRNO__INVALID_EXP_TYPE;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
get_arg_value(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
	      काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err)
अणु
	चयन (arg->type) अणु
	हाल TEP_FILTER_ARG_FIELD:
		वापस get_value(event, arg->field.field, record);

	हाल TEP_FILTER_ARG_VALUE:
		अगर (arg->value.type != TEP_FILTER_NUMBER) अणु
			अगर (!*err)
				*err = TEP_ERRNO__NOT_A_NUMBER;
		पूर्ण
		वापस arg->value.val;

	हाल TEP_FILTER_ARG_EXP:
		वापस get_exp_value(event, arg, record, err);

	शेष:
		अगर (!*err)
			*err = TEP_ERRNO__INVALID_ARG_TYPE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_num(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
		    काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err)
अणु
	अचिन्हित दीर्घ दीर्घ lval, rval;

	lval = get_arg_value(event, arg->num.left, record, err);
	rval = get_arg_value(event, arg->num.right, record, err);

	अगर (*err) अणु
		/*
		 * There was an error, no need to process anymore.
		 */
		वापस 0;
	पूर्ण

	चयन (arg->num.type) अणु
	हाल TEP_FILTER_CMP_EQ:
		वापस lval == rval;

	हाल TEP_FILTER_CMP_NE:
		वापस lval != rval;

	हाल TEP_FILTER_CMP_GT:
		वापस lval > rval;

	हाल TEP_FILTER_CMP_LT:
		वापस lval < rval;

	हाल TEP_FILTER_CMP_GE:
		वापस lval >= rval;

	हाल TEP_FILTER_CMP_LE:
		वापस lval <= rval;

	शेष:
		अगर (!*err)
			*err = TEP_ERRNO__ILLEGAL_INTEGER_CMP;
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *get_field_str(काष्ठा tep_filter_arg *arg, काष्ठा tep_record *record)
अणु
	काष्ठा tep_event *event;
	काष्ठा tep_handle *tep;
	अचिन्हित दीर्घ दीर्घ addr;
	स्थिर अक्षर *val = शून्य;
	अचिन्हित पूर्णांक size;
	अक्षर hex[64];

	/* If the field is not a string convert it */
	अगर (arg->str.field->flags & TEP_FIELD_IS_STRING) अणु
		val = record->data + arg->str.field->offset;
		size = arg->str.field->size;

		अगर (arg->str.field->flags & TEP_FIELD_IS_DYNAMIC) अणु
			addr = *(अचिन्हित पूर्णांक *)val;
			val = record->data + (addr & 0xffff);
			size = addr >> 16;
		पूर्ण

		/*
		 * We need to copy the data since we can't be sure the field
		 * is null terminated.
		 */
		अगर (*(val + size - 1)) अणु
			/* copy it */
			स_नकल(arg->str.buffer, val, arg->str.field->size);
			/* the buffer is alपढ़ोy शून्य terminated */
			val = arg->str.buffer;
		पूर्ण

	पूर्ण अन्यथा अणु
		event = arg->str.field->event;
		tep = event->tep;
		addr = get_value(event, arg->str.field, record);

		अगर (arg->str.field->flags & (TEP_FIELD_IS_POINTER | TEP_FIELD_IS_LONG))
			/* convert to a kernel symbol */
			val = tep_find_function(tep, addr);

		अगर (val == शून्य) अणु
			/* just use the hex of the string name */
			snम_लिखो(hex, 64, "0x%llx", addr);
			val = hex;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक test_str(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
		    काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err)
अणु
	स्थिर अक्षर *val;

	अगर (arg->str.field == &comm)
		val = get_comm(event, record);
	अन्यथा
		val = get_field_str(arg, record);

	चयन (arg->str.type) अणु
	हाल TEP_FILTER_CMP_MATCH:
		वापस म_भेद(val, arg->str.val) == 0;

	हाल TEP_FILTER_CMP_NOT_MATCH:
		वापस म_भेद(val, arg->str.val) != 0;

	हाल TEP_FILTER_CMP_REGEX:
		/* Returns zero on match */
		वापस !regexec(&arg->str.reg, val, 0, शून्य, 0);

	हाल TEP_FILTER_CMP_NOT_REGEX:
		वापस regexec(&arg->str.reg, val, 0, शून्य, 0);

	शेष:
		अगर (!*err)
			*err = TEP_ERRNO__ILLEGAL_STRING_CMP;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक test_op(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
		   काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err)
अणु
	चयन (arg->op.type) अणु
	हाल TEP_FILTER_OP_AND:
		वापस test_filter(event, arg->op.left, record, err) &&
			test_filter(event, arg->op.right, record, err);

	हाल TEP_FILTER_OP_OR:
		वापस test_filter(event, arg->op.left, record, err) ||
			test_filter(event, arg->op.right, record, err);

	हाल TEP_FILTER_OP_NOT:
		वापस !test_filter(event, arg->op.right, record, err);

	शेष:
		अगर (!*err)
			*err = TEP_ERRNO__INVALID_OP_TYPE;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक test_filter(काष्ठा tep_event *event, काष्ठा tep_filter_arg *arg,
		       काष्ठा tep_record *record, क्रमागत tep_त्रुटि_सं *err)
अणु
	अगर (*err) अणु
		/*
		 * There was an error, no need to process anymore.
		 */
		वापस 0;
	पूर्ण

	चयन (arg->type) अणु
	हाल TEP_FILTER_ARG_BOOLEAN:
		/* easy हाल */
		वापस arg->boolean.value;

	हाल TEP_FILTER_ARG_OP:
		वापस test_op(event, arg, record, err);

	हाल TEP_FILTER_ARG_NUM:
		वापस test_num(event, arg, record, err);

	हाल TEP_FILTER_ARG_STR:
		वापस test_str(event, arg, record, err);

	हाल TEP_FILTER_ARG_EXP:
	हाल TEP_FILTER_ARG_VALUE:
	हाल TEP_FILTER_ARG_FIELD:
		/*
		 * Expressions, fields and values evaluate
		 * to true अगर they वापस non zero
		 */
		वापस !!get_arg_value(event, arg, record, err);

	शेष:
		अगर (!*err)
			*err = TEP_ERRNO__INVALID_ARG_TYPE;
		वापस 0;
	पूर्ण
पूर्ण

/**
 * tep_event_filtered - वापस true अगर event has filter
 * @filter: filter काष्ठा with filter inक्रमmation
 * @event_id: event id to test अगर filter exists
 *
 * Returns 1 अगर filter found क्रम @event_id
 *   otherwise 0;
 */
पूर्णांक tep_event_filtered(काष्ठा tep_event_filter *filter, पूर्णांक event_id)
अणु
	काष्ठा tep_filter_type *filter_type;

	अगर (!filter->filters)
		वापस 0;

	filter_type = find_filter_type(filter, event_id);

	वापस filter_type ? 1 : 0;
पूर्ण

/**
 * tep_filter_match - test अगर a record matches a filter
 * @filter: filter काष्ठा with filter inक्रमmation
 * @record: the record to test against the filter
 *
 * Returns: match result or error code (prefixed with TEP_ERRNO__)
 * FILTER_MATCH - filter found क्रम event and @record matches
 * FILTER_MISS  - filter found क्रम event and @record करोes not match
 * FILTER_NOT_FOUND - no filter found क्रम @record's event
 * NO_FILTER - अगर no filters exist
 * otherwise - error occurred during test
 */
क्रमागत tep_त्रुटि_सं tep_filter_match(काष्ठा tep_event_filter *filter,
				काष्ठा tep_record *record)
अणु
	काष्ठा tep_handle *tep = filter->tep;
	काष्ठा tep_filter_type *filter_type;
	पूर्णांक event_id;
	पूर्णांक ret;
	क्रमागत tep_त्रुटि_सं err = 0;

	filter_init_error_buf(filter);

	अगर (!filter->filters)
		वापस TEP_ERRNO__NO_FILTER;

	event_id = tep_data_type(tep, record);

	filter_type = find_filter_type(filter, event_id);
	अगर (!filter_type)
		वापस TEP_ERRNO__FILTER_NOT_FOUND;

	ret = test_filter(filter_type->event, filter_type->filter, record, &err);
	अगर (err)
		वापस err;

	वापस ret ? TEP_ERRNO__FILTER_MATCH : TEP_ERRNO__FILTER_MISS;
पूर्ण

अटल अक्षर *op_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg)
अणु
	अक्षर *str = शून्य;
	अक्षर *left = शून्य;
	अक्षर *right = शून्य;
	अक्षर *op = शून्य;
	पूर्णांक left_val = -1;
	पूर्णांक right_val = -1;
	पूर्णांक val;

	चयन (arg->op.type) अणु
	हाल TEP_FILTER_OP_AND:
		op = "&&";
		/* fall through */
	हाल TEP_FILTER_OP_OR:
		अगर (!op)
			op = "||";

		left = arg_to_str(filter, arg->op.left);
		right = arg_to_str(filter, arg->op.right);
		अगर (!left || !right)
			अवरोध;

		/* Try to consolidate boolean values */
		अगर (म_भेद(left, "TRUE") == 0)
			left_val = 1;
		अन्यथा अगर (म_भेद(left, "FALSE") == 0)
			left_val = 0;

		अगर (म_भेद(right, "TRUE") == 0)
			right_val = 1;
		अन्यथा अगर (म_भेद(right, "FALSE") == 0)
			right_val = 0;

		अगर (left_val >= 0) अणु
			अगर ((arg->op.type == TEP_FILTER_OP_AND && !left_val) ||
			    (arg->op.type == TEP_FILTER_OP_OR && left_val)) अणु
				/* Just वापस left value */
				str = left;
				left = शून्य;
				अवरोध;
			पूर्ण
			अगर (right_val >= 0) अणु
				/* just evaluate this. */
				val = 0;
				चयन (arg->op.type) अणु
				हाल TEP_FILTER_OP_AND:
					val = left_val && right_val;
					अवरोध;
				हाल TEP_FILTER_OP_OR:
					val = left_val || right_val;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				अगर (aप्र_लिखो(&str, val ? "TRUE" : "FALSE") < 0)
					str = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (right_val >= 0) अणु
			अगर ((arg->op.type == TEP_FILTER_OP_AND && !right_val) ||
			    (arg->op.type == TEP_FILTER_OP_OR && right_val)) अणु
				/* Just वापस right value */
				str = right;
				right = शून्य;
				अवरोध;
			पूर्ण
			/* The right value is meaningless */
			str = left;
			left = शून्य;
			अवरोध;
		पूर्ण

		अगर (aप्र_लिखो(&str, "(%s) %s (%s)", left, op, right) < 0)
			str = शून्य;
		अवरोध;

	हाल TEP_FILTER_OP_NOT:
		op = "!";
		right = arg_to_str(filter, arg->op.right);
		अगर (!right)
			अवरोध;

		/* See अगर we can consolidate */
		अगर (म_भेद(right, "TRUE") == 0)
			right_val = 1;
		अन्यथा अगर (म_भेद(right, "FALSE") == 0)
			right_val = 0;
		अगर (right_val >= 0) अणु
			/* just वापस the opposite */
			अगर (aप्र_लिखो(&str, right_val ? "FALSE" : "TRUE") < 0)
				str = शून्य;
			अवरोध;
		पूर्ण
		अगर (aप्र_लिखो(&str, "%s(%s)", op, right) < 0)
			str = शून्य;
		अवरोध;

	शेष:
		/* ?? */
		अवरोध;
	पूर्ण
	मुक्त(left);
	मुक्त(right);
	वापस str;
पूर्ण

अटल अक्षर *val_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg)
अणु
	अक्षर *str = शून्य;

	अगर (aप्र_लिखो(&str, "%lld", arg->value.val) < 0)
		str = शून्य;

	वापस str;
पूर्ण

अटल अक्षर *field_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg)
अणु
	वापस strdup(arg->field.field->name);
पूर्ण

अटल अक्षर *exp_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg)
अणु
	अक्षर *lstr;
	अक्षर *rstr;
	अक्षर *op;
	अक्षर *str = शून्य;

	lstr = arg_to_str(filter, arg->exp.left);
	rstr = arg_to_str(filter, arg->exp.right);
	अगर (!lstr || !rstr)
		जाओ out;

	चयन (arg->exp.type) अणु
	हाल TEP_FILTER_EXP_ADD:
		op = "+";
		अवरोध;
	हाल TEP_FILTER_EXP_SUB:
		op = "-";
		अवरोध;
	हाल TEP_FILTER_EXP_MUL:
		op = "*";
		अवरोध;
	हाल TEP_FILTER_EXP_DIV:
		op = "/";
		अवरोध;
	हाल TEP_FILTER_EXP_MOD:
		op = "%";
		अवरोध;
	हाल TEP_FILTER_EXP_RSHIFT:
		op = ">>";
		अवरोध;
	हाल TEP_FILTER_EXP_LSHIFT:
		op = "<<";
		अवरोध;
	हाल TEP_FILTER_EXP_AND:
		op = "&";
		अवरोध;
	हाल TEP_FILTER_EXP_OR:
		op = "|";
		अवरोध;
	हाल TEP_FILTER_EXP_XOR:
		op = "^";
		अवरोध;
	शेष:
		op = "[ERROR IN EXPRESSION TYPE]";
		अवरोध;
	पूर्ण

	अगर (aप्र_लिखो(&str, "%s %s %s", lstr, op, rstr) < 0)
		str = शून्य;
out:
	मुक्त(lstr);
	मुक्त(rstr);

	वापस str;
पूर्ण

अटल अक्षर *num_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg)
अणु
	अक्षर *lstr;
	अक्षर *rstr;
	अक्षर *str = शून्य;
	अक्षर *op = शून्य;

	lstr = arg_to_str(filter, arg->num.left);
	rstr = arg_to_str(filter, arg->num.right);
	अगर (!lstr || !rstr)
		जाओ out;

	चयन (arg->num.type) अणु
	हाल TEP_FILTER_CMP_EQ:
		op = "==";
		/* fall through */
	हाल TEP_FILTER_CMP_NE:
		अगर (!op)
			op = "!=";
		/* fall through */
	हाल TEP_FILTER_CMP_GT:
		अगर (!op)
			op = ">";
		/* fall through */
	हाल TEP_FILTER_CMP_LT:
		अगर (!op)
			op = "<";
		/* fall through */
	हाल TEP_FILTER_CMP_GE:
		अगर (!op)
			op = ">=";
		/* fall through */
	हाल TEP_FILTER_CMP_LE:
		अगर (!op)
			op = "<=";

		अगर (aप्र_लिखो(&str, "%s %s %s", lstr, op, rstr) < 0)
			str = शून्य;
		अवरोध;

	शेष:
		/* ?? */
		अवरोध;
	पूर्ण

out:
	मुक्त(lstr);
	मुक्त(rstr);
	वापस str;
पूर्ण

अटल अक्षर *str_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg)
अणु
	अक्षर *str = शून्य;
	अक्षर *op = शून्य;

	चयन (arg->str.type) अणु
	हाल TEP_FILTER_CMP_MATCH:
		op = "==";
		/* fall through */
	हाल TEP_FILTER_CMP_NOT_MATCH:
		अगर (!op)
			op = "!=";
		/* fall through */
	हाल TEP_FILTER_CMP_REGEX:
		अगर (!op)
			op = "=~";
		/* fall through */
	हाल TEP_FILTER_CMP_NOT_REGEX:
		अगर (!op)
			op = "!~";

		अगर (aप्र_लिखो(&str, "%s %s \"%s\"",
			 arg->str.field->name, op, arg->str.val) < 0)
			str = शून्य;
		अवरोध;

	शेष:
		/* ?? */
		अवरोध;
	पूर्ण
	वापस str;
पूर्ण

अटल अक्षर *arg_to_str(काष्ठा tep_event_filter *filter, काष्ठा tep_filter_arg *arg)
अणु
	अक्षर *str = शून्य;

	चयन (arg->type) अणु
	हाल TEP_FILTER_ARG_BOOLEAN:
		अगर (aप्र_लिखो(&str, arg->boolean.value ? "TRUE" : "FALSE") < 0)
			str = शून्य;
		वापस str;

	हाल TEP_FILTER_ARG_OP:
		वापस op_to_str(filter, arg);

	हाल TEP_FILTER_ARG_NUM:
		वापस num_to_str(filter, arg);

	हाल TEP_FILTER_ARG_STR:
		वापस str_to_str(filter, arg);

	हाल TEP_FILTER_ARG_VALUE:
		वापस val_to_str(filter, arg);

	हाल TEP_FILTER_ARG_FIELD:
		वापस field_to_str(filter, arg);

	हाल TEP_FILTER_ARG_EXP:
		वापस exp_to_str(filter, arg);

	शेष:
		/* ?? */
		वापस शून्य;
	पूर्ण

पूर्ण

/**
 * tep_filter_make_string - वापस a string showing the filter
 * @filter: filter काष्ठा with filter inक्रमmation
 * @event_id: the event id to वापस the filter string with
 *
 * Returns a string that displays the filter contents.
 *  This string must be मुक्तd with मुक्त(str).
 *  शून्य is वापसed अगर no filter is found or allocation failed.
 */
अक्षर *
tep_filter_make_string(काष्ठा tep_event_filter *filter, पूर्णांक event_id)
अणु
	काष्ठा tep_filter_type *filter_type;

	अगर (!filter->filters)
		वापस शून्य;

	filter_type = find_filter_type(filter, event_id);

	अगर (!filter_type)
		वापस शून्य;

	वापस arg_to_str(filter, filter_type->filter);
पूर्ण

/**
 * tep_filter_compare - compare two filters and वापस अगर they are the same
 * @filter1: Filter to compare with @filter2
 * @filter2: Filter to compare with @filter1
 *
 * Returns:
 *  1 अगर the two filters hold the same content.
 *  0 अगर they करो not.
 */
पूर्णांक tep_filter_compare(काष्ठा tep_event_filter *filter1, काष्ठा tep_event_filter *filter2)
अणु
	काष्ठा tep_filter_type *filter_type1;
	काष्ठा tep_filter_type *filter_type2;
	अक्षर *str1, *str2;
	पूर्णांक result;
	पूर्णांक i;

	/* Do the easy checks first */
	अगर (filter1->filters != filter2->filters)
		वापस 0;
	अगर (!filter1->filters && !filter2->filters)
		वापस 1;

	/*
	 * Now take a look at each of the events to see अगर they have the same
	 * filters to them.
	 */
	क्रम (i = 0; i < filter1->filters; i++) अणु
		filter_type1 = &filter1->event_filters[i];
		filter_type2 = find_filter_type(filter2, filter_type1->event_id);
		अगर (!filter_type2)
			अवरोध;
		अगर (filter_type1->filter->type != filter_type2->filter->type)
			अवरोध;
		/* The best way to compare complex filters is with strings */
		str1 = arg_to_str(filter1, filter_type1->filter);
		str2 = arg_to_str(filter2, filter_type2->filter);
		अगर (str1 && str2)
			result = म_भेद(str1, str2) != 0;
		अन्यथा
			/* bail out अगर allocation fails */
			result = 1;

		मुक्त(str1);
		मुक्त(str2);
		अगर (result)
			अवरोध;
	पूर्ण

	अगर (i < filter1->filters)
		वापस 0;
	वापस 1;
पूर्ण

