<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
 */

#अगर_अघोषित _UVERBS_NAMED_IOCTL_
#घोषणा _UVERBS_NAMED_IOCTL_

#समावेश <rdma/uverbs_ioctl.h>

#अगर_अघोषित UVERBS_MODULE_NAME
#त्रुटि "Please #define UVERBS_MODULE_NAME before including rdma/uverbs_named_ioctl.h"
#पूर्ण_अगर

#घोषणा _UVERBS_PASTE(x, y)	x ## y
#घोषणा _UVERBS_NAME(x, y)	_UVERBS_PASTE(x, y)
#घोषणा UVERBS_METHOD(id)	_UVERBS_NAME(UVERBS_MODULE_NAME, _method_##id)
#घोषणा UVERBS_HANDLER(id)	_UVERBS_NAME(UVERBS_MODULE_NAME, _handler_##id)
#घोषणा UVERBS_OBJECT(id)	_UVERBS_NAME(UVERBS_MODULE_NAME, _object_##id)

/* These are अटल so they करो not need to be qualअगरied */
#घोषणा UVERBS_METHOD_ATTRS(method_id) _method_attrs_##method_id
#घोषणा UVERBS_OBJECT_METHODS(object_id) _UVERBS_NAME(_object_methods_##object_id, __LINE__)

#घोषणा DECLARE_UVERBS_NAMED_METHOD(_method_id, ...)                           \
	अटल स्थिर काष्ठा uverbs_attr_def *स्थिर UVERBS_METHOD_ATTRS(        \
		_method_id)[] = अणु __VA_ARGS__ पूर्ण;                               \
	अटल स्थिर काष्ठा uverbs_method_def UVERBS_METHOD(_method_id) = अणु    \
		.id = _method_id,                                              \
		.handler = UVERBS_HANDLER(_method_id),                         \
		.num_attrs = ARRAY_SIZE(UVERBS_METHOD_ATTRS(_method_id)),      \
		.attrs = &UVERBS_METHOD_ATTRS(_method_id),                     \
	पूर्ण

/* Create a standard destroy method using the शेष handler. The handle_attr
 * argument must be the attribute specअगरying the handle to destroy, the
 * शेष handler करोes not support any other attributes.
 */
#घोषणा DECLARE_UVERBS_NAMED_METHOD_DESTROY(_method_id, _handle_attr)          \
	अटल स्थिर काष्ठा uverbs_attr_def *स्थिर UVERBS_METHOD_ATTRS(        \
		_method_id)[] = अणु _handle_attr पूर्ण;                              \
	अटल स्थिर काष्ठा uverbs_method_def UVERBS_METHOD(_method_id) = अणु    \
		.id = _method_id,                                              \
		.handler = uverbs_destroy_def_handler,                         \
		.num_attrs = ARRAY_SIZE(UVERBS_METHOD_ATTRS(_method_id)),      \
		.attrs = &UVERBS_METHOD_ATTRS(_method_id),                     \
	पूर्ण

#घोषणा DECLARE_UVERBS_NAMED_OBJECT(_object_id, _type_attrs, ...)              \
	अटल स्थिर काष्ठा uverbs_method_def *स्थिर UVERBS_OBJECT_METHODS(    \
		_object_id)[] = अणु __VA_ARGS__ पूर्ण;                               \
	अटल स्थिर काष्ठा uverbs_object_def UVERBS_OBJECT(_object_id) = अणु    \
		.id = _object_id,                                              \
		.type_attrs = &_type_attrs,                                    \
		.num_methods = ARRAY_SIZE(UVERBS_OBJECT_METHODS(_object_id)),  \
		.methods = &UVERBS_OBJECT_METHODS(_object_id)                  \
	पूर्ण

/*
 * Declare global methods. These still have a unique object_id because we
 * identअगरy all uapi methods with a (object,method) tuple. However, they have
 * no type poपूर्णांकer.
 */
#घोषणा DECLARE_UVERBS_GLOBAL_METHODS(_object_id, ...)                         \
	अटल स्थिर काष्ठा uverbs_method_def *स्थिर UVERBS_OBJECT_METHODS(    \
		_object_id)[] = अणु __VA_ARGS__ पूर्ण;                               \
	अटल स्थिर काष्ठा uverbs_object_def UVERBS_OBJECT(_object_id) = अणु    \
		.id = _object_id,                                              \
		.num_methods = ARRAY_SIZE(UVERBS_OBJECT_METHODS(_object_id)),  \
		.methods = &UVERBS_OBJECT_METHODS(_object_id)                  \
	पूर्ण

/* Used by drivers to declare a complete parsing tree क्रम new methods
 */
#घोषणा ADD_UVERBS_METHODS(_name, _object_id, ...)                             \
	अटल स्थिर काष्ठा uverbs_method_def *स्थिर UVERBS_OBJECT_METHODS(    \
		_object_id)[] = अणु __VA_ARGS__ पूर्ण;                               \
	अटल स्थिर काष्ठा uverbs_object_def _name = अणु                        \
		.id = _object_id,                                              \
		.num_methods = ARRAY_SIZE(UVERBS_OBJECT_METHODS(_object_id)),  \
		.methods = &UVERBS_OBJECT_METHODS(_object_id)                  \
	पूर्ण;

/* Used by drivers to declare a complete parsing tree क्रम a single method that
 * dअगरfers only in having additional driver specअगरic attributes.
 */
#घोषणा ADD_UVERBS_ATTRIBUTES_SIMPLE(_name, _object_id, _method_id, ...)       \
	अटल स्थिर काष्ठा uverbs_attr_def *स्थिर UVERBS_METHOD_ATTRS(        \
		_method_id)[] = अणु __VA_ARGS__ पूर्ण;                               \
	अटल स्थिर काष्ठा uverbs_method_def UVERBS_METHOD(_method_id) = अणु    \
		.id = _method_id,                                              \
		.num_attrs = ARRAY_SIZE(UVERBS_METHOD_ATTRS(_method_id)),      \
		.attrs = &UVERBS_METHOD_ATTRS(_method_id),                     \
	पूर्ण;                                                                     \
	ADD_UVERBS_METHODS(_name, _object_id, &UVERBS_METHOD(_method_id))

#पूर्ण_अगर
