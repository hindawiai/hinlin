<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/uपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mshyperv.h>

#समावेश "hyperv_vmbus.h"

/*
 * hv_gpadl_size - Return the real size of a gpadl, the size that Hyper-V uses
 *
 * For BUFFER gpadl, Hyper-V uses the exact same size as the guest करोes.
 *
 * For RING gpadl, in each ring, the guest uses one PAGE_SIZE as the header
 * (because of the alignment requirement), however, the hypervisor only
 * uses the first HV_HYP_PAGE_SIZE as the header, thereक्रमe leaving a
 * (PAGE_SIZE - HV_HYP_PAGE_SIZE) gap. And since there are two rings in a
 * ringbuffer, the total size क्रम a RING gpadl that Hyper-V uses is the
 * total size that the guest uses minus twice of the gap size.
 */
अटल अंतरभूत u32 hv_gpadl_size(क्रमागत hv_gpadl_type type, u32 size)
अणु
	चयन (type) अणु
	हाल HV_GPADL_BUFFER:
		वापस size;
	हाल HV_GPADL_RING:
		/* The size of a ringbuffer must be page-aligned */
		BUG_ON(size % PAGE_SIZE);
		/*
		 * Two things to notice here:
		 * 1) We're processing two ring buffers as a unit
		 * 2) We're skipping any space larger than HV_HYP_PAGE_SIZE in
		 * the first guest-size page of each of the two ring buffers.
		 * So we effectively subtract out two guest-size pages, and add
		 * back two Hyper-V size pages.
		 */
		वापस size - 2 * (PAGE_SIZE - HV_HYP_PAGE_SIZE);
	पूर्ण
	BUG();
	वापस 0;
पूर्ण

/*
 * hv_ring_gpadl_send_hvpgoffset - Calculate the send offset (in unit of
 *                                 HV_HYP_PAGE) in a ring gpadl based on the
 *                                 offset in the guest
 *
 * @offset: the offset (in bytes) where the send ringbuffer starts in the
 *               भव address space of the guest
 */
अटल अंतरभूत u32 hv_ring_gpadl_send_hvpgoffset(u32 offset)
अणु

	/*
	 * For RING gpadl, in each ring, the guest uses one PAGE_SIZE as the
	 * header (because of the alignment requirement), however, the
	 * hypervisor only uses the first HV_HYP_PAGE_SIZE as the header,
	 * thereक्रमe leaving a (PAGE_SIZE - HV_HYP_PAGE_SIZE) gap.
	 *
	 * And to calculate the effective send offset in gpadl, we need to
	 * substract this gap.
	 */
	वापस (offset - (PAGE_SIZE - HV_HYP_PAGE_SIZE)) >> HV_HYP_PAGE_SHIFT;
पूर्ण

/*
 * hv_gpadl_hvpfn - Return the Hyper-V page PFN of the @i th Hyper-V page in
 *                  the gpadl
 *
 * @type: the type of the gpadl
 * @kbuffer: the poपूर्णांकer to the gpadl in the guest
 * @size: the total size (in bytes) of the gpadl
 * @send_offset: the offset (in bytes) where the send ringbuffer starts in the
 *               भव address space of the guest
 * @i: the index
 */
अटल अंतरभूत u64 hv_gpadl_hvpfn(क्रमागत hv_gpadl_type type, व्योम *kbuffer,
				 u32 size, u32 send_offset, पूर्णांक i)
अणु
	पूर्णांक send_idx = hv_ring_gpadl_send_hvpgoffset(send_offset);
	अचिन्हित दीर्घ delta = 0UL;

	चयन (type) अणु
	हाल HV_GPADL_BUFFER:
		अवरोध;
	हाल HV_GPADL_RING:
		अगर (i == 0)
			delta = 0;
		अन्यथा अगर (i <= send_idx)
			delta = PAGE_SIZE - HV_HYP_PAGE_SIZE;
		अन्यथा
			delta = 2 * (PAGE_SIZE - HV_HYP_PAGE_SIZE);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	वापस virt_to_hvpfn(kbuffer + delta + (HV_HYP_PAGE_SIZE * i));
पूर्ण

/*
 * vmbus_setevent- Trigger an event notअगरication on the specअगरied
 * channel.
 */
व्योम vmbus_setevent(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा hv_monitor_page *monitorpage;

	trace_vmbus_setevent(channel);

	/*
	 * For channels marked as in "low latency" mode
	 * bypass the monitor page mechanism.
	 */
	अगर (channel->offermsg.monitor_allocated && !channel->low_latency) अणु
		vmbus_send_पूर्णांकerrupt(channel->offermsg.child_relid);

		/* Get the child to parent monitor page */
		monitorpage = vmbus_connection.monitor_pages[1];

		sync_set_bit(channel->monitor_bit,
			(अचिन्हित दीर्घ *)&monitorpage->trigger_group
					[channel->monitor_grp].pending);

	पूर्ण अन्यथा अणु
		vmbus_set_event(channel);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_setevent);

/* vmbus_मुक्त_ring - drop mapping of ring buffer */
व्योम vmbus_मुक्त_ring(काष्ठा vmbus_channel *channel)
अणु
	hv_ringbuffer_cleanup(&channel->outbound);
	hv_ringbuffer_cleanup(&channel->inbound);

	अगर (channel->ringbuffer_page) अणु
		__मुक्त_pages(channel->ringbuffer_page,
			     get_order(channel->ringbuffer_pagecount
				       << PAGE_SHIFT));
		channel->ringbuffer_page = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_मुक्त_ring);

/* vmbus_alloc_ring - allocate and map pages क्रम ring buffer */
पूर्णांक vmbus_alloc_ring(काष्ठा vmbus_channel *newchannel,
		     u32 send_size, u32 recv_size)
