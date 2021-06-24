<शैली गुरु>
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 PathScale, Inc.  All rights reserved.
 * Copyright (c) 2006 Mellanox Technologies.  All rights reserved.
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

#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#समावेश <linux/uaccess.h>

#समावेश <rdma/uverbs_types.h>
#समावेश <rdma/uverbs_std_types.h>
#समावेश "rdma_core.h"

#समावेश "uverbs.h"
#समावेश "core_priv.h"

/*
 * Copy a response to userspace. If the provided 'resp' is larger than the
 * user buffer it is silently truncated. If the user provided a larger buffer
 * then the trailing portion is zero filled.
 *
 * These semantics are पूर्णांकended to support future extension of the output
 * काष्ठाures.
 */
अटल पूर्णांक uverbs_response(काष्ठा uverbs_attr_bundle *attrs, स्थिर व्योम *resp,
			   माप_प्रकार resp_len)
अणु
	पूर्णांक ret;

	अगर (uverbs_attr_is_valid(attrs, UVERBS_ATTR_CORE_OUT))
		वापस uverbs_copy_to_काष्ठा_or_zero(
			attrs, UVERBS_ATTR_CORE_OUT, resp, resp_len);

	अगर (copy_to_user(attrs->ucore.outbuf, resp,
			 min(attrs->ucore.outlen, resp_len)))
		वापस -EFAULT;

	अगर (resp_len < attrs->ucore.outlen) अणु
		/*
		 * Zero fill any extra memory that user
		 * space might have provided.
		 */
		ret = clear_user(attrs->ucore.outbuf + resp_len,
				 attrs->ucore.outlen - resp_len);
		अगर (ret)
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Copy a request from userspace. If the provided 'req' is larger than the
 * user buffer then the user buffer is zero extended पूर्णांकo the 'req'. If 'req'
 * is smaller than the user buffer then the uncopied bytes in the user buffer
 * must be zero.
 */
अटल पूर्णांक uverbs_request(काष्ठा uverbs_attr_bundle *attrs, व्योम *req,
			  माप_प्रकार req_len)
अणु
	अगर (copy_from_user(req, attrs->ucore.inbuf,
			   min(attrs->ucore.inlen, req_len)))
		वापस -EFAULT;

	अगर (attrs->ucore.inlen < req_len) अणु
		स_रखो(req + attrs->ucore.inlen, 0,
		       req_len - attrs->ucore.inlen);
	पूर्ण अन्यथा अगर (attrs->ucore.inlen > req_len) अणु
		अगर (!ib_is_buffer_cleared(attrs->ucore.inbuf + req_len,
					  attrs->ucore.inlen - req_len))
			वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Generate the value क्रम the 'response_length' protocol used by ग_लिखो_ex.
 * This is the number of bytes the kernel actually wrote. Userspace can use
 * this to detect what काष्ठाure members in the response the kernel
 * understood.
 */
अटल u32 uverbs_response_length(काष्ठा uverbs_attr_bundle *attrs,
				  माप_प्रकार resp_len)
अणु
	वापस min_t(माप_प्रकार, attrs->ucore.outlen, resp_len);
पूर्ण

/*
 * The iterator version of the request पूर्णांकerface is क्रम handlers that need to
 * step over a flex array at the end of a command header.
 */
काष्ठा uverbs_req_iter अणु
	स्थिर व्योम __user *cur;
	स्थिर व्योम __user *end;
पूर्ण;

अटल पूर्णांक uverbs_request_start(काष्ठा uverbs_attr_bundle *attrs,
				काष्ठा uverbs_req_iter *iter,
				व्योम *req,
				माप_प्रकार req_len)
अणु
	अगर (attrs->ucore.inlen < req_len)
		वापस -ENOSPC;

	अगर (copy_from_user(req, attrs->ucore.inbuf, req_len))
		वापस -EFAULT;

	iter->cur = attrs->ucore.inbuf + req_len;
	iter->end = attrs->ucore.inbuf + attrs->ucore.inlen;
	वापस 0;
पूर्ण

अटल पूर्णांक uverbs_request_next(काष्ठा uverbs_req_iter *iter, व्योम *val,
			       माप_प्रकार len)
अणु
	अगर (iter->cur + len > iter->end)
		वापस -ENOSPC;

	अगर (copy_from_user(val, iter->cur, len))
		वापस -EFAULT;

	iter->cur += len;
	वापस 0;
पूर्ण

अटल स्थिर व्योम __user *uverbs_request_next_ptr(काष्ठा uverbs_req_iter *iter,
						  माप_प्रकार len)
अणु
	स्थिर व्योम __user *res = iter->cur;

	अगर (iter->cur + len > iter->end)
		वापस (व्योम __क्रमce __user *)ERR_PTR(-ENOSPC);
	iter->cur += len;
	वापस res;
पूर्ण

अटल पूर्णांक uverbs_request_finish(काष्ठा uverbs_req_iter *iter)
अणु
	अगर (!ib_is_buffer_cleared(iter->cur, iter->end - iter->cur))
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

/*
 * When calling a destroy function during an error unwind we need to pass in
 * the udata that is sanitized of all user arguments. Ie from the driver
 * perspective it looks like no udata was passed.
 */
काष्ठा ib_udata *uverbs_get_cleared_udata(काष्ठा uverbs_attr_bundle *attrs)
अणु
	attrs->driver_udata = (काष्ठा ib_udata)अणुपूर्ण;
	वापस &attrs->driver_udata;
पूर्ण

