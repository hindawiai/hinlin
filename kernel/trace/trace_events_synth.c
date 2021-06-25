<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_events_synth - synthetic trace events
 *
 * Copyright (C) 2015, 2020 Tom Zanussi <tom.zanussi@linux.पूर्णांकel.com>
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

#समावेश "trace_synth.h"

#अघोषित ERRORS
#घोषणा ERRORS	\
	C(BAD_NAME,		"Illegal name"),		\
	C(INVALID_CMD,		"Command must be of the form: <name> field[;field] ..."),\
	C(INVALID_DYN_CMD,	"Command must be of the form: s or -:[synthetic/]<name> field[;field] ..."),\
	C(EVENT_EXISTS,		"Event already exists"),	\
	C(TOO_MANY_FIELDS,	"Too many fields"),		\
	C(INCOMPLETE_TYPE,	"Incomplete type"),		\
	C(INVALID_TYPE,		"Invalid type"),		\
	C(INVALID_FIELD,        "Invalid field"),		\
	C(INVALID_ARRAY_SPEC,	"Invalid array specification"),

#अघोषित C
#घोषणा C(a, b)		SYNTH_ERR_##a

क्रमागत अणु ERRORS पूर्ण;

#अघोषित C
#घोषणा C(a, b)		b

अटल स्थिर अक्षर *err_text[] = अणु ERRORS पूर्ण;

अटल अक्षर last_cmd[MAX_FILTER_STR_VAL];

अटल पूर्णांक errpos(स्थिर अक्षर *str)
अणु
	वापस err_pos(last_cmd, str);
पूर्ण

अटल व्योम last_cmd_set(स्थिर अक्षर *str)
अणु
	अगर (!str)
		वापस;

	म_नकलन(last_cmd, str, MAX_FILTER_STR_VAL - 1);
पूर्ण

अटल व्योम synth_err(u8 err_type, u8 err_pos)
अणु
	tracing_log_err(शून्य, "synthetic_events", last_cmd, err_text,
			err_type, err_pos);
पूर्ण

अटल पूर्णांक create_synth_event(स्थिर अक्षर *raw_command);
अटल पूर्णांक synth_event_show(काष्ठा seq_file *m, काष्ठा dyn_event *ev);
अटल पूर्णांक synth_event_release(काष्ठा dyn_event *ev);
अटल bool synth_event_is_busy(काष्ठा dyn_event *ev);
अटल bool synth_event_match(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event,
			पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा dyn_event *ev);

अटल काष्ठा dyn_event_operations synth_event_ops = अणु
	.create = create_synth_event,
	.show = synth_event_show,
	.is_busy = synth_event_is_busy,
	.मुक्त = synth_event_release,
	.match = synth_event_match,
पूर्ण;

अटल bool is_synth_event(काष्ठा dyn_event *ev)
अणु
	वापस ev->ops == &synth_event_ops;
पूर्ण

अटल काष्ठा synth_event *to_synth_event(काष्ठा dyn_event *ev)
अणु
	वापस container_of(ev, काष्ठा synth_event, devent);
पूर्ण

अटल bool synth_event_is_busy(काष्ठा dyn_event *ev)
अणु
	काष्ठा synth_event *event = to_synth_event(ev);

	वापस event->ref != 0;
पूर्ण

अटल bool synth_event_match(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event,
			पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा dyn_event *ev)
अणु
	काष्ठा synth_event *sev = to_synth_event(ev);

	वापस म_भेद(sev->name, event) == 0 &&
		(!प्रणाली || म_भेद(प्रणाली, SYNTH_SYSTEM) == 0);
पूर्ण

काष्ठा synth_trace_event अणु
	काष्ठा trace_entry	ent;
	u64			fields[];
पूर्ण;

अटल पूर्णांक synth_event_define_fields(काष्ठा trace_event_call *call)
अणु
	काष्ठा synth_trace_event trace;
	पूर्णांक offset = दुरत्व(typeof(trace), fields);
	काष्ठा synth_event *event = call->data;
	अचिन्हित पूर्णांक i, size, n_u64;
	अक्षर *name, *type;
	bool is_चिन्हित;
	पूर्णांक ret = 0;

	क्रम (i = 0, n_u64 = 0; i < event->n_fields; i++) अणु
		size = event->fields[i]->size;
		is_चिन्हित = event->fields[i]->is_चिन्हित;
		type = event->fields[i]->type;
		name = event->fields[i]->name;
		ret = trace_define_field(call, type, name, offset, size,
					 is_चिन्हित, FILTER_OTHER);
		अगर (ret)
			अवरोध;

		event->fields[i]->offset = n_u64;

		अगर (event->fields[i]->is_string && !event->fields[i]->is_dynamic) अणु
			offset += STR_VAR_LEN_MAX;
			n_u64 += STR_VAR_LEN_MAX / माप(u64);
		पूर्ण अन्यथा अणु
			offset += माप(u64);
			n_u64++;
		पूर्ण
	पूर्ण

	event->n_u64 = n_u64;

	वापस ret;
पूर्ण

