<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2017, Mellanox Technologies inc.  All rights reserved.
 */

#अगर_अघोषित _UVERBS_IOCTL_
#घोषणा _UVERBS_IOCTL_

#समावेश <rdma/uverbs_types.h>
#समावेश <linux/uaccess.h>
#समावेश <rdma/rdma_user_ioctl.h>
#समावेश <rdma/ib_user_ioctl_verbs.h>
#समावेश <rdma/ib_user_ioctl_cmds.h>

/*
 * =======================================
 *	Verbs action specअगरications
 * =======================================
 */

क्रमागत uverbs_attr_type अणु
	UVERBS_ATTR_TYPE_NA,
	UVERBS_ATTR_TYPE_PTR_IN,
	UVERBS_ATTR_TYPE_PTR_OUT,
	UVERBS_ATTR_TYPE_IDR,
	UVERBS_ATTR_TYPE_FD,
	UVERBS_ATTR_TYPE_ENUM_IN,
	UVERBS_ATTR_TYPE_IDRS_ARRAY,
पूर्ण;

क्रमागत uverbs_obj_access अणु
	UVERBS_ACCESS_READ,
	UVERBS_ACCESS_WRITE,
	UVERBS_ACCESS_NEW,
	UVERBS_ACCESS_DESTROY
पूर्ण;

/* Specअगरication of a single attribute inside the ioctl message */
/* good size 16 */
काष्ठा uverbs_attr_spec अणु
	u8 type;

	/*
	 * Support extending attributes by length. Allow the user to provide
	 * more bytes than ptr.len, but check that everything after is zero'd
	 * by the user.
	 */
	u8 zero_trailing:1;
	/*
	 * Valid only क्रम PTR_IN. Allocate and copy the data inside
	 * the parser
	 */
	u8 alloc_and_copy:1;
	u8 mandatory:1;
	/* True अगर this is from UVERBS_ATTR_UHW */
	u8 is_udata:1;

	जोड़ अणु
		काष्ठा अणु
			/* Current known size to kernel */
			u16 len;
			/* User isn't allowed to provide something < min_len */
			u16 min_len;
		पूर्ण ptr;

		काष्ठा अणु
			/*
			 * higher bits mean the namespace and lower bits mean
			 * the type id within the namespace.
			 */
			u16 obj_type;
			u8 access;
		पूर्ण obj;

		काष्ठा अणु
			u8 num_elems;
		पूर्ण क्रमागत_def;
	पूर्ण u;

	/* This weird split lets us हटाओ some padding */
	जोड़ अणु
		काष्ठा अणु
			/*
			 * The क्रमागत attribute can select one of the attributes
			 * contained in the ids array. Currently only PTR_IN
			 * attributes are supported in the ids array.
			 */
			स्थिर काष्ठा uverbs_attr_spec *ids;
		पूर्ण क्रमागत_def;

		काष्ठा अणु
			/*
			 * higher bits mean the namespace and lower bits mean
			 * the type id within the namespace.
			 */
			u16				obj_type;
			u16				min_len;
			u16				max_len;
			u8				access;
		पूर्ण objs_arr;
	पूर्ण u2;
पूर्ण;

/*
 * Inक्रमmation about the API is loaded पूर्णांकo a radix tree. For IOCTL we start
 * with a tuple of:
 *  object_id, attr_id, method_id
 *
 * Which is a 48 bit value, with most of the bits guaranteed to be zero. Based
 * on the current kernel support this is compressed पूर्णांकo 16 bit key क्रम the
 * radix tree. Since this compression is entirely पूर्णांकernal to the kernel the
 * below limits can be revised अगर the kernel gains additional data.
 *
 * With 64 leafs per node this is a 3 level radix tree.
 *
 * The tree encodes multiple types, and uses a scheme where OBJ_ID,0,0 वापसs
 * the object slot, and OBJ_ID,METH_ID,0 and वापसs the method slot.
 *
 * This also encodes the tables क्रम the ग_लिखो() and ग_लिखो() extended commands
 * using the coding
 *   OBJ_ID,UVERBS_API_METHOD_IS_WRITE,command #
 *   OBJ_ID,UVERBS_API_METHOD_IS_WRITE_EX,command_ex #
 * ie the WRITE path is treated as a special method type in the ioctl
 * framework.
 */
