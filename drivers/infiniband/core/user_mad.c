<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2008 Cisco. All rights reserved.
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

#घोषणा pr_fmt(fmt) "user_mad: " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kref.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/slab.h>
#समावेश <linux/nospec.h>

#समावेश <linux/uaccess.h>

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_user_mad.h>
#समावेश <rdma/rdma_netlink.h>

#समावेश "core_priv.h"

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("InfiniBand userspace MAD packet access");
MODULE_LICENSE("Dual BSD/GPL");

क्रमागत अणु
	IB_UMAD_MAX_PORTS  = RDMA_MAX_PORTS,
	IB_UMAD_MAX_AGENTS = 32,

	IB_UMAD_MAJOR      = 231,
	IB_UMAD_MINOR_BASE = 0,
	IB_UMAD_NUM_FIXED_MINOR = 64,
	IB_UMAD_NUM_DYNAMIC_MINOR = IB_UMAD_MAX_PORTS - IB_UMAD_NUM_FIXED_MINOR,
	IB_ISSM_MINOR_BASE        = IB_UMAD_NUM_FIXED_MINOR,
पूर्ण;

/*
 * Our lअगरeसमय rules क्रम these काष्ठाs are the following:
 * device special file is खोलोed, we take a reference on the
 * ib_umad_port's काष्ठा ib_umad_device. We drop these
 * references in the corresponding बंद().
 *
 * In addition to references coming from खोलो अक्षरacter devices, there
 * is one more reference to each ib_umad_device representing the
 * module's reference taken when allocating the ib_umad_device in
 * ib_umad_add_one().
 *
 * When destroying an ib_umad_device, we drop the module's reference.
 */

काष्ठा ib_umad_port अणु
	काष्ठा cdev           cdev;
	काष्ठा device	      dev;
	काष्ठा cdev           sm_cdev;
	काष्ठा device	      sm_dev;
	काष्ठा semaphore       sm_sem;

	काष्ठा mutex	       file_mutex;
	काष्ठा list_head       file_list;

	काष्ठा ib_device      *ib_dev;
	काष्ठा ib_umad_device *umad_dev;
	पूर्णांक                    dev_num;
	u32                     port_num;
पूर्ण;

काष्ठा ib_umad_device अणु
	काष्ठा kref kref;
	काष्ठा ib_umad_port ports[];
पूर्ण;

काष्ठा ib_umad_file अणु
	काष्ठा mutex		mutex;
	काष्ठा ib_umad_port    *port;
	काष्ठा list_head	recv_list;
	काष्ठा list_head	send_list;
	काष्ठा list_head	port_list;
	spinlock_t		send_lock;
	रुको_queue_head_t	recv_रुको;
	काष्ठा ib_mad_agent    *agent[IB_UMAD_MAX_AGENTS];
	पूर्णांक			agents_dead;
	u8			use_pkey_index;
	u8			alपढ़ोy_used;
पूर्ण;

काष्ठा ib_umad_packet अणु
	काष्ठा ib_mad_send_buf *msg;
	काष्ठा ib_mad_recv_wc  *recv_wc;
	काष्ठा list_head   list;
	पूर्णांक		   length;
	काष्ठा ib_user_mad mad;
पूर्ण;

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/ib_umad.h>

अटल स्थिर dev_t base_umad_dev = MKDEV(IB_UMAD_MAJOR, IB_UMAD_MINOR_BASE);
अटल स्थिर dev_t base_issm_dev = MKDEV(IB_UMAD_MAJOR, IB_UMAD_MINOR_BASE) +
				   IB_UMAD_NUM_FIXED_MINOR;
अटल dev_t dynamic_umad_dev;
अटल dev_t dynamic_issm_dev;

अटल DEFINE_IDA(umad_ida);

अटल पूर्णांक ib_umad_add_one(काष्ठा ib_device *device);
अटल व्योम ib_umad_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);

अटल व्योम ib_umad_dev_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा ib_umad_device *dev =
		container_of(kref, काष्ठा ib_umad_device, kref);

	kमुक्त(dev);
पूर्ण

अटल व्योम ib_umad_dev_get(काष्ठा ib_umad_device *dev)
अणु
	kref_get(&dev->kref);
पूर्ण

अटल व्योम ib_umad_dev_put(काष्ठा ib_umad_device *dev)
अणु
	kref_put(&dev->kref, ib_umad_dev_मुक्त);
पूर्ण

अटल पूर्णांक hdr_size(काष्ठा ib_umad_file *file)
अणु
	वापस file->use_pkey_index ? माप(काष्ठा ib_user_mad_hdr) :
				      माप(काष्ठा ib_user_mad_hdr_old);
पूर्ण

/* caller must hold file->mutex */
अटल काष्ठा ib_mad_agent *__get_agent(काष्ठा ib_umad_file *file, पूर्णांक id)
अणु
	वापस file->agents_dead ? शून्य : file->agent[id];
पूर्ण

अटल पूर्णांक queue_packet(काष्ठा ib_umad_file *file,
			काष्ठा ib_mad_agent *agent,
			काष्ठा ib_umad_packet *packet)
अणु
	पूर्णांक ret = 1;

	mutex_lock(&file->mutex);

	क्रम (packet->mad.hdr.id = 0;
	     packet->mad.hdr.id < IB_UMAD_MAX_AGENTS;
	     packet->mad.hdr.id++)
		अगर (agent == __get_agent(file, packet->mad.hdr.id)) अणु
			list_add_tail(&packet->list, &file->recv_list);
			wake_up_पूर्णांकerruptible(&file->recv_रुको);
			ret = 0;
			अवरोध;
		पूर्ण

	mutex_unlock(&file->mutex);

	वापस ret;
पूर्ण

अटल व्योम dequeue_send(काष्ठा ib_umad_file *file,
			 काष्ठा ib_umad_packet *packet)
अणु
	spin_lock_irq(&file->send_lock);
	list_del(&packet->list);
	spin_unlock_irq(&file->send_lock);
पूर्ण

अटल व्योम send_handler(काष्ठा ib_mad_agent *agent,
			 काष्ठा ib_mad_send_wc *send_wc)