अणु
	काष्ठा page *page;
	पूर्णांक order;

	अगर (send_size % PAGE_SIZE || recv_size % PAGE_SIZE)
		वापस -EINVAL;

	/* Allocate the ring buffer */
	order = get_order(send_size + recv_size);
	page = alloc_pages_node(cpu_to_node(newchannel->target_cpu),
				GFP_KERNEL|__GFP_ZERO, order);

	अगर (!page)
		page = alloc_pages(GFP_KERNEL|__GFP_ZERO, order);

	अगर (!page)
		वापस -ENOMEM;

	newchannel->ringbuffer_page = page;
	newchannel->ringbuffer_pagecount = (send_size + recv_size) >> PAGE_SHIFT;
	newchannel->ringbuffer_send_offset = send_size >> PAGE_SHIFT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_alloc_ring);

/* Used क्रम Hyper-V Socket: a guest client's connect() to the host */
पूर्णांक vmbus_send_tl_connect_request(स्थिर guid_t *shv_guest_servie_id,
				  स्थिर guid_t *shv_host_servie_id)
अणु
	काष्ठा vmbus_channel_tl_connect_request conn_msg;
	पूर्णांक ret;

	स_रखो(&conn_msg, 0, माप(conn_msg));
	conn_msg.header.msgtype = CHANNELMSG_TL_CONNECT_REQUEST;
	conn_msg.guest_endpoपूर्णांक_id = *shv_guest_servie_id;
	conn_msg.host_service_id = *shv_host_servie_id;

	ret = vmbus_post_msg(&conn_msg, माप(conn_msg), true);

	trace_vmbus_send_tl_connect_request(&conn_msg, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_send_tl_connect_request);

