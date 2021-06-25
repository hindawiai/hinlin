<शैली गुरु>
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित UVERBS_H
#घोषणा UVERBS_H

#समावेश <linux/kref.h>
#समावेश <linux/idr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/cdev.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/uverbs_std_types.h>

#घोषणा UVERBS_MODULE_NAME ib_uverbs
#समावेश <rdma/uverbs_named_ioctl.h>

अटल अंतरभूत व्योम
ib_uverbs_init_udata(काष्ठा ib_udata *udata,
		     स्थिर व्योम __user *ibuf,
		     व्योम __user *obuf,
		     माप_प्रकार ilen, माप_प्रकार olen)
अणु
	udata->inbuf  = ibuf;
	udata->outbuf = obuf;
	udata->inlen  = ilen;
	udata->outlen = olen;
पूर्ण

अटल अंतरभूत व्योम
ib_uverbs_init_udata_buf_or_null(काष्ठा ib_udata *udata,
				 स्थिर व्योम __user *ibuf,
				 व्योम __user *obuf,
				 माप_प्रकार ilen, माप_प्रकार olen)
अणु
	ib_uverbs_init_udata(udata,
			     ilen ? ibuf : शून्य, olen ? obuf : शून्य,
			     ilen, olen);
पूर्ण

/*
 * Our lअगरeसमय rules क्रम these काष्ठाs are the following:
 *
 * काष्ठा ib_uverbs_device: One reference is held by the module and
 * released in ib_uverbs_हटाओ_one().  Another reference is taken by
 * ib_uverbs_खोलो() each समय the अक्षरacter special file is खोलोed,
 * and released in ib_uverbs_release_file() when the file is released.
 *
 * काष्ठा ib_uverbs_file: One reference is held by the VFS and
 * released when the file is बंदd.  Another reference is taken when
 * an asynchronous event queue file is created and released when the
 * event file is बंदd.
 *
 * काष्ठा ib_uverbs_event_queue: Base काष्ठाure क्रम
 * काष्ठा ib_uverbs_async_event_file and काष्ठा ib_uverbs_completion_event_file.
 * One reference is held by the VFS and released when the file is बंदd.
 * For asynchronous event files, another reference is held by the corresponding
 * मुख्य context file and released when that file is बंदd.  For completion
 * event files, a reference is taken when a CQ is created that uses the file,
 * and released when the CQ is destroyed.
 */

काष्ठा ib_uverbs_device अणु
	atomic_t				refcount;
	u32					num_comp_vectors;
	काष्ठा completion			comp;
	काष्ठा device				dev;
	/* First group क्रम device attributes, शून्य terminated array */
	स्थिर काष्ठा attribute_group		*groups[2];
	काष्ठा ib_device	__rcu	       *ib_dev;
	पूर्णांक					devnum;
	काष्ठा cdev			        cdev;
	काष्ठा rb_root				xrcd_tree;
	काष्ठा mutex				xrcd_tree_mutex;
	काष्ठा srcu_काष्ठा			disassociate_srcu;
	काष्ठा mutex				lists_mutex; /* protect lists */
	काष्ठा list_head			uverbs_file_list;
	काष्ठा uverbs_api			*uapi;
पूर्ण;

काष्ठा ib_uverbs_event_queue अणु
	spinlock_t				lock;
	पूर्णांक					is_बंदd;
	रुको_queue_head_t			poll_रुको;
	काष्ठा fasync_काष्ठा		       *async_queue;
	काष्ठा list_head			event_list;
पूर्ण;

काष्ठा ib_uverbs_async_event_file अणु
	काष्ठा ib_uobject			uobj;
	काष्ठा ib_uverbs_event_queue		ev_queue;
	काष्ठा ib_event_handler			event_handler;
पूर्ण;

काष्ठा ib_uverbs_completion_event_file अणु
	काष्ठा ib_uobject			uobj;
	काष्ठा ib_uverbs_event_queue		ev_queue;
पूर्ण;