क्रमागत uapi_radix_data अणु
	UVERBS_API_NS_FLAG = 1U << UVERBS_ID_NS_SHIFT,

	UVERBS_API_ATTR_KEY_BITS = 6,
	UVERBS_API_ATTR_KEY_MASK = GENMASK(UVERBS_API_ATTR_KEY_BITS - 1, 0),
	UVERBS_API_ATTR_BKEY_LEN = (1 << UVERBS_API_ATTR_KEY_BITS) - 1,
	UVERBS_API_WRITE_KEY_NUM = 1 << UVERBS_API_ATTR_KEY_BITS,

	UVERBS_API_METHOD_KEY_BITS = 5,
	UVERBS_API_METHOD_KEY_SHIFT = UVERBS_API_ATTR_KEY_BITS,
	UVERBS_API_METHOD_KEY_NUM_CORE = 22,
	UVERBS_API_METHOD_IS_WRITE = 30 << UVERBS_API_METHOD_KEY_SHIFT,
	UVERBS_API_METHOD_IS_WRITE_EX = 31 << UVERBS_API_METHOD_KEY_SHIFT,
	UVERBS_API_METHOD_KEY_NUM_DRIVER =
		(UVERBS_API_METHOD_IS_WRITE >> UVERBS_API_METHOD_KEY_SHIFT) -
		UVERBS_API_METHOD_KEY_NUM_CORE,
	UVERBS_API_METHOD_KEY_MASK = GENMASK(
		UVERBS_API_METHOD_KEY_BITS + UVERBS_API_METHOD_KEY_SHIFT - 1,
		UVERBS_API_METHOD_KEY_SHIFT),

	UVERBS_API_OBJ_KEY_BITS = 5,
	UVERBS_API_OBJ_KEY_SHIFT =
		UVERBS_API_METHOD_KEY_BITS + UVERBS_API_METHOD_KEY_SHIFT,
	UVERBS_API_OBJ_KEY_NUM_CORE = 20,
	UVERBS_API_OBJ_KEY_NUM_DRIVER =
		(1 << UVERBS_API_OBJ_KEY_BITS) - UVERBS_API_OBJ_KEY_NUM_CORE,
	UVERBS_API_OBJ_KEY_MASK = GENMASK(31, UVERBS_API_OBJ_KEY_SHIFT),

	/* This id guaranteed to not exist in the radix tree */
	UVERBS_API_KEY_ERR = 0xFFFFFFFF,
पूर्ण;

अटल अंतरभूत __attribute_स्थिर__ u32 uapi_key_obj(u32 id)
अणु
	अगर (id & UVERBS_API_NS_FLAG) अणु
		id &= ~UVERBS_API_NS_FLAG;
		अगर (id >= UVERBS_API_OBJ_KEY_NUM_DRIVER)
			वापस UVERBS_API_KEY_ERR;
		id = id + UVERBS_API_OBJ_KEY_NUM_CORE;
	पूर्ण अन्यथा अणु
		अगर (id >= UVERBS_API_OBJ_KEY_NUM_CORE)
			वापस UVERBS_API_KEY_ERR;
	पूर्ण

	वापस id << UVERBS_API_OBJ_KEY_SHIFT;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ bool uapi_key_is_object(u32 key)
अणु
	वापस (key & ~UVERBS_API_OBJ_KEY_MASK) == 0;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32 uapi_key_ioctl_method(u32 id)
अणु
	अगर (id & UVERBS_API_NS_FLAG) अणु
		id &= ~UVERBS_API_NS_FLAG;
		अगर (id >= UVERBS_API_METHOD_KEY_NUM_DRIVER)
			वापस UVERBS_API_KEY_ERR;
		id = id + UVERBS_API_METHOD_KEY_NUM_CORE;
	पूर्ण अन्यथा अणु
		id++;
		अगर (id >= UVERBS_API_METHOD_KEY_NUM_CORE)
			वापस UVERBS_API_KEY_ERR;
	पूर्ण

	वापस id << UVERBS_API_METHOD_KEY_SHIFT;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32 uapi_key_ग_लिखो_method(u32 id)
अणु
	अगर (id >= UVERBS_API_WRITE_KEY_NUM)
		वापस UVERBS_API_KEY_ERR;
	वापस UVERBS_API_METHOD_IS_WRITE | id;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32 uapi_key_ग_लिखो_ex_method(u32 id)
अणु
	अगर (id >= UVERBS_API_WRITE_KEY_NUM)
		वापस UVERBS_API_KEY_ERR;
	वापस UVERBS_API_METHOD_IS_WRITE_EX | id;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32
uapi_key_attr_to_ioctl_method(u32 attr_key)
अणु
	वापस attr_key &
	       (UVERBS_API_OBJ_KEY_MASK | UVERBS_API_METHOD_KEY_MASK);
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ bool uapi_key_is_ioctl_method(u32 key)
अणु
	अचिन्हित पूर्णांक method = key & UVERBS_API_METHOD_KEY_MASK;

	वापस method != 0 && method < UVERBS_API_METHOD_IS_WRITE &&
	       (key & UVERBS_API_ATTR_KEY_MASK) == 0;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ bool uapi_key_is_ग_लिखो_method(u32 key)
अणु
	वापस (key & UVERBS_API_METHOD_KEY_MASK) == UVERBS_API_METHOD_IS_WRITE;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ bool uapi_key_is_ग_लिखो_ex_method(u32 key)
अणु
	वापस (key & UVERBS_API_METHOD_KEY_MASK) ==
	       UVERBS_API_METHOD_IS_WRITE_EX;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32 uapi_key_attrs_start(u32 ioctl_method_key)
अणु
	/* 0 is the method slot itself */
	वापस ioctl_method_key + 1;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32 uapi_key_attr(u32 id)
अणु
	/*
	 * The attr is deचिन्हित to fit in the typical single radix tree node
	 * of 64 entries. Since allmost all methods have driver attributes we
	 * organize things so that the driver and core attributes पूर्णांकerleave to
	 * reduce the length of the attributes array in typical हालs.
	 */
	अगर (id & UVERBS_API_NS_FLAG) अणु
		id &= ~UVERBS_API_NS_FLAG;
		id++;
		अगर (id >= 1 << (UVERBS_API_ATTR_KEY_BITS - 1))
			वापस UVERBS_API_KEY_ERR;
		id = (id << 1) | 0;
	पूर्ण अन्यथा अणु
		अगर (id >= 1 << (UVERBS_API_ATTR_KEY_BITS - 1))
			वापस UVERBS_API_KEY_ERR;
		id = (id << 1) | 1;
	पूर्ण

	वापस id;