अटल bool synth_field_चिन्हित(अक्षर *type)
अणु
	अगर (str_has_prefix(type, "u"))
		वापस false;
	अगर (म_भेद(type, "gfp_t") == 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक synth_field_is_string(अक्षर *type)
अणु
	अगर (म_माला(type, "char[") != शून्य)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक synth_field_string_size(अक्षर *type)
अणु
	अक्षर buf[4], *end, *start;
	अचिन्हित पूर्णांक len;
	पूर्णांक size, err;

	start = म_माला(type, "char[");
	अगर (start == शून्य)
		वापस -EINVAL;
	start += माप("char[") - 1;

	end = म_अक्षर(type, ']');
	अगर (!end || end < start || type + म_माप(type) > end + 1)
		वापस -EINVAL;

	len = end - start;
	अगर (len > 3)
		वापस -EINVAL;

	अगर (len == 0)
		वापस 0; /* variable-length string */

	म_नकलन(buf, start, len);
	buf[len] = '\0';

	err = kstrtouपूर्णांक(buf, 0, &size);
	अगर (err)
		वापस err;

	अगर (size > STR_VAR_LEN_MAX)
		वापस -EINVAL;

	वापस size;
पूर्ण

अटल पूर्णांक synth_field_size(अक्षर *type)
अणु
	पूर्णांक size = 0;

	अगर (म_भेद(type, "s64") == 0)
		size = माप(s64);
	अन्यथा अगर (म_भेद(type, "u64") == 0)
		size = माप(u64);
	अन्यथा अगर (म_भेद(type, "s32") == 0)
		size = माप(s32);
	अन्यथा अगर (म_भेद(type, "u32") == 0)
		size = माप(u32);
	अन्यथा अगर (म_भेद(type, "s16") == 0)
		size = माप(s16);
	अन्यथा अगर (म_भेद(type, "u16") == 0)
		size = माप(u16);
	अन्यथा अगर (म_भेद(type, "s8") == 0)
		size = माप(s8);
	अन्यथा अगर (म_भेद(type, "u8") == 0)
		size = माप(u8);
	अन्यथा अगर (म_भेद(type, "char") == 0)
		size = माप(अक्षर);
	अन्यथा अगर (म_भेद(type, "unsigned char") == 0)
		size = माप(अचिन्हित अक्षर);
	अन्यथा अगर (म_भेद(type, "int") == 0)
		size = माप(पूर्णांक);
	अन्यथा अगर (म_भेद(type, "unsigned int") == 0)
		size = माप(अचिन्हित पूर्णांक);
	अन्यथा अगर (म_भेद(type, "long") == 0)
		size = माप(दीर्घ);
	अन्यथा अगर (म_भेद(type, "unsigned long") == 0)
		size = माप(अचिन्हित दीर्घ);
	अन्यथा अगर (म_भेद(type, "bool") == 0)
		size = माप(bool);
	अन्यथा अगर (म_भेद(type, "pid_t") == 0)
		size = माप(pid_t);
	अन्यथा अगर (म_भेद(type, "gfp_t") == 0)
		size = माप(gfp_t);
	अन्यथा अगर (synth_field_is_string(type))
		size = synth_field_string_size(type);

	वापस size;
पूर्ण

अटल स्थिर अक्षर *synth_field_fmt(अक्षर *type)
अणु
	स्थिर अक्षर *fmt = "%llu";

	अगर (म_भेद(type, "s64") == 0)
		fmt = "%lld";
	अन्यथा अगर (म_भेद(type, "u64") == 0)
		fmt = "%llu";
	अन्यथा अगर (म_भेद(type, "s32") == 0)
		fmt = "%d";
	अन्यथा अगर (म_भेद(type, "u32") == 0)
		fmt = "%u";
	अन्यथा अगर (म_भेद(type, "s16") == 0)
		fmt = "%d";
	अन्यथा अगर (म_भेद(type, "u16") == 0)
		fmt = "%u";
	अन्यथा अगर (म_भेद(type, "s8") == 0)
		fmt = "%d";
	अन्यथा अगर (म_भेद(type, "u8") == 0)
		fmt = "%u";
	अन्यथा अगर (म_भेद(type, "char") == 0)
		fmt = "%d";
	अन्यथा अगर (म_भेद(type, "unsigned char") == 0)
		fmt = "%u";
	अन्यथा अगर (म_भेद(type, "int") == 0)
		fmt = "%d";
	अन्यथा अगर (म_भेद(type, "unsigned int") == 0)
		fmt = "%u";
	अन्यथा अगर (म_भेद(type, "long") == 0)
		fmt = "%ld";
	अन्यथा अगर (म_भेद(type, "unsigned long") == 0)
		fmt = "%lu";
	अन्यथा अगर (म_भेद(type, "bool") == 0)
		fmt = "%d";
	अन्यथा अगर (म_भेद(type, "pid_t") == 0)
		fmt = "%d";
	अन्यथा अगर (म_भेद(type, "gfp_t") == 0)
		fmt = "%x";
	अन्यथा अगर (synth_field_is_string(type))
		fmt = "%.*s";

	वापस fmt;
पूर्ण

अटल व्योम prपूर्णांक_synth_event_num_val(काष्ठा trace_seq *s,
				      अक्षर *prपूर्णांक_fmt, अक्षर *name,
				      पूर्णांक size, u64 val, अक्षर *space)
अणु
	चयन (size) अणु
	हाल 1:
		trace_seq_म_लिखो(s, prपूर्णांक_fmt, name, (u8)val, space);
		अवरोध;

	हाल 2:
		trace_seq_म_लिखो(s, prपूर्णांक_fmt, name, (u16)val, space);
		अवरोध;

	हाल 4:
		trace_seq_म_लिखो(s, prपूर्णांक_fmt, name, (u32)val, space);
		अवरोध;

	शेष:
		trace_seq_म_लिखो(s, prपूर्णांक_fmt, name, val, space);
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत prपूर्णांक_line_t prपूर्णांक_synth_event(काष्ठा trace_iterator *iter,
					   पूर्णांक flags,
					   काष्ठा trace_event *event)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा synth_trace_event *entry;
	काष्ठा synth_event *se;
	अचिन्हित पूर्णांक i, n_u64;
	अक्षर prपूर्णांक_fmt[32];
	स्थिर अक्षर *fmt;

	entry = (काष्ठा synth_trace_event *)iter->ent;
	se = container_of(event, काष्ठा synth_event, call.event);

	trace_seq_म_लिखो(s, "%s: ", se->name);

	क्रम (i = 0, n_u64 = 0; i < se->n_fields; i++) अणु
		अगर (trace_seq_has_overflowed(s))
			जाओ end;

		fmt = synth_field_fmt(se->fields[i]->type);

		/* parameter types */
		अगर (tr && tr->trace_flags & TRACE_ITER_VERBOSE)
			trace_seq_म_लिखो(s, "%s ", fmt);

		snम_लिखो(prपूर्णांक_fmt, माप(prपूर्णांक_fmt), "%%s=%s%%s", fmt);

		/* parameter values */
		अगर (se->fields[i]->is_string) अणु
			अगर (se->fields[i]->is_dynamic) अणु
				u32 offset, data_offset;
				अक्षर *str_field;

				offset = (u32)entry->fields[n_u64];
				data_offset = offset & 0xffff;

				str_field = (अक्षर *)entry + data_offset;

				trace_seq_म_लिखो(s, prपूर्णांक_fmt, se->fields[i]->name,
						 STR_VAR_LEN_MAX,
						 str_field,
						 i == se->n_fields - 1 ? "" : " ");
				n_u64++;
			पूर्ण अन्यथा अणु
				trace_seq_म_लिखो(s, prपूर्णांक_fmt, se->fields[i]->name,
						 STR_VAR_LEN_MAX,
						 (अक्षर *)&entry->fields[n_u64],
						 i == se->n_fields - 1 ? "" : " ");
				n_u64 += STR_VAR_LEN_MAX / माप(u64);
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा trace_prपूर्णांक_flags __flags[] = अणु
			    __def_gfpflag_names, अणु-1, शून्यपूर्ण पूर्ण;
			अक्षर *space = (i == se->n_fields - 1 ? "" : " ");

			prपूर्णांक_synth_event_num_val(s, prपूर्णांक_fmt,
						  se->fields[i]->name,
						  se->fields[i]->size,
						  entry->fields[n_u64],
						  space);

			अगर (म_भेद(se->fields[i]->type, "gfp_t") == 0) अणु
				trace_seq_माला_दो(s, " (");
				trace_prपूर्णांक_flags_seq(s, "|",
						      entry->fields[n_u64],
						      __flags);
				trace_seq_अ_दो(s, ')');
			पूर्ण
			n_u64++;
		पूर्ण
	पूर्ण
end:
	trace_seq_अ_दो(s, '\n');

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions synth_event_funcs = अणु
	.trace		= prपूर्णांक_synth_event
पूर्ण;

अटल अचिन्हित पूर्णांक trace_string(काष्ठा synth_trace_event *entry,
				 काष्ठा synth_event *event,
				 अक्षर *str_val,
				 bool is_dynamic,
				 अचिन्हित पूर्णांक data_size,
				 अचिन्हित पूर्णांक *n_u64)
अणु
	अचिन्हित पूर्णांक len = 0;
	अक्षर *str_field;

	अगर (is_dynamic) अणु
		u32 data_offset;

		data_offset = दुरत्व(typeof(*entry), fields);
		data_offset += event->n_u64 * माप(u64);
		data_offset += data_size;

		str_field = (अक्षर *)entry + data_offset;

		len = म_माप(str_val) + 1;
		strscpy(str_field, str_val, len);

		data_offset |= len << 16;
		*(u32 *)&entry->fields[*n_u64] = data_offset;

		(*n_u64)++;
	पूर्ण अन्यथा अणु
		str_field = (अक्षर *)&entry->fields[*n_u64];

		strscpy(str_field, str_val, STR_VAR_LEN_MAX);
		(*n_u64) += STR_VAR_LEN_MAX / माप(u64);
	पूर्ण

	वापस len;
पूर्ण

अटल notrace व्योम trace_event_raw_event_synth(व्योम *__data,
						u64 *var_ref_vals,
						अचिन्हित पूर्णांक *var_ref_idx)
अणु
	अचिन्हित पूर्णांक i, n_u64, val_idx, len, data_size = 0;
	काष्ठा trace_event_file *trace_file = __data;
	काष्ठा synth_trace_event *entry;
	काष्ठा trace_event_buffer fbuffer;
	काष्ठा trace_buffer *buffer;
	काष्ठा synth_event *event;
	पूर्णांक fields_size = 0;

	event = trace_file->event_call->data;

	अगर (trace_trigger_soft_disabled(trace_file))
		वापस;

	fields_size = event->n_u64 * माप(u64);

	क्रम (i = 0; i < event->n_dynamic_fields; i++) अणु
		अचिन्हित पूर्णांक field_pos = event->dynamic_fields[i]->field_pos;
		अक्षर *str_val;

		val_idx = var_ref_idx[field_pos];
		str_val = (अक्षर *)(दीर्घ)var_ref_vals[val_idx];

		len = म_माप(str_val) + 1;

		fields_size += len;
	पूर्ण

	/*
	 * Aव्योम ring buffer recursion detection, as this event
	 * is being perक्रमmed within another event.
	 */
	buffer = trace_file->tr->array_buffer.buffer;
	ring_buffer_nest_start(buffer);

	entry = trace_event_buffer_reserve(&fbuffer, trace_file,
					   माप(*entry) + fields_size);
	अगर (!entry)
		जाओ out;

	क्रम (i = 0, n_u64 = 0; i < event->n_fields; i++) अणु
		val_idx = var_ref_idx[i];
		अगर (event->fields[i]->is_string) अणु
			अक्षर *str_val = (अक्षर *)(दीर्घ)var_ref_vals[val_idx];

			len = trace_string(entry, event, str_val,
					   event->fields[i]->is_dynamic,
					   data_size, &n_u64);
			data_size += len; /* only dynamic string increments */
		पूर्ण अन्यथा अणु
			काष्ठा synth_field *field = event->fields[i];
			u64 val = var_ref_vals[val_idx];

			चयन (field->size) अणु
			हाल 1:
				*(u8 *)&entry->fields[n_u64] = (u8)val;
				अवरोध;

			हाल 2:
				*(u16 *)&entry->fields[n_u64] = (u16)val;
				अवरोध;

			हाल 4:
				*(u32 *)&entry->fields[n_u64] = (u32)val;
				अवरोध;

			शेष:
				entry->fields[n_u64] = val;
				अवरोध;
			पूर्ण
			n_u64++;
		पूर्ण
	पूर्ण

	trace_event_buffer_commit(&fbuffer);
out:
	ring_buffer_nest_end(buffer);
पूर्ण

अटल व्योम मुक्त_synth_event_prपूर्णांक_fmt(काष्ठा trace_event_call *call)
अणु
	अगर (call) अणु
		kमुक्त(call->prपूर्णांक_fmt);
		call->prपूर्णांक_fmt = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __set_synth_event_prपूर्णांक_fmt(काष्ठा synth_event *event,
				       अक्षर *buf, पूर्णांक len)
अणु
	स्थिर अक्षर *fmt;
	पूर्णांक pos = 0;
	पूर्णांक i;

	/* When len=0, we just calculate the needed length */
#घोषणा LEN_OR_ZERO (len ? len - pos : 0)

	pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "\"");
	क्रम (i = 0; i < event->n_fields; i++) अणु
		fmt = synth_field_fmt(event->fields[i]->type);
		pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "%s=%s%s",
				event->fields[i]->name, fmt,
				i == event->n_fields - 1 ? "" : ", ");
	पूर्ण
	pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "\"");

	क्रम (i = 0; i < event->n_fields; i++) अणु
		अगर (event->fields[i]->is_string &&
		    event->fields[i]->is_dynamic)
			pos += snम_लिखो(buf + pos, LEN_OR_ZERO,
				", __get_str(%s)", event->fields[i]->name);
		अन्यथा
			pos += snम_लिखो(buf + pos, LEN_OR_ZERO,
					", REC->%s", event->fields[i]->name);
	पूर्ण

