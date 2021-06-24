<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2017, Mellanox Technologies inc.  All rights reserved.
 */
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/rdma_user_ioctl.h>
#समावेश <linux/bitops.h>
#समावेश "rdma_core.h"
#समावेश "uverbs.h"

अटल पूर्णांक ib_uverbs_notsupp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम *uapi_add_elm(काष्ठा uverbs_api *uapi, u32 key, माप_प्रकार alloc_size)
अणु
	व्योम *elm;
	पूर्णांक rc;

	अगर (key == UVERBS_API_KEY_ERR)
		वापस ERR_PTR(-EOVERFLOW);

	elm = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!elm)
		वापस ERR_PTR(-ENOMEM);
	rc = radix_tree_insert(&uapi->radix, key, elm);
	अगर (rc) अणु
		kमुक्त(elm);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस elm;
पूर्ण

अटल व्योम *uapi_add_get_elm(काष्ठा uverbs_api *uapi, u32 key,
			      माप_प्रकार alloc_size, bool *exists)
अणु
	व्योम *elm;

	elm = uapi_add_elm(uapi, key, alloc_size);
	अगर (!IS_ERR(elm)) अणु
		*exists = false;
		वापस elm;
	पूर्ण

	अगर (elm != ERR_PTR(-EEXIST))
		वापस elm;

	elm = radix_tree_lookup(&uapi->radix, key);
	अगर (WARN_ON(!elm))
		वापस ERR_PTR(-EINVAL);
	*exists = true;
	वापस elm;
पूर्ण

अटल पूर्णांक uapi_create_ग_लिखो(काष्ठा uverbs_api *uapi,
			     काष्ठा ib_device *ibdev,
			     स्थिर काष्ठा uapi_definition *def,
			     u32 obj_key,
			     u32 *cur_method_key)
अणु
	काष्ठा uverbs_api_ग_लिखो_method *method_elm;
	u32 method_key = obj_key;
	bool exists;

	अगर (def->ग_लिखो.is_ex)
		method_key |= uapi_key_ग_लिखो_ex_method(def->ग_लिखो.command_num);
	अन्यथा
		method_key |= uapi_key_ग_लिखो_method(def->ग_लिखो.command_num);

	method_elm = uapi_add_get_elm(uapi, method_key, माप(*method_elm),
				      &exists);
	अगर (IS_ERR(method_elm))
		वापस PTR_ERR(method_elm);

	अगर (WARN_ON(exists && (def->ग_लिखो.is_ex != method_elm->is_ex)))
		वापस -EINVAL;

	method_elm->is_ex = def->ग_लिखो.is_ex;
	method_elm->handler = def->func_ग_लिखो;
	अगर (!def->ग_लिखो.is_ex)
		method_elm->disabled = !(ibdev->uverbs_cmd_mask &
					 BIT_ULL(def->ग_लिखो.command_num));

	अगर (!def->ग_लिखो.is_ex && def->func_ग_लिखो) अणु
		method_elm->has_udata = def->ग_लिखो.has_udata;
		method_elm->has_resp = def->ग_लिखो.has_resp;
		method_elm->req_size = def->ग_लिखो.req_size;
		method_elm->resp_size = def->ग_लिखो.resp_size;
	पूर्ण

	*cur_method_key = method_key;
	वापस 0;
पूर्ण

अटल पूर्णांक uapi_merge_method(काष्ठा uverbs_api *uapi,
			     काष्ठा uverbs_api_object *obj_elm, u32 obj_key,
			     स्थिर काष्ठा uverbs_method_def *method,
			     bool is_driver)