पूर्ण

/* Only true क्रम ioctl methods */
अटल अंतरभूत __attribute_स्थिर__ bool uapi_key_is_attr(u32 key)
अणु
	अचिन्हित पूर्णांक method = key & UVERBS_API_METHOD_KEY_MASK;

	वापस method != 0 && method < UVERBS_API_METHOD_IS_WRITE &&
	       (key & UVERBS_API_ATTR_KEY_MASK) != 0;
पूर्ण

/*
 * This वापसs a value in the range [0 to UVERBS_API_ATTR_BKEY_LEN),
 * basically it unकरोes the reservation of 0 in the ID numbering. attr_key
 * must alपढ़ोy be masked with UVERBS_API_ATTR_KEY_MASK, or be the output of
 * uapi_key_attr().
 */
अटल अंतरभूत __attribute_स्थिर__ u32 uapi_bkey_attr(u32 attr_key)
अणु
	वापस attr_key - 1;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ u32 uapi_bkey_to_key_attr(u32 attr_bkey)
अणु
	वापस attr_bkey + 1;
पूर्ण

/*
 * =======================================
 *	Verbs definitions
 * =======================================
 */

काष्ठा uverbs_attr_def अणु
	u16                           id;
	काष्ठा uverbs_attr_spec       attr;
पूर्ण;

काष्ठा uverbs_method_def अणु
	u16                                  id;
	/* Combination of bits from क्रमागत UVERBS_ACTION_FLAG_XXXX */
	u32				     flags;
	माप_प्रकार				     num_attrs;
	स्थिर काष्ठा uverbs_attr_def * स्थिर (*attrs)[];
	पूर्णांक (*handler)(काष्ठा uverbs_attr_bundle *attrs);
पूर्ण;

काष्ठा uverbs_object_def अणु
	u16					 id;
	स्थिर काष्ठा uverbs_obj_type	        *type_attrs;
	माप_प्रकार				         num_methods;
	स्थिर काष्ठा uverbs_method_def * स्थिर (*methods)[];
पूर्ण;

क्रमागत uapi_definition_kind अणु
	UAPI_DEF_END = 0,
	UAPI_DEF_OBJECT_START,
	UAPI_DEF_WRITE,
	UAPI_DEF_CHAIN_OBJ_TREE,
	UAPI_DEF_CHAIN,
	UAPI_DEF_IS_SUPPORTED_FUNC,
	UAPI_DEF_IS_SUPPORTED_DEV_FN,
पूर्ण;

क्रमागत uapi_definition_scope अणु
	UAPI_SCOPE_OBJECT = 1,
	UAPI_SCOPE_METHOD = 2,
पूर्ण;

काष्ठा uapi_definition अणु
	u8 kind;
	u8 scope;
	जोड़ अणु
		काष्ठा अणु
			u16 object_id;
		पूर्ण object_start;
		काष्ठा अणु
			u16 command_num;
			u8 is_ex:1;
			u8 has_udata:1;
			u8 has_resp:1;
			u8 req_size;
			u8 resp_size;
		पूर्ण ग_लिखो;
	पूर्ण;

	जोड़ अणु
		bool (*func_is_supported)(काष्ठा ib_device *device);
		पूर्णांक (*func_ग_लिखो)(काष्ठा uverbs_attr_bundle *attrs);
		स्थिर काष्ठा uapi_definition *chain;
		स्थिर काष्ठा uverbs_object_def *chain_obj_tree;
		माप_प्रकार needs_fn_offset;
	पूर्ण;
पूर्ण;

/* Define things connected to object_id */
#घोषणा DECLARE_UVERBS_OBJECT(_object_id, ...)                                 \
	अणु                                                                      \
		.kind = UAPI_DEF_OBJECT_START,                                 \
		.object_start = अणु .object_id = _object_id पूर्ण,                   \
	पूर्ण,                                                                     \
		##__VA_ARGS__

/* Use in a var_args of DECLARE_UVERBS_OBJECT */
#घोषणा DECLARE_UVERBS_WRITE(_command_num, _func, _cmd_desc, ...)              \
	अणु                                                                      \
		.kind = UAPI_DEF_WRITE,                                        \
		.scope = UAPI_SCOPE_OBJECT,                                    \
		.ग_लिखो = अणु .is_ex = 0, .command_num = _command_num पूर्ण,          \
		.func_ग_लिखो = _func,                                           \
		_cmd_desc,                                                     \
	पूर्ण,                                                                     \
		##__VA_ARGS__

/* Use in a var_args of DECLARE_UVERBS_OBJECT */
#घोषणा DECLARE_UVERBS_WRITE_EX(_command_num, _func, _cmd_desc, ...)           \
	अणु                                                                      \
		.kind = UAPI_DEF_WRITE,                                        \
		.scope = UAPI_SCOPE_OBJECT,                                    \
		.ग_लिखो = अणु .is_ex = 1, .command_num = _command_num पूर्ण,          \
		.func_ग_लिखो = _func,                                           \
		_cmd_desc,                                                     \
	पूर्ण,                                                                     \
		##__VA_ARGS__