काष्ठा ib_uverbs_file अणु
	काष्ठा kref				ref;
	काष्ठा ib_uverbs_device		       *device;
	काष्ठा mutex				ucontext_lock;
	/*
	 * ucontext must be accessed via ib_uverbs_get_ucontext() or with
	 * ucontext_lock held
	 */
	काष्ठा ib_ucontext		       *ucontext;
	काष्ठा ib_uverbs_async_event_file      *शेष_async_file;
	काष्ठा list_head			list;

	/*
	 * To access the uobjects list hw_destroy_rwsem must be held क्रम ग_लिखो
	 * OR hw_destroy_rwsem held क्रम पढ़ो AND uobjects_lock held.
	 * hw_destroy_rwsem should be called across any deकाष्ठाion of the HW
	 * object of an associated uobject.
	 */
	काष्ठा rw_semaphore	hw_destroy_rwsem;
	spinlock_t		uobjects_lock;
	काष्ठा list_head	uobjects;

	काष्ठा mutex umap_lock;
	काष्ठा list_head umaps;
	काष्ठा page *disassociate_page;

	काष्ठा xarray		idr;
पूर्ण;

काष्ठा ib_uverbs_event अणु
	जोड़ अणु
		काष्ठा ib_uverbs_async_event_desc	async;
		काष्ठा ib_uverbs_comp_event_desc	comp;
	पूर्ण					desc;
	काष्ठा list_head			list;
	काष्ठा list_head			obj_list;
	u32				       *counter;
पूर्ण;

काष्ठा ib_uverbs_mcast_entry अणु
	काष्ठा list_head	list;
	जोड़ ib_gid 		gid;
	u16 			lid;
पूर्ण;

काष्ठा ib_uevent_object अणु
	काष्ठा ib_uobject	uobject;
	काष्ठा ib_uverbs_async_event_file *event_file;
	/* List member क्रम ib_uverbs_async_event_file list */
	काष्ठा list_head	event_list;
	u32			events_reported;
पूर्ण;

काष्ठा ib_uxrcd_object अणु
	काष्ठा ib_uobject	uobject;
	atomic_t		refcnt;
पूर्ण;

काष्ठा ib_usrq_object अणु
	काष्ठा ib_uevent_object	uevent;
	काष्ठा ib_uxrcd_object *uxrcd;
पूर्ण;

काष्ठा ib_uqp_object अणु
	काष्ठा ib_uevent_object	uevent;
	/* lock क्रम mcast list */
	काष्ठा mutex		mcast_lock;
	काष्ठा list_head 	mcast_list;
	काष्ठा ib_uxrcd_object *uxrcd;
पूर्ण;

काष्ठा ib_uwq_object अणु
	काष्ठा ib_uevent_object	uevent;
पूर्ण;

काष्ठा ib_ucq_object अणु
	काष्ठा ib_uevent_object uevent;
	काष्ठा list_head	comp_list;
	u32			comp_events_reported;
पूर्ण;

बाह्य स्थिर काष्ठा file_operations uverbs_event_fops;
बाह्य स्थिर काष्ठा file_operations uverbs_async_event_fops;
व्योम ib_uverbs_init_event_queue(काष्ठा ib_uverbs_event_queue *ev_queue);
व्योम ib_uverbs_init_async_event_file(काष्ठा ib_uverbs_async_event_file *ev_file);
व्योम ib_uverbs_मुक्त_event_queue(काष्ठा ib_uverbs_event_queue *event_queue);
व्योम ib_uverbs_flow_resources_मुक्त(काष्ठा ib_uflow_resources *uflow_res);
पूर्णांक uverbs_async_event_release(काष्ठा inode *inode, काष्ठा file *filp);

पूर्णांक ib_alloc_ucontext(काष्ठा uverbs_attr_bundle *attrs);
पूर्णांक ib_init_ucontext(काष्ठा uverbs_attr_bundle *attrs);

व्योम ib_uverbs_release_ucq(काष्ठा ib_uverbs_completion_event_file *ev_file,
			   काष्ठा ib_ucq_object *uobj);
व्योम ib_uverbs_release_uevent(काष्ठा ib_uevent_object *uobj);
व्योम ib_uverbs_release_file(काष्ठा kref *ref);
व्योम ib_uverbs_async_handler(काष्ठा ib_uverbs_async_event_file *async_file,
			     __u64 element, __u64 event,
			     काष्ठा list_head *obj_list, u32 *counter);