#अघोषित LEN_OR_ZERO

	/* वापस the length of prपूर्णांक_fmt */
	वापस pos;
पूर्ण

अटल पूर्णांक set_synth_event_prपूर्णांक_fmt(काष्ठा trace_event_call *call)
अणु
	काष्ठा synth_event *event = call->data;
	अक्षर *prपूर्णांक_fmt;
	पूर्णांक len;

	/* First: called with 0 length to calculate the needed length */
	len = __set_synth_event_prपूर्णांक_fmt(event, शून्य, 0);

	prपूर्णांक_fmt = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!prपूर्णांक_fmt)
		वापस -ENOMEM;

	/* Second: actually ग_लिखो the @prपूर्णांक_fmt */
	__set_synth_event_prपूर्णांक_fmt(event, prपूर्णांक_fmt, len + 1);
	call->prपूर्णांक_fmt = prपूर्णांक_fmt;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_synth_field(काष्ठा synth_field *field)
अणु
	kमुक्त(field->type);
	kमुक्त(field->name);
	kमुक्त(field);
पूर्ण

अटल पूर्णांक check_field_version(स्थिर अक्षर *prefix, स्थिर अक्षर *field_type,
			       स्थिर अक्षर *field_name)
अणु
	/*
	 * For backward compatibility, the old synthetic event command
	 * क्रमmat did not require semicolons, and in order to not
	 * अवरोध user space, that old क्रमmat must still work. If a new
	 * feature is added, then the क्रमmat that uses the new feature
	 * will be required to have semicolons, as nothing that uses
	 * the old क्रमmat would be using the new, yet to be created,
	 * feature. When a new feature is added, this will detect it,
	 * and वापस a number greater than 1, and require the क्रमmat
	 * to use semicolons.
	 */
	वापस 1;
पूर्ण

अटल काष्ठा synth_field *parse_synth_field(पूर्णांक argc, अक्षर **argv,
					     पूर्णांक *consumed, पूर्णांक *field_version)
अणु
	स्थिर अक्षर *prefix = शून्य, *field_type = argv[0], *field_name, *array;
	काष्ठा synth_field *field;
	पूर्णांक len, ret = -ENOMEM;
	काष्ठा seq_buf s;
	sमाप_प्रकार size;

	अगर (!म_भेद(field_type, "unsigned")) अणु
		अगर (argc < 3) अणु
			synth_err(SYNTH_ERR_INCOMPLETE_TYPE, errpos(field_type));
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		prefix = "unsigned ";
		field_type = argv[1];
		field_name = argv[2];
		*consumed += 3;
	पूर्ण अन्यथा अणु
		field_name = argv[1];
		*consumed += 2;
	पूर्ण

	अगर (!field_name) अणु
		synth_err(SYNTH_ERR_INVALID_FIELD, errpos(field_type));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	*field_version = check_field_version(prefix, field_type, field_name);

	field = kzalloc(माप(*field), GFP_KERNEL);
	अगर (!field)
		वापस ERR_PTR(-ENOMEM);

	len = म_माप(field_name);
	array = म_अक्षर(field_name, '[');
	अगर (array)
		len -= म_माप(array);

	field->name = kmemdup_nul(field_name, len, GFP_KERNEL);
	अगर (!field->name)
		जाओ मुक्त;

	अगर (!is_good_name(field->name)) अणु
		synth_err(SYNTH_ERR_BAD_NAME, errpos(field_name));
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	len = म_माप(field_type) + 1;

	अगर (array)
		len += म_माप(array);

	अगर (prefix)
		len += म_माप(prefix);

	field->type = kzalloc(len, GFP_KERNEL);
	अगर (!field->type)
		जाओ मुक्त;

	seq_buf_init(&s, field->type, len);
	अगर (prefix)
		seq_buf_माला_दो(&s, prefix);
	seq_buf_माला_दो(&s, field_type);
	अगर (array)
		seq_buf_माला_दो(&s, array);
	अगर (WARN_ON_ONCE(!seq_buf_buffer_left(&s)))
		जाओ मुक्त;

	s.buffer[s.len] = '\0';

	size = synth_field_size(field->type);
	अगर (size < 0) अणु
		अगर (array)
			synth_err(SYNTH_ERR_INVALID_ARRAY_SPEC, errpos(field_name));
		अन्यथा
			synth_err(SYNTH_ERR_INVALID_TYPE, errpos(field_type));
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण अन्यथा अगर (size == 0) अणु
		अगर (synth_field_is_string(field->type)) अणु
			अक्षर *type;

			len = माप("__data_loc ") + म_माप(field->type) + 1;
			type = kzalloc(len, GFP_KERNEL);
			अगर (!type)
				जाओ मुक्त;

			seq_buf_init(&s, type, len);
			seq_buf_माला_दो(&s, "__data_loc ");
			seq_buf_माला_दो(&s, field->type);

			अगर (WARN_ON_ONCE(!seq_buf_buffer_left(&s)))
				जाओ मुक्त;
			s.buffer[s.len] = '\0';

			kमुक्त(field->type);
			field->type = type;

			field->is_dynamic = true;
			size = माप(u64);
		पूर्ण अन्यथा अणु
			synth_err(SYNTH_ERR_INVALID_TYPE, errpos(field_type));
			ret = -EINVAL;
			जाओ मुक्त;
		पूर्ण
	पूर्ण
	field->size = size;

	अगर (synth_field_is_string(field->type))
		field->is_string = true;

	field->is_चिन्हित = synth_field_चिन्हित(field->type);
 out:
	वापस field;
 मुक्त:
	मुक्त_synth_field(field);
	field = ERR_PTR(ret);
	जाओ out;
पूर्ण

अटल व्योम मुक्त_synth_tracepoपूर्णांक(काष्ठा tracepoपूर्णांक *tp)
अणु
	अगर (!tp)
		वापस;

	kमुक्त(tp->name);
	kमुक्त(tp);
पूर्ण

अटल काष्ठा tracepoपूर्णांक *alloc_synth_tracepoपूर्णांक(अक्षर *name)
अणु
	काष्ठा tracepoपूर्णांक *tp;

	tp = kzalloc(माप(*tp), GFP_KERNEL);
	अगर (!tp)
		वापस ERR_PTR(-ENOMEM);

	tp->name = kstrdup(name, GFP_KERNEL);
	अगर (!tp->name) अणु
		kमुक्त(tp);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस tp;
पूर्ण