/*
 * Object is only supported अगर the function poपूर्णांकer named ibdev_fn in काष्ठा
 * ib_device is not शून्य.
 */
#घोषणा UAPI_DEF_OBJ_NEEDS_FN(ibdev_fn)                                        \
	अणु                                                                      \
		.kind = UAPI_DEF_IS_SUPPORTED_DEV_FN,                          \
		.scope = UAPI_SCOPE_OBJECT,                                    \
		.needs_fn_offset =                                             \
			दुरत्व(काष्ठा ib_device_ops, ibdev_fn) +             \
			BUILD_BUG_ON_ZERO(माप_field(काष्ठा ib_device_ops,   \
						       ibdev_fn) !=            \
					  माप(व्योम *)),                     \
	पूर्ण

/*
 * Method is only supported अगर the function poपूर्णांकer named ibdev_fn in काष्ठा
 * ib_device is not शून्य.
 */
#घोषणा UAPI_DEF_METHOD_NEEDS_FN(ibdev_fn)                                     \
	अणु                                                                      \
		.kind = UAPI_DEF_IS_SUPPORTED_DEV_FN,                          \
		.scope = UAPI_SCOPE_METHOD,                                    \
		.needs_fn_offset =                                             \
			दुरत्व(काष्ठा ib_device_ops, ibdev_fn) +             \
			BUILD_BUG_ON_ZERO(माप_field(काष्ठा ib_device_ops,   \
						       ibdev_fn) !=            \
					  माप(व्योम *)),                     \
	पूर्ण

/* Call a function to determine अगर the entire object is supported or not */
#घोषणा UAPI_DEF_IS_OBJ_SUPPORTED(_func)                                       \
	अणु                                                                      \
		.kind = UAPI_DEF_IS_SUPPORTED_FUNC,                            \
		.scope = UAPI_SCOPE_OBJECT, .func_is_supported = _func,        \
	पूर्ण

/* Include another काष्ठा uapi_definition in this one */
#घोषणा UAPI_DEF_CHAIN(_def_var)                                               \
	अणु                                                                      \
		.kind = UAPI_DEF_CHAIN, .chain = _def_var,                     \
	पूर्ण

/* Temporary until the tree base description is replaced */
#घोषणा UAPI_DEF_CHAIN_OBJ_TREE(_object_क्रमागत, _object_ptr, ...)                \
	अणु                                                                      \
		.kind = UAPI_DEF_CHAIN_OBJ_TREE,                               \
		.object_start = अणु .object_id = _object_क्रमागत पूर्ण,                 \
		.chain_obj_tree = _object_ptr,                                 \
	पूर्ण,								       \
		##__VA_ARGS__
#घोषणा UAPI_DEF_CHAIN_OBJ_TREE_NAMED(_object_क्रमागत, ...)                       \
	UAPI_DEF_CHAIN_OBJ_TREE(_object_क्रमागत, &UVERBS_OBJECT(_object_क्रमागत),    \
				##__VA_ARGS__)

/*
 * =======================================
 *	Attribute Specअगरications
 * =======================================
 */

#घोषणा UVERBS_ATTR_SIZE(_min_len, _len)			\
	.u.ptr.min_len = _min_len, .u.ptr.len = _len

#घोषणा UVERBS_ATTR_NO_DATA() UVERBS_ATTR_SIZE(0, 0)

/*
 * Specअगरies a uapi काष्ठाure that cannot be extended. The user must always
 * supply the whole काष्ठाure and nothing more. The काष्ठाure must be declared
 * in a header under include/uapi/rdma.
 */
#घोषणा UVERBS_ATTR_TYPE(_type)					\
	.u.ptr.min_len = माप(_type), .u.ptr.len = माप(_type)
/*
 * Specअगरies a uapi काष्ठाure where the user must provide at least up to
 * member 'last'.  Anything after last and up until the end of the काष्ठाure
 * can be non-zero, anything दीर्घer than the end of the काष्ठाure must be
 * zero. The काष्ठाure must be declared in a header under include/uapi/rdma.
 */
#घोषणा UVERBS_ATTR_STRUCT(_type, _last)                                       \
	.zero_trailing = 1,                                                    \
	UVERBS_ATTR_SIZE(दुरत्वend(_type, _last), माप(_type))
/*
 * Specअगरies at least min_len bytes must be passed in, but the amount can be
 * larger, up to the protocol maximum size. No check क्रम zeroing is करोne.
 */
#घोषणा UVERBS_ATTR_MIN_SIZE(_min_len) UVERBS_ATTR_SIZE(_min_len, अच_लघु_उच्च)

/* Must be used in the '...' of any UVERBS_ATTR */
#घोषणा UA_ALLOC_AND_COPY .alloc_and_copy = 1
#घोषणा UA_MANDATORY .mandatory = 1
#घोषणा UA_OPTIONAL .mandatory = 0

/*
 * min_len must be bigger than 0 and _max_len must be smaller than 4095.  Only
 * READ\WRITE accesses are supported.
 */
#घोषणा UVERBS_ATTR_IDRS_ARR(_attr_id, _idr_type, _access, _min_len, _max_len, \
			     ...)                                              \
	(&(स्थिर काष्ठा uverbs_attr_def)अणु                                      \
		.id = (_attr_id) +                                             \
		      BUILD_BUG_ON_ZERO((_min_len) == 0 ||                     \
					(_max_len) >                           \
						PAGE_SIZE / माप(व्योम *) ||  \
					(_min_len) > (_max_len) ||             \
					(_access) == UVERBS_ACCESS_NEW ||      \
					(_access) == UVERBS_ACCESS_DESTROY),   \
		.attr = अणु .type = UVERBS_ATTR_TYPE_IDRS_ARRAY,                 \
			  .u2.objs_arr.obj_type = _idr_type,                   \
			  .u2.objs_arr.access = _access,                       \
			  .u2.objs_arr.min_len = _min_len,                     \
			  .u2.objs_arr.max_len = _max_len,                     \
			  __VA_ARGS__ पूर्ण पूर्ण)