अणु
	u32 method_key = obj_key | uapi_key_ioctl_method(method->id);
	काष्ठा uverbs_api_ioctl_method *method_elm;
	अचिन्हित पूर्णांक i;
	bool exists;

	अगर (!method->attrs)
		वापस 0;

	method_elm = uapi_add_get_elm(uapi, method_key, माप(*method_elm),
				      &exists);
	अगर (IS_ERR(method_elm))
		वापस PTR_ERR(method_elm);
	अगर (exists) अणु
		/*
		 * This occurs when a driver uses ADD_UVERBS_ATTRIBUTES_SIMPLE
		 */
		अगर (WARN_ON(method->handler))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		WARN_ON(!method->handler);
		rcu_assign_poपूर्णांकer(method_elm->handler, method->handler);
		अगर (method->handler != uverbs_destroy_def_handler)
			method_elm->driver_method = is_driver;
	पूर्ण

	क्रम (i = 0; i != method->num_attrs; i++) अणु
		स्थिर काष्ठा uverbs_attr_def *attr = (*method->attrs)[i];
		काष्ठा uverbs_api_attr *attr_slot;

		अगर (!attr)
			जारी;

		/*
		 * ENUM_IN contains the 'ids' pointer to the driver's .rodata,
		 * so अगर it is specअगरied by a driver then it always makes this
		 * पूर्णांकo a driver method.
		 */
		अगर (attr->attr.type == UVERBS_ATTR_TYPE_ENUM_IN)
			method_elm->driver_method |= is_driver;

		/*
		 * Like other uobject based things we only support a single
		 * uobject being NEW'd or DESTROY'd
		 */
		अगर (attr->attr.type == UVERBS_ATTR_TYPE_IDRS_ARRAY) अणु
			u8 access = attr->attr.u2.objs_arr.access;

			अगर (WARN_ON(access == UVERBS_ACCESS_NEW ||
				    access == UVERBS_ACCESS_DESTROY))
				वापस -EINVAL;
		पूर्ण

		attr_slot =
			uapi_add_elm(uapi, method_key | uapi_key_attr(attr->id),
				     माप(*attr_slot));
		/* Attributes are not allowed to be modअगरied by drivers */
		अगर (IS_ERR(attr_slot))
			वापस PTR_ERR(attr_slot);

		attr_slot->spec = attr->attr;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uapi_merge_obj_tree(काष्ठा uverbs_api *uapi,
			       स्थिर काष्ठा uverbs_object_def *obj,
			       bool is_driver)
अणु
	काष्ठा uverbs_api_object *obj_elm;
	अचिन्हित पूर्णांक i;
	u32 obj_key;
	bool exists;
	पूर्णांक rc;

	obj_key = uapi_key_obj(obj->id);
	obj_elm = uapi_add_get_elm(uapi, obj_key, माप(*obj_elm), &exists);
	अगर (IS_ERR(obj_elm))
		वापस PTR_ERR(obj_elm);

	अगर (obj->type_attrs) अणु
		अगर (WARN_ON(obj_elm->type_attrs))
			वापस -EINVAL;

		obj_elm->id = obj->id;
		obj_elm->type_attrs = obj->type_attrs;
		obj_elm->type_class = obj->type_attrs->type_class;
		/*
		 * Today drivers are only permitted to use idr_class and
		 * fd_class types. We can revoke the IDR types during
		 * disassociation, and the FD types require the driver to use
		 * काष्ठा file_operations.owner to prevent the driver module
		 * code from unloading जबतक the file is खोलो. This provides
		 * enough safety that uverbs_uobject_fd_release() will
		 * जारी to work.  Drivers using FD are responsible to
		 * handle disassociation of the device on their own.
		 */
		अगर (WARN_ON(is_driver &&
			    obj->type_attrs->type_class != &uverbs_idr_class &&
			    obj->type_attrs->type_class != &uverbs_fd_class))
			वापस -EINVAL;
	पूर्ण

	अगर (!obj->methods)
		वापस 0;

	क्रम (i = 0; i != obj->num_methods; i++) अणु
		स्थिर काष्ठा uverbs_method_def *method = (*obj->methods)[i];

		अगर (!method)
			जारी;

		rc = uapi_merge_method(uapi, obj_elm, obj_key, method,
				       is_driver);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uapi_disable_elm(काष्ठा uverbs_api *uapi,
			    स्थिर काष्ठा uapi_definition *def,
			    u32 obj_key,
			    u32 method_key)
