<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GENL_MAGIC_STRUCT_H
#घोषणा GENL_MAGIC_STRUCT_H

#अगर_अघोषित GENL_MAGIC_FAMILY
# error "you need to define GENL_MAGIC_FAMILY before inclusion"
#पूर्ण_अगर

#अगर_अघोषित GENL_MAGIC_VERSION
# error "you need to define GENL_MAGIC_VERSION before inclusion"
#पूर्ण_अगर

#अगर_अघोषित GENL_MAGIC_INCLUDE_खाता
# error "you need to define GENL_MAGIC_INCLUDE_FILE before inclusion"
#पूर्ण_अगर

#समावेश <linux/genetlink.h>
#समावेश <linux/types.h>

#घोषणा CONCAT__(a,b)	a ## b
#घोषणा CONCAT_(a,b)	CONCAT__(a,b)

बाह्य पूर्णांक CONCAT_(GENL_MAGIC_FAMILY, _genl_रेजिस्टर)(व्योम);
बाह्य व्योम CONCAT_(GENL_MAGIC_FAMILY, _genl_unरेजिस्टर)(व्योम);

/*
 * Extension of genl attribute validation policies			अणुअणुअणु2
 */

/*
 * @DRBD_GENLA_F_MANDATORY: By शेष, netlink ignores attributes it करोes not
 * know about.  This flag can be set in nlattr->nla_type to indicate that this
 * attribute must not be ignored.
 *
 * We check and हटाओ this flag in drbd_nla_check_mandatory() beक्रमe
 * validating the attribute types and lengths via nla_parse_nested().
 */
#घोषणा DRBD_GENLA_F_MANDATORY (1 << 14)

/*
 * Flags specअगरic to drbd and not visible at the netlink layer, used in
 * <काष्ठा>_from_attrs and <काष्ठा>_to_skb:
 *
 * @DRBD_F_REQUIRED: Attribute is required; a request without this attribute is
 * invalid.
 *
 * @DRBD_F_SENSITIVE: Attribute includes sensitive inक्रमmation and must not be
 * included in unpriviledged get requests or broadcasts.
 *
 * @DRBD_F_INVARIANT: Attribute is set when an object is initially created, but
 * cannot subsequently be changed.
 */
#घोषणा DRBD_F_REQUIRED (1 << 0)
#घोषणा DRBD_F_SENSITIVE (1 << 1)
#घोषणा DRBD_F_INVARIANT (1 << 2)

#घोषणा __nla_type(x)	((__u16)((x) & NLA_TYPE_MASK & ~DRBD_GENLA_F_MANDATORY))

/*									पूर्णपूर्णपूर्ण1
 * MAGIC
 * multi-include macro expansion magic starts here
 */

/* MAGIC helpers							अणुअणुअणु2 */

अटल अंतरभूत पूर्णांक nla_put_u64_0pad(काष्ठा sk_buff *skb, पूर्णांक attrtype, u64 value)
अणु
	वापस nla_put_64bit(skb, attrtype, माप(u64), &value, 0);
पूर्ण

/* possible field types */
#घोषणा __flg_field(attr_nr, attr_flag, name) \
	__field(attr_nr, attr_flag, name, NLA_U8, अक्षर, \
			nla_get_u8, nla_put_u8, false)
#घोषणा __u8_field(attr_nr, attr_flag, name)	\
	__field(attr_nr, attr_flag, name, NLA_U8, अचिन्हित अक्षर, \
			nla_get_u8, nla_put_u8, false)
#घोषणा __u16_field(attr_nr, attr_flag, name)	\
	__field(attr_nr, attr_flag, name, NLA_U16, __u16, \
			nla_get_u16, nla_put_u16, false)
#घोषणा __u32_field(attr_nr, attr_flag, name)	\
	__field(attr_nr, attr_flag, name, NLA_U32, __u32, \
			nla_get_u32, nla_put_u32, false)
#घोषणा __s32_field(attr_nr, attr_flag, name)	\
	__field(attr_nr, attr_flag, name, NLA_U32, __s32, \
			nla_get_u32, nla_put_u32, true)
#घोषणा __u64_field(attr_nr, attr_flag, name)	\
	__field(attr_nr, attr_flag, name, NLA_U64, __u64, \
			nla_get_u64, nla_put_u64_0pad, false)
#घोषणा __str_field(attr_nr, attr_flag, name, maxlen) \
	__array(attr_nr, attr_flag, name, NLA_NUL_STRING, अक्षर, maxlen, \
			nla_strscpy, nla_put, false)
#घोषणा __bin_field(attr_nr, attr_flag, name, maxlen) \
	__array(attr_nr, attr_flag, name, NLA_BINARY, अक्षर, maxlen, \
			nla_स_नकल, nla_put, false)

/* fields with शेष values */
#घोषणा __flg_field_def(attr_nr, attr_flag, name, शेष) \
	__flg_field(attr_nr, attr_flag, name)
#घोषणा __u32_field_def(attr_nr, attr_flag, name, शेष) \
	__u32_field(attr_nr, attr_flag, name)
