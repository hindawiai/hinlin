<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CTF writing support via babeltrace.
 *
 * Copyright (C) 2014, Jiri Olsa <jolsa@redhat.com>
 * Copyright (C) 2014, Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <babeltrace/ctf-ग_लिखोr/ग_लिखोr.h>
#समावेश <babeltrace/ctf-ग_लिखोr/घड़ी.h>
#समावेश <babeltrace/ctf-ग_लिखोr/stream.h>
#समावेश <babeltrace/ctf-ग_लिखोr/event.h>
#समावेश <babeltrace/ctf-ग_लिखोr/event-types.h>
#समावेश <babeltrace/ctf-ग_लिखोr/event-fields.h>
#समावेश <babeltrace/ctf-ir/utils.h>
#समावेश <babeltrace/ctf/events.h>
#समावेश <traceevent/event-parse.h>
#समावेश "asm/bug.h"
#समावेश "data-convert.h"
#समावेश "session.h"
#समावेश "debug.h"
#समावेश "tool.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "machine.h"
#समावेश "config.h"
#समावेश <linux/प्रकार.स>
#समावेश <linux/err.h>
#समावेश <linux/समय64.h>
#समावेश "util.h"
#समावेश "clockid.h"

#घोषणा pr_N(n, fmt, ...) \
	eम_लिखो(n, debug_data_convert, fmt, ##__VA_ARGS__)

#घोषणा pr(fmt, ...)  pr_N(1, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr2(fmt, ...) pr_N(2, pr_fmt(fmt), ##__VA_ARGS__)

#घोषणा pr_समय2(t, fmt, ...) pr_समय_N(2, debug_data_convert, t, pr_fmt(fmt), ##__VA_ARGS__)

काष्ठा evsel_priv अणु
	काष्ठा bt_ctf_event_class *event_class;
पूर्ण;

#घोषणा MAX_CPUS	4096

काष्ठा ctf_stream अणु
	काष्ठा bt_ctf_stream *stream;
	पूर्णांक cpu;
	u32 count;
पूर्ण;

काष्ठा ctf_ग_लिखोr अणु
	/* ग_लिखोr primitives */
	काष्ठा bt_ctf_ग_लिखोr		 *ग_लिखोr;
	काष्ठा ctf_stream		**stream;
	पूर्णांक				  stream_cnt;
	काष्ठा bt_ctf_stream_class	 *stream_class;
	काष्ठा bt_ctf_घड़ी		 *घड़ी;

	/* data types */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा bt_ctf_field_type	*s64;
			काष्ठा bt_ctf_field_type	*u64;
			काष्ठा bt_ctf_field_type	*s32;
			काष्ठा bt_ctf_field_type	*u32;
			काष्ठा bt_ctf_field_type	*string;
			काष्ठा bt_ctf_field_type	*u32_hex;
			काष्ठा bt_ctf_field_type	*u64_hex;
		पूर्ण;
		काष्ठा bt_ctf_field_type *array[6];
	पूर्ण data;
	काष्ठा bt_ctf_event_class	*comm_class;
	काष्ठा bt_ctf_event_class	*निकास_class;
	काष्ठा bt_ctf_event_class	*विभाजन_class;
	काष्ठा bt_ctf_event_class	*mmap_class;
	काष्ठा bt_ctf_event_class	*mmap2_class;
पूर्ण;

काष्ठा convert अणु
	काष्ठा perf_tool	tool;
	काष्ठा ctf_ग_लिखोr	ग_लिखोr;

	u64			events_size;
	u64			events_count;
	u64			non_sample_count;

	/* Ordered events configured queue size. */
	u64			queue_size;
पूर्ण;

अटल पूर्णांक value_set(काष्ठा bt_ctf_field_type *type,
		     काष्ठा bt_ctf_event *event,
		     स्थिर अक्षर *name, u64 val)
अणु
	काष्ठा bt_ctf_field *field;
	bool sign = bt_ctf_field_type_पूर्णांकeger_get_चिन्हित(type);
	पूर्णांक ret;

	field = bt_ctf_field_create(type);
	अगर (!field) अणु
		pr_err("failed to create a field %s\n", name);
		वापस -1;
	पूर्ण

	अगर (sign) अणु
		ret = bt_ctf_field_चिन्हित_पूर्णांकeger_set_value(field, val);
		अगर (ret) अणु
			pr_err("failed to set field value %s\n", name);
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = bt_ctf_field_अचिन्हित_पूर्णांकeger_set_value(field, val);
		अगर (ret) अणु
			pr_err("failed to set field value %s\n", name);
			जाओ err;
		पूर्ण
	पूर्ण

	ret = bt_ctf_event_set_payload(event, name, field);
	अगर (ret) अणु
		pr_err("failed to set payload %s\n", name);
		जाओ err;
	पूर्ण

	pr2("  SET [%s = %" PRIu64 "]\n", name, val);

err:
	bt_ctf_field_put(field);
	वापस ret;
पूर्ण

#घोषणा __FUNC_VALUE_SET(_name, _val_type)				\
अटल __maybe_unused पूर्णांक value_set_##_name(काष्ठा ctf_ग_लिखोr *cw,	\
			     काष्ठा bt_ctf_event *event,		\
			     स्थिर अक्षर *name,				\
			     _val_type val)				\
अणु									\
	काष्ठा bt_ctf_field_type *type = cw->data._name;		\
	वापस value_set(type, event, name, (u64) val);			\
पूर्ण

#घोषणा FUNC_VALUE_SET(_name) __FUNC_VALUE_SET(_name, _name)

FUNC_VALUE_SET(s32)
FUNC_VALUE_SET(u32)
FUNC_VALUE_SET(s64)
FUNC_VALUE_SET(u64)
__FUNC_VALUE_SET(u64_hex, u64)

अटल पूर्णांक string_set_value(काष्ठा bt_ctf_field *field, स्थिर अक्षर *string);
अटल __maybe_unused पूर्णांक
value_set_string(काष्ठा ctf_ग_लिखोr *cw, काष्ठा bt_ctf_event *event,
		 स्थिर अक्षर *name, स्थिर अक्षर *string)
अणु
	काष्ठा bt_ctf_field_type *type = cw->data.string;
	काष्ठा bt_ctf_field *field;
	पूर्णांक ret = 0;

	field = bt_ctf_field_create(type);
	अगर (!field) अणु
		pr_err("failed to create a field %s\n", name);
		वापस -1;
	पूर्ण

	ret = string_set_value(field, string);
	अगर (ret) अणु
		pr_err("failed to set value %s\n", name);
		जाओ err_put_field;
	पूर्ण

	ret = bt_ctf_event_set_payload(event, name, field);
	अगर (ret)
		pr_err("failed to set payload %s\n", name);

err_put_field:
	bt_ctf_field_put(field);
	वापस ret;
पूर्ण

अटल काष्ठा bt_ctf_field_type*
get_tracepoपूर्णांक_field_type(काष्ठा ctf_ग_लिखोr *cw, काष्ठा tep_क्रमmat_field *field)
अणु
	अचिन्हित दीर्घ flags = field->flags;

	अगर (flags & TEP_FIELD_IS_STRING)
		वापस cw->data.string;

	अगर (!(flags & TEP_FIELD_IS_SIGNED)) अणु
		/* अचिन्हित दीर्घ are mostly poपूर्णांकers */
		अगर (flags & TEP_FIELD_IS_LONG || flags & TEP_FIELD_IS_POINTER)
			वापस cw->data.u64_hex;
	पूर्ण

	अगर (flags & TEP_FIELD_IS_SIGNED) अणु
		अगर (field->size == 8)
			वापस cw->data.s64;
		अन्यथा
			वापस cw->data.s32;
	पूर्ण

	अगर (field->size == 8)
		वापस cw->data.u64;
	अन्यथा
		वापस cw->data.u32;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ adjust_चिन्हितness(अचिन्हित दीर्घ दीर्घ value_पूर्णांक, पूर्णांक size)
