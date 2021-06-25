<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <linux/overflow.h>
#समावेश <rdma/uverbs_std_types.h>
#समावेश "rdma_core.h"
#समावेश "uverbs.h"
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/opa_addr.h>
#समावेश <rdma/ib_cache.h>

/*
 * This ioctl method allows calling any defined ग_लिखो or ग_लिखो_ex
 * handler. This essentially replaces the hdr/ex_hdr प्रणाली with the ioctl
 * marshalling, and brings the non-ex path पूर्णांकo the same marshalling as the ex
 * path.
 */
अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_INVOKE_WRITE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा uverbs_api *uapi = attrs->ufile->device->uapi;
	स्थिर काष्ठा uverbs_api_ग_लिखो_method *method_elm;
	u32 cmd;
	पूर्णांक rc;

	rc = uverbs_get_स्थिर(&cmd, attrs, UVERBS_ATTR_WRITE_CMD);
	अगर (rc)
		वापस rc;

	method_elm = uapi_get_method(uapi, cmd);
	अगर (IS_ERR(method_elm))
		वापस PTR_ERR(method_elm);

	uverbs_fill_udata(attrs, &attrs->ucore, UVERBS_ATTR_CORE_IN,
			  UVERBS_ATTR_CORE_OUT);

	अगर (attrs->ucore.inlen < method_elm->req_size ||
	    attrs->ucore.outlen < method_elm->resp_size)
		वापस -ENOSPC;

	attrs->uobject = शून्य;
	rc = method_elm->handler(attrs);
	अगर (attrs->uobject)
		uverbs_finalize_object(attrs->uobject, UVERBS_ACCESS_NEW, true,
				       !rc, attrs);
	वापस rc;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(UVERBS_METHOD_INVOKE_WRITE,
			    UVERBS_ATTR_CONST_IN(UVERBS_ATTR_WRITE_CMD,
						 क्रमागत ib_uverbs_ग_लिखो_cmds,
						 UA_MANDATORY),
			    UVERBS_ATTR_PTR_IN(UVERBS_ATTR_CORE_IN,
					       UVERBS_ATTR_MIN_SIZE(माप(u32)),
					       UA_OPTIONAL),
			    UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_CORE_OUT,
						UVERBS_ATTR_MIN_SIZE(0),
						UA_OPTIONAL),
			    UVERBS_ATTR_UHW());

अटल uपूर्णांक32_t *
gather_objects_handle(काष्ठा ib_uverbs_file *ufile,
		      स्थिर काष्ठा uverbs_api_object *uapi_object,
		      काष्ठा uverbs_attr_bundle *attrs,
		      sमाप_प्रकार out_len,
		      u64 *total)
अणु
	u64 max_count = out_len / माप(u32);
	काष्ठा ib_uobject *obj;
	u64 count = 0;
	u32 *handles;

	/* Allocated memory that cannot page out where we gather
	 * all object ids under a spin_lock.
	 */
	handles = uverbs_zalloc(attrs, out_len);
	अगर (IS_ERR(handles))
		वापस handles;

	spin_lock_irq(&ufile->uobjects_lock);
	list_क्रम_each_entry(obj, &ufile->uobjects, list) अणु
		u32 obj_id = obj->id;

		अगर (obj->uapi_object != uapi_object)
			जारी;

		अगर (count >= max_count)
			अवरोध;

		handles[count] = obj_id;
		count++;
	पूर्ण
	spin_unlock_irq(&ufile->uobjects_lock);

	*total = count;
	वापस handles;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_INFO_HANDLES)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	स्थिर काष्ठा uverbs_api_object *uapi_object;
	sमाप_प्रकार out_len;
	u64 total = 0;
	u16 object_id;
	u32 *handles;
	पूर्णांक ret;

	out_len = uverbs_attr_get_len(attrs, UVERBS_ATTR_INFO_HANDLES_LIST);
	अगर (out_len <= 0 || (out_len % माप(u32) != 0))
		वापस -EINVAL;

	ret = uverbs_get_स्थिर(&object_id, attrs, UVERBS_ATTR_INFO_OBJECT_ID);
	अगर (ret)
		वापस ret;

	uapi_object = uapi_get_object(attrs->ufile->device->uapi, object_id);
	अगर (IS_ERR(uapi_object))
		वापस PTR_ERR(uapi_object);

	handles = gather_objects_handle(attrs->ufile, uapi_object, attrs,
					out_len, &total);
	अगर (IS_ERR(handles))
		वापस PTR_ERR(handles);

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_INFO_HANDLES_LIST, handles,
			     माप(u32) * total);
	अगर (ret)
		जाओ err;

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_INFO_TOTAL_HANDLES, &total,
			     माप(total));