अणु
	काष्ठा ib_umad_file *file = agent->context;
	काष्ठा ib_umad_packet *packet = send_wc->send_buf->context[0];

	dequeue_send(file, packet);
	rdma_destroy_ah(packet->msg->ah, RDMA_DESTROY_AH_SLEEPABLE);
	ib_मुक्त_send_mad(packet->msg);

	अगर (send_wc->status == IB_WC_RESP_TIMEOUT_ERR) अणु
		packet->length = IB_MGMT_MAD_HDR;
		packet->mad.hdr.status = ETIMEDOUT;
		अगर (!queue_packet(file, agent, packet))
			वापस;
	पूर्ण
	kमुक्त(packet);
पूर्ण

अटल व्योम recv_handler(काष्ठा ib_mad_agent *agent,
			 काष्ठा ib_mad_send_buf *send_buf,
			 काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_umad_file *file = agent->context;
	काष्ठा ib_umad_packet *packet;

	अगर (mad_recv_wc->wc->status != IB_WC_SUCCESS)
		जाओ err1;

	packet = kzalloc(माप *packet, GFP_KERNEL);
	अगर (!packet)
		जाओ err1;

	packet->length = mad_recv_wc->mad_len;
	packet->recv_wc = mad_recv_wc;

	packet->mad.hdr.status	   = 0;
	packet->mad.hdr.length	   = hdr_size(file) + mad_recv_wc->mad_len;
	packet->mad.hdr.qpn	   = cpu_to_be32(mad_recv_wc->wc->src_qp);
	/*
	 * On OPA devices it is okay to lose the upper 16 bits of LID as this
	 * inक्रमmation is obtained अन्यथाwhere. Mask off the upper 16 bits.
	 */
	अगर (rdma_cap_opa_mad(agent->device, agent->port_num))
		packet->mad.hdr.lid = ib_lid_be16(0xFFFF &
						  mad_recv_wc->wc->slid);
	अन्यथा
		packet->mad.hdr.lid = ib_lid_be16(mad_recv_wc->wc->slid);
	packet->mad.hdr.sl	   = mad_recv_wc->wc->sl;
	packet->mad.hdr.path_bits  = mad_recv_wc->wc->dlid_path_bits;
	packet->mad.hdr.pkey_index = mad_recv_wc->wc->pkey_index;
	packet->mad.hdr.grh_present = !!(mad_recv_wc->wc->wc_flags & IB_WC_GRH);
	अगर (packet->mad.hdr.grh_present) अणु
		काष्ठा rdma_ah_attr ah_attr;
		स्थिर काष्ठा ib_global_route *grh;
		पूर्णांक ret;

		ret = ib_init_ah_attr_from_wc(agent->device, agent->port_num,
					      mad_recv_wc->wc,
					      mad_recv_wc->recv_buf.grh,
					      &ah_attr);
		अगर (ret)
			जाओ err2;

		grh = rdma_ah_पढ़ो_grh(&ah_attr);
		packet->mad.hdr.gid_index = grh->sgid_index;
		packet->mad.hdr.hop_limit = grh->hop_limit;
		packet->mad.hdr.traffic_class = grh->traffic_class;
		स_नकल(packet->mad.hdr.gid, &grh->dgid, 16);
		packet->mad.hdr.flow_label = cpu_to_be32(grh->flow_label);
		rdma_destroy_ah_attr(&ah_attr);
	पूर्ण

	अगर (queue_packet(file, agent, packet))
		जाओ err2;
	वापस;

err2:
	kमुक्त(packet);
err1:
	ib_मुक्त_recv_mad(mad_recv_wc);
पूर्ण

अटल sमाप_प्रकार copy_recv_mad(काष्ठा ib_umad_file *file, अक्षर __user *buf,
			     काष्ठा ib_umad_packet *packet, माप_प्रकार count)
अणु
	काष्ठा ib_mad_recv_buf *recv_buf;
	पूर्णांक left, seg_payload, offset, max_seg_payload;
	माप_प्रकार seg_size;

	recv_buf = &packet->recv_wc->recv_buf;
	seg_size = packet->recv_wc->mad_seg_size;

	/* We need enough room to copy the first (or only) MAD segment. */
	अगर ((packet->length <= seg_size &&
	     count < hdr_size(file) + packet->length) ||
	    (packet->length > seg_size &&
	     count < hdr_size(file) + seg_size))
		वापस -EINVAL;

	अगर (copy_to_user(buf, &packet->mad, hdr_size(file)))
		वापस -EFAULT;

	buf += hdr_size(file);
	seg_payload = min_t(पूर्णांक, packet->length, seg_size);
	अगर (copy_to_user(buf, recv_buf->mad, seg_payload))
		वापस -EFAULT;

	अगर (seg_payload < packet->length) अणु
		/*
		 * Multipacket RMPP MAD message. Copy reमुख्यder of message.
		 * Note that last segment may have a लघुer payload.
		 */
		अगर (count < hdr_size(file) + packet->length) अणु
			/*
			 * The buffer is too small, वापस the first RMPP segment,
			 * which includes the RMPP message length.
			 */
			वापस -ENOSPC;
		पूर्ण
		offset = ib_get_mad_data_offset(recv_buf->mad->mad_hdr.mgmt_class);
		max_seg_payload = seg_size - offset;

		क्रम (left = packet->length - seg_payload, buf += seg_payload;
		     left; left -= seg_payload, buf += seg_payload) अणु
			recv_buf = container_of(recv_buf->list.next,
						काष्ठा ib_mad_recv_buf, list);
			seg_payload = min(left, max_seg_payload);
			अगर (copy_to_user(buf, ((व्योम *) recv_buf->mad) + offset,
					 seg_payload))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	trace_ib_umad_पढ़ो_recv(file, &packet->mad.hdr, &recv_buf->mad->mad_hdr);

	वापस hdr_size(file) + packet->length;
पूर्ण

अटल sमाप_प्रकार copy_send_mad(काष्ठा ib_umad_file *file, अक्षर __user *buf,
			     काष्ठा ib_umad_packet *packet, माप_प्रकार count)
अणु
	sमाप_प्रकार size = hdr_size(file) + packet->length;

	अगर (count < size)
		वापस -EINVAL;

	अगर (copy_to_user(buf, &packet->mad, hdr_size(file)))
		वापस -EFAULT;

	buf += hdr_size(file);

	अगर (copy_to_user(buf, packet->mad.data, packet->length))
		वापस -EFAULT;

	trace_ib_umad_पढ़ो_send(file, &packet->mad.hdr,
				(काष्ठा ib_mad_hdr *)&packet->mad.data);

	वापस size;
पूर्ण

अटल sमाप_प्रकार ib_umad_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ib_umad_file *file = filp->निजी_data;
	काष्ठा ib_umad_packet *packet;
	sमाप_प्रकार ret;

	अगर (count < hdr_size(file))
		वापस -EINVAL;

	mutex_lock(&file->mutex);

	अगर (file->agents_dead) अणु
		mutex_unlock(&file->mutex);
		वापस -EIO;
	पूर्ण

	जबतक (list_empty(&file->recv_list)) अणु
		mutex_unlock(&file->mutex);

		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible(file->recv_रुको,
					     !list_empty(&file->recv_list)))
			वापस -ERESTARTSYS;

		mutex_lock(&file->mutex);
	पूर्ण

	अगर (file->agents_dead) अणु
		mutex_unlock(&file->mutex);
		वापस -EIO;
	पूर्ण

	packet = list_entry(file->recv_list.next, काष्ठा ib_umad_packet, list);
	list_del(&packet->list);

	mutex_unlock(&file->mutex);

	अगर (packet->recv_wc)
		ret = copy_recv_mad(file, buf, packet, count);
	अन्यथा
		ret = copy_send_mad(file, buf, packet, count);

	अगर (ret < 0) अणु
		/* Requeue packet */
		mutex_lock(&file->mutex);
		list_add(&packet->list, &file->recv_list);
		mutex_unlock(&file->mutex);
	पूर्ण अन्यथा अणु
		अगर (packet->recv_wc)
			ib_मुक्त_recv_mad(packet->recv_wc);
		kमुक्त(packet);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक copy_rmpp_mad(काष्ठा ib_mad_send_buf *msg, स्थिर अक्षर __user *buf)