अणु
	अचिन्हित दीर्घ दीर्घ value_mask;

	/*
	 * value_mask = (1 << (size * 8 - 1)) - 1.
	 * Directly set value_mask क्रम code पढ़ोers.
	 */
	चयन (size) अणु
	हाल 1:
		value_mask = 0x7fULL;
		अवरोध;
	हाल 2:
		value_mask = 0x7fffULL;
		अवरोध;
	हाल 4:
		value_mask = 0x7fffffffULL;
		अवरोध;
	हाल 8:
		/*
		 * For 64 bit value, वापस it self. There is no need
		 * to fill high bit.
		 */
		/* Fall through */
	शेष:
		/* BUG! */
		वापस value_पूर्णांक;
	पूर्ण

	/* If it is a positive value, करोn't adjust. */
	अगर ((value_पूर्णांक & (~0ULL - value_mask)) == 0)
		वापस value_पूर्णांक;

	/* Fill upper part of value_पूर्णांक with 1 to make it a negative दीर्घ दीर्घ. */
	वापस (value_पूर्णांक & value_mask) | ~value_mask;
पूर्ण

अटल पूर्णांक string_set_value(काष्ठा bt_ctf_field *field, स्थिर अक्षर *string)
अणु
	अक्षर *buffer = शून्य;
	माप_प्रकार len = म_माप(string), i, p;
	पूर्णांक err;

	क्रम (i = p = 0; i < len; i++, p++) अणु
		अगर (है_छाप(string[i])) अणु
			अगर (!buffer)
				जारी;
			buffer[p] = string[i];
		पूर्ण अन्यथा अणु
			अक्षर numstr[5];

			snम_लिखो(numstr, माप(numstr), "\\x%02x",
				 (अचिन्हित पूर्णांक)(string[i]) & 0xff);

			अगर (!buffer) अणु
				buffer = zalloc(i + (len - i) * 4 + 2);
				अगर (!buffer) अणु
					pr_err("failed to set unprintable string '%s'\n", string);
					वापस bt_ctf_field_string_set_value(field, "UNPRINTABLE-STRING");
				पूर्ण
				अगर (i > 0)
					म_नकलन(buffer, string, i);
			पूर्ण
			स_नकल(buffer + p, numstr, 4);
			p += 3;
		पूर्ण
	पूर्ण

	अगर (!buffer)
		वापस bt_ctf_field_string_set_value(field, string);
	err = bt_ctf_field_string_set_value(field, buffer);
	मुक्त(buffer);
	वापस err;
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_field_value(काष्ठा ctf_ग_लिखोr *cw,
				      काष्ठा bt_ctf_event_class *event_class,
				      काष्ठा bt_ctf_event *event,
				      काष्ठा perf_sample *sample,
				      काष्ठा tep_क्रमmat_field *fmtf)
अणु
	काष्ठा bt_ctf_field_type *type;
	काष्ठा bt_ctf_field *array_field;
	काष्ठा bt_ctf_field *field;
	स्थिर अक्षर *name = fmtf->name;
	व्योम *data = sample->raw_data;
	अचिन्हित दीर्घ flags = fmtf->flags;
	अचिन्हित पूर्णांक n_items;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;

	name = fmtf->alias;
	offset = fmtf->offset;
	len = fmtf->size;
	अगर (flags & TEP_FIELD_IS_STRING)
		flags &= ~TEP_FIELD_IS_ARRAY;

	अगर (flags & TEP_FIELD_IS_DYNAMIC) अणु
		अचिन्हित दीर्घ दीर्घ पंचांगp_val;

		पंचांगp_val = tep_पढ़ो_number(fmtf->event->tep,
					  data + offset, len);
		offset = पंचांगp_val;
		len = offset >> 16;
		offset &= 0xffff;
	पूर्ण

	अगर (flags & TEP_FIELD_IS_ARRAY) अणु

		type = bt_ctf_event_class_get_field_by_name(
				event_class, name);
		array_field = bt_ctf_field_create(type);
		bt_ctf_field_type_put(type);
		अगर (!array_field) अणु
			pr_err("Failed to create array type %s\n", name);
			वापस -1;
		पूर्ण

		len = fmtf->size / fmtf->arraylen;
		n_items = fmtf->arraylen;
	पूर्ण अन्यथा अणु
		n_items = 1;
		array_field = शून्य;
	पूर्ण

	type = get_tracepoपूर्णांक_field_type(cw, fmtf);

	क्रम (i = 0; i < n_items; i++) अणु
		अगर (flags & TEP_FIELD_IS_ARRAY)
			field = bt_ctf_field_array_get_field(array_field, i);
		अन्यथा
			field = bt_ctf_field_create(type);

		अगर (!field) अणु
			pr_err("failed to create a field %s\n", name);
			वापस -1;
		पूर्ण

		अगर (flags & TEP_FIELD_IS_STRING)
			ret = string_set_value(field, data + offset + i * len);
		अन्यथा अणु
			अचिन्हित दीर्घ दीर्घ value_पूर्णांक;

			value_पूर्णांक = tep_पढ़ो_number(
					fmtf->event->tep,
					data + offset + i * len, len);

			अगर (!(flags & TEP_FIELD_IS_SIGNED))
				ret = bt_ctf_field_अचिन्हित_पूर्णांकeger_set_value(
						field, value_पूर्णांक);
			अन्यथा
				ret = bt_ctf_field_चिन्हित_पूर्णांकeger_set_value(
						field, adjust_चिन्हितness(value_पूर्णांक, len));
		पूर्ण

		अगर (ret) अणु
			pr_err("failed to set file value %s\n", name);
			जाओ err_put_field;
		पूर्ण
		अगर (!(flags & TEP_FIELD_IS_ARRAY)) अणु
			ret = bt_ctf_event_set_payload(event, name, field);
			अगर (ret) अणु
				pr_err("failed to set payload %s\n", name);
				जाओ err_put_field;
			पूर्ण
		पूर्ण
		bt_ctf_field_put(field);
	पूर्ण
	अगर (flags & TEP_FIELD_IS_ARRAY) अणु
		ret = bt_ctf_event_set_payload(event, name, array_field);
		अगर (ret) अणु
			pr_err("Failed add payload array %s\n", name);
			वापस -1;
		पूर्ण
		bt_ctf_field_put(array_field);
	पूर्ण
	वापस 0;

err_put_field:
	bt_ctf_field_put(field);
	वापस -1;
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_fields_values(काष्ठा ctf_ग_लिखोr *cw,
					काष्ठा bt_ctf_event_class *event_class,
					काष्ठा bt_ctf_event *event,
					काष्ठा tep_क्रमmat_field *fields,
					काष्ठा perf_sample *sample)
अणु
	काष्ठा tep_क्रमmat_field *field;
	पूर्णांक ret;

	क्रम (field = fields; field; field = field->next) अणु
		ret = add_tracepoपूर्णांक_field_value(cw, event_class, event, sample,
				field);
		अगर (ret)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_values(काष्ठा ctf_ग_लिखोr *cw,
				 काष्ठा bt_ctf_event_class *event_class,
				 काष्ठा bt_ctf_event *event,
				 काष्ठा evsel *evsel,
				 काष्ठा perf_sample *sample)
