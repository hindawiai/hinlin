<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright Linaro, Ltd. 2018
 * (C) Copyright Arm Holdings.  2017
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश <मानककोष.स>
#समावेश <yaml.h>
#समावेश "dtc.h"
#समावेश "srcpos.h"

अक्षर *yaml_error_name[] = अणु
	[YAML_NO_ERROR] = "no error",
	[YAML_MEMORY_ERROR] = "memory error",
	[YAML_READER_ERROR] = "reader error",
	[YAML_SCANNER_ERROR] = "scanner error",
	[YAML_PARSER_ERROR] = "parser error",
	[YAML_COMPOSER_ERROR] = "composer error",
	[YAML_WRITER_ERROR] = "writer error",
	[YAML_EMITTER_ERROR] = "emitter error",
पूर्ण;

#घोषणा yaml_emitter_emit_or_die(emitter, event) (			\
अणु									\
	अगर (!yaml_emitter_emit(emitter, event))				\
		die("yaml '%s': %s in %s, line %i\n",			\
		    yaml_error_name[(emitter)->error], 			\
		    (emitter)->problem, __func__, __LINE__);		\
पूर्ण)

अटल व्योम yaml_propval_पूर्णांक(yaml_emitter_t *emitter, काष्ठा marker *markers, अक्षर *data, अचिन्हित पूर्णांक len, पूर्णांक width)
अणु
	yaml_event_t event;
	व्योम *tag;
	अचिन्हित पूर्णांक off, start_offset = markers->offset;

	चयन(width) अणु
		हाल 1: tag = "!u8"; अवरोध;
		हाल 2: tag = "!u16"; अवरोध;
		हाल 4: tag = "!u32"; अवरोध;
		हाल 8: tag = "!u64"; अवरोध;
		शेष:
			die("Invalid width %i", width);
	पूर्ण
	निश्चित(len % width == 0);

	yaml_sequence_start_event_initialize(&event, शून्य,
		(yaml_अक्षर_t *)tag, width == 4, YAML_FLOW_SEQUENCE_STYLE);
	yaml_emitter_emit_or_die(emitter, &event);

	क्रम (off = 0; off < len; off += width) अणु
		अक्षर buf[32];
		काष्ठा marker *m;
		bool is_phandle = false;

		चयन(width) अणु
		हाल 1:
			प्र_लिखो(buf, "0x%"PRIx8, *(uपूर्णांक8_t*)(data + off));
			अवरोध;
		हाल 2:
			प्र_लिखो(buf, "0x%"PRIx16, dtb_ld16(data + off));
			अवरोध;
		हाल 4:
			प्र_लिखो(buf, "0x%"PRIx32, dtb_ld32(data + off));
			m = markers;
			is_phandle = false;
			क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
				अगर (m->offset == (start_offset + off)) अणु
					is_phandle = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 8:
			प्र_लिखो(buf, "0x%"PRIx64, dtb_ld64(data + off));
			अवरोध;
		पूर्ण

		अगर (is_phandle)
			yaml_scalar_event_initialize(&event, शून्य,
				(yaml_अक्षर_t*)"!phandle", (yaml_अक्षर_t *)buf,
				म_माप(buf), 0, 0, YAML_PLAIN_SCALAR_STYLE);
		अन्यथा
			yaml_scalar_event_initialize(&event, शून्य,
				(yaml_अक्षर_t*)YAML_INT_TAG, (yaml_अक्षर_t *)buf,
				म_माप(buf), 1, 1, YAML_PLAIN_SCALAR_STYLE);
		yaml_emitter_emit_or_die(emitter, &event);
	पूर्ण

	yaml_sequence_end_event_initialize(&event);
	yaml_emitter_emit_or_die(emitter, &event);
पूर्ण

अटल व्योम yaml_propval_string(yaml_emitter_t *emitter, अक्षर *str, पूर्णांक len)
अणु
	yaml_event_t event;
	पूर्णांक i;

	निश्चित(str[len-1] == '\0');

	/* Make sure the entire string is in the lower 7-bit ascii range */
	क्रम (i = 0; i < len; i++)
		निश्चित(isascii(str[i]));

	yaml_scalar_event_initialize(&event, शून्य,
		(yaml_अक्षर_t *)YAML_STR_TAG, (yaml_अक्षर_t*)str,
		len-1, 0, 1, YAML_DOUBLE_QUOTED_SCALAR_STYLE);
	yaml_emitter_emit_or_die(emitter, &event);
पूर्ण