अटल पूर्णांक send_modअगरychannel_without_ack(काष्ठा vmbus_channel *channel, u32 target_vp)
अणु
	काष्ठा vmbus_channel_modअगरychannel msg;
	पूर्णांक ret;

	स_रखो(&msg, 0, माप(msg));
	msg.header.msgtype = CHANNELMSG_MODIFYCHANNEL;
	msg.child_relid = channel->offermsg.child_relid;
	msg.target_vp = target_vp;

	ret = vmbus_post_msg(&msg, माप(msg), true);
	trace_vmbus_send_modअगरychannel(&msg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक send_modअगरychannel_with_ack(काष्ठा vmbus_channel *channel, u32 target_vp)
अणु
	काष्ठा vmbus_channel_modअगरychannel *msg;
	काष्ठा vmbus_channel_msginfo *info;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	info = kzalloc(माप(काष्ठा vmbus_channel_msginfo) +
				माप(काष्ठा vmbus_channel_modअगरychannel),
		       GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	init_completion(&info->रुकोevent);
	info->रुकोing_channel = channel;

	msg = (काष्ठा vmbus_channel_modअगरychannel *)info->msg;
	msg->header.msgtype = CHANNELMSG_MODIFYCHANNEL;
	msg->child_relid = channel->offermsg.child_relid;
	msg->target_vp = target_vp;

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_add_tail(&info->msglistentry, &vmbus_connection.chn_msg_list);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	ret = vmbus_post_msg(msg, माप(*msg), true);
	trace_vmbus_send_modअगरychannel(msg, ret);
	अगर (ret != 0) अणु
		spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
		list_del(&info->msglistentry);
		spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
		जाओ मुक्त_info;
	पूर्ण

	/*
	 * Release channel_mutex; otherwise, vmbus_onoffer_rescind() could block on
	 * the mutex and be unable to संकेत the completion.
	 *
	 * See the caller target_cpu_store() क्रम inक्रमmation about the usage of the
	 * mutex.
	 */
	mutex_unlock(&vmbus_connection.channel_mutex);
	रुको_क्रम_completion(&info->रुकोevent);
	mutex_lock(&vmbus_connection.channel_mutex);

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&info->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	अगर (info->response.modअगरy_response.status)
		ret = -EAGAIN;

मुक्त_info:
	kमुक्त(info);
	वापस ret;
पूर्ण

/*
 * Set/change the vCPU (@target_vp) the channel (@child_relid) will पूर्णांकerrupt.
 *
 * CHANNELMSG_MODIFYCHANNEL messages are aynchronous.  When VMbus version 5.3
 * or later is negotiated, Hyper-V always sends an ACK in response to such a
 * message.  For VMbus version 5.2 and earlier, it never sends an ACK.  With-
 * out an ACK, we can not know when the host will stop पूर्णांकerrupting the "old"
 * vCPU and start पूर्णांकerrupting the "new" vCPU क्रम the given channel.
 *
 * The CHANNELMSG_MODIFYCHANNEL message type is supported since VMBus version
 * VERSION_WIN10_V4_1.
 */
पूर्णांक vmbus_send_modअगरychannel(काष्ठा vmbus_channel *channel, u32 target_vp)
अणु
	अगर (vmbus_proto_version >= VERSION_WIN10_V5_3)
		वापस send_modअगरychannel_with_ack(channel, target_vp);
	वापस send_modअगरychannel_without_ack(channel, target_vp);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_send_modअगरychannel);

/*
 * create_gpadl_header - Creates a gpadl क्रम the specअगरied buffer
 */
अटल पूर्णांक create_gpadl_header(क्रमागत hv_gpadl_type type, व्योम *kbuffer,
			       u32 size, u32 send_offset,
			       काष्ठा vmbus_channel_msginfo **msginfo)
अणु
	पूर्णांक i;
	पूर्णांक pagecount;
	काष्ठा vmbus_channel_gpadl_header *gpadl_header;
	काष्ठा vmbus_channel_gpadl_body *gpadl_body;
	काष्ठा vmbus_channel_msginfo *msgheader;
	काष्ठा vmbus_channel_msginfo *msgbody = शून्य;
	u32 msgsize;

	पूर्णांक pfnsum, pfncount, pfnleft, pfncurr, pfnsize;

	pagecount = hv_gpadl_size(type, size) >> HV_HYP_PAGE_SHIFT;

	/* करो we need a gpadl body msg */
	pfnsize = MAX_SIZE_CHANNEL_MESSAGE -
		  माप(काष्ठा vmbus_channel_gpadl_header) -
		  माप(काष्ठा gpa_range);
	pfncount = pfnsize / माप(u64);

	अगर (pagecount > pfncount) अणु
		/* we need a gpadl body */
		/* fill in the header */
		msgsize = माप(काष्ठा vmbus_channel_msginfo) +
			  माप(काष्ठा vmbus_channel_gpadl_header) +
			  माप(काष्ठा gpa_range) + pfncount * माप(u64);
		msgheader =  kzalloc(msgsize, GFP_KERNEL);
		अगर (!msgheader)
			जाओ nomem;

		INIT_LIST_HEAD(&msgheader->submsglist);
		msgheader->msgsize = msgsize;

		gpadl_header = (काष्ठा vmbus_channel_gpadl_header *)
			msgheader->msg;
		gpadl_header->rangecount = 1;
		gpadl_header->range_buflen = माप(काष्ठा gpa_range) +
					 pagecount * माप(u64);
		gpadl_header->range[0].byte_offset = 0;
		gpadl_header->range[0].byte_count = hv_gpadl_size(type, size);
		क्रम (i = 0; i < pfncount; i++)
			gpadl_header->range[0].pfn_array[i] = hv_gpadl_hvpfn(
				type, kbuffer, size, send_offset, i);
		*msginfo = msgheader;

		pfnsum = pfncount;
		pfnleft = pagecount - pfncount;

		/* how many pfns can we fit */
		pfnsize = MAX_SIZE_CHANNEL_MESSAGE -
			  माप(काष्ठा vmbus_channel_gpadl_body);
		pfncount = pfnsize / माप(u64);

		/* fill in the body */
		जबतक (pfnleft) अणु
			अगर (pfnleft > pfncount)
				pfncurr = pfncount;
			अन्यथा
				pfncurr = pfnleft;

			msgsize = माप(काष्ठा vmbus_channel_msginfo) +
				  माप(काष्ठा vmbus_channel_gpadl_body) +
				  pfncurr * माप(u64);
			msgbody = kzalloc(msgsize, GFP_KERNEL);

			अगर (!msgbody) अणु
				काष्ठा vmbus_channel_msginfo *pos = शून्य;
				काष्ठा vmbus_channel_msginfo *पंचांगp = शून्य;
				/*
				 * Free up all the allocated messages.
				 */
				list_क्रम_each_entry_safe(pos, पंचांगp,
					&msgheader->submsglist,
					msglistentry) अणु

					list_del(&pos->msglistentry);
					kमुक्त(pos);
				पूर्ण

				जाओ nomem;
			पूर्ण

			msgbody->msgsize = msgsize;
			gpadl_body =
				(काष्ठा vmbus_channel_gpadl_body *)msgbody->msg;

			/*
			 * Gpadl is u32 and we are using a poपूर्णांकer which could
			 * be 64-bit
			 * This is governed by the guest/host protocol and
			 * so the hypervisor guarantees that this is ok.
			 */
			क्रम (i = 0; i < pfncurr; i++)
				gpadl_body->pfn[i] = hv_gpadl_hvpfn(type,
					kbuffer, size, send_offset, pfnsum + i);

			/* add to msg header */
			list_add_tail(&msgbody->msglistentry,
				      &msgheader->submsglist);
			pfnsum += pfncurr;
			pfnleft -= pfncurr;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* everything fits in a header */
		msgsize = माप(काष्ठा vmbus_channel_msginfo) +
			  माप(काष्ठा vmbus_channel_gpadl_header) +
			  माप(काष्ठा gpa_range) + pagecount * माप(u64);
		msgheader = kzalloc(msgsize, GFP_KERNEL);
		अगर (msgheader == शून्य)
			जाओ nomem;

		INIT_LIST_HEAD(&msgheader->submsglist);
		msgheader->msgsize = msgsize;

		gpadl_header = (काष्ठा vmbus_channel_gpadl_header *)
			msgheader->msg;
		gpadl_header->rangecount = 1;
		gpadl_header->range_buflen = माप(काष्ठा gpa_range) +
					 pagecount * माप(u64);
		gpadl_header->range[0].byte_offset = 0;
		gpadl_header->range[0].byte_count = hv_gpadl_size(type, size);
		क्रम (i = 0; i < pagecount; i++)
			gpadl_header->range[0].pfn_array[i] = hv_gpadl_hvpfn(
				type, kbuffer, size, send_offset, i);

		*msginfo = msgheader;
	पूर्ण

	वापस 0;
nomem:
	kमुक्त(msgheader);
	kमुक्त(msgbody);
	वापस -ENOMEM;
पूर्ण

/*
 * __vmbus_establish_gpadl - Establish a GPADL क्रम a buffer or ringbuffer
 *
 * @channel: a channel
 * @type: the type of the corresponding GPADL, only meaningful क्रम the guest.
 * @kbuffer: from kदो_स्मृति or vदो_स्मृति
 * @size: page-size multiple
 * @send_offset: the offset (in bytes) where the send ring buffer starts,
 *              should be 0 क्रम BUFFER type gpadl
 * @gpadl_handle: some funky thing
 */
अटल पूर्णांक __vmbus_establish_gpadl(काष्ठा vmbus_channel *channel,
				   क्रमागत hv_gpadl_type type, व्योम *kbuffer,
				   u32 size, u32 send_offset,
				   u32 *gpadl_handle)
अणु
	काष्ठा vmbus_channel_gpadl_header *gpadlmsg;
	काष्ठा vmbus_channel_gpadl_body *gpadl_body;
	काष्ठा vmbus_channel_msginfo *msginfo = शून्य;
	काष्ठा vmbus_channel_msginfo *submsginfo, *पंचांगp;
	काष्ठा list_head *curr;
	u32 next_gpadl_handle;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	next_gpadl_handle =
		(atomic_inc_वापस(&vmbus_connection.next_gpadl_handle) - 1);

	ret = create_gpadl_header(type, kbuffer, size, send_offset, &msginfo);
	अगर (ret)
		वापस ret;

	init_completion(&msginfo->रुकोevent);
	msginfo->रुकोing_channel = channel;

	gpadlmsg = (काष्ठा vmbus_channel_gpadl_header *)msginfo->msg;
	gpadlmsg->header.msgtype = CHANNELMSG_GPADL_HEADER;
	gpadlmsg->child_relid = channel->offermsg.child_relid;
	gpadlmsg->gpadl = next_gpadl_handle;


	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_add_tail(&msginfo->msglistentry,
		      &vmbus_connection.chn_msg_list);

	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	अगर (channel->rescind) अणु
		ret = -ENODEV;
		जाओ cleanup;
	पूर्ण

	ret = vmbus_post_msg(gpadlmsg, msginfo->msgsize -
			     माप(*msginfo), true);

	trace_vmbus_establish_gpadl_header(gpadlmsg, ret);

	अगर (ret != 0)
		जाओ cleanup;

	list_क्रम_each(curr, &msginfo->submsglist) अणु
		submsginfo = (काष्ठा vmbus_channel_msginfo *)curr;
		gpadl_body =
			(काष्ठा vmbus_channel_gpadl_body *)submsginfo->msg;

		gpadl_body->header.msgtype =
			CHANNELMSG_GPADL_BODY;
		gpadl_body->gpadl = next_gpadl_handle;

		ret = vmbus_post_msg(gpadl_body,
				     submsginfo->msgsize - माप(*submsginfo),
				     true);

		trace_vmbus_establish_gpadl_body(gpadl_body, ret);

		अगर (ret != 0)
			जाओ cleanup;

	पूर्ण
	रुको_क्रम_completion(&msginfo->रुकोevent);

	अगर (msginfo->response.gpadl_created.creation_status != 0) अणु
		pr_err("Failed to establish GPADL: err = 0x%x\n",
		       msginfo->response.gpadl_created.creation_status);

		ret = -EDQUOT;
		जाओ cleanup;
	पूर्ण

	अगर (channel->rescind) अणु
		ret = -ENODEV;
		जाओ cleanup;
	पूर्ण

	/* At this poपूर्णांक, we received the gpadl created msg */
	*gpadl_handle = gpadlmsg->gpadl;

cleanup:
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&msginfo->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
	list_क्रम_each_entry_safe(submsginfo, पंचांगp, &msginfo->submsglist,
				 msglistentry) अणु
		kमुक्त(submsginfo);
	पूर्ण

	kमुक्त(msginfo);
	वापस ret;
पूर्ण

/*
 * vmbus_establish_gpadl - Establish a GPADL क्रम the specअगरied buffer
 *
 * @channel: a channel
 * @kbuffer: from kदो_स्मृति or vदो_स्मृति
 * @size: page-size multiple
 * @gpadl_handle: some funky thing
 */
पूर्णांक vmbus_establish_gpadl(काष्ठा vmbus_channel *channel, व्योम *kbuffer,
			  u32 size, u32 *gpadl_handle)
अणु
	वापस __vmbus_establish_gpadl(channel, HV_GPADL_BUFFER, kbuffer, size,
				       0U, gpadl_handle);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_establish_gpadl);

