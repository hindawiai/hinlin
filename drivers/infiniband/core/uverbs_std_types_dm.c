<शैली गुरु>
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

अटल पूर्णांक uverbs_मुक्त_dm(काष्ठा ib_uobject *uobject,
			  क्रमागत rdma_हटाओ_reason why,
			  काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_dm *dm = uobject->object;

	अगर (atomic_पढ़ो(&dm->usecnt))
		वापस -EBUSY;

	वापस dm->device->ops.dealloc_dm(dm, attrs);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_DM_ALLOC)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_dm_alloc_attr attr = अणुपूर्ण;
	काष्ठा ib_uobject *uobj =
		uverbs_attr_get(attrs, UVERBS_ATTR_ALLOC_DM_HANDLE)
			->obj_attr.uobject;
	काष्ठा ib_device *ib_dev = attrs->context->device;
	काष्ठा ib_dm *dm;
	पूर्णांक ret;

	अगर (!ib_dev->ops.alloc_dm)
		वापस -EOPNOTSUPP;

	ret = uverbs_copy_from(&attr.length, attrs,
			       UVERBS_ATTR_ALLOC_DM_LENGTH);
	अगर (ret)
		वापस ret;

	ret = uverbs_copy_from(&attr.alignment, attrs,
			       UVERBS_ATTR_ALLOC_DM_ALIGNMENT);
	अगर (ret)
		वापस ret;

	dm = ib_dev->ops.alloc_dm(ib_dev, attrs->context, &attr, attrs);
	अगर (IS_ERR(dm))
		वापस PTR_ERR(dm);

	dm->device  = ib_dev;
	dm->length  = attr.length;
	dm->uobject = uobj;
	atomic_set(&dm->usecnt, 0);

	uobj->object = dm;

	वापस 0;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_DM_ALLOC,
	UVERBS_ATTR_IDR(UVERBS_ATTR_ALLOC_DM_HANDLE,
			UVERBS_OBJECT_DM,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_ALLOC_DM_LENGTH,
			   UVERBS_ATTR_TYPE(u64),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(UVERBS_ATTR_ALLOC_DM_ALIGNMENT,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	UVERBS_METHOD_DM_FREE,
	UVERBS_ATTR_IDR(UVERBS_ATTR_FREE_DM_HANDLE,
			UVERBS_OBJECT_DM,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(UVERBS_OBJECT_DM,
			    UVERBS_TYPE_ALLOC_IDR(uverbs_मुक्त_dm),
			    &UVERBS_METHOD(UVERBS_METHOD_DM_ALLOC),
			    &UVERBS_METHOD(UVERBS_METHOD_DM_FREE));

स्थिर काष्ठा uapi_definition uverbs_def_obj_dm[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_DM,
				      UAPI_DEF_OBJ_NEEDS_FN(dealloc_dm)),
	अणुपूर्ण
पूर्ण;