/*
 * Only क्रम use with UVERBS_ATTR_IDR, allows any uobject type to be accepted,
 * the user must validate the type of the uobject instead.
 */
#घोषणा UVERBS_IDR_ANY_OBJECT 0xFFFF

#घोषणा UVERBS_ATTR_IDR(_attr_id, _idr_type, _access, ...)                     \
	(&(स्थिर काष्ठा uverbs_attr_def)अणु                                      \
		.id = _attr_id,                                                \
		.attr = अणु .type = UVERBS_ATTR_TYPE_IDR,                        \
			  .u.obj.obj_type = _idr_type,                         \
			  .u.obj.access = _access,                             \
			  __VA_ARGS__ पूर्ण पूर्ण)

#घोषणा UVERBS_ATTR_FD(_attr_id, _fd_type, _access, ...)                       \
	(&(स्थिर काष्ठा uverbs_attr_def)अणु                                      \
		.id = (_attr_id) +                                             \
		      BUILD_BUG_ON_ZERO((_access) != UVERBS_ACCESS_NEW &&      \
					(_access) != UVERBS_ACCESS_READ),      \
		.attr = अणु .type = UVERBS_ATTR_TYPE_FD,                         \
			  .u.obj.obj_type = _fd_type,                          \
			  .u.obj.access = _access,                             \
			  __VA_ARGS__ पूर्ण पूर्ण)

#घोषणा UVERBS_ATTR_PTR_IN(_attr_id, _type, ...)                               \
	(&(स्थिर काष्ठा uverbs_attr_def)अणु                                      \
		.id = _attr_id,                                                \
		.attr = अणु .type = UVERBS_ATTR_TYPE_PTR_IN,                     \
			  _type,                                               \
			  __VA_ARGS__ पूर्ण पूर्ण)

#घोषणा UVERBS_ATTR_PTR_OUT(_attr_id, _type, ...)                              \
	(&(स्थिर काष्ठा uverbs_attr_def)अणु                                      \
		.id = _attr_id,                                                \
		.attr = अणु .type = UVERBS_ATTR_TYPE_PTR_OUT,                    \
			  _type,                                               \
			  __VA_ARGS__ पूर्ण पूर्ण)

/* _क्रमागत_arry should be a 'static const union uverbs_attr_spec[]' */
#घोषणा UVERBS_ATTR_ENUM_IN(_attr_id, _क्रमागत_arr, ...)                          \
	(&(स्थिर काष्ठा uverbs_attr_def)अणु                                      \
		.id = _attr_id,                                                \
		.attr = अणु .type = UVERBS_ATTR_TYPE_ENUM_IN,                    \
			  .u2.क्रमागत_def.ids = _क्रमागत_arr,                        \
			  .u.क्रमागत_def.num_elems = ARRAY_SIZE(_क्रमागत_arr),       \
			  __VA_ARGS__ पूर्ण,                                       \
	पूर्ण)

/* An input value that is a member in the क्रमागत _क्रमागत_type. */
#घोषणा UVERBS_ATTR_CONST_IN(_attr_id, _क्रमागत_type, ...)                        \
	UVERBS_ATTR_PTR_IN(                                                    \
		_attr_id,                                                      \
		UVERBS_ATTR_SIZE(                                              \
			माप(u64) + BUILD_BUG_ON_ZERO(!माप(_क्रमागत_type)),  \
			माप(u64)),                                          \
		__VA_ARGS__)

/*
 * An input value that is a bitwise combination of values of _क्रमागत_type.
 * This permits the flag value to be passed as either a u32 or u64, it must
 * be retrieved via uverbs_get_flag().
 */
#घोषणा UVERBS_ATTR_FLAGS_IN(_attr_id, _क्रमागत_type, ...)                        \
	UVERBS_ATTR_PTR_IN(                                                    \
		_attr_id,                                                      \
		UVERBS_ATTR_SIZE(माप(u32) + BUILD_BUG_ON_ZERO(              \
						       !माप(_क्रमागत_type *)), \
				 माप(u64)),                                 \
		__VA_ARGS__)

/*
 * This spec is used in order to pass inक्रमmation to the hardware driver in a
 * legacy way. Every verb that could get driver specअगरic data should get this
 * spec.
 */
#घोषणा UVERBS_ATTR_UHW()                                                      \
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_UHW_IN,                                 \
			   UVERBS_ATTR_MIN_SIZE(0),			       \
			   UA_OPTIONAL,                                        \
			   .is_udata = 1),				       \
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_UHW_OUT,                               \
			    UVERBS_ATTR_MIN_SIZE(0),			       \
			    UA_OPTIONAL,                                       \
			    .is_udata = 1)

