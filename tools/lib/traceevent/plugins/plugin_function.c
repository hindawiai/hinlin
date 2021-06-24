<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "event-parse.h"
#समावेश "event-utils.h"
#समावेश "trace-seq.h"

अटल काष्ठा func_stack अणु
	पूर्णांक size;
	अक्षर **stack;
पूर्ण *fstack;

अटल पूर्णांक cpus = -1;

#घोषणा STK_BLK 10

काष्ठा tep_plugin_option plugin_options[] =
अणु
	अणु
		.name = "parent",
		.plugin_alias = "ftrace",
		.description =
		"Print parent of functions for function events",
	पूर्ण,
	अणु
		.name = "indent",
		.plugin_alias = "ftrace",
		.description =
		"Try to show function call indents, based on parents",
		.set = 1,
	पूर्ण,
	अणु
		.name = "offset",
		.plugin_alias = "ftrace",
		.description =
		"Show function names as well as their offsets",
		.set = 0,
	पूर्ण,
	अणु
		.name = शून्य,
	पूर्ण
पूर्ण;

अटल काष्ठा tep_plugin_option *ftrace_parent = &plugin_options[0];
अटल काष्ठा tep_plugin_option *ftrace_indent = &plugin_options[1];
अटल काष्ठा tep_plugin_option *ftrace_offset = &plugin_options[2];

अटल व्योम add_child(काष्ठा func_stack *stack, स्थिर अक्षर *child, पूर्णांक pos)
अणु
	पूर्णांक i;

	अगर (!child)
		वापस;

	अगर (pos < stack->size)
		मुक्त(stack->stack[pos]);
	अन्यथा अणु
		अक्षर **ptr;

		ptr = पुनः_स्मृति(stack->stack, माप(अक्षर *) *
			      (stack->size + STK_BLK));
		अगर (!ptr) अणु
			warning("could not allocate plugin memory\n");
			वापस;
		पूर्ण

		stack->stack = ptr;

		क्रम (i = stack->size; i < stack->size + STK_BLK; i++)
			stack->stack[i] = शून्य;
		stack->size += STK_BLK;
	पूर्ण

	stack->stack[pos] = strdup(child);
पूर्ण

अटल पूर्णांक add_and_get_index(स्थिर अक्षर *parent, स्थिर अक्षर *child, पूर्णांक cpu)
अणु
	पूर्णांक i;

	अगर (cpu < 0)
		वापस 0;

	अगर (cpu > cpus) अणु
		काष्ठा func_stack *ptr;

		ptr = पुनः_स्मृति(fstack, माप(*fstack) * (cpu + 1));
		अगर (!ptr) अणु
			warning("could not allocate plugin memory\n");
			वापस 0;
		पूर्ण

		fstack = ptr;

		/* Account क्रम holes in the cpu count */
		क्रम (i = cpus + 1; i <= cpu; i++)
			स_रखो(&fstack[i], 0, माप(fstack[i]));
		cpus = cpu;
	पूर्ण

	क्रम (i = 0; i < fstack[cpu].size && fstack[cpu].stack[i]; i++) अणु
		अगर (म_भेद(parent, fstack[cpu].stack[i]) == 0) अणु
			add_child(&fstack[cpu], child, i+1);
			वापस i;
		पूर्ण
	पूर्ण

	/* Not found */
	add_child(&fstack[cpu], parent, 0);
	add_child(&fstack[cpu], child, 1);
	वापस 0;
पूर्ण

अटल व्योम show_function(काष्ठा trace_seq *s, काष्ठा tep_handle *tep,
			  स्थिर अक्षर *func, अचिन्हित दीर्घ दीर्घ function)
अणु
	अचिन्हित दीर्घ दीर्घ offset;

	trace_seq_म_लिखो(s, "%s", func);
	अगर (ftrace_offset->set) अणु
		offset = tep_find_function_address(tep, function);
		trace_seq_म_लिखो(s, "+0x%x ", (पूर्णांक)(function - offset));
	पूर्ण
पूर्ण

अटल पूर्णांक function_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
			    काष्ठा tep_event *event, व्योम *context)
