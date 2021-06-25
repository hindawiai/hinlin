<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
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
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/mshyperv.h>

#समावेश "hyperv_vmbus.h"


काष्ठा vmbus_connection vmbus_connection = अणु
	.conn_state		= DISCONNECTED,
	.unload_event		= COMPLETION_INITIALIZER(
				  vmbus_connection.unload_event),
	.next_gpadl_handle	= ATOMIC_INIT(0xE1E10),

	.पढ़ोy_क्रम_suspend_event = COMPLETION_INITIALIZER(
				  vmbus_connection.पढ़ोy_क्रम_suspend_event),
	.पढ़ोy_क्रम_resume_event	= COMPLETION_INITIALIZER(
				  vmbus_connection.पढ़ोy_क्रम_resume_event),
पूर्ण;
EXPORT_SYMBOL_GPL(vmbus_connection);

/*
 * Negotiated protocol version with the host.
 */
__u32 vmbus_proto_version;
EXPORT_SYMBOL_GPL(vmbus_proto_version);

/*
 * Table of VMBus versions listed from newest to oldest.
 */
अटल __u32 vmbus_versions[] = अणु
	VERSION_WIN10_V5_3,
	VERSION_WIN10_V5_2,
	VERSION_WIN10_V5_1,
	VERSION_WIN10_V5,
	VERSION_WIN10_V4_1,
	VERSION_WIN10,
	VERSION_WIN8_1,
	VERSION_WIN8,
	VERSION_WIN7,
	VERSION_WS2008
पूर्ण;

/*
 * Maximal VMBus protocol version guests can negotiate.  Useful to cap the
 * VMBus version क्रम testing and debugging purpose.
 */
अटल uपूर्णांक max_version = VERSION_WIN10_V5_3;

module_param(max_version, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_version,
		 "Maximal VMBus protocol version which can be negotiated");

पूर्णांक vmbus_negotiate_version(काष्ठा vmbus_channel_msginfo *msginfo, u32 version)
अणु
	पूर्णांक ret = 0;
	काष्ठा vmbus_channel_initiate_contact *msg;
	अचिन्हित दीर्घ flags;

	init_completion(&msginfo->रुकोevent);

	msg = (काष्ठा vmbus_channel_initiate_contact *)msginfo->msg;

	स_रखो(msg, 0, माप(*msg));
	msg->header.msgtype = CHANNELMSG_INITIATE_CONTACT;
	msg->vmbus_version_requested = version;

	/*
	 * VMBus protocol 5.0 (VERSION_WIN10_V5) and higher require that we must
	 * use VMBUS_MESSAGE_CONNECTION_ID_4 क्रम the Initiate Contact Message,
	 * and क्रम subsequent messages, we must use the Message Connection ID
	 * field in the host-वापसed Version Response Message. And, with
	 * VERSION_WIN10_V5 and higher, we करोn't use msg->पूर्णांकerrupt_page, but we
	 * tell the host explicitly that we still use VMBUS_MESSAGE_SINT(2) क्रम
	 * compatibility.
	 *
	 * On old hosts, we should always use VMBUS_MESSAGE_CONNECTION_ID (1).
	 */
	अगर (version >= VERSION_WIN10_V5) अणु
		msg->msg_sपूर्णांक = VMBUS_MESSAGE_SINT;
		vmbus_connection.msg_conn_id = VMBUS_MESSAGE_CONNECTION_ID_4;
	पूर्ण अन्यथा अणु
		msg->पूर्णांकerrupt_page = virt_to_phys(vmbus_connection.पूर्णांक_page);
		vmbus_connection.msg_conn_id = VMBUS_MESSAGE_CONNECTION_ID;
	पूर्ण

	msg->monitor_page1 = virt_to_phys(vmbus_connection.monitor_pages[0]);
	msg->monitor_page2 = virt_to_phys(vmbus_connection.monitor_pages[1]);
	msg->target_vcpu = hv_cpu_number_to_vp_number(VMBUS_CONNECT_CPU);

	/*
	 * Add to list beक्रमe we send the request since we may
	 * receive the response beक्रमe वापसing from this routine
	 */
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_add_tail(&msginfo->msglistentry,
		      &vmbus_connection.chn_msg_list);

	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	ret = vmbus_post_msg(msg,
			     माप(काष्ठा vmbus_channel_initiate_contact),
			     true);

	trace_vmbus_negotiate_version(msg, ret);

	अगर (ret != 0) अणु
		spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
		list_del(&msginfo->msglistentry);
		spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock,
					flags);
		वापस ret;
	पूर्ण

	/* Wait क्रम the connection response */
	रुको_क्रम_completion(&msginfo->रुकोevent);

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&msginfo->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	/* Check अगर successful */
	अगर (msginfo->response.version_response.version_supported) अणु
		vmbus_connection.conn_state = CONNECTED;

		अगर (version >= VERSION_WIN10_V5)
			vmbus_connection.msg_conn_id =
				msginfo->response.version_response.msg_conn_id;
	पूर्ण अन्यथा अणु
		वापस -ECONNREFUSED;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * vmbus_connect - Sends a connect request on the partition service connection
 */