व्योम ib_uverbs_comp_handler(काष्ठा ib_cq *cq, व्योम *cq_context);
व्योम ib_uverbs_cq_event_handler(काष्ठा ib_event *event, व्योम *context_ptr);
व्योम ib_uverbs_qp_event_handler(काष्ठा ib_event *event, व्योम *context_ptr);
व्योम ib_uverbs_wq_event_handler(काष्ठा ib_event *event, व्योम *context_ptr);
व्योम ib_uverbs_srq_event_handler(काष्ठा ib_event *event, व्योम *context_ptr);
पूर्णांक ib_uverbs_dealloc_xrcd(काष्ठा ib_uobject *uobject, काष्ठा ib_xrcd *xrcd,
			   क्रमागत rdma_हटाओ_reason why,
			   काष्ठा uverbs_attr_bundle *attrs);

पूर्णांक uverbs_dealloc_mw(काष्ठा ib_mw *mw);
व्योम ib_uverbs_detach_umcast(काष्ठा ib_qp *qp,
			     काष्ठा ib_uqp_object *uobj);

दीर्घ ib_uverbs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

काष्ठा ib_uverbs_flow_spec अणु
	जोड़ अणु
		जोड़ अणु
			काष्ठा ib_uverbs_flow_spec_hdr hdr;
			काष्ठा अणु
				__u32 type;
				__u16 size;
				__u16 reserved;
			पूर्ण;
		पूर्ण;
		काष्ठा ib_uverbs_flow_spec_eth     eth;
		काष्ठा ib_uverbs_flow_spec_ipv4    ipv4;
		काष्ठा ib_uverbs_flow_spec_esp     esp;
		काष्ठा ib_uverbs_flow_spec_tcp_udp tcp_udp;
		काष्ठा ib_uverbs_flow_spec_ipv6    ipv6;
		काष्ठा ib_uverbs_flow_spec_action_tag	flow_tag;
		काष्ठा ib_uverbs_flow_spec_action_drop	drop;
		काष्ठा ib_uverbs_flow_spec_action_handle action;
		काष्ठा ib_uverbs_flow_spec_action_count flow_count;
	पूर्ण;
पूर्ण;

पूर्णांक ib_uverbs_kern_spec_to_ib_spec_filter(क्रमागत ib_flow_spec_type type,
					  स्थिर व्योम *kern_spec_mask,
					  स्थिर व्योम *kern_spec_val,
					  माप_प्रकार kern_filter_sz,
					  जोड़ ib_flow_spec *ib_spec);

/*
 * ib_uverbs_query_port_resp.port_cap_flags started out as just a copy of the
 * PortInfo CapabilityMask, but was extended with unique bits.
 */
अटल अंतरभूत u32 make_port_cap_flags(स्थिर काष्ठा ib_port_attr *attr)
अणु
	u32 res;

	/* All IBA CapabilityMask bits are passed through here, except bit 26,
	 * which is overridden with IP_BASED_GIDS. This is due to a historical
	 * mistake in the implementation of IP_BASED_GIDS. Otherwise all other
	 * bits match the IBA definition across all kernel versions.
	 */
	res = attr->port_cap_flags & ~(u32)IB_UVERBS_PCF_IP_BASED_GIDS;

	अगर (attr->ip_gids)
		res |= IB_UVERBS_PCF_IP_BASED_GIDS;

	वापस res;
पूर्ण

अटल अंतरभूत काष्ठा ib_uverbs_async_event_file *
ib_uverbs_get_async_event(काष्ठा uverbs_attr_bundle *attrs,
			  u16 id)
अणु
	काष्ठा ib_uobject *async_ev_file_uobj;
	काष्ठा ib_uverbs_async_event_file *async_ev_file;

	async_ev_file_uobj = uverbs_attr_get_uobject(attrs, id);
	अगर (IS_ERR(async_ev_file_uobj))
		async_ev_file = READ_ONCE(attrs->ufile->शेष_async_file);
	अन्यथा
		async_ev_file = container_of(async_ev_file_uobj,
				       काष्ठा ib_uverbs_async_event_file,
				       uobj);
	अगर (async_ev_file)
		uverbs_uobject_get(&async_ev_file->uobj);
	वापस async_ev_file;
पूर्ण

व्योम copy_port_attr_to_resp(काष्ठा ib_port_attr *attr,
			    काष्ठा ib_uverbs_query_port_resp *resp,
			    काष्ठा ib_device *ib_dev, u8 port_num);
#पूर्ण_अगर /* UVERBS_H */