अणु
	पूर्णांक left, seg;

	/* Copy class specअगरic header */
	अगर ((msg->hdr_len > IB_MGMT_RMPP_HDR) &&
	    copy_from_user(msg->mad + IB_MGMT_RMPP_HDR, buf + IB_MGMT_RMPP_HDR,
			   msg->hdr_len - IB_MGMT_RMPP_HDR))
		वापस -EFAULT;

	/* All headers are in place.  Copy data segments. */
	क्रम (seg = 1, left = msg->data_len, buf += msg->hdr_len; left > 0;
	     seg++, left -= msg->seg_size, buf += msg->seg_size) अणु
		अगर (copy_from_user(ib_get_rmpp_segment(msg, seg), buf,
				   min(left, msg->seg_size)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक same_destination(काष्ठा ib_user_mad_hdr *hdr1,
			    काष्ठा ib_user_mad_hdr *hdr2)
अणु
	अगर (!hdr1->grh_present && !hdr2->grh_present)
	   वापस (hdr1->lid == hdr2->lid);

	अगर (hdr1->grh_present && hdr2->grh_present)
	   वापस !स_भेद(hdr1->gid, hdr2->gid, 16);

	वापस 0;
पूर्ण

अटल पूर्णांक is_duplicate(काष्ठा ib_umad_file *file,
			काष्ठा ib_umad_packet *packet)
अणु
	काष्ठा ib_umad_packet *sent_packet;
	काष्ठा ib_mad_hdr *sent_hdr, *hdr;

	hdr = (काष्ठा ib_mad_hdr *) packet->mad.data;
	list_क्रम_each_entry(sent_packet, &file->send_list, list) अणु
		sent_hdr = (काष्ठा ib_mad_hdr *) sent_packet->mad.data;

		अगर ((hdr->tid != sent_hdr->tid) ||
		    (hdr->mgmt_class != sent_hdr->mgmt_class))
			जारी;

		/*
		 * No need to be overly clever here.  If two new operations have
		 * the same TID, reject the second as a duplicate.  This is more
		 * restrictive than required by the spec.
		 */
		अगर (!ib_response_mad(hdr)) अणु
			अगर (!ib_response_mad(sent_hdr))
				वापस 1;
			जारी;
		पूर्ण अन्यथा अगर (!ib_response_mad(sent_hdr))
			जारी;

		अगर (same_destination(&packet->mad.hdr, &sent_packet->mad.hdr))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ib_umad_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ib_umad_file *file = filp->निजी_data;
	काष्ठा ib_umad_packet *packet;
	काष्ठा ib_mad_agent *agent;
	काष्ठा rdma_ah_attr ah_attr;
	काष्ठा ib_ah *ah;
	काष्ठा ib_rmpp_mad *rmpp_mad;
	__be64 *tid;
	पूर्णांक ret, data_len, hdr_len, copy_offset, rmpp_active;
	u8 base_version;

	अगर (count < hdr_size(file) + IB_MGMT_RMPP_HDR)
		वापस -EINVAL;

	packet = kzalloc(माप *packet + IB_MGMT_RMPP_HDR, GFP_KERNEL);
	अगर (!packet)
		वापस -ENOMEM;

	अगर (copy_from_user(&packet->mad, buf, hdr_size(file))) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	अगर (packet->mad.hdr.id >= IB_UMAD_MAX_AGENTS) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	buf += hdr_size(file);

	अगर (copy_from_user(packet->mad.data, buf, IB_MGMT_RMPP_HDR)) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	mutex_lock(&file->mutex);

	trace_ib_umad_ग_लिखो(file, &packet->mad.hdr,
			    (काष्ठा ib_mad_hdr *)&packet->mad.data);

	agent = __get_agent(file, packet->mad.hdr.id);
	अगर (!agent) अणु
		ret = -EIO;
		जाओ err_up;
	पूर्ण

	स_रखो(&ah_attr, 0, माप ah_attr);
	ah_attr.type = rdma_ah_find_type(agent->device,
					 file->port->port_num);
	rdma_ah_set_dlid(&ah_attr, be16_to_cpu(packet->mad.hdr.lid));
	rdma_ah_set_sl(&ah_attr, packet->mad.hdr.sl);
	rdma_ah_set_path_bits(&ah_attr, packet->mad.hdr.path_bits);
	rdma_ah_set_port_num(&ah_attr, file->port->port_num);
	अगर (packet->mad.hdr.grh_present) अणु
		rdma_ah_set_grh(&ah_attr, शून्य,
				be32_to_cpu(packet->mad.hdr.flow_label),
				packet->mad.hdr.gid_index,
				packet->mad.hdr.hop_limit,
				packet->mad.hdr.traffic_class);
		rdma_ah_set_dgid_raw(&ah_attr, packet->mad.hdr.gid);
	पूर्ण

	ah = rdma_create_user_ah(agent->qp->pd, &ah_attr, शून्य);
	अगर (IS_ERR(ah)) अणु
		ret = PTR_ERR(ah);
		जाओ err_up;
	पूर्ण

	rmpp_mad = (काष्ठा ib_rmpp_mad *) packet->mad.data;
	hdr_len = ib_get_mad_data_offset(rmpp_mad->mad_hdr.mgmt_class);

	अगर (ib_is_mad_class_rmpp(rmpp_mad->mad_hdr.mgmt_class)
	    && ib_mad_kernel_rmpp_agent(agent)) अणु
		copy_offset = IB_MGMT_RMPP_HDR;
		rmpp_active = ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) &
						IB_MGMT_RMPP_FLAG_ACTIVE;
	पूर्ण अन्यथा अणु
		copy_offset = IB_MGMT_MAD_HDR;
		rmpp_active = 0;
	पूर्ण

	base_version = ((काष्ठा ib_mad_hdr *)&packet->mad.data)->base_version;
	data_len = count - hdr_size(file) - hdr_len;
	packet->msg = ib_create_send_mad(agent,
					 be32_to_cpu(packet->mad.hdr.qpn),
					 packet->mad.hdr.pkey_index, rmpp_active,
					 hdr_len, data_len, GFP_KERNEL,
					 base_version);
	अगर (IS_ERR(packet->msg)) अणु
		ret = PTR_ERR(packet->msg);
		जाओ err_ah;
	पूर्ण

	packet->msg->ah		= ah;
	packet->msg->समयout_ms = packet->mad.hdr.समयout_ms;
	packet->msg->retries	= packet->mad.hdr.retries;
	packet->msg->context[0] = packet;

	/* Copy MAD header.  Any RMPP header is alपढ़ोy in place. */
	स_नकल(packet->msg->mad, packet->mad.data, IB_MGMT_MAD_HDR);

	अगर (!rmpp_active) अणु
		अगर (copy_from_user(packet->msg->mad + copy_offset,
				   buf + copy_offset,
				   hdr_len + data_len - copy_offset)) अणु
			ret = -EFAULT;
			जाओ err_msg;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = copy_rmpp_mad(packet->msg, buf);
		अगर (ret)
			जाओ err_msg;
	पूर्ण

	/*
	 * Set the high-order part of the transaction ID to make MADs from
	 * dअगरferent agents unique, and allow routing responses back to the
	 * original requestor.
	 */
	अगर (!ib_response_mad(packet->msg->mad)) अणु
		tid = &((काष्ठा ib_mad_hdr *) packet->msg->mad)->tid;
		*tid = cpu_to_be64(((u64) agent->hi_tid) << 32 |
				   (be64_to_cpup(tid) & 0xffffffff));
		rmpp_mad->mad_hdr.tid = *tid;
	पूर्ण

	अगर (!ib_mad_kernel_rmpp_agent(agent)
	   && ib_is_mad_class_rmpp(rmpp_mad->mad_hdr.mgmt_class)
	   && (ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) & IB_MGMT_RMPP_FLAG_ACTIVE)) अणु
		spin_lock_irq(&file->send_lock);
		list_add_tail(&packet->list, &file->send_list);
		spin_unlock_irq(&file->send_lock);
	पूर्ण अन्यथा अणु
		spin_lock_irq(&file->send_lock);
		ret = is_duplicate(file, packet);
		अगर (!ret)
			list_add_tail(&packet->list, &file->send_list);
		spin_unlock_irq(&file->send_lock);
		अगर (ret) अणु
			ret = -EINVAL;
			जाओ err_msg;
		पूर्ण
	पूर्ण

	ret = ib_post_send_mad(packet->msg, शून्य);
	अगर (ret)
		जाओ err_send;

	mutex_unlock(&file->mutex);
	वापस count;