पूर्णांक vmbus_connect(व्योम)
अणु
	काष्ठा vmbus_channel_msginfo *msginfo = शून्य;
	पूर्णांक i, ret = 0;
	__u32 version;

	/* Initialize the vmbus connection */
	vmbus_connection.conn_state = CONNECTING;
	vmbus_connection.work_queue = create_workqueue("hv_vmbus_con");
	अगर (!vmbus_connection.work_queue) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	vmbus_connection.handle_primary_chan_wq =
		create_workqueue("hv_pri_chan");
	अगर (!vmbus_connection.handle_primary_chan_wq) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	vmbus_connection.handle_sub_chan_wq =
		create_workqueue("hv_sub_chan");
	अगर (!vmbus_connection.handle_sub_chan_wq) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	INIT_LIST_HEAD(&vmbus_connection.chn_msg_list);
	spin_lock_init(&vmbus_connection.channelmsg_lock);

	INIT_LIST_HEAD(&vmbus_connection.chn_list);
	mutex_init(&vmbus_connection.channel_mutex);

	/*
	 * Setup the vmbus event connection क्रम channel पूर्णांकerrupt
	 * असलtraction stuff
	 */
	vmbus_connection.पूर्णांक_page =
	(व्योम *)hv_alloc_hyperv_zeroed_page();
	अगर (vmbus_connection.पूर्णांक_page == शून्य) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	vmbus_connection.recv_पूर्णांक_page = vmbus_connection.पूर्णांक_page;
	vmbus_connection.send_पूर्णांक_page =
		(व्योम *)((अचिन्हित दीर्घ)vmbus_connection.पूर्णांक_page +
			(HV_HYP_PAGE_SIZE >> 1));

	/*
	 * Setup the monitor notअगरication facility. The 1st page क्रम
	 * parent->child and the 2nd page क्रम child->parent
	 */
	vmbus_connection.monitor_pages[0] = (व्योम *)hv_alloc_hyperv_zeroed_page();
	vmbus_connection.monitor_pages[1] = (व्योम *)hv_alloc_hyperv_zeroed_page();
	अगर ((vmbus_connection.monitor_pages[0] == शून्य) ||
	    (vmbus_connection.monitor_pages[1] == शून्य)) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	msginfo = kzalloc(माप(*msginfo) +
			  माप(काष्ठा vmbus_channel_initiate_contact),
			  GFP_KERNEL);
	अगर (msginfo == शून्य) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/*
	 * Negotiate a compatible VMBUS version number with the
	 * host. We start with the highest number we can support
	 * and work our way करोwn until we negotiate a compatible
	 * version.
	 */

	क्रम (i = 0; ; i++) अणु
		अगर (i == ARRAY_SIZE(vmbus_versions))
			जाओ cleanup;

		version = vmbus_versions[i];
		अगर (version > max_version)
			जारी;

		ret = vmbus_negotiate_version(msginfo, version);
		अगर (ret == -ETIMEDOUT)
			जाओ cleanup;

		अगर (vmbus_connection.conn_state == CONNECTED)
			अवरोध;
	पूर्ण

	अगर (hv_is_isolation_supported() && version < VERSION_WIN10_V5_2) अणु
		pr_err("Invalid VMBus version %d.%d (expected >= %d.%d) from the host supporting isolation\n",
		       version >> 16, version & 0xFFFF, VERSION_WIN10_V5_2 >> 16, VERSION_WIN10_V5_2 & 0xFFFF);
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	vmbus_proto_version = version;
	pr_info("Vmbus version:%d.%d\n",
		version >> 16, version & 0xFFFF);

	vmbus_connection.channels = kसुस्मृति(MAX_CHANNEL_RELIDS,
					    माप(काष्ठा vmbus_channel *),
					    GFP_KERNEL);
	अगर (vmbus_connection.channels == शून्य) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	kमुक्त(msginfo);
	वापस 0;

