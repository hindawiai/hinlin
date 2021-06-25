<शैली गुरु>
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005-2017 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2005 PathScale, Inc. All rights reserved.
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

#अगर_अघोषित RDMA_CORE_H
#घोषणा RDMA_CORE_H

#समावेश <linux/idr.h>
#समावेश <rdma/uverbs_types.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <linux/mutex.h>

काष्ठा ib_uverbs_device;

व्योम uverbs_destroy_ufile_hw(काष्ठा ib_uverbs_file *ufile,
			     क्रमागत rdma_हटाओ_reason reason);

पूर्णांक uobj_destroy(काष्ठा ib_uobject *uobj, काष्ठा uverbs_attr_bundle *attrs);

/*
 * Get an ib_uobject that corresponds to the given id from ufile, assuming
 * the object is from the given type. Lock it to the required access when
 * applicable.
 * This function could create (access == NEW), destroy (access == DESTROY)
 * or unlock (access == READ || access == WRITE) objects अगर required.
 * The action will be finalized only when uverbs_finalize_object or
 * uverbs_finalize_objects are called.
 */
काष्ठा ib_uobject *
uverbs_get_uobject_from_file(u16 object_id, क्रमागत uverbs_obj_access access,
			     s64 id, काष्ठा uverbs_attr_bundle *attrs);

व्योम uverbs_finalize_object(काष्ठा ib_uobject *uobj,
			    क्रमागत uverbs_obj_access access, bool hw_obj_valid,
			    bool commit, काष्ठा uverbs_attr_bundle *attrs);

पूर्णांक uverbs_output_written(स्थिर काष्ठा uverbs_attr_bundle *bundle, माप_प्रकार idx);

व्योम setup_ufile_idr_uobject(काष्ठा ib_uverbs_file *ufile);
व्योम release_ufile_idr_uobject(काष्ठा ib_uverbs_file *ufile);

काष्ठा ib_udata *uverbs_get_cleared_udata(काष्ठा uverbs_attr_bundle *attrs);

/*
 * This is the runसमय description of the uverbs API, used by the syscall
 * machinery to validate and dispatch calls.
 */

/*
 * Depending on ID the slot poपूर्णांकer in the radix tree poपूर्णांकs at one of these
 * काष्ठाs.
 */

काष्ठा uverbs_api_ioctl_method अणु
	पूर्णांक(__rcu *handler)(काष्ठा uverbs_attr_bundle *attrs);
	DECLARE_BITMAP(attr_mandatory, UVERBS_API_ATTR_BKEY_LEN);
	u16 bundle_size;
	u8 use_stack:1;
	u8 driver_method:1;
	u8 disabled:1;
	u8 has_udata:1;
	u8 key_biपंचांगap_len;
	u8 destroy_bkey;
पूर्ण;

काष्ठा uverbs_api_ग_लिखो_method अणु
	पूर्णांक (*handler)(काष्ठा uverbs_attr_bundle *attrs);
	u8 disabled:1;
	u8 is_ex:1;
	u8 has_udata:1;
	u8 has_resp:1;
	u8 req_size;
	u8 resp_size;
पूर्ण;

काष्ठा uverbs_api_attr अणु
	काष्ठा uverbs_attr_spec spec;
पूर्ण;

काष्ठा uverbs_api अणु
	/* radix tree contains काष्ठा uverbs_api_* poपूर्णांकers */
	काष्ठा radix_tree_root radix;
	क्रमागत rdma_driver_id driver_id;

	अचिन्हित पूर्णांक num_ग_लिखो;
	अचिन्हित पूर्णांक num_ग_लिखो_ex;
	काष्ठा uverbs_api_ग_लिखो_method notsupp_method;
	स्थिर काष्ठा uverbs_api_ग_लिखो_method **ग_लिखो_methods;
	स्थिर काष्ठा uverbs_api_ग_लिखो_method **ग_लिखो_ex_methods;
पूर्ण;

/*
 * Get an uverbs_api_object that corresponds to the given object_id.
 * Note:
 * -ENOMSG means that any object is allowed to match during lookup.
 */
अटल अंतरभूत स्थिर काष्ठा uverbs_api_object *
uapi_get_object(काष्ठा uverbs_api *uapi, u16 object_id)
अणु
	स्थिर काष्ठा uverbs_api_object *res;

	अगर (object_id == UVERBS_IDR_ANY_OBJECT)
		वापस ERR_PTR(-ENOMSG);

	res = radix_tree_lookup(&uapi->radix, uapi_key_obj(object_id));
	अगर (!res)
		वापस ERR_PTR(-ENOENT);

	वापस res;
पूर्ण

अक्षर *uapi_key_क्रमmat(अक्षर *S, अचिन्हित पूर्णांक key);
काष्ठा uverbs_api *uverbs_alloc_api(काष्ठा ib_device *ibdev);
व्योम uverbs_disassociate_api_pre(काष्ठा ib_uverbs_device *uverbs_dev);
व्योम uverbs_disassociate_api(काष्ठा uverbs_api *uapi);
व्योम uverbs_destroy_api(काष्ठा uverbs_api *uapi);
व्योम uapi_compute_bundle_size(काष्ठा uverbs_api_ioctl_method *method_elm,
			      अचिन्हित पूर्णांक num_attrs);
व्योम uverbs_user_mmap_disassociate(काष्ठा ib_uverbs_file *ufile);

बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_async_fd[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_counters[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_cq[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_device[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_dm[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_flow_action[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_पूर्णांकf[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_mr[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_qp[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_srq[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_obj_wq[];
बाह्य स्थिर काष्ठा uapi_definition uverbs_def_ग_लिखो_पूर्णांकf[];

अटल अंतरभूत स्थिर काष्ठा uverbs_api_ग_लिखो_method *
uapi_get_method(स्थिर काष्ठा uverbs_api *uapi, u32 command)
अणु
	u32 cmd_idx = command & IB_USER_VERBS_CMD_COMMAND_MASK;

	अगर (command & ~(u32)(IB_USER_VERBS_CMD_FLAG_EXTENDED |
			     IB_USER_VERBS_CMD_COMMAND_MASK))
		वापस ERR_PTR(-EINVAL);

	अगर (command & IB_USER_VERBS_CMD_FLAG_EXTENDED) अणु
		अगर (cmd_idx >= uapi->num_ग_लिखो_ex)
			वापस ERR_PTR(-EOPNOTSUPP);
		वापस uapi->ग_लिखो_ex_methods[cmd_idx];
	पूर्ण

	अगर (cmd_idx >= uapi->num_ग_लिखो)
		वापस ERR_PTR(-EOPNOTSUPP);
	वापस uapi->ग_लिखो_methods[cmd_idx];
पूर्ण

व्योम uverbs_fill_udata(काष्ठा uverbs_attr_bundle *bundle,
		       काष्ठा ib_udata *udata, अचिन्हित पूर्णांक attr_in,
		       अचिन्हित पूर्णांक attr_out);

#पूर्ण_अगर /* RDMA_CORE_H */