अणु
	काष्ठा tep_क्रमmat_field *common_fields = evsel->tp_क्रमmat->क्रमmat.common_fields;
	काष्ठा tep_क्रमmat_field *fields        = evsel->tp_क्रमmat->क्रमmat.fields;
	पूर्णांक ret;

	ret = add_tracepoपूर्णांक_fields_values(cw, event_class, event,
					   common_fields, sample);
	अगर (!ret)
		ret = add_tracepoपूर्णांक_fields_values(cw, event_class, event,
						   fields, sample);

	वापस ret;
पूर्ण

अटल पूर्णांक
add_bpf_output_values(काष्ठा bt_ctf_event_class *event_class,
		      काष्ठा bt_ctf_event *event,
		      काष्ठा perf_sample *sample)
अणु
	काष्ठा bt_ctf_field_type *len_type, *seq_type;
	काष्ठा bt_ctf_field *len_field, *seq_field;
	अचिन्हित पूर्णांक raw_size = sample->raw_size;
	अचिन्हित पूर्णांक nr_elements = raw_size / माप(u32);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (nr_elements * माप(u32) != raw_size)
		pr_warning("Incorrect raw_size (%u) in bpf output event, skip %zu bytes\n",
			   raw_size, nr_elements * माप(u32) - raw_size);

	len_type = bt_ctf_event_class_get_field_by_name(event_class, "raw_len");
	len_field = bt_ctf_field_create(len_type);
	अगर (!len_field) अणु
		pr_err("failed to create 'raw_len' for bpf output event\n");
		ret = -1;
		जाओ put_len_type;
	पूर्ण

	ret = bt_ctf_field_अचिन्हित_पूर्णांकeger_set_value(len_field, nr_elements);
	अगर (ret) अणु
		pr_err("failed to set field value for raw_len\n");
		जाओ put_len_field;
	पूर्ण
	ret = bt_ctf_event_set_payload(event, "raw_len", len_field);
	अगर (ret) अणु
		pr_err("failed to set payload to raw_len\n");
		जाओ put_len_field;
	पूर्ण

	seq_type = bt_ctf_event_class_get_field_by_name(event_class, "raw_data");
	seq_field = bt_ctf_field_create(seq_type);
	अगर (!seq_field) अणु
		pr_err("failed to create 'raw_data' for bpf output event\n");
		ret = -1;
		जाओ put_seq_type;
	पूर्ण

	ret = bt_ctf_field_sequence_set_length(seq_field, len_field);
	अगर (ret) अणु
		pr_err("failed to set length of 'raw_data'\n");
		जाओ put_seq_field;
	पूर्ण

	क्रम (i = 0; i < nr_elements; i++) अणु
		काष्ठा bt_ctf_field *elem_field =
			bt_ctf_field_sequence_get_field(seq_field, i);

		ret = bt_ctf_field_अचिन्हित_पूर्णांकeger_set_value(elem_field,
				((u32 *)(sample->raw_data))[i]);

		bt_ctf_field_put(elem_field);
		अगर (ret) अणु
			pr_err("failed to set raw_data[%d]\n", i);
			जाओ put_seq_field;
		पूर्ण
	पूर्ण

	ret = bt_ctf_event_set_payload(event, "raw_data", seq_field);
	अगर (ret)
		pr_err("failed to set payload for raw_data\n");

put_seq_field:
	bt_ctf_field_put(seq_field);
put_seq_type:
	bt_ctf_field_type_put(seq_type);
put_len_field:
	bt_ctf_field_put(len_field);
put_len_type:
	bt_ctf_field_type_put(len_type);
	वापस ret;
पूर्ण

अटल पूर्णांक
add_callchain_output_values(काष्ठा bt_ctf_event_class *event_class,
		      काष्ठा bt_ctf_event *event,
		      काष्ठा ip_callchain *callchain)
अणु
	काष्ठा bt_ctf_field_type *len_type, *seq_type;
	काष्ठा bt_ctf_field *len_field, *seq_field;
	अचिन्हित पूर्णांक nr_elements = callchain->nr;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	len_type = bt_ctf_event_class_get_field_by_name(
			event_class, "perf_callchain_size");
	len_field = bt_ctf_field_create(len_type);
	अगर (!len_field) अणु
		pr_err("failed to create 'perf_callchain_size' for callchain output event\n");
		ret = -1;
		जाओ put_len_type;
	पूर्ण

	ret = bt_ctf_field_अचिन्हित_पूर्णांकeger_set_value(len_field, nr_elements);
	अगर (ret) अणु
		pr_err("failed to set field value for perf_callchain_size\n");
		जाओ put_len_field;
	पूर्ण
	ret = bt_ctf_event_set_payload(event, "perf_callchain_size", len_field);
	अगर (ret) अणु
		pr_err("failed to set payload to perf_callchain_size\n");
		जाओ put_len_field;
	पूर्ण

	seq_type = bt_ctf_event_class_get_field_by_name(
			event_class, "perf_callchain");
	seq_field = bt_ctf_field_create(seq_type);
	अगर (!seq_field) अणु
		pr_err("failed to create 'perf_callchain' for callchain output event\n");
		ret = -1;
		जाओ put_seq_type;
	पूर्ण

	ret = bt_ctf_field_sequence_set_length(seq_field, len_field);
	अगर (ret) अणु
		pr_err("failed to set length of 'perf_callchain'\n");
		जाओ put_seq_field;
	पूर्ण

	क्रम (i = 0; i < nr_elements; i++) अणु
		काष्ठा bt_ctf_field *elem_field =
			bt_ctf_field_sequence_get_field(seq_field, i);

		ret = bt_ctf_field_अचिन्हित_पूर्णांकeger_set_value(elem_field,
				((u64 *)(callchain->ips))[i]);

		bt_ctf_field_put(elem_field);
		अगर (ret) अणु
			pr_err("failed to set callchain[%d]\n", i);
			जाओ put_seq_field;
		पूर्ण
	पूर्ण

	ret = bt_ctf_event_set_payload(event, "perf_callchain", seq_field);
	अगर (ret)
		pr_err("failed to set payload for raw_data\n");

put_seq_field:
	bt_ctf_field_put(seq_field);
put_seq_type:
	bt_ctf_field_type_put(seq_type);
put_len_field:
	bt_ctf_field_put(len_field);
put_len_type:
	bt_ctf_field_type_put(len_type);
	वापस ret;
पूर्ण

अटल पूर्णांक add_generic_values(काष्ठा ctf_ग_लिखोr *cw,
			      काष्ठा bt_ctf_event *event,
			      काष्ठा evsel *evsel,
			      काष्ठा perf_sample *sample)
अणु
	u64 type = evsel->core.attr.sample_type;
	पूर्णांक ret;

	/*
	 * missing:
	 *   PERF_SAMPLE_TIME         - not needed as we have it in
	 *                              ctf event header
	 *   PERF_SAMPLE_READ         - TODO
	 *   PERF_SAMPLE_RAW          - tracepoपूर्णांक fields are handled separately
	 *   PERF_SAMPLE_BRANCH_STACK - TODO
	 *   PERF_SAMPLE_REGS_USER    - TODO
	 *   PERF_SAMPLE_STACK_USER   - TODO
	 */

	अगर (type & PERF_SAMPLE_IP) अणु
		ret = value_set_u64_hex(cw, event, "perf_ip", sample->ip);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (type & PERF_SAMPLE_TID) अणु
		ret = value_set_s32(cw, event, "perf_tid", sample->tid);
		अगर (ret)
			वापस -1;

		ret = value_set_s32(cw, event, "perf_pid", sample->pid);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर ((type & PERF_SAMPLE_ID) ||
	    (type & PERF_SAMPLE_IDENTIFIER)) अणु
		ret = value_set_u64(cw, event, "perf_id", sample->id);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (type & PERF_SAMPLE_STREAM_ID) अणु
		ret = value_set_u64(cw, event, "perf_stream_id", sample->stream_id);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (type & PERF_SAMPLE_PERIOD) अणु
		ret = value_set_u64(cw, event, "perf_period", sample->period);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (type & PERF_SAMPLE_WEIGHT) अणु
		ret = value_set_u64(cw, event, "perf_weight", sample->weight);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (type & PERF_SAMPLE_DATA_SRC) अणु
		ret = value_set_u64(cw, event, "perf_data_src",
				sample->data_src);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (type & PERF_SAMPLE_TRANSACTION) अणु
		ret = value_set_u64(cw, event, "perf_transaction",
				sample->transaction);
		अगर (ret)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ctf_stream__flush(काष्ठा ctf_stream *cs)