#घोषणा __s32_field_def(attr_nr, attr_flag, name, शेष) \
	__s32_field(attr_nr, attr_flag, name)
#घोषणा __str_field_def(attr_nr, attr_flag, name, maxlen) \
	__str_field(attr_nr, attr_flag, name, maxlen)

#घोषणा GENL_op_init(args...)	args
#घोषणा GENL_करोit(handler)		\
	.करोit = handler,		\
	.flags = GENL_ADMIN_PERM,
#घोषणा GENL_dumpit(handler)		\
	.dumpit = handler,		\
	.flags = GENL_ADMIN_PERM,

/*									पूर्णपूर्णपूर्ण1
 * Magic: define the क्रमागत symbols क्रम genl_ops
 * Magic: define the क्रमागत symbols क्रम top level attributes
 * Magic: define the क्रमागत symbols क्रम nested attributes
 *									अणुअणुअणु2
 */

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)

#अघोषित GENL_mc_group
#घोषणा GENL_mc_group(group)

#अघोषित GENL_notअगरication
#घोषणा GENL_notअगरication(op_name, op_num, mcast_group, tla_list)	\
	op_name = op_num,

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, tla_list)			\
	op_name = op_num,

क्रमागत अणु
#समावेश GENL_MAGIC_INCLUDE_खाता
पूर्ण;

#अघोषित GENL_notअगरication
#घोषणा GENL_notअगरication(op_name, op_num, mcast_group, tla_list)

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, attr_list)

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields) \
		tag_name = tag_number,

क्रमागत अणु
#समावेश GENL_MAGIC_INCLUDE_खाता
पूर्ण;

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)	\
क्रमागत अणु								\
	s_fields						\
पूर्ण;

#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, type,	\
		__get, __put, __is_चिन्हित)			\
	T_ ## name = (__u16)(attr_nr | ((attr_flag) & DRBD_GENLA_F_MANDATORY)),

#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, type,	\
		maxlen, __get, __put, __is_चिन्हित)		\
	T_ ## name = (__u16)(attr_nr | ((attr_flag) & DRBD_GENLA_F_MANDATORY)),

#समावेश GENL_MAGIC_INCLUDE_खाता

/*									पूर्णपूर्णपूर्ण1
 * Magic: compile समय निश्चित unique numbers क्रम operations
 * Magic: -"- unique numbers क्रम top level attributes
 * Magic: -"- unique numbers क्रम nested attributes
 *									अणुअणुअणु2
 */

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, attr_list)	\
	हाल op_name:

#अघोषित GENL_notअगरication
#घोषणा GENL_notअगरication(op_name, op_num, mcast_group, tla_list)	\
	हाल op_name:

अटल अंतरभूत व्योम ct_निश्चित_unique_operations(व्योम)
अणु
	चयन (0) अणु
#समावेश GENL_MAGIC_INCLUDE_खाता
	हाल 0:
		;
	पूर्ण
पूर्ण

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, attr_list)

#अघोषित GENL_notअगरication
#घोषणा GENL_notअगरication(op_name, op_num, mcast_group, tla_list)

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
		हाल tag_number:

अटल अंतरभूत व्योम ct_निश्चित_unique_top_level_attributes(व्योम)
अणु
	चयन (0) अणु
#समावेश GENL_MAGIC_INCLUDE_खाता
	हाल 0:
		;
	पूर्ण
पूर्ण

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
अटल अंतरभूत व्योम ct_निश्चित_unique_ ## s_name ## _attributes(व्योम)	\
अणु									\
	चयन (0) अणु							\
	s_fields							\
	हाल 0:								\
			;						\
	पूर्ण								\
पूर्ण

#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, type, __get, __put,	\
		__is_चिन्हित)						\
	हाल attr_nr:

#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, type, maxlen,	\
		__get, __put, __is_चिन्हित)				\
	हाल attr_nr:

#समावेश GENL_MAGIC_INCLUDE_खाता

/*									पूर्णपूर्णपूर्ण1
 * Magic: declare काष्ठाs
 * काष्ठा <name> अणु
 *	fields
 * पूर्ण;
 *									अणुअणुअणु2
 */

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
काष्ठा s_name अणु s_fields पूर्ण;

#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, type, __get, __put,	\
		__is_चिन्हित)						\
	type name;

#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, type, maxlen,	\
		__get, __put, __is_चिन्हित)				\
	type name[maxlen];	\
	__u32 name ## _len;

#समावेश GENL_MAGIC_INCLUDE_खाता

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
क्रमागत अणु									\
	s_fields							\
पूर्ण;

#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, type, __get, __put,	\
		is_चिन्हित)						\
	F_ ## name ## _IS_SIGNED = is_चिन्हित,

#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, type, maxlen,	\
		__get, __put, is_चिन्हित)				\
	F_ ## name ## _IS_SIGNED = is_चिन्हित,

#समावेश GENL_MAGIC_INCLUDE_खाता

/* पूर्णपूर्णपूर्ण1 */
#पूर्ण_अगर /* GENL_MAGIC_STRUCT_H */