/**
 * request_arr_init - Allocates memory क्रम the requestor array. Each slot
 * keeps track of the next available slot in the array. Initially, each
 * slot poपूर्णांकs to the next one (as in a Linked List). The last slot
 * करोes not poपूर्णांक to anything, so its value is U64_MAX by शेष.
 * @size The size of the array
 */
अटल u64 *request_arr_init(u32 size)
अणु
	पूर्णांक i;
	u64 *req_arr;

	req_arr = kसुस्मृति(size, माप(u64), GFP_KERNEL);
	अगर (!req_arr)
		वापस शून्य;

	क्रम (i = 0; i < size - 1; i++)
		req_arr[i] = i + 1;

	/* Last slot (no more available slots) */
	req_arr[i] = U64_MAX;

	वापस req_arr;
पूर्ण

/*
 * vmbus_alloc_requestor - Initializes @rqstor's fields.
 * Index 0 is the first मुक्त slot
 * @size: Size of the requestor array
 */
अटल पूर्णांक vmbus_alloc_requestor(काष्ठा vmbus_requestor *rqstor, u32 size)
अणु
	u64 *rqst_arr;
	अचिन्हित दीर्घ *biपंचांगap;

	rqst_arr = request_arr_init(size);
	अगर (!rqst_arr)
		वापस -ENOMEM;

	biपंचांगap = biपंचांगap_zalloc(size, GFP_KERNEL);
	अगर (!biपंचांगap) अणु
		kमुक्त(rqst_arr);
		वापस -ENOMEM;
	पूर्ण

	rqstor->req_arr = rqst_arr;
	rqstor->req_biपंचांगap = biपंचांगap;
	rqstor->size = size;
	rqstor->next_request_id = 0;
	spin_lock_init(&rqstor->req_lock);

	वापस 0;
पूर्ण

/*
 * vmbus_मुक्त_requestor - Frees memory allocated क्रम @rqstor
 * @rqstor: Poपूर्णांकer to the requestor काष्ठा
 */
अटल व्योम vmbus_मुक्त_requestor(काष्ठा vmbus_requestor *rqstor)
अणु
	kमुक्त(rqstor->req_arr);
	biपंचांगap_मुक्त(rqstor->req_biपंचांगap);
पूर्ण

अटल पूर्णांक __vmbus_खोलो(काष्ठा vmbus_channel *newchannel,
		       व्योम *userdata, u32 userdatalen,
		       व्योम (*onchannelcallback)(व्योम *context), व्योम *context)