cleanup:
	pr_err("Unable to connect to host\n");

	vmbus_connection.conn_state = DISCONNECTED;
	vmbus_disconnect();

	kमुक्त(msginfo);

	वापस ret;
पूर्ण

व्योम vmbus_disconnect(व्योम)
अणु
	/*
	 * First send the unload request to the host.
	 */
	vmbus_initiate_unload(false);

	अगर (vmbus_connection.handle_sub_chan_wq)
		destroy_workqueue(vmbus_connection.handle_sub_chan_wq);

	अगर (vmbus_connection.handle_primary_chan_wq)
		destroy_workqueue(vmbus_connection.handle_primary_chan_wq);

	अगर (vmbus_connection.work_queue)
		destroy_workqueue(vmbus_connection.work_queue);

	अगर (vmbus_connection.पूर्णांक_page) अणु
		hv_मुक्त_hyperv_page((अचिन्हित दीर्घ)vmbus_connection.पूर्णांक_page);
		vmbus_connection.पूर्णांक_page = शून्य;
	पूर्ण

	hv_मुक्त_hyperv_page((अचिन्हित दीर्घ)vmbus_connection.monitor_pages[0]);
	hv_मुक्त_hyperv_page((अचिन्हित दीर्घ)vmbus_connection.monitor_pages[1]);
	vmbus_connection.monitor_pages[0] = शून्य;
	vmbus_connection.monitor_pages[1] = शून्य;
पूर्ण

/*
 * relid2channel - Get the channel object given its
 * child relative id (ie channel id)
 */
काष्ठा vmbus_channel *relid2channel(u32 relid)
अणु
	अगर (WARN_ON(relid >= MAX_CHANNEL_RELIDS))
		वापस शून्य;
	वापस READ_ONCE(vmbus_connection.channels[relid]);
पूर्ण

/*
 * vmbus_on_event - Process a channel event notअगरication
 *
 * For batched channels (शेष) optimize host to guest संकेतing
 * by ensuring:
 * 1. While पढ़ोing the channel, we disable पूर्णांकerrupts from host.
 * 2. Ensure that we process all posted messages from the host
 *    beक्रमe वापसing from this callback.
 * 3. Once we वापस, enable संकेतing from the host. Once this
 *    state is set we check to see अगर additional packets are
 *    available to पढ़ो. In this हाल we repeat the process.
 *    If this tasklet has been running क्रम a दीर्घ समय
 *    then reschedule ourselves.
 */