काष्ठा synth_event *find_synth_event(स्थिर अक्षर *name)
अणु
	काष्ठा dyn_event *pos;
	काष्ठा synth_event *event;

	क्रम_each_dyn_event(pos) अणु
		अगर (!is_synth_event(pos))
			जारी;
		event = to_synth_event(pos);
		अगर (म_भेद(event->name, name) == 0)
			वापस event;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा trace_event_fields synth_event_fields_array[] = अणु
	अणु .type = TRACE_FUNCTION_TYPE,
	  .define_fields = synth_event_define_fields पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक रेजिस्टर_synth_event(काष्ठा synth_event *event)
अणु
	काष्ठा trace_event_call *call = &event->call;
	पूर्णांक ret = 0;

	event->call.class = &event->class;
	event->class.प्रणाली = kstrdup(SYNTH_SYSTEM, GFP_KERNEL);
	अगर (!event->class.प्रणाली) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	event->tp = alloc_synth_tracepoपूर्णांक(event->name);
	अगर (IS_ERR(event->tp)) अणु
		ret = PTR_ERR(event->tp);
		event->tp = शून्य;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&call->class->fields);
	call->event.funcs = &synth_event_funcs;
	call->class->fields_array = synth_event_fields_array;

	ret = रेजिस्टर_trace_event(&call->event);
	अगर (!ret) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	call->flags = TRACE_EVENT_FL_TRACEPOINT;
	call->class->reg = trace_event_reg;
	call->class->probe = trace_event_raw_event_synth;
	call->data = event;
	call->tp = event->tp;

	ret = trace_add_event_call(call);
	अगर (ret) अणु
		pr_warn("Failed to register synthetic event: %s\n",
			trace_event_name(call));
		जाओ err;
	पूर्ण

	ret = set_synth_event_prपूर्णांक_fmt(call);
	अगर (ret < 0) अणु
		trace_हटाओ_event_call(call);
		जाओ err;
	पूर्ण
 out:
	वापस ret;
 err:
	unरेजिस्टर_trace_event(&call->event);
	जाओ out;
पूर्ण

अटल पूर्णांक unरेजिस्टर_synth_event(काष्ठा synth_event *event)
अणु
	काष्ठा trace_event_call *call = &event->call;
	पूर्णांक ret;

	ret = trace_हटाओ_event_call(call);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_synth_event(काष्ठा synth_event *event)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!event)
		वापस;

	क्रम (i = 0; i < event->n_fields; i++)
		मुक्त_synth_field(event->fields[i]);

	kमुक्त(event->fields);
	kमुक्त(event->dynamic_fields);
	kमुक्त(event->name);
	kमुक्त(event->class.प्रणाली);
	मुक्त_synth_tracepoपूर्णांक(event->tp);
	मुक्त_synth_event_prपूर्णांक_fmt(&event->call);
	kमुक्त(event);
पूर्ण

अटल काष्ठा synth_event *alloc_synth_event(स्थिर अक्षर *name, पूर्णांक n_fields,
					     काष्ठा synth_field **fields)
अणु
	अचिन्हित पूर्णांक i, j, n_dynamic_fields = 0;
	काष्ठा synth_event *event;

	event = kzalloc(माप(*event), GFP_KERNEL);
	अगर (!event) अणु
		event = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	event->name = kstrdup(name, GFP_KERNEL);
	अगर (!event->name) अणु
		kमुक्त(event);
		event = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	event->fields = kसुस्मृति(n_fields, माप(*event->fields), GFP_KERNEL);
	अगर (!event->fields) अणु
		मुक्त_synth_event(event);
		event = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < n_fields; i++)
		अगर (fields[i]->is_dynamic)
			n_dynamic_fields++;

	अगर (n_dynamic_fields) अणु
		event->dynamic_fields = kसुस्मृति(n_dynamic_fields,
						माप(*event->dynamic_fields),
						GFP_KERNEL);
		अगर (!event->dynamic_fields) अणु
			मुक्त_synth_event(event);
			event = ERR_PTR(-ENOMEM);
			जाओ out;
		पूर्ण
	पूर्ण

	dyn_event_init(&event->devent, &synth_event_ops);

	क्रम (i = 0, j = 0; i < n_fields; i++) अणु
		event->fields[i] = fields[i];

		अगर (fields[i]->is_dynamic) अणु
			event->dynamic_fields[j] = fields[i];
			event->dynamic_fields[j]->field_pos = i;
			event->dynamic_fields[j++] = fields[i];
			event->n_dynamic_fields++;
		पूर्ण
	पूर्ण
	event->n_fields = n_fields;
 out:
	वापस event;
पूर्ण

अटल पूर्णांक synth_event_check_arg_fn(व्योम *data)
अणु
	काष्ठा dynevent_arg_pair *arg_pair = data;
	पूर्णांक size;

	size = synth_field_size((अक्षर *)arg_pair->lhs);
	अगर (size == 0) अणु
		अगर (म_माला((अक्षर *)arg_pair->lhs, "["))
			वापस 0;
	पूर्ण

	वापस size ? 0 : -EINVAL;
पूर्ण