अणु
	काष्ठा vmbus_channel_खोलो_channel *खोलो_msg;
	काष्ठा vmbus_channel_msginfo *खोलो_info = शून्य;
	काष्ठा page *page = newchannel->ringbuffer_page;
	u32 send_pages, recv_pages;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (userdatalen > MAX_USER_DEFINED_BYTES)
		वापस -EINVAL;

	send_pages = newchannel->ringbuffer_send_offset;
	recv_pages = newchannel->ringbuffer_pagecount - send_pages;

	अगर (newchannel->state != CHANNEL_OPEN_STATE)
		वापस -EINVAL;

	/* Create and init requestor */
	अगर (newchannel->rqstor_size) अणु
		अगर (vmbus_alloc_requestor(&newchannel->requestor, newchannel->rqstor_size))
			वापस -ENOMEM;
	पूर्ण

	newchannel->state = CHANNEL_OPENING_STATE;
	newchannel->onchannel_callback = onchannelcallback;
	newchannel->channel_callback_context = context;

	err = hv_ringbuffer_init(&newchannel->outbound, page, send_pages);
	अगर (err)
		जाओ error_clean_ring;

	err = hv_ringbuffer_init(&newchannel->inbound,
				 &page[send_pages], recv_pages);
	अगर (err)
		जाओ error_clean_ring;

	/* Establish the gpadl क्रम the ring buffer */
	newchannel->ringbuffer_gpadlhandle = 0;

	err = __vmbus_establish_gpadl(newchannel, HV_GPADL_RING,
				      page_address(newchannel->ringbuffer_page),
				      (send_pages + recv_pages) << PAGE_SHIFT,
				      newchannel->ringbuffer_send_offset << PAGE_SHIFT,
				      &newchannel->ringbuffer_gpadlhandle);
	अगर (err)
		जाओ error_clean_ring;

	/* Create and init the channel खोलो message */
	खोलो_info = kzalloc(माप(*खोलो_info) +
			   माप(काष्ठा vmbus_channel_खोलो_channel),
			   GFP_KERNEL);
	अगर (!खोलो_info) अणु
		err = -ENOMEM;
		जाओ error_मुक्त_gpadl;
	पूर्ण

	init_completion(&खोलो_info->रुकोevent);
	खोलो_info->रुकोing_channel = newchannel;

	खोलो_msg = (काष्ठा vmbus_channel_खोलो_channel *)खोलो_info->msg;
	खोलो_msg->header.msgtype = CHANNELMSG_OPENCHANNEL;
	खोलो_msg->खोलोid = newchannel->offermsg.child_relid;
	खोलो_msg->child_relid = newchannel->offermsg.child_relid;
	खोलो_msg->ringbuffer_gpadlhandle = newchannel->ringbuffer_gpadlhandle;
	/*
	 * The unit of ->करोwnstream_ringbuffer_pageoffset is HV_HYP_PAGE and
	 * the unit of ->ringbuffer_send_offset (i.e. send_pages) is PAGE, so
	 * here we calculate it पूर्णांकo HV_HYP_PAGE.
	 */
	खोलो_msg->करोwnstream_ringbuffer_pageoffset =
		hv_ring_gpadl_send_hvpgoffset(send_pages << PAGE_SHIFT);
	खोलो_msg->target_vp = hv_cpu_number_to_vp_number(newchannel->target_cpu);

	अगर (userdatalen)
		स_नकल(खोलो_msg->userdata, userdata, userdatalen);

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_add_tail(&खोलो_info->msglistentry,
		      &vmbus_connection.chn_msg_list);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	अगर (newchannel->rescind) अणु
		err = -ENODEV;
		जाओ error_clean_msglist;
	पूर्ण

	err = vmbus_post_msg(खोलो_msg,
			     माप(काष्ठा vmbus_channel_खोलो_channel), true);

	trace_vmbus_खोलो(खोलो_msg, err);

	अगर (err != 0)
		जाओ error_clean_msglist;

	रुको_क्रम_completion(&खोलो_info->रुकोevent);

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&खोलो_info->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	अगर (newchannel->rescind) अणु
		err = -ENODEV;
		जाओ error_मुक्त_info;
	पूर्ण

	अगर (खोलो_info->response.खोलो_result.status) अणु
		err = -EAGAIN;
		जाओ error_मुक्त_info;
	पूर्ण

	newchannel->state = CHANNEL_OPENED_STATE;
	kमुक्त(खोलो_info);
	वापस 0;

error_clean_msglist:
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&खोलो_info->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
error_मुक्त_info:
	kमुक्त(खोलो_info);
error_मुक्त_gpadl:
	vmbus_tearकरोwn_gpadl(newchannel, newchannel->ringbuffer_gpadlhandle);
	newchannel->ringbuffer_gpadlhandle = 0;
error_clean_ring:
	hv_ringbuffer_cleanup(&newchannel->outbound);
	hv_ringbuffer_cleanup(&newchannel->inbound);
	vmbus_मुक्त_requestor(&newchannel->requestor);
	newchannel->state = CHANNEL_OPEN_STATE;
	वापस err;
पूर्ण

/*
 * vmbus_connect_ring - Open the channel but reuse ring buffer
 */
पूर्णांक vmbus_connect_ring(काष्ठा vmbus_channel *newchannel,
		       व्योम (*onchannelcallback)(व्योम *context), व्योम *context)
अणु
	वापस  __vmbus_खोलो(newchannel, शून्य, 0, onchannelcallback, context);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_connect_ring);

/*
 * vmbus_खोलो - Open the specअगरied channel.
 */
पूर्णांक vmbus_खोलो(काष्ठा vmbus_channel *newchannel,
	       u32 send_ringbuffer_size, u32 recv_ringbuffer_size,
	       व्योम *userdata, u32 userdatalen,
	       व्योम (*onchannelcallback)(व्योम *context), व्योम *context)
अणु
	पूर्णांक err;

	err = vmbus_alloc_ring(newchannel, send_ringbuffer_size,
			       recv_ringbuffer_size);
	अगर (err)
		वापस err;

	err = __vmbus_खोलो(newchannel, userdata, userdatalen,
			   onchannelcallback, context);
	अगर (err)
		vmbus_मुक्त_ring(newchannel);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_खोलो);

/*
 * vmbus_tearकरोwn_gpadl -Tearकरोwn the specअगरied GPADL handle
 */
