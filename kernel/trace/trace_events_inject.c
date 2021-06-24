<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_events_inject - trace event injection
 *
 * Copyright (C) 2019 Cong Wang <cwang@twitter.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>

#समावेश "trace.h"

अटल पूर्णांक
trace_inject_entry(काष्ठा trace_event_file *file, व्योम *rec, पूर्णांक len)
अणु
	काष्ठा trace_event_buffer fbuffer;
	पूर्णांक written = 0;
	व्योम *entry;

	rcu_पढ़ो_lock_sched();
	entry = trace_event_buffer_reserve(&fbuffer, file, len);
	अगर (entry) अणु
		स_नकल(entry, rec, len);
		written = len;
		trace_event_buffer_commit(&fbuffer);
	पूर्ण
	rcu_पढ़ो_unlock_sched();

	वापस written;
पूर्ण

अटल पूर्णांक
parse_field(अक्षर *str, काष्ठा trace_event_call *call,
	    काष्ठा ftrace_event_field **pf, u64 *pv)
अणु
	काष्ठा ftrace_event_field *field;
	अक्षर *field_name;
	पूर्णांक s, i = 0;
	पूर्णांक len;
	u64 val;

	अगर (!str[i])
		वापस 0;
	/* First find the field to associate to */
	जबतक (है_खाली(str[i]))
		i++;
	s = i;
	जबतक (है_अक्षर_अंक(str[i]) || str[i] == '_')
		i++;
	len = i - s;
	अगर (!len)
		वापस -EINVAL;

	field_name = kmemdup_nul(str + s, len, GFP_KERNEL);
	अगर (!field_name)
		वापस -ENOMEM;
	field = trace_find_event_field(call, field_name);
	kमुक्त(field_name);
	अगर (!field)
		वापस -ENOENT;

	*pf = field;
	जबतक (है_खाली(str[i]))
		i++;
	अगर (str[i] != '=')
		वापस -EINVAL;
	i++;
	जबतक (है_खाली(str[i]))
		i++;
	s = i;
	अगर (है_अंक(str[i]) || str[i] == '-') अणु
		अक्षर *num, c;
		पूर्णांक ret;

		/* Make sure the field is not a string */
		अगर (is_string_field(field))
			वापस -EINVAL;

		अगर (str[i] == '-')
			i++;

		/* We allow 0xDEADBEEF */
		जबतक (है_अक्षर_अंक(str[i]))
			i++;
		num = str + s;
		c = str[i];
		अगर (c != '\0' && !है_खाली(c))
			वापस -EINVAL;
		str[i] = '\0';
		/* Make sure it is a value */
		अगर (field->is_चिन्हित)
			ret = kम_से_दीर्घl(num, 0, &val);
		अन्यथा
			ret = kम_से_अदीर्घl(num, 0, &val);
		str[i] = c;
		अगर (ret)
			वापस ret;

		*pv = val;
		वापस i;
	पूर्ण अन्यथा अगर (str[i] == '\'' || str[i] == '"') अणु
		अक्षर q = str[i];

		/* Make sure the field is OK क्रम strings */
		अगर (!is_string_field(field))
			वापस -EINVAL;

		क्रम (i++; str[i]; i++) अणु
			अगर (str[i] == '\\' && str[i + 1]) अणु
				i++;
				जारी;
			पूर्ण
			अगर (str[i] == q)
				अवरोध;
		पूर्ण
		अगर (!str[i])
			वापस -EINVAL;

		/* Skip quotes */
		s++;
		len = i - s;
		अगर (len >= MAX_FILTER_STR_VAL)
			वापस -EINVAL;

		*pv = (अचिन्हित दीर्घ)(str + s);
		str[i] = 0;
		/* go past the last quote */
		i++;
		वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक trace_get_entry_size(काष्ठा trace_event_call *call)
अणु
	काष्ठा ftrace_event_field *field;
	काष्ठा list_head *head;
	पूर्णांक size = 0;

	head = trace_get_fields(call);
	list_क्रम_each_entry(field, head, link) अणु
		अगर (field->size + field->offset > size)
			size = field->size + field->offset;
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम *trace_alloc_entry(काष्ठा trace_event_call *call, पूर्णांक *size)
अणु
	पूर्णांक entry_size = trace_get_entry_size(call);
	काष्ठा ftrace_event_field *field;
	काष्ठा list_head *head;
	व्योम *entry = शून्य;

	/* We need an extra '\0' at the end. */
	entry = kzalloc(entry_size + 1, GFP_KERNEL);
	अगर (!entry)
		वापस शून्य;

	head = trace_get_fields(call);
	list_क्रम_each_entry(field, head, link) अणु
		अगर (!is_string_field(field))
			जारी;
		अगर (field->filter_type == FILTER_STATIC_STRING)
			जारी;
		अगर (field->filter_type == FILTER_DYN_STRING) अणु
			u32 *str_item;
			पूर्णांक str_loc = entry_size & 0xffff;

			str_item = (u32 *)(entry + field->offset);
			*str_item = str_loc; /* string length is 0. */
		पूर्ण अन्यथा अणु
			अक्षर **paddr;

			paddr = (अक्षर **)(entry + field->offset);
			*paddr = "";
		पूर्ण
	पूर्ण

	*size = entry_size + 1;
	वापस entry;
