<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "rdma_core.h"
#समावेश "uverbs.h"
#समावेश <rdma/uverbs_std_types.h>

अटल पूर्णांक uverbs_मुक्त_counters(काष्ठा ib_uobject *uobject,
				क्रमागत rdma_हटाओ_reason why,
				काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_counters *counters = uobject->object;
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&counters->usecnt))
		वापस -EBUSY;

	ret = counters->device->ops.destroy_counters(counters);
	अगर (ret)
		वापस ret;
	kमुक्त(counters);
	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_COUNTERS_CREATE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, UVERBS_ATTR_CREATE_COUNTERS_HANDLE);
	काष्ठा ib_device *ib_dev = attrs->context->device;
	काष्ठा ib_counters *counters;
	पूर्णांक ret;

	/*
	 * This check should be हटाओd once the infraकाष्ठाure
	 * have the ability to हटाओ methods from parse tree once
	 * such condition is met.
	 */
	अगर (!ib_dev->ops.create_counters)
		वापस -EOPNOTSUPP;

	counters = rdma_zalloc_drv_obj(ib_dev, ib_counters);
	अगर (!counters)
		वापस -ENOMEM;

	counters->device = ib_dev;
	counters->uobject = uobj;
	uobj->object = counters;
	atomic_set(&counters->usecnt, 0);

	ret = ib_dev->ops.create_counters(counters, attrs);
	अगर (ret)
		kमुक्त(counters);

	वापस ret;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_COUNTERS_READ)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_counters_पढ़ो_attr पढ़ो_attr = अणुपूर्ण;
	स्थिर काष्ठा uverbs_attr *uattr;
	काष्ठा ib_counters *counters =
		uverbs_attr_get_obj(attrs, UVERBS_ATTR_READ_COUNTERS_HANDLE);
	पूर्णांक ret;

	अगर (!counters->device->ops.पढ़ो_counters)
		वापस -EOPNOTSUPP;

	अगर (!atomic_पढ़ो(&counters->usecnt))
		वापस -EINVAL;

	ret = uverbs_get_flags32(&पढ़ो_attr.flags, attrs,
				 UVERBS_ATTR_READ_COUNTERS_FLAGS,
				 IB_UVERBS_READ_COUNTERS_PREFER_CACHED);
	अगर (ret)
		वापस ret;

	uattr = uverbs_attr_get(attrs, UVERBS_ATTR_READ_COUNTERS_BUFF);
	पढ़ो_attr.ncounters = uattr->ptr_attr.len / माप(u64);
	पढ़ो_attr.counters_buff = uverbs_zalloc(
		attrs, array_size(पढ़ो_attr.ncounters, माप(u64)));
	अगर (IS_ERR(पढ़ो_attr.counters_buff))
		वापस PTR_ERR(पढ़ो_attr.counters_buff);

	ret = counters->device->ops.पढ़ो_counters(counters, &पढ़ो_attr, attrs);
	अगर (ret)
		वापस ret;

	वापस uverbs_copy_to(attrs, UVERBS_ATTR_READ_COUNTERS_BUFF,
			      पढ़ो_attr.counters_buff,
			      पढ़ो_attr.ncounters * माप(u64));
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_COUNTERS_CREATE,
	UVERBS_ATTR_IDR(UVERBS_ATTR_CREATE_COUNTERS_HANDLE,
			UVERBS_OBJECT_COUNTERS,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_COUNTERS_DESTROY,
	UVERBS_ATTR_IDR(UVERBS_ATTR_DESTROY_COUNTERS_HANDLE,
			UVERBS_OBJECT_COUNTERS,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_COUNTERS_READ,
	UVERBS_ATTR_IDR(UVERBS_ATTR_READ_COUNTERS_HANDLE,
			UVERBS_OBJECT_COUNTERS,
			UVERBS_ACCESS_READ,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_READ_COUNTERS_BUFF,
			    UVERBS_ATTR_MIN_SIZE(0),
			    UA_MANDATORY),
	UVERBS_ATTR_FLAGS_IN(UVERBS_ATTR_READ_COUNTERS_FLAGS,
			     क्रमागत ib_uverbs_पढ़ो_counters_flags));

DECLARE_UVERBS_NAMED_OBJECT(UVERBS_OBJECT_COUNTERS,
			    UVERBS_TYPE_ALLOC_IDR(uverbs_मुक्त_counters),
			    &UVERBS_METHOD(UVERBS_METHOD_COUNTERS_CREATE),
			    &UVERBS_METHOD(UVERBS_METHOD_COUNTERS_DESTROY),
			    &UVERBS_METHOD(UVERBS_METHOD_COUNTERS_READ));

स्थिर काष्ठा uapi_definition uverbs_def_obj_counters[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_COUNTERS,
				      UAPI_DEF_OBJ_NEEDS_FN(destroy_counters)),
	अणुपूर्ण
पूर्ण;