/**
 * synth_event_add_field - Add a new field to a synthetic event cmd
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @type: The type of the new field to add
 * @name: The name of the new field to add
 *
 * Add a new field to a synthetic event cmd object.  Field ordering is in
 * the same order the fields are added.
 *
 * See synth_field_size() क्रम available types. If field_name contains
 * [n] the field is considered to be an array.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक synth_event_add_field(काष्ठा dynevent_cmd *cmd, स्थिर अक्षर *type,
			  स्थिर अक्षर *name)
अणु
	काष्ठा dynevent_arg_pair arg_pair;
	पूर्णांक ret;

	अगर (cmd->type != DYNEVENT_TYPE_SYNTH)
		वापस -EINVAL;

	अगर (!type || !name)
		वापस -EINVAL;

	dynevent_arg_pair_init(&arg_pair, 0, ';');

	arg_pair.lhs = type;
	arg_pair.rhs = name;

	ret = dynevent_arg_pair_add(cmd, &arg_pair, synth_event_check_arg_fn);
	अगर (ret)
		वापस ret;

	अगर (++cmd->n_fields > SYNTH_FIELDS_MAX)
		ret = -EINVAL;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_add_field);

/**
 * synth_event_add_field_str - Add a new field to a synthetic event cmd
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @type_name: The type and name of the new field to add, as a single string
 *
 * Add a new field to a synthetic event cmd object, as a single
 * string.  The @type_name string is expected to be of the क्रमm 'type
 * name', which will be appended by ';'.  No sanity checking is करोne -
 * what's passed in is assumed to alपढ़ोy be well-क्रमmed.  Field
 * ordering is in the same order the fields are added.
 *
 * See synth_field_size() क्रम available types. If field_name contains
 * [n] the field is considered to be an array.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक synth_event_add_field_str(काष्ठा dynevent_cmd *cmd, स्थिर अक्षर *type_name)
अणु
	काष्ठा dynevent_arg arg;
	पूर्णांक ret;

	अगर (cmd->type != DYNEVENT_TYPE_SYNTH)
		वापस -EINVAL;

	अगर (!type_name)
		वापस -EINVAL;

	dynevent_arg_init(&arg, ';');

	arg.str = type_name;

	ret = dynevent_arg_add(cmd, &arg, शून्य);
	अगर (ret)
		वापस ret;

	अगर (++cmd->n_fields > SYNTH_FIELDS_MAX)
		ret = -EINVAL;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_add_field_str);

/**
 * synth_event_add_fields - Add multiple fields to a synthetic event cmd
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @fields: An array of type/name field descriptions
 * @n_fields: The number of field descriptions contained in the fields array
 *
 * Add a new set of fields to a synthetic event cmd object.  The event
 * fields that will be defined क्रम the event should be passed in as an
 * array of काष्ठा synth_field_desc, and the number of elements in the
 * array passed in as n_fields.  Field ordering will retain the
 * ordering given in the fields array.
 *
 * See synth_field_size() क्रम available types. If field_name contains
 * [n] the field is considered to be an array.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक synth_event_add_fields(काष्ठा dynevent_cmd *cmd,
			   काष्ठा synth_field_desc *fields,
			   अचिन्हित पूर्णांक n_fields)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < n_fields; i++) अणु
		अगर (fields[i].type == शून्य || fields[i].name == शून्य) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = synth_event_add_field(cmd, fields[i].type, fields[i].name);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_add_fields);

/**
 * __synth_event_gen_cmd_start - Start a synthetic event command from arg list
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @name: The name of the synthetic event
 * @mod: The module creating the event, शून्य अगर not created from a module
 * @args: Variable number of arg (pairs), one pair क्रम each field
 *
 * NOTE: Users normally won't want to call this function directly, but
 * rather use the synth_event_gen_cmd_start() wrapper, which
 * स्वतःmatically adds a शून्य to the end of the arg list.  If this
 * function is used directly, make sure the last arg in the variable
 * arg list is शून्य.
 *
 * Generate a synthetic event command to be executed by
 * synth_event_gen_cmd_end().  This function can be used to generate
 * the complete command or only the first part of it; in the latter
 * हाल, synth_event_add_field(), synth_event_add_field_str(), or
 * synth_event_add_fields() can be used to add more fields following
 * this.
 *
 * There should be an even number variable args, each pair consisting
 * of a type followed by a field name.
 *
 * See synth_field_size() क्रम available types. If field_name contains
 * [n] the field is considered to be an array.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक __synth_event_gen_cmd_start(काष्ठा dynevent_cmd *cmd, स्थिर अक्षर *name,
				काष्ठा module *mod, ...)
अणु
	काष्ठा dynevent_arg arg;
	बहु_सूची args;
	पूर्णांक ret;

	cmd->event_name = name;
	cmd->निजी_data = mod;

	अगर (cmd->type != DYNEVENT_TYPE_SYNTH)
		वापस -EINVAL;

	dynevent_arg_init(&arg, 0);
	arg.str = name;
	ret = dynevent_arg_add(cmd, &arg, शून्य);
	अगर (ret)
		वापस ret;

	बहु_शुरू(args, mod);
	क्रम (;;) अणु
		स्थिर अक्षर *type, *name;

		type = बहु_तर्क(args, स्थिर अक्षर *);
		अगर (!type)
			अवरोध;
		name = बहु_तर्क(args, स्थिर अक्षर *);
		अगर (!name)
			अवरोध;

		अगर (++cmd->n_fields > SYNTH_FIELDS_MAX) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = synth_event_add_field(cmd, type, name);
		अगर (ret)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(args);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__synth_event_gen_cmd_start);

/**
 * synth_event_gen_cmd_array_start - Start synthetic event command from an array
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @name: The name of the synthetic event
 * @fields: An array of type/name field descriptions
 * @n_fields: The number of field descriptions contained in the fields array
 *
 * Generate a synthetic event command to be executed by
 * synth_event_gen_cmd_end().  This function can be used to generate
 * the complete command or only the first part of it; in the latter
 * हाल, synth_event_add_field(), synth_event_add_field_str(), or
 * synth_event_add_fields() can be used to add more fields following
 * this.
 *
 * The event fields that will be defined क्रम the event should be
 * passed in as an array of काष्ठा synth_field_desc, and the number of
 * elements in the array passed in as n_fields.  Field ordering will
 * retain the ordering given in the fields array.
 *
 * See synth_field_size() क्रम available types. If field_name contains
 * [n] the field is considered to be an array.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक synth_event_gen_cmd_array_start(काष्ठा dynevent_cmd *cmd, स्थिर अक्षर *name,
				    काष्ठा module *mod,
				    काष्ठा synth_field_desc *fields,
				    अचिन्हित पूर्णांक n_fields)
अणु
	काष्ठा dynevent_arg arg;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	cmd->event_name = name;
	cmd->निजी_data = mod;

	अगर (cmd->type != DYNEVENT_TYPE_SYNTH)
		वापस -EINVAL;

	अगर (n_fields > SYNTH_FIELDS_MAX)
		वापस -EINVAL;

	dynevent_arg_init(&arg, 0);
	arg.str = name;
	ret = dynevent_arg_add(cmd, &arg, शून्य);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < n_fields; i++) अणु
		अगर (fields[i].type == शून्य || fields[i].name == शून्य)
			वापस -EINVAL;

		ret = synth_event_add_field(cmd, fields[i].type, fields[i].name);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_gen_cmd_array_start);

अटल पूर्णांक __create_synth_event(स्थिर अक्षर *name, स्थिर अक्षर *raw_fields)
अणु
	अक्षर **argv, *field_str, *पंचांगp_fields, *saved_fields = शून्य;
	काष्ठा synth_field *field, *fields[SYNTH_FIELDS_MAX];
	पूर्णांक consumed, cmd_version = 1, n_fields_this_loop;
	पूर्णांक i, argc, n_fields = 0, ret = 0;
	काष्ठा synth_event *event = शून्य;

	/*
	 * Argument syntax:
	 *  - Add synthetic event: <event_name> field[;field] ...
	 *  - Remove synthetic event: !<event_name> field[;field] ...
	 *      where 'field' = type field_name
	 */

	अगर (name[0] == '\0') अणु
		synth_err(SYNTH_ERR_INVALID_CMD, 0);
		वापस -EINVAL;
	पूर्ण

	अगर (!is_good_name(name)) अणु
		synth_err(SYNTH_ERR_BAD_NAME, errpos(name));
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&event_mutex);

	event = find_synth_event(name);
	अगर (event) अणु
		synth_err(SYNTH_ERR_EVENT_EXISTS, errpos(name));
		ret = -EEXIST;
		जाओ err;
	पूर्ण

	पंचांगp_fields = saved_fields = kstrdup(raw_fields, GFP_KERNEL);
	अगर (!पंचांगp_fields) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	जबतक ((field_str = strsep(&पंचांगp_fields, ";")) != शून्य) अणु
		argv = argv_split(GFP_KERNEL, field_str, &argc);
		अगर (!argv) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		अगर (!argc) अणु
			argv_मुक्त(argv);
			जारी;
		पूर्ण

		n_fields_this_loop = 0;
		consumed = 0;
		जबतक (argc > consumed) अणु
			पूर्णांक field_version;

			field = parse_synth_field(argc - consumed,
						  argv + consumed, &consumed,
						  &field_version);
			अगर (IS_ERR(field)) अणु
				argv_मुक्त(argv);
				ret = PTR_ERR(field);
				जाओ err;
			पूर्ण

			/*
			 * Track the highest version of any field we
			 * found in the command.
			 */
			अगर (field_version > cmd_version)
				cmd_version = field_version;

			/*
			 * Now sort out what is and isn't valid क्रम
			 * each supported version.
			 *
			 * If we see more than 1 field per loop, it
			 * means we have multiple fields between
			 * semicolons, and that's something we no
			 * दीर्घer support in a version 2 or greater
			 * command.
			 */
			अगर (cmd_version > 1 && n_fields_this_loop >= 1) अणु
				synth_err(SYNTH_ERR_INVALID_CMD, errpos(field_str));
				ret = -EINVAL;
				जाओ err;
			पूर्ण

			fields[n_fields++] = field;
			अगर (n_fields == SYNTH_FIELDS_MAX) अणु
				synth_err(SYNTH_ERR_TOO_MANY_FIELDS, 0);
				ret = -EINVAL;
				जाओ err;
			पूर्ण

			n_fields_this_loop++;
		पूर्ण

		अगर (consumed < argc) अणु
			synth_err(SYNTH_ERR_INVALID_CMD, 0);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		argv_मुक्त(argv);
	पूर्ण

	अगर (n_fields == 0) अणु
		synth_err(SYNTH_ERR_INVALID_CMD, 0);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	event = alloc_synth_event(name, n_fields, fields);
	अगर (IS_ERR(event)) अणु
		ret = PTR_ERR(event);
		event = शून्य;
		जाओ err;
	पूर्ण
	ret = रेजिस्टर_synth_event(event);
	अगर (!ret)
		dyn_event_add(&event->devent);
	अन्यथा
		मुक्त_synth_event(event);
 out:
	mutex_unlock(&event_mutex);

	kमुक्त(saved_fields);

	वापस ret;
 err:
	क्रम (i = 0; i < n_fields; i++)
		मुक्त_synth_field(fields[i]);

	जाओ out;
पूर्ण