पूर्णांक vmbus_tearकरोwn_gpadl(काष्ठा vmbus_channel *channel, u32 gpadl_handle)
अणु
	काष्ठा vmbus_channel_gpadl_tearकरोwn *msg;
	काष्ठा vmbus_channel_msginfo *info;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	info = kzalloc(माप(*info) +
		       माप(काष्ठा vmbus_channel_gpadl_tearकरोwn), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	init_completion(&info->रुकोevent);
	info->रुकोing_channel = channel;

	msg = (काष्ठा vmbus_channel_gpadl_tearकरोwn *)info->msg;

	msg->header.msgtype = CHANNELMSG_GPADL_TEARDOWN;
	msg->child_relid = channel->offermsg.child_relid;
	msg->gpadl = gpadl_handle;

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_add_tail(&info->msglistentry,
		      &vmbus_connection.chn_msg_list);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	अगर (channel->rescind)
		जाओ post_msg_err;

	ret = vmbus_post_msg(msg, माप(काष्ठा vmbus_channel_gpadl_tearकरोwn),
			     true);

	trace_vmbus_tearकरोwn_gpadl(msg, ret);

	अगर (ret)
		जाओ post_msg_err;

	रुको_क्रम_completion(&info->रुकोevent);

post_msg_err:
	/*
	 * If the channel has been rescinded;
	 * we will be awakened by the rescind
	 * handler; set the error code to zero so we करोn't leak memory.
	 */
	अगर (channel->rescind)
		ret = 0;

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&info->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	kमुक्त(info);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_tearकरोwn_gpadl);

व्योम vmbus_reset_channel_cb(काष्ठा vmbus_channel *channel)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * vmbus_on_event(), running in the per-channel tasklet, can race
	 * with vmbus_बंद_पूर्णांकernal() in the हाल of SMP guest, e.g., when
	 * the क्रमmer is accessing channel->inbound.ring_buffer, the latter
	 * could be मुक्तing the ring_buffer pages, so here we must stop it
	 * first.
	 *
	 * vmbus_chan_sched() might call the netvsc driver callback function
	 * that ends up scheduling NAPI work that accesses the ring buffer.
	 * At this poपूर्णांक, we have to ensure that any such work is completed
	 * and that the channel ring buffer is no दीर्घer being accessed, cf.
	 * the calls to napi_disable() in netvsc_device_हटाओ().
	 */
	tasklet_disable(&channel->callback_event);

	/* See the अंतरभूत comments in vmbus_chan_sched(). */
	spin_lock_irqsave(&channel->sched_lock, flags);
	channel->onchannel_callback = शून्य;
	spin_unlock_irqrestore(&channel->sched_lock, flags);

	channel->sc_creation_callback = शून्य;

	/* Re-enable tasklet क्रम use on re-खोलो */
	tasklet_enable(&channel->callback_event);
पूर्ण

