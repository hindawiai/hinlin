<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_POWERPC_PERF_REQ_GEN_PERF_H_
#घोषणा LINUX_POWERPC_PERF_REQ_GEN_PERF_H_

#समावेश <linux/perf_event.h>
#समावेश <linux/stringअगरy.h>

#अगर_अघोषित REQUEST_खाता
#त्रुटि "REQUEST_FILE must be defined before including"
#पूर्ण_अगर

#अगर_अघोषित NAME_LOWER
#त्रुटि "NAME_LOWER must be defined before including"
#पूर्ण_अगर

#अगर_अघोषित NAME_UPPER
#त्रुटि "NAME_UPPER must be defined before including"
#पूर्ण_अगर

#घोषणा BE_TYPE_b1 __u8
#घोषणा BE_TYPE_b2 __be16
#घोषणा BE_TYPE_b4 __be32
#घोषणा BE_TYPE_b8 __be64

#घोषणा BYTES_TO_BE_TYPE(bytes) \
		BE_TYPE_b##bytes

#घोषणा CAT2_(a, b) a ## b
#घोषणा CAT2(a, b) CAT2_(a, b)
#घोषणा CAT3_(a, b, c) a ## b ## c
#घोषणा CAT3(a, b, c) CAT3_(a, b, c)

/*
 * क्रमागतerate the request values as
 * <NAME_UPPER>_<request name> = <request value>
 */
#घोषणा REQUEST_VALUE__(name_upper, r_name) name_upper ## _ ## r_name
#घोषणा REQUEST_VALUE_(name_upper, r_name) REQUEST_VALUE__(name_upper, r_name)
#घोषणा REQUEST_VALUE(r_name) REQUEST_VALUE_(NAME_UPPER, r_name)

#समावेश "_clear.h"
#घोषणा REQUEST_(r_name, r_value, r_idx_1, r_fields) \
	REQUEST_VALUE(r_name) = r_value,
क्रमागत CAT2(NAME_LOWER, _requests) अणु
#समावेश REQUEST_खाता
पूर्ण;

/*
 * For each request:
 * काष्ठा <NAME_LOWER>_<request name> अणु
 *	r_fields
 * पूर्ण;
 */
#समावेश "_clear.h"
#घोषणा STRUCT_NAME__(name_lower, r_name) name_lower ## _ ## r_name
#घोषणा STRUCT_NAME_(name_lower, r_name) STRUCT_NAME__(name_lower, r_name)
#घोषणा STRUCT_NAME(r_name) STRUCT_NAME_(NAME_LOWER, r_name)
#घोषणा REQUEST_(r_name, r_value, r_idx_1, r_fields)	\
काष्ठा STRUCT_NAME(r_name) अणु				\
	r_fields					\
पूर्ण;
#घोषणा __field_(r_name, r_value, r_idx_1, f_offset, f_bytes, f_name) \
	BYTES_TO_BE_TYPE(f_bytes) f_name;
#घोषणा __count_(r_name, r_value, r_idx_1, f_offset, f_bytes, f_name) \
	__field_(r_name, r_value, r_idx_1, f_offset, f_bytes, f_name)
#घोषणा __array_(r_name, r_value, r_idx_1, a_offset, a_bytes, a_name) \
	__u8 a_name[a_bytes];

#समावेश REQUEST_खाता

/*
 * Generate a check of the field offsets
 * <NAME_LOWER>_निश्चित_offsets_correct()
 */
#समावेश "_clear.h"
#घोषणा REQUEST_(r_name, r_value, index, r_fields)			\
r_fields
#घोषणा __field_(r_name, r_value, r_idx_1, f_offset, f_size, f_name) \
	BUILD_BUG_ON(दुरत्व(काष्ठा STRUCT_NAME(r_name), f_name) != f_offset);
#घोषणा __count_(r_name, r_value, r_idx_1, c_offset, c_size, c_name) \
	__field_(r_name, r_value, r_idx_1, c_offset, c_size, c_name)
#घोषणा __array_(r_name, r_value, r_idx_1, a_offset, a_size, a_name) \
	__field_(r_name, r_value, r_idx_1, a_offset, a_size, a_name)

अटल अंतरभूत व्योम CAT2(NAME_LOWER, _निश्चित_offsets_correct)(व्योम)
अणु
#समावेश REQUEST_खाता
पूर्ण

/*
 * Generate event attributes:
 * PMU_EVENT_ATTR_STRING(<request name>_<field name>,
 *	<NAME_LOWER>_event_attr_<request name>_<field name>,
 *		"request=<request value>"
 *		"starting_index=<starting index type>"
 *		"counter_info_version=CURRENT_COUNTER_INFO_VERSION"
 *		"length=<f_size>"
 *		"offset=<f_offset>")
 *
 *	TODO: counter_info_version may need to vary, we should पूर्णांकerperate the
 *	value to some extent
 */
#घोषणा EVENT_ATTR_NAME__(name, r_name, c_name) \
	name ## _event_attr_ ## r_name ## _ ## c_name
#घोषणा EVENT_ATTR_NAME_(name, r_name, c_name) \
	EVENT_ATTR_NAME__(name, r_name, c_name)
#घोषणा EVENT_ATTR_NAME(r_name, c_name) \
	EVENT_ATTR_NAME_(NAME_LOWER, r_name, c_name)

#समावेश "_clear.h"
#घोषणा __field_(r_name, r_value, r_idx_1, f_offset, f_size, f_name)
#घोषणा __array_(r_name, r_value, r_idx_1, a_offset, a_size, a_name)
#घोषणा __count_(r_name, r_value, r_idx_1, c_offset, c_size, c_name)	\
PMU_EVENT_ATTR_STRING(							\
		CAT3(r_name, _, c_name),				\
		EVENT_ATTR_NAME(r_name, c_name),			\
		"request=" __stringअगरy(r_value) ","			\
		r_idx_1 ","						\
		"counter_info_version="					\
			__stringअगरy(COUNTER_INFO_VERSION_CURRENT) ","	\
		"length=" #c_size ","					\
		"offset=" #c_offset)
#घोषणा REQUEST_(r_name, r_value, r_idx_1, r_fields)			\
	r_fields

#समावेश REQUEST_खाता

/*
 * Define event attribute array
 * अटल काष्ठा attribute *hv_gpci_event_attrs[] = अणु
 *	&<NAME_LOWER>_event_attr_<request name>_<field name>.attr,
 * पूर्ण;
 */
#समावेश "_clear.h"
#घोषणा __field_(r_name, r_value, r_idx_1, f_offset, f_size, f_name)
#घोषणा __count_(r_name, r_value, r_idx_1, c_offset, c_size, c_name)	\
	&EVENT_ATTR_NAME(r_name, c_name).attr.attr,
#घोषणा __array_(r_name, r_value, r_idx_1, a_offset, a_size, a_name)
#घोषणा REQUEST_(r_name, r_value, r_idx_1, r_fields)			\
	r_fields

अटल __maybe_unused काष्ठा attribute *hv_gpci_event_attrs[] = अणु
#समावेश REQUEST_खाता
	शून्य
पूर्ण;

/* cleanup */
#समावेश "_clear.h"
#अघोषित EVENT_ATTR_NAME
#अघोषित EVENT_ATTR_NAME_
#अघोषित BIT_NAME
#अघोषित BIT_NAME_
#अघोषित STRUCT_NAME
#अघोषित REQUEST_VALUE
#अघोषित REQUEST_VALUE_

#पूर्ण_अगर
