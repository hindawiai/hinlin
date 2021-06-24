<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies inc.  All rights reserved.
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

#समावेश <rdma/rdma_user_ioctl.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "rdma_core.h"
#समावेश "uverbs.h"

काष्ठा bundle_alloc_head अणु
	काष्ठा bundle_alloc_head *next;
	u8 data[];
पूर्ण;

काष्ठा bundle_priv अणु
	/* Must be first */
	काष्ठा bundle_alloc_head alloc_head;
	काष्ठा bundle_alloc_head *allocated_mem;
	माप_प्रकार पूर्णांकernal_avail;
	माप_प्रकार पूर्णांकernal_used;

	काष्ठा radix_tree_root *radix;
	स्थिर काष्ठा uverbs_api_ioctl_method *method_elm;
	व्योम __rcu **radix_slots;
	अचिन्हित दीर्घ radix_slots_len;
	u32 method_key;

	काष्ठा ib_uverbs_attr __user *user_attrs;
	काष्ठा ib_uverbs_attr *uattrs;

	DECLARE_BITMAP(uobj_finalize, UVERBS_API_ATTR_BKEY_LEN);
	DECLARE_BITMAP(spec_finalize, UVERBS_API_ATTR_BKEY_LEN);
	DECLARE_BITMAP(uobj_hw_obj_valid, UVERBS_API_ATTR_BKEY_LEN);

	/*
	 * Must be last. bundle ends in a flex array which overlaps
	 * पूर्णांकernal_buffer.
	 */
	काष्ठा uverbs_attr_bundle bundle;
	u64 पूर्णांकernal_buffer[32];
पूर्ण;

/*
 * Each method has an असलolute minimum amount of memory it needs to allocate,
 * precompute that amount and determine अगर the onstack memory can be used or
 * अगर allocation is need.
 */
व्योम uapi_compute_bundle_size(काष्ठा uverbs_api_ioctl_method *method_elm,
			      अचिन्हित पूर्णांक num_attrs)
अणु
	काष्ठा bundle_priv *pbundle;
	माप_प्रकार bundle_size =
		दुरत्व(काष्ठा bundle_priv, पूर्णांकernal_buffer) +
		माप(*pbundle->bundle.attrs) * method_elm->key_biपंचांगap_len +
		माप(*pbundle->uattrs) * num_attrs;

	method_elm->use_stack = bundle_size <= माप(*pbundle);
	method_elm->bundle_size =
		ALIGN(bundle_size + 256, माप(*pbundle->पूर्णांकernal_buffer));

	/* Do not want order-2 allocations क्रम this. */
	WARN_ON_ONCE(method_elm->bundle_size > PAGE_SIZE);
पूर्ण

/**
 * _uverbs_alloc() - Quickly allocate memory क्रम use with a bundle
 * @bundle: The bundle
 * @size: Number of bytes to allocate
 * @flags: Allocator flags
 *
 * The bundle allocator is पूर्णांकended क्रम allocations that are connected with
 * processing the प्रणाली call related to the bundle. The allocated memory is
 * always मुक्तd once the प्रणाली call completes, and cannot be मुक्तd any other
 * way.
 *
 * This tries to use a small pool of pre-allocated memory क्रम perक्रमmance.
 */
__दो_स्मृति व्योम *_uverbs_alloc(काष्ठा uverbs_attr_bundle *bundle, माप_प्रकार size,
			     gfp_t flags)
अणु
	काष्ठा bundle_priv *pbundle =
		container_of(bundle, काष्ठा bundle_priv, bundle);
	माप_प्रकार new_used;
	व्योम *res;

	अगर (check_add_overflow(size, pbundle->पूर्णांकernal_used, &new_used))
		वापस ERR_PTR(-EOVERFLOW);

	अगर (new_used > pbundle->पूर्णांकernal_avail) अणु
		काष्ठा bundle_alloc_head *buf;

		buf = kvदो_स्मृति(काष्ठा_size(buf, data, size), flags);
		अगर (!buf)
			वापस ERR_PTR(-ENOMEM);
		buf->next = pbundle->allocated_mem;
		pbundle->allocated_mem = buf;
		वापस buf->data;
	पूर्ण

	res = (व्योम *)pbundle->पूर्णांकernal_buffer + pbundle->पूर्णांकernal_used;
	pbundle->पूर्णांकernal_used =
		ALIGN(new_used, माप(*pbundle->पूर्णांकernal_buffer));
	अगर (want_init_on_alloc(flags))
		स_रखो(res, 0, size);
	वापस res;