अटल पूर्णांक vmbus_बंद_पूर्णांकernal(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा vmbus_channel_बंद_channel *msg;
	पूर्णांक ret;

	vmbus_reset_channel_cb(channel);

	/*
	 * In हाल a device driver's probe() fails (e.g.,
	 * util_probe() -> vmbus_खोलो() वापसs -ENOMEM) and the device is
	 * rescinded later (e.g., we dynamically disable an Integrated Service
	 * in Hyper-V Manager), the driver's हटाओ() invokes vmbus_बंद():
	 * here we should skip most of the below cleanup work.
	 */
	अगर (channel->state != CHANNEL_OPENED_STATE)
		वापस -EINVAL;

	channel->state = CHANNEL_OPEN_STATE;

	/* Send a closing message */

	msg = &channel->बंद_msg.msg;

	msg->header.msgtype = CHANNELMSG_CLOSECHANNEL;
	msg->child_relid = channel->offermsg.child_relid;

	ret = vmbus_post_msg(msg, माप(काष्ठा vmbus_channel_बंद_channel),
			     true);

	trace_vmbus_बंद_पूर्णांकernal(msg, ret);

	अगर (ret) अणु
		pr_err("Close failed: close post msg return is %d\n", ret);
		/*
		 * If we failed to post the बंद msg,
		 * it is perhaps better to leak memory.
		 */
	पूर्ण

	/* Tear करोwn the gpadl क्रम the channel's ring buffer */
	अन्यथा अगर (channel->ringbuffer_gpadlhandle) अणु
		ret = vmbus_tearकरोwn_gpadl(channel,
					   channel->ringbuffer_gpadlhandle);
		अगर (ret) अणु
			pr_err("Close failed: teardown gpadl return %d\n", ret);
			/*
			 * If we failed to tearकरोwn gpadl,
			 * it is perhaps better to leak memory.
			 */
		पूर्ण

		channel->ringbuffer_gpadlhandle = 0;
	पूर्ण

	अगर (!ret)
		vmbus_मुक्त_requestor(&channel->requestor);

	वापस ret;
पूर्ण

/* disconnect ring - बंद all channels */
पूर्णांक vmbus_disconnect_ring(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा vmbus_channel *cur_channel, *पंचांगp;
	पूर्णांक ret;

	अगर (channel->primary_channel != शून्य)
		वापस -EINVAL;

	list_क्रम_each_entry_safe(cur_channel, पंचांगp, &channel->sc_list, sc_list) अणु
		अगर (cur_channel->rescind)
			रुको_क्रम_completion(&cur_channel->rescind_event);

		mutex_lock(&vmbus_connection.channel_mutex);
		अगर (vmbus_बंद_पूर्णांकernal(cur_channel) == 0) अणु
			vmbus_मुक्त_ring(cur_channel);

			अगर (cur_channel->rescind)
				hv_process_channel_removal(cur_channel);
		पूर्ण
		mutex_unlock(&vmbus_connection.channel_mutex);
	पूर्ण

	/*
	 * Now बंद the primary.
	 */
	mutex_lock(&vmbus_connection.channel_mutex);
	ret = vmbus_बंद_पूर्णांकernal(channel);
	mutex_unlock(&vmbus_connection.channel_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_disconnect_ring);

/*
 * vmbus_बंद - Close the specअगरied channel
 */
व्योम vmbus_बंद(काष्ठा vmbus_channel *channel)
अणु
	अगर (vmbus_disconnect_ring(channel) == 0)
		vmbus_मुक्त_ring(channel);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_बंद);

/**
 * vmbus_sendpacket() - Send the specअगरied buffer on the given channel
 * @channel: Poपूर्णांकer to vmbus_channel काष्ठाure
 * @buffer: Poपूर्णांकer to the buffer you want to send the data from.
 * @bufferlen: Maximum size of what the buffer holds.
 * @requestid: Identअगरier of the request
 * @type: Type of packet that is being sent e.g. negotiate, समय
 *	  packet etc.
 * @flags: 0 or VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED
 *
 * Sends data in @buffer directly to Hyper-V via the vmbus.
 * This will send the data unparsed to Hyper-V.
 *
 * Mainly used by Hyper-V drivers.
 */
पूर्णांक vmbus_sendpacket(काष्ठा vmbus_channel *channel, व्योम *buffer,
			   u32 bufferlen, u64 requestid,
			   क्रमागत vmbus_packet_type type, u32 flags)
अणु
	काष्ठा vmpacket_descriptor desc;
	u32 packetlen = माप(काष्ठा vmpacket_descriptor) + bufferlen;
	u32 packetlen_aligned = ALIGN(packetlen, माप(u64));
	काष्ठा kvec bufferlist[3];
	u64 aligned_data = 0;
	पूर्णांक num_vecs = ((bufferlen != 0) ? 3 : 1);


	/* Setup the descriptor */
	desc.type = type; /* VmbusPacketTypeDataInBand; */
	desc.flags = flags; /* VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED; */
	/* in 8-bytes granularity */
	desc.offset8 = माप(काष्ठा vmpacket_descriptor) >> 3;
	desc.len8 = (u16)(packetlen_aligned >> 3);
	desc.trans_id = VMBUS_RQST_ERROR; /* will be updated in hv_ringbuffer_ग_लिखो() */

	bufferlist[0].iov_base = &desc;
	bufferlist[0].iov_len = माप(काष्ठा vmpacket_descriptor);
	bufferlist[1].iov_base = buffer;
	bufferlist[1].iov_len = bufferlen;
	bufferlist[2].iov_base = &aligned_data;
	bufferlist[2].iov_len = (packetlen_aligned - packetlen);

	वापस hv_ringbuffer_ग_लिखो(channel, bufferlist, num_vecs, requestid);
पूर्ण
EXPORT_SYMBOL(vmbus_sendpacket);

/*
 * vmbus_sendpacket_pagebuffer - Send a range of single-page buffer
 * packets using a GPADL Direct packet type. This पूर्णांकerface allows you
 * to control notअगरying the host. This will be useful क्रम sending
 * batched data. Also the sender can control the send flags
 * explicitly.
 */
पूर्णांक vmbus_sendpacket_pagebuffer(काष्ठा vmbus_channel *channel,
				काष्ठा hv_page_buffer pagebuffers[],
				u32 pagecount, व्योम *buffer, u32 bufferlen,
				u64 requestid)
अणु
	पूर्णांक i;
	काष्ठा vmbus_channel_packet_page_buffer desc;
	u32 descsize;
	u32 packetlen;
	u32 packetlen_aligned;
	काष्ठा kvec bufferlist[3];
	u64 aligned_data = 0;

	अगर (pagecount > MAX_PAGE_BUFFER_COUNT)
		वापस -EINVAL;

	/*
	 * Adjust the size करोwn since vmbus_channel_packet_page_buffer is the
	 * largest size we support
	 */
	descsize = माप(काष्ठा vmbus_channel_packet_page_buffer) -
			  ((MAX_PAGE_BUFFER_COUNT - pagecount) *
			  माप(काष्ठा hv_page_buffer));
	packetlen = descsize + bufferlen;
	packetlen_aligned = ALIGN(packetlen, माप(u64));

	/* Setup the descriptor */
	desc.type = VM_PKT_DATA_USING_GPA_सूचीECT;
	desc.flags = VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED;
	desc.dataoffset8 = descsize >> 3; /* in 8-bytes granularity */
	desc.length8 = (u16)(packetlen_aligned >> 3);
	desc.transactionid = VMBUS_RQST_ERROR; /* will be updated in hv_ringbuffer_ग_लिखो() */
	desc.reserved = 0;
	desc.rangecount = pagecount;

	क्रम (i = 0; i < pagecount; i++) अणु
		desc.range[i].len = pagebuffers[i].len;
		desc.range[i].offset = pagebuffers[i].offset;
		desc.range[i].pfn	 = pagebuffers[i].pfn;
	पूर्ण

	bufferlist[0].iov_base = &desc;
	bufferlist[0].iov_len = descsize;
	bufferlist[1].iov_base = buffer;
	bufferlist[1].iov_len = bufferlen;
	bufferlist[2].iov_base = &aligned_data;
	bufferlist[2].iov_len = (packetlen_aligned - packetlen);

	वापस hv_ringbuffer_ग_लिखो(channel, bufferlist, 3, requestid);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_sendpacket_pagebuffer);

/*
 * vmbus_sendpacket_multipagebuffer - Send a multi-page buffer packet
 * using a GPADL Direct packet type.
 * The buffer includes the vmbus descriptor.
 */
पूर्णांक vmbus_sendpacket_mpb_desc(काष्ठा vmbus_channel *channel,
			      काष्ठा vmbus_packet_mpb_array *desc,
			      u32 desc_size,
			      व्योम *buffer, u32 bufferlen, u64 requestid)
अणु
	u32 packetlen;
	u32 packetlen_aligned;
	काष्ठा kvec bufferlist[3];
	u64 aligned_data = 0;

	packetlen = desc_size + bufferlen;
	packetlen_aligned = ALIGN(packetlen, माप(u64));

	/* Setup the descriptor */
	desc->type = VM_PKT_DATA_USING_GPA_सूचीECT;
	desc->flags = VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED;
	desc->dataoffset8 = desc_size >> 3; /* in 8-bytes granularity */
	desc->length8 = (u16)(packetlen_aligned >> 3);
	desc->transactionid = VMBUS_RQST_ERROR; /* will be updated in hv_ringbuffer_ग_लिखो() */
	desc->reserved = 0;
	desc->rangecount = 1;

	bufferlist[0].iov_base = desc;
	bufferlist[0].iov_len = desc_size;
	bufferlist[1].iov_base = buffer;
	bufferlist[1].iov_len = bufferlen;
	bufferlist[2].iov_base = &aligned_data;
	bufferlist[2].iov_len = (packetlen_aligned - packetlen);

	वापस hv_ringbuffer_ग_लिखो(channel, bufferlist, 3, requestid);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_sendpacket_mpb_desc);