/**
 * synth_event_create - Create a new synthetic event
 * @name: The name of the new synthetic event
 * @fields: An array of type/name field descriptions
 * @n_fields: The number of field descriptions contained in the fields array
 * @mod: The module creating the event, शून्य अगर not created from a module
 *
 * Create a new synthetic event with the given name under the
 * trace/events/synthetic/ directory.  The event fields that will be
 * defined क्रम the event should be passed in as an array of काष्ठा
 * synth_field_desc, and the number elements in the array passed in as
 * n_fields. Field ordering will retain the ordering given in the
 * fields array.
 *
 * If the new synthetic event is being created from a module, the mod
 * param must be non-शून्य.  This will ensure that the trace buffer
 * won't contain unपढ़ोable events.
 *
 * The new synth event should be deleted using synth_event_delete()
 * function.  The new synthetic event can be generated from modules or
 * other kernel code using trace_synth_event() and related functions.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक synth_event_create(स्थिर अक्षर *name, काष्ठा synth_field_desc *fields,
		       अचिन्हित पूर्णांक n_fields, काष्ठा module *mod)
अणु
	काष्ठा dynevent_cmd cmd;
	अक्षर *buf;
	पूर्णांक ret;

	buf = kzalloc(MAX_DYNEVENT_CMD_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	synth_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_LEN);

	ret = synth_event_gen_cmd_array_start(&cmd, name, mod,
					      fields, n_fields);
	अगर (ret)
		जाओ out;

	ret = synth_event_gen_cmd_end(&cmd);
 out:
	kमुक्त(buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_create);

अटल पूर्णांक destroy_synth_event(काष्ठा synth_event *se)
अणु
	पूर्णांक ret;

	अगर (se->ref)
		ret = -EBUSY;
	अन्यथा अणु
		ret = unरेजिस्टर_synth_event(se);
		अगर (!ret) अणु
			dyn_event_हटाओ(&se->devent);
			मुक्त_synth_event(se);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * synth_event_delete - Delete a synthetic event
 * @event_name: The name of the new synthetic event
 *
 * Delete a synthetic event that was created with synth_event_create().
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक synth_event_delete(स्थिर अक्षर *event_name)
अणु
	काष्ठा synth_event *se = शून्य;
	काष्ठा module *mod = शून्य;
	पूर्णांक ret = -ENOENT;

	mutex_lock(&event_mutex);
	se = find_synth_event(event_name);
	अगर (se) अणु
		mod = se->mod;
		ret = destroy_synth_event(se);
	पूर्ण
	mutex_unlock(&event_mutex);

	अगर (mod) अणु
		mutex_lock(&trace_types_lock);
		/*
		 * It is safest to reset the ring buffer अगर the module
		 * being unloaded रेजिस्टरed any events that were
		 * used. The only worry is अगर a new module माला_लो
		 * loaded, and takes on the same id as the events of
		 * this module. When prपूर्णांकing out the buffer, traced
		 * events left over from this module may be passed to
		 * the new module events and unexpected results may
		 * occur.
		 */
		tracing_reset_all_online_cpus();
		mutex_unlock(&trace_types_lock);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_delete);

अटल पूर्णांक check_command(स्थिर अक्षर *raw_command)
अणु
	अक्षर **argv = शून्य, *cmd, *saved_cmd, *name_and_field;
	पूर्णांक argc, ret = 0;

	cmd = saved_cmd = kstrdup(raw_command, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	name_and_field = strsep(&cmd, ";");
	अगर (!name_and_field) अणु
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	अगर (name_and_field[0] == '!')
		जाओ मुक्त;

	argv = argv_split(GFP_KERNEL, name_and_field, &argc);
	अगर (!argv) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण
	argv_मुक्त(argv);

	अगर (argc < 3)
		ret = -EINVAL;
मुक्त:
	kमुक्त(saved_cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक create_or_delete_synth_event(स्थिर अक्षर *raw_command)
अणु
	अक्षर *name = शून्य, *fields, *p;
	पूर्णांक ret = 0;

	raw_command = skip_spaces(raw_command);
	अगर (raw_command[0] == '\0')
		वापस ret;

	last_cmd_set(raw_command);

	ret = check_command(raw_command);
	अगर (ret) अणु
		synth_err(SYNTH_ERR_INVALID_CMD, 0);
		वापस ret;
	पूर्ण

	p = strpbrk(raw_command, " \t");
	अगर (!p && raw_command[0] != '!') अणु
		synth_err(SYNTH_ERR_INVALID_CMD, 0);
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	name = kmemdup_nul(raw_command, p ? p - raw_command : म_माप(raw_command), GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	अगर (name[0] == '!') अणु
		ret = synth_event_delete(name + 1);
		जाओ मुक्त;
	पूर्ण

	fields = skip_spaces(p);

	ret = __create_synth_event(name, fields);
मुक्त:
	kमुक्त(name);

	वापस ret;
पूर्ण

अटल पूर्णांक synth_event_run_command(काष्ठा dynevent_cmd *cmd)
अणु
	काष्ठा synth_event *se;
	पूर्णांक ret;

	ret = create_or_delete_synth_event(cmd->seq.buffer);
	अगर (ret)
		वापस ret;

	se = find_synth_event(cmd->event_name);
	अगर (WARN_ON(!se))
		वापस -ENOENT;

	se->mod = cmd->निजी_data;

	वापस ret;
पूर्ण

/**
 * synth_event_cmd_init - Initialize a synthetic event command object
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @buf: A poपूर्णांकer to the buffer used to build the command
 * @maxlen: The length of the buffer passed in @buf
 *
 * Initialize a synthetic event command object.  Use this beक्रमe
 * calling any of the other dyenvent_cmd functions.
 */
व्योम synth_event_cmd_init(काष्ठा dynevent_cmd *cmd, अक्षर *buf, पूर्णांक maxlen)
अणु
	dynevent_cmd_init(cmd, buf, maxlen, DYNEVENT_TYPE_SYNTH,
			  synth_event_run_command);
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_cmd_init);

अटल अंतरभूत पूर्णांक
__synth_event_trace_init(काष्ठा trace_event_file *file,
			 काष्ठा synth_event_trace_state *trace_state)
अणु
	पूर्णांक ret = 0;

	स_रखो(trace_state, '\0', माप(*trace_state));

	/*
	 * Normal event tracing करोesn't get called at all unless the
	 * ENABLED bit is set (which attaches the probe thus allowing
	 * this code to be called, etc).  Because this is called
	 * directly by the user, we करोn't have that but we still need
	 * to honor not logging when disabled.  For the iterated
	 * trace हाल, we save the enabled state upon start and just
	 * ignore the following data calls.
	 */
	अगर (!(file->flags & EVENT_खाता_FL_ENABLED) ||
	    trace_trigger_soft_disabled(file)) अणु
		trace_state->disabled = true;
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	trace_state->event = file->event_call->data;
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
__synth_event_trace_start(काष्ठा trace_event_file *file,
			  काष्ठा synth_event_trace_state *trace_state,
			  पूर्णांक dynamic_fields_size)
अणु
	पूर्णांक entry_size, fields_size = 0;
	पूर्णांक ret = 0;

	fields_size = trace_state->event->n_u64 * माप(u64);
	fields_size += dynamic_fields_size;

	/*
	 * Aव्योम ring buffer recursion detection, as this event
	 * is being perक्रमmed within another event.
	 */
	trace_state->buffer = file->tr->array_buffer.buffer;
	ring_buffer_nest_start(trace_state->buffer);

	entry_size = माप(*trace_state->entry) + fields_size;
	trace_state->entry = trace_event_buffer_reserve(&trace_state->fbuffer,
							file,
							entry_size);
	अगर (!trace_state->entry) अणु
		ring_buffer_nest_end(trace_state->buffer);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
__synth_event_trace_end(काष्ठा synth_event_trace_state *trace_state)
अणु
	trace_event_buffer_commit(&trace_state->fbuffer);

	ring_buffer_nest_end(trace_state->buffer);
पूर्ण

/**
 * synth_event_trace - Trace a synthetic event
 * @file: The trace_event_file representing the synthetic event
 * @n_vals: The number of values in vals
 * @args: Variable number of args containing the event values
 *
 * Trace a synthetic event using the values passed in the variable
 * argument list.
 *
 * The argument list should be a list 'n_vals' u64 values.  The number
 * of vals must match the number of field in the synthetic event, and
 * must be in the same order as the synthetic event fields.
 *
 * All vals should be cast to u64, and string vals are just poपूर्णांकers
 * to strings, cast to u64.  Strings will be copied पूर्णांकo space
 * reserved in the event क्रम the string, using these poपूर्णांकers.
 *
 * Return: 0 on success, err otherwise.
 */
पूर्णांक synth_event_trace(काष्ठा trace_event_file *file, अचिन्हित पूर्णांक n_vals, ...)
अणु
	अचिन्हित पूर्णांक i, n_u64, len, data_size = 0;
	काष्ठा synth_event_trace_state state;
	बहु_सूची args;
	पूर्णांक ret;

	ret = __synth_event_trace_init(file, &state);
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			ret = 0; /* just disabled, not really an error */
		वापस ret;
	पूर्ण

	अगर (state.event->n_dynamic_fields) अणु
		बहु_शुरू(args, n_vals);

		क्रम (i = 0; i < state.event->n_fields; i++) अणु
			u64 val = बहु_तर्क(args, u64);

			अगर (state.event->fields[i]->is_string &&
			    state.event->fields[i]->is_dynamic) अणु
				अक्षर *str_val = (अक्षर *)(दीर्घ)val;

				data_size += म_माप(str_val) + 1;
			पूर्ण
		पूर्ण

		बहु_पूर्ण(args);
	पूर्ण

	ret = __synth_event_trace_start(file, &state, data_size);
	अगर (ret)
		वापस ret;

	अगर (n_vals != state.event->n_fields) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	data_size = 0;

	बहु_शुरू(args, n_vals);
	क्रम (i = 0, n_u64 = 0; i < state.event->n_fields; i++) अणु
		u64 val;

		val = बहु_तर्क(args, u64);

		अगर (state.event->fields[i]->is_string) अणु
			अक्षर *str_val = (अक्षर *)(दीर्घ)val;

			len = trace_string(state.entry, state.event, str_val,
					   state.event->fields[i]->is_dynamic,
					   data_size, &n_u64);
			data_size += len; /* only dynamic string increments */
		पूर्ण अन्यथा अणु
			काष्ठा synth_field *field = state.event->fields[i];

			चयन (field->size) अणु
			हाल 1:
				*(u8 *)&state.entry->fields[n_u64] = (u8)val;
				अवरोध;

			हाल 2:
				*(u16 *)&state.entry->fields[n_u64] = (u16)val;
				अवरोध;

			हाल 4:
				*(u32 *)&state.entry->fields[n_u64] = (u32)val;
				अवरोध;

			शेष:
				state.entry->fields[n_u64] = val;
				अवरोध;
			पूर्ण
			n_u64++;
		पूर्ण
	पूर्ण
	बहु_पूर्ण(args);
out:
	__synth_event_trace_end(&state);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_trace);

/**
 * synth_event_trace_array - Trace a synthetic event from an array
 * @file: The trace_event_file representing the synthetic event
 * @vals: Array of values
 * @n_vals: The number of values in vals
 *
 * Trace a synthetic event using the values passed in as 'vals'.
 *
 * The 'vals' array is just an array of 'n_vals' u64.  The number of
 * vals must match the number of field in the synthetic event, and
 * must be in the same order as the synthetic event fields.
 *
 * All vals should be cast to u64, and string vals are just poपूर्णांकers
 * to strings, cast to u64.  Strings will be copied पूर्णांकo space
 * reserved in the event क्रम the string, using these poपूर्णांकers.
 *
 * Return: 0 on success, err otherwise.
 */
पूर्णांक synth_event_trace_array(काष्ठा trace_event_file *file, u64 *vals,
			    अचिन्हित पूर्णांक n_vals)
अणु
	अचिन्हित पूर्णांक i, n_u64, field_pos, len, data_size = 0;
	काष्ठा synth_event_trace_state state;
	अक्षर *str_val;
	पूर्णांक ret;

	ret = __synth_event_trace_init(file, &state);
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			ret = 0; /* just disabled, not really an error */
		वापस ret;
	पूर्ण

	अगर (state.event->n_dynamic_fields) अणु
		क्रम (i = 0; i < state.event->n_dynamic_fields; i++) अणु
			field_pos = state.event->dynamic_fields[i]->field_pos;
			str_val = (अक्षर *)(दीर्घ)vals[field_pos];
			len = म_माप(str_val) + 1;
			data_size += len;
		पूर्ण
	पूर्ण

	ret = __synth_event_trace_start(file, &state, data_size);
	अगर (ret)
		वापस ret;

	अगर (n_vals != state.event->n_fields) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	data_size = 0;

	क्रम (i = 0, n_u64 = 0; i < state.event->n_fields; i++) अणु
		अगर (state.event->fields[i]->is_string) अणु
			अक्षर *str_val = (अक्षर *)(दीर्घ)vals[i];

			len = trace_string(state.entry, state.event, str_val,
					   state.event->fields[i]->is_dynamic,
					   data_size, &n_u64);
			data_size += len; /* only dynamic string increments */
		पूर्ण अन्यथा अणु
			काष्ठा synth_field *field = state.event->fields[i];
			u64 val = vals[i];

			चयन (field->size) अणु
			हाल 1:
				*(u8 *)&state.entry->fields[n_u64] = (u8)val;
				अवरोध;

			हाल 2:
				*(u16 *)&state.entry->fields[n_u64] = (u16)val;
				अवरोध;

			हाल 4:
				*(u32 *)&state.entry->fields[n_u64] = (u32)val;
				अवरोध;

			शेष:
				state.entry->fields[n_u64] = val;
				अवरोध;
			पूर्ण
			n_u64++;
		पूर्ण
	पूर्ण
out:
	__synth_event_trace_end(&state);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_trace_array);