/* =================================================
 *              Parsing infraकाष्ठाure
 * =================================================
 */


काष्ठा uverbs_ptr_attr अणु
	/*
	 * If UVERBS_ATTR_SPEC_F_ALLOC_AND_COPY is set then the 'ptr' is
	 * used.
	 */
	जोड़ अणु
		व्योम *ptr;
		u64 data;
	पूर्ण;
	u16		len;
	u16		uattr_idx;
	u8		क्रमागत_id;
पूर्ण;

काष्ठा uverbs_obj_attr अणु
	काष्ठा ib_uobject		*uobject;
	स्थिर काष्ठा uverbs_api_attr	*attr_elm;
पूर्ण;

काष्ठा uverbs_objs_arr_attr अणु
	काष्ठा ib_uobject **uobjects;
	u16 len;
पूर्ण;

काष्ठा uverbs_attr अणु
	जोड़ अणु
		काष्ठा uverbs_ptr_attr	ptr_attr;
		काष्ठा uverbs_obj_attr	obj_attr;
		काष्ठा uverbs_objs_arr_attr objs_arr_attr;
	पूर्ण;
पूर्ण;

काष्ठा uverbs_attr_bundle अणु
	काष्ठा ib_udata driver_udata;
	काष्ठा ib_udata ucore;
	काष्ठा ib_uverbs_file *ufile;
	काष्ठा ib_ucontext *context;
	काष्ठा ib_uobject *uobject;
	DECLARE_BITMAP(attr_present, UVERBS_API_ATTR_BKEY_LEN);
	काष्ठा uverbs_attr attrs[];
पूर्ण;

अटल अंतरभूत bool uverbs_attr_is_valid(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
					अचिन्हित पूर्णांक idx)
अणु
	वापस test_bit(uapi_bkey_attr(uapi_key_attr(idx)),
			attrs_bundle->attr_present);
पूर्ण

/**
 * rdma_udata_to_drv_context - Helper macro to get the driver's context out of
 *                             ib_udata which is embedded in uverbs_attr_bundle.
 *
 * If udata is not शून्य this cannot fail. Otherwise a शून्य udata will result
 * in a शून्य ucontext poपूर्णांकer, as a safety precaution. Callers should be using
 * 'udata' to determine अगर the driver call is in user or kernel mode, not
 * 'ucontext'.
 *
 */
अटल अंतरभूत काष्ठा uverbs_attr_bundle *
rdma_udata_to_uverbs_attr_bundle(काष्ठा ib_udata *udata)
अणु
	वापस container_of(udata, काष्ठा uverbs_attr_bundle, driver_udata);
पूर्ण

#घोषणा rdma_udata_to_drv_context(udata, drv_dev_काष्ठा, member)                \
	(udata ? container_of(rdma_udata_to_uverbs_attr_bundle(udata)->context, \
			      drv_dev_काष्ठा, member) : (drv_dev_काष्ठा *)शून्य)

#घोषणा IS_UVERBS_COPY_ERR(_ret)		((_ret) && (_ret) != -ENOENT)

अटल अंतरभूत स्थिर काष्ठा uverbs_attr *uverbs_attr_get(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
							u16 idx)
अणु
	अगर (!uverbs_attr_is_valid(attrs_bundle, idx))
		वापस ERR_PTR(-ENOENT);

	वापस &attrs_bundle->attrs[uapi_bkey_attr(uapi_key_attr(idx))];
पूर्ण

अटल अंतरभूत पूर्णांक uverbs_attr_get_क्रमागत_id(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
					  u16 idx)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(attrs_bundle, idx);

	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	वापस attr->ptr_attr.क्रमागत_id;
पूर्ण

अटल अंतरभूत व्योम *uverbs_attr_get_obj(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
					u16 idx)
अणु
	स्थिर काष्ठा uverbs_attr *attr;

	attr = uverbs_attr_get(attrs_bundle, idx);
	अगर (IS_ERR(attr))
		वापस ERR_CAST(attr);

	वापस attr->obj_attr.uobject->object;
पूर्ण

अटल अंतरभूत काष्ठा ib_uobject *uverbs_attr_get_uobject(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
							 u16 idx)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(attrs_bundle, idx);

	अगर (IS_ERR(attr))
		वापस ERR_CAST(attr);

	वापस attr->obj_attr.uobject;
पूर्ण

अटल अंतरभूत पूर्णांक
uverbs_attr_get_len(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle, u16 idx)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(attrs_bundle, idx);

	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	वापस attr->ptr_attr.len;
पूर्ण

व्योम uverbs_finalize_uobj_create(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
				 u16 idx);

/*
 * uverbs_attr_ptr_get_array_size() - Get array size poपूर्णांकer by a ptr
 * attribute.
 * @attrs: The attribute bundle
 * @idx: The ID of the attribute
 * @elem_size: The size of the element in the array
 */
अटल अंतरभूत पूर्णांक
uverbs_attr_ptr_get_array_size(काष्ठा uverbs_attr_bundle *attrs, u16 idx,
			       माप_प्रकार elem_size)
अणु
	पूर्णांक size = uverbs_attr_get_len(attrs, idx);

	अगर (size < 0)
		वापस size;

	अगर (size % elem_size)
		वापस -EINVAL;

	वापस size / elem_size;