err:
	वापस ret;
पूर्ण

व्योम copy_port_attr_to_resp(काष्ठा ib_port_attr *attr,
			    काष्ठा ib_uverbs_query_port_resp *resp,
			    काष्ठा ib_device *ib_dev, u8 port_num)
अणु
	resp->state = attr->state;
	resp->max_mtu = attr->max_mtu;
	resp->active_mtu = attr->active_mtu;
	resp->gid_tbl_len = attr->gid_tbl_len;
	resp->port_cap_flags = make_port_cap_flags(attr);
	resp->max_msg_sz = attr->max_msg_sz;
	resp->bad_pkey_cntr = attr->bad_pkey_cntr;
	resp->qkey_viol_cntr = attr->qkey_viol_cntr;
	resp->pkey_tbl_len = attr->pkey_tbl_len;

	अगर (rdma_is_grh_required(ib_dev, port_num))
		resp->flags |= IB_UVERBS_QPF_GRH_REQUIRED;

	अगर (rdma_cap_opa_ah(ib_dev, port_num)) अणु
		resp->lid = OPA_TO_IB_UCAST_LID(attr->lid);
		resp->sm_lid = OPA_TO_IB_UCAST_LID(attr->sm_lid);
	पूर्ण अन्यथा अणु
		resp->lid = ib_lid_cpu16(attr->lid);
		resp->sm_lid = ib_lid_cpu16(attr->sm_lid);
	पूर्ण

	resp->lmc = attr->lmc;
	resp->max_vl_num = attr->max_vl_num;
	resp->sm_sl = attr->sm_sl;
	resp->subnet_समयout = attr->subnet_समयout;
	resp->init_type_reply = attr->init_type_reply;
	resp->active_width = attr->active_width;
	/* This ABI needs to be extended to provide any speed more than IB_SPEED_NDR */
	resp->active_speed = min_t(u16, attr->active_speed, IB_SPEED_NDR);
	resp->phys_state = attr->phys_state;
	resp->link_layer = rdma_port_get_link_layer(ib_dev, port_num);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_QUERY_PORT)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_device *ib_dev;
	काष्ठा ib_port_attr attr = अणुपूर्ण;
	काष्ठा ib_uverbs_query_port_resp_ex resp = अणुपूर्ण;
	काष्ठा ib_ucontext *ucontext;
	पूर्णांक ret;
	u8 port_num;

	ucontext = ib_uverbs_get_ucontext(attrs);
	अगर (IS_ERR(ucontext))
		वापस PTR_ERR(ucontext);
	ib_dev = ucontext->device;

	/* FIXME: Extend the UAPI_DEF_OBJ_NEEDS_FN stuff.. */
	अगर (!ib_dev->ops.query_port)
		वापस -EOPNOTSUPP;

	ret = uverbs_get_स्थिर(&port_num, attrs,
			       UVERBS_ATTR_QUERY_PORT_PORT_NUM);
	अगर (ret)
		वापस ret;

	ret = ib_query_port(ib_dev, port_num, &attr);
	अगर (ret)
		वापस ret;

	copy_port_attr_to_resp(&attr, &resp.legacy_resp, ib_dev, port_num);
	resp.port_cap_flags2 = attr.port_cap_flags2;

	वापस uverbs_copy_to_काष्ठा_or_zero(attrs, UVERBS_ATTR_QUERY_PORT_RESP,
					     &resp, माप(resp));
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_GET_CONTEXT)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	u32 num_comp = attrs->ufile->device->num_comp_vectors;
	u64 core_support = IB_UVERBS_CORE_SUPPORT_OPTIONAL_MR_ACCESS;
	पूर्णांक ret;

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_GET_CONTEXT_NUM_COMP_VECTORS,
			     &num_comp, माप(num_comp));
	अगर (IS_UVERBS_COPY_ERR(ret))
		वापस ret;

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_GET_CONTEXT_CORE_SUPPORT,
			     &core_support, माप(core_support));
	अगर (IS_UVERBS_COPY_ERR(ret))
		वापस ret;

	ret = ib_alloc_ucontext(attrs);
	अगर (ret)
		वापस ret;
	ret = ib_init_ucontext(attrs);
	अगर (ret) अणु
		kमुक्त(attrs->context);
		attrs->context = शून्य;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_QUERY_CONTEXT)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	u64 core_support = IB_UVERBS_CORE_SUPPORT_OPTIONAL_MR_ACCESS;
	काष्ठा ib_ucontext *ucontext;
	काष्ठा ib_device *ib_dev;
	u32 num_comp;
	पूर्णांक ret;

	ucontext = ib_uverbs_get_ucontext(attrs);
	अगर (IS_ERR(ucontext))
		वापस PTR_ERR(ucontext);
	ib_dev = ucontext->device;

	अगर (!ib_dev->ops.query_ucontext)
		वापस -EOPNOTSUPP;

	num_comp = attrs->ufile->device->num_comp_vectors;
	ret = uverbs_copy_to(attrs, UVERBS_ATTR_QUERY_CONTEXT_NUM_COMP_VECTORS,
			     &num_comp, माप(num_comp));
	अगर (IS_UVERBS_COPY_ERR(ret))
		वापस ret;

	ret = uverbs_copy_to(attrs, UVERBS_ATTR_QUERY_CONTEXT_CORE_SUPPORT,
			     &core_support, माप(core_support));
	अगर (IS_UVERBS_COPY_ERR(ret))
		वापस ret;

	वापस ucontext->device->ops.query_ucontext(ucontext, attrs);