अणु
	bool exists;

	अगर (def->scope == UAPI_SCOPE_OBJECT) अणु
		काष्ठा uverbs_api_object *obj_elm;

		obj_elm = uapi_add_get_elm(
			uapi, obj_key, माप(*obj_elm), &exists);
		अगर (IS_ERR(obj_elm))
			वापस PTR_ERR(obj_elm);
		obj_elm->disabled = 1;
		वापस 0;
	पूर्ण

	अगर (def->scope == UAPI_SCOPE_METHOD &&
	    uapi_key_is_ioctl_method(method_key)) अणु
		काष्ठा uverbs_api_ioctl_method *method_elm;

		method_elm = uapi_add_get_elm(uapi, method_key,
					      माप(*method_elm), &exists);
		अगर (IS_ERR(method_elm))
			वापस PTR_ERR(method_elm);
		method_elm->disabled = 1;
		वापस 0;
	पूर्ण

	अगर (def->scope == UAPI_SCOPE_METHOD &&
	    (uapi_key_is_ग_लिखो_method(method_key) ||
	     uapi_key_is_ग_लिखो_ex_method(method_key))) अणु
		काष्ठा uverbs_api_ग_लिखो_method *ग_लिखो_elm;

		ग_लिखो_elm = uapi_add_get_elm(uapi, method_key,
					     माप(*ग_लिखो_elm), &exists);
		अगर (IS_ERR(ग_लिखो_elm))
			वापस PTR_ERR(ग_लिखो_elm);
		ग_लिखो_elm->disabled = 1;
		वापस 0;
	पूर्ण

	WARN_ON(true);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक uapi_merge_def(काष्ठा uverbs_api *uapi, काष्ठा ib_device *ibdev,
			  स्थिर काष्ठा uapi_definition *def_list,
			  bool is_driver)
अणु
	स्थिर काष्ठा uapi_definition *def = def_list;
	u32 cur_obj_key = UVERBS_API_KEY_ERR;
	u32 cur_method_key = UVERBS_API_KEY_ERR;
	bool exists;
	पूर्णांक rc;

	अगर (!def_list)
		वापस 0;

	क्रम (;; def++) अणु
		चयन ((क्रमागत uapi_definition_kind)def->kind) अणु
		हाल UAPI_DEF_CHAIN:
			rc = uapi_merge_def(uapi, ibdev, def->chain, is_driver);
			अगर (rc)
				वापस rc;
			जारी;

		हाल UAPI_DEF_CHAIN_OBJ_TREE:
			अगर (WARN_ON(def->object_start.object_id !=
				    def->chain_obj_tree->id))
				वापस -EINVAL;

			cur_obj_key = uapi_key_obj(def->object_start.object_id);
			rc = uapi_merge_obj_tree(uapi, def->chain_obj_tree,
						 is_driver);
			अगर (rc)
				वापस rc;
			जारी;

		हाल UAPI_DEF_END:
			वापस 0;

		हाल UAPI_DEF_IS_SUPPORTED_DEV_FN: अणु
			व्योम **ibdev_fn =
				(व्योम *)(&ibdev->ops) + def->needs_fn_offset;

			अगर (*ibdev_fn)
				जारी;
			rc = uapi_disable_elm(
				uapi, def, cur_obj_key, cur_method_key);
			अगर (rc)
				वापस rc;
			जारी;
		पूर्ण

		हाल UAPI_DEF_IS_SUPPORTED_FUNC:
			अगर (def->func_is_supported(ibdev))
				जारी;
			rc = uapi_disable_elm(
				uapi, def, cur_obj_key, cur_method_key);
			अगर (rc)
				वापस rc;
			जारी;

		हाल UAPI_DEF_OBJECT_START: अणु
			काष्ठा uverbs_api_object *obj_elm;

			cur_obj_key = uapi_key_obj(def->object_start.object_id);
			obj_elm = uapi_add_get_elm(uapi, cur_obj_key,
						   माप(*obj_elm), &exists);
			अगर (IS_ERR(obj_elm))
				वापस PTR_ERR(obj_elm);
			जारी;
		पूर्ण

		हाल UAPI_DEF_WRITE:
			rc = uapi_create_ग_लिखो(
				uapi, ibdev, def, cur_obj_key, &cur_method_key);
			अगर (rc)
				वापस rc;
			जारी;
		पूर्ण
		WARN_ON(true);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