अणु
	पूर्णांक err = 0;

	अगर (cs) अणु
		err = bt_ctf_stream_flush(cs->stream);
		अगर (err)
			pr_err("CTF stream %d flush failed\n", cs->cpu);

		pr("Flush stream for cpu %d (%u samples)\n",
		   cs->cpu, cs->count);

		cs->count = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा ctf_stream *ctf_stream__create(काष्ठा ctf_ग_लिखोr *cw, पूर्णांक cpu)
अणु
	काष्ठा ctf_stream *cs;
	काष्ठा bt_ctf_field *pkt_ctx   = शून्य;
	काष्ठा bt_ctf_field *cpu_field = शून्य;
	काष्ठा bt_ctf_stream *stream   = शून्य;
	पूर्णांक ret;

	cs = zalloc(माप(*cs));
	अगर (!cs) अणु
		pr_err("Failed to allocate ctf stream\n");
		वापस शून्य;
	पूर्ण

	stream = bt_ctf_ग_लिखोr_create_stream(cw->ग_लिखोr, cw->stream_class);
	अगर (!stream) अणु
		pr_err("Failed to create CTF stream\n");
		जाओ out;
	पूर्ण

	pkt_ctx = bt_ctf_stream_get_packet_context(stream);
	अगर (!pkt_ctx) अणु
		pr_err("Failed to obtain packet context\n");
		जाओ out;
	पूर्ण

	cpu_field = bt_ctf_field_काष्ठाure_get_field(pkt_ctx, "cpu_id");
	bt_ctf_field_put(pkt_ctx);
	अगर (!cpu_field) अणु
		pr_err("Failed to obtain cpu field\n");
		जाओ out;
	पूर्ण

	ret = bt_ctf_field_अचिन्हित_पूर्णांकeger_set_value(cpu_field, (u32) cpu);
	अगर (ret) अणु
		pr_err("Failed to update CPU number\n");
		जाओ out;
	पूर्ण

	bt_ctf_field_put(cpu_field);

	cs->cpu    = cpu;
	cs->stream = stream;
	वापस cs;

out:
	अगर (cpu_field)
		bt_ctf_field_put(cpu_field);
	अगर (stream)
		bt_ctf_stream_put(stream);

	मुक्त(cs);
	वापस शून्य;
पूर्ण

अटल व्योम ctf_stream__delete(काष्ठा ctf_stream *cs)
अणु
	अगर (cs) अणु
		bt_ctf_stream_put(cs->stream);
		मुक्त(cs);
	पूर्ण
पूर्ण

अटल काष्ठा ctf_stream *ctf_stream(काष्ठा ctf_ग_लिखोr *cw, पूर्णांक cpu)
अणु
	काष्ठा ctf_stream *cs = cw->stream[cpu];

	अगर (!cs) अणु
		cs = ctf_stream__create(cw, cpu);
		cw->stream[cpu] = cs;
	पूर्ण

	वापस cs;
पूर्ण

अटल पूर्णांक get_sample_cpu(काष्ठा ctf_ग_लिखोr *cw, काष्ठा perf_sample *sample,
			  काष्ठा evsel *evsel)
अणु
	पूर्णांक cpu = 0;

	अगर (evsel->core.attr.sample_type & PERF_SAMPLE_CPU)
		cpu = sample->cpu;

	अगर (cpu > cw->stream_cnt) अणु
		pr_err("Event was recorded for CPU %d, limit is at %d.\n",
			cpu, cw->stream_cnt);
		cpu = 0;
	पूर्ण

	वापस cpu;
पूर्ण

#घोषणा STREAM_FLUSH_COUNT 100000

/*
 * Currently we have no other way to determine the
 * समय क्रम the stream flush other than keep track
 * of the number of events and check it against
 * threshold.
 */
अटल bool is_flush_needed(काष्ठा ctf_stream *cs)
अणु
	वापस cs->count >= STREAM_FLUSH_COUNT;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *_event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा convert *c = container_of(tool, काष्ठा convert, tool);
	काष्ठा evsel_priv *priv = evsel->priv;
	काष्ठा ctf_ग_लिखोr *cw = &c->ग_लिखोr;
	काष्ठा ctf_stream *cs;
	काष्ठा bt_ctf_event_class *event_class;
	काष्ठा bt_ctf_event *event;
	पूर्णांक ret;
	अचिन्हित दीर्घ type = evsel->core.attr.sample_type;

	अगर (WARN_ONCE(!priv, "Failed to setup all events.\n"))
		वापस 0;

	event_class = priv->event_class;

	/* update stats */
	c->events_count++;
	c->events_size += _event->header.size;

	pr_समय2(sample->समय, "sample %" PRIu64 "\n", c->events_count);

	event = bt_ctf_event_create(event_class);
	अगर (!event) अणु
		pr_err("Failed to create an CTF event\n");
		वापस -1;
	पूर्ण

	bt_ctf_घड़ी_set_समय(cw->घड़ी, sample->समय);

	ret = add_generic_values(cw, event, evsel, sample);
	अगर (ret)
		वापस -1;

	अगर (evsel->core.attr.type == PERF_TYPE_TRACEPOINT) अणु
		ret = add_tracepoपूर्णांक_values(cw, event_class, event,
					    evsel, sample);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (type & PERF_SAMPLE_CALLCHAIN) अणु
		ret = add_callchain_output_values(event_class,
				event, sample->callchain);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (evsel__is_bpf_output(evsel)) अणु
		ret = add_bpf_output_values(event_class, event, sample);
		अगर (ret)
			वापस -1;
	पूर्ण

	cs = ctf_stream(cw, get_sample_cpu(cw, sample, evsel));
	अगर (cs) अणु
		अगर (is_flush_needed(cs))
			ctf_stream__flush(cs);

		cs->count++;
		bt_ctf_stream_append_event(cs->stream, event);
	पूर्ण

	bt_ctf_event_put(event);
	वापस cs ? 0 : -1;
पूर्ण

#घोषणा __NON_SAMPLE_SET_FIELD(_name, _type, _field) 	\
करो अणु							\
	ret = value_set_##_type(cw, event, #_field, _event->_name._field);\
	अगर (ret)					\
		वापस -1;				\
पूर्ण जबतक(0)

#घोषणा __FUNC_PROCESS_NON_SAMPLE(_name, body) 	\
अटल पूर्णांक process_##_name##_event(काष्ठा perf_tool *tool,	\
				   जोड़ perf_event *_event,	\
				   काष्ठा perf_sample *sample,	\
				   काष्ठा machine *machine)	\