पूर्ण

अटल पूर्णांक copy_gid_entries_to_user(काष्ठा uverbs_attr_bundle *attrs,
				    काष्ठा ib_uverbs_gid_entry *entries,
				    माप_प्रकार num_entries, माप_प्रकार user_entry_size)
अणु
	स्थिर काष्ठा uverbs_attr *attr;
	व्योम __user *user_entries;
	माप_प्रकार copy_len;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (user_entry_size == माप(*entries)) अणु
		ret = uverbs_copy_to(attrs,
				     UVERBS_ATTR_QUERY_GID_TABLE_RESP_ENTRIES,
				     entries, माप(*entries) * num_entries);
		वापस ret;
	पूर्ण

	copy_len = min_t(माप_प्रकार, user_entry_size, माप(*entries));
	attr = uverbs_attr_get(attrs, UVERBS_ATTR_QUERY_GID_TABLE_RESP_ENTRIES);
	अगर (IS_ERR(attr))
		वापस PTR_ERR(attr);

	user_entries = u64_to_user_ptr(attr->ptr_attr.data);
	क्रम (i = 0; i < num_entries; i++) अणु
		अगर (copy_to_user(user_entries, entries, copy_len))
			वापस -EFAULT;

		अगर (user_entry_size > माप(*entries)) अणु
			अगर (clear_user(user_entries + माप(*entries),
				       user_entry_size - माप(*entries)))
				वापस -EFAULT;
		पूर्ण

		entries++;
		user_entries += user_entry_size;
	पूर्ण

	वापस uverbs_output_written(attrs,
				     UVERBS_ATTR_QUERY_GID_TABLE_RESP_ENTRIES);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_QUERY_GID_TABLE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_gid_entry *entries;
	काष्ठा ib_ucontext *ucontext;
	काष्ठा ib_device *ib_dev;
	माप_प्रकार user_entry_size;
	sमाप_प्रकार num_entries;
	पूर्णांक max_entries;
	u32 flags;
	पूर्णांक ret;

	ret = uverbs_get_flags32(&flags, attrs,
				 UVERBS_ATTR_QUERY_GID_TABLE_FLAGS, 0);
	अगर (ret)
		वापस ret;

	ret = uverbs_get_स्थिर(&user_entry_size, attrs,
			       UVERBS_ATTR_QUERY_GID_TABLE_ENTRY_SIZE);
	अगर (ret)
		वापस ret;

	अगर (!user_entry_size)
		वापस -EINVAL;

	max_entries = uverbs_attr_ptr_get_array_size(
		attrs, UVERBS_ATTR_QUERY_GID_TABLE_RESP_ENTRIES,
		user_entry_size);
	अगर (max_entries <= 0)
		वापस max_entries ?: -EINVAL;

	ucontext = ib_uverbs_get_ucontext(attrs);
	अगर (IS_ERR(ucontext))
		वापस PTR_ERR(ucontext);
	ib_dev = ucontext->device;

	entries = uverbs_kसुस्मृति(attrs, max_entries, माप(*entries));
	अगर (IS_ERR(entries))
		वापस PTR_ERR(entries);

	num_entries = rdma_query_gid_table(ib_dev, entries, max_entries);
	अगर (num_entries < 0)
		वापस -EINVAL;

	ret = copy_gid_entries_to_user(attrs, entries, num_entries,
				       user_entry_size);
	अगर (ret)
		वापस ret;

	ret = uverbs_copy_to(attrs,
			     UVERBS_ATTR_QUERY_GID_TABLE_RESP_NUM_ENTRIES,
			     &num_entries, माप(num_entries));
	वापस ret;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_QUERY_GID_ENTRY)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_gid_entry entry = अणुपूर्ण;
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	काष्ठा ib_ucontext *ucontext;
	काष्ठा ib_device *ib_dev;
	काष्ठा net_device *ndev;
	u32 gid_index;
	u32 port_num;
	u32 flags;
	पूर्णांक ret;

	ret = uverbs_get_flags32(&flags, attrs,
				 UVERBS_ATTR_QUERY_GID_ENTRY_FLAGS, 0);
	अगर (ret)
		वापस ret;

	ret = uverbs_get_स्थिर(&port_num, attrs,
			       UVERBS_ATTR_QUERY_GID_ENTRY_PORT);
	अगर (ret)
		वापस ret;

	ret = uverbs_get_स्थिर(&gid_index, attrs,
			       UVERBS_ATTR_QUERY_GID_ENTRY_GID_INDEX);
	अगर (ret)
		वापस ret;

	ucontext = ib_uverbs_get_ucontext(attrs);
	अगर (IS_ERR(ucontext))
		वापस PTR_ERR(ucontext);
	ib_dev = ucontext->device;

	अगर (!rdma_is_port_valid(ib_dev, port_num))
		वापस -EINVAL;

	gid_attr = rdma_get_gid_attr(ib_dev, port_num, gid_index);
	अगर (IS_ERR(gid_attr))
		वापस PTR_ERR(gid_attr);

	स_नकल(&entry.gid, &gid_attr->gid, माप(gid_attr->gid));
	entry.gid_index = gid_attr->index;
	entry.port_num = gid_attr->port_num;
	entry.gid_type = gid_attr->gid_type;

	rcu_पढ़ो_lock();
	ndev = rdma_पढ़ो_gid_attr_ndev_rcu(gid_attr);
	अगर (IS_ERR(ndev)) अणु
		अगर (PTR_ERR(ndev) != -ENODEV) अणु
			ret = PTR_ERR(ndev);
			rcu_पढ़ो_unlock();
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		entry.netdev_अगरindex = ndev->अगरindex;
	पूर्ण
	rcu_पढ़ो_unlock();

	ret = uverbs_copy_to_काष्ठा_or_zero(
		attrs, UVERBS_ATTR_QUERY_GID_ENTRY_RESP_ENTRY, &entry,
		माप(entry));