uapi_finalize_ioctl_method(काष्ठा uverbs_api *uapi,
			   काष्ठा uverbs_api_ioctl_method *method_elm,
			   u32 method_key)
अणु
	काष्ठा radix_tree_iter iter;
	अचिन्हित पूर्णांक num_attrs = 0;
	अचिन्हित पूर्णांक max_bkey = 0;
	bool single_uobj = false;
	व्योम __rcu **slot;

	method_elm->destroy_bkey = UVERBS_API_ATTR_BKEY_LEN;
	radix_tree_क्रम_each_slot (slot, &uapi->radix, &iter,
				  uapi_key_attrs_start(method_key)) अणु
		काष्ठा uverbs_api_attr *elm =
			rcu_dereference_रक्षित(*slot, true);
		u32 attr_key = iter.index & UVERBS_API_ATTR_KEY_MASK;
		u32 attr_bkey = uapi_bkey_attr(attr_key);
		u8 type = elm->spec.type;

		अगर (uapi_key_attr_to_ioctl_method(iter.index) !=
		    uapi_key_attr_to_ioctl_method(method_key))
			अवरोध;

		अगर (elm->spec.mandatory)
			__set_bit(attr_bkey, method_elm->attr_mandatory);

		अगर (elm->spec.is_udata)
			method_elm->has_udata = true;

		अगर (type == UVERBS_ATTR_TYPE_IDR ||
		    type == UVERBS_ATTR_TYPE_FD) अणु
			u8 access = elm->spec.u.obj.access;

			/*
			 * Verbs specs may only have one NEW/DESTROY, we करोn't
			 * have the infraकाष्ठाure to पात multiple NEW's or
			 * cope with multiple DESTROY failure.
			 */
			अगर (access == UVERBS_ACCESS_NEW ||
			    access == UVERBS_ACCESS_DESTROY) अणु
				अगर (WARN_ON(single_uobj))
					वापस -EINVAL;

				single_uobj = true;
				अगर (WARN_ON(!elm->spec.mandatory))
					वापस -EINVAL;
			पूर्ण

			अगर (access == UVERBS_ACCESS_DESTROY)
				method_elm->destroy_bkey = attr_bkey;
		पूर्ण

		max_bkey = max(max_bkey, attr_bkey);
		num_attrs++;
	पूर्ण

	method_elm->key_biपंचांगap_len = max_bkey + 1;
	WARN_ON(method_elm->key_biपंचांगap_len > UVERBS_API_ATTR_BKEY_LEN);

	uapi_compute_bundle_size(method_elm, num_attrs);
	वापस 0;
पूर्ण