पूर्ण
EXPORT_SYMBOL(_uverbs_alloc);

अटल bool uverbs_is_attr_cleared(स्थिर काष्ठा ib_uverbs_attr *uattr,
				   u16 len)
अणु
	अगर (uattr->len > माप_field(काष्ठा ib_uverbs_attr, data))
		वापस ib_is_buffer_cleared(u64_to_user_ptr(uattr->data) + len,
					    uattr->len - len);

	वापस !स_प्रथम_inv((स्थिर व्योम *)&uattr->data + len,
			   0, uattr->len - len);
पूर्ण

अटल पूर्णांक uverbs_set_output(स्थिर काष्ठा uverbs_attr_bundle *bundle,
			     स्थिर काष्ठा uverbs_attr *attr)
अणु
	काष्ठा bundle_priv *pbundle =
		container_of(bundle, काष्ठा bundle_priv, bundle);
	u16 flags;

	flags = pbundle->uattrs[attr->ptr_attr.uattr_idx].flags |
		UVERBS_ATTR_F_VALID_OUTPUT;
	अगर (put_user(flags,
		     &pbundle->user_attrs[attr->ptr_attr.uattr_idx].flags))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक uverbs_process_idrs_array(काष्ठा bundle_priv *pbundle,
				     स्थिर काष्ठा uverbs_api_attr *attr_uapi,
				     काष्ठा uverbs_objs_arr_attr *attr,
				     काष्ठा ib_uverbs_attr *uattr,
				     u32 attr_bkey)