पूर्ण

/**
 * uverbs_attr_get_uobjs_arr() - Provides array's properties क्रम attribute क्रम
 * UVERBS_ATTR_TYPE_IDRS_ARRAY.
 * @arr: Returned poपूर्णांकer to array of poपूर्णांकers क्रम uobjects or शून्य अगर
 *       the attribute isn't provided.
 *
 * Return: The array length or 0 अगर no attribute was provided.
 */
अटल अंतरभूत पूर्णांक uverbs_attr_get_uobjs_arr(
	स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle, u16 attr_idx,
	काष्ठा ib_uobject ***arr)
अणु
	स्थिर काष्ठा uverbs_attr *attr =
			uverbs_attr_get(attrs_bundle, attr_idx);

	अगर (IS_ERR(attr)) अणु
		*arr = शून्य;
		वापस 0;
	पूर्ण

	*arr = attr->objs_arr_attr.uobjects;

	वापस attr->objs_arr_attr.len;
पूर्ण

अटल अंतरभूत bool uverbs_attr_ptr_is_अंतरभूत(स्थिर काष्ठा uverbs_attr *attr)
अणु
	वापस attr->ptr_attr.len <= माप(attr->ptr_attr.data);
पूर्ण

अटल अंतरभूत व्योम *uverbs_attr_get_alloced_ptr(
	स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle, u16 idx)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(attrs_bundle, idx);

	अगर (IS_ERR(attr))
		वापस (व्योम *)attr;

	वापस uverbs_attr_ptr_is_अंतरभूत(attr) ? (व्योम *)&attr->ptr_attr.data :
						 attr->ptr_attr.ptr;
पूर्ण

अटल अंतरभूत पूर्णांक _uverbs_copy_from(व्योम *to,
				    स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
				    माप_प्रकार idx,
				    माप_प्रकार size)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(attrs_bundle, idx);

	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	/*
	 * Validation ensures attr->ptr_attr.len >= size. If the caller is
	 * using UVERBS_ATTR_SPEC_F_MIN_SZ_OR_ZERO then it must call
	 * uverbs_copy_from_or_zero.
	 */
	अगर (unlikely(size < attr->ptr_attr.len))
		वापस -EINVAL;

	अगर (uverbs_attr_ptr_is_अंतरभूत(attr))
		स_नकल(to, &attr->ptr_attr.data, attr->ptr_attr.len);
	अन्यथा अगर (copy_from_user(to, u64_to_user_ptr(attr->ptr_attr.data),
				attr->ptr_attr.len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक _uverbs_copy_from_or_zero(व्योम *to,
					    स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
					    माप_प्रकार idx,
					    माप_प्रकार size)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(attrs_bundle, idx);
	माप_प्रकार min_size;

	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	min_size = min_t(माप_प्रकार, size, attr->ptr_attr.len);

	अगर (uverbs_attr_ptr_is_अंतरभूत(attr))
		स_नकल(to, &attr->ptr_attr.data, min_size);
	अन्यथा अगर (copy_from_user(to, u64_to_user_ptr(attr->ptr_attr.data),
				min_size))
		वापस -EFAULT;

	अगर (size > min_size)
		स_रखो(to + min_size, 0, size - min_size);

	वापस 0;
पूर्ण

#घोषणा uverbs_copy_from(to, attrs_bundle, idx)				      \
	_uverbs_copy_from(to, attrs_bundle, idx, माप(*to))

#घोषणा uverbs_copy_from_or_zero(to, attrs_bundle, idx)			      \
	_uverbs_copy_from_or_zero(to, attrs_bundle, idx, माप(*to))

अटल अंतरभूत काष्ठा ib_ucontext *
ib_uverbs_get_ucontext(स्थिर काष्ठा uverbs_attr_bundle *attrs)
अणु
	वापस ib_uverbs_get_ucontext_file(attrs->ufile);
पूर्ण

#अगर IS_ENABLED(CONFIG_INFINIBAND_USER_ACCESS)
पूर्णांक uverbs_get_flags64(u64 *to, स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
		       माप_प्रकार idx, u64 allowed_bits);
पूर्णांक uverbs_get_flags32(u32 *to, स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
		       माप_प्रकार idx, u64 allowed_bits);
पूर्णांक uverbs_copy_to(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle, माप_प्रकार idx,
		   स्थिर व्योम *from, माप_प्रकार size);
__दो_स्मृति व्योम *_uverbs_alloc(काष्ठा uverbs_attr_bundle *bundle, माप_प्रकार size,
			     gfp_t flags);

अटल अंतरभूत __दो_स्मृति व्योम *uverbs_alloc(काष्ठा uverbs_attr_bundle *bundle,
					  माप_प्रकार size)
अणु
	वापस _uverbs_alloc(bundle, size, GFP_KERNEL);
पूर्ण

अटल अंतरभूत __दो_स्मृति व्योम *uverbs_zalloc(काष्ठा uverbs_attr_bundle *bundle,
					   माप_प्रकार size)
अणु
	वापस _uverbs_alloc(bundle, size, GFP_KERNEL | __GFP_ZERO);
पूर्ण

अटल अंतरभूत __दो_स्मृति व्योम *uverbs_kसुस्मृति(काष्ठा uverbs_attr_bundle *bundle,
					    माप_प्रकार n, माप_प्रकार size)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(n, size, &bytes)))
		वापस ERR_PTR(-EOVERFLOW);
	वापस uverbs_zalloc(bundle, bytes);