पूर्ण

#घोषणा INJECT_STRING "STATIC STRING CAN NOT BE INJECTED"

/* Caller is responsible to मुक्त the *pentry. */
अटल पूर्णांक parse_entry(अक्षर *str, काष्ठा trace_event_call *call, व्योम **pentry)
अणु
	काष्ठा ftrace_event_field *field;
	व्योम *entry = शून्य;
	पूर्णांक entry_size;
	u64 val = 0;
	पूर्णांक len;

	entry = trace_alloc_entry(call, &entry_size);
	*pentry = entry;
	अगर (!entry)
		वापस -ENOMEM;

	tracing_generic_entry_update(entry, call->event.type,
				     tracing_gen_ctx());

	जबतक ((len = parse_field(str, call, &field, &val)) > 0) अणु
		अगर (is_function_field(field))
			वापस -EINVAL;

		अगर (is_string_field(field)) अणु
			अक्षर *addr = (अक्षर *)(अचिन्हित दीर्घ) val;

			अगर (field->filter_type == FILTER_STATIC_STRING) अणु
				strlcpy(entry + field->offset, addr, field->size);
			पूर्ण अन्यथा अगर (field->filter_type == FILTER_DYN_STRING) अणु
				पूर्णांक str_len = म_माप(addr) + 1;
				पूर्णांक str_loc = entry_size & 0xffff;
				u32 *str_item;

				entry_size += str_len;
				*pentry = kपुनः_स्मृति(entry, entry_size, GFP_KERNEL);
				अगर (!*pentry) अणु
					kमुक्त(entry);
					वापस -ENOMEM;
				पूर्ण
				entry = *pentry;

				strlcpy(entry + (entry_size - str_len), addr, str_len);
				str_item = (u32 *)(entry + field->offset);
				*str_item = (str_len << 16) | str_loc;
			पूर्ण अन्यथा अणु
				अक्षर **paddr;

				paddr = (अक्षर **)(entry + field->offset);
				*paddr = INJECT_STRING;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (field->size) अणु
			हाल 1: अणु
				u8 पंचांगp = (u8) val;

				स_नकल(entry + field->offset, &पंचांगp, 1);
				अवरोध;
			पूर्ण
			हाल 2: अणु
				u16 पंचांगp = (u16) val;

				स_नकल(entry + field->offset, &पंचांगp, 2);
				अवरोध;
			पूर्ण
			हाल 4: अणु
				u32 पंचांगp = (u32) val;

				स_नकल(entry + field->offset, &पंचांगp, 4);
				अवरोध;
			पूर्ण
			हाल 8:
				स_नकल(entry + field->offset, &val, 8);
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		str += len;
	पूर्ण

	अगर (len < 0)
		वापस len;

	वापस entry_size;
पूर्ण

अटल sमाप_प्रकार
event_inject_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
		   loff_t *ppos)
अणु
	काष्ठा trace_event_call *call;
	काष्ठा trace_event_file *file;
	पूर्णांक err = -ENODEV, size;
	व्योम *entry = शून्य;
	अक्षर *buf;

	अगर (cnt >= PAGE_SIZE)
		वापस -EINVAL;

	buf = memdup_user_nul(ubuf, cnt);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);
	strim(buf);

	mutex_lock(&event_mutex);
	file = event_file_data(filp);
	अगर (file) अणु
		call = file->event_call;
		size = parse_entry(buf, call, &entry);
		अगर (size < 0)
			err = size;
		अन्यथा
			err = trace_inject_entry(file, entry, size);
	पूर्ण
	mutex_unlock(&event_mutex);

	kमुक्त(entry);
	kमुक्त(buf);

	अगर (err < 0)
		वापस err;

	*ppos += err;
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
event_inject_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
		  loff_t *ppos)
अणु
	वापस -EPERM;
पूर्ण

स्थिर काष्ठा file_operations event_inject_fops = अणु
	.खोलो = tracing_खोलो_generic,
	.पढ़ो = event_inject_पढ़ो,
	.ग_लिखो = event_inject_ग_लिखो,
पूर्ण;