अणु								\
	काष्ठा convert *c = container_of(tool, काष्ठा convert, tool);\
	काष्ठा ctf_ग_लिखोr *cw = &c->ग_लिखोr;			\
	काष्ठा bt_ctf_event_class *event_class = cw->_name##_class;\
	काष्ठा bt_ctf_event *event;				\
	काष्ठा ctf_stream *cs;					\
	पूर्णांक ret;						\
								\
	c->non_sample_count++;					\
	c->events_size += _event->header.size;			\
	event = bt_ctf_event_create(event_class);		\
	अगर (!event) अणु						\
		pr_err("Failed to create an CTF event\n");	\
		वापस -1;					\
	पूर्ण							\
								\
	bt_ctf_घड़ी_set_समय(cw->घड़ी, sample->समय);		\
	body							\
	cs = ctf_stream(cw, 0);					\
	अगर (cs) अणु						\
		अगर (is_flush_needed(cs))			\
			ctf_stream__flush(cs);			\
								\
		cs->count++;					\
		bt_ctf_stream_append_event(cs->stream, event);	\
	पूर्ण							\
	bt_ctf_event_put(event);				\
								\
	वापस perf_event__process_##_name(tool, _event, sample, machine);\
पूर्ण

__FUNC_PROCESS_NON_SAMPLE(comm,
	__NON_SAMPLE_SET_FIELD(comm, u32, pid);
	__NON_SAMPLE_SET_FIELD(comm, u32, tid);
	__NON_SAMPLE_SET_FIELD(comm, string, comm);
)
__FUNC_PROCESS_NON_SAMPLE(विभाजन,
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, pid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, ppid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, tid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, ptid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u64, समय);
)

__FUNC_PROCESS_NON_SAMPLE(निकास,
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, pid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, ppid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, tid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u32, ptid);
	__NON_SAMPLE_SET_FIELD(विभाजन, u64, समय);
)
__FUNC_PROCESS_NON_SAMPLE(mmap,
	__NON_SAMPLE_SET_FIELD(mmap, u32, pid);
	__NON_SAMPLE_SET_FIELD(mmap, u32, tid);
	__NON_SAMPLE_SET_FIELD(mmap, u64_hex, start);
	__NON_SAMPLE_SET_FIELD(mmap, string, filename);
)
__FUNC_PROCESS_NON_SAMPLE(mmap2,
	__NON_SAMPLE_SET_FIELD(mmap2, u32, pid);
	__NON_SAMPLE_SET_FIELD(mmap2, u32, tid);
	__NON_SAMPLE_SET_FIELD(mmap2, u64_hex, start);
	__NON_SAMPLE_SET_FIELD(mmap2, string, filename);
)
#अघोषित __NON_SAMPLE_SET_FIELD
#अघोषित __FUNC_PROCESS_NON_SAMPLE

/* If dup < 0, add a prefix. Else, add _dupl_X suffix. */
अटल अक्षर *change_name(अक्षर *name, अक्षर *orig_name, पूर्णांक dup)
अणु
	अक्षर *new_name = शून्य;
	माप_प्रकार len;

	अगर (!name)
		name = orig_name;

	अगर (dup >= 10)
		जाओ out;
	/*
	 * Add '_' prefix to potential keywork.  According to
	 * Mathieu Desnoyers (https://lore.kernel.org/lkml/1074266107.40857.1422045946295.JavaMail.zimbra@efficios.com),
	 * further CTF spec updating may require us to use '$'.
	 */
	अगर (dup < 0)
		len = म_माप(name) + माप("_");
	अन्यथा
		len = म_माप(orig_name) + माप("_dupl_X");

	new_name = दो_स्मृति(len);
	अगर (!new_name)
		जाओ out;

	अगर (dup < 0)
		snम_लिखो(new_name, len, "_%s", name);
	अन्यथा
		snम_लिखो(new_name, len, "%s_dupl_%d", orig_name, dup);

out:
	अगर (name != orig_name)
		मुक्त(name);
	वापस new_name;
पूर्ण

अटल पूर्णांक event_class_add_field(काष्ठा bt_ctf_event_class *event_class,
		काष्ठा bt_ctf_field_type *type,
		काष्ठा tep_क्रमmat_field *field)
अणु
	काष्ठा bt_ctf_field_type *t = शून्य;
	अक्षर *name;
	पूर्णांक dup = 1;
	पूर्णांक ret;

	/* alias was alपढ़ोy asचिन्हित */
	अगर (field->alias != field->name)
		वापस bt_ctf_event_class_add_field(event_class, type,
				(अक्षर *)field->alias);

	name = field->name;

	/* If 'name' is a keywork, add prefix. */
	अगर (bt_ctf_validate_identअगरier(name))
		name = change_name(name, field->name, -1);

	अगर (!name) अणु
		pr_err("Failed to fix invalid identifier.");
		वापस -1;
	पूर्ण
	जबतक ((t = bt_ctf_event_class_get_field_by_name(event_class, name))) अणु
		bt_ctf_field_type_put(t);
		name = change_name(name, field->name, dup++);
		अगर (!name) अणु
			pr_err("Failed to create dup name for '%s'\n", field->name);
			वापस -1;
		पूर्ण
	पूर्ण

	ret = bt_ctf_event_class_add_field(event_class, type, name);
	अगर (!ret)
		field->alias = name;

	वापस ret;
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_fields_types(काष्ठा ctf_ग_लिखोr *cw,
				       काष्ठा tep_क्रमmat_field *fields,
				       काष्ठा bt_ctf_event_class *event_class)
अणु
	काष्ठा tep_क्रमmat_field *field;
	पूर्णांक ret;

	क्रम (field = fields; field; field = field->next) अणु
		काष्ठा bt_ctf_field_type *type;
		अचिन्हित दीर्घ flags = field->flags;

		pr2("  field '%s'\n", field->name);

		type = get_tracepoपूर्णांक_field_type(cw, field);
		अगर (!type)
			वापस -1;

		/*
		 * A string is an array of अक्षरs. For this we use the string
		 * type and करोn't care that it is an array. What we don't
		 * support is an array of strings.
		 */
		अगर (flags & TEP_FIELD_IS_STRING)
			flags &= ~TEP_FIELD_IS_ARRAY;

		अगर (flags & TEP_FIELD_IS_ARRAY)
			type = bt_ctf_field_type_array_create(type, field->arraylen);

		ret = event_class_add_field(event_class, type, field);

		अगर (flags & TEP_FIELD_IS_ARRAY)
			bt_ctf_field_type_put(type);

		अगर (ret) अणु
			pr_err("Failed to add field '%s': %d\n",
					field->name, ret);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक add_tracepoपूर्णांक_types(काष्ठा ctf_ग_लिखोr *cw,
				काष्ठा evsel *evsel,
				काष्ठा bt_ctf_event_class *class)
अणु
	काष्ठा tep_क्रमmat_field *common_fields = evsel->tp_क्रमmat->क्रमmat.common_fields;
	काष्ठा tep_क्रमmat_field *fields        = evsel->tp_क्रमmat->क्रमmat.fields;
	पूर्णांक ret;

	ret = add_tracepoपूर्णांक_fields_types(cw, common_fields, class);
	अगर (!ret)
		ret = add_tracepoपूर्णांक_fields_types(cw, fields, class);

	वापस ret;
पूर्ण

अटल पूर्णांक add_bpf_output_types(काष्ठा ctf_ग_लिखोr *cw,
				काष्ठा bt_ctf_event_class *class)
अणु
	काष्ठा bt_ctf_field_type *len_type = cw->data.u32;
	काष्ठा bt_ctf_field_type *seq_base_type = cw->data.u32_hex;
	काष्ठा bt_ctf_field_type *seq_type;
	पूर्णांक ret;

	ret = bt_ctf_event_class_add_field(class, len_type, "raw_len");
	अगर (ret)
		वापस ret;

	seq_type = bt_ctf_field_type_sequence_create(seq_base_type, "raw_len");
	अगर (!seq_type)
		वापस -1;

	वापस bt_ctf_event_class_add_field(class, seq_type, "raw_data");