पूर्ण

पूर्णांक _uverbs_get_स्थिर_चिन्हित(s64 *to,
			     स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
			     माप_प्रकार idx, s64 lower_bound, u64 upper_bound,
			     s64 *def_val);
पूर्णांक _uverbs_get_स्थिर_अचिन्हित(u64 *to,
			       स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
			       माप_प्रकार idx, u64 upper_bound, u64 *def_val);
पूर्णांक uverbs_copy_to_काष्ठा_or_zero(स्थिर काष्ठा uverbs_attr_bundle *bundle,
				  माप_प्रकार idx, स्थिर व्योम *from, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत पूर्णांक
uverbs_get_flags64(u64 *to, स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
		   माप_प्रकार idx, u64 allowed_bits)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक
uverbs_get_flags32(u32 *to, स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
		   माप_प्रकार idx, u64 allowed_bits)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक uverbs_copy_to(स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
				 माप_प्रकार idx, स्थिर व्योम *from, माप_प्रकार size)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत __दो_स्मृति व्योम *uverbs_alloc(काष्ठा uverbs_attr_bundle *bundle,
					  माप_प्रकार size)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत __दो_स्मृति व्योम *uverbs_zalloc(काष्ठा uverbs_attr_bundle *bundle,
					   माप_प्रकार size)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत पूर्णांक
_uverbs_get_स्थिर(s64 *to, स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
		  माप_प्रकार idx, s64 lower_bound, u64 upper_bound,
		  s64 *def_val)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक
uverbs_copy_to_काष्ठा_or_zero(स्थिर काष्ठा uverbs_attr_bundle *bundle,
			      माप_प्रकार idx, स्थिर व्योम *from, माप_प्रकार size)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक
_uverbs_get_स्थिर_चिन्हित(s64 *to,
			 स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
			 माप_प्रकार idx, s64 lower_bound, u64 upper_bound,
			 s64 *def_val)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक
_uverbs_get_स्थिर_अचिन्हित(u64 *to,
			   स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
			   माप_प्रकार idx, u64 upper_bound, u64 *def_val)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#घोषणा uverbs_get_स्थिर_चिन्हित(_to, _attrs_bundle, _idx)                      \
	(अणु                                                                     \
		s64 _val;                                                      \
		पूर्णांक _ret =                                                     \
			_uverbs_get_स्थिर_चिन्हित(&_val, _attrs_bundle, _idx,   \
					  type_min(typeof(*(_to))),            \
					  type_max(typeof(*(_to))), शून्य);     \
		(*(_to)) = _val;                                               \
		_ret;                                                          \
	पूर्ण)

#घोषणा uverbs_get_स्थिर_अचिन्हित(_to, _attrs_bundle, _idx)                    \
	(अणु                                                                     \
		u64 _val;                                                      \
		पूर्णांक _ret =                                                     \
			_uverbs_get_स्थिर_अचिन्हित(&_val, _attrs_bundle, _idx, \
					  type_max(typeof(*(_to))), शून्य);     \
		(*(_to)) = _val;                                               \
		_ret;                                                          \
	पूर्ण)

#घोषणा uverbs_get_स्थिर_शेष_चिन्हित(_to, _attrs_bundle, _idx, _शेष)    \
	(अणु                                                                     \
		s64 _val;                                                      \
		s64 _def_val = _शेष;                                       \
		पूर्णांक _ret =                                                     \
			_uverbs_get_स्थिर_चिन्हित(&_val, _attrs_bundle, _idx,   \
				type_min(typeof(*(_to))),                      \
				type_max(typeof(*(_to))), &_def_val);          \
		(*(_to)) = _val;                                               \
		_ret;                                                          \
	पूर्ण)

#घोषणा uverbs_get_स्थिर_शेष_अचिन्हित(_to, _attrs_bundle, _idx, _शेष)  \
	(अणु                                                                     \
		u64 _val;                                                      \
		u64 _def_val = _शेष;                                       \
		पूर्णांक _ret =                                                     \
			_uverbs_get_स्थिर_अचिन्हित(&_val, _attrs_bundle, _idx, \
				type_max(typeof(*(_to))), &_def_val);          \
		(*(_to)) = _val;                                               \
		_ret;                                                          \
	पूर्ण)

#घोषणा uverbs_get_स्थिर(_to, _attrs_bundle, _idx)                             \
	(is_चिन्हित_type(typeof(*(_to))) ?                                      \
		 uverbs_get_स्थिर_चिन्हित(_to, _attrs_bundle, _idx) :           \
		 uverbs_get_स्थिर_अचिन्हित(_to, _attrs_bundle, _idx))          \

#घोषणा uverbs_get_स्थिर_शेष(_to, _attrs_bundle, _idx, _शेष)           \
	(is_चिन्हित_type(typeof(*(_to))) ?                                      \
		 uverbs_get_स्थिर_शेष_चिन्हित(_to, _attrs_bundle, _idx,     \
						  _शेष) :                  \
		 uverbs_get_स्थिर_शेष_अचिन्हित(_to, _attrs_bundle, _idx,   \
						    _शेष))

#पूर्ण_अगर