अणु
	स्थिर काष्ठा uverbs_attr_spec *spec = &attr_uapi->spec;
	माप_प्रकार array_len;
	u32 *idr_vals;
	पूर्णांक ret = 0;
	माप_प्रकार i;

	अगर (uattr->attr_data.reserved)
		वापस -EINVAL;

	अगर (uattr->len % माप(u32))
		वापस -EINVAL;

	array_len = uattr->len / माप(u32);
	अगर (array_len < spec->u2.objs_arr.min_len ||
	    array_len > spec->u2.objs_arr.max_len)
		वापस -EINVAL;

	attr->uobjects =
		uverbs_alloc(&pbundle->bundle,
			     array_size(array_len, माप(*attr->uobjects)));
	अगर (IS_ERR(attr->uobjects))
		वापस PTR_ERR(attr->uobjects);

	/*
	 * Since idr is 4B and *uobjects is >= 4B, we can use attr->uobjects
	 * to store idrs array and aव्योम additional memory allocation. The
	 * idrs array is offset to the end of the uobjects array so we will be
	 * able to पढ़ो idr and replace with a poपूर्णांकer.
	 */
	idr_vals = (u32 *)(attr->uobjects + array_len) - array_len;

	अगर (uattr->len > माप(uattr->data)) अणु
		ret = copy_from_user(idr_vals, u64_to_user_ptr(uattr->data),
				     uattr->len);
		अगर (ret)
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		स_नकल(idr_vals, &uattr->data, uattr->len);
	पूर्ण

	क्रम (i = 0; i != array_len; i++) अणु
		attr->uobjects[i] = uverbs_get_uobject_from_file(
			spec->u2.objs_arr.obj_type, spec->u2.objs_arr.access,
			idr_vals[i], &pbundle->bundle);
		अगर (IS_ERR(attr->uobjects[i])) अणु
			ret = PTR_ERR(attr->uobjects[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	attr->len = i;
	__set_bit(attr_bkey, pbundle->spec_finalize);
	वापस ret;
पूर्ण

अटल व्योम uverbs_मुक्त_idrs_array(स्थिर काष्ठा uverbs_api_attr *attr_uapi,
				   काष्ठा uverbs_objs_arr_attr *attr,
				   bool commit,
				   काष्ठा uverbs_attr_bundle *attrs)
अणु
	स्थिर काष्ठा uverbs_attr_spec *spec = &attr_uapi->spec;
	माप_प्रकार i;

	क्रम (i = 0; i != attr->len; i++)
		uverbs_finalize_object(attr->uobjects[i],
				       spec->u2.objs_arr.access, false, commit,
				       attrs);
पूर्ण

अटल पूर्णांक uverbs_process_attr(काष्ठा bundle_priv *pbundle,
			       स्थिर काष्ठा uverbs_api_attr *attr_uapi,
			       काष्ठा ib_uverbs_attr *uattr, u32 attr_bkey)
अणु
	स्थिर काष्ठा uverbs_attr_spec *spec = &attr_uapi->spec;
	काष्ठा uverbs_attr *e = &pbundle->bundle.attrs[attr_bkey];
	स्थिर काष्ठा uverbs_attr_spec *val_spec = spec;
	काष्ठा uverbs_obj_attr *o_attr;

	चयन (spec->type) अणु
	हाल UVERBS_ATTR_TYPE_ENUM_IN:
		अगर (uattr->attr_data.क्रमागत_data.elem_id >= spec->u.क्रमागत_def.num_elems)
			वापस -EOPNOTSUPP;

		अगर (uattr->attr_data.क्रमागत_data.reserved)
			वापस -EINVAL;

		val_spec = &spec->u2.क्रमागत_def.ids[uattr->attr_data.क्रमागत_data.elem_id];

		/* Currently we only support PTR_IN based क्रमागतs */
		अगर (val_spec->type != UVERBS_ATTR_TYPE_PTR_IN)
			वापस -EOPNOTSUPP;

		e->ptr_attr.क्रमागत_id = uattr->attr_data.क्रमागत_data.elem_id;
		fallthrough;
	हाल UVERBS_ATTR_TYPE_PTR_IN:
		/* Ensure that any data provided by userspace beyond the known
		 * काष्ठा is zero. Userspace that knows how to use some future
		 * दीर्घer काष्ठा will fail here अगर used with an old kernel and
		 * non-zero content, making ABI compat/discovery simpler.
		 */
		अगर (uattr->len > val_spec->u.ptr.len &&
		    val_spec->zero_trailing &&
		    !uverbs_is_attr_cleared(uattr, val_spec->u.ptr.len))
			वापस -EOPNOTSUPP;

		fallthrough;
	हाल UVERBS_ATTR_TYPE_PTR_OUT:
		अगर (uattr->len < val_spec->u.ptr.min_len ||
		    (!val_spec->zero_trailing &&
		     uattr->len > val_spec->u.ptr.len))
			वापस -EINVAL;

		अगर (spec->type != UVERBS_ATTR_TYPE_ENUM_IN &&
		    uattr->attr_data.reserved)
			वापस -EINVAL;

		e->ptr_attr.uattr_idx = uattr - pbundle->uattrs;
		e->ptr_attr.len = uattr->len;

		अगर (val_spec->alloc_and_copy && !uverbs_attr_ptr_is_अंतरभूत(e)) अणु
			व्योम *p;

			p = uverbs_alloc(&pbundle->bundle, uattr->len);
			अगर (IS_ERR(p))
				वापस PTR_ERR(p);

			e->ptr_attr.ptr = p;

			अगर (copy_from_user(p, u64_to_user_ptr(uattr->data),
					   uattr->len))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			e->ptr_attr.data = uattr->data;
		पूर्ण
		अवरोध;

	हाल UVERBS_ATTR_TYPE_IDR:
	हाल UVERBS_ATTR_TYPE_FD:
		अगर (uattr->attr_data.reserved)
			वापस -EINVAL;

		अगर (uattr->len != 0)
			वापस -EINVAL;

		o_attr = &e->obj_attr;
		o_attr->attr_elm = attr_uapi;

		/*
		 * The type of uattr->data is u64 क्रम UVERBS_ATTR_TYPE_IDR and
		 * s64 क्रम UVERBS_ATTR_TYPE_FD. We can cast the u64 to s64
		 * here without caring about truncation as we know that the
		 * IDR implementation today rejects negative IDs
		 */
		o_attr->uobject = uverbs_get_uobject_from_file(
			spec->u.obj.obj_type, spec->u.obj.access,
			uattr->data_s64, &pbundle->bundle);
		अगर (IS_ERR(o_attr->uobject))
			वापस PTR_ERR(o_attr->uobject);
		__set_bit(attr_bkey, pbundle->uobj_finalize);

		अगर (spec->u.obj.access == UVERBS_ACCESS_NEW) अणु
			अचिन्हित पूर्णांक uattr_idx = uattr - pbundle->uattrs;
			s64 id = o_attr->uobject->id;

			/* Copy the allocated id to the user-space */
			अगर (put_user(id, &pbundle->user_attrs[uattr_idx].data))
				वापस -EFAULT;
		पूर्ण

		अवरोध;

	हाल UVERBS_ATTR_TYPE_IDRS_ARRAY:
		वापस uverbs_process_idrs_array(pbundle, attr_uapi,
						 &e->objs_arr_attr, uattr,
						 attr_bkey);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We search the radix tree with the method prefix and now we want to fast
 * search the suffix bits to get a particular attribute poपूर्णांकer. It is not
 * totally clear to me अगर this अवरोधs the radix tree encasulation or not, but
 * it uses the iter data to determine अगर the method iter poपूर्णांकs at the same
 * chunk that will store the attribute, अगर so it just derefs it directly. By
 * स्थिरruction in most kernel configs the method and attrs will all fit in a
 * single radix chunk, so in most हालs this will have no search. Other हालs
 * this falls back to a full search.
 */
अटल व्योम __rcu **uapi_get_attr_क्रम_method(काष्ठा bundle_priv *pbundle,
					     u32 attr_key)
अणु
	व्योम __rcu **slot;

	अगर (likely(attr_key < pbundle->radix_slots_len)) अणु
		व्योम *entry;

		slot = pbundle->radix_slots + attr_key;
		entry = rcu_dereference_raw(*slot);
		अगर (likely(!radix_tree_is_पूर्णांकernal_node(entry) && entry))
			वापस slot;
	पूर्ण

	वापस radix_tree_lookup_slot(pbundle->radix,
				      pbundle->method_key | attr_key);
पूर्ण

अटल पूर्णांक uverbs_set_attr(काष्ठा bundle_priv *pbundle,
			   काष्ठा ib_uverbs_attr *uattr)
अणु
	u32 attr_key = uapi_key_attr(uattr->attr_id);
	u32 attr_bkey = uapi_bkey_attr(attr_key);
	स्थिर काष्ठा uverbs_api_attr *attr;
	व्योम __rcu **slot;
	पूर्णांक ret;

	slot = uapi_get_attr_क्रम_method(pbundle, attr_key);
	अगर (!slot) अणु
		/*
		 * Kernel करोes not support the attribute but user-space says it
		 * is mandatory
		 */
		अगर (uattr->flags & UVERBS_ATTR_F_MANDATORY)
			वापस -EPROTONOSUPPORT;
		वापस 0;
	पूर्ण
	attr = rcu_dereference_रक्षित(*slot, true);

	/* Reject duplicate attributes from user-space */
	अगर (test_bit(attr_bkey, pbundle->bundle.attr_present))
		वापस -EINVAL;

	ret = uverbs_process_attr(pbundle, attr, uattr, attr_bkey);
	अगर (ret)
		वापस ret;

	__set_bit(attr_bkey, pbundle->bundle.attr_present);

	वापस 0;
पूर्ण

अटल पूर्णांक ib_uverbs_run_method(काष्ठा bundle_priv *pbundle,
				अचिन्हित पूर्णांक num_attrs)
अणु
	पूर्णांक (*handler)(काष्ठा uverbs_attr_bundle *attrs);
	माप_प्रकार uattrs_size = array_size(माप(*pbundle->uattrs), num_attrs);
	अचिन्हित पूर्णांक destroy_bkey = pbundle->method_elm->destroy_bkey;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* See uverbs_disassociate_api() */
	handler = srcu_dereference(
		pbundle->method_elm->handler,
		&pbundle->bundle.ufile->device->disassociate_srcu);
	अगर (!handler)
		वापस -EIO;

	pbundle->uattrs = uverbs_alloc(&pbundle->bundle, uattrs_size);
	अगर (IS_ERR(pbundle->uattrs))
		वापस PTR_ERR(pbundle->uattrs);
	अगर (copy_from_user(pbundle->uattrs, pbundle->user_attrs, uattrs_size))
		वापस -EFAULT;

	क्रम (i = 0; i != num_attrs; i++) अणु
		ret = uverbs_set_attr(pbundle, &pbundle->uattrs[i]);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण

	/* User space did not provide all the mandatory attributes */
	अगर (unlikely(!biपंचांगap_subset(pbundle->method_elm->attr_mandatory,
				    pbundle->bundle.attr_present,
				    pbundle->method_elm->key_biपंचांगap_len)))
		वापस -EINVAL;

	अगर (pbundle->method_elm->has_udata)
		uverbs_fill_udata(&pbundle->bundle,
				  &pbundle->bundle.driver_udata,
				  UVERBS_ATTR_UHW_IN, UVERBS_ATTR_UHW_OUT);
	अन्यथा
		pbundle->bundle.driver_udata = (काष्ठा ib_udata)अणुपूर्ण;

	अगर (destroy_bkey != UVERBS_API_ATTR_BKEY_LEN) अणु
		काष्ठा uverbs_obj_attr *destroy_attr =
			&pbundle->bundle.attrs[destroy_bkey].obj_attr;

		ret = uobj_destroy(destroy_attr->uobject, &pbundle->bundle);
		अगर (ret)
			वापस ret;
		__clear_bit(destroy_bkey, pbundle->uobj_finalize);

		ret = handler(&pbundle->bundle);
		uobj_put_destroy(destroy_attr->uobject);
	पूर्ण अन्यथा अणु
		ret = handler(&pbundle->bundle);
	पूर्ण

	/*
	 * Until the drivers are revised to use the bundle directly we have to
	 * assume that the driver wrote to its UHW_OUT and flag userspace
	 * appropriately.
	 */
	अगर (!ret && pbundle->method_elm->has_udata) अणु
		स्थिर काष्ठा uverbs_attr *attr =
			uverbs_attr_get(&pbundle->bundle, UVERBS_ATTR_UHW_OUT);

		अगर (!IS_ERR(attr))
			ret = uverbs_set_output(&pbundle->bundle, attr);
	पूर्ण

	/*
	 * EPROTONOSUPPORT is ONLY to be वापसed अगर the ioctl framework can
	 * not invoke the method because the request is not supported.  No
	 * other हालs should वापस this code.
	 */
	अगर (WARN_ON_ONCE(ret == -EPROTONOSUPPORT))
		वापस -EINVAL;

	वापस ret;
पूर्ण

अटल व्योम bundle_destroy(काष्ठा bundle_priv *pbundle, bool commit)
अणु
	अचिन्हित पूर्णांक key_biपंचांगap_len = pbundle->method_elm->key_biपंचांगap_len;
	काष्ठा bundle_alloc_head *memblock;
	अचिन्हित पूर्णांक i;

	/* fast path क्रम simple uobjects */
	i = -1;
	जबतक ((i = find_next_bit(pbundle->uobj_finalize, key_biपंचांगap_len,
				  i + 1)) < key_biपंचांगap_len) अणु
		काष्ठा uverbs_attr *attr = &pbundle->bundle.attrs[i];

		uverbs_finalize_object(
			attr->obj_attr.uobject,
			attr->obj_attr.attr_elm->spec.u.obj.access,
			test_bit(i, pbundle->uobj_hw_obj_valid),
			commit,
			&pbundle->bundle);
	पूर्ण

	i = -1;
	जबतक ((i = find_next_bit(pbundle->spec_finalize, key_biपंचांगap_len,
				  i + 1)) < key_biपंचांगap_len) अणु
		काष्ठा uverbs_attr *attr = &pbundle->bundle.attrs[i];
		स्थिर काष्ठा uverbs_api_attr *attr_uapi;
		व्योम __rcu **slot;

		slot = uapi_get_attr_क्रम_method(
			pbundle,
			pbundle->method_key | uapi_bkey_to_key_attr(i));
		अगर (WARN_ON(!slot))
			जारी;

		attr_uapi = rcu_dereference_रक्षित(*slot, true);

		अगर (attr_uapi->spec.type == UVERBS_ATTR_TYPE_IDRS_ARRAY) अणु
			uverbs_मुक्त_idrs_array(attr_uapi, &attr->objs_arr_attr,
					       commit, &pbundle->bundle);
		पूर्ण
	पूर्ण

	क्रम (memblock = pbundle->allocated_mem; memblock;) अणु
		काष्ठा bundle_alloc_head *पंचांगp = memblock;

		memblock = memblock->next;
		kvमुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल पूर्णांक ib_uverbs_cmd_verbs(काष्ठा ib_uverbs_file *ufile,
			       काष्ठा ib_uverbs_ioctl_hdr *hdr,
			       काष्ठा ib_uverbs_attr __user *user_attrs)
अणु
	स्थिर काष्ठा uverbs_api_ioctl_method *method_elm;
	काष्ठा uverbs_api *uapi = ufile->device->uapi;
	काष्ठा radix_tree_iter attrs_iter;
	काष्ठा bundle_priv *pbundle;
	काष्ठा bundle_priv onstack;
	व्योम __rcu **slot;
	पूर्णांक ret;

	अगर (unlikely(hdr->driver_id != uapi->driver_id))
		वापस -EINVAL;

	slot = radix_tree_iter_lookup(
		&uapi->radix, &attrs_iter,
		uapi_key_obj(hdr->object_id) |
			uapi_key_ioctl_method(hdr->method_id));
	अगर (unlikely(!slot))
		वापस -EPROTONOSUPPORT;
	method_elm = rcu_dereference_रक्षित(*slot, true);

	अगर (!method_elm->use_stack) अणु
		pbundle = kदो_स्मृति(method_elm->bundle_size, GFP_KERNEL);
		अगर (!pbundle)
			वापस -ENOMEM;
		pbundle->पूर्णांकernal_avail =
			method_elm->bundle_size -
			दुरत्व(काष्ठा bundle_priv, पूर्णांकernal_buffer);
		pbundle->alloc_head.next = शून्य;
		pbundle->allocated_mem = &pbundle->alloc_head;
	पूर्ण अन्यथा अणु
		pbundle = &onstack;
		pbundle->पूर्णांकernal_avail = माप(pbundle->पूर्णांकernal_buffer);
		pbundle->allocated_mem = शून्य;
	पूर्ण

	/* Space क्रम the pbundle->bundle.attrs flex array */
	pbundle->method_elm = method_elm;
	pbundle->method_key = attrs_iter.index;
	pbundle->bundle.ufile = ufile;
	pbundle->bundle.context = शून्य; /* only valid अगर bundle has uobject */
	pbundle->radix = &uapi->radix;
	pbundle->radix_slots = slot;
	pbundle->radix_slots_len = radix_tree_chunk_size(&attrs_iter);
	pbundle->user_attrs = user_attrs;

	pbundle->पूर्णांकernal_used = ALIGN(pbundle->method_elm->key_biपंचांगap_len *
					       माप(*pbundle->bundle.attrs),
				       माप(*pbundle->पूर्णांकernal_buffer));
	स_रखो(pbundle->bundle.attr_present, 0,
	       माप(pbundle->bundle.attr_present));
	स_रखो(pbundle->uobj_finalize, 0, माप(pbundle->uobj_finalize));
	स_रखो(pbundle->spec_finalize, 0, माप(pbundle->spec_finalize));
	स_रखो(pbundle->uobj_hw_obj_valid, 0,
	       माप(pbundle->uobj_hw_obj_valid));

	ret = ib_uverbs_run_method(pbundle, hdr->num_attrs);
	bundle_destroy(pbundle, ret == 0);
	वापस ret;
पूर्ण

दीर्घ ib_uverbs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ib_uverbs_file *file = filp->निजी_data;
	काष्ठा ib_uverbs_ioctl_hdr __user *user_hdr =
		(काष्ठा ib_uverbs_ioctl_hdr __user *)arg;
	काष्ठा ib_uverbs_ioctl_hdr hdr;
	पूर्णांक srcu_key;
	पूर्णांक err;

	अगर (unlikely(cmd != RDMA_VERBS_IOCTL))
		वापस -ENOIOCTLCMD;

	err = copy_from_user(&hdr, user_hdr, माप(hdr));
	अगर (err)
		वापस -EFAULT;

	अगर (hdr.length > PAGE_SIZE ||
	    hdr.length != काष्ठा_size(&hdr, attrs, hdr.num_attrs))
		वापस -EINVAL;

	अगर (hdr.reserved1 || hdr.reserved2)
		वापस -EPROTONOSUPPORT;

	srcu_key = srcu_पढ़ो_lock(&file->device->disassociate_srcu);
	err = ib_uverbs_cmd_verbs(file, &hdr, user_hdr->attrs);
	srcu_पढ़ो_unlock(&file->device->disassociate_srcu, srcu_key);
	वापस err;
पूर्ण

पूर्णांक uverbs_get_flags64(u64 *to, स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
		       माप_प्रकार idx, u64 allowed_bits)
अणु
	स्थिर काष्ठा uverbs_attr *attr;
	u64 flags;

	attr = uverbs_attr_get(attrs_bundle, idx);
	/* Missing attribute means 0 flags */
	अगर (IS_ERR(attr)) अणु
		*to = 0;
		वापस 0;
	पूर्ण

	/*
	 * New userspace code should use 8 bytes to pass flags, but we
	 * transparently support old userspaces that were using 4 bytes as
	 * well.
	 */
	अगर (attr->ptr_attr.len == 8)
		flags = attr->ptr_attr.data;
	अन्यथा अगर (attr->ptr_attr.len == 4)
		flags = *(u32 *)&attr->ptr_attr.data;
	अन्यथा
		वापस -EINVAL;

	अगर (flags & ~allowed_bits)
		वापस -EINVAL;

	*to = flags;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(uverbs_get_flags64);

पूर्णांक uverbs_get_flags32(u32 *to, स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
		       माप_प्रकार idx, u64 allowed_bits)
अणु
	u64 flags;
	पूर्णांक ret;

	ret = uverbs_get_flags64(&flags, attrs_bundle, idx, allowed_bits);
	अगर (ret)
		वापस ret;

	अगर (flags > U32_MAX)
		वापस -EINVAL;
	*to = flags;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(uverbs_get_flags32);

/*
 * Fill a ib_udata काष्ठा (core or uhw) using the given attribute IDs.
 * This is primarily used to convert the UVERBS_ATTR_UHW() पूर्णांकo the
 * ib_udata क्रमmat used by the drivers.
 */
व्योम uverbs_fill_udata(काष्ठा uverbs_attr_bundle *bundle,
		       काष्ठा ib_udata *udata, अचिन्हित पूर्णांक attr_in,
		       अचिन्हित पूर्णांक attr_out)
अणु
	काष्ठा bundle_priv *pbundle =
		container_of(bundle, काष्ठा bundle_priv, bundle);
	स्थिर काष्ठा uverbs_attr *in =
		uverbs_attr_get(&pbundle->bundle, attr_in);
	स्थिर काष्ठा uverbs_attr *out =
		uverbs_attr_get(&pbundle->bundle, attr_out);

	अगर (!IS_ERR(in)) अणु
		udata->inlen = in->ptr_attr.len;
		अगर (uverbs_attr_ptr_is_अंतरभूत(in))
			udata->inbuf =
				&pbundle->user_attrs[in->ptr_attr.uattr_idx]
					 .data;
		अन्यथा
			udata->inbuf = u64_to_user_ptr(in->ptr_attr.data);
	पूर्ण अन्यथा अणु
		udata->inbuf = शून्य;
		udata->inlen = 0;
	पूर्ण

	अगर (!IS_ERR(out)) अणु
		udata->outbuf = u64_to_user_ptr(out->ptr_attr.data);
		udata->outlen = out->ptr_attr.len;
	पूर्ण अन्यथा अणु
		udata->outbuf = शून्य;
		udata->outlen = 0;
	पूर्ण
पूर्ण

पूर्णांक uverbs_copy_to(स्थिर काष्ठा uverbs_attr_bundle *bundle, माप_प्रकार idx,
		   स्थिर व्योम *from, माप_प्रकार size)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(bundle, idx);
	माप_प्रकार min_size;

	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	min_size = min_t(माप_प्रकार, attr->ptr_attr.len, size);
	अगर (copy_to_user(u64_to_user_ptr(attr->ptr_attr.data), from, min_size))
		वापस -EFAULT;

	वापस uverbs_set_output(bundle, attr);
पूर्ण
EXPORT_SYMBOL(uverbs_copy_to);


/*
 * This is only used अगर the caller has directly used copy_to_use to ग_लिखो the
 * data.  It संकेतs to user space that the buffer is filled in.
 */
पूर्णांक uverbs_output_written(स्थिर काष्ठा uverbs_attr_bundle *bundle, माप_प्रकार idx)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(bundle, idx);

	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	वापस uverbs_set_output(bundle, attr);
पूर्ण

पूर्णांक _uverbs_get_स्थिर_चिन्हित(s64 *to,
			     स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
			     माप_प्रकार idx, s64 lower_bound, u64 upper_bound,
			     s64  *def_val)
अणु
	स्थिर काष्ठा uverbs_attr *attr;

	attr = uverbs_attr_get(attrs_bundle, idx);
	अगर (IS_ERR(attr)) अणु
		अगर ((PTR_ERR(attr) != -ENOENT) || !def_val)
			वापस PTR_ERR(attr);

		*to = *def_val;
	पूर्ण अन्यथा अणु
		*to = attr->ptr_attr.data;
	पूर्ण

	अगर (*to < lower_bound || (*to > 0 && (u64)*to > upper_bound))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(_uverbs_get_स्थिर_चिन्हित);

पूर्णांक _uverbs_get_स्थिर_अचिन्हित(u64 *to,
			       स्थिर काष्ठा uverbs_attr_bundle *attrs_bundle,
			       माप_प्रकार idx, u64 upper_bound, u64 *def_val)
अणु
	स्थिर काष्ठा uverbs_attr *attr;

	attr = uverbs_attr_get(attrs_bundle, idx);
	अगर (IS_ERR(attr)) अणु
		अगर ((PTR_ERR(attr) != -ENOENT) || !def_val)
			वापस PTR_ERR(attr);

		*to = *def_val;
	पूर्ण अन्यथा अणु
		*to = attr->ptr_attr.data;
	पूर्ण

	अगर (*to > upper_bound)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(_uverbs_get_स्थिर_अचिन्हित);

पूर्णांक uverbs_copy_to_काष्ठा_or_zero(स्थिर काष्ठा uverbs_attr_bundle *bundle,
				  माप_प्रकार idx, स्थिर व्योम *from, माप_प्रकार size)
अणु
	स्थिर काष्ठा uverbs_attr *attr = uverbs_attr_get(bundle, idx);

	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	अगर (size < attr->ptr_attr.len) अणु
		अगर (clear_user(u64_to_user_ptr(attr->ptr_attr.data) + size,
			       attr->ptr_attr.len - size))
			वापस -EFAULT;
	पूर्ण
	वापस uverbs_copy_to(bundle, idx, from, size);
पूर्ण
EXPORT_SYMBOL(uverbs_copy_to_काष्ठा_or_zero);

/* Once called an पात will call through to the type's destroy_hw() */
व्योम uverbs_finalize_uobj_create(स्थिर काष्ठा uverbs_attr_bundle *bundle,
				 u16 idx)
अणु
	काष्ठा bundle_priv *pbundle =
		container_of(bundle, काष्ठा bundle_priv, bundle);

	__set_bit(uapi_bkey_attr(uapi_key_attr(idx)),
		  pbundle->uobj_hw_obj_valid);
पूर्ण
EXPORT_SYMBOL(uverbs_finalize_uobj_create);