व्योम vmbus_on_event(अचिन्हित दीर्घ data)
अणु
	काष्ठा vmbus_channel *channel = (व्योम *) data;
	अचिन्हित दीर्घ समय_limit = jअगरfies + 2;

	trace_vmbus_on_event(channel);

	hv_debug_delay_test(channel, INTERRUPT_DELAY);
	करो अणु
		व्योम (*callback_fn)(व्योम *);

		/* A channel once created is persistent even when
		 * there is no driver handling the device. An
		 * unloading driver sets the onchannel_callback to शून्य.
		 */
		callback_fn = READ_ONCE(channel->onchannel_callback);
		अगर (unlikely(callback_fn == शून्य))
			वापस;

		(*callback_fn)(channel->channel_callback_context);

		अगर (channel->callback_mode != HV_CALL_BATCHED)
			वापस;

		अगर (likely(hv_end_पढ़ो(&channel->inbound) == 0))
			वापस;

		hv_begin_पढ़ो(&channel->inbound);
	पूर्ण जबतक (likely(समय_beक्रमe(jअगरfies, समय_limit)));

	/* The समय limit (2 jअगरfies) has been reached */
	tasklet_schedule(&channel->callback_event);
पूर्ण

/*
 * vmbus_post_msg - Send a msg on the vmbus's message connection
 */
पूर्णांक vmbus_post_msg(व्योम *buffer, माप_प्रकार buflen, bool can_sleep)
अणु
	काष्ठा vmbus_channel_message_header *hdr;
	जोड़ hv_connection_id conn_id;
	पूर्णांक ret = 0;
	पूर्णांक retries = 0;
	u32 usec = 1;

	conn_id.asu32 = 0;
	conn_id.u.id = vmbus_connection.msg_conn_id;

	/*
	 * hv_post_message() can have transient failures because of
	 * insufficient resources. Retry the operation a couple of
	 * बार beक्रमe giving up.
	 */
	जबतक (retries < 100) अणु
		ret = hv_post_message(conn_id, 1, buffer, buflen);

		चयन (ret) अणु
		हाल HV_STATUS_INVALID_CONNECTION_ID:
			/*
			 * See vmbus_negotiate_version(): VMBus protocol 5.0
			 * and higher require that we must use
			 * VMBUS_MESSAGE_CONNECTION_ID_4 क्रम the Initiate
			 * Contact message, but on old hosts that only
			 * support VMBus protocol 4.0 or lower, here we get
			 * HV_STATUS_INVALID_CONNECTION_ID and we should
			 * वापस an error immediately without retrying.
			 */
			hdr = buffer;
			अगर (hdr->msgtype == CHANNELMSG_INITIATE_CONTACT)
				वापस -EINVAL;
			/*
			 * We could get this अगर we send messages too
			 * frequently.
			 */
			ret = -EAGAIN;
			अवरोध;
		हाल HV_STATUS_INSUFFICIENT_MEMORY:
		हाल HV_STATUS_INSUFFICIENT_BUFFERS:
			ret = -ENOBUFS;
			अवरोध;
		हाल HV_STATUS_SUCCESS:
			वापस ret;
		शेष:
			pr_err("hv_post_msg() failed; error code:%d\n", ret);
			वापस -EINVAL;
		पूर्ण

		retries++;
		अगर (can_sleep && usec > 1000)
			msleep(usec / 1000);
		अन्यथा अगर (usec < MAX_UDELAY_MS * 1000)
			udelay(usec);
		अन्यथा
			mdelay(usec / 1000);

		अगर (retries < 22)
			usec *= 2;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * vmbus_set_event - Send an event notअगरication to the parent
 */
व्योम vmbus_set_event(काष्ठा vmbus_channel *channel)
अणु
	u32 child_relid = channel->offermsg.child_relid;

	अगर (!channel->is_dedicated_पूर्णांकerrupt)
		vmbus_send_पूर्णांकerrupt(child_relid);

	++channel->sig_events;

	hv_करो_fast_hypercall8(HVCALL_SIGNAL_EVENT, channel->sig_event);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_set_event);