अटल पूर्णांक uapi_finalize(काष्ठा uverbs_api *uapi)
अणु
	स्थिर काष्ठा uverbs_api_ग_लिखो_method **data;
	अचिन्हित दीर्घ max_ग_लिखो_ex = 0;
	अचिन्हित दीर्घ max_ग_लिखो = 0;
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;
	पूर्णांक rc;
	पूर्णांक i;

	radix_tree_क्रम_each_slot (slot, &uapi->radix, &iter, 0) अणु
		काष्ठा uverbs_api_ioctl_method *method_elm =
			rcu_dereference_रक्षित(*slot, true);

		अगर (uapi_key_is_ioctl_method(iter.index)) अणु
			rc = uapi_finalize_ioctl_method(uapi, method_elm,
							iter.index);
			अगर (rc)
				वापस rc;
		पूर्ण

		अगर (uapi_key_is_ग_लिखो_method(iter.index))
			max_ग_लिखो = max(max_ग_लिखो,
					iter.index & UVERBS_API_ATTR_KEY_MASK);
		अगर (uapi_key_is_ग_लिखो_ex_method(iter.index))
			max_ग_लिखो_ex =
				max(max_ग_लिखो_ex,
				    iter.index & UVERBS_API_ATTR_KEY_MASK);
	पूर्ण

	uapi->notsupp_method.handler = ib_uverbs_notsupp;
	uapi->num_ग_लिखो = max_ग_लिखो + 1;
	uapi->num_ग_लिखो_ex = max_ग_लिखो_ex + 1;
	data = kदो_स्मृति_array(uapi->num_ग_लिखो + uapi->num_ग_लिखो_ex,
			     माप(*uapi->ग_लिखो_methods), GFP_KERNEL);
	क्रम (i = 0; i != uapi->num_ग_लिखो + uapi->num_ग_लिखो_ex; i++)
		data[i] = &uapi->notsupp_method;
	uapi->ग_लिखो_methods = data;
	uapi->ग_लिखो_ex_methods = data + uapi->num_ग_लिखो;

	radix_tree_क्रम_each_slot (slot, &uapi->radix, &iter, 0) अणु
		अगर (uapi_key_is_ग_लिखो_method(iter.index))
			uapi->ग_लिखो_methods[iter.index &
					    UVERBS_API_ATTR_KEY_MASK] =
				rcu_dereference_रक्षित(*slot, true);
		अगर (uapi_key_is_ग_लिखो_ex_method(iter.index))
			uapi->ग_लिखो_ex_methods[iter.index &
					       UVERBS_API_ATTR_KEY_MASK] =
				rcu_dereference_रक्षित(*slot, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uapi_हटाओ_range(काष्ठा uverbs_api *uapi, u32 start, u32 last)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	radix_tree_क्रम_each_slot (slot, &uapi->radix, &iter, start) अणु
		अगर (iter.index > last)
			वापस;
		kमुक्त(rcu_dereference_रक्षित(*slot, true));
		radix_tree_iter_delete(&uapi->radix, &iter, slot);
	पूर्ण
पूर्ण

अटल व्योम uapi_हटाओ_object(काष्ठा uverbs_api *uapi, u32 obj_key)
अणु
	uapi_हटाओ_range(uapi, obj_key,
			  obj_key | UVERBS_API_METHOD_KEY_MASK |
				  UVERBS_API_ATTR_KEY_MASK);
पूर्ण

अटल व्योम uapi_हटाओ_method(काष्ठा uverbs_api *uapi, u32 method_key)
अणु
	uapi_हटाओ_range(uapi, method_key,
			  method_key | UVERBS_API_ATTR_KEY_MASK);
पूर्ण


अटल u32 uapi_get_obj_id(काष्ठा uverbs_attr_spec *spec)
अणु
	अगर (spec->type == UVERBS_ATTR_TYPE_IDR ||
	    spec->type == UVERBS_ATTR_TYPE_FD)
		वापस spec->u.obj.obj_type;
	अगर (spec->type == UVERBS_ATTR_TYPE_IDRS_ARRAY)
		वापस spec->u2.objs_arr.obj_type;
	वापस UVERBS_API_KEY_ERR;
पूर्ण

अटल व्योम uapi_key_okay(u32 key)
अणु
	अचिन्हित पूर्णांक count = 0;

	अगर (uapi_key_is_object(key))
		count++;
	अगर (uapi_key_is_ioctl_method(key))
		count++;
	अगर (uapi_key_is_ग_लिखो_method(key))
		count++;
	अगर (uapi_key_is_ग_लिखो_ex_method(key))
		count++;
	अगर (uapi_key_is_attr(key))
		count++;
	WARN(count != 1, "Bad count %d key=%x", count, key);
पूर्ण

अटल व्योम uapi_finalize_disable(काष्ठा uverbs_api *uapi)
अणु
	काष्ठा radix_tree_iter iter;
	u32 starting_key = 0;
	bool scan_again = false;
	व्योम __rcu **slot;

again:
	radix_tree_क्रम_each_slot (slot, &uapi->radix, &iter, starting_key) अणु
		uapi_key_okay(iter.index);

		अगर (uapi_key_is_object(iter.index)) अणु
			काष्ठा uverbs_api_object *obj_elm =
				rcu_dereference_रक्षित(*slot, true);

			अगर (obj_elm->disabled) अणु
				/* Have to check all the attrs again */
				scan_again = true;
				starting_key = iter.index;
				uapi_हटाओ_object(uapi, iter.index);
				जाओ again;
			पूर्ण
			जारी;
		पूर्ण

		अगर (uapi_key_is_ioctl_method(iter.index)) अणु
			काष्ठा uverbs_api_ioctl_method *method_elm =
				rcu_dereference_रक्षित(*slot, true);

			अगर (method_elm->disabled) अणु
				starting_key = iter.index;
				uapi_हटाओ_method(uapi, iter.index);
				जाओ again;
			पूर्ण
			जारी;
		पूर्ण

		अगर (uapi_key_is_ग_लिखो_method(iter.index) ||
		    uapi_key_is_ग_लिखो_ex_method(iter.index)) अणु
			काष्ठा uverbs_api_ग_लिखो_method *method_elm =
				rcu_dereference_रक्षित(*slot, true);

			अगर (method_elm->disabled) अणु
				kमुक्त(method_elm);
				radix_tree_iter_delete(&uapi->radix, &iter, slot);
			पूर्ण
			जारी;
		पूर्ण

		अगर (uapi_key_is_attr(iter.index)) अणु
			काष्ठा uverbs_api_attr *attr_elm =
				rcu_dereference_रक्षित(*slot, true);
			स्थिर काष्ठा uverbs_api_object *पंचांगp_obj;
			u32 obj_key;

			/*
			 * If the method has a mandatory object handle
			 * attribute which relies on an object which is not
			 * present then the entire method is uncallable.
			 */
			अगर (!attr_elm->spec.mandatory)
				जारी;
			obj_key = uapi_get_obj_id(&attr_elm->spec);
			अगर (obj_key == UVERBS_API_KEY_ERR)
				जारी;
			पंचांगp_obj = uapi_get_object(uapi, obj_key);
			अगर (IS_ERR(पंचांगp_obj)) अणु
				अगर (PTR_ERR(पंचांगp_obj) == -ENOMSG)
					जारी;
			पूर्ण अन्यथा अणु
				अगर (!पंचांगp_obj->disabled)
					जारी;
			पूर्ण

			starting_key = iter.index;
			uapi_हटाओ_method(
				uapi,
				iter.index & (UVERBS_API_OBJ_KEY_MASK |
					      UVERBS_API_METHOD_KEY_MASK));
			जाओ again;
		पूर्ण

		WARN_ON(false);
	पूर्ण

	अगर (!scan_again)
		वापस;
	scan_again = false;
	starting_key = 0;
	जाओ again;
पूर्ण

व्योम uverbs_destroy_api(काष्ठा uverbs_api *uapi)
अणु
	अगर (!uapi)
		वापस;

	uapi_हटाओ_range(uapi, 0, U32_MAX);
	kमुक्त(uapi->ग_लिखो_methods);
	kमुक्त(uapi);
पूर्ण

अटल स्थिर काष्ठा uapi_definition uverbs_core_api[] = अणु
	UAPI_DEF_CHAIN(uverbs_def_obj_async_fd),
	UAPI_DEF_CHAIN(uverbs_def_obj_counters),
	UAPI_DEF_CHAIN(uverbs_def_obj_cq),
	UAPI_DEF_CHAIN(uverbs_def_obj_device),
	UAPI_DEF_CHAIN(uverbs_def_obj_dm),
	UAPI_DEF_CHAIN(uverbs_def_obj_flow_action),
	UAPI_DEF_CHAIN(uverbs_def_obj_पूर्णांकf),
	UAPI_DEF_CHAIN(uverbs_def_obj_mr),
	UAPI_DEF_CHAIN(uverbs_def_obj_qp),
	UAPI_DEF_CHAIN(uverbs_def_obj_srq),
	UAPI_DEF_CHAIN(uverbs_def_obj_wq),
	UAPI_DEF_CHAIN(uverbs_def_ग_लिखो_पूर्णांकf),
	अणुपूर्ण,
पूर्ण;

काष्ठा uverbs_api *uverbs_alloc_api(काष्ठा ib_device *ibdev)
अणु
	काष्ठा uverbs_api *uapi;
	पूर्णांक rc;

	uapi = kzalloc(माप(*uapi), GFP_KERNEL);
	अगर (!uapi)
		वापस ERR_PTR(-ENOMEM);

	INIT_RADIX_TREE(&uapi->radix, GFP_KERNEL);
	uapi->driver_id = ibdev->ops.driver_id;

	rc = uapi_merge_def(uapi, ibdev, uverbs_core_api, false);
	अगर (rc)
		जाओ err;
	rc = uapi_merge_def(uapi, ibdev, ibdev->driver_def, true);
	अगर (rc)
		जाओ err;

	uapi_finalize_disable(uapi);
	rc = uapi_finalize(uapi);
	अगर (rc)
		जाओ err;

	वापस uapi;
err:
	अगर (rc != -ENOMEM)
		dev_err(&ibdev->dev,
			"Setup of uverbs_api failed, kernel parsing tree description is not valid (%d)??\n",
			rc);

	uverbs_destroy_api(uapi);
	वापस ERR_PTR(rc);
पूर्ण

/*
 * The pre version is करोne beक्रमe destroying the HW objects, it only blocks
 * off method access. All methods that require the ib_dev or the module data
 * must test one of these assignments prior to continuing.
 */
व्योम uverbs_disassociate_api_pre(काष्ठा ib_uverbs_device *uverbs_dev)
अणु
	काष्ठा uverbs_api *uapi = uverbs_dev->uapi;
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	rcu_assign_poपूर्णांकer(uverbs_dev->ib_dev, शून्य);

	radix_tree_क्रम_each_slot (slot, &uapi->radix, &iter, 0) अणु
		अगर (uapi_key_is_ioctl_method(iter.index)) अणु
			काष्ठा uverbs_api_ioctl_method *method_elm =
				rcu_dereference_रक्षित(*slot, true);

			अगर (method_elm->driver_method)
				rcu_assign_poपूर्णांकer(method_elm->handler, शून्य);
		पूर्ण
	पूर्ण

	synchronize_srcu(&uverbs_dev->disassociate_srcu);
पूर्ण

/*
 * Called when a driver disassociates from the ib_uverbs_device. The
 * assumption is that the driver module will unload after. Replace everything
 * related to the driver with शून्य as a safety measure.
 */
व्योम uverbs_disassociate_api(काष्ठा uverbs_api *uapi)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	radix_tree_क्रम_each_slot (slot, &uapi->radix, &iter, 0) अणु
		अगर (uapi_key_is_object(iter.index)) अणु
			काष्ठा uverbs_api_object *object_elm =
				rcu_dereference_रक्षित(*slot, true);

			/*
			 * Some type_attrs are in the driver module. We करोn't
			 * bother to keep track of which since there should be
			 * no use of this after disassociate.
			 */
			object_elm->type_attrs = शून्य;
		पूर्ण अन्यथा अगर (uapi_key_is_attr(iter.index)) अणु
			काष्ठा uverbs_api_attr *elm =
				rcu_dereference_रक्षित(*slot, true);

			अगर (elm->spec.type == UVERBS_ATTR_TYPE_ENUM_IN)
				elm->spec.u2.क्रमागत_def.ids = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