पूर्ण

अटल पूर्णांक add_generic_types(काष्ठा ctf_ग_लिखोr *cw, काष्ठा evsel *evsel,
			     काष्ठा bt_ctf_event_class *event_class)
अणु
	u64 type = evsel->core.attr.sample_type;

	/*
	 * missing:
	 *   PERF_SAMPLE_TIME         - not needed as we have it in
	 *                              ctf event header
	 *   PERF_SAMPLE_READ         - TODO
	 *   PERF_SAMPLE_CALLCHAIN    - TODO
	 *   PERF_SAMPLE_RAW          - tracepoपूर्णांक fields and BPF output
	 *                              are handled separately
	 *   PERF_SAMPLE_BRANCH_STACK - TODO
	 *   PERF_SAMPLE_REGS_USER    - TODO
	 *   PERF_SAMPLE_STACK_USER   - TODO
	 */

#घोषणा ADD_FIELD(cl, t, n)						\
	करो अणु								\
		pr2("  field '%s'\n", n);				\
		अगर (bt_ctf_event_class_add_field(cl, t, n)) अणु		\
			pr_err("Failed to add field '%s';\n", n);	\
			वापस -1;					\
		पूर्ण							\
	पूर्ण जबतक (0)

	अगर (type & PERF_SAMPLE_IP)
		ADD_FIELD(event_class, cw->data.u64_hex, "perf_ip");

	अगर (type & PERF_SAMPLE_TID) अणु
		ADD_FIELD(event_class, cw->data.s32, "perf_tid");
		ADD_FIELD(event_class, cw->data.s32, "perf_pid");
	पूर्ण

	अगर ((type & PERF_SAMPLE_ID) ||
	    (type & PERF_SAMPLE_IDENTIFIER))
		ADD_FIELD(event_class, cw->data.u64, "perf_id");

	अगर (type & PERF_SAMPLE_STREAM_ID)
		ADD_FIELD(event_class, cw->data.u64, "perf_stream_id");

	अगर (type & PERF_SAMPLE_PERIOD)
		ADD_FIELD(event_class, cw->data.u64, "perf_period");

	अगर (type & PERF_SAMPLE_WEIGHT)
		ADD_FIELD(event_class, cw->data.u64, "perf_weight");

	अगर (type & PERF_SAMPLE_DATA_SRC)
		ADD_FIELD(event_class, cw->data.u64, "perf_data_src");

	अगर (type & PERF_SAMPLE_TRANSACTION)
		ADD_FIELD(event_class, cw->data.u64, "perf_transaction");

	अगर (type & PERF_SAMPLE_CALLCHAIN) अणु
		ADD_FIELD(event_class, cw->data.u32, "perf_callchain_size");
		ADD_FIELD(event_class,
			bt_ctf_field_type_sequence_create(
				cw->data.u64_hex, "perf_callchain_size"),
			"perf_callchain");
	पूर्ण

#अघोषित ADD_FIELD
	वापस 0;
पूर्ण

अटल पूर्णांक add_event(काष्ठा ctf_ग_लिखोr *cw, काष्ठा evsel *evsel)
अणु
	काष्ठा bt_ctf_event_class *event_class;
	काष्ठा evsel_priv *priv;
	स्थिर अक्षर *name = evsel__name(evsel);
	पूर्णांक ret;

	pr("Adding event '%s' (type %d)\n", name, evsel->core.attr.type);

	event_class = bt_ctf_event_class_create(name);
	अगर (!event_class)
		वापस -1;

	ret = add_generic_types(cw, evsel, event_class);
	अगर (ret)
		जाओ err;

	अगर (evsel->core.attr.type == PERF_TYPE_TRACEPOINT) अणु
		ret = add_tracepoपूर्णांक_types(cw, evsel, event_class);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (evsel__is_bpf_output(evsel)) अणु
		ret = add_bpf_output_types(cw, event_class);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = bt_ctf_stream_class_add_event_class(cw->stream_class, event_class);
	अगर (ret) अणु
		pr("Failed to add event class into stream.\n");
		जाओ err;
	पूर्ण

	priv = दो_स्मृति(माप(*priv));
	अगर (!priv)
		जाओ err;

	priv->event_class = event_class;
	evsel->priv       = priv;
	वापस 0;

err:
	bt_ctf_event_class_put(event_class);
	pr_err("Failed to add event '%s'.\n", name);
	वापस -1;
पूर्ण