/**
 * synth_event_trace_start - Start piecewise synthetic event trace
 * @file: The trace_event_file representing the synthetic event
 * @trace_state: A poपूर्णांकer to object tracking the piecewise trace state
 *
 * Start the trace of a synthetic event field-by-field rather than all
 * at once.
 *
 * This function 'opens' an event trace, which means space is reserved
 * क्रम the event in the trace buffer, after which the event's
 * inभागidual field values can be set through either
 * synth_event_add_next_val() or synth_event_add_val().
 *
 * A poपूर्णांकer to a trace_state object is passed in, which will keep
 * track of the current event trace state until the event trace is
 * बंदd (and the event finally traced) using
 * synth_event_trace_end().
 *
 * Note that synth_event_trace_end() must be called after all values
 * have been added क्रम each event trace, regardless of whether adding
 * all field values succeeded or not.
 *
 * Note also that क्रम a given event trace, all fields must be added
 * using either synth_event_add_next_val() or synth_event_add_val()
 * but not both together or पूर्णांकerleaved.
 *
 * Return: 0 on success, err otherwise.
 */
पूर्णांक synth_event_trace_start(काष्ठा trace_event_file *file,
			    काष्ठा synth_event_trace_state *trace_state)
अणु
	पूर्णांक ret;

	अगर (!trace_state)
		वापस -EINVAL;

	ret = __synth_event_trace_init(file, trace_state);
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			ret = 0; /* just disabled, not really an error */
		वापस ret;
	पूर्ण

	अगर (trace_state->event->n_dynamic_fields)
		वापस -ENOTSUPP;

	ret = __synth_event_trace_start(file, trace_state, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_trace_start);

अटल पूर्णांक __synth_event_add_val(स्थिर अक्षर *field_name, u64 val,
				 काष्ठा synth_event_trace_state *trace_state)
अणु
	काष्ठा synth_field *field = शून्य;
	काष्ठा synth_trace_event *entry;
	काष्ठा synth_event *event;
	पूर्णांक i, ret = 0;

	अगर (!trace_state) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* can't mix add_next_synth_val() with add_synth_val() */
	अगर (field_name) अणु
		अगर (trace_state->add_next) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		trace_state->add_name = true;
	पूर्ण अन्यथा अणु
		अगर (trace_state->add_name) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		trace_state->add_next = true;
	पूर्ण

	अगर (trace_state->disabled)
		जाओ out;

	event = trace_state->event;
	अगर (trace_state->add_name) अणु
		क्रम (i = 0; i < event->n_fields; i++) अणु
			field = event->fields[i];
			अगर (म_भेद(field->name, field_name) == 0)
				अवरोध;
		पूर्ण
		अगर (!field) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (trace_state->cur_field >= event->n_fields) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		field = event->fields[trace_state->cur_field++];
	पूर्ण

	entry = trace_state->entry;
	अगर (field->is_string) अणु
		अक्षर *str_val = (अक्षर *)(दीर्घ)val;
		अक्षर *str_field;

		अगर (field->is_dynamic) अणु /* add_val can't करो dynamic strings */
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!str_val) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		str_field = (अक्षर *)&entry->fields[field->offset];
		strscpy(str_field, str_val, STR_VAR_LEN_MAX);
	पूर्ण अन्यथा अणु
		चयन (field->size) अणु
		हाल 1:
			*(u8 *)&trace_state->entry->fields[field->offset] = (u8)val;
			अवरोध;

		हाल 2:
			*(u16 *)&trace_state->entry->fields[field->offset] = (u16)val;
			अवरोध;

		हाल 4:
			*(u32 *)&trace_state->entry->fields[field->offset] = (u32)val;
			अवरोध;

		शेष:
			trace_state->entry->fields[field->offset] = val;
			अवरोध;
		पूर्ण
	पूर्ण
 out:
	वापस ret;
पूर्ण