अटल व्योम yaml_propval(yaml_emitter_t *emitter, काष्ठा property *prop)
अणु
	yaml_event_t event;
	अचिन्हित पूर्णांक len = prop->val.len;
	काष्ठा marker *m = prop->val.markers;

	/* Emit the property name */
	yaml_scalar_event_initialize(&event, शून्य,
		(yaml_अक्षर_t *)YAML_STR_TAG, (yaml_अक्षर_t*)prop->name,
		म_माप(prop->name), 1, 1, YAML_PLAIN_SCALAR_STYLE);
	yaml_emitter_emit_or_die(emitter, &event);

	/* Boolean properties are easiest to deal with. Length is zero, so just emit 'true' */
	अगर (len == 0) अणु
		yaml_scalar_event_initialize(&event, शून्य,
			(yaml_अक्षर_t *)YAML_BOOL_TAG,
			(yaml_अक्षर_t*)"true",
			म_माप("true"), 1, 0, YAML_PLAIN_SCALAR_STYLE);
		yaml_emitter_emit_or_die(emitter, &event);
		वापस;
	पूर्ण

	अगर (!m)
		die("No markers present in property '%s' value\n", prop->name);

	yaml_sequence_start_event_initialize(&event, शून्य,
		(yaml_अक्षर_t *)YAML_SEQ_TAG, 1, YAML_FLOW_SEQUENCE_STYLE);
	yaml_emitter_emit_or_die(emitter, &event);

	क्रम_each_marker(m) अणु
		पूर्णांक chunk_len;
		अक्षर *data = &prop->val.val[m->offset];

		अगर (m->type < TYPE_UINT8)
			जारी;

		chunk_len = type_marker_length(m) ? : len;
		निश्चित(chunk_len > 0);
		len -= chunk_len;

		चयन(m->type) अणु
		हाल TYPE_UINT16:
			yaml_propval_पूर्णांक(emitter, m, data, chunk_len, 2);
			अवरोध;
		हाल TYPE_UINT32:
			yaml_propval_पूर्णांक(emitter, m, data, chunk_len, 4);
			अवरोध;
		हाल TYPE_UINT64:
			yaml_propval_पूर्णांक(emitter, m, data, chunk_len, 8);
			अवरोध;
		हाल TYPE_STRING:
			yaml_propval_string(emitter, data, chunk_len);
			अवरोध;
		शेष:
			yaml_propval_पूर्णांक(emitter, m, data, chunk_len, 1);
			अवरोध;
		पूर्ण
	पूर्ण

	yaml_sequence_end_event_initialize(&event);
	yaml_emitter_emit_or_die(emitter, &event);
पूर्ण


अटल व्योम yaml_tree(काष्ठा node *tree, yaml_emitter_t *emitter)
अणु
	काष्ठा property *prop;
	काष्ठा node *child;
	yaml_event_t event;

	अगर (tree->deleted)
		वापस;

	yaml_mapping_start_event_initialize(&event, शून्य,
		(yaml_अक्षर_t *)YAML_MAP_TAG, 1, YAML_ANY_MAPPING_STYLE);
	yaml_emitter_emit_or_die(emitter, &event);

	क्रम_each_property(tree, prop)
		yaml_propval(emitter, prop);

	/* Loop over all the children, emitting them पूर्णांकo the map */
	क्रम_each_child(tree, child) अणु
		yaml_scalar_event_initialize(&event, शून्य,
			(yaml_अक्षर_t *)YAML_STR_TAG, (yaml_अक्षर_t*)child->name,
			म_माप(child->name), 1, 0, YAML_PLAIN_SCALAR_STYLE);
		yaml_emitter_emit_or_die(emitter, &event);
		yaml_tree(child, emitter);
	पूर्ण

	yaml_mapping_end_event_initialize(&event);
	yaml_emitter_emit_or_die(emitter, &event);
पूर्ण

व्योम dt_to_yaml(खाता *f, काष्ठा dt_info *dti)
अणु
	yaml_emitter_t emitter;
	yaml_event_t event;

	yaml_emitter_initialize(&emitter);
	yaml_emitter_set_output_file(&emitter, f);
	yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_करोcument_start_event_initialize(&event, शून्य, शून्य, शून्य, 0);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_sequence_start_event_initialize(&event, शून्य, (yaml_अक्षर_t *)YAML_SEQ_TAG, 1, YAML_ANY_SEQUENCE_STYLE);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_tree(dti->dt, &emitter);

	yaml_sequence_end_event_initialize(&event);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_करोcument_end_event_initialize(&event, 0);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_stream_end_event_initialize(&event);
	yaml_emitter_emit_or_die(&emitter, &event);

	yaml_emitter_delete(&emitter);
पूर्ण