out:
	rdma_put_gid_attr(gid_attr);
	वापस ret;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_GET_CONTEXT,
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_GET_CONTEXT_NUM_COMP_VECTORS,
			    UVERBS_ATTR_TYPE(u32), UA_OPTIONAL),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_GET_CONTEXT_CORE_SUPPORT,
			    UVERBS_ATTR_TYPE(u64), UA_OPTIONAL),
	UVERBS_ATTR_UHW());

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_QUERY_CONTEXT,
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_QUERY_CONTEXT_NUM_COMP_VECTORS,
			    UVERBS_ATTR_TYPE(u32), UA_OPTIONAL),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_QUERY_CONTEXT_CORE_SUPPORT,
			    UVERBS_ATTR_TYPE(u64), UA_OPTIONAL));

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_INFO_HANDLES,
	/* Also includes any device specअगरic object ids */
	UVERBS_ATTR_CONST_IN(UVERBS_ATTR_INFO_OBJECT_ID,
			     क्रमागत uverbs_शेष_objects, UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_INFO_TOTAL_HANDLES,
			    UVERBS_ATTR_TYPE(u32), UA_OPTIONAL),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_INFO_HANDLES_LIST,
			    UVERBS_ATTR_MIN_SIZE(माप(u32)), UA_OPTIONAL));

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_QUERY_PORT,
	UVERBS_ATTR_CONST_IN(UVERBS_ATTR_QUERY_PORT_PORT_NUM, u8, UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(
		UVERBS_ATTR_QUERY_PORT_RESP,
		UVERBS_ATTR_STRUCT(काष्ठा ib_uverbs_query_port_resp_ex,
				   reserved),
		UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_QUERY_GID_TABLE,
	UVERBS_ATTR_CONST_IN(UVERBS_ATTR_QUERY_GID_TABLE_ENTRY_SIZE, u64,
			     UA_MANDATORY),
	UVERBS_ATTR_FLAGS_IN(UVERBS_ATTR_QUERY_GID_TABLE_FLAGS, u32,
			     UA_OPTIONAL),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_QUERY_GID_TABLE_RESP_ENTRIES,
			    UVERBS_ATTR_MIN_SIZE(0), UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_QUERY_GID_TABLE_RESP_NUM_ENTRIES,
			    UVERBS_ATTR_TYPE(u64), UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_QUERY_GID_ENTRY,
	UVERBS_ATTR_CONST_IN(UVERBS_ATTR_QUERY_GID_ENTRY_PORT, u32,
			     UA_MANDATORY),
	UVERBS_ATTR_CONST_IN(UVERBS_ATTR_QUERY_GID_ENTRY_GID_INDEX, u32,
			     UA_MANDATORY),
	UVERBS_ATTR_FLAGS_IN(UVERBS_ATTR_QUERY_GID_ENTRY_FLAGS, u32,
			     UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(UVERBS_ATTR_QUERY_GID_ENTRY_RESP_ENTRY,
			    UVERBS_ATTR_STRUCT(काष्ठा ib_uverbs_gid_entry,
					       netdev_अगरindex),
			    UA_MANDATORY));

DECLARE_UVERBS_GLOBAL_METHODS(UVERBS_OBJECT_DEVICE,
			      &UVERBS_METHOD(UVERBS_METHOD_GET_CONTEXT),
			      &UVERBS_METHOD(UVERBS_METHOD_INVOKE_WRITE),
			      &UVERBS_METHOD(UVERBS_METHOD_INFO_HANDLES),
			      &UVERBS_METHOD(UVERBS_METHOD_QUERY_PORT),
			      &UVERBS_METHOD(UVERBS_METHOD_QUERY_CONTEXT),
			      &UVERBS_METHOD(UVERBS_METHOD_QUERY_GID_TABLE),
			      &UVERBS_METHOD(UVERBS_METHOD_QUERY_GID_ENTRY));

स्थिर काष्ठा uapi_definition uverbs_def_obj_device[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_DEVICE),
	अणुपूर्ण,
पूर्ण;