अणु
	काष्ठा tep_handle *tep = event->tep;
	अचिन्हित दीर्घ दीर्घ function;
	अचिन्हित दीर्घ दीर्घ pfunction;
	स्थिर अक्षर *func;
	स्थिर अक्षर *parent;
	पूर्णांक index = 0;

	अगर (tep_get_field_val(s, event, "ip", record, &function, 1))
		वापस trace_seq_अ_दो(s, '!');

	func = tep_find_function(tep, function);

	अगर (tep_get_field_val(s, event, "parent_ip", record, &pfunction, 1))
		वापस trace_seq_अ_दो(s, '!');

	parent = tep_find_function(tep, pfunction);

	अगर (parent && ftrace_indent->set)
		index = add_and_get_index(parent, func, record->cpu);

	trace_seq_म_लिखो(s, "%*s", index*3, "");

	अगर (func)
		show_function(s, tep, func, function);
	अन्यथा
		trace_seq_म_लिखो(s, "0x%llx", function);

	अगर (ftrace_parent->set) अणु
		trace_seq_म_लिखो(s, " <-- ");
		अगर (parent)
			show_function(s, tep, parent, pfunction);
		अन्यथा
			trace_seq_म_लिखो(s, "0x%llx", pfunction);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
trace_stack_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
		    काष्ठा tep_event *event, व्योम *context)
अणु
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित दीर्घ दीर्घ addr;
	स्थिर अक्षर *func;
	पूर्णांक दीर्घ_size;
	व्योम *data = record->data;

	field = tep_find_any_field(event, "caller");
	अगर (!field) अणु
		trace_seq_म_लिखो(s, "<CANT FIND FIELD %s>", "caller");
		वापस 0;
	पूर्ण

	trace_seq_माला_दो(s, "<stack trace >\n");

	दीर्घ_size = tep_get_दीर्घ_size(event->tep);

	क्रम (data += field->offset; data < record->data + record->size;
	     data += दीर्घ_size) अणु
		addr = tep_पढ़ो_number(event->tep, data, दीर्घ_size);

		अगर ((दीर्घ_size == 8 && addr == (अचिन्हित दीर्घ दीर्घ)-1) ||
		    ((पूर्णांक)addr == -1))
			अवरोध;

		func = tep_find_function(event->tep, addr);
		अगर (func)
			trace_seq_म_लिखो(s, "=> %s (%llx)\n", func, addr);
		अन्यथा
			trace_seq_म_लिखो(s, "=> %llx\n", addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
trace_raw_data_handler(काष्ठा trace_seq *s, काष्ठा tep_record *record,
		    काष्ठा tep_event *event, व्योम *context)
अणु
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित दीर्घ दीर्घ id;
	पूर्णांक दीर्घ_size;
	व्योम *data = record->data;

	अगर (tep_get_field_val(s, event, "id", record, &id, 1))
		वापस trace_seq_अ_दो(s, '!');

	trace_seq_म_लिखो(s, "# %llx", id);

	field = tep_find_any_field(event, "buf");
	अगर (!field) अणु
		trace_seq_म_लिखो(s, "<CANT FIND FIELD %s>", "buf");
		वापस 0;
	पूर्ण

	दीर्घ_size = tep_get_दीर्घ_size(event->tep);

	क्रम (data += field->offset; data < record->data + record->size;
	     data += दीर्घ_size) अणु
		पूर्णांक size = माप(दीर्घ);
		पूर्णांक left = (record->data + record->size) - data;
		पूर्णांक i;

		अगर (size > left)
			size = left;

		क्रम (i = 0; i < size; i++)
			trace_seq_म_लिखो(s, " %02x", *(अचिन्हित अक्षर *)(data + i));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_event_handler(tep, -1, "ftrace", "function",
				   function_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "ftrace", "kernel_stack",
				      trace_stack_handler, शून्य);

	tep_रेजिस्टर_event_handler(tep, -1, "ftrace", "raw_data",
				      trace_raw_data_handler, शून्य);

	tep_plugin_add_options("ftrace", plugin_options);

	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	पूर्णांक i, x;

	tep_unरेजिस्टर_event_handler(tep, -1, "ftrace", "function",
				     function_handler, शून्य);

	क्रम (i = 0; i <= cpus; i++) अणु
		क्रम (x = 0; x < fstack[i].size && fstack[i].stack[x]; x++)
			मुक्त(fstack[i].stack[x]);
		मुक्त(fstack[i].stack);
	पूर्ण

	tep_plugin_हटाओ_options(plugin_options);

	मुक्त(fstack);
	fstack = शून्य;
	cpus = -1;
पूर्ण