अटल काष्ठा ib_uverbs_completion_event_file *
_ib_uverbs_lookup_comp_file(s32 fd, काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = ufd_get_पढ़ो(UVERBS_OBJECT_COMP_CHANNEL,
					       fd, attrs);

	अगर (IS_ERR(uobj))
		वापस (व्योम *)uobj;

	uverbs_uobject_get(uobj);
	uobj_put_पढ़ो(uobj);

	वापस container_of(uobj, काष्ठा ib_uverbs_completion_event_file,
			    uobj);
पूर्ण
#घोषणा ib_uverbs_lookup_comp_file(_fd, _ufile)                                \
	_ib_uverbs_lookup_comp_file((_fd)*typecheck(s32, _fd), _ufile)

पूर्णांक ib_alloc_ucontext(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_file *ufile = attrs->ufile;
	काष्ठा ib_ucontext *ucontext;
	काष्ठा ib_device *ib_dev;

	ib_dev = srcu_dereference(ufile->device->ib_dev,
				  &ufile->device->disassociate_srcu);
	अगर (!ib_dev)
		वापस -EIO;

	ucontext = rdma_zalloc_drv_obj(ib_dev, ib_ucontext);
	अगर (!ucontext)
		वापस -ENOMEM;

	ucontext->device = ib_dev;
	ucontext->ufile = ufile;
	xa_init_flags(&ucontext->mmap_xa, XA_FLAGS_ALLOC);

	rdma_restrack_new(&ucontext->res, RDMA_RESTRACK_CTX);
	rdma_restrack_set_name(&ucontext->res, शून्य);
	attrs->context = ucontext;
	वापस 0;
पूर्ण

पूर्णांक ib_init_ucontext(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_ucontext *ucontext = attrs->context;
	काष्ठा ib_uverbs_file *file = attrs->ufile;
	पूर्णांक ret;

	अगर (!करोwn_पढ़ो_trylock(&file->hw_destroy_rwsem))
		वापस -EIO;
	mutex_lock(&file->ucontext_lock);
	अगर (file->ucontext) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = ib_rdmacg_try_अक्षरge(&ucontext->cg_obj, ucontext->device,
				   RDMACG_RESOURCE_HCA_HANDLE);
	अगर (ret)
		जाओ err;

	ret = ucontext->device->ops.alloc_ucontext(ucontext,
						   &attrs->driver_udata);
	अगर (ret)
		जाओ err_unअक्षरge;

	rdma_restrack_add(&ucontext->res);

	/*
	 * Make sure that ib_uverbs_get_ucontext() sees the poपूर्णांकer update
	 * only after all ग_लिखोs to setup the ucontext have completed
	 */
	smp_store_release(&file->ucontext, ucontext);

	mutex_unlock(&file->ucontext_lock);
	up_पढ़ो(&file->hw_destroy_rwsem);
	वापस 0;

err_unअक्षरge:
	ib_rdmacg_unअक्षरge(&ucontext->cg_obj, ucontext->device,
			   RDMACG_RESOURCE_HCA_HANDLE);
err:
	mutex_unlock(&file->ucontext_lock);
	up_पढ़ो(&file->hw_destroy_rwsem);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_get_context(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_get_context_resp resp;
	काष्ठा ib_uverbs_get_context cmd;
	काष्ठा ib_device *ib_dev;
	काष्ठा ib_uobject *uobj;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	ret = ib_alloc_ucontext(attrs);
	अगर (ret)
		वापस ret;

	uobj = uobj_alloc(UVERBS_OBJECT_ASYNC_EVENT, attrs, &ib_dev);
	अगर (IS_ERR(uobj)) अणु
		ret = PTR_ERR(uobj);
		जाओ err_ucontext;
	पूर्ण

	resp = (काष्ठा ib_uverbs_get_context_resp)अणु
		.num_comp_vectors = attrs->ufile->device->num_comp_vectors,
		.async_fd = uobj->id,
	पूर्ण;
	ret = uverbs_response(attrs, &resp, माप(resp));
	अगर (ret)
		जाओ err_uobj;

	ret = ib_init_ucontext(attrs);
	अगर (ret)
		जाओ err_uobj;

	ib_uverbs_init_async_event_file(
		container_of(uobj, काष्ठा ib_uverbs_async_event_file, uobj));
	rdma_alloc_commit_uobject(uobj, attrs);
	वापस 0;

err_uobj:
	rdma_alloc_पात_uobject(uobj, attrs, false);
err_ucontext:
	rdma_restrack_put(&attrs->context->res);
	kमुक्त(attrs->context);
	attrs->context = शून्य;
	वापस ret;
पूर्ण

अटल व्योम copy_query_dev_fields(काष्ठा ib_ucontext *ucontext,
				  काष्ठा ib_uverbs_query_device_resp *resp,
				  काष्ठा ib_device_attr *attr)
अणु
	काष्ठा ib_device *ib_dev = ucontext->device;

	resp->fw_ver		= attr->fw_ver;
	resp->node_guid		= ib_dev->node_guid;
	resp->sys_image_guid	= attr->sys_image_guid;
	resp->max_mr_size	= attr->max_mr_size;
	resp->page_size_cap	= attr->page_size_cap;
	resp->venकरोr_id		= attr->venकरोr_id;
	resp->venकरोr_part_id	= attr->venकरोr_part_id;
	resp->hw_ver		= attr->hw_ver;
	resp->max_qp		= attr->max_qp;
	resp->max_qp_wr		= attr->max_qp_wr;
	resp->device_cap_flags	= lower_32_bits(attr->device_cap_flags);
	resp->max_sge		= min(attr->max_send_sge, attr->max_recv_sge);
	resp->max_sge_rd	= attr->max_sge_rd;
	resp->max_cq		= attr->max_cq;
	resp->max_cqe		= attr->max_cqe;
	resp->max_mr		= attr->max_mr;
	resp->max_pd		= attr->max_pd;
	resp->max_qp_rd_atom	= attr->max_qp_rd_atom;
	resp->max_ee_rd_atom	= attr->max_ee_rd_atom;
	resp->max_res_rd_atom	= attr->max_res_rd_atom;
	resp->max_qp_init_rd_atom	= attr->max_qp_init_rd_atom;
	resp->max_ee_init_rd_atom	= attr->max_ee_init_rd_atom;
	resp->atomic_cap		= attr->atomic_cap;
	resp->max_ee			= attr->max_ee;
	resp->max_rdd			= attr->max_rdd;
	resp->max_mw			= attr->max_mw;
	resp->max_raw_ipv6_qp		= attr->max_raw_ipv6_qp;
	resp->max_raw_ethy_qp		= attr->max_raw_ethy_qp;
	resp->max_mcast_grp		= attr->max_mcast_grp;
	resp->max_mcast_qp_attach	= attr->max_mcast_qp_attach;
	resp->max_total_mcast_qp_attach	= attr->max_total_mcast_qp_attach;
	resp->max_ah			= attr->max_ah;
	resp->max_srq			= attr->max_srq;
	resp->max_srq_wr		= attr->max_srq_wr;
	resp->max_srq_sge		= attr->max_srq_sge;
	resp->max_pkeys			= attr->max_pkeys;
	resp->local_ca_ack_delay	= attr->local_ca_ack_delay;
	resp->phys_port_cnt = min_t(u32, ib_dev->phys_port_cnt, U8_MAX);
पूर्ण

अटल पूर्णांक ib_uverbs_query_device(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_query_device      cmd;
	काष्ठा ib_uverbs_query_device_resp resp;
	काष्ठा ib_ucontext *ucontext;
	पूर्णांक ret;

	ucontext = ib_uverbs_get_ucontext(attrs);
	अगर (IS_ERR(ucontext))
		वापस PTR_ERR(ucontext);

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	स_रखो(&resp, 0, माप resp);
	copy_query_dev_fields(ucontext, &resp, &ucontext->device->attrs);

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक ib_uverbs_query_port(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_query_port      cmd;
	काष्ठा ib_uverbs_query_port_resp resp;
	काष्ठा ib_port_attr              attr;
	पूर्णांक                              ret;
	काष्ठा ib_ucontext *ucontext;
	काष्ठा ib_device *ib_dev;

	ucontext = ib_uverbs_get_ucontext(attrs);
	अगर (IS_ERR(ucontext))
		वापस PTR_ERR(ucontext);
	ib_dev = ucontext->device;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	ret = ib_query_port(ib_dev, cmd.port_num, &attr);
	अगर (ret)
		वापस ret;

	स_रखो(&resp, 0, माप resp);
	copy_port_attr_to_resp(&attr, &resp, ib_dev, cmd.port_num);

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक ib_uverbs_alloc_pd(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_alloc_pd_resp resp = अणुपूर्ण;
	काष्ठा ib_uverbs_alloc_pd      cmd;
	काष्ठा ib_uobject             *uobj;
	काष्ठा ib_pd                  *pd;
	पूर्णांक                            ret;
	काष्ठा ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	uobj = uobj_alloc(UVERBS_OBJECT_PD, attrs, &ib_dev);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	pd = rdma_zalloc_drv_obj(ib_dev, ib_pd);
	अगर (!pd) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	pd->device  = ib_dev;
	pd->uobject = uobj;
	atomic_set(&pd->usecnt, 0);

	rdma_restrack_new(&pd->res, RDMA_RESTRACK_PD);
	rdma_restrack_set_name(&pd->res, शून्य);

	ret = ib_dev->ops.alloc_pd(pd, &attrs->driver_udata);
	अगर (ret)
		जाओ err_alloc;
	rdma_restrack_add(&pd->res);

	uobj->object = pd;
	uobj_finalize_uobj_create(uobj, attrs);

	resp.pd_handle = uobj->id;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_alloc:
	rdma_restrack_put(&pd->res);
	kमुक्त(pd);
err:
	uobj_alloc_पात(uobj, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_dealloc_pd(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_dealloc_pd cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	वापस uobj_perक्रमm_destroy(UVERBS_OBJECT_PD, cmd.pd_handle, attrs);
पूर्ण

काष्ठा xrcd_table_entry अणु
	काष्ठा rb_node  node;
	काष्ठा ib_xrcd *xrcd;
	काष्ठा inode   *inode;
पूर्ण;

अटल पूर्णांक xrcd_table_insert(काष्ठा ib_uverbs_device *dev,
			    काष्ठा inode *inode,
			    काष्ठा ib_xrcd *xrcd)
अणु
	काष्ठा xrcd_table_entry *entry, *scan;
	काष्ठा rb_node **p = &dev->xrcd_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;

	entry = kदो_स्मृति(माप *entry, GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->xrcd  = xrcd;
	entry->inode = inode;

	जबतक (*p) अणु
		parent = *p;
		scan = rb_entry(parent, काष्ठा xrcd_table_entry, node);

		अगर (inode < scan->inode) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (inode > scan->inode) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			kमुक्त(entry);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	rb_link_node(&entry->node, parent, p);
	rb_insert_color(&entry->node, &dev->xrcd_tree);
	igrab(inode);
	वापस 0;
पूर्ण

अटल काष्ठा xrcd_table_entry *xrcd_table_search(काष्ठा ib_uverbs_device *dev,
						  काष्ठा inode *inode)
अणु
	काष्ठा xrcd_table_entry *entry;
	काष्ठा rb_node *p = dev->xrcd_tree.rb_node;

	जबतक (p) अणु
		entry = rb_entry(p, काष्ठा xrcd_table_entry, node);

		अगर (inode < entry->inode)
			p = p->rb_left;
		अन्यथा अगर (inode > entry->inode)
			p = p->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा ib_xrcd *find_xrcd(काष्ठा ib_uverbs_device *dev, काष्ठा inode *inode)
अणु
	काष्ठा xrcd_table_entry *entry;

	entry = xrcd_table_search(dev, inode);
	अगर (!entry)
		वापस शून्य;

	वापस entry->xrcd;
पूर्ण

अटल व्योम xrcd_table_delete(काष्ठा ib_uverbs_device *dev,
			      काष्ठा inode *inode)
अणु
	काष्ठा xrcd_table_entry *entry;

	entry = xrcd_table_search(dev, inode);
	अगर (entry) अणु
		iput(inode);
		rb_erase(&entry->node, &dev->xrcd_tree);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल पूर्णांक ib_uverbs_खोलो_xrcd(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_device *ibudev = attrs->ufile->device;
	काष्ठा ib_uverbs_खोलो_xrcd_resp	resp = अणुपूर्ण;
	काष्ठा ib_uverbs_खोलो_xrcd	cmd;
	काष्ठा ib_uxrcd_object         *obj;
	काष्ठा ib_xrcd                 *xrcd = शून्य;
	काष्ठा inode                   *inode = शून्य;
	पूर्णांक				new_xrcd = 0;
	काष्ठा ib_device *ib_dev;
	काष्ठा fd f = अणुपूर्ण;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	mutex_lock(&ibudev->xrcd_tree_mutex);

	अगर (cmd.fd != -1) अणु
		/* search क्रम file descriptor */
		f = fdget(cmd.fd);
		अगर (!f.file) अणु
			ret = -EBADF;
			जाओ err_tree_mutex_unlock;
		पूर्ण

		inode = file_inode(f.file);
		xrcd = find_xrcd(ibudev, inode);
		अगर (!xrcd && !(cmd.oflags & O_CREAT)) अणु
			/* no file descriptor. Need CREATE flag */
			ret = -EAGAIN;
			जाओ err_tree_mutex_unlock;
		पूर्ण

		अगर (xrcd && cmd.oflags & O_EXCL) अणु
			ret = -EINVAL;
			जाओ err_tree_mutex_unlock;
		पूर्ण
	पूर्ण

	obj = (काष्ठा ib_uxrcd_object *)uobj_alloc(UVERBS_OBJECT_XRCD, attrs,
						   &ib_dev);
	अगर (IS_ERR(obj)) अणु
		ret = PTR_ERR(obj);
		जाओ err_tree_mutex_unlock;
	पूर्ण

	अगर (!xrcd) अणु
		xrcd = ib_alloc_xrcd_user(ib_dev, inode, &attrs->driver_udata);
		अगर (IS_ERR(xrcd)) अणु
			ret = PTR_ERR(xrcd);
			जाओ err;
		पूर्ण
		new_xrcd = 1;
	पूर्ण

	atomic_set(&obj->refcnt, 0);
	obj->uobject.object = xrcd;

	अगर (inode) अणु
		अगर (new_xrcd) अणु
			/* create new inode/xrcd table entry */
			ret = xrcd_table_insert(ibudev, inode, xrcd);
			अगर (ret)
				जाओ err_dealloc_xrcd;
		पूर्ण
		atomic_inc(&xrcd->usecnt);
	पूर्ण

	अगर (f.file)
		fdput(f);

	mutex_unlock(&ibudev->xrcd_tree_mutex);
	uobj_finalize_uobj_create(&obj->uobject, attrs);

	resp.xrcd_handle = obj->uobject.id;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_dealloc_xrcd:
	ib_dealloc_xrcd_user(xrcd, uverbs_get_cleared_udata(attrs));

err:
	uobj_alloc_पात(&obj->uobject, attrs);

err_tree_mutex_unlock:
	अगर (f.file)
		fdput(f);

	mutex_unlock(&ibudev->xrcd_tree_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_बंद_xrcd(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_बंद_xrcd cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	वापस uobj_perक्रमm_destroy(UVERBS_OBJECT_XRCD, cmd.xrcd_handle, attrs);
पूर्ण

पूर्णांक ib_uverbs_dealloc_xrcd(काष्ठा ib_uobject *uobject, काष्ठा ib_xrcd *xrcd,
			   क्रमागत rdma_हटाओ_reason why,
			   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा inode *inode;
	पूर्णांक ret;
	काष्ठा ib_uverbs_device *dev = attrs->ufile->device;

	inode = xrcd->inode;
	अगर (inode && !atomic_dec_and_test(&xrcd->usecnt))
		वापस 0;

	ret = ib_dealloc_xrcd_user(xrcd, &attrs->driver_udata);
	अगर (ret) अणु
		atomic_inc(&xrcd->usecnt);
		वापस ret;
	पूर्ण

	अगर (inode)
		xrcd_table_delete(dev, inode);

	वापस 0;
पूर्ण

अटल पूर्णांक ib_uverbs_reg_mr(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_reg_mr_resp resp = अणुपूर्ण;
	काष्ठा ib_uverbs_reg_mr      cmd;
	काष्ठा ib_uobject           *uobj;
	काष्ठा ib_pd                *pd;
	काष्ठा ib_mr                *mr;
	पूर्णांक                          ret;
	काष्ठा ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर ((cmd.start & ~PAGE_MASK) != (cmd.hca_va & ~PAGE_MASK))
		वापस -EINVAL;

	uobj = uobj_alloc(UVERBS_OBJECT_MR, attrs, &ib_dev);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	ret = ib_check_mr_access(ib_dev, cmd.access_flags);
	अगर (ret)
		जाओ err_मुक्त;

	pd = uobj_get_obj_पढ़ो(pd, UVERBS_OBJECT_PD, cmd.pd_handle, attrs);
	अगर (!pd) अणु
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	mr = pd->device->ops.reg_user_mr(pd, cmd.start, cmd.length, cmd.hca_va,
					 cmd.access_flags,
					 &attrs->driver_udata);
	अगर (IS_ERR(mr)) अणु
		ret = PTR_ERR(mr);
		जाओ err_put;
	पूर्ण

	mr->device  = pd->device;
	mr->pd      = pd;
	mr->type    = IB_MR_TYPE_USER;
	mr->dm	    = शून्य;
	mr->sig_attrs = शून्य;
	mr->uobject = uobj;
	atomic_inc(&pd->usecnt);
	mr->iova = cmd.hca_va;

	rdma_restrack_new(&mr->res, RDMA_RESTRACK_MR);
	rdma_restrack_set_name(&mr->res, शून्य);
	rdma_restrack_add(&mr->res);

	uobj->object = mr;
	uobj_put_obj_पढ़ो(pd);
	uobj_finalize_uobj_create(uobj, attrs);

	resp.lkey = mr->lkey;
	resp.rkey = mr->rkey;
	resp.mr_handle = uobj->id;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_put:
	uobj_put_obj_पढ़ो(pd);
err_मुक्त:
	uobj_alloc_पात(uobj, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_rereg_mr(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_rereg_mr      cmd;
	काष्ठा ib_uverbs_rereg_mr_resp resp;
	काष्ठा ib_mr                *mr;
	पूर्णांक                          ret;
	काष्ठा ib_uobject	    *uobj;
	काष्ठा ib_uobject *new_uobj;
	काष्ठा ib_device *ib_dev;
	काष्ठा ib_pd *orig_pd;
	काष्ठा ib_pd *new_pd;
	काष्ठा ib_mr *new_mr;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (!cmd.flags)
		वापस -EINVAL;

	अगर (cmd.flags & ~IB_MR_REREG_SUPPORTED)
		वापस -EOPNOTSUPP;

	अगर ((cmd.flags & IB_MR_REREG_TRANS) &&
	    (cmd.start & ~PAGE_MASK) != (cmd.hca_va & ~PAGE_MASK))
		वापस -EINVAL;

	uobj = uobj_get_ग_लिखो(UVERBS_OBJECT_MR, cmd.mr_handle, attrs);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	mr = uobj->object;

	अगर (mr->dm) अणु
		ret = -EINVAL;
		जाओ put_uobjs;
	पूर्ण

	अगर (cmd.flags & IB_MR_REREG_ACCESS) अणु
		ret = ib_check_mr_access(mr->device, cmd.access_flags);
		अगर (ret)
			जाओ put_uobjs;
	पूर्ण

	orig_pd = mr->pd;
	अगर (cmd.flags & IB_MR_REREG_PD) अणु
		new_pd = uobj_get_obj_पढ़ो(pd, UVERBS_OBJECT_PD, cmd.pd_handle,
					   attrs);
		अगर (!new_pd) अणु
			ret = -EINVAL;
			जाओ put_uobjs;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_pd = mr->pd;
	पूर्ण

	/*
	 * The driver might create a new HW object as part of the rereg, we need
	 * to have a uobject पढ़ोy to hold it.
	 */
	new_uobj = uobj_alloc(UVERBS_OBJECT_MR, attrs, &ib_dev);
	अगर (IS_ERR(new_uobj)) अणु
		ret = PTR_ERR(new_uobj);
		जाओ put_uobj_pd;
	पूर्ण

	new_mr = ib_dev->ops.rereg_user_mr(mr, cmd.flags, cmd.start, cmd.length,
					   cmd.hca_va, cmd.access_flags, new_pd,
					   &attrs->driver_udata);
	अगर (IS_ERR(new_mr)) अणु
		ret = PTR_ERR(new_mr);
		जाओ put_new_uobj;
	पूर्ण
	अगर (new_mr) अणु
		new_mr->device = new_pd->device;
		new_mr->pd = new_pd;
		new_mr->type = IB_MR_TYPE_USER;
		new_mr->dm = शून्य;
		new_mr->sig_attrs = शून्य;
		new_mr->uobject = uobj;
		atomic_inc(&new_pd->usecnt);
		new_mr->iova = cmd.hca_va;
		new_uobj->object = new_mr;

		rdma_restrack_new(&new_mr->res, RDMA_RESTRACK_MR);
		rdma_restrack_set_name(&new_mr->res, शून्य);
		rdma_restrack_add(&new_mr->res);

		/*
		 * The new uobj क्रम the new HW object is put पूर्णांकo the same spot
		 * in the IDR and the old uobj & HW object is deleted.
		 */
		rdma_assign_uobject(uobj, new_uobj, attrs);
		rdma_alloc_commit_uobject(new_uobj, attrs);
		uobj_put_destroy(uobj);
		new_uobj = शून्य;
		uobj = शून्य;
		mr = new_mr;
	पूर्ण अन्यथा अणु
		अगर (cmd.flags & IB_MR_REREG_PD) अणु
			atomic_dec(&orig_pd->usecnt);
			mr->pd = new_pd;
			atomic_inc(&new_pd->usecnt);
		पूर्ण
		अगर (cmd.flags & IB_MR_REREG_TRANS)
			mr->iova = cmd.hca_va;
	पूर्ण

	स_रखो(&resp, 0, माप(resp));
	resp.lkey      = mr->lkey;
	resp.rkey      = mr->rkey;

	ret = uverbs_response(attrs, &resp, माप(resp));

put_new_uobj:
	अगर (new_uobj)
		uobj_alloc_पात(new_uobj, attrs);
put_uobj_pd:
	अगर (cmd.flags & IB_MR_REREG_PD)
		uobj_put_obj_पढ़ो(new_pd);

put_uobjs:
	अगर (uobj)
		uobj_put_ग_लिखो(uobj);

	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_dereg_mr(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_dereg_mr cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	वापस uobj_perक्रमm_destroy(UVERBS_OBJECT_MR, cmd.mr_handle, attrs);
पूर्ण

अटल पूर्णांक ib_uverbs_alloc_mw(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_alloc_mw      cmd;
	काष्ठा ib_uverbs_alloc_mw_resp resp = अणुपूर्ण;
	काष्ठा ib_uobject             *uobj;
	काष्ठा ib_pd                  *pd;
	काष्ठा ib_mw                  *mw;
	पूर्णांक                            ret;
	काष्ठा ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	uobj = uobj_alloc(UVERBS_OBJECT_MW, attrs, &ib_dev);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	pd = uobj_get_obj_पढ़ो(pd, UVERBS_OBJECT_PD, cmd.pd_handle, attrs);
	अगर (!pd) अणु
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	अगर (cmd.mw_type != IB_MW_TYPE_1 && cmd.mw_type != IB_MW_TYPE_2) अणु
		ret = -EINVAL;
		जाओ err_put;
	पूर्ण

	mw = rdma_zalloc_drv_obj(ib_dev, ib_mw);
	अगर (!mw) अणु
		ret = -ENOMEM;
		जाओ err_put;
	पूर्ण

	mw->device = ib_dev;
	mw->pd = pd;
	mw->uobject = uobj;
	mw->type = cmd.mw_type;

	ret = pd->device->ops.alloc_mw(mw, &attrs->driver_udata);
	अगर (ret)
		जाओ err_alloc;

	atomic_inc(&pd->usecnt);

	uobj->object = mw;
	uobj_put_obj_पढ़ो(pd);
	uobj_finalize_uobj_create(uobj, attrs);

	resp.rkey = mw->rkey;
	resp.mw_handle = uobj->id;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_alloc:
	kमुक्त(mw);
err_put:
	uobj_put_obj_पढ़ो(pd);
err_मुक्त:
	uobj_alloc_पात(uobj, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_dealloc_mw(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_dealloc_mw cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	वापस uobj_perक्रमm_destroy(UVERBS_OBJECT_MW, cmd.mw_handle, attrs);
पूर्ण

अटल पूर्णांक ib_uverbs_create_comp_channel(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_comp_channel	   cmd;
	काष्ठा ib_uverbs_create_comp_channel_resp  resp;
	काष्ठा ib_uobject			  *uobj;
	काष्ठा ib_uverbs_completion_event_file	  *ev_file;
	काष्ठा ib_device *ib_dev;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	uobj = uobj_alloc(UVERBS_OBJECT_COMP_CHANNEL, attrs, &ib_dev);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	ev_file = container_of(uobj, काष्ठा ib_uverbs_completion_event_file,
			       uobj);
	ib_uverbs_init_event_queue(&ev_file->ev_queue);
	uobj_finalize_uobj_create(uobj, attrs);

	resp.fd = uobj->id;
	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक create_cq(काष्ठा uverbs_attr_bundle *attrs,
		     काष्ठा ib_uverbs_ex_create_cq *cmd)
अणु
	काष्ठा ib_ucq_object           *obj;
	काष्ठा ib_uverbs_completion_event_file    *ev_file = शून्य;
	काष्ठा ib_cq                   *cq;
	पूर्णांक                             ret;
	काष्ठा ib_uverbs_ex_create_cq_resp resp = अणुपूर्ण;
	काष्ठा ib_cq_init_attr attr = अणुपूर्ण;
	काष्ठा ib_device *ib_dev;

	अगर (cmd->comp_vector >= attrs->ufile->device->num_comp_vectors)
		वापस -EINVAL;

	obj = (काष्ठा ib_ucq_object *)uobj_alloc(UVERBS_OBJECT_CQ, attrs,
						 &ib_dev);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	अगर (cmd->comp_channel >= 0) अणु
		ev_file = ib_uverbs_lookup_comp_file(cmd->comp_channel, attrs);
		अगर (IS_ERR(ev_file)) अणु
			ret = PTR_ERR(ev_file);
			जाओ err;
		पूर्ण
	पूर्ण

	obj->uevent.uobject.user_handle = cmd->user_handle;
	INIT_LIST_HEAD(&obj->comp_list);
	INIT_LIST_HEAD(&obj->uevent.event_list);

	attr.cqe = cmd->cqe;
	attr.comp_vector = cmd->comp_vector;
	attr.flags = cmd->flags;

	cq = rdma_zalloc_drv_obj(ib_dev, ib_cq);
	अगर (!cq) अणु
		ret = -ENOMEM;
		जाओ err_file;
	पूर्ण
	cq->device        = ib_dev;
	cq->uobject       = obj;
	cq->comp_handler  = ib_uverbs_comp_handler;
	cq->event_handler = ib_uverbs_cq_event_handler;
	cq->cq_context    = ev_file ? &ev_file->ev_queue : शून्य;
	atomic_set(&cq->usecnt, 0);

	rdma_restrack_new(&cq->res, RDMA_RESTRACK_CQ);
	rdma_restrack_set_name(&cq->res, शून्य);

	ret = ib_dev->ops.create_cq(cq, &attr, &attrs->driver_udata);
	अगर (ret)
		जाओ err_मुक्त;
	rdma_restrack_add(&cq->res);

	obj->uevent.uobject.object = cq;
	obj->uevent.event_file = READ_ONCE(attrs->ufile->शेष_async_file);
	अगर (obj->uevent.event_file)
		uverbs_uobject_get(&obj->uevent.event_file->uobj);
	uobj_finalize_uobj_create(&obj->uevent.uobject, attrs);

	resp.base.cq_handle = obj->uevent.uobject.id;
	resp.base.cqe = cq->cqe;
	resp.response_length = uverbs_response_length(attrs, माप(resp));
	वापस uverbs_response(attrs, &resp, माप(resp));

err_मुक्त:
	rdma_restrack_put(&cq->res);
	kमुक्त(cq);
err_file:
	अगर (ev_file)
		ib_uverbs_release_ucq(ev_file, obj);
err:
	uobj_alloc_पात(&obj->uevent.uobject, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_create_cq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_cq      cmd;
	काष्ठा ib_uverbs_ex_create_cq	cmd_ex;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	स_रखो(&cmd_ex, 0, माप(cmd_ex));
	cmd_ex.user_handle = cmd.user_handle;
	cmd_ex.cqe = cmd.cqe;
	cmd_ex.comp_vector = cmd.comp_vector;
	cmd_ex.comp_channel = cmd.comp_channel;

	वापस create_cq(attrs, &cmd_ex);
पूर्ण

अटल पूर्णांक ib_uverbs_ex_create_cq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_create_cq  cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (cmd.comp_mask)
		वापस -EINVAL;

	अगर (cmd.reserved)
		वापस -EINVAL;

	वापस create_cq(attrs, &cmd);
पूर्ण

अटल पूर्णांक ib_uverbs_resize_cq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_resize_cq	cmd;
	काष्ठा ib_uverbs_resize_cq_resp	resp = अणुपूर्ण;
	काष्ठा ib_cq			*cq;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	cq = uobj_get_obj_पढ़ो(cq, UVERBS_OBJECT_CQ, cmd.cq_handle, attrs);
	अगर (!cq)
		वापस -EINVAL;

	ret = cq->device->ops.resize_cq(cq, cmd.cqe, &attrs->driver_udata);
	अगर (ret)
		जाओ out;

	resp.cqe = cq->cqe;

	ret = uverbs_response(attrs, &resp, माप(resp));
out:
	rdma_lookup_put_uobject(&cq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);

	वापस ret;
पूर्ण

अटल पूर्णांक copy_wc_to_user(काष्ठा ib_device *ib_dev, व्योम __user *dest,
			   काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_uverbs_wc पंचांगp;

	पंचांगp.wr_id		= wc->wr_id;
	पंचांगp.status		= wc->status;
	पंचांगp.opcode		= wc->opcode;
	पंचांगp.venकरोr_err		= wc->venकरोr_err;
	पंचांगp.byte_len		= wc->byte_len;
	पंचांगp.ex.imm_data		= wc->ex.imm_data;
	पंचांगp.qp_num		= wc->qp->qp_num;
	पंचांगp.src_qp		= wc->src_qp;
	पंचांगp.wc_flags		= wc->wc_flags;
	पंचांगp.pkey_index		= wc->pkey_index;
	अगर (rdma_cap_opa_ah(ib_dev, wc->port_num))
		पंचांगp.slid	= OPA_TO_IB_UCAST_LID(wc->slid);
	अन्यथा
		पंचांगp.slid	= ib_lid_cpu16(wc->slid);
	पंचांगp.sl			= wc->sl;
	पंचांगp.dlid_path_bits	= wc->dlid_path_bits;
	पंचांगp.port_num		= wc->port_num;
	पंचांगp.reserved		= 0;

	अगर (copy_to_user(dest, &पंचांगp, माप पंचांगp))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ib_uverbs_poll_cq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_poll_cq       cmd;
	काष्ठा ib_uverbs_poll_cq_resp  resp;
	u8 __user                     *header_ptr;
	u8 __user                     *data_ptr;
	काष्ठा ib_cq                  *cq;
	काष्ठा ib_wc                   wc;
	पूर्णांक                            ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	cq = uobj_get_obj_पढ़ो(cq, UVERBS_OBJECT_CQ, cmd.cq_handle, attrs);
	अगर (!cq)
		वापस -EINVAL;

	/* we copy a काष्ठा ib_uverbs_poll_cq_resp to user space */
	header_ptr = attrs->ucore.outbuf;
	data_ptr = header_ptr + माप resp;

	स_रखो(&resp, 0, माप resp);
	जबतक (resp.count < cmd.ne) अणु
		ret = ib_poll_cq(cq, 1, &wc);
		अगर (ret < 0)
			जाओ out_put;
		अगर (!ret)
			अवरोध;

		ret = copy_wc_to_user(cq->device, data_ptr, &wc);
		अगर (ret)
			जाओ out_put;

		data_ptr += माप(काष्ठा ib_uverbs_wc);
		++resp.count;
	पूर्ण

	अगर (copy_to_user(header_ptr, &resp, माप resp)) अणु
		ret = -EFAULT;
		जाओ out_put;
	पूर्ण
	ret = 0;

	अगर (uverbs_attr_is_valid(attrs, UVERBS_ATTR_CORE_OUT))
		ret = uverbs_output_written(attrs, UVERBS_ATTR_CORE_OUT);

out_put:
	rdma_lookup_put_uobject(&cq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_req_notअगरy_cq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_req_notअगरy_cq cmd;
	काष्ठा ib_cq                  *cq;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	cq = uobj_get_obj_पढ़ो(cq, UVERBS_OBJECT_CQ, cmd.cq_handle, attrs);
	अगर (!cq)
		वापस -EINVAL;

	ib_req_notअगरy_cq(cq, cmd.solicited_only ?
			 IB_CQ_SOLICITED : IB_CQ_NEXT_COMP);

	rdma_lookup_put_uobject(&cq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	वापस 0;
पूर्ण

अटल पूर्णांक ib_uverbs_destroy_cq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_destroy_cq      cmd;
	काष्ठा ib_uverbs_destroy_cq_resp resp;
	काष्ठा ib_uobject		*uobj;
	काष्ठा ib_ucq_object        	*obj;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	uobj = uobj_get_destroy(UVERBS_OBJECT_CQ, cmd.cq_handle, attrs);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	obj = container_of(uobj, काष्ठा ib_ucq_object, uevent.uobject);
	स_रखो(&resp, 0, माप(resp));
	resp.comp_events_reported  = obj->comp_events_reported;
	resp.async_events_reported = obj->uevent.events_reported;

	uobj_put_destroy(uobj);

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक create_qp(काष्ठा uverbs_attr_bundle *attrs,
		     काष्ठा ib_uverbs_ex_create_qp *cmd)
अणु
	काष्ठा ib_uqp_object		*obj;
	काष्ठा ib_device		*device;
	काष्ठा ib_pd			*pd = शून्य;
	काष्ठा ib_xrcd			*xrcd = शून्य;
	काष्ठा ib_uobject		*xrcd_uobj = ERR_PTR(-ENOENT);
	काष्ठा ib_cq			*scq = शून्य, *rcq = शून्य;
	काष्ठा ib_srq			*srq = शून्य;
	काष्ठा ib_qp			*qp;
	काष्ठा ib_qp_init_attr		attr = अणुपूर्ण;
	काष्ठा ib_uverbs_ex_create_qp_resp resp = अणुपूर्ण;
	पूर्णांक				ret;
	काष्ठा ib_rwq_ind_table *ind_tbl = शून्य;
	bool has_sq = true;
	काष्ठा ib_device *ib_dev;

	चयन (cmd->qp_type) अणु
	हाल IB_QPT_RAW_PACKET:
		अगर (!capable(CAP_NET_RAW))
			वापस -EPERM;
		अवरोध;
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
	हाल IB_QPT_UD:
	हाल IB_QPT_XRC_INI:
	हाल IB_QPT_XRC_TGT:
	हाल IB_QPT_DRIVER:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	obj = (काष्ठा ib_uqp_object *)uobj_alloc(UVERBS_OBJECT_QP, attrs,
						 &ib_dev);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);
	obj->uxrcd = शून्य;
	obj->uevent.uobject.user_handle = cmd->user_handle;
	mutex_init(&obj->mcast_lock);

	अगर (cmd->comp_mask & IB_UVERBS_CREATE_QP_MASK_IND_TABLE) अणु
		ind_tbl = uobj_get_obj_पढ़ो(rwq_ind_table,
					    UVERBS_OBJECT_RWQ_IND_TBL,
					    cmd->rwq_ind_tbl_handle, attrs);
		अगर (!ind_tbl) अणु
			ret = -EINVAL;
			जाओ err_put;
		पूर्ण

		attr.rwq_ind_tbl = ind_tbl;
	पूर्ण

	अगर (ind_tbl && (cmd->max_recv_wr || cmd->max_recv_sge || cmd->is_srq)) अणु
		ret = -EINVAL;
		जाओ err_put;
	पूर्ण

	अगर (ind_tbl && !cmd->max_send_wr)
		has_sq = false;

	अगर (cmd->qp_type == IB_QPT_XRC_TGT) अणु
		xrcd_uobj = uobj_get_पढ़ो(UVERBS_OBJECT_XRCD, cmd->pd_handle,
					  attrs);

		अगर (IS_ERR(xrcd_uobj)) अणु
			ret = -EINVAL;
			जाओ err_put;
		पूर्ण

		xrcd = (काष्ठा ib_xrcd *)xrcd_uobj->object;
		अगर (!xrcd) अणु
			ret = -EINVAL;
			जाओ err_put;
		पूर्ण
		device = xrcd->device;
	पूर्ण अन्यथा अणु
		अगर (cmd->qp_type == IB_QPT_XRC_INI) अणु
			cmd->max_recv_wr = 0;
			cmd->max_recv_sge = 0;
		पूर्ण अन्यथा अणु
			अगर (cmd->is_srq) अणु
				srq = uobj_get_obj_पढ़ो(srq, UVERBS_OBJECT_SRQ,
							cmd->srq_handle, attrs);
				अगर (!srq || srq->srq_type == IB_SRQT_XRC) अणु
					ret = -EINVAL;
					जाओ err_put;
				पूर्ण
			पूर्ण

			अगर (!ind_tbl) अणु
				अगर (cmd->recv_cq_handle != cmd->send_cq_handle) अणु
					rcq = uobj_get_obj_पढ़ो(
						cq, UVERBS_OBJECT_CQ,
						cmd->recv_cq_handle, attrs);
					अगर (!rcq) अणु
						ret = -EINVAL;
						जाओ err_put;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (has_sq)
			scq = uobj_get_obj_पढ़ो(cq, UVERBS_OBJECT_CQ,
						cmd->send_cq_handle, attrs);
		अगर (!ind_tbl && cmd->qp_type != IB_QPT_XRC_INI)
			rcq = rcq ?: scq;
		pd = uobj_get_obj_पढ़ो(pd, UVERBS_OBJECT_PD, cmd->pd_handle,
				       attrs);
		अगर (!pd || (!scq && has_sq)) अणु
			ret = -EINVAL;
			जाओ err_put;
		पूर्ण

		device = pd->device;
	पूर्ण

	attr.event_handler = ib_uverbs_qp_event_handler;
	attr.send_cq       = scq;
	attr.recv_cq       = rcq;
	attr.srq           = srq;
	attr.xrcd	   = xrcd;
	attr.sq_sig_type   = cmd->sq_sig_all ? IB_SIGNAL_ALL_WR :
					      IB_SIGNAL_REQ_WR;
	attr.qp_type       = cmd->qp_type;
	attr.create_flags  = 0;

	attr.cap.max_send_wr     = cmd->max_send_wr;
	attr.cap.max_recv_wr     = cmd->max_recv_wr;
	attr.cap.max_send_sge    = cmd->max_send_sge;
	attr.cap.max_recv_sge    = cmd->max_recv_sge;
	attr.cap.max_अंतरभूत_data = cmd->max_अंतरभूत_data;

	INIT_LIST_HEAD(&obj->uevent.event_list);
	INIT_LIST_HEAD(&obj->mcast_list);

	attr.create_flags = cmd->create_flags;
	अगर (attr.create_flags & ~(IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK |
				IB_QP_CREATE_CROSS_CHANNEL |
				IB_QP_CREATE_MANAGED_SEND |
				IB_QP_CREATE_MANAGED_RECV |
				IB_QP_CREATE_SCATTER_FCS |
				IB_QP_CREATE_CVLAN_STRIPPING |
				IB_QP_CREATE_SOURCE_QPN |
				IB_QP_CREATE_PCI_WRITE_END_PADDING)) अणु
		ret = -EINVAL;
		जाओ err_put;
	पूर्ण

	अगर (attr.create_flags & IB_QP_CREATE_SOURCE_QPN) अणु
		अगर (!capable(CAP_NET_RAW)) अणु
			ret = -EPERM;
			जाओ err_put;
		पूर्ण

		attr.source_qpn = cmd->source_qpn;
	पूर्ण

	अगर (cmd->qp_type == IB_QPT_XRC_TGT)
		qp = ib_create_qp(pd, &attr);
	अन्यथा
		qp = _ib_create_qp(device, pd, &attr, &attrs->driver_udata, obj,
				   शून्य);

	अगर (IS_ERR(qp)) अणु
		ret = PTR_ERR(qp);
		जाओ err_put;
	पूर्ण

	अगर (cmd->qp_type != IB_QPT_XRC_TGT) अणु
		ret = ib_create_qp_security(qp, device);
		अगर (ret)
			जाओ err_cb;

		atomic_inc(&pd->usecnt);
		अगर (attr.send_cq)
			atomic_inc(&attr.send_cq->usecnt);
		अगर (attr.recv_cq)
			atomic_inc(&attr.recv_cq->usecnt);
		अगर (attr.srq)
			atomic_inc(&attr.srq->usecnt);
		अगर (ind_tbl)
			atomic_inc(&ind_tbl->usecnt);
	पूर्ण अन्यथा अणु
		/* It is करोne in _ib_create_qp क्रम other QP types */
		qp->uobject = obj;
	पूर्ण

	obj->uevent.uobject.object = qp;
	obj->uevent.event_file = READ_ONCE(attrs->ufile->शेष_async_file);
	अगर (obj->uevent.event_file)
		uverbs_uobject_get(&obj->uevent.event_file->uobj);

	अगर (xrcd) अणु
		obj->uxrcd = container_of(xrcd_uobj, काष्ठा ib_uxrcd_object,
					  uobject);
		atomic_inc(&obj->uxrcd->refcnt);
		uobj_put_पढ़ो(xrcd_uobj);
	पूर्ण

	अगर (pd)
		uobj_put_obj_पढ़ो(pd);
	अगर (scq)
		rdma_lookup_put_uobject(&scq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
	अगर (rcq && rcq != scq)
		rdma_lookup_put_uobject(&rcq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
	अगर (srq)
		rdma_lookup_put_uobject(&srq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
	अगर (ind_tbl)
		uobj_put_obj_पढ़ो(ind_tbl);
	uobj_finalize_uobj_create(&obj->uevent.uobject, attrs);

	resp.base.qpn             = qp->qp_num;
	resp.base.qp_handle       = obj->uevent.uobject.id;
	resp.base.max_recv_sge    = attr.cap.max_recv_sge;
	resp.base.max_send_sge    = attr.cap.max_send_sge;
	resp.base.max_recv_wr     = attr.cap.max_recv_wr;
	resp.base.max_send_wr     = attr.cap.max_send_wr;
	resp.base.max_अंतरभूत_data = attr.cap.max_अंतरभूत_data;
	resp.response_length = uverbs_response_length(attrs, माप(resp));
	वापस uverbs_response(attrs, &resp, माप(resp));

err_cb:
	ib_destroy_qp_user(qp, uverbs_get_cleared_udata(attrs));

err_put:
	अगर (!IS_ERR(xrcd_uobj))
		uobj_put_पढ़ो(xrcd_uobj);
	अगर (pd)
		uobj_put_obj_पढ़ो(pd);
	अगर (scq)
		rdma_lookup_put_uobject(&scq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
	अगर (rcq && rcq != scq)
		rdma_lookup_put_uobject(&rcq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
	अगर (srq)
		rdma_lookup_put_uobject(&srq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
	अगर (ind_tbl)
		uobj_put_obj_पढ़ो(ind_tbl);

	uobj_alloc_पात(&obj->uevent.uobject, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_create_qp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_qp      cmd;
	काष्ठा ib_uverbs_ex_create_qp	cmd_ex;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	स_रखो(&cmd_ex, 0, माप(cmd_ex));
	cmd_ex.user_handle = cmd.user_handle;
	cmd_ex.pd_handle = cmd.pd_handle;
	cmd_ex.send_cq_handle = cmd.send_cq_handle;
	cmd_ex.recv_cq_handle = cmd.recv_cq_handle;
	cmd_ex.srq_handle = cmd.srq_handle;
	cmd_ex.max_send_wr = cmd.max_send_wr;
	cmd_ex.max_recv_wr = cmd.max_recv_wr;
	cmd_ex.max_send_sge = cmd.max_send_sge;
	cmd_ex.max_recv_sge = cmd.max_recv_sge;
	cmd_ex.max_अंतरभूत_data = cmd.max_अंतरभूत_data;
	cmd_ex.sq_sig_all = cmd.sq_sig_all;
	cmd_ex.qp_type = cmd.qp_type;
	cmd_ex.is_srq = cmd.is_srq;

	वापस create_qp(attrs, &cmd_ex);
पूर्ण

अटल पूर्णांक ib_uverbs_ex_create_qp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_create_qp cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (cmd.comp_mask & ~IB_UVERBS_CREATE_QP_SUP_COMP_MASK)
		वापस -EINVAL;

	अगर (cmd.reserved)
		वापस -EINVAL;

	वापस create_qp(attrs, &cmd);
पूर्ण

अटल पूर्णांक ib_uverbs_खोलो_qp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_qp_resp resp = अणुपूर्ण;
	काष्ठा ib_uverbs_खोलो_qp        cmd;
	काष्ठा ib_uqp_object           *obj;
	काष्ठा ib_xrcd		       *xrcd;
	काष्ठा ib_qp                   *qp;
	काष्ठा ib_qp_खोलो_attr          attr = अणुपूर्ण;
	पूर्णांक ret;
	काष्ठा ib_uobject *xrcd_uobj;
	काष्ठा ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	obj = (काष्ठा ib_uqp_object *)uobj_alloc(UVERBS_OBJECT_QP, attrs,
						 &ib_dev);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	xrcd_uobj = uobj_get_पढ़ो(UVERBS_OBJECT_XRCD, cmd.pd_handle, attrs);
	अगर (IS_ERR(xrcd_uobj)) अणु
		ret = -EINVAL;
		जाओ err_put;
	पूर्ण

	xrcd = (काष्ठा ib_xrcd *)xrcd_uobj->object;
	अगर (!xrcd) अणु
		ret = -EINVAL;
		जाओ err_xrcd;
	पूर्ण

	attr.event_handler = ib_uverbs_qp_event_handler;
	attr.qp_num        = cmd.qpn;
	attr.qp_type       = cmd.qp_type;

	INIT_LIST_HEAD(&obj->uevent.event_list);
	INIT_LIST_HEAD(&obj->mcast_list);

	qp = ib_खोलो_qp(xrcd, &attr);
	अगर (IS_ERR(qp)) अणु
		ret = PTR_ERR(qp);
		जाओ err_xrcd;
	पूर्ण

	obj->uevent.uobject.object = qp;
	obj->uevent.uobject.user_handle = cmd.user_handle;

	obj->uxrcd = container_of(xrcd_uobj, काष्ठा ib_uxrcd_object, uobject);
	atomic_inc(&obj->uxrcd->refcnt);
	qp->uobject = obj;
	uobj_put_पढ़ो(xrcd_uobj);
	uobj_finalize_uobj_create(&obj->uevent.uobject, attrs);

	resp.qpn = qp->qp_num;
	resp.qp_handle = obj->uevent.uobject.id;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_xrcd:
	uobj_put_पढ़ो(xrcd_uobj);
err_put:
	uobj_alloc_पात(&obj->uevent.uobject, attrs);
	वापस ret;
पूर्ण

अटल व्योम copy_ah_attr_to_uverbs(काष्ठा ib_uverbs_qp_dest *uverb_attr,
				   काष्ठा rdma_ah_attr *rdma_attr)
अणु
	स्थिर काष्ठा ib_global_route   *grh;

	uverb_attr->dlid              = rdma_ah_get_dlid(rdma_attr);
	uverb_attr->sl                = rdma_ah_get_sl(rdma_attr);
	uverb_attr->src_path_bits     = rdma_ah_get_path_bits(rdma_attr);
	uverb_attr->अटल_rate       = rdma_ah_get_अटल_rate(rdma_attr);
	uverb_attr->is_global         = !!(rdma_ah_get_ah_flags(rdma_attr) &
					 IB_AH_GRH);
	अगर (uverb_attr->is_global) अणु
		grh = rdma_ah_पढ़ो_grh(rdma_attr);
		स_नकल(uverb_attr->dgid, grh->dgid.raw, 16);
		uverb_attr->flow_label        = grh->flow_label;
		uverb_attr->sgid_index        = grh->sgid_index;
		uverb_attr->hop_limit         = grh->hop_limit;
		uverb_attr->traffic_class     = grh->traffic_class;
	पूर्ण
	uverb_attr->port_num          = rdma_ah_get_port_num(rdma_attr);
पूर्ण

अटल पूर्णांक ib_uverbs_query_qp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_query_qp      cmd;
	काष्ठा ib_uverbs_query_qp_resp resp;
	काष्ठा ib_qp                   *qp;
	काष्ठा ib_qp_attr              *attr;
	काष्ठा ib_qp_init_attr         *init_attr;
	पूर्णांक                            ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	attr      = kदो_स्मृति(माप *attr, GFP_KERNEL);
	init_attr = kदो_स्मृति(माप *init_attr, GFP_KERNEL);
	अगर (!attr || !init_attr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	qp = uobj_get_obj_पढ़ो(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	अगर (!qp) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = ib_query_qp(qp, attr, cmd.attr_mask, init_attr);

	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);

	अगर (ret)
		जाओ out;

	स_रखो(&resp, 0, माप resp);

	resp.qp_state               = attr->qp_state;
	resp.cur_qp_state           = attr->cur_qp_state;
	resp.path_mtu               = attr->path_mtu;
	resp.path_mig_state         = attr->path_mig_state;
	resp.qkey                   = attr->qkey;
	resp.rq_psn                 = attr->rq_psn;
	resp.sq_psn                 = attr->sq_psn;
	resp.dest_qp_num            = attr->dest_qp_num;
	resp.qp_access_flags        = attr->qp_access_flags;
	resp.pkey_index             = attr->pkey_index;
	resp.alt_pkey_index         = attr->alt_pkey_index;
	resp.sq_draining            = attr->sq_draining;
	resp.max_rd_atomic          = attr->max_rd_atomic;
	resp.max_dest_rd_atomic     = attr->max_dest_rd_atomic;
	resp.min_rnr_समयr          = attr->min_rnr_समयr;
	resp.port_num               = attr->port_num;
	resp.समयout                = attr->समयout;
	resp.retry_cnt              = attr->retry_cnt;
	resp.rnr_retry              = attr->rnr_retry;
	resp.alt_port_num           = attr->alt_port_num;
	resp.alt_समयout            = attr->alt_समयout;

	copy_ah_attr_to_uverbs(&resp.dest, &attr->ah_attr);
	copy_ah_attr_to_uverbs(&resp.alt_dest, &attr->alt_ah_attr);

	resp.max_send_wr            = init_attr->cap.max_send_wr;
	resp.max_recv_wr            = init_attr->cap.max_recv_wr;
	resp.max_send_sge           = init_attr->cap.max_send_sge;
	resp.max_recv_sge           = init_attr->cap.max_recv_sge;
	resp.max_अंतरभूत_data        = init_attr->cap.max_अंतरभूत_data;
	resp.sq_sig_all             = init_attr->sq_sig_type == IB_SIGNAL_ALL_WR;

	ret = uverbs_response(attrs, &resp, माप(resp));

out:
	kमुक्त(attr);
	kमुक्त(init_attr);

	वापस ret;
पूर्ण

/* Remove ignored fields set in the attribute mask */
अटल पूर्णांक modअगरy_qp_mask(क्रमागत ib_qp_type qp_type, पूर्णांक mask)
अणु
	चयन (qp_type) अणु
	हाल IB_QPT_XRC_INI:
		वापस mask & ~(IB_QP_MAX_DEST_RD_ATOMIC | IB_QP_MIN_RNR_TIMER);
	हाल IB_QPT_XRC_TGT:
		वापस mask & ~(IB_QP_MAX_QP_RD_ATOMIC | IB_QP_RETRY_CNT |
				IB_QP_RNR_RETRY);
	शेष:
		वापस mask;
	पूर्ण
पूर्ण

अटल व्योम copy_ah_attr_from_uverbs(काष्ठा ib_device *dev,
				     काष्ठा rdma_ah_attr *rdma_attr,
				     काष्ठा ib_uverbs_qp_dest *uverb_attr)
अणु
	rdma_attr->type = rdma_ah_find_type(dev, uverb_attr->port_num);
	अगर (uverb_attr->is_global) अणु
		rdma_ah_set_grh(rdma_attr, शून्य,
				uverb_attr->flow_label,
				uverb_attr->sgid_index,
				uverb_attr->hop_limit,
				uverb_attr->traffic_class);
		rdma_ah_set_dgid_raw(rdma_attr, uverb_attr->dgid);
	पूर्ण अन्यथा अणु
		rdma_ah_set_ah_flags(rdma_attr, 0);
	पूर्ण
	rdma_ah_set_dlid(rdma_attr, uverb_attr->dlid);
	rdma_ah_set_sl(rdma_attr, uverb_attr->sl);
	rdma_ah_set_path_bits(rdma_attr, uverb_attr->src_path_bits);
	rdma_ah_set_अटल_rate(rdma_attr, uverb_attr->अटल_rate);
	rdma_ah_set_port_num(rdma_attr, uverb_attr->port_num);
	rdma_ah_set_make_grd(rdma_attr, false);
पूर्ण

अटल पूर्णांक modअगरy_qp(काष्ठा uverbs_attr_bundle *attrs,
		     काष्ठा ib_uverbs_ex_modअगरy_qp *cmd)
अणु
	काष्ठा ib_qp_attr *attr;
	काष्ठा ib_qp *qp;
	पूर्णांक ret;

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	qp = uobj_get_obj_पढ़ो(qp, UVERBS_OBJECT_QP, cmd->base.qp_handle,
			       attrs);
	अगर (!qp) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((cmd->base.attr_mask & IB_QP_PORT) &&
	    !rdma_is_port_valid(qp->device, cmd->base.port_num)) अणु
		ret = -EINVAL;
		जाओ release_qp;
	पूर्ण

	अगर ((cmd->base.attr_mask & IB_QP_AV)) अणु
		अगर (!rdma_is_port_valid(qp->device, cmd->base.dest.port_num)) अणु
			ret = -EINVAL;
			जाओ release_qp;
		पूर्ण

		अगर (cmd->base.attr_mask & IB_QP_STATE &&
		    cmd->base.qp_state == IB_QPS_RTR) अणु
		/* We are in INIT->RTR TRANSITION (अगर we are not,
		 * this transition will be rejected in subsequent checks).
		 * In the INIT->RTR transition, we cannot have IB_QP_PORT set,
		 * but the IB_QP_STATE flag is required.
		 *
		 * Since kernel 3.14 (commit dbf727de7440), the uverbs driver,
		 * when IB_QP_AV is set, has required inclusion of a valid
		 * port number in the primary AV. (AVs are created and handled
		 * dअगरferently क्रम infiniband and ethernet (RoCE) ports).
		 *
		 * Check the port number included in the primary AV against
		 * the port number in the qp काष्ठा, which was set (and saved)
		 * in the RST->INIT transition.
		 */
			अगर (cmd->base.dest.port_num != qp->real_qp->port) अणु
				ret = -EINVAL;
				जाओ release_qp;
			पूर्ण
		पूर्ण अन्यथा अणु
		/* We are in SQD->SQD. (If we are not, this transition will
		 * be rejected later in the verbs layer checks).
		 * Check क्रम both IB_QP_PORT and IB_QP_AV, these can be set
		 * together in the SQD->SQD transition.
		 *
		 * If only IP_QP_AV was set, add in IB_QP_PORT as well (the
		 * verbs layer driver करोes not track primary port changes
		 * resulting from path migration. Thus, in SQD, अगर the primary
		 * AV is modअगरied, the primary port should also be modअगरied).
		 *
		 * Note that in this transition, the IB_QP_STATE flag
		 * is not allowed.
		 */
			अगर (((cmd->base.attr_mask & (IB_QP_AV | IB_QP_PORT))
			     == (IB_QP_AV | IB_QP_PORT)) &&
			    cmd->base.port_num != cmd->base.dest.port_num) अणु
				ret = -EINVAL;
				जाओ release_qp;
			पूर्ण
			अगर ((cmd->base.attr_mask & (IB_QP_AV | IB_QP_PORT))
			    == IB_QP_AV) अणु
				cmd->base.attr_mask |= IB_QP_PORT;
				cmd->base.port_num = cmd->base.dest.port_num;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((cmd->base.attr_mask & IB_QP_ALT_PATH) &&
	    (!rdma_is_port_valid(qp->device, cmd->base.alt_port_num) ||
	    !rdma_is_port_valid(qp->device, cmd->base.alt_dest.port_num) ||
	    cmd->base.alt_port_num != cmd->base.alt_dest.port_num)) अणु
		ret = -EINVAL;
		जाओ release_qp;
	पूर्ण

	अगर ((cmd->base.attr_mask & IB_QP_CUR_STATE &&
	    cmd->base.cur_qp_state > IB_QPS_ERR) ||
	    (cmd->base.attr_mask & IB_QP_STATE &&
	    cmd->base.qp_state > IB_QPS_ERR)) अणु
		ret = -EINVAL;
		जाओ release_qp;
	पूर्ण

	अगर (cmd->base.attr_mask & IB_QP_STATE)
		attr->qp_state = cmd->base.qp_state;
	अगर (cmd->base.attr_mask & IB_QP_CUR_STATE)
		attr->cur_qp_state = cmd->base.cur_qp_state;
	अगर (cmd->base.attr_mask & IB_QP_PATH_MTU)
		attr->path_mtu = cmd->base.path_mtu;
	अगर (cmd->base.attr_mask & IB_QP_PATH_MIG_STATE)
		attr->path_mig_state = cmd->base.path_mig_state;
	अगर (cmd->base.attr_mask & IB_QP_QKEY)
		attr->qkey = cmd->base.qkey;
	अगर (cmd->base.attr_mask & IB_QP_RQ_PSN)
		attr->rq_psn = cmd->base.rq_psn;
	अगर (cmd->base.attr_mask & IB_QP_SQ_PSN)
		attr->sq_psn = cmd->base.sq_psn;
	अगर (cmd->base.attr_mask & IB_QP_DEST_QPN)
		attr->dest_qp_num = cmd->base.dest_qp_num;
	अगर (cmd->base.attr_mask & IB_QP_ACCESS_FLAGS)
		attr->qp_access_flags = cmd->base.qp_access_flags;
	अगर (cmd->base.attr_mask & IB_QP_PKEY_INDEX)
		attr->pkey_index = cmd->base.pkey_index;
	अगर (cmd->base.attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY)
		attr->en_sqd_async_notअगरy = cmd->base.en_sqd_async_notअगरy;
	अगर (cmd->base.attr_mask & IB_QP_MAX_QP_RD_ATOMIC)
		attr->max_rd_atomic = cmd->base.max_rd_atomic;
	अगर (cmd->base.attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		attr->max_dest_rd_atomic = cmd->base.max_dest_rd_atomic;
	अगर (cmd->base.attr_mask & IB_QP_MIN_RNR_TIMER)
		attr->min_rnr_समयr = cmd->base.min_rnr_समयr;
	अगर (cmd->base.attr_mask & IB_QP_PORT)
		attr->port_num = cmd->base.port_num;
	अगर (cmd->base.attr_mask & IB_QP_TIMEOUT)
		attr->समयout = cmd->base.समयout;
	अगर (cmd->base.attr_mask & IB_QP_RETRY_CNT)
		attr->retry_cnt = cmd->base.retry_cnt;
	अगर (cmd->base.attr_mask & IB_QP_RNR_RETRY)
		attr->rnr_retry = cmd->base.rnr_retry;
	अगर (cmd->base.attr_mask & IB_QP_ALT_PATH) अणु
		attr->alt_port_num = cmd->base.alt_port_num;
		attr->alt_समयout = cmd->base.alt_समयout;
		attr->alt_pkey_index = cmd->base.alt_pkey_index;
	पूर्ण
	अगर (cmd->base.attr_mask & IB_QP_RATE_LIMIT)
		attr->rate_limit = cmd->rate_limit;

	अगर (cmd->base.attr_mask & IB_QP_AV)
		copy_ah_attr_from_uverbs(qp->device, &attr->ah_attr,
					 &cmd->base.dest);

	अगर (cmd->base.attr_mask & IB_QP_ALT_PATH)
		copy_ah_attr_from_uverbs(qp->device, &attr->alt_ah_attr,
					 &cmd->base.alt_dest);

	ret = ib_modअगरy_qp_with_udata(qp, attr,
				      modअगरy_qp_mask(qp->qp_type,
						     cmd->base.attr_mask),
				      &attrs->driver_udata);

release_qp:
	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
out:
	kमुक्त(attr);

	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_modअगरy_qp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_modअगरy_qp cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd.base, माप(cmd.base));
	अगर (ret)
		वापस ret;

	अगर (cmd.base.attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	वापस modअगरy_qp(attrs, &cmd);
पूर्ण

अटल पूर्णांक ib_uverbs_ex_modअगरy_qp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_modअगरy_qp cmd;
	काष्ठा ib_uverbs_ex_modअगरy_qp_resp resp = अणु
		.response_length = uverbs_response_length(attrs, माप(resp))
	पूर्ण;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	/*
	 * Last bit is reserved क्रम extending the attr_mask by
	 * using another field.
	 */
	अगर (cmd.base.attr_mask & ~(IB_QP_ATTR_STANDARD_BITS | IB_QP_RATE_LIMIT))
		वापस -EOPNOTSUPP;

	ret = modअगरy_qp(attrs, &cmd);
	अगर (ret)
		वापस ret;

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक ib_uverbs_destroy_qp(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_destroy_qp      cmd;
	काष्ठा ib_uverbs_destroy_qp_resp resp;
	काष्ठा ib_uobject		*uobj;
	काष्ठा ib_uqp_object        	*obj;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	uobj = uobj_get_destroy(UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	obj = container_of(uobj, काष्ठा ib_uqp_object, uevent.uobject);
	स_रखो(&resp, 0, माप(resp));
	resp.events_reported = obj->uevent.events_reported;

	uobj_put_destroy(uobj);

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल व्योम *alloc_wr(माप_प्रकार wr_size, __u32 num_sge)
अणु
	अगर (num_sge >= (U32_MAX - ALIGN(wr_size, माप(काष्ठा ib_sge))) /
			       माप(काष्ठा ib_sge))
		वापस शून्य;

	वापस kदो_स्मृति(ALIGN(wr_size, माप(काष्ठा ib_sge)) +
			       num_sge * माप(काष्ठा ib_sge),
		       GFP_KERNEL);
पूर्ण

अटल पूर्णांक ib_uverbs_post_send(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_post_send      cmd;
	काष्ठा ib_uverbs_post_send_resp resp;
	काष्ठा ib_uverbs_send_wr       *user_wr;
	काष्ठा ib_send_wr              *wr = शून्य, *last, *next;
	स्थिर काष्ठा ib_send_wr	       *bad_wr;
	काष्ठा ib_qp                   *qp;
	पूर्णांक                             i, sg_ind;
	पूर्णांक				is_ud;
	पूर्णांक ret, ret2;
	माप_प्रकार                          next_size;
	स्थिर काष्ठा ib_sge __user *sgls;
	स्थिर व्योम __user *wqes;
	काष्ठा uverbs_req_iter iter;

	ret = uverbs_request_start(attrs, &iter, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;
	wqes = uverbs_request_next_ptr(&iter, cmd.wqe_size * cmd.wr_count);
	अगर (IS_ERR(wqes))
		वापस PTR_ERR(wqes);
	sgls = uverbs_request_next_ptr(
		&iter, cmd.sge_count * माप(काष्ठा ib_uverbs_sge));
	अगर (IS_ERR(sgls))
		वापस PTR_ERR(sgls);
	ret = uverbs_request_finish(&iter);
	अगर (ret)
		वापस ret;

	user_wr = kदो_स्मृति(cmd.wqe_size, GFP_KERNEL);
	अगर (!user_wr)
		वापस -ENOMEM;

	qp = uobj_get_obj_पढ़ो(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	अगर (!qp) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	is_ud = qp->qp_type == IB_QPT_UD;
	sg_ind = 0;
	last = शून्य;
	क्रम (i = 0; i < cmd.wr_count; ++i) अणु
		अगर (copy_from_user(user_wr, wqes + i * cmd.wqe_size,
				   cmd.wqe_size)) अणु
			ret = -EFAULT;
			जाओ out_put;
		पूर्ण

		अगर (user_wr->num_sge + sg_ind > cmd.sge_count) अणु
			ret = -EINVAL;
			जाओ out_put;
		पूर्ण

		अगर (is_ud) अणु
			काष्ठा ib_ud_wr *ud;

			अगर (user_wr->opcode != IB_WR_SEND &&
			    user_wr->opcode != IB_WR_SEND_WITH_IMM) अणु
				ret = -EINVAL;
				जाओ out_put;
			पूर्ण

			next_size = माप(*ud);
			ud = alloc_wr(next_size, user_wr->num_sge);
			अगर (!ud) अणु
				ret = -ENOMEM;
				जाओ out_put;
			पूर्ण

			ud->ah = uobj_get_obj_पढ़ो(ah, UVERBS_OBJECT_AH,
						   user_wr->wr.ud.ah, attrs);
			अगर (!ud->ah) अणु
				kमुक्त(ud);
				ret = -EINVAL;
				जाओ out_put;
			पूर्ण
			ud->remote_qpn = user_wr->wr.ud.remote_qpn;
			ud->remote_qkey = user_wr->wr.ud.remote_qkey;

			next = &ud->wr;
		पूर्ण अन्यथा अगर (user_wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM ||
			   user_wr->opcode == IB_WR_RDMA_WRITE ||
			   user_wr->opcode == IB_WR_RDMA_READ) अणु
			काष्ठा ib_rdma_wr *rdma;

			next_size = माप(*rdma);
			rdma = alloc_wr(next_size, user_wr->num_sge);
			अगर (!rdma) अणु
				ret = -ENOMEM;
				जाओ out_put;
			पूर्ण

			rdma->remote_addr = user_wr->wr.rdma.remote_addr;
			rdma->rkey = user_wr->wr.rdma.rkey;

			next = &rdma->wr;
		पूर्ण अन्यथा अगर (user_wr->opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
			   user_wr->opcode == IB_WR_ATOMIC_FETCH_AND_ADD) अणु
			काष्ठा ib_atomic_wr *atomic;

			next_size = माप(*atomic);
			atomic = alloc_wr(next_size, user_wr->num_sge);
			अगर (!atomic) अणु
				ret = -ENOMEM;
				जाओ out_put;
			पूर्ण

			atomic->remote_addr = user_wr->wr.atomic.remote_addr;
			atomic->compare_add = user_wr->wr.atomic.compare_add;
			atomic->swap = user_wr->wr.atomic.swap;
			atomic->rkey = user_wr->wr.atomic.rkey;

			next = &atomic->wr;
		पूर्ण अन्यथा अगर (user_wr->opcode == IB_WR_SEND ||
			   user_wr->opcode == IB_WR_SEND_WITH_IMM ||
			   user_wr->opcode == IB_WR_SEND_WITH_INV) अणु
			next_size = माप(*next);
			next = alloc_wr(next_size, user_wr->num_sge);
			अगर (!next) अणु
				ret = -ENOMEM;
				जाओ out_put;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ out_put;
		पूर्ण

		अगर (user_wr->opcode == IB_WR_SEND_WITH_IMM ||
		    user_wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM) अणु
			next->ex.imm_data =
					(__be32 __क्रमce) user_wr->ex.imm_data;
		पूर्ण अन्यथा अगर (user_wr->opcode == IB_WR_SEND_WITH_INV) अणु
			next->ex.invalidate_rkey = user_wr->ex.invalidate_rkey;
		पूर्ण

		अगर (!last)
			wr = next;
		अन्यथा
			last->next = next;
		last = next;

		next->next       = शून्य;
		next->wr_id      = user_wr->wr_id;
		next->num_sge    = user_wr->num_sge;
		next->opcode     = user_wr->opcode;
		next->send_flags = user_wr->send_flags;

		अगर (next->num_sge) अणु
			next->sg_list = (व्योम *) next +
				ALIGN(next_size, माप(काष्ठा ib_sge));
			अगर (copy_from_user(next->sg_list, sgls + sg_ind,
					   next->num_sge *
						   माप(काष्ठा ib_sge))) अणु
				ret = -EFAULT;
				जाओ out_put;
			पूर्ण
			sg_ind += next->num_sge;
		पूर्ण अन्यथा
			next->sg_list = शून्य;
	पूर्ण

	resp.bad_wr = 0;
	ret = qp->device->ops.post_send(qp->real_qp, wr, &bad_wr);
	अगर (ret)
		क्रम (next = wr; next; next = next->next) अणु
			++resp.bad_wr;
			अगर (next == bad_wr)
				अवरोध;
		पूर्ण

	ret2 = uverbs_response(attrs, &resp, माप(resp));
	अगर (ret2)
		ret = ret2;

out_put:
	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);

	जबतक (wr) अणु
		अगर (is_ud && ud_wr(wr)->ah)
			uobj_put_obj_पढ़ो(ud_wr(wr)->ah);
		next = wr->next;
		kमुक्त(wr);
		wr = next;
	पूर्ण

out:
	kमुक्त(user_wr);

	वापस ret;
पूर्ण

अटल काष्ठा ib_recv_wr *
ib_uverbs_unmarshall_recv(काष्ठा uverbs_req_iter *iter, u32 wr_count,
			  u32 wqe_size, u32 sge_count)
अणु
	काष्ठा ib_uverbs_recv_wr *user_wr;
	काष्ठा ib_recv_wr        *wr = शून्य, *last, *next;
	पूर्णांक                       sg_ind;
	पूर्णांक                       i;
	पूर्णांक                       ret;
	स्थिर काष्ठा ib_sge __user *sgls;
	स्थिर व्योम __user *wqes;

	अगर (wqe_size < माप(काष्ठा ib_uverbs_recv_wr))
		वापस ERR_PTR(-EINVAL);

	wqes = uverbs_request_next_ptr(iter, wqe_size * wr_count);
	अगर (IS_ERR(wqes))
		वापस ERR_CAST(wqes);
	sgls = uverbs_request_next_ptr(
		iter, sge_count * माप(काष्ठा ib_uverbs_sge));
	अगर (IS_ERR(sgls))
		वापस ERR_CAST(sgls);
	ret = uverbs_request_finish(iter);
	अगर (ret)
		वापस ERR_PTR(ret);

	user_wr = kदो_स्मृति(wqe_size, GFP_KERNEL);
	अगर (!user_wr)
		वापस ERR_PTR(-ENOMEM);

	sg_ind = 0;
	last = शून्य;
	क्रम (i = 0; i < wr_count; ++i) अणु
		अगर (copy_from_user(user_wr, wqes + i * wqe_size,
				   wqe_size)) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		अगर (user_wr->num_sge + sg_ind > sge_count) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (user_wr->num_sge >=
		    (U32_MAX - ALIGN(माप(*next), माप(काष्ठा ib_sge))) /
			    माप(काष्ठा ib_sge)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		next = kदो_स्मृति(ALIGN(माप(*next), माप(काष्ठा ib_sge)) +
				       user_wr->num_sge * माप(काष्ठा ib_sge),
			       GFP_KERNEL);
		अगर (!next) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		अगर (!last)
			wr = next;
		अन्यथा
			last->next = next;
		last = next;

		next->next       = शून्य;
		next->wr_id      = user_wr->wr_id;
		next->num_sge    = user_wr->num_sge;

		अगर (next->num_sge) अणु
			next->sg_list = (व्योम *)next +
				ALIGN(माप(*next), माप(काष्ठा ib_sge));
			अगर (copy_from_user(next->sg_list, sgls + sg_ind,
					   next->num_sge *
						   माप(काष्ठा ib_sge))) अणु
				ret = -EFAULT;
				जाओ err;
			पूर्ण
			sg_ind += next->num_sge;
		पूर्ण अन्यथा
			next->sg_list = शून्य;
	पूर्ण

	kमुक्त(user_wr);
	वापस wr;

err:
	kमुक्त(user_wr);

	जबतक (wr) अणु
		next = wr->next;
		kमुक्त(wr);
		wr = next;
	पूर्ण

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक ib_uverbs_post_recv(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_post_recv      cmd;
	काष्ठा ib_uverbs_post_recv_resp resp;
	काष्ठा ib_recv_wr              *wr, *next;
	स्थिर काष्ठा ib_recv_wr	       *bad_wr;
	काष्ठा ib_qp                   *qp;
	पूर्णांक ret, ret2;
	काष्ठा uverbs_req_iter iter;

	ret = uverbs_request_start(attrs, &iter, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	wr = ib_uverbs_unmarshall_recv(&iter, cmd.wr_count, cmd.wqe_size,
				       cmd.sge_count);
	अगर (IS_ERR(wr))
		वापस PTR_ERR(wr);

	qp = uobj_get_obj_पढ़ो(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	अगर (!qp) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	resp.bad_wr = 0;
	ret = qp->device->ops.post_recv(qp->real_qp, wr, &bad_wr);

	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	अगर (ret) अणु
		क्रम (next = wr; next; next = next->next) अणु
			++resp.bad_wr;
			अगर (next == bad_wr)
				अवरोध;
		पूर्ण
	पूर्ण

	ret2 = uverbs_response(attrs, &resp, माप(resp));
	अगर (ret2)
		ret = ret2;
out:
	जबतक (wr) अणु
		next = wr->next;
		kमुक्त(wr);
		wr = next;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_post_srq_recv(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_post_srq_recv      cmd;
	काष्ठा ib_uverbs_post_srq_recv_resp resp;
	काष्ठा ib_recv_wr                  *wr, *next;
	स्थिर काष्ठा ib_recv_wr		   *bad_wr;
	काष्ठा ib_srq                      *srq;
	पूर्णांक ret, ret2;
	काष्ठा uverbs_req_iter iter;

	ret = uverbs_request_start(attrs, &iter, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	wr = ib_uverbs_unmarshall_recv(&iter, cmd.wr_count, cmd.wqe_size,
				       cmd.sge_count);
	अगर (IS_ERR(wr))
		वापस PTR_ERR(wr);

	srq = uobj_get_obj_पढ़ो(srq, UVERBS_OBJECT_SRQ, cmd.srq_handle, attrs);
	अगर (!srq) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	resp.bad_wr = 0;
	ret = srq->device->ops.post_srq_recv(srq, wr, &bad_wr);

	rdma_lookup_put_uobject(&srq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);

	अगर (ret)
		क्रम (next = wr; next; next = next->next) अणु
			++resp.bad_wr;
			अगर (next == bad_wr)
				अवरोध;
		पूर्ण

	ret2 = uverbs_response(attrs, &resp, माप(resp));
	अगर (ret2)
		ret = ret2;

out:
	जबतक (wr) अणु
		next = wr->next;
		kमुक्त(wr);
		wr = next;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_create_ah(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_ah	 cmd;
	काष्ठा ib_uverbs_create_ah_resp	 resp;
	काष्ठा ib_uobject		*uobj;
	काष्ठा ib_pd			*pd;
	काष्ठा ib_ah			*ah;
	काष्ठा rdma_ah_attr		attr = अणुपूर्ण;
	पूर्णांक ret;
	काष्ठा ib_device *ib_dev;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	uobj = uobj_alloc(UVERBS_OBJECT_AH, attrs, &ib_dev);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	अगर (!rdma_is_port_valid(ib_dev, cmd.attr.port_num)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	pd = uobj_get_obj_पढ़ो(pd, UVERBS_OBJECT_PD, cmd.pd_handle, attrs);
	अगर (!pd) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	attr.type = rdma_ah_find_type(ib_dev, cmd.attr.port_num);
	rdma_ah_set_make_grd(&attr, false);
	rdma_ah_set_dlid(&attr, cmd.attr.dlid);
	rdma_ah_set_sl(&attr, cmd.attr.sl);
	rdma_ah_set_path_bits(&attr, cmd.attr.src_path_bits);
	rdma_ah_set_अटल_rate(&attr, cmd.attr.अटल_rate);
	rdma_ah_set_port_num(&attr, cmd.attr.port_num);

	अगर (cmd.attr.is_global) अणु
		rdma_ah_set_grh(&attr, शून्य, cmd.attr.grh.flow_label,
				cmd.attr.grh.sgid_index,
				cmd.attr.grh.hop_limit,
				cmd.attr.grh.traffic_class);
		rdma_ah_set_dgid_raw(&attr, cmd.attr.grh.dgid);
	पूर्ण अन्यथा अणु
		rdma_ah_set_ah_flags(&attr, 0);
	पूर्ण

	ah = rdma_create_user_ah(pd, &attr, &attrs->driver_udata);
	अगर (IS_ERR(ah)) अणु
		ret = PTR_ERR(ah);
		जाओ err_put;
	पूर्ण

	ah->uobject  = uobj;
	uobj->user_handle = cmd.user_handle;
	uobj->object = ah;
	uobj_put_obj_पढ़ो(pd);
	uobj_finalize_uobj_create(uobj, attrs);

	resp.ah_handle = uobj->id;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_put:
	uobj_put_obj_पढ़ो(pd);
err:
	uobj_alloc_पात(uobj, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_destroy_ah(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_destroy_ah cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	वापस uobj_perक्रमm_destroy(UVERBS_OBJECT_AH, cmd.ah_handle, attrs);
पूर्ण

अटल पूर्णांक ib_uverbs_attach_mcast(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_attach_mcast cmd;
	काष्ठा ib_qp                 *qp;
	काष्ठा ib_uqp_object         *obj;
	काष्ठा ib_uverbs_mcast_entry *mcast;
	पूर्णांक                           ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	qp = uobj_get_obj_पढ़ो(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	अगर (!qp)
		वापस -EINVAL;

	obj = qp->uobject;

	mutex_lock(&obj->mcast_lock);
	list_क्रम_each_entry(mcast, &obj->mcast_list, list)
		अगर (cmd.mlid == mcast->lid &&
		    !स_भेद(cmd.gid, mcast->gid.raw, माप mcast->gid.raw)) अणु
			ret = 0;
			जाओ out_put;
		पूर्ण

	mcast = kदो_स्मृति(माप *mcast, GFP_KERNEL);
	अगर (!mcast) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण

	mcast->lid = cmd.mlid;
	स_नकल(mcast->gid.raw, cmd.gid, माप mcast->gid.raw);

	ret = ib_attach_mcast(qp, &mcast->gid, cmd.mlid);
	अगर (!ret)
		list_add_tail(&mcast->list, &obj->mcast_list);
	अन्यथा
		kमुक्त(mcast);

out_put:
	mutex_unlock(&obj->mcast_lock);
	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);

	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_detach_mcast(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_detach_mcast cmd;
	काष्ठा ib_uqp_object         *obj;
	काष्ठा ib_qp                 *qp;
	काष्ठा ib_uverbs_mcast_entry *mcast;
	पूर्णांक                           ret;
	bool                          found = false;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	qp = uobj_get_obj_पढ़ो(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	अगर (!qp)
		वापस -EINVAL;

	obj = qp->uobject;
	mutex_lock(&obj->mcast_lock);

	list_क्रम_each_entry(mcast, &obj->mcast_list, list)
		अगर (cmd.mlid == mcast->lid &&
		    !स_भेद(cmd.gid, mcast->gid.raw, माप mcast->gid.raw)) अणु
			list_del(&mcast->list);
			kमुक्त(mcast);
			found = true;
			अवरोध;
		पूर्ण

	अगर (!found) अणु
		ret = -EINVAL;
		जाओ out_put;
	पूर्ण

	ret = ib_detach_mcast(qp, (जोड़ ib_gid *)cmd.gid, cmd.mlid);

out_put:
	mutex_unlock(&obj->mcast_lock);
	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	वापस ret;
पूर्ण

काष्ठा ib_uflow_resources *flow_resources_alloc(माप_प्रकार num_specs)
अणु
	काष्ठा ib_uflow_resources *resources;

	resources = kzalloc(माप(*resources), GFP_KERNEL);

	अगर (!resources)
		वापस शून्य;

	अगर (!num_specs)
		जाओ out;

	resources->counters =
		kसुस्मृति(num_specs, माप(*resources->counters), GFP_KERNEL);
	resources->collection =
		kसुस्मृति(num_specs, माप(*resources->collection), GFP_KERNEL);

	अगर (!resources->counters || !resources->collection)
		जाओ err;

out:
	resources->max = num_specs;
	वापस resources;

err:
	kमुक्त(resources->counters);
	kमुक्त(resources);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(flow_resources_alloc);

व्योम ib_uverbs_flow_resources_मुक्त(काष्ठा ib_uflow_resources *uflow_res)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!uflow_res)
		वापस;

	क्रम (i = 0; i < uflow_res->collection_num; i++)
		atomic_dec(&uflow_res->collection[i]->usecnt);

	क्रम (i = 0; i < uflow_res->counters_num; i++)
		atomic_dec(&uflow_res->counters[i]->usecnt);

	kमुक्त(uflow_res->collection);
	kमुक्त(uflow_res->counters);
	kमुक्त(uflow_res);
पूर्ण
EXPORT_SYMBOL(ib_uverbs_flow_resources_मुक्त);

व्योम flow_resources_add(काष्ठा ib_uflow_resources *uflow_res,
			क्रमागत ib_flow_spec_type type,
			व्योम *ibobj)
अणु
	WARN_ON(uflow_res->num >= uflow_res->max);

	चयन (type) अणु
	हाल IB_FLOW_SPEC_ACTION_HANDLE:
		atomic_inc(&((काष्ठा ib_flow_action *)ibobj)->usecnt);
		uflow_res->collection[uflow_res->collection_num++] =
			(काष्ठा ib_flow_action *)ibobj;
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_COUNT:
		atomic_inc(&((काष्ठा ib_counters *)ibobj)->usecnt);
		uflow_res->counters[uflow_res->counters_num++] =
			(काष्ठा ib_counters *)ibobj;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	uflow_res->num++;
पूर्ण
EXPORT_SYMBOL(flow_resources_add);

अटल पूर्णांक kern_spec_to_ib_spec_action(काष्ठा uverbs_attr_bundle *attrs,
				       काष्ठा ib_uverbs_flow_spec *kern_spec,
				       जोड़ ib_flow_spec *ib_spec,
				       काष्ठा ib_uflow_resources *uflow_res)
अणु
	ib_spec->type = kern_spec->type;
	चयन (ib_spec->type) अणु
	हाल IB_FLOW_SPEC_ACTION_TAG:
		अगर (kern_spec->flow_tag.size !=
		    माप(काष्ठा ib_uverbs_flow_spec_action_tag))
			वापस -EINVAL;

		ib_spec->flow_tag.size = माप(काष्ठा ib_flow_spec_action_tag);
		ib_spec->flow_tag.tag_id = kern_spec->flow_tag.tag_id;
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_DROP:
		अगर (kern_spec->drop.size !=
		    माप(काष्ठा ib_uverbs_flow_spec_action_drop))
			वापस -EINVAL;

		ib_spec->drop.size = माप(काष्ठा ib_flow_spec_action_drop);
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_HANDLE:
		अगर (kern_spec->action.size !=
		    माप(काष्ठा ib_uverbs_flow_spec_action_handle))
			वापस -EOPNOTSUPP;
		ib_spec->action.act = uobj_get_obj_पढ़ो(flow_action,
							UVERBS_OBJECT_FLOW_ACTION,
							kern_spec->action.handle,
							attrs);
		अगर (!ib_spec->action.act)
			वापस -EINVAL;
		ib_spec->action.size =
			माप(काष्ठा ib_flow_spec_action_handle);
		flow_resources_add(uflow_res,
				   IB_FLOW_SPEC_ACTION_HANDLE,
				   ib_spec->action.act);
		uobj_put_obj_पढ़ो(ib_spec->action.act);
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_COUNT:
		अगर (kern_spec->flow_count.size !=
			माप(काष्ठा ib_uverbs_flow_spec_action_count))
			वापस -EINVAL;
		ib_spec->flow_count.counters =
			uobj_get_obj_पढ़ो(counters,
					  UVERBS_OBJECT_COUNTERS,
					  kern_spec->flow_count.handle,
					  attrs);
		अगर (!ib_spec->flow_count.counters)
			वापस -EINVAL;
		ib_spec->flow_count.size =
				माप(काष्ठा ib_flow_spec_action_count);
		flow_resources_add(uflow_res,
				   IB_FLOW_SPEC_ACTION_COUNT,
				   ib_spec->flow_count.counters);
		uobj_put_obj_पढ़ो(ib_spec->flow_count.counters);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार spec_filter_size(स्थिर व्योम *kern_spec_filter, u16 kern_filter_size,
				u16 ib_real_filter_sz)
अणु
	/*
	 * User space filter काष्ठाures must be 64 bit aligned, otherwise this
	 * may pass, but we won't handle additional new attributes.
	 */

	अगर (kern_filter_size > ib_real_filter_sz) अणु
		अगर (स_प्रथम_inv(kern_spec_filter +
			       ib_real_filter_sz, 0,
			       kern_filter_size - ib_real_filter_sz))
			वापस -EINVAL;
		वापस ib_real_filter_sz;
	पूर्ण
	वापस kern_filter_size;
पूर्ण

पूर्णांक ib_uverbs_kern_spec_to_ib_spec_filter(क्रमागत ib_flow_spec_type type,
					  स्थिर व्योम *kern_spec_mask,
					  स्थिर व्योम *kern_spec_val,
					  माप_प्रकार kern_filter_sz,
					  जोड़ ib_flow_spec *ib_spec)
अणु
	sमाप_प्रकार actual_filter_sz;
	sमाप_प्रकार ib_filter_sz;

	/* User flow spec size must be aligned to 4 bytes */
	अगर (kern_filter_sz != ALIGN(kern_filter_sz, 4))
		वापस -EINVAL;

	ib_spec->type = type;

	अगर (ib_spec->type == (IB_FLOW_SPEC_INNER | IB_FLOW_SPEC_VXLAN_TUNNEL))
		वापस -EINVAL;

	चयन (ib_spec->type & ~IB_FLOW_SPEC_INNER) अणु
	हाल IB_FLOW_SPEC_ETH:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_eth_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->size = माप(काष्ठा ib_flow_spec_eth);
		स_नकल(&ib_spec->eth.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->eth.mask, kern_spec_mask, actual_filter_sz);
		अवरोध;
	हाल IB_FLOW_SPEC_IPV4:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_ipv4_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->size = माप(काष्ठा ib_flow_spec_ipv4);
		स_नकल(&ib_spec->ipv4.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->ipv4.mask, kern_spec_mask, actual_filter_sz);
		अवरोध;
	हाल IB_FLOW_SPEC_IPV6:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_ipv6_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->size = माप(काष्ठा ib_flow_spec_ipv6);
		स_नकल(&ib_spec->ipv6.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->ipv6.mask, kern_spec_mask, actual_filter_sz);

		अगर ((ntohl(ib_spec->ipv6.mask.flow_label)) >= BIT(20) ||
		    (ntohl(ib_spec->ipv6.val.flow_label)) >= BIT(20))
			वापस -EINVAL;
		अवरोध;
	हाल IB_FLOW_SPEC_TCP:
	हाल IB_FLOW_SPEC_UDP:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_tcp_udp_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->size = माप(काष्ठा ib_flow_spec_tcp_udp);
		स_नकल(&ib_spec->tcp_udp.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->tcp_udp.mask, kern_spec_mask, actual_filter_sz);
		अवरोध;
	हाल IB_FLOW_SPEC_VXLAN_TUNNEL:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_tunnel_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->tunnel.size = माप(काष्ठा ib_flow_spec_tunnel);
		स_नकल(&ib_spec->tunnel.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->tunnel.mask, kern_spec_mask, actual_filter_sz);

		अगर ((ntohl(ib_spec->tunnel.mask.tunnel_id)) >= BIT(24) ||
		    (ntohl(ib_spec->tunnel.val.tunnel_id)) >= BIT(24))
			वापस -EINVAL;
		अवरोध;
	हाल IB_FLOW_SPEC_ESP:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_esp_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->esp.size = माप(काष्ठा ib_flow_spec_esp);
		स_नकल(&ib_spec->esp.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->esp.mask, kern_spec_mask, actual_filter_sz);
		अवरोध;
	हाल IB_FLOW_SPEC_GRE:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_gre_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->gre.size = माप(काष्ठा ib_flow_spec_gre);
		स_नकल(&ib_spec->gre.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->gre.mask, kern_spec_mask, actual_filter_sz);
		अवरोध;
	हाल IB_FLOW_SPEC_MPLS:
		ib_filter_sz = दुरत्व(काष्ठा ib_flow_mpls_filter, real_sz);
		actual_filter_sz = spec_filter_size(kern_spec_mask,
						    kern_filter_sz,
						    ib_filter_sz);
		अगर (actual_filter_sz <= 0)
			वापस -EINVAL;
		ib_spec->mpls.size = माप(काष्ठा ib_flow_spec_mpls);
		स_नकल(&ib_spec->mpls.val, kern_spec_val, actual_filter_sz);
		स_नकल(&ib_spec->mpls.mask, kern_spec_mask, actual_filter_sz);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kern_spec_to_ib_spec_filter(काष्ठा ib_uverbs_flow_spec *kern_spec,
				       जोड़ ib_flow_spec *ib_spec)
अणु
	माप_प्रकार kern_filter_sz;
	व्योम *kern_spec_mask;
	व्योम *kern_spec_val;

	अगर (check_sub_overflow((माप_प्रकार)kern_spec->hdr.size,
			       माप(काष्ठा ib_uverbs_flow_spec_hdr),
			       &kern_filter_sz))
		वापस -EINVAL;

	kern_filter_sz /= 2;

	kern_spec_val = (व्योम *)kern_spec +
		माप(काष्ठा ib_uverbs_flow_spec_hdr);
	kern_spec_mask = kern_spec_val + kern_filter_sz;

	वापस ib_uverbs_kern_spec_to_ib_spec_filter(kern_spec->type,
						     kern_spec_mask,
						     kern_spec_val,
						     kern_filter_sz, ib_spec);
पूर्ण

अटल पूर्णांक kern_spec_to_ib_spec(काष्ठा uverbs_attr_bundle *attrs,
				काष्ठा ib_uverbs_flow_spec *kern_spec,
				जोड़ ib_flow_spec *ib_spec,
				काष्ठा ib_uflow_resources *uflow_res)
अणु
	अगर (kern_spec->reserved)
		वापस -EINVAL;

	अगर (kern_spec->type >= IB_FLOW_SPEC_ACTION_TAG)
		वापस kern_spec_to_ib_spec_action(attrs, kern_spec, ib_spec,
						   uflow_res);
	अन्यथा
		वापस kern_spec_to_ib_spec_filter(kern_spec, ib_spec);
पूर्ण

अटल पूर्णांक ib_uverbs_ex_create_wq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_create_wq cmd;
	काष्ठा ib_uverbs_ex_create_wq_resp resp = अणुपूर्ण;
	काष्ठा ib_uwq_object           *obj;
	पूर्णांक err = 0;
	काष्ठा ib_cq *cq;
	काष्ठा ib_pd *pd;
	काष्ठा ib_wq *wq;
	काष्ठा ib_wq_init_attr wq_init_attr = अणुपूर्ण;
	काष्ठा ib_device *ib_dev;

	err = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (err)
		वापस err;

	अगर (cmd.comp_mask)
		वापस -EOPNOTSUPP;

	obj = (काष्ठा ib_uwq_object *)uobj_alloc(UVERBS_OBJECT_WQ, attrs,
						 &ib_dev);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	pd = uobj_get_obj_पढ़ो(pd, UVERBS_OBJECT_PD, cmd.pd_handle, attrs);
	अगर (!pd) अणु
		err = -EINVAL;
		जाओ err_uobj;
	पूर्ण

	cq = uobj_get_obj_पढ़ो(cq, UVERBS_OBJECT_CQ, cmd.cq_handle, attrs);
	अगर (!cq) अणु
		err = -EINVAL;
		जाओ err_put_pd;
	पूर्ण

	wq_init_attr.cq = cq;
	wq_init_attr.max_sge = cmd.max_sge;
	wq_init_attr.max_wr = cmd.max_wr;
	wq_init_attr.wq_type = cmd.wq_type;
	wq_init_attr.event_handler = ib_uverbs_wq_event_handler;
	wq_init_attr.create_flags = cmd.create_flags;
	INIT_LIST_HEAD(&obj->uevent.event_list);
	obj->uevent.uobject.user_handle = cmd.user_handle;

	wq = pd->device->ops.create_wq(pd, &wq_init_attr, &attrs->driver_udata);
	अगर (IS_ERR(wq)) अणु
		err = PTR_ERR(wq);
		जाओ err_put_cq;
	पूर्ण

	wq->uobject = obj;
	obj->uevent.uobject.object = wq;
	wq->wq_type = wq_init_attr.wq_type;
	wq->cq = cq;
	wq->pd = pd;
	wq->device = pd->device;
	atomic_set(&wq->usecnt, 0);
	atomic_inc(&pd->usecnt);
	atomic_inc(&cq->usecnt);
	obj->uevent.event_file = READ_ONCE(attrs->ufile->शेष_async_file);
	अगर (obj->uevent.event_file)
		uverbs_uobject_get(&obj->uevent.event_file->uobj);

	uobj_put_obj_पढ़ो(pd);
	rdma_lookup_put_uobject(&cq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	uobj_finalize_uobj_create(&obj->uevent.uobject, attrs);

	resp.wq_handle = obj->uevent.uobject.id;
	resp.max_sge = wq_init_attr.max_sge;
	resp.max_wr = wq_init_attr.max_wr;
	resp.wqn = wq->wq_num;
	resp.response_length = uverbs_response_length(attrs, माप(resp));
	वापस uverbs_response(attrs, &resp, माप(resp));

err_put_cq:
	rdma_lookup_put_uobject(&cq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
err_put_pd:
	uobj_put_obj_पढ़ो(pd);
err_uobj:
	uobj_alloc_पात(&obj->uevent.uobject, attrs);

	वापस err;
पूर्ण

अटल पूर्णांक ib_uverbs_ex_destroy_wq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_destroy_wq	cmd;
	काष्ठा ib_uverbs_ex_destroy_wq_resp	resp = अणुपूर्ण;
	काष्ठा ib_uobject		*uobj;
	काष्ठा ib_uwq_object		*obj;
	पूर्णांक				ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (cmd.comp_mask)
		वापस -EOPNOTSUPP;

	resp.response_length = uverbs_response_length(attrs, माप(resp));
	uobj = uobj_get_destroy(UVERBS_OBJECT_WQ, cmd.wq_handle, attrs);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	obj = container_of(uobj, काष्ठा ib_uwq_object, uevent.uobject);
	resp.events_reported = obj->uevent.events_reported;

	uobj_put_destroy(uobj);

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक ib_uverbs_ex_modअगरy_wq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_modअगरy_wq cmd;
	काष्ठा ib_wq *wq;
	काष्ठा ib_wq_attr wq_attr = अणुपूर्ण;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (!cmd.attr_mask)
		वापस -EINVAL;

	अगर (cmd.attr_mask > (IB_WQ_STATE | IB_WQ_CUR_STATE | IB_WQ_FLAGS))
		वापस -EINVAL;

	wq = uobj_get_obj_पढ़ो(wq, UVERBS_OBJECT_WQ, cmd.wq_handle, attrs);
	अगर (!wq)
		वापस -EINVAL;

	wq_attr.curr_wq_state = cmd.curr_wq_state;
	wq_attr.wq_state = cmd.wq_state;
	अगर (cmd.attr_mask & IB_WQ_FLAGS) अणु
		wq_attr.flags = cmd.flags;
		wq_attr.flags_mask = cmd.flags_mask;
	पूर्ण
	ret = wq->device->ops.modअगरy_wq(wq, &wq_attr, cmd.attr_mask,
					&attrs->driver_udata);
	rdma_lookup_put_uobject(&wq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_ex_create_rwq_ind_table(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_create_rwq_ind_table cmd;
	काष्ठा ib_uverbs_ex_create_rwq_ind_table_resp  resp = अणुपूर्ण;
	काष्ठा ib_uobject *uobj;
	पूर्णांक err;
	काष्ठा ib_rwq_ind_table_init_attr init_attr = अणुपूर्ण;
	काष्ठा ib_rwq_ind_table *rwq_ind_tbl;
	काष्ठा ib_wq **wqs = शून्य;
	u32 *wqs_handles = शून्य;
	काष्ठा ib_wq	*wq = शून्य;
	पूर्णांक i, num_पढ़ो_wqs;
	u32 num_wq_handles;
	काष्ठा uverbs_req_iter iter;
	काष्ठा ib_device *ib_dev;

	err = uverbs_request_start(attrs, &iter, &cmd, माप(cmd));
	अगर (err)
		वापस err;

	अगर (cmd.comp_mask)
		वापस -EOPNOTSUPP;

	अगर (cmd.log_ind_tbl_size > IB_USER_VERBS_MAX_LOG_IND_TBL_SIZE)
		वापस -EINVAL;

	num_wq_handles = 1 << cmd.log_ind_tbl_size;
	wqs_handles = kसुस्मृति(num_wq_handles, माप(*wqs_handles),
			      GFP_KERNEL);
	अगर (!wqs_handles)
		वापस -ENOMEM;

	err = uverbs_request_next(&iter, wqs_handles,
				  num_wq_handles * माप(__u32));
	अगर (err)
		जाओ err_मुक्त;

	err = uverbs_request_finish(&iter);
	अगर (err)
		जाओ err_मुक्त;

	wqs = kसुस्मृति(num_wq_handles, माप(*wqs), GFP_KERNEL);
	अगर (!wqs) अणु
		err = -ENOMEM;
		जाओ  err_मुक्त;
	पूर्ण

	क्रम (num_पढ़ो_wqs = 0; num_पढ़ो_wqs < num_wq_handles;
			num_पढ़ो_wqs++) अणु
		wq = uobj_get_obj_पढ़ो(wq, UVERBS_OBJECT_WQ,
				       wqs_handles[num_पढ़ो_wqs], attrs);
		अगर (!wq) अणु
			err = -EINVAL;
			जाओ put_wqs;
		पूर्ण

		wqs[num_पढ़ो_wqs] = wq;
		atomic_inc(&wqs[num_पढ़ो_wqs]->usecnt);
	पूर्ण

	uobj = uobj_alloc(UVERBS_OBJECT_RWQ_IND_TBL, attrs, &ib_dev);
	अगर (IS_ERR(uobj)) अणु
		err = PTR_ERR(uobj);
		जाओ put_wqs;
	पूर्ण

	rwq_ind_tbl = rdma_zalloc_drv_obj(ib_dev, ib_rwq_ind_table);
	अगर (!rwq_ind_tbl) अणु
		err = -ENOMEM;
		जाओ err_uobj;
	पूर्ण

	init_attr.log_ind_tbl_size = cmd.log_ind_tbl_size;
	init_attr.ind_tbl = wqs;

	rwq_ind_tbl->ind_tbl = wqs;
	rwq_ind_tbl->log_ind_tbl_size = init_attr.log_ind_tbl_size;
	rwq_ind_tbl->uobject = uobj;
	uobj->object = rwq_ind_tbl;
	rwq_ind_tbl->device = ib_dev;
	atomic_set(&rwq_ind_tbl->usecnt, 0);

	err = ib_dev->ops.create_rwq_ind_table(rwq_ind_tbl, &init_attr,
					       &attrs->driver_udata);
	अगर (err)
		जाओ err_create;

	क्रम (i = 0; i < num_wq_handles; i++)
		rdma_lookup_put_uobject(&wqs[i]->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
	kमुक्त(wqs_handles);
	uobj_finalize_uobj_create(uobj, attrs);

	resp.ind_tbl_handle = uobj->id;
	resp.ind_tbl_num = rwq_ind_tbl->ind_tbl_num;
	resp.response_length = uverbs_response_length(attrs, माप(resp));
	वापस uverbs_response(attrs, &resp, माप(resp));

err_create:
	kमुक्त(rwq_ind_tbl);
err_uobj:
	uobj_alloc_पात(uobj, attrs);
put_wqs:
	क्रम (i = 0; i < num_पढ़ो_wqs; i++) अणु
		rdma_lookup_put_uobject(&wqs[i]->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);
		atomic_dec(&wqs[i]->usecnt);
	पूर्ण
err_मुक्त:
	kमुक्त(wqs_handles);
	kमुक्त(wqs);
	वापस err;
पूर्ण

अटल पूर्णांक ib_uverbs_ex_destroy_rwq_ind_table(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_destroy_rwq_ind_table cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (cmd.comp_mask)
		वापस -EOPNOTSUPP;

	वापस uobj_perक्रमm_destroy(UVERBS_OBJECT_RWQ_IND_TBL,
				    cmd.ind_tbl_handle, attrs);
पूर्ण

अटल पूर्णांक ib_uverbs_ex_create_flow(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_flow	  cmd;
	काष्ठा ib_uverbs_create_flow_resp resp = अणुपूर्ण;
	काष्ठा ib_uobject		  *uobj;
	काष्ठा ib_flow			  *flow_id;
	काष्ठा ib_uverbs_flow_attr	  *kern_flow_attr;
	काष्ठा ib_flow_attr		  *flow_attr;
	काष्ठा ib_qp			  *qp;
	काष्ठा ib_uflow_resources	  *uflow_res;
	काष्ठा ib_uverbs_flow_spec_hdr	  *kern_spec;
	काष्ठा uverbs_req_iter iter;
	पूर्णांक err;
	व्योम *ib_spec;
	पूर्णांक i;
	काष्ठा ib_device *ib_dev;

	err = uverbs_request_start(attrs, &iter, &cmd, माप(cmd));
	अगर (err)
		वापस err;

	अगर (cmd.comp_mask)
		वापस -EINVAL;

	अगर (!capable(CAP_NET_RAW))
		वापस -EPERM;

	अगर (cmd.flow_attr.flags >= IB_FLOW_ATTR_FLAGS_RESERVED)
		वापस -EINVAL;

	अगर ((cmd.flow_attr.flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP) &&
	    ((cmd.flow_attr.type == IB_FLOW_ATTR_ALL_DEFAULT) ||
	     (cmd.flow_attr.type == IB_FLOW_ATTR_MC_DEFAULT)))
		वापस -EINVAL;

	अगर (cmd.flow_attr.num_of_specs > IB_FLOW_SPEC_SUPPORT_LAYERS)
		वापस -EINVAL;

	अगर (cmd.flow_attr.size >
	    (cmd.flow_attr.num_of_specs * माप(काष्ठा ib_uverbs_flow_spec)))
		वापस -EINVAL;

	अगर (cmd.flow_attr.reserved[0] ||
	    cmd.flow_attr.reserved[1])
		वापस -EINVAL;

	अगर (cmd.flow_attr.num_of_specs) अणु
		kern_flow_attr = kदो_स्मृति(माप(*kern_flow_attr) + cmd.flow_attr.size,
					 GFP_KERNEL);
		अगर (!kern_flow_attr)
			वापस -ENOMEM;

		*kern_flow_attr = cmd.flow_attr;
		err = uverbs_request_next(&iter, &kern_flow_attr->flow_specs,
					  cmd.flow_attr.size);
		अगर (err)
			जाओ err_मुक्त_attr;
	पूर्ण अन्यथा अणु
		kern_flow_attr = &cmd.flow_attr;
	पूर्ण

	err = uverbs_request_finish(&iter);
	अगर (err)
		जाओ err_मुक्त_attr;

	uobj = uobj_alloc(UVERBS_OBJECT_FLOW, attrs, &ib_dev);
	अगर (IS_ERR(uobj)) अणु
		err = PTR_ERR(uobj);
		जाओ err_मुक्त_attr;
	पूर्ण

	अगर (!rdma_is_port_valid(uobj->context->device, cmd.flow_attr.port)) अणु
		err = -EINVAL;
		जाओ err_uobj;
	पूर्ण

	qp = uobj_get_obj_पढ़ो(qp, UVERBS_OBJECT_QP, cmd.qp_handle, attrs);
	अगर (!qp) अणु
		err = -EINVAL;
		जाओ err_uobj;
	पूर्ण

	अगर (qp->qp_type != IB_QPT_UD && qp->qp_type != IB_QPT_RAW_PACKET) अणु
		err = -EINVAL;
		जाओ err_put;
	पूर्ण

	flow_attr = kzalloc(काष्ठा_size(flow_attr, flows,
				cmd.flow_attr.num_of_specs), GFP_KERNEL);
	अगर (!flow_attr) अणु
		err = -ENOMEM;
		जाओ err_put;
	पूर्ण
	uflow_res = flow_resources_alloc(cmd.flow_attr.num_of_specs);
	अगर (!uflow_res) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_flow_attr;
	पूर्ण

	flow_attr->type = kern_flow_attr->type;
	flow_attr->priority = kern_flow_attr->priority;
	flow_attr->num_of_specs = kern_flow_attr->num_of_specs;
	flow_attr->port = kern_flow_attr->port;
	flow_attr->flags = kern_flow_attr->flags;
	flow_attr->size = माप(*flow_attr);

	kern_spec = kern_flow_attr->flow_specs;
	ib_spec = flow_attr + 1;
	क्रम (i = 0; i < flow_attr->num_of_specs &&
			cmd.flow_attr.size >= माप(*kern_spec) &&
			cmd.flow_attr.size >= kern_spec->size;
	     i++) अणु
		err = kern_spec_to_ib_spec(
				attrs, (काष्ठा ib_uverbs_flow_spec *)kern_spec,
				ib_spec, uflow_res);
		अगर (err)
			जाओ err_मुक्त;

		flow_attr->size +=
			((जोड़ ib_flow_spec *) ib_spec)->size;
		cmd.flow_attr.size -= kern_spec->size;
		kern_spec = ((व्योम *)kern_spec) + kern_spec->size;
		ib_spec += ((जोड़ ib_flow_spec *) ib_spec)->size;
	पूर्ण
	अगर (cmd.flow_attr.size || (i != flow_attr->num_of_specs)) अणु
		pr_warn("create flow failed, flow %d: %d bytes left from uverb cmd\n",
			i, cmd.flow_attr.size);
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	flow_id = qp->device->ops.create_flow(qp, flow_attr,
					      &attrs->driver_udata);

	अगर (IS_ERR(flow_id)) अणु
		err = PTR_ERR(flow_id);
		जाओ err_मुक्त;
	पूर्ण

	ib_set_flow(uobj, flow_id, qp, qp->device, uflow_res);

	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	kमुक्त(flow_attr);

	अगर (cmd.flow_attr.num_of_specs)
		kमुक्त(kern_flow_attr);
	uobj_finalize_uobj_create(uobj, attrs);

	resp.flow_handle = uobj->id;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_मुक्त:
	ib_uverbs_flow_resources_मुक्त(uflow_res);
err_मुक्त_flow_attr:
	kमुक्त(flow_attr);
err_put:
	rdma_lookup_put_uobject(&qp->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
err_uobj:
	uobj_alloc_पात(uobj, attrs);
err_मुक्त_attr:
	अगर (cmd.flow_attr.num_of_specs)
		kमुक्त(kern_flow_attr);
	वापस err;
पूर्ण

अटल पूर्णांक ib_uverbs_ex_destroy_flow(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_destroy_flow	cmd;
	पूर्णांक				ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (cmd.comp_mask)
		वापस -EINVAL;

	वापस uobj_perक्रमm_destroy(UVERBS_OBJECT_FLOW, cmd.flow_handle, attrs);
पूर्ण

अटल पूर्णांक __uverbs_create_xsrq(काष्ठा uverbs_attr_bundle *attrs,
				काष्ठा ib_uverbs_create_xsrq *cmd,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_uverbs_create_srq_resp resp = अणुपूर्ण;
	काष्ठा ib_usrq_object           *obj;
	काष्ठा ib_pd                    *pd;
	काष्ठा ib_srq                   *srq;
	काष्ठा ib_srq_init_attr          attr;
	पूर्णांक ret;
	काष्ठा ib_uobject *xrcd_uobj;
	काष्ठा ib_device *ib_dev;

	obj = (काष्ठा ib_usrq_object *)uobj_alloc(UVERBS_OBJECT_SRQ, attrs,
						  &ib_dev);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	अगर (cmd->srq_type == IB_SRQT_TM)
		attr.ext.tag_matching.max_num_tags = cmd->max_num_tags;

	अगर (cmd->srq_type == IB_SRQT_XRC) अणु
		xrcd_uobj = uobj_get_पढ़ो(UVERBS_OBJECT_XRCD, cmd->xrcd_handle,
					  attrs);
		अगर (IS_ERR(xrcd_uobj)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		attr.ext.xrc.xrcd = (काष्ठा ib_xrcd *)xrcd_uobj->object;
		अगर (!attr.ext.xrc.xrcd) अणु
			ret = -EINVAL;
			जाओ err_put_xrcd;
		पूर्ण

		obj->uxrcd = container_of(xrcd_uobj, काष्ठा ib_uxrcd_object, uobject);
		atomic_inc(&obj->uxrcd->refcnt);
	पूर्ण

	अगर (ib_srq_has_cq(cmd->srq_type)) अणु
		attr.ext.cq = uobj_get_obj_पढ़ो(cq, UVERBS_OBJECT_CQ,
						cmd->cq_handle, attrs);
		अगर (!attr.ext.cq) अणु
			ret = -EINVAL;
			जाओ err_put_xrcd;
		पूर्ण
	पूर्ण

	pd = uobj_get_obj_पढ़ो(pd, UVERBS_OBJECT_PD, cmd->pd_handle, attrs);
	अगर (!pd) अणु
		ret = -EINVAL;
		जाओ err_put_cq;
	पूर्ण

	attr.event_handler  = ib_uverbs_srq_event_handler;
	attr.srq_type       = cmd->srq_type;
	attr.attr.max_wr    = cmd->max_wr;
	attr.attr.max_sge   = cmd->max_sge;
	attr.attr.srq_limit = cmd->srq_limit;

	INIT_LIST_HEAD(&obj->uevent.event_list);
	obj->uevent.uobject.user_handle = cmd->user_handle;

	srq = ib_create_srq_user(pd, &attr, obj, udata);
	अगर (IS_ERR(srq)) अणु
		ret = PTR_ERR(srq);
		जाओ err_put_pd;
	पूर्ण

	obj->uevent.uobject.object = srq;
	obj->uevent.uobject.user_handle = cmd->user_handle;
	obj->uevent.event_file = READ_ONCE(attrs->ufile->शेष_async_file);
	अगर (obj->uevent.event_file)
		uverbs_uobject_get(&obj->uevent.event_file->uobj);

	अगर (cmd->srq_type == IB_SRQT_XRC)
		resp.srqn = srq->ext.xrc.srq_num;

	अगर (cmd->srq_type == IB_SRQT_XRC)
		uobj_put_पढ़ो(xrcd_uobj);

	अगर (ib_srq_has_cq(cmd->srq_type))
		rdma_lookup_put_uobject(&attr.ext.cq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);

	uobj_put_obj_पढ़ो(pd);
	uobj_finalize_uobj_create(&obj->uevent.uobject, attrs);

	resp.srq_handle = obj->uevent.uobject.id;
	resp.max_wr = attr.attr.max_wr;
	resp.max_sge = attr.attr.max_sge;
	वापस uverbs_response(attrs, &resp, माप(resp));

err_put_pd:
	uobj_put_obj_पढ़ो(pd);
err_put_cq:
	अगर (ib_srq_has_cq(cmd->srq_type))
		rdma_lookup_put_uobject(&attr.ext.cq->uobject->uevent.uobject,
					UVERBS_LOOKUP_READ);

err_put_xrcd:
	अगर (cmd->srq_type == IB_SRQT_XRC) अणु
		atomic_dec(&obj->uxrcd->refcnt);
		uobj_put_पढ़ो(xrcd_uobj);
	पूर्ण

err:
	uobj_alloc_पात(&obj->uevent.uobject, attrs);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_create_srq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_srq      cmd;
	काष्ठा ib_uverbs_create_xsrq     xcmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	स_रखो(&xcmd, 0, माप(xcmd));
	xcmd.response	 = cmd.response;
	xcmd.user_handle = cmd.user_handle;
	xcmd.srq_type	 = IB_SRQT_BASIC;
	xcmd.pd_handle	 = cmd.pd_handle;
	xcmd.max_wr	 = cmd.max_wr;
	xcmd.max_sge	 = cmd.max_sge;
	xcmd.srq_limit	 = cmd.srq_limit;

	वापस __uverbs_create_xsrq(attrs, &xcmd, &attrs->driver_udata);
पूर्ण

अटल पूर्णांक ib_uverbs_create_xsrq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_create_xsrq     cmd;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	वापस __uverbs_create_xsrq(attrs, &cmd, &attrs->driver_udata);
पूर्ण

अटल पूर्णांक ib_uverbs_modअगरy_srq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_modअगरy_srq cmd;
	काष्ठा ib_srq              *srq;
	काष्ठा ib_srq_attr          attr;
	पूर्णांक                         ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	srq = uobj_get_obj_पढ़ो(srq, UVERBS_OBJECT_SRQ, cmd.srq_handle, attrs);
	अगर (!srq)
		वापस -EINVAL;

	attr.max_wr    = cmd.max_wr;
	attr.srq_limit = cmd.srq_limit;

	ret = srq->device->ops.modअगरy_srq(srq, &attr, cmd.attr_mask,
					  &attrs->driver_udata);

	rdma_lookup_put_uobject(&srq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);

	वापस ret;
पूर्ण

अटल पूर्णांक ib_uverbs_query_srq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_query_srq      cmd;
	काष्ठा ib_uverbs_query_srq_resp resp;
	काष्ठा ib_srq_attr              attr;
	काष्ठा ib_srq                   *srq;
	पूर्णांक                             ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	srq = uobj_get_obj_पढ़ो(srq, UVERBS_OBJECT_SRQ, cmd.srq_handle, attrs);
	अगर (!srq)
		वापस -EINVAL;

	ret = ib_query_srq(srq, &attr);

	rdma_lookup_put_uobject(&srq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);

	अगर (ret)
		वापस ret;

	स_रखो(&resp, 0, माप resp);

	resp.max_wr    = attr.max_wr;
	resp.max_sge   = attr.max_sge;
	resp.srq_limit = attr.srq_limit;

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक ib_uverbs_destroy_srq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_destroy_srq      cmd;
	काष्ठा ib_uverbs_destroy_srq_resp resp;
	काष्ठा ib_uobject		 *uobj;
	काष्ठा ib_uevent_object        	 *obj;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	uobj = uobj_get_destroy(UVERBS_OBJECT_SRQ, cmd.srq_handle, attrs);
	अगर (IS_ERR(uobj))
		वापस PTR_ERR(uobj);

	obj = container_of(uobj, काष्ठा ib_uevent_object, uobject);
	स_रखो(&resp, 0, माप(resp));
	resp.events_reported = obj->events_reported;

	uobj_put_destroy(uobj);

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक ib_uverbs_ex_query_device(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_query_device_resp resp = अणुपूर्ण;
	काष्ठा ib_uverbs_ex_query_device  cmd;
	काष्ठा ib_device_attr attr = अणु0पूर्ण;
	काष्ठा ib_ucontext *ucontext;
	काष्ठा ib_device *ib_dev;
	पूर्णांक err;

	ucontext = ib_uverbs_get_ucontext(attrs);
	अगर (IS_ERR(ucontext))
		वापस PTR_ERR(ucontext);
	ib_dev = ucontext->device;

	err = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (err)
		वापस err;

	अगर (cmd.comp_mask)
		वापस -EINVAL;

	अगर (cmd.reserved)
		वापस -EINVAL;

	err = ib_dev->ops.query_device(ib_dev, &attr, &attrs->driver_udata);
	अगर (err)
		वापस err;

	copy_query_dev_fields(ucontext, &resp.base, &attr);

	resp.odp_caps.general_caps = attr.odp_caps.general_caps;
	resp.odp_caps.per_transport_caps.rc_odp_caps =
		attr.odp_caps.per_transport_caps.rc_odp_caps;
	resp.odp_caps.per_transport_caps.uc_odp_caps =
		attr.odp_caps.per_transport_caps.uc_odp_caps;
	resp.odp_caps.per_transport_caps.ud_odp_caps =
		attr.odp_caps.per_transport_caps.ud_odp_caps;
	resp.xrc_odp_caps = attr.odp_caps.per_transport_caps.xrc_odp_caps;

	resp.बारtamp_mask = attr.बारtamp_mask;
	resp.hca_core_घड़ी = attr.hca_core_घड़ी;
	resp.device_cap_flags_ex = attr.device_cap_flags;
	resp.rss_caps.supported_qpts = attr.rss_caps.supported_qpts;
	resp.rss_caps.max_rwq_indirection_tables =
		attr.rss_caps.max_rwq_indirection_tables;
	resp.rss_caps.max_rwq_indirection_table_size =
		attr.rss_caps.max_rwq_indirection_table_size;
	resp.max_wq_type_rq = attr.max_wq_type_rq;
	resp.raw_packet_caps = attr.raw_packet_caps;
	resp.पंचांग_caps.max_rndv_hdr_size	= attr.पंचांग_caps.max_rndv_hdr_size;
	resp.पंचांग_caps.max_num_tags	= attr.पंचांग_caps.max_num_tags;
	resp.पंचांग_caps.max_ops		= attr.पंचांग_caps.max_ops;
	resp.पंचांग_caps.max_sge		= attr.पंचांग_caps.max_sge;
	resp.पंचांग_caps.flags		= attr.पंचांग_caps.flags;
	resp.cq_moderation_caps.max_cq_moderation_count  =
		attr.cq_caps.max_cq_moderation_count;
	resp.cq_moderation_caps.max_cq_moderation_period =
		attr.cq_caps.max_cq_moderation_period;
	resp.max_dm_size = attr.max_dm_size;
	resp.response_length = uverbs_response_length(attrs, माप(resp));

	वापस uverbs_response(attrs, &resp, माप(resp));
पूर्ण

अटल पूर्णांक ib_uverbs_ex_modअगरy_cq(काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uverbs_ex_modअगरy_cq cmd;
	काष्ठा ib_cq *cq;
	पूर्णांक ret;

	ret = uverbs_request(attrs, &cmd, माप(cmd));
	अगर (ret)
		वापस ret;

	अगर (!cmd.attr_mask || cmd.reserved)
		वापस -EINVAL;

	अगर (cmd.attr_mask > IB_CQ_MODERATE)
		वापस -EOPNOTSUPP;

	cq = uobj_get_obj_पढ़ो(cq, UVERBS_OBJECT_CQ, cmd.cq_handle, attrs);
	अगर (!cq)
		वापस -EINVAL;

	ret = rdma_set_cq_moderation(cq, cmd.attr.cq_count, cmd.attr.cq_period);

	rdma_lookup_put_uobject(&cq->uobject->uevent.uobject,
				UVERBS_LOOKUP_READ);
	वापस ret;
पूर्ण

/*
 * Describe the input काष्ठाs क्रम ग_लिखो(). Some ग_लिखो methods have an input
 * only काष्ठा, most have an input and output. If the काष्ठा has an output then
 * the 'response' u64 must be the first field in the request काष्ठाure.
 *
 * If udata is present then both the request and response काष्ठाs have a
 * trailing driver_data flex array. In this हाल the size of the base काष्ठा
 * cannot be changed.
 */
#घोषणा UAPI_DEF_WRITE_IO(req, resp)                                           \
	.ग_लिखो.has_resp = 1 +                                                  \
			  BUILD_BUG_ON_ZERO(दुरत्व(req, response) != 0) +    \
			  BUILD_BUG_ON_ZERO(माप_field(req, response) !=    \
					    माप(u64)),                      \
	.ग_लिखो.req_size = माप(req), .ग_लिखो.resp_size = माप(resp)

#घोषणा UAPI_DEF_WRITE_I(req) .ग_लिखो.req_size = माप(req)

#घोषणा UAPI_DEF_WRITE_UDATA_IO(req, resp)                                     \
	UAPI_DEF_WRITE_IO(req, resp),                                          \
		.ग_लिखो.has_udata =                                             \
			1 +                                                    \
			BUILD_BUG_ON_ZERO(दुरत्व(req, driver_data) !=        \
					  माप(req)) +                       \
			BUILD_BUG_ON_ZERO(दुरत्व(resp, driver_data) !=       \
					  माप(resp))

#घोषणा UAPI_DEF_WRITE_UDATA_I(req)                                            \
	UAPI_DEF_WRITE_I(req),                                                 \
		.ग_लिखो.has_udata =                                             \
			1 + BUILD_BUG_ON_ZERO(दुरत्व(req, driver_data) !=    \
					      माप(req))

/*
 * The _EX versions are क्रम use with WRITE_EX and allow the last काष्ठा member
 * to be specअगरied. Buffers that करो not include that member will be rejected.
 */
#घोषणा UAPI_DEF_WRITE_IO_EX(req, req_last_member, resp, resp_last_member)     \
	.ग_लिखो.has_resp = 1,                                                   \
	.ग_लिखो.req_size = दुरत्वend(req, req_last_member),                   \
	.ग_लिखो.resp_size = दुरत्वend(resp, resp_last_member)

#घोषणा UAPI_DEF_WRITE_I_EX(req, req_last_member)                              \
	.ग_लिखो.req_size = दुरत्वend(req, req_last_member)

स्थिर काष्ठा uapi_definition uverbs_def_ग_लिखो_पूर्णांकf[] = अणु
	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_AH,
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_CREATE_AH,
				     ib_uverbs_create_ah,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_create_ah,
					     काष्ठा ib_uverbs_create_ah_resp)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_DESTROY_AH,
			ib_uverbs_destroy_ah,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_destroy_ah)),
		UAPI_DEF_OBJ_NEEDS_FN(create_user_ah),
		UAPI_DEF_OBJ_NEEDS_FN(destroy_ah)),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_COMP_CHANNEL,
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL,
			ib_uverbs_create_comp_channel,
			UAPI_DEF_WRITE_IO(
				काष्ठा ib_uverbs_create_comp_channel,
				काष्ठा ib_uverbs_create_comp_channel_resp))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_CQ,
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_CREATE_CQ,
				     ib_uverbs_create_cq,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_create_cq,
					     काष्ठा ib_uverbs_create_cq_resp),
				     UAPI_DEF_METHOD_NEEDS_FN(create_cq)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_DESTROY_CQ,
			ib_uverbs_destroy_cq,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_destroy_cq,
					  काष्ठा ib_uverbs_destroy_cq_resp),
			UAPI_DEF_METHOD_NEEDS_FN(destroy_cq)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_POLL_CQ,
			ib_uverbs_poll_cq,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_poll_cq,
					  काष्ठा ib_uverbs_poll_cq_resp),
			UAPI_DEF_METHOD_NEEDS_FN(poll_cq)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_REQ_NOTIFY_CQ,
			ib_uverbs_req_notअगरy_cq,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_req_notअगरy_cq),
			UAPI_DEF_METHOD_NEEDS_FN(req_notअगरy_cq)),
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_RESIZE_CQ,
				     ib_uverbs_resize_cq,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_resize_cq,
					     काष्ठा ib_uverbs_resize_cq_resp),
				     UAPI_DEF_METHOD_NEEDS_FN(resize_cq)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_CREATE_CQ,
			ib_uverbs_ex_create_cq,
			UAPI_DEF_WRITE_IO_EX(काष्ठा ib_uverbs_ex_create_cq,
					     reserved,
					     काष्ठा ib_uverbs_ex_create_cq_resp,
					     response_length),
			UAPI_DEF_METHOD_NEEDS_FN(create_cq)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_MODIFY_CQ,
			ib_uverbs_ex_modअगरy_cq,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_ex_modअगरy_cq),
			UAPI_DEF_METHOD_NEEDS_FN(modअगरy_cq))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_DEVICE,
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_GET_CONTEXT,
				     ib_uverbs_get_context,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_get_context,
					     काष्ठा ib_uverbs_get_context_resp)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_QUERY_DEVICE,
			ib_uverbs_query_device,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_query_device,
					  काष्ठा ib_uverbs_query_device_resp)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_QUERY_PORT,
			ib_uverbs_query_port,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_query_port,
					  काष्ठा ib_uverbs_query_port_resp),
			UAPI_DEF_METHOD_NEEDS_FN(query_port)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_QUERY_DEVICE,
			ib_uverbs_ex_query_device,
			UAPI_DEF_WRITE_IO_EX(
				काष्ठा ib_uverbs_ex_query_device,
				reserved,
				काष्ठा ib_uverbs_ex_query_device_resp,
				response_length),
			UAPI_DEF_METHOD_NEEDS_FN(query_device)),
		UAPI_DEF_OBJ_NEEDS_FN(alloc_ucontext),
		UAPI_DEF_OBJ_NEEDS_FN(dealloc_ucontext)),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_FLOW,
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_CREATE_FLOW,
			ib_uverbs_ex_create_flow,
			UAPI_DEF_WRITE_IO_EX(काष्ठा ib_uverbs_create_flow,
					     flow_attr,
					     काष्ठा ib_uverbs_create_flow_resp,
					     flow_handle),
			UAPI_DEF_METHOD_NEEDS_FN(create_flow)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_DESTROY_FLOW,
			ib_uverbs_ex_destroy_flow,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_destroy_flow),
			UAPI_DEF_METHOD_NEEDS_FN(destroy_flow))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_MR,
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_DEREG_MR,
				     ib_uverbs_dereg_mr,
				     UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_dereg_mr),
				     UAPI_DEF_METHOD_NEEDS_FN(dereg_mr)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_REG_MR,
			ib_uverbs_reg_mr,
			UAPI_DEF_WRITE_UDATA_IO(काष्ठा ib_uverbs_reg_mr,
						काष्ठा ib_uverbs_reg_mr_resp),
			UAPI_DEF_METHOD_NEEDS_FN(reg_user_mr)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_REREG_MR,
			ib_uverbs_rereg_mr,
			UAPI_DEF_WRITE_UDATA_IO(काष्ठा ib_uverbs_rereg_mr,
						काष्ठा ib_uverbs_rereg_mr_resp),
			UAPI_DEF_METHOD_NEEDS_FN(rereg_user_mr))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_MW,
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_ALLOC_MW,
			ib_uverbs_alloc_mw,
			UAPI_DEF_WRITE_UDATA_IO(काष्ठा ib_uverbs_alloc_mw,
						काष्ठा ib_uverbs_alloc_mw_resp),
			UAPI_DEF_METHOD_NEEDS_FN(alloc_mw)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_DEALLOC_MW,
			ib_uverbs_dealloc_mw,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_dealloc_mw),
			UAPI_DEF_METHOD_NEEDS_FN(dealloc_mw))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_PD,
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_ALLOC_PD,
			ib_uverbs_alloc_pd,
			UAPI_DEF_WRITE_UDATA_IO(काष्ठा ib_uverbs_alloc_pd,
						काष्ठा ib_uverbs_alloc_pd_resp),
			UAPI_DEF_METHOD_NEEDS_FN(alloc_pd)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_DEALLOC_PD,
			ib_uverbs_dealloc_pd,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_dealloc_pd),
			UAPI_DEF_METHOD_NEEDS_FN(dealloc_pd))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_QP,
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_ATTACH_MCAST,
			ib_uverbs_attach_mcast,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_attach_mcast),
			UAPI_DEF_METHOD_NEEDS_FN(attach_mcast),
			UAPI_DEF_METHOD_NEEDS_FN(detach_mcast)),
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_CREATE_QP,
				     ib_uverbs_create_qp,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_create_qp,
					     काष्ठा ib_uverbs_create_qp_resp),
				     UAPI_DEF_METHOD_NEEDS_FN(create_qp)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_DESTROY_QP,
			ib_uverbs_destroy_qp,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_destroy_qp,
					  काष्ठा ib_uverbs_destroy_qp_resp),
			UAPI_DEF_METHOD_NEEDS_FN(destroy_qp)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_DETACH_MCAST,
			ib_uverbs_detach_mcast,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_detach_mcast),
			UAPI_DEF_METHOD_NEEDS_FN(detach_mcast)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_MODIFY_QP,
			ib_uverbs_modअगरy_qp,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_modअगरy_qp),
			UAPI_DEF_METHOD_NEEDS_FN(modअगरy_qp)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_POST_RECV,
			ib_uverbs_post_recv,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_post_recv,
					  काष्ठा ib_uverbs_post_recv_resp),
			UAPI_DEF_METHOD_NEEDS_FN(post_recv)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_POST_SEND,
			ib_uverbs_post_send,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_post_send,
					  काष्ठा ib_uverbs_post_send_resp),
			UAPI_DEF_METHOD_NEEDS_FN(post_send)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_QUERY_QP,
			ib_uverbs_query_qp,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_query_qp,
					  काष्ठा ib_uverbs_query_qp_resp),
			UAPI_DEF_METHOD_NEEDS_FN(query_qp)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_CREATE_QP,
			ib_uverbs_ex_create_qp,
			UAPI_DEF_WRITE_IO_EX(काष्ठा ib_uverbs_ex_create_qp,
					     comp_mask,
					     काष्ठा ib_uverbs_ex_create_qp_resp,
					     response_length),
			UAPI_DEF_METHOD_NEEDS_FN(create_qp)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_MODIFY_QP,
			ib_uverbs_ex_modअगरy_qp,
			UAPI_DEF_WRITE_IO_EX(काष्ठा ib_uverbs_ex_modअगरy_qp,
					     base,
					     काष्ठा ib_uverbs_ex_modअगरy_qp_resp,
					     response_length),
			UAPI_DEF_METHOD_NEEDS_FN(modअगरy_qp))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_RWQ_IND_TBL,
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_CREATE_RWQ_IND_TBL,
			ib_uverbs_ex_create_rwq_ind_table,
			UAPI_DEF_WRITE_IO_EX(
				काष्ठा ib_uverbs_ex_create_rwq_ind_table,
				log_ind_tbl_size,
				काष्ठा ib_uverbs_ex_create_rwq_ind_table_resp,
				ind_tbl_num),
			UAPI_DEF_METHOD_NEEDS_FN(create_rwq_ind_table)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_DESTROY_RWQ_IND_TBL,
			ib_uverbs_ex_destroy_rwq_ind_table,
			UAPI_DEF_WRITE_I(
				काष्ठा ib_uverbs_ex_destroy_rwq_ind_table),
			UAPI_DEF_METHOD_NEEDS_FN(destroy_rwq_ind_table))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_WQ,
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_CREATE_WQ,
			ib_uverbs_ex_create_wq,
			UAPI_DEF_WRITE_IO_EX(काष्ठा ib_uverbs_ex_create_wq,
					     max_sge,
					     काष्ठा ib_uverbs_ex_create_wq_resp,
					     wqn),
			UAPI_DEF_METHOD_NEEDS_FN(create_wq)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_DESTROY_WQ,
			ib_uverbs_ex_destroy_wq,
			UAPI_DEF_WRITE_IO_EX(काष्ठा ib_uverbs_ex_destroy_wq,
					     wq_handle,
					     काष्ठा ib_uverbs_ex_destroy_wq_resp,
					     reserved),
			UAPI_DEF_METHOD_NEEDS_FN(destroy_wq)),
		DECLARE_UVERBS_WRITE_EX(
			IB_USER_VERBS_EX_CMD_MODIFY_WQ,
			ib_uverbs_ex_modअगरy_wq,
			UAPI_DEF_WRITE_I_EX(काष्ठा ib_uverbs_ex_modअगरy_wq,
					    curr_wq_state),
			UAPI_DEF_METHOD_NEEDS_FN(modअगरy_wq))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_SRQ,
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_CREATE_SRQ,
				     ib_uverbs_create_srq,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_create_srq,
					     काष्ठा ib_uverbs_create_srq_resp),
				     UAPI_DEF_METHOD_NEEDS_FN(create_srq)),
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_CREATE_XSRQ,
				     ib_uverbs_create_xsrq,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_create_xsrq,
					     काष्ठा ib_uverbs_create_srq_resp),
				     UAPI_DEF_METHOD_NEEDS_FN(create_srq)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_DESTROY_SRQ,
			ib_uverbs_destroy_srq,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_destroy_srq,
					  काष्ठा ib_uverbs_destroy_srq_resp),
			UAPI_DEF_METHOD_NEEDS_FN(destroy_srq)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_MODIFY_SRQ,
			ib_uverbs_modअगरy_srq,
			UAPI_DEF_WRITE_UDATA_I(काष्ठा ib_uverbs_modअगरy_srq),
			UAPI_DEF_METHOD_NEEDS_FN(modअगरy_srq)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_POST_SRQ_RECV,
			ib_uverbs_post_srq_recv,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_post_srq_recv,
					  काष्ठा ib_uverbs_post_srq_recv_resp),
			UAPI_DEF_METHOD_NEEDS_FN(post_srq_recv)),
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_QUERY_SRQ,
			ib_uverbs_query_srq,
			UAPI_DEF_WRITE_IO(काष्ठा ib_uverbs_query_srq,
					  काष्ठा ib_uverbs_query_srq_resp),
			UAPI_DEF_METHOD_NEEDS_FN(query_srq))),

	DECLARE_UVERBS_OBJECT(
		UVERBS_OBJECT_XRCD,
		DECLARE_UVERBS_WRITE(
			IB_USER_VERBS_CMD_CLOSE_XRCD,
			ib_uverbs_बंद_xrcd,
			UAPI_DEF_WRITE_I(काष्ठा ib_uverbs_बंद_xrcd)),
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_OPEN_QP,
				     ib_uverbs_खोलो_qp,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_खोलो_qp,
					     काष्ठा ib_uverbs_create_qp_resp)),
		DECLARE_UVERBS_WRITE(IB_USER_VERBS_CMD_OPEN_XRCD,
				     ib_uverbs_खोलो_xrcd,
				     UAPI_DEF_WRITE_UDATA_IO(
					     काष्ठा ib_uverbs_खोलो_xrcd,
					     काष्ठा ib_uverbs_खोलो_xrcd_resp)),
		UAPI_DEF_OBJ_NEEDS_FN(alloc_xrcd),
		UAPI_DEF_OBJ_NEEDS_FN(dealloc_xrcd)),

	अणुपूर्ण,
पूर्ण;