अटल पूर्णांक setup_events(काष्ठा ctf_ग_लिखोr *cw, काष्ठा perf_session *session)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा evsel *evsel;
	पूर्णांक ret;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		ret = add_event(cw, evsel);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा __NON_SAMPLE_ADD_FIELD(t, n)						\
	करो अणु							\
		pr2("  field '%s'\n", #n);			\
		अगर (bt_ctf_event_class_add_field(event_class, cw->data.t, #n)) अणु\
			pr_err("Failed to add field '%s';\n", #n);\
			वापस -1;				\
		पूर्ण						\
	पूर्ण जबतक(0)

#घोषणा __FUNC_ADD_NON_SAMPLE_EVENT_CLASS(_name, body) 		\
अटल पूर्णांक add_##_name##_event(काष्ठा ctf_ग_लिखोr *cw)		\
अणु								\
	काष्ठा bt_ctf_event_class *event_class;			\
	पूर्णांक ret;						\
								\
	pr("Adding "#_name" event\n");				\
	event_class = bt_ctf_event_class_create("perf_" #_name);\
	अगर (!event_class)					\
		वापस -1;					\
	body							\
								\
	ret = bt_ctf_stream_class_add_event_class(cw->stream_class, event_class);\
	अगर (ret) अणु						\
		pr("Failed to add event class '"#_name"' into stream.\n");\
		वापस ret;					\
	पूर्ण							\
								\
	cw->_name##_class = event_class;			\
	bt_ctf_event_class_put(event_class);			\
	वापस 0;						\
पूर्ण

__FUNC_ADD_NON_SAMPLE_EVENT_CLASS(comm,
	__NON_SAMPLE_ADD_FIELD(u32, pid);
	__NON_SAMPLE_ADD_FIELD(u32, tid);
	__NON_SAMPLE_ADD_FIELD(string, comm);
)

__FUNC_ADD_NON_SAMPLE_EVENT_CLASS(विभाजन,
	__NON_SAMPLE_ADD_FIELD(u32, pid);
	__NON_SAMPLE_ADD_FIELD(u32, ppid);
	__NON_SAMPLE_ADD_FIELD(u32, tid);
	__NON_SAMPLE_ADD_FIELD(u32, ptid);
	__NON_SAMPLE_ADD_FIELD(u64, समय);
)

__FUNC_ADD_NON_SAMPLE_EVENT_CLASS(निकास,
	__NON_SAMPLE_ADD_FIELD(u32, pid);
	__NON_SAMPLE_ADD_FIELD(u32, ppid);
	__NON_SAMPLE_ADD_FIELD(u32, tid);
	__NON_SAMPLE_ADD_FIELD(u32, ptid);
	__NON_SAMPLE_ADD_FIELD(u64, समय);
)

__FUNC_ADD_NON_SAMPLE_EVENT_CLASS(mmap,
	__NON_SAMPLE_ADD_FIELD(u32, pid);
	__NON_SAMPLE_ADD_FIELD(u32, tid);
	__NON_SAMPLE_ADD_FIELD(u64_hex, start);
	__NON_SAMPLE_ADD_FIELD(string, filename);
)

__FUNC_ADD_NON_SAMPLE_EVENT_CLASS(mmap2,
	__NON_SAMPLE_ADD_FIELD(u32, pid);
	__NON_SAMPLE_ADD_FIELD(u32, tid);
	__NON_SAMPLE_ADD_FIELD(u64_hex, start);
	__NON_SAMPLE_ADD_FIELD(string, filename);
)
#अघोषित __NON_SAMPLE_ADD_FIELD
#अघोषित __FUNC_ADD_NON_SAMPLE_EVENT_CLASS

अटल पूर्णांक setup_non_sample_events(काष्ठा ctf_ग_लिखोr *cw,
				   काष्ठा perf_session *session __maybe_unused)
अणु
	पूर्णांक ret;

	ret = add_comm_event(cw);
	अगर (ret)
		वापस ret;
	ret = add_निकास_event(cw);
	अगर (ret)
		वापस ret;
	ret = add_विभाजन_event(cw);
	अगर (ret)
		वापस ret;
	ret = add_mmap_event(cw);
	अगर (ret)
		वापस ret;
	ret = add_mmap2_event(cw);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

अटल व्योम cleanup_events(काष्ठा perf_session *session)
अणु
	काष्ठा evlist *evlist = session->evlist;
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		काष्ठा evsel_priv *priv;

		priv = evsel->priv;
		bt_ctf_event_class_put(priv->event_class);
		zमुक्त(&evsel->priv);
	पूर्ण

	evlist__delete(evlist);
	session->evlist = शून्य;
पूर्ण

अटल पूर्णांक setup_streams(काष्ठा ctf_ग_लिखोr *cw, काष्ठा perf_session *session)
अणु
	काष्ठा ctf_stream **stream;
	काष्ठा perf_header *ph = &session->header;
	पूर्णांक ncpus;

	/*
	 * Try to get the number of cpus used in the data file,
	 * अगर not present fallback to the MAX_CPUS.
	 */
	ncpus = ph->env.nr_cpus_avail ?: MAX_CPUS;

	stream = zalloc(माप(*stream) * ncpus);
	अगर (!stream) अणु
		pr_err("Failed to allocate streams.\n");
		वापस -ENOMEM;
	पूर्ण

	cw->stream     = stream;
	cw->stream_cnt = ncpus;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_streams(काष्ठा ctf_ग_लिखोr *cw)
अणु
	पूर्णांक cpu;

	क्रम (cpu = 0; cpu < cw->stream_cnt; cpu++)
		ctf_stream__delete(cw->stream[cpu]);

	zमुक्त(&cw->stream);
पूर्ण

अटल पूर्णांक ctf_ग_लिखोr__setup_env(काष्ठा ctf_ग_लिखोr *cw,
				 काष्ठा perf_session *session)
अणु
	काष्ठा perf_header *header = &session->header;
	काष्ठा bt_ctf_ग_लिखोr *ग_लिखोr = cw->ग_लिखोr;

#घोषणा ADD(__n, __v)							\
करो अणु									\
	अगर (bt_ctf_ग_लिखोr_add_environment_field(ग_लिखोr, __n, __v))	\
		वापस -1;						\
पूर्ण जबतक (0)

	ADD("host",    header->env.hostname);
	ADD("sysname", "Linux");
	ADD("release", header->env.os_release);
	ADD("version", header->env.version);
	ADD("machine", header->env.arch);
	ADD("domain", "kernel");
	ADD("tracer_name", "perf");

#अघोषित ADD
	वापस 0;
पूर्ण

अटल पूर्णांक ctf_ग_लिखोr__setup_घड़ी(काष्ठा ctf_ग_लिखोr *cw,
				   काष्ठा perf_session *session,
				   bool tod)
अणु
	काष्ठा bt_ctf_घड़ी *घड़ी = cw->घड़ी;
	स्थिर अक्षर *desc = "perf clock";
	पूर्णांक64_t offset = 0;

	अगर (tod) अणु
		काष्ठा perf_env *env = &session->header.env;

		अगर (!env->घड़ी.enabled) अणु
			pr_err("Can't provide --tod time, missing clock data. "
			       "Please record with -k/--clockid option.\n");
			वापस -1;
		पूर्ण

		desc   = घड़ीid_name(env->घड़ी.घड़ीid);
		offset = env->घड़ी.tod_ns - env->घड़ी.घड़ीid_ns;
	पूर्ण

#घोषणा SET(__n, __v)				\
करो अणु						\
	अगर (bt_ctf_घड़ी_set_##__n(घड़ी, __v))	\
		वापस -1;			\
पूर्ण जबतक (0)

	SET(frequency,   1000000000);
	SET(offset,      offset);
	SET(description, desc);
	SET(precision,   10);
	SET(is_असलolute, 0);

#अघोषित SET
	वापस 0;
पूर्ण

अटल काष्ठा bt_ctf_field_type *create_पूर्णांक_type(पूर्णांक size, bool sign, bool hex)
अणु
	काष्ठा bt_ctf_field_type *type;

	type = bt_ctf_field_type_पूर्णांकeger_create(size);
	अगर (!type)
		वापस शून्य;

	अगर (sign &&
	    bt_ctf_field_type_पूर्णांकeger_set_चिन्हित(type, 1))
		जाओ err;

	अगर (hex &&
	    bt_ctf_field_type_पूर्णांकeger_set_base(type, BT_CTF_INTEGER_BASE_HEXADECIMAL))
		जाओ err;

#अगर __BYTE_ORDER == __BIG_ENDIAN
	bt_ctf_field_type_set_byte_order(type, BT_CTF_BYTE_ORDER_BIG_ENDIAN);
#अन्यथा
	bt_ctf_field_type_set_byte_order(type, BT_CTF_BYTE_ORDER_LITTLE_ENDIAN);
#पूर्ण_अगर

	pr2("Created type: INTEGER %d-bit %ssigned %s\n",
	    size, sign ? "un" : "", hex ? "hex" : "");
	वापस type;

err:
	bt_ctf_field_type_put(type);
	वापस शून्य;
पूर्ण

अटल व्योम ctf_ग_लिखोr__cleanup_data(काष्ठा ctf_ग_लिखोr *cw)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cw->data.array); i++)
		bt_ctf_field_type_put(cw->data.array[i]);
पूर्ण

अटल पूर्णांक ctf_ग_लिखोr__init_data(काष्ठा ctf_ग_लिखोr *cw)
अणु
#घोषणा CREATE_INT_TYPE(type, size, sign, hex)		\
करो अणु							\
	(type) = create_पूर्णांक_type(size, sign, hex);	\
	अगर (!(type))					\
		जाओ err;				\
पूर्ण जबतक (0)

	CREATE_INT_TYPE(cw->data.s64, 64, true,  false);
	CREATE_INT_TYPE(cw->data.u64, 64, false, false);
	CREATE_INT_TYPE(cw->data.s32, 32, true,  false);
	CREATE_INT_TYPE(cw->data.u32, 32, false, false);
	CREATE_INT_TYPE(cw->data.u32_hex, 32, false, true);
	CREATE_INT_TYPE(cw->data.u64_hex, 64, false, true);

	cw->data.string  = bt_ctf_field_type_string_create();
	अगर (cw->data.string)
		वापस 0;

err:
	ctf_ग_लिखोr__cleanup_data(cw);
	pr_err("Failed to create data types.\n");
	वापस -1;
पूर्ण

अटल व्योम ctf_ग_लिखोr__cleanup(काष्ठा ctf_ग_लिखोr *cw)
अणु
	ctf_ग_लिखोr__cleanup_data(cw);

	bt_ctf_घड़ी_put(cw->घड़ी);
	मुक्त_streams(cw);
	bt_ctf_stream_class_put(cw->stream_class);
	bt_ctf_ग_लिखोr_put(cw->ग_लिखोr);

	/* and शून्य all the poपूर्णांकers */
	स_रखो(cw, 0, माप(*cw));
पूर्ण

अटल पूर्णांक ctf_ग_लिखोr__init(काष्ठा ctf_ग_लिखोr *cw, स्थिर अक्षर *path,
			    काष्ठा perf_session *session, bool tod)
अणु
	काष्ठा bt_ctf_ग_लिखोr		*ग_लिखोr;
	काष्ठा bt_ctf_stream_class	*stream_class;
	काष्ठा bt_ctf_घड़ी		*घड़ी;
	काष्ठा bt_ctf_field_type	*pkt_ctx_type;
	पूर्णांक				ret;

	/* CTF ग_लिखोr */
	ग_लिखोr = bt_ctf_ग_लिखोr_create(path);
	अगर (!ग_लिखोr)
		जाओ err;

	cw->ग_लिखोr = ग_लिखोr;

	/* CTF घड़ी */
	घड़ी = bt_ctf_घड़ी_create("perf_clock");
	अगर (!घड़ी) अणु
		pr("Failed to create CTF clock.\n");
		जाओ err_cleanup;
	पूर्ण

	cw->घड़ी = घड़ी;

	अगर (ctf_ग_लिखोr__setup_घड़ी(cw, session, tod)) अणु
		pr("Failed to setup CTF clock.\n");
		जाओ err_cleanup;
	पूर्ण

	/* CTF stream class */
	stream_class = bt_ctf_stream_class_create("perf_stream");
	अगर (!stream_class) अणु
		pr("Failed to create CTF stream class.\n");
		जाओ err_cleanup;
	पूर्ण

	cw->stream_class = stream_class;

	/* CTF घड़ी stream setup */
	अगर (bt_ctf_stream_class_set_घड़ी(stream_class, घड़ी)) अणु
		pr("Failed to assign CTF clock to stream class.\n");
		जाओ err_cleanup;
	पूर्ण

	अगर (ctf_ग_लिखोr__init_data(cw))
		जाओ err_cleanup;

	/* Add cpu_id क्रम packet context */
	pkt_ctx_type = bt_ctf_stream_class_get_packet_context_type(stream_class);
	अगर (!pkt_ctx_type)
		जाओ err_cleanup;

	ret = bt_ctf_field_type_काष्ठाure_add_field(pkt_ctx_type, cw->data.u32, "cpu_id");
	bt_ctf_field_type_put(pkt_ctx_type);
	अगर (ret)
		जाओ err_cleanup;

	/* CTF घड़ी ग_लिखोr setup */
	अगर (bt_ctf_ग_लिखोr_add_घड़ी(ग_लिखोr, घड़ी)) अणु
		pr("Failed to assign CTF clock to writer.\n");
		जाओ err_cleanup;
	पूर्ण

	वापस 0;

err_cleanup:
	ctf_ग_लिखोr__cleanup(cw);
err:
	pr_err("Failed to setup CTF writer.\n");
	वापस -1;
पूर्ण

अटल पूर्णांक ctf_ग_लिखोr__flush_streams(काष्ठा ctf_ग_लिखोr *cw)
अणु
	पूर्णांक cpu, ret = 0;

	क्रम (cpu = 0; cpu < cw->stream_cnt && !ret; cpu++)
		ret = ctf_stream__flush(cw->stream[cpu]);

	वापस ret;
पूर्ण

अटल पूर्णांक convert__config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	काष्ठा convert *c = cb;

	अगर (!म_भेद(var, "convert.queue-size"))
		वापस perf_config_u64(&c->queue_size, var, value);

	वापस 0;
पूर्ण

पूर्णांक bt_convert__perf2ctf(स्थिर अक्षर *input, स्थिर अक्षर *path,
			 काष्ठा perf_data_convert_opts *opts)
अणु
	काष्ठा perf_session *session;
	काष्ठा perf_data data = अणु
		.path	   = input,
		.mode      = PERF_DATA_MODE_READ,
		.क्रमce     = opts->क्रमce,
	पूर्ण;
	काष्ठा convert c = अणु
		.tool = अणु
			.sample          = process_sample_event,
			.mmap            = perf_event__process_mmap,
			.mmap2           = perf_event__process_mmap2,
			.comm            = perf_event__process_comm,
			.निकास            = perf_event__process_निकास,
			.विभाजन            = perf_event__process_विभाजन,
			.lost            = perf_event__process_lost,
			.tracing_data    = perf_event__process_tracing_data,
			.build_id        = perf_event__process_build_id,
			.namespaces      = perf_event__process_namespaces,
			.ordered_events  = true,
			.ordering_requires_बारtamps = true,
		पूर्ण,
	पूर्ण;
	काष्ठा ctf_ग_लिखोr *cw = &c.ग_लिखोr;
	पूर्णांक err;

	अगर (opts->all) अणु
		c.tool.comm = process_comm_event;
		c.tool.निकास = process_निकास_event;
		c.tool.विभाजन = process_विभाजन_event;
		c.tool.mmap = process_mmap_event;
		c.tool.mmap2 = process_mmap2_event;
	पूर्ण

	err = perf_config(convert__config, &c);
	अगर (err)
		वापस err;

	err = -1;
	/* perf.data session */
	session = perf_session__new(&data, 0, &c.tool);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	/* CTF ग_लिखोr */
	अगर (ctf_ग_लिखोr__init(cw, path, session, opts->tod))
		जाओ मुक्त_session;

	अगर (c.queue_size) अणु
		ordered_events__set_alloc_size(&session->ordered_events,
					       c.queue_size);
	पूर्ण

	/* CTF ग_लिखोr env/घड़ी setup  */
	अगर (ctf_ग_लिखोr__setup_env(cw, session))
		जाओ मुक्त_ग_लिखोr;

	/* CTF events setup */
	अगर (setup_events(cw, session))
		जाओ मुक्त_ग_लिखोr;

	अगर (opts->all && setup_non_sample_events(cw, session))
		जाओ मुक्त_ग_लिखोr;

	अगर (setup_streams(cw, session))
		जाओ मुक्त_ग_लिखोr;

	err = perf_session__process_events(session);
	अगर (!err)
		err = ctf_ग_लिखोr__flush_streams(cw);
	अन्यथा
		pr_err("Error during conversion.\n");

	ख_लिखो(मानक_त्रुटि,
		"[ perf data convert: Converted '%s' into CTF data '%s' ]\n",
		data.path, path);

	ख_लिखो(मानक_त्रुटि,
		"[ perf data convert: Converted and wrote %.3f MB (%" PRIu64 " samples",
		(द्विगुन) c.events_size / 1024.0 / 1024.0,
		c.events_count);

	अगर (!c.non_sample_count)
		ख_लिखो(मानक_त्रुटि, ") ]\n");
	अन्यथा
		ख_लिखो(मानक_त्रुटि, ", %" PRIu64 " non-samples) ]\n", c.non_sample_count);

	cleanup_events(session);
	perf_session__delete(session);
	ctf_ग_लिखोr__cleanup(cw);

	वापस err;

मुक्त_ग_लिखोr:
	ctf_ग_लिखोr__cleanup(cw);
मुक्त_session:
	perf_session__delete(session);
	pr_err("Error during conversion setup.\n");
	वापस err;
पूर्ण