/**
 * __vmbus_recvpacket() - Retrieve the user packet on the specअगरied channel
 * @channel: Poपूर्णांकer to vmbus_channel काष्ठाure
 * @buffer: Poपूर्णांकer to the buffer you want to receive the data पूर्णांकo.
 * @bufferlen: Maximum size of what the buffer can hold.
 * @buffer_actual_len: The actual size of the data after it was received.
 * @requestid: Identअगरier of the request
 * @raw: true means keep the vmpacket_descriptor header in the received data.
 *
 * Receives directly from the hyper-v vmbus and माला_दो the data it received
 * पूर्णांकo Buffer. This will receive the data unparsed from hyper-v.
 *
 * Mainly used by Hyper-V drivers.
 */
अटल अंतरभूत पूर्णांक
__vmbus_recvpacket(काष्ठा vmbus_channel *channel, व्योम *buffer,
		   u32 bufferlen, u32 *buffer_actual_len, u64 *requestid,
		   bool raw)
अणु
	वापस hv_ringbuffer_पढ़ो(channel, buffer, bufferlen,
				  buffer_actual_len, requestid, raw);

पूर्ण

पूर्णांक vmbus_recvpacket(काष्ठा vmbus_channel *channel, व्योम *buffer,
		     u32 bufferlen, u32 *buffer_actual_len,
		     u64 *requestid)
अणु
	वापस __vmbus_recvpacket(channel, buffer, bufferlen,
				  buffer_actual_len, requestid, false);
पूर्ण
EXPORT_SYMBOL(vmbus_recvpacket);

/*
 * vmbus_recvpacket_raw - Retrieve the raw packet on the specअगरied channel
 */
पूर्णांक vmbus_recvpacket_raw(काष्ठा vmbus_channel *channel, व्योम *buffer,
			      u32 bufferlen, u32 *buffer_actual_len,
			      u64 *requestid)
अणु
	वापस __vmbus_recvpacket(channel, buffer, bufferlen,
				  buffer_actual_len, requestid, true);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_recvpacket_raw);

/*
 * vmbus_next_request_id - Returns a new request id. It is also
 * the index at which the guest memory address is stored.
 * Uses a spin lock to aव्योम race conditions.
 * @rqstor: Poपूर्णांकer to the requestor काष्ठा
 * @rqst_add: Guest memory address to be stored in the array
 */
u64 vmbus_next_request_id(काष्ठा vmbus_requestor *rqstor, u64 rqst_addr)
अणु
	अचिन्हित दीर्घ flags;
	u64 current_id;
	स्थिर काष्ठा vmbus_channel *channel =
		container_of(rqstor, स्थिर काष्ठा vmbus_channel, requestor);

	/* Check rqstor has been initialized */
	अगर (!channel->rqstor_size)
		वापस VMBUS_NO_RQSTOR;

	spin_lock_irqsave(&rqstor->req_lock, flags);
	current_id = rqstor->next_request_id;

	/* Requestor array is full */
	अगर (current_id >= rqstor->size) अणु
		spin_unlock_irqrestore(&rqstor->req_lock, flags);
		वापस VMBUS_RQST_ERROR;
	पूर्ण

	rqstor->next_request_id = rqstor->req_arr[current_id];
	rqstor->req_arr[current_id] = rqst_addr;

	/* The alपढ़ोy held spin lock provides atomicity */
	biपंचांगap_set(rqstor->req_biपंचांगap, current_id, 1);

	spin_unlock_irqrestore(&rqstor->req_lock, flags);

	/*
	 * Cannot वापस an ID of 0, which is reserved क्रम an unsolicited
	 * message from Hyper-V.
	 */
	वापस current_id + 1;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_next_request_id);

/*
 * vmbus_request_addr - Returns the memory address stored at @trans_id
 * in @rqstor. Uses a spin lock to aव्योम race conditions.
 * @rqstor: Poपूर्णांकer to the requestor काष्ठा
 * @trans_id: Request id sent back from Hyper-V. Becomes the requestor's
 * next request id.
 */
u64 vmbus_request_addr(काष्ठा vmbus_requestor *rqstor, u64 trans_id)
अणु
	अचिन्हित दीर्घ flags;
	u64 req_addr;
	स्थिर काष्ठा vmbus_channel *channel =
		container_of(rqstor, स्थिर काष्ठा vmbus_channel, requestor);

	/* Check rqstor has been initialized */
	अगर (!channel->rqstor_size)
		वापस VMBUS_NO_RQSTOR;

	/* Hyper-V can send an unsolicited message with ID of 0 */
	अगर (!trans_id)
		वापस trans_id;

	spin_lock_irqsave(&rqstor->req_lock, flags);

	/* Data corresponding to trans_id is stored at trans_id - 1 */
	trans_id--;

	/* Invalid trans_id */
	अगर (trans_id >= rqstor->size || !test_bit(trans_id, rqstor->req_biपंचांगap)) अणु
		spin_unlock_irqrestore(&rqstor->req_lock, flags);
		वापस VMBUS_RQST_ERROR;
	पूर्ण

	req_addr = rqstor->req_arr[trans_id];
	rqstor->req_arr[trans_id] = rqstor->next_request_id;
	rqstor->next_request_id = trans_id;

	/* The alपढ़ोy held spin lock provides atomicity */
	biपंचांगap_clear(rqstor->req_biपंचांगap, trans_id, 1);

	spin_unlock_irqrestore(&rqstor->req_lock, flags);
	वापस req_addr;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_request_addr);