/**
 * synth_event_add_next_val - Add the next field's value to an खोलो synth trace
 * @val: The value to set the next field to
 * @trace_state: A poपूर्णांकer to object tracking the piecewise trace state
 *
 * Set the value of the next field in an event that's been खोलोed by
 * synth_event_trace_start().
 *
 * The val param should be the value cast to u64.  If the value poपूर्णांकs
 * to a string, the val param should be a अक्षर * cast to u64.
 *
 * This function assumes all the fields in an event are to be set one
 * after another - successive calls to this function are made, one क्रम
 * each field, in the order of the fields in the event, until all
 * fields have been set.  If you'd rather set each field inभागidually
 * without regard to ordering, synth_event_add_val() can be used
 * instead.
 *
 * Note however that synth_event_add_next_val() and
 * synth_event_add_val() can't be पूर्णांकermixed क्रम a given event trace -
 * one or the other but not both can be used at the same समय.
 *
 * Note also that synth_event_trace_end() must be called after all
 * values have been added क्रम each event trace, regardless of whether
 * adding all field values succeeded or not.
 *
 * Return: 0 on success, err otherwise.
 */
पूर्णांक synth_event_add_next_val(u64 val,
			     काष्ठा synth_event_trace_state *trace_state)
अणु
	वापस __synth_event_add_val(शून्य, val, trace_state);
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_add_next_val);

/**
 * synth_event_add_val - Add a named field's value to an खोलो synth trace
 * @field_name: The name of the synthetic event field value to set
 * @val: The value to set the next field to
 * @trace_state: A poपूर्णांकer to object tracking the piecewise trace state
 *
 * Set the value of the named field in an event that's been खोलोed by
 * synth_event_trace_start().
 *
 * The val param should be the value cast to u64.  If the value poपूर्णांकs
 * to a string, the val param should be a अक्षर * cast to u64.
 *
 * This function looks up the field name, and अगर found, sets the field
 * to the specअगरied value.  This lookup makes this function more
 * expensive than synth_event_add_next_val(), so use that or the
 * none-piecewise synth_event_trace() instead अगर efficiency is more
 * important.
 *
 * Note however that synth_event_add_next_val() and
 * synth_event_add_val() can't be पूर्णांकermixed क्रम a given event trace -
 * one or the other but not both can be used at the same समय.
 *
 * Note also that synth_event_trace_end() must be called after all
 * values have been added क्रम each event trace, regardless of whether
 * adding all field values succeeded or not.
 *
 * Return: 0 on success, err otherwise.
 */
पूर्णांक synth_event_add_val(स्थिर अक्षर *field_name, u64 val,
			काष्ठा synth_event_trace_state *trace_state)
अणु
	वापस __synth_event_add_val(field_name, val, trace_state);
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_add_val);

/**
 * synth_event_trace_end - End piecewise synthetic event trace
 * @trace_state: A poपूर्णांकer to object tracking the piecewise trace state
 *
 * End the trace of a synthetic event खोलोed by
 * synth_event_trace__start().
 *
 * This function 'closes' an event trace, which basically means that
 * it commits the reserved event and cleans up other loose ends.
 *
 * A poपूर्णांकer to a trace_state object is passed in, which will keep
 * track of the current event trace state खोलोed with
 * synth_event_trace_start().
 *
 * Note that this function must be called after all values have been
 * added क्रम each event trace, regardless of whether adding all field
 * values succeeded or not.
 *
 * Return: 0 on success, err otherwise.
 */
पूर्णांक synth_event_trace_end(काष्ठा synth_event_trace_state *trace_state)
अणु
	अगर (!trace_state)
		वापस -EINVAL;

	__synth_event_trace_end(trace_state);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(synth_event_trace_end);

अटल पूर्णांक create_synth_event(स्थिर अक्षर *raw_command)
अणु
	अक्षर *fields, *p;
	स्थिर अक्षर *name;
	पूर्णांक len, ret = 0;

	raw_command = skip_spaces(raw_command);
	अगर (raw_command[0] == '\0')
		वापस ret;

	last_cmd_set(raw_command);

	p = strpbrk(raw_command, " \t");
	अगर (!p) अणु
		synth_err(SYNTH_ERR_INVALID_CMD, 0);
		वापस -EINVAL;
	पूर्ण

	fields = skip_spaces(p);

	name = raw_command;

	अगर (name[0] != 's' || name[1] != ':')
		वापस -ECANCELED;
	name += 2;

	/* This पूर्णांकerface accepts group name prefix */
	अगर (म_अक्षर(name, '/')) अणु
		len = str_has_prefix(name, SYNTH_SYSTEM "/");
		अगर (len == 0) अणु
			synth_err(SYNTH_ERR_INVALID_DYN_CMD, 0);
			वापस -EINVAL;
		पूर्ण
		name += len;
	पूर्ण

	len = name - raw_command;

	ret = check_command(raw_command + len);
	अगर (ret) अणु
		synth_err(SYNTH_ERR_INVALID_CMD, 0);
		वापस ret;
	पूर्ण

	name = kmemdup_nul(raw_command + len, p - raw_command - len, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	ret = __create_synth_event(name, fields);

	kमुक्त(name);

	वापस ret;
पूर्ण

अटल पूर्णांक synth_event_release(काष्ठा dyn_event *ev)
अणु
	काष्ठा synth_event *event = to_synth_event(ev);
	पूर्णांक ret;

	अगर (event->ref)
		वापस -EBUSY;

	ret = unरेजिस्टर_synth_event(event);
	अगर (ret)
		वापस ret;

	dyn_event_हटाओ(ev);
	मुक्त_synth_event(event);
	वापस 0;
पूर्ण

अटल पूर्णांक __synth_event_show(काष्ठा seq_file *m, काष्ठा synth_event *event)
अणु
	काष्ठा synth_field *field;
	अचिन्हित पूर्णांक i;
	अक्षर *type, *t;

	seq_म_लिखो(m, "%s\t", event->name);

	क्रम (i = 0; i < event->n_fields; i++) अणु
		field = event->fields[i];

		type = field->type;
		t = म_माला(type, "__data_loc");
		अगर (t) अणु /* __data_loc beदीर्घs in क्रमmat but not event desc */
			t += माप("__data_loc");
			type = t;
		पूर्ण

		/* parameter values */
		seq_म_लिखो(m, "%s %s%s", type, field->name,
			   i == event->n_fields - 1 ? "" : "; ");
	पूर्ण

	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

अटल पूर्णांक synth_event_show(काष्ठा seq_file *m, काष्ठा dyn_event *ev)
अणु
	काष्ठा synth_event *event = to_synth_event(ev);

	seq_म_लिखो(m, "s:%s/", event->class.प्रणाली);

	वापस __synth_event_show(m, event);
पूर्ण

अटल पूर्णांक synth_events_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dyn_event *ev = v;

	अगर (!is_synth_event(ev))
		वापस 0;

	वापस __synth_event_show(m, to_synth_event(ev));
पूर्ण

अटल स्थिर काष्ठा seq_operations synth_events_seq_op = अणु
	.start	= dyn_event_seq_start,
	.next	= dyn_event_seq_next,
	.stop	= dyn_event_seq_stop,
	.show	= synth_events_seq_show,
पूर्ण;

अटल पूर्णांक synth_events_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) अणु
		ret = dyn_events_release_all(&synth_event_ops);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस seq_खोलो(file, &synth_events_seq_op);
पूर्ण

अटल sमाप_प्रकार synth_events_ग_लिखो(काष्ठा file *file,
				  स्थिर अक्षर __user *buffer,
				  माप_प्रकार count, loff_t *ppos)
अणु
	वापस trace_parse_run_command(file, buffer, count, ppos,
				       create_or_delete_synth_event);
पूर्ण

अटल स्थिर काष्ठा file_operations synth_events_fops = अणु
	.खोलो           = synth_events_खोलो,
	.ग_लिखो		= synth_events_ग_लिखो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = seq_release,
पूर्ण;

/*
 * Register dynevent at core_initcall. This allows kernel to setup kprobe
 * events in postcore_initcall without tracefs.
 */
अटल __init पूर्णांक trace_events_synth_init_early(व्योम)
अणु
	पूर्णांक err = 0;

	err = dyn_event_रेजिस्टर(&synth_event_ops);
	अगर (err)
		pr_warn("Could not register synth_event_ops\n");

	वापस err;
पूर्ण
core_initcall(trace_events_synth_init_early);

अटल __init पूर्णांक trace_events_synth_init(व्योम)
अणु
	काष्ठा dentry *entry = शून्य;
	पूर्णांक err = 0;
	err = tracing_init_dentry();
	अगर (err)
		जाओ err;

	entry = tracefs_create_file("synthetic_events", 0644, शून्य,
				    शून्य, &synth_events_fops);
	अगर (!entry) अणु
		err = -ENODEV;
		जाओ err;
	पूर्ण

	वापस err;
 err:
	pr_warn("Could not create tracefs 'synthetic_events' entry\n");

	वापस err;
पूर्ण

fs_initcall(trace_events_synth_init);