err_send:
	dequeue_send(file, packet);
err_msg:
	ib_मुक्त_send_mad(packet->msg);
err_ah:
	rdma_destroy_ah(ah, RDMA_DESTROY_AH_SLEEPABLE);
err_up:
	mutex_unlock(&file->mutex);
err:
	kमुक्त(packet);
	वापस ret;
पूर्ण

अटल __poll_t ib_umad_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा ib_umad_file *file = filp->निजी_data;

	/* we will always be able to post a MAD send */
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;

	mutex_lock(&file->mutex);
	poll_रुको(filp, &file->recv_रुको, रुको);

	अगर (!list_empty(&file->recv_list))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (file->agents_dead)
		mask = EPOLLERR;
	mutex_unlock(&file->mutex);

	वापस mask;
पूर्ण

अटल पूर्णांक ib_umad_reg_agent(काष्ठा ib_umad_file *file, व्योम __user *arg,
			     पूर्णांक compat_method_mask)
अणु
	काष्ठा ib_user_mad_reg_req ureq;
	काष्ठा ib_mad_reg_req req;
	काष्ठा ib_mad_agent *agent = शून्य;
	पूर्णांक agent_id;
	पूर्णांक ret;

	mutex_lock(&file->port->file_mutex);
	mutex_lock(&file->mutex);

	अगर (!file->port->ib_dev) अणु
		dev_notice(&file->port->dev, "%s: invalid device\n", __func__);
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(&ureq, arg, माप ureq)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (ureq.qpn != 0 && ureq.qpn != 1) अणु
		dev_notice(&file->port->dev,
			   "%s: invalid QPN %d specified\n", __func__,
			   ureq.qpn);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (agent_id = 0; agent_id < IB_UMAD_MAX_AGENTS; ++agent_id)
		अगर (!__get_agent(file, agent_id))
			जाओ found;

	dev_notice(&file->port->dev, "%s: Max Agents (%u) reached\n", __func__,
		   IB_UMAD_MAX_AGENTS);

	ret = -ENOMEM;
	जाओ out;

found:
	अगर (ureq.mgmt_class) अणु
		स_रखो(&req, 0, माप(req));
		req.mgmt_class         = ureq.mgmt_class;
		req.mgmt_class_version = ureq.mgmt_class_version;
		स_नकल(req.oui, ureq.oui, माप req.oui);

		अगर (compat_method_mask) अणु
			u32 *umm = (u32 *) ureq.method_mask;
			पूर्णांक i;

			क्रम (i = 0; i < BITS_TO_LONGS(IB_MGMT_MAX_METHODS); ++i)
				req.method_mask[i] =
					umm[i * 2] | ((u64) umm[i * 2 + 1] << 32);
		पूर्ण अन्यथा
			स_नकल(req.method_mask, ureq.method_mask,
			       माप req.method_mask);
	पूर्ण

	agent = ib_रेजिस्टर_mad_agent(file->port->ib_dev, file->port->port_num,
				      ureq.qpn ? IB_QPT_GSI : IB_QPT_SMI,
				      ureq.mgmt_class ? &req : शून्य,
				      ureq.rmpp_version,
				      send_handler, recv_handler, file, 0);
	अगर (IS_ERR(agent)) अणु
		ret = PTR_ERR(agent);
		agent = शून्य;
		जाओ out;
	पूर्ण

	अगर (put_user(agent_id,
		     (u32 __user *) (arg + दुरत्व(काष्ठा ib_user_mad_reg_req, id)))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (!file->alपढ़ोy_used) अणु
		file->alपढ़ोy_used = 1;
		अगर (!file->use_pkey_index) अणु
			dev_warn(&file->port->dev,
				"process %s did not enable P_Key index support.\n",
				current->comm);
			dev_warn(&file->port->dev,
				"   Documentation/infiniband/user_mad.rst has info on the new ABI.\n");
		पूर्ण
	पूर्ण

	file->agent[agent_id] = agent;
	ret = 0;

out:
	mutex_unlock(&file->mutex);

	अगर (ret && agent)
		ib_unरेजिस्टर_mad_agent(agent);

	mutex_unlock(&file->port->file_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ib_umad_reg_agent2(काष्ठा ib_umad_file *file, व्योम __user *arg)
अणु
	काष्ठा ib_user_mad_reg_req2 ureq;
	काष्ठा ib_mad_reg_req req;
	काष्ठा ib_mad_agent *agent = शून्य;
	पूर्णांक agent_id;
	पूर्णांक ret;

	mutex_lock(&file->port->file_mutex);
	mutex_lock(&file->mutex);

	अगर (!file->port->ib_dev) अणु
		dev_notice(&file->port->dev, "%s: invalid device\n", __func__);
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(&ureq, arg, माप(ureq))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (ureq.qpn != 0 && ureq.qpn != 1) अणु
		dev_notice(&file->port->dev, "%s: invalid QPN %d specified\n",
			   __func__, ureq.qpn);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (ureq.flags & ~IB_USER_MAD_REG_FLAGS_CAP) अणु
		dev_notice(&file->port->dev,
			   "%s failed: invalid registration flags specified 0x%x; supported 0x%x\n",
			   __func__, ureq.flags, IB_USER_MAD_REG_FLAGS_CAP);
		ret = -EINVAL;

		अगर (put_user((u32)IB_USER_MAD_REG_FLAGS_CAP,
				(u32 __user *) (arg + दुरत्व(काष्ठा
				ib_user_mad_reg_req2, flags))))
			ret = -EFAULT;

		जाओ out;
	पूर्ण

	क्रम (agent_id = 0; agent_id < IB_UMAD_MAX_AGENTS; ++agent_id)
		अगर (!__get_agent(file, agent_id))
			जाओ found;

	dev_notice(&file->port->dev, "%s: Max Agents (%u) reached\n", __func__,
		   IB_UMAD_MAX_AGENTS);
	ret = -ENOMEM;
	जाओ out;

found:
	अगर (ureq.mgmt_class) अणु
		स_रखो(&req, 0, माप(req));
		req.mgmt_class         = ureq.mgmt_class;
		req.mgmt_class_version = ureq.mgmt_class_version;
		अगर (ureq.oui & 0xff000000) अणु
			dev_notice(&file->port->dev,
				   "%s failed: oui invalid 0x%08x\n", __func__,
				   ureq.oui);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		req.oui[2] =  ureq.oui & 0x0000ff;
		req.oui[1] = (ureq.oui & 0x00ff00) >> 8;
		req.oui[0] = (ureq.oui & 0xff0000) >> 16;
		स_नकल(req.method_mask, ureq.method_mask,
			माप(req.method_mask));
	पूर्ण

	agent = ib_रेजिस्टर_mad_agent(file->port->ib_dev, file->port->port_num,
				      ureq.qpn ? IB_QPT_GSI : IB_QPT_SMI,
				      ureq.mgmt_class ? &req : शून्य,
				      ureq.rmpp_version,
				      send_handler, recv_handler, file,
				      ureq.flags);
	अगर (IS_ERR(agent)) अणु
		ret = PTR_ERR(agent);
		agent = शून्य;
		जाओ out;
	पूर्ण

	अगर (put_user(agent_id,
		     (u32 __user *)(arg +
				दुरत्व(काष्ठा ib_user_mad_reg_req2, id)))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (!file->alपढ़ोy_used) अणु
		file->alपढ़ोy_used = 1;
		file->use_pkey_index = 1;
	पूर्ण

	file->agent[agent_id] = agent;
	ret = 0;

out:
	mutex_unlock(&file->mutex);

	अगर (ret && agent)
		ib_unरेजिस्टर_mad_agent(agent);

	mutex_unlock(&file->port->file_mutex);

	वापस ret;
पूर्ण


अटल पूर्णांक ib_umad_unreg_agent(काष्ठा ib_umad_file *file, u32 __user *arg)
अणु
	काष्ठा ib_mad_agent *agent = शून्य;
	u32 id;
	पूर्णांक ret = 0;

	अगर (get_user(id, arg))
		वापस -EFAULT;
	अगर (id >= IB_UMAD_MAX_AGENTS)
		वापस -EINVAL;

	mutex_lock(&file->port->file_mutex);
	mutex_lock(&file->mutex);

	id = array_index_nospec(id, IB_UMAD_MAX_AGENTS);
	अगर (!__get_agent(file, id)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	agent = file->agent[id];
	file->agent[id] = शून्य;

out:
	mutex_unlock(&file->mutex);

	अगर (agent)
		ib_unरेजिस्टर_mad_agent(agent);

	mutex_unlock(&file->port->file_mutex);

	वापस ret;
पूर्ण

अटल दीर्घ ib_umad_enable_pkey(काष्ठा ib_umad_file *file)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&file->mutex);
	अगर (file->alपढ़ोy_used)
		ret = -EINVAL;
	अन्यथा
		file->use_pkey_index = 1;
	mutex_unlock(&file->mutex);

	वापस ret;
पूर्ण

अटल दीर्घ ib_umad_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल IB_USER_MAD_REGISTER_AGENT:
		वापस ib_umad_reg_agent(filp->निजी_data, (व्योम __user *) arg, 0);
	हाल IB_USER_MAD_UNREGISTER_AGENT:
		वापस ib_umad_unreg_agent(filp->निजी_data, (__u32 __user *) arg);
	हाल IB_USER_MAD_ENABLE_PKEY:
		वापस ib_umad_enable_pkey(filp->निजी_data);
	हाल IB_USER_MAD_REGISTER_AGENT2:
		वापस ib_umad_reg_agent2(filp->निजी_data, (व्योम __user *) arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ ib_umad_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल IB_USER_MAD_REGISTER_AGENT:
		वापस ib_umad_reg_agent(filp->निजी_data, compat_ptr(arg), 1);
	हाल IB_USER_MAD_UNREGISTER_AGENT:
		वापस ib_umad_unreg_agent(filp->निजी_data, compat_ptr(arg));
	हाल IB_USER_MAD_ENABLE_PKEY:
		वापस ib_umad_enable_pkey(filp->निजी_data);
	हाल IB_USER_MAD_REGISTER_AGENT2:
		वापस ib_umad_reg_agent2(filp->निजी_data, compat_ptr(arg));
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * ib_umad_खोलो() करोes not need the BKL:
 *
 *  - the ib_umad_port काष्ठाures are properly reference counted, and
 *    everything अन्यथा is purely local to the file being created, so
 *    races against other खोलो calls are not a problem;
 *  - the ioctl method करोes not affect any global state outside of the
 *    file काष्ठाure being operated on;
 */
अटल पूर्णांक ib_umad_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_umad_port *port;
	काष्ठा ib_umad_file *file;
	पूर्णांक ret = 0;

	port = container_of(inode->i_cdev, काष्ठा ib_umad_port, cdev);

	mutex_lock(&port->file_mutex);

	अगर (!port->ib_dev) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (!rdma_dev_access_netns(port->ib_dev, current->nsproxy->net_ns)) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	file = kzalloc(माप(*file), GFP_KERNEL);
	अगर (!file) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_init(&file->mutex);
	spin_lock_init(&file->send_lock);
	INIT_LIST_HEAD(&file->recv_list);
	INIT_LIST_HEAD(&file->send_list);
	init_रुकोqueue_head(&file->recv_रुको);

	file->port = port;
	filp->निजी_data = file;

	list_add_tail(&file->port_list, &port->file_list);

	stream_खोलो(inode, filp);
out:
	mutex_unlock(&port->file_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ib_umad_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_umad_file *file = filp->निजी_data;
	काष्ठा ib_umad_packet *packet, *पंचांगp;
	पूर्णांक alपढ़ोy_dead;
	पूर्णांक i;

	mutex_lock(&file->port->file_mutex);
	mutex_lock(&file->mutex);

	alपढ़ोy_dead = file->agents_dead;
	file->agents_dead = 1;

	list_क्रम_each_entry_safe(packet, पंचांगp, &file->recv_list, list) अणु
		अगर (packet->recv_wc)
			ib_मुक्त_recv_mad(packet->recv_wc);
		kमुक्त(packet);
	पूर्ण

	list_del(&file->port_list);

	mutex_unlock(&file->mutex);

	अगर (!alपढ़ोy_dead)
		क्रम (i = 0; i < IB_UMAD_MAX_AGENTS; ++i)
			अगर (file->agent[i])
				ib_unरेजिस्टर_mad_agent(file->agent[i]);

	mutex_unlock(&file->port->file_mutex);
	mutex_destroy(&file->mutex);
	kमुक्त(file);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations umad_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= ib_umad_पढ़ो,
	.ग_लिखो		= ib_umad_ग_लिखो,
	.poll		= ib_umad_poll,
	.unlocked_ioctl = ib_umad_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ib_umad_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= ib_umad_खोलो,
	.release	= ib_umad_बंद,
	.llseek		= no_llseek,
पूर्ण;

अटल पूर्णांक ib_umad_sm_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_umad_port *port;
	काष्ठा ib_port_modअगरy props = अणु
		.set_port_cap_mask = IB_PORT_SM
	पूर्ण;
	पूर्णांक ret;

	port = container_of(inode->i_cdev, काष्ठा ib_umad_port, sm_cdev);

	अगर (filp->f_flags & O_NONBLOCK) अणु
		अगर (करोwn_trylock(&port->sm_sem)) अणु
			ret = -EAGAIN;
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (करोwn_पूर्णांकerruptible(&port->sm_sem)) अणु
			ret = -ERESTARTSYS;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (!rdma_dev_access_netns(port->ib_dev, current->nsproxy->net_ns)) अणु
		ret = -EPERM;
		जाओ err_up_sem;
	पूर्ण

	ret = ib_modअगरy_port(port->ib_dev, port->port_num, 0, &props);
	अगर (ret)
		जाओ err_up_sem;

	filp->निजी_data = port;

	nonseekable_खोलो(inode, filp);
	वापस 0;

err_up_sem:
	up(&port->sm_sem);

fail:
	वापस ret;
पूर्ण

अटल पूर्णांक ib_umad_sm_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_umad_port *port = filp->निजी_data;
	काष्ठा ib_port_modअगरy props = अणु
		.clr_port_cap_mask = IB_PORT_SM
	पूर्ण;
	पूर्णांक ret = 0;

	mutex_lock(&port->file_mutex);
	अगर (port->ib_dev)
		ret = ib_modअगरy_port(port->ib_dev, port->port_num, 0, &props);
	mutex_unlock(&port->file_mutex);

	up(&port->sm_sem);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations umad_sm_fops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = ib_umad_sm_खोलो,
	.release = ib_umad_sm_बंद,
	.llseek	 = no_llseek,
पूर्ण;

अटल काष्ठा ib_umad_port *get_port(काष्ठा ib_device *ibdev,
				     काष्ठा ib_umad_device *umad_dev,
				     u32 port)
अणु
	अगर (!umad_dev)
		वापस ERR_PTR(-EOPNOTSUPP);
	अगर (!rdma_is_port_valid(ibdev, port))
		वापस ERR_PTR(-EINVAL);
	अगर (!rdma_cap_ib_mad(ibdev, port))
		वापस ERR_PTR(-EOPNOTSUPP);

	वापस &umad_dev->ports[port - rdma_start_port(ibdev)];
पूर्ण

अटल पूर्णांक ib_umad_get_nl_info(काष्ठा ib_device *ibdev, व्योम *client_data,
			       काष्ठा ib_client_nl_info *res)
अणु
	काष्ठा ib_umad_port *port = get_port(ibdev, client_data, res->port);

	अगर (IS_ERR(port))
		वापस PTR_ERR(port);

	res->abi = IB_USER_MAD_ABI_VERSION;
	res->cdev = &port->dev;
	वापस 0;
पूर्ण

अटल काष्ठा ib_client umad_client = अणु
	.name   = "umad",
	.add    = ib_umad_add_one,
	.हटाओ = ib_umad_हटाओ_one,
	.get_nl_info = ib_umad_get_nl_info,
पूर्ण;
MODULE_ALIAS_RDMA_CLIENT("umad");

अटल पूर्णांक ib_issm_get_nl_info(काष्ठा ib_device *ibdev, व्योम *client_data,
			       काष्ठा ib_client_nl_info *res)
अणु
	काष्ठा ib_umad_port *port = get_port(ibdev, client_data, res->port);

	अगर (IS_ERR(port))
		वापस PTR_ERR(port);

	res->abi = IB_USER_MAD_ABI_VERSION;
	res->cdev = &port->sm_dev;
	वापस 0;
पूर्ण

अटल काष्ठा ib_client issm_client = अणु
	.name = "issm",
	.get_nl_info = ib_issm_get_nl_info,
पूर्ण;
MODULE_ALIAS_RDMA_CLIENT("issm");

अटल sमाप_प्रकार ibdev_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा ib_umad_port *port = dev_get_drvdata(dev);

	अगर (!port)
		वापस -ENODEV;

	वापस sysfs_emit(buf, "%s\n", dev_name(&port->ib_dev->dev));
पूर्ण
अटल DEVICE_ATTR_RO(ibdev);

अटल sमाप_प्रकार port_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा ib_umad_port *port = dev_get_drvdata(dev);

	अगर (!port)
		वापस -ENODEV;

	वापस sysfs_emit(buf, "%d\n", port->port_num);
पूर्ण
अटल DEVICE_ATTR_RO(port);

अटल काष्ठा attribute *umad_class_dev_attrs[] = अणु
	&dev_attr_ibdev.attr,
	&dev_attr_port.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(umad_class_dev);

अटल अक्षर *umad_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "infiniband/%s", dev_name(dev));
पूर्ण

अटल sमाप_प्रकार abi_version_show(काष्ठा class *class,
				काष्ठा class_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", IB_USER_MAD_ABI_VERSION);
पूर्ण
अटल CLASS_ATTR_RO(abi_version);

अटल काष्ठा attribute *umad_class_attrs[] = अणु
	&class_attr_abi_version.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(umad_class);

अटल काष्ठा class umad_class = अणु
	.name		= "infiniband_mad",
	.devnode	= umad_devnode,
	.class_groups	= umad_class_groups,
	.dev_groups	= umad_class_dev_groups,
पूर्ण;

अटल व्योम ib_umad_release_port(काष्ठा device *device)
अणु
	काष्ठा ib_umad_port *port = dev_get_drvdata(device);
	काष्ठा ib_umad_device *umad_dev = port->umad_dev;

	ib_umad_dev_put(umad_dev);
पूर्ण

अटल व्योम ib_umad_init_port_dev(काष्ठा device *dev,
				  काष्ठा ib_umad_port *port,
				  स्थिर काष्ठा ib_device *device)
अणु
	device_initialize(dev);
	ib_umad_dev_get(port->umad_dev);
	dev->class = &umad_class;
	dev->parent = device->dev.parent;
	dev_set_drvdata(dev, port);
	dev->release = ib_umad_release_port;
पूर्ण

अटल पूर्णांक ib_umad_init_port(काष्ठा ib_device *device, पूर्णांक port_num,
			     काष्ठा ib_umad_device *umad_dev,
			     काष्ठा ib_umad_port *port)
अणु
	पूर्णांक devnum;
	dev_t base_umad;
	dev_t base_issm;
	पूर्णांक ret;

	devnum = ida_alloc_max(&umad_ida, IB_UMAD_MAX_PORTS - 1, GFP_KERNEL);
	अगर (devnum < 0)
		वापस -1;
	port->dev_num = devnum;
	अगर (devnum >= IB_UMAD_NUM_FIXED_MINOR) अणु
		base_umad = dynamic_umad_dev + devnum - IB_UMAD_NUM_FIXED_MINOR;
		base_issm = dynamic_issm_dev + devnum - IB_UMAD_NUM_FIXED_MINOR;
	पूर्ण अन्यथा अणु
		base_umad = devnum + base_umad_dev;
		base_issm = devnum + base_issm_dev;
	पूर्ण

	port->ib_dev   = device;
	port->umad_dev = umad_dev;
	port->port_num = port_num;
	sema_init(&port->sm_sem, 1);
	mutex_init(&port->file_mutex);
	INIT_LIST_HEAD(&port->file_list);

	ib_umad_init_port_dev(&port->dev, port, device);
	port->dev.devt = base_umad;
	dev_set_name(&port->dev, "umad%d", port->dev_num);
	cdev_init(&port->cdev, &umad_fops);
	port->cdev.owner = THIS_MODULE;

	ret = cdev_device_add(&port->cdev, &port->dev);
	अगर (ret)
		जाओ err_cdev;

	ib_umad_init_port_dev(&port->sm_dev, port, device);
	port->sm_dev.devt = base_issm;
	dev_set_name(&port->sm_dev, "issm%d", port->dev_num);
	cdev_init(&port->sm_cdev, &umad_sm_fops);
	port->sm_cdev.owner = THIS_MODULE;

	ret = cdev_device_add(&port->sm_cdev, &port->sm_dev);
	अगर (ret)
		जाओ err_dev;

	वापस 0;

err_dev:
	put_device(&port->sm_dev);
	cdev_device_del(&port->cdev, &port->dev);
err_cdev:
	put_device(&port->dev);
	ida_मुक्त(&umad_ida, devnum);
	वापस ret;
पूर्ण

अटल व्योम ib_umad_समाप्त_port(काष्ठा ib_umad_port *port)
अणु
	काष्ठा ib_umad_file *file;
	पूर्णांक id;

	cdev_device_del(&port->sm_cdev, &port->sm_dev);
	cdev_device_del(&port->cdev, &port->dev);

	mutex_lock(&port->file_mutex);

	/* Mark ib_dev शून्य and block ioctl or other file ops to progress
	 * further.
	 */
	port->ib_dev = शून्य;

	list_क्रम_each_entry(file, &port->file_list, port_list) अणु
		mutex_lock(&file->mutex);
		file->agents_dead = 1;
		wake_up_पूर्णांकerruptible(&file->recv_रुको);
		mutex_unlock(&file->mutex);

		क्रम (id = 0; id < IB_UMAD_MAX_AGENTS; ++id)
			अगर (file->agent[id])
				ib_unरेजिस्टर_mad_agent(file->agent[id]);
	पूर्ण

	mutex_unlock(&port->file_mutex);

	ida_मुक्त(&umad_ida, port->dev_num);

	/* balances device_initialize() */
	put_device(&port->sm_dev);
	put_device(&port->dev);
पूर्ण

अटल पूर्णांक ib_umad_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा ib_umad_device *umad_dev;
	पूर्णांक s, e, i;
	पूर्णांक count = 0;
	पूर्णांक ret;

	s = rdma_start_port(device);
	e = rdma_end_port(device);

	umad_dev = kzalloc(काष्ठा_size(umad_dev, ports, e - s + 1), GFP_KERNEL);
	अगर (!umad_dev)
		वापस -ENOMEM;

	kref_init(&umad_dev->kref);
	क्रम (i = s; i <= e; ++i) अणु
		अगर (!rdma_cap_ib_mad(device, i))
			जारी;

		ret = ib_umad_init_port(device, i, umad_dev,
					&umad_dev->ports[i - s]);
		अगर (ret)
			जाओ err;

		count++;
	पूर्ण

	अगर (!count) अणु
		ret = -EOPNOTSUPP;
		जाओ मुक्त;
	पूर्ण

	ib_set_client_data(device, &umad_client, umad_dev);

	वापस 0;

err:
	जबतक (--i >= s) अणु
		अगर (!rdma_cap_ib_mad(device, i))
			जारी;

		ib_umad_समाप्त_port(&umad_dev->ports[i - s]);
	पूर्ण
मुक्त:
	/* balances kref_init */
	ib_umad_dev_put(umad_dev);
	वापस ret;
पूर्ण

अटल व्योम ib_umad_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा ib_umad_device *umad_dev = client_data;
	अचिन्हित पूर्णांक i;

	rdma_क्रम_each_port (device, i) अणु
		अगर (rdma_cap_ib_mad(device, i))
			ib_umad_समाप्त_port(
				&umad_dev->ports[i - rdma_start_port(device)]);
	पूर्ण
	/* balances kref_init() */
	ib_umad_dev_put(umad_dev);
पूर्ण

अटल पूर्णांक __init ib_umad_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_chrdev_region(base_umad_dev,
				     IB_UMAD_NUM_FIXED_MINOR * 2,
				     umad_class.name);
	अगर (ret) अणु
		pr_err("couldn't register device number\n");
		जाओ out;
	पूर्ण

	ret = alloc_chrdev_region(&dynamic_umad_dev, 0,
				  IB_UMAD_NUM_DYNAMIC_MINOR * 2,
				  umad_class.name);
	अगर (ret) अणु
		pr_err("couldn't register dynamic device number\n");
		जाओ out_alloc;
	पूर्ण
	dynamic_issm_dev = dynamic_umad_dev + IB_UMAD_NUM_DYNAMIC_MINOR;

	ret = class_रेजिस्टर(&umad_class);
	अगर (ret) अणु
		pr_err("couldn't create class infiniband_mad\n");
		जाओ out_chrdev;
	पूर्ण

	ret = ib_रेजिस्टर_client(&umad_client);
	अगर (ret)
		जाओ out_class;

	ret = ib_रेजिस्टर_client(&issm_client);
	अगर (ret)
		जाओ out_client;

	वापस 0;

out_client:
	ib_unरेजिस्टर_client(&umad_client);
out_class:
	class_unरेजिस्टर(&umad_class);

out_chrdev:
	unरेजिस्टर_chrdev_region(dynamic_umad_dev,
				 IB_UMAD_NUM_DYNAMIC_MINOR * 2);

out_alloc:
	unरेजिस्टर_chrdev_region(base_umad_dev,
				 IB_UMAD_NUM_FIXED_MINOR * 2);

out:
	वापस ret;
पूर्ण

अटल व्योम __निकास ib_umad_cleanup(व्योम)
अणु
	ib_unरेजिस्टर_client(&issm_client);
	ib_unरेजिस्टर_client(&umad_client);
	class_unरेजिस्टर(&umad_class);
	unरेजिस्टर_chrdev_region(base_umad_dev,
				 IB_UMAD_NUM_FIXED_MINOR * 2);
	unरेजिस्टर_chrdev_region(dynamic_umad_dev,
				 IB_UMAD_NUM_DYNAMIC_MINOR * 2);
पूर्ण

module_init(ib_umad_init);
module_निकास(ib_umad_cleanup);
