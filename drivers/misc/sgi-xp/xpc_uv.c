<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2008-2009 Silicon Graphics, Inc.  All Rights Reserved.
 */

/*
 * Cross Partition Communication (XPC) uv-based functions.
 *
 *     Architecture specअगरic implementation of common functions.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/numa.h>
#समावेश <यंत्र/uv/uv_hub.h>
#अगर defined CONFIG_X86_64
#समावेश <यंत्र/uv/मूलप्रण.स>
#समावेश <यंत्र/uv/uv_irq.h>
#या_अगर defined CONFIG_IA64_SGI_UV
#समावेश <यंत्र/sn/पूर्णांकr.h>
#समावेश <यंत्र/sn/sn_sal.h>
#पूर्ण_अगर
#समावेश "../sgi-gru/gru.h"
#समावेश "../sgi-gru/grukservices.h"
#समावेश "xpc.h"

#अगर defined CONFIG_IA64_SGI_UV
काष्ठा uv_IO_APIC_route_entry अणु
	__u64	vector		:  8,
		delivery_mode	:  3,
		dest_mode	:  1,
		delivery_status	:  1,
		polarity	:  1,
		__reserved_1	:  1,
		trigger		:  1,
		mask		:  1,
		__reserved_2	: 15,
		dest		: 32;
पूर्ण;

#घोषणा sn_partition_id 0
#पूर्ण_अगर

अटल काष्ठा xpc_heartbeat_uv *xpc_heartbeat_uv;

#घोषणा XPC_ACTIVATE_MSG_SIZE_UV	(1 * GRU_CACHE_LINE_BYTES)
#घोषणा XPC_ACTIVATE_MQ_SIZE_UV		(4 * XP_MAX_NPARTITIONS_UV * \
					 XPC_ACTIVATE_MSG_SIZE_UV)
#घोषणा XPC_ACTIVATE_IRQ_NAME		"xpc_activate"

#घोषणा XPC_NOTIFY_MSG_SIZE_UV		(2 * GRU_CACHE_LINE_BYTES)
#घोषणा XPC_NOTIFY_MQ_SIZE_UV		(4 * XP_MAX_NPARTITIONS_UV * \
					 XPC_NOTIFY_MSG_SIZE_UV)
#घोषणा XPC_NOTIFY_IRQ_NAME		"xpc_notify"

अटल पूर्णांक xpc_mq_node = NUMA_NO_NODE;

अटल काष्ठा xpc_gru_mq_uv *xpc_activate_mq_uv;
अटल काष्ठा xpc_gru_mq_uv *xpc_notअगरy_mq_uv;

अटल पूर्णांक
xpc_setup_partitions_uv(व्योम)
अणु
	लघु partid;
	काष्ठा xpc_partition_uv *part_uv;

	क्रम (partid = 0; partid < XP_MAX_NPARTITIONS_UV; partid++) अणु
		part_uv = &xpc_partitions[partid].sn.uv;

		mutex_init(&part_uv->cached_activate_gru_mq_desc_mutex);
		spin_lock_init(&part_uv->flags_lock);
		part_uv->remote_act_state = XPC_P_AS_INACTIVE;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
xpc_tearकरोwn_partitions_uv(व्योम)
अणु
	लघु partid;
	काष्ठा xpc_partition_uv *part_uv;
	अचिन्हित दीर्घ irq_flags;

	क्रम (partid = 0; partid < XP_MAX_NPARTITIONS_UV; partid++) अणु
		part_uv = &xpc_partitions[partid].sn.uv;

		अगर (part_uv->cached_activate_gru_mq_desc != शून्य) अणु
			mutex_lock(&part_uv->cached_activate_gru_mq_desc_mutex);
			spin_lock_irqsave(&part_uv->flags_lock, irq_flags);
			part_uv->flags &= ~XPC_P_CACHED_ACTIVATE_GRU_MQ_DESC_UV;
			spin_unlock_irqrestore(&part_uv->flags_lock, irq_flags);
			kमुक्त(part_uv->cached_activate_gru_mq_desc);
			part_uv->cached_activate_gru_mq_desc = शून्य;
			mutex_unlock(&part_uv->
				     cached_activate_gru_mq_desc_mutex);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
xpc_get_gru_mq_irq_uv(काष्ठा xpc_gru_mq_uv *mq, पूर्णांक cpu, अक्षर *irq_name)
अणु
	पूर्णांक mmr_pnode = uv_blade_to_pnode(mq->mmr_blade);

#अगर defined CONFIG_X86_64
	mq->irq = uv_setup_irq(irq_name, cpu, mq->mmr_blade, mq->mmr_offset,
			UV_AFFINITY_CPU);
	अगर (mq->irq < 0)
		वापस mq->irq;

	mq->mmr_value = uv_पढ़ो_global_mmr64(mmr_pnode, mq->mmr_offset);

#या_अगर defined CONFIG_IA64_SGI_UV
	अगर (म_भेद(irq_name, XPC_ACTIVATE_IRQ_NAME) == 0)
		mq->irq = SGI_XPC_ACTIVATE;
	अन्यथा अगर (म_भेद(irq_name, XPC_NOTIFY_IRQ_NAME) == 0)
		mq->irq = SGI_XPC_NOTIFY;
	अन्यथा
		वापस -EINVAL;

	mq->mmr_value = (अचिन्हित दीर्घ)cpu_physical_id(cpu) << 32 | mq->irq;
	uv_ग_लिखो_global_mmr64(mmr_pnode, mq->mmr_offset, mq->mmr_value);
#अन्यथा
	#त्रुटि not a supported configuration
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम
xpc_release_gru_mq_irq_uv(काष्ठा xpc_gru_mq_uv *mq)
अणु
#अगर defined CONFIG_X86_64
	uv_tearकरोwn_irq(mq->irq);

#या_अगर defined CONFIG_IA64_SGI_UV
	पूर्णांक mmr_pnode;
	अचिन्हित दीर्घ mmr_value;

	mmr_pnode = uv_blade_to_pnode(mq->mmr_blade);
	mmr_value = 1UL << 16;

	uv_ग_लिखो_global_mmr64(mmr_pnode, mq->mmr_offset, mmr_value);
#अन्यथा
	#त्रुटि not a supported configuration
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
xpc_gru_mq_watchlist_alloc_uv(काष्ठा xpc_gru_mq_uv *mq)
अणु
	पूर्णांक ret;

#अगर defined CONFIG_IA64_SGI_UV
	पूर्णांक mmr_pnode = uv_blade_to_pnode(mq->mmr_blade);

	ret = sn_mq_watchlist_alloc(mmr_pnode, (व्योम *)uv_gpa(mq->address),
				    mq->order, &mq->mmr_offset);
	अगर (ret < 0) अणु
		dev_err(xpc_part, "sn_mq_watchlist_alloc() failed, ret=%d\n",
			ret);
		वापस -EBUSY;
	पूर्ण
#या_अगर defined CONFIG_X86_64
	ret = uv_bios_mq_watchlist_alloc(uv_gpa(mq->address),
					 mq->order, &mq->mmr_offset);
	अगर (ret < 0) अणु
		dev_err(xpc_part, "uv_bios_mq_watchlist_alloc() failed, "
			"ret=%d\n", ret);
		वापस ret;
	पूर्ण
#अन्यथा
	#त्रुटि not a supported configuration
#पूर्ण_अगर

	mq->watchlist_num = ret;
	वापस 0;
पूर्ण

अटल व्योम
xpc_gru_mq_watchlist_मुक्त_uv(काष्ठा xpc_gru_mq_uv *mq)
अणु
	पूर्णांक ret;
	पूर्णांक mmr_pnode = uv_blade_to_pnode(mq->mmr_blade);

#अगर defined CONFIG_X86_64
	ret = uv_bios_mq_watchlist_मुक्त(mmr_pnode, mq->watchlist_num);
	BUG_ON(ret != BIOS_STATUS_SUCCESS);
#या_अगर defined CONFIG_IA64_SGI_UV
	ret = sn_mq_watchlist_मुक्त(mmr_pnode, mq->watchlist_num);
	BUG_ON(ret != SALRET_OK);
#अन्यथा
	#त्रुटि not a supported configuration
#पूर्ण_अगर
पूर्ण

अटल काष्ठा xpc_gru_mq_uv *
xpc_create_gru_mq_uv(अचिन्हित पूर्णांक mq_size, पूर्णांक cpu, अक्षर *irq_name,
		     irq_handler_t irq_handler)
अणु
	क्रमागत xp_retval xp_ret;
	पूर्णांक ret;
	पूर्णांक nid;
	पूर्णांक nasid;
	पूर्णांक pg_order;
	काष्ठा page *page;
	काष्ठा xpc_gru_mq_uv *mq;
	काष्ठा uv_IO_APIC_route_entry *mmr_value;

	mq = kदो_स्मृति(माप(काष्ठा xpc_gru_mq_uv), GFP_KERNEL);
	अगर (mq == शून्य) अणु
		dev_err(xpc_part, "xpc_create_gru_mq_uv() failed to kmalloc() "
			"a xpc_gru_mq_uv structure\n");
		ret = -ENOMEM;
		जाओ out_0;
	पूर्ण

	mq->gru_mq_desc = kzalloc(माप(काष्ठा gru_message_queue_desc),
				  GFP_KERNEL);
	अगर (mq->gru_mq_desc == शून्य) अणु
		dev_err(xpc_part, "xpc_create_gru_mq_uv() failed to kmalloc() "
			"a gru_message_queue_desc structure\n");
		ret = -ENOMEM;
		जाओ out_1;
	पूर्ण

	pg_order = get_order(mq_size);
	mq->order = pg_order + PAGE_SHIFT;
	mq_size = 1UL << mq->order;

	mq->mmr_blade = uv_cpu_to_blade_id(cpu);

	nid = cpu_to_node(cpu);
	page = __alloc_pages_node(nid,
				      GFP_KERNEL | __GFP_ZERO | __GFP_THISNODE,
				      pg_order);
	अगर (page == शून्य) अणु
		dev_err(xpc_part, "xpc_create_gru_mq_uv() failed to alloc %d "
			"bytes of memory on nid=%d for GRU mq\n", mq_size, nid);
		ret = -ENOMEM;
		जाओ out_2;
	पूर्ण
	mq->address = page_address(page);

	/* enable generation of irq when GRU mq operation occurs to this mq */
	ret = xpc_gru_mq_watchlist_alloc_uv(mq);
	अगर (ret != 0)
		जाओ out_3;

	ret = xpc_get_gru_mq_irq_uv(mq, cpu, irq_name);
	अगर (ret != 0)
		जाओ out_4;

	ret = request_irq(mq->irq, irq_handler, 0, irq_name, शून्य);
	अगर (ret != 0) अणु
		dev_err(xpc_part, "request_irq(irq=%d) returned error=%d\n",
			mq->irq, -ret);
		जाओ out_5;
	पूर्ण

	nasid = UV_PNODE_TO_NASID(uv_cpu_to_pnode(cpu));

	mmr_value = (काष्ठा uv_IO_APIC_route_entry *)&mq->mmr_value;
	ret = gru_create_message_queue(mq->gru_mq_desc, mq->address, mq_size,
				     nasid, mmr_value->vector, mmr_value->dest);
	अगर (ret != 0) अणु
		dev_err(xpc_part, "gru_create_message_queue() returned "
			"error=%d\n", ret);
		ret = -EINVAL;
		जाओ out_6;
	पूर्ण

	/* allow other partitions to access this GRU mq */
	xp_ret = xp_expand_memprotect(xp_pa(mq->address), mq_size);
	अगर (xp_ret != xpSuccess) अणु
		ret = -EACCES;
		जाओ out_6;
	पूर्ण

	वापस mq;

	/* something went wrong */
out_6:
	मुक्त_irq(mq->irq, शून्य);
out_5:
	xpc_release_gru_mq_irq_uv(mq);
out_4:
	xpc_gru_mq_watchlist_मुक्त_uv(mq);
out_3:
	मुक्त_pages((अचिन्हित दीर्घ)mq->address, pg_order);
out_2:
	kमुक्त(mq->gru_mq_desc);
out_1:
	kमुक्त(mq);
out_0:
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम
xpc_destroy_gru_mq_uv(काष्ठा xpc_gru_mq_uv *mq)
अणु
	अचिन्हित पूर्णांक mq_size;
	पूर्णांक pg_order;
	पूर्णांक ret;

	/* disallow other partitions to access GRU mq */
	mq_size = 1UL << mq->order;
	ret = xp_restrict_memprotect(xp_pa(mq->address), mq_size);
	BUG_ON(ret != xpSuccess);

	/* unरेजिस्टर irq handler and release mq irq/vector mapping */
	मुक्त_irq(mq->irq, शून्य);
	xpc_release_gru_mq_irq_uv(mq);

	/* disable generation of irq when GRU mq op occurs to this mq */
	xpc_gru_mq_watchlist_मुक्त_uv(mq);

	pg_order = mq->order - PAGE_SHIFT;
	मुक्त_pages((अचिन्हित दीर्घ)mq->address, pg_order);

	kमुक्त(mq);
पूर्ण

अटल क्रमागत xp_retval
xpc_send_gru_msg(काष्ठा gru_message_queue_desc *gru_mq_desc, व्योम *msg,
		 माप_प्रकार msg_size)
अणु
	क्रमागत xp_retval xp_ret;
	पूर्णांक ret;

	जबतक (1) अणु
		ret = gru_send_message_gpa(gru_mq_desc, msg, msg_size);
		अगर (ret == MQE_OK) अणु
			xp_ret = xpSuccess;
			अवरोध;
		पूर्ण

		अगर (ret == MQE_QUEUE_FULL) अणु
			dev_dbg(xpc_chan, "gru_send_message_gpa() returned "
				"error=MQE_QUEUE_FULL\n");
			/* !!! handle QLimit reached; delay & try again */
			/* ??? Do we add a limit to the number of retries? */
			(व्योम)msleep_पूर्णांकerruptible(10);
		पूर्ण अन्यथा अगर (ret == MQE_CONGESTION) अणु
			dev_dbg(xpc_chan, "gru_send_message_gpa() returned "
				"error=MQE_CONGESTION\n");
			/* !!! handle LB Overflow; simply try again */
			/* ??? Do we add a limit to the number of retries? */
		पूर्ण अन्यथा अणु
			/* !!! Currently this is MQE_UNEXPECTED_CB_ERR */
			dev_err(xpc_chan, "gru_send_message_gpa() returned "
				"error=%d\n", ret);
			xp_ret = xpGruSendMqError;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस xp_ret;
पूर्ण

अटल व्योम
xpc_process_activate_IRQ_rcvd_uv(व्योम)
अणु
	अचिन्हित दीर्घ irq_flags;
	लघु partid;
	काष्ठा xpc_partition *part;
	u8 act_state_req;

	DBUG_ON(xpc_activate_IRQ_rcvd == 0);

	spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
	क्रम (partid = 0; partid < XP_MAX_NPARTITIONS_UV; partid++) अणु
		part = &xpc_partitions[partid];

		अगर (part->sn.uv.act_state_req == 0)
			जारी;

		xpc_activate_IRQ_rcvd--;
		BUG_ON(xpc_activate_IRQ_rcvd < 0);

		act_state_req = part->sn.uv.act_state_req;
		part->sn.uv.act_state_req = 0;
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		अगर (act_state_req == XPC_P_ASR_ACTIVATE_UV) अणु
			अगर (part->act_state == XPC_P_AS_INACTIVE)
				xpc_activate_partition(part);
			अन्यथा अगर (part->act_state == XPC_P_AS_DEACTIVATING)
				XPC_DEACTIVATE_PARTITION(part, xpReactivating);

		पूर्ण अन्यथा अगर (act_state_req == XPC_P_ASR_REACTIVATE_UV) अणु
			अगर (part->act_state == XPC_P_AS_INACTIVE)
				xpc_activate_partition(part);
			अन्यथा
				XPC_DEACTIVATE_PARTITION(part, xpReactivating);

		पूर्ण अन्यथा अगर (act_state_req == XPC_P_ASR_DEACTIVATE_UV) अणु
			XPC_DEACTIVATE_PARTITION(part, part->sn.uv.reason);

		पूर्ण अन्यथा अणु
			BUG();
		पूर्ण

		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		अगर (xpc_activate_IRQ_rcvd == 0)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

पूर्ण

अटल व्योम
xpc_handle_activate_mq_msg_uv(काष्ठा xpc_partition *part,
			      काष्ठा xpc_activate_mq_msghdr_uv *msg_hdr,
			      पूर्णांक part_setup,
			      पूर्णांक *wakeup_hb_checker)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा xpc_partition_uv *part_uv = &part->sn.uv;
	काष्ठा xpc_खोलोबंद_args *args;

	part_uv->remote_act_state = msg_hdr->act_state;

	चयन (msg_hdr->type) अणु
	हाल XPC_ACTIVATE_MQ_MSG_SYNC_ACT_STATE_UV:
		/* syncing of remote_act_state was just करोne above */
		अवरोध;

	हाल XPC_ACTIVATE_MQ_MSG_ACTIVATE_REQ_UV: अणु
		काष्ठा xpc_activate_mq_msg_activate_req_uv *msg;

		/*
		 * ??? Do we deal here with ts_jअगरfies being dअगरferent
		 * ??? अगर act_state != XPC_P_AS_INACTIVE instead of
		 * ??? below?
		 */
		msg = container_of(msg_hdr, काष्ठा
				   xpc_activate_mq_msg_activate_req_uv, hdr);

		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		अगर (part_uv->act_state_req == 0)
			xpc_activate_IRQ_rcvd++;
		part_uv->act_state_req = XPC_P_ASR_ACTIVATE_UV;
		part->remote_rp_pa = msg->rp_gpa; /* !!! _pa is _gpa */
		part->remote_rp_ts_jअगरfies = msg_hdr->rp_ts_jअगरfies;
		part_uv->heartbeat_gpa = msg->heartbeat_gpa;

		अगर (msg->activate_gru_mq_desc_gpa !=
		    part_uv->activate_gru_mq_desc_gpa) अणु
			spin_lock(&part_uv->flags_lock);
			part_uv->flags &= ~XPC_P_CACHED_ACTIVATE_GRU_MQ_DESC_UV;
			spin_unlock(&part_uv->flags_lock);
			part_uv->activate_gru_mq_desc_gpa =
			    msg->activate_gru_mq_desc_gpa;
		पूर्ण
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		(*wakeup_hb_checker)++;
		अवरोध;
	पूर्ण
	हाल XPC_ACTIVATE_MQ_MSG_DEACTIVATE_REQ_UV: अणु
		काष्ठा xpc_activate_mq_msg_deactivate_req_uv *msg;

		msg = container_of(msg_hdr, काष्ठा
				   xpc_activate_mq_msg_deactivate_req_uv, hdr);

		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		अगर (part_uv->act_state_req == 0)
			xpc_activate_IRQ_rcvd++;
		part_uv->act_state_req = XPC_P_ASR_DEACTIVATE_UV;
		part_uv->reason = msg->reason;
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		(*wakeup_hb_checker)++;
		वापस;
	पूर्ण
	हाल XPC_ACTIVATE_MQ_MSG_CHCTL_CLOSEREQUEST_UV: अणु
		काष्ठा xpc_activate_mq_msg_chctl_बंदrequest_uv *msg;

		अगर (!part_setup)
			अवरोध;

		msg = container_of(msg_hdr, काष्ठा
				   xpc_activate_mq_msg_chctl_बंदrequest_uv,
				   hdr);
		args = &part->remote_खोलोबंद_args[msg->ch_number];
		args->reason = msg->reason;

		spin_lock_irqsave(&part->chctl_lock, irq_flags);
		part->chctl.flags[msg->ch_number] |= XPC_CHCTL_CLOSEREQUEST;
		spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

		xpc_wakeup_channel_mgr(part);
		अवरोध;
	पूर्ण
	हाल XPC_ACTIVATE_MQ_MSG_CHCTL_CLOSEREPLY_UV: अणु
		काष्ठा xpc_activate_mq_msg_chctl_बंदreply_uv *msg;

		अगर (!part_setup)
			अवरोध;

		msg = container_of(msg_hdr, काष्ठा
				   xpc_activate_mq_msg_chctl_बंदreply_uv,
				   hdr);

		spin_lock_irqsave(&part->chctl_lock, irq_flags);
		part->chctl.flags[msg->ch_number] |= XPC_CHCTL_CLOSEREPLY;
		spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

		xpc_wakeup_channel_mgr(part);
		अवरोध;
	पूर्ण
	हाल XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREQUEST_UV: अणु
		काष्ठा xpc_activate_mq_msg_chctl_खोलोrequest_uv *msg;

		अगर (!part_setup)
			अवरोध;

		msg = container_of(msg_hdr, काष्ठा
				   xpc_activate_mq_msg_chctl_खोलोrequest_uv,
				   hdr);
		args = &part->remote_खोलोबंद_args[msg->ch_number];
		args->entry_size = msg->entry_size;
		args->local_nentries = msg->local_nentries;

		spin_lock_irqsave(&part->chctl_lock, irq_flags);
		part->chctl.flags[msg->ch_number] |= XPC_CHCTL_OPENREQUEST;
		spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

		xpc_wakeup_channel_mgr(part);
		अवरोध;
	पूर्ण
	हाल XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREPLY_UV: अणु
		काष्ठा xpc_activate_mq_msg_chctl_खोलोreply_uv *msg;

		अगर (!part_setup)
			अवरोध;

		msg = container_of(msg_hdr, काष्ठा
				   xpc_activate_mq_msg_chctl_खोलोreply_uv, hdr);
		args = &part->remote_खोलोबंद_args[msg->ch_number];
		args->remote_nentries = msg->remote_nentries;
		args->local_nentries = msg->local_nentries;
		args->local_msgqueue_pa = msg->notअगरy_gru_mq_desc_gpa;

		spin_lock_irqsave(&part->chctl_lock, irq_flags);
		part->chctl.flags[msg->ch_number] |= XPC_CHCTL_OPENREPLY;
		spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

		xpc_wakeup_channel_mgr(part);
		अवरोध;
	पूर्ण
	हाल XPC_ACTIVATE_MQ_MSG_CHCTL_OPENCOMPLETE_UV: अणु
		काष्ठा xpc_activate_mq_msg_chctl_खोलोcomplete_uv *msg;

		अगर (!part_setup)
			अवरोध;

		msg = container_of(msg_hdr, काष्ठा
				xpc_activate_mq_msg_chctl_खोलोcomplete_uv, hdr);
		spin_lock_irqsave(&part->chctl_lock, irq_flags);
		part->chctl.flags[msg->ch_number] |= XPC_CHCTL_OPENCOMPLETE;
		spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

		xpc_wakeup_channel_mgr(part);
	पूर्ण
		fallthrough;
	हाल XPC_ACTIVATE_MQ_MSG_MARK_ENGAGED_UV:
		spin_lock_irqsave(&part_uv->flags_lock, irq_flags);
		part_uv->flags |= XPC_P_ENGAGED_UV;
		spin_unlock_irqrestore(&part_uv->flags_lock, irq_flags);
		अवरोध;

	हाल XPC_ACTIVATE_MQ_MSG_MARK_DISENGAGED_UV:
		spin_lock_irqsave(&part_uv->flags_lock, irq_flags);
		part_uv->flags &= ~XPC_P_ENGAGED_UV;
		spin_unlock_irqrestore(&part_uv->flags_lock, irq_flags);
		अवरोध;

	शेष:
		dev_err(xpc_part, "received unknown activate_mq msg type=%d "
			"from partition=%d\n", msg_hdr->type, XPC_PARTID(part));

		/* get hb checker to deactivate from the remote partition */
		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		अगर (part_uv->act_state_req == 0)
			xpc_activate_IRQ_rcvd++;
		part_uv->act_state_req = XPC_P_ASR_DEACTIVATE_UV;
		part_uv->reason = xpBadMsgType;
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		(*wakeup_hb_checker)++;
		वापस;
	पूर्ण

	अगर (msg_hdr->rp_ts_jअगरfies != part->remote_rp_ts_jअगरfies &&
	    part->remote_rp_ts_jअगरfies != 0) अणु
		/*
		 * ??? Does what we करो here need to be sensitive to
		 * ??? act_state or remote_act_state?
		 */
		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		अगर (part_uv->act_state_req == 0)
			xpc_activate_IRQ_rcvd++;
		part_uv->act_state_req = XPC_P_ASR_REACTIVATE_UV;
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		(*wakeup_hb_checker)++;
	पूर्ण
पूर्ण

अटल irqवापस_t
xpc_handle_activate_IRQ_uv(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xpc_activate_mq_msghdr_uv *msg_hdr;
	लघु partid;
	काष्ठा xpc_partition *part;
	पूर्णांक wakeup_hb_checker = 0;
	पूर्णांक part_referenced;

	जबतक (1) अणु
		msg_hdr = gru_get_next_message(xpc_activate_mq_uv->gru_mq_desc);
		अगर (msg_hdr == शून्य)
			अवरोध;

		partid = msg_hdr->partid;
		अगर (partid < 0 || partid >= XP_MAX_NPARTITIONS_UV) अणु
			dev_err(xpc_part, "xpc_handle_activate_IRQ_uv() "
				"received invalid partid=0x%x in message\n",
				partid);
		पूर्ण अन्यथा अणु
			part = &xpc_partitions[partid];

			part_referenced = xpc_part_ref(part);
			xpc_handle_activate_mq_msg_uv(part, msg_hdr,
						      part_referenced,
						      &wakeup_hb_checker);
			अगर (part_referenced)
				xpc_part_deref(part);
		पूर्ण

		gru_मुक्त_message(xpc_activate_mq_uv->gru_mq_desc, msg_hdr);
	पूर्ण

	अगर (wakeup_hb_checker)
		wake_up_पूर्णांकerruptible(&xpc_activate_IRQ_wq);

	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत xp_retval
xpc_cache_remote_gru_mq_desc_uv(काष्ठा gru_message_queue_desc *gru_mq_desc,
				अचिन्हित दीर्घ gru_mq_desc_gpa)
अणु
	क्रमागत xp_retval ret;

	ret = xp_remote_स_नकल(uv_gpa(gru_mq_desc), gru_mq_desc_gpa,
			       माप(काष्ठा gru_message_queue_desc));
	अगर (ret == xpSuccess)
		gru_mq_desc->mq = शून्य;

	वापस ret;
पूर्ण

अटल क्रमागत xp_retval
xpc_send_activate_IRQ_uv(काष्ठा xpc_partition *part, व्योम *msg, माप_प्रकार msg_size,
			 पूर्णांक msg_type)
अणु
	काष्ठा xpc_activate_mq_msghdr_uv *msg_hdr = msg;
	काष्ठा xpc_partition_uv *part_uv = &part->sn.uv;
	काष्ठा gru_message_queue_desc *gru_mq_desc;
	अचिन्हित दीर्घ irq_flags;
	क्रमागत xp_retval ret;

	DBUG_ON(msg_size > XPC_ACTIVATE_MSG_SIZE_UV);

	msg_hdr->type = msg_type;
	msg_hdr->partid = xp_partition_id;
	msg_hdr->act_state = part->act_state;
	msg_hdr->rp_ts_jअगरfies = xpc_rsvd_page->ts_jअगरfies;

	mutex_lock(&part_uv->cached_activate_gru_mq_desc_mutex);
again:
	अगर (!(part_uv->flags & XPC_P_CACHED_ACTIVATE_GRU_MQ_DESC_UV)) अणु
		gru_mq_desc = part_uv->cached_activate_gru_mq_desc;
		अगर (gru_mq_desc == शून्य) अणु
			gru_mq_desc = kदो_स्मृति(माप(काष्ठा
					      gru_message_queue_desc),
					      GFP_ATOMIC);
			अगर (gru_mq_desc == शून्य) अणु
				ret = xpNoMemory;
				जाओ करोne;
			पूर्ण
			part_uv->cached_activate_gru_mq_desc = gru_mq_desc;
		पूर्ण

		ret = xpc_cache_remote_gru_mq_desc_uv(gru_mq_desc,
						      part_uv->
						      activate_gru_mq_desc_gpa);
		अगर (ret != xpSuccess)
			जाओ करोne;

		spin_lock_irqsave(&part_uv->flags_lock, irq_flags);
		part_uv->flags |= XPC_P_CACHED_ACTIVATE_GRU_MQ_DESC_UV;
		spin_unlock_irqrestore(&part_uv->flags_lock, irq_flags);
	पूर्ण

	/* ??? Is holding a spin_lock (ch->lock) during this call a bad idea? */
	ret = xpc_send_gru_msg(part_uv->cached_activate_gru_mq_desc, msg,
			       msg_size);
	अगर (ret != xpSuccess) अणु
		smp_rmb();	/* ensure a fresh copy of part_uv->flags */
		अगर (!(part_uv->flags & XPC_P_CACHED_ACTIVATE_GRU_MQ_DESC_UV))
			जाओ again;
	पूर्ण
करोne:
	mutex_unlock(&part_uv->cached_activate_gru_mq_desc_mutex);
	वापस ret;
पूर्ण

अटल व्योम
xpc_send_activate_IRQ_part_uv(काष्ठा xpc_partition *part, व्योम *msg,
			      माप_प्रकार msg_size, पूर्णांक msg_type)
अणु
	क्रमागत xp_retval ret;

	ret = xpc_send_activate_IRQ_uv(part, msg, msg_size, msg_type);
	अगर (unlikely(ret != xpSuccess))
		XPC_DEACTIVATE_PARTITION(part, ret);
पूर्ण

अटल व्योम
xpc_send_activate_IRQ_ch_uv(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags,
			 व्योम *msg, माप_प्रकार msg_size, पूर्णांक msg_type)
अणु
	काष्ठा xpc_partition *part = &xpc_partitions[ch->partid];
	क्रमागत xp_retval ret;

	ret = xpc_send_activate_IRQ_uv(part, msg, msg_size, msg_type);
	अगर (unlikely(ret != xpSuccess)) अणु
		अगर (irq_flags != शून्य)
			spin_unlock_irqrestore(&ch->lock, *irq_flags);

		XPC_DEACTIVATE_PARTITION(part, ret);

		अगर (irq_flags != शून्य)
			spin_lock_irqsave(&ch->lock, *irq_flags);
	पूर्ण
पूर्ण

अटल व्योम
xpc_send_local_activate_IRQ_uv(काष्ठा xpc_partition *part, पूर्णांक act_state_req)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा xpc_partition_uv *part_uv = &part->sn.uv;

	/*
	 * !!! Make our side think that the remote partition sent an activate
	 * !!! mq message our way by करोing what the activate IRQ handler would
	 * !!! करो had one really been sent.
	 */

	spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
	अगर (part_uv->act_state_req == 0)
		xpc_activate_IRQ_rcvd++;
	part_uv->act_state_req = act_state_req;
	spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

	wake_up_पूर्णांकerruptible(&xpc_activate_IRQ_wq);
पूर्ण

अटल क्रमागत xp_retval
xpc_get_partition_rsvd_page_pa_uv(व्योम *buf, u64 *cookie, अचिन्हित दीर्घ *rp_pa,
				  माप_प्रकार *len)
अणु
	s64 status;
	क्रमागत xp_retval ret;

#अगर defined CONFIG_X86_64
	status = uv_bios_reserved_page_pa((u64)buf, cookie, (u64 *)rp_pa,
					  (u64 *)len);
	अगर (status == BIOS_STATUS_SUCCESS)
		ret = xpSuccess;
	अन्यथा अगर (status == BIOS_STATUS_MORE_PASSES)
		ret = xpNeedMoreInfo;
	अन्यथा
		ret = xpBiosError;

#या_अगर defined CONFIG_IA64_SGI_UV
	status = sn_partition_reserved_page_pa((u64)buf, cookie, rp_pa, len);
	अगर (status == SALRET_OK)
		ret = xpSuccess;
	अन्यथा अगर (status == SALRET_MORE_PASSES)
		ret = xpNeedMoreInfo;
	अन्यथा
		ret = xpSalError;

#अन्यथा
	#त्रुटि not a supported configuration
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक
xpc_setup_rsvd_page_uv(काष्ठा xpc_rsvd_page *rp)
अणु
	xpc_heartbeat_uv =
	    &xpc_partitions[sn_partition_id].sn.uv.cached_heartbeat;
	rp->sn.uv.heartbeat_gpa = uv_gpa(xpc_heartbeat_uv);
	rp->sn.uv.activate_gru_mq_desc_gpa =
	    uv_gpa(xpc_activate_mq_uv->gru_mq_desc);
	वापस 0;
पूर्ण

अटल व्योम
xpc_allow_hb_uv(लघु partid)
अणु
पूर्ण

अटल व्योम
xpc_disallow_hb_uv(लघु partid)
अणु
पूर्ण

अटल व्योम
xpc_disallow_all_hbs_uv(व्योम)
अणु
पूर्ण

अटल व्योम
xpc_increment_heartbeat_uv(व्योम)
अणु
	xpc_heartbeat_uv->value++;
पूर्ण

अटल व्योम
xpc_offline_heartbeat_uv(व्योम)
अणु
	xpc_increment_heartbeat_uv();
	xpc_heartbeat_uv->offline = 1;
पूर्ण

अटल व्योम
xpc_online_heartbeat_uv(व्योम)
अणु
	xpc_increment_heartbeat_uv();
	xpc_heartbeat_uv->offline = 0;
पूर्ण

अटल व्योम
xpc_heartbeat_init_uv(व्योम)
अणु
	xpc_heartbeat_uv->value = 1;
	xpc_heartbeat_uv->offline = 0;
पूर्ण

अटल व्योम
xpc_heartbeat_निकास_uv(व्योम)
अणु
	xpc_offline_heartbeat_uv();
पूर्ण

अटल क्रमागत xp_retval
xpc_get_remote_heartbeat_uv(काष्ठा xpc_partition *part)
अणु
	काष्ठा xpc_partition_uv *part_uv = &part->sn.uv;
	क्रमागत xp_retval ret;

	ret = xp_remote_स_नकल(uv_gpa(&part_uv->cached_heartbeat),
			       part_uv->heartbeat_gpa,
			       माप(काष्ठा xpc_heartbeat_uv));
	अगर (ret != xpSuccess)
		वापस ret;

	अगर (part_uv->cached_heartbeat.value == part->last_heartbeat &&
	    !part_uv->cached_heartbeat.offline) अणु

		ret = xpNoHeartbeat;
	पूर्ण अन्यथा अणु
		part->last_heartbeat = part_uv->cached_heartbeat.value;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
xpc_request_partition_activation_uv(काष्ठा xpc_rsvd_page *remote_rp,
				    अचिन्हित दीर्घ remote_rp_gpa, पूर्णांक nasid)
अणु
	लघु partid = remote_rp->SAL_partid;
	काष्ठा xpc_partition *part = &xpc_partitions[partid];
	काष्ठा xpc_activate_mq_msg_activate_req_uv msg;

	part->remote_rp_pa = remote_rp_gpa; /* !!! _pa here is really _gpa */
	part->remote_rp_ts_jअगरfies = remote_rp->ts_jअगरfies;
	part->sn.uv.heartbeat_gpa = remote_rp->sn.uv.heartbeat_gpa;
	part->sn.uv.activate_gru_mq_desc_gpa =
	    remote_rp->sn.uv.activate_gru_mq_desc_gpa;

	/*
	 * ??? Is it a good idea to make this conditional on what is
	 * ??? potentially stale state inक्रमmation?
	 */
	अगर (part->sn.uv.remote_act_state == XPC_P_AS_INACTIVE) अणु
		msg.rp_gpa = uv_gpa(xpc_rsvd_page);
		msg.heartbeat_gpa = xpc_rsvd_page->sn.uv.heartbeat_gpa;
		msg.activate_gru_mq_desc_gpa =
		    xpc_rsvd_page->sn.uv.activate_gru_mq_desc_gpa;
		xpc_send_activate_IRQ_part_uv(part, &msg, माप(msg),
					   XPC_ACTIVATE_MQ_MSG_ACTIVATE_REQ_UV);
	पूर्ण

	अगर (part->act_state == XPC_P_AS_INACTIVE)
		xpc_send_local_activate_IRQ_uv(part, XPC_P_ASR_ACTIVATE_UV);
पूर्ण

अटल व्योम
xpc_request_partition_reactivation_uv(काष्ठा xpc_partition *part)
अणु
	xpc_send_local_activate_IRQ_uv(part, XPC_P_ASR_ACTIVATE_UV);
पूर्ण

अटल व्योम
xpc_request_partition_deactivation_uv(काष्ठा xpc_partition *part)
अणु
	काष्ठा xpc_activate_mq_msg_deactivate_req_uv msg;

	/*
	 * ??? Is it a good idea to make this conditional on what is
	 * ??? potentially stale state inक्रमmation?
	 */
	अगर (part->sn.uv.remote_act_state != XPC_P_AS_DEACTIVATING &&
	    part->sn.uv.remote_act_state != XPC_P_AS_INACTIVE) अणु

		msg.reason = part->reason;
		xpc_send_activate_IRQ_part_uv(part, &msg, माप(msg),
					 XPC_ACTIVATE_MQ_MSG_DEACTIVATE_REQ_UV);
	पूर्ण
पूर्ण

अटल व्योम
xpc_cancel_partition_deactivation_request_uv(काष्ठा xpc_partition *part)
अणु
	/* nothing needs to be करोne */
	वापस;
पूर्ण

अटल व्योम
xpc_init_fअगरo_uv(काष्ठा xpc_fअगरo_head_uv *head)
अणु
	head->first = शून्य;
	head->last = शून्य;
	spin_lock_init(&head->lock);
	head->n_entries = 0;
पूर्ण

अटल व्योम *
xpc_get_fअगरo_entry_uv(काष्ठा xpc_fअगरo_head_uv *head)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा xpc_fअगरo_entry_uv *first;

	spin_lock_irqsave(&head->lock, irq_flags);
	first = head->first;
	अगर (head->first != शून्य) अणु
		head->first = first->next;
		अगर (head->first == शून्य)
			head->last = शून्य;

		head->n_entries--;
		BUG_ON(head->n_entries < 0);

		first->next = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&head->lock, irq_flags);
	वापस first;
पूर्ण

अटल व्योम
xpc_put_fअगरo_entry_uv(काष्ठा xpc_fअगरo_head_uv *head,
		      काष्ठा xpc_fअगरo_entry_uv *last)
अणु
	अचिन्हित दीर्घ irq_flags;

	last->next = शून्य;
	spin_lock_irqsave(&head->lock, irq_flags);
	अगर (head->last != शून्य)
		head->last->next = last;
	अन्यथा
		head->first = last;
	head->last = last;
	head->n_entries++;
	spin_unlock_irqrestore(&head->lock, irq_flags);
पूर्ण

अटल पूर्णांक
xpc_n_of_fअगरo_entries_uv(काष्ठा xpc_fअगरo_head_uv *head)
अणु
	वापस head->n_entries;
पूर्ण

/*
 * Setup the channel काष्ठाures that are uv specअगरic.
 */
अटल क्रमागत xp_retval
xpc_setup_ch_काष्ठाures_uv(काष्ठा xpc_partition *part)
अणु
	काष्ठा xpc_channel_uv *ch_uv;
	पूर्णांक ch_number;

	क्रम (ch_number = 0; ch_number < part->nchannels; ch_number++) अणु
		ch_uv = &part->channels[ch_number].sn.uv;

		xpc_init_fअगरo_uv(&ch_uv->msg_slot_मुक्त_list);
		xpc_init_fअगरo_uv(&ch_uv->recv_msg_list);
	पूर्ण

	वापस xpSuccess;
पूर्ण

/*
 * Tearकरोwn the channel काष्ठाures that are uv specअगरic.
 */
अटल व्योम
xpc_tearकरोwn_ch_काष्ठाures_uv(काष्ठा xpc_partition *part)
अणु
	/* nothing needs to be करोne */
	वापस;
पूर्ण

अटल क्रमागत xp_retval
xpc_make_first_contact_uv(काष्ठा xpc_partition *part)
अणु
	काष्ठा xpc_activate_mq_msg_uv msg;

	/*
	 * We send a sync msg to get the remote partition's remote_act_state
	 * updated to our current act_state which at this poपूर्णांक should
	 * be XPC_P_AS_ACTIVATING.
	 */
	xpc_send_activate_IRQ_part_uv(part, &msg, माप(msg),
				      XPC_ACTIVATE_MQ_MSG_SYNC_ACT_STATE_UV);

	जबतक (!((part->sn.uv.remote_act_state == XPC_P_AS_ACTIVATING) ||
		 (part->sn.uv.remote_act_state == XPC_P_AS_ACTIVE))) अणु

		dev_dbg(xpc_part, "waiting to make first contact with "
			"partition %d\n", XPC_PARTID(part));

		/* रुको a 1/4 of a second or so */
		(व्योम)msleep_पूर्णांकerruptible(250);

		अगर (part->act_state == XPC_P_AS_DEACTIVATING)
			वापस part->reason;
	पूर्ण

	वापस xpSuccess;
पूर्ण

अटल u64
xpc_get_chctl_all_flags_uv(काष्ठा xpc_partition *part)
अणु
	अचिन्हित दीर्घ irq_flags;
	जोड़ xpc_channel_ctl_flags chctl;

	spin_lock_irqsave(&part->chctl_lock, irq_flags);
	chctl = part->chctl;
	अगर (chctl.all_flags != 0)
		part->chctl.all_flags = 0;

	spin_unlock_irqrestore(&part->chctl_lock, irq_flags);
	वापस chctl.all_flags;
पूर्ण

अटल क्रमागत xp_retval
xpc_allocate_send_msg_slot_uv(काष्ठा xpc_channel *ch)
अणु
	काष्ठा xpc_channel_uv *ch_uv = &ch->sn.uv;
	काष्ठा xpc_send_msg_slot_uv *msg_slot;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक nentries;
	पूर्णांक entry;
	माप_प्रकार nbytes;

	क्रम (nentries = ch->local_nentries; nentries > 0; nentries--) अणु
		nbytes = nentries * माप(काष्ठा xpc_send_msg_slot_uv);
		ch_uv->send_msg_slots = kzalloc(nbytes, GFP_KERNEL);
		अगर (ch_uv->send_msg_slots == शून्य)
			जारी;

		क्रम (entry = 0; entry < nentries; entry++) अणु
			msg_slot = &ch_uv->send_msg_slots[entry];

			msg_slot->msg_slot_number = entry;
			xpc_put_fअगरo_entry_uv(&ch_uv->msg_slot_मुक्त_list,
					      &msg_slot->next);
		पूर्ण

		spin_lock_irqsave(&ch->lock, irq_flags);
		अगर (nentries < ch->local_nentries)
			ch->local_nentries = nentries;
		spin_unlock_irqrestore(&ch->lock, irq_flags);
		वापस xpSuccess;
	पूर्ण

	वापस xpNoMemory;
पूर्ण

अटल क्रमागत xp_retval
xpc_allocate_recv_msg_slot_uv(काष्ठा xpc_channel *ch)
अणु
	काष्ठा xpc_channel_uv *ch_uv = &ch->sn.uv;
	काष्ठा xpc_notअगरy_mq_msg_uv *msg_slot;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक nentries;
	पूर्णांक entry;
	माप_प्रकार nbytes;

	क्रम (nentries = ch->remote_nentries; nentries > 0; nentries--) अणु
		nbytes = nentries * ch->entry_size;
		ch_uv->recv_msg_slots = kzalloc(nbytes, GFP_KERNEL);
		अगर (ch_uv->recv_msg_slots == शून्य)
			जारी;

		क्रम (entry = 0; entry < nentries; entry++) अणु
			msg_slot = ch_uv->recv_msg_slots +
			    entry * ch->entry_size;

			msg_slot->hdr.msg_slot_number = entry;
		पूर्ण

		spin_lock_irqsave(&ch->lock, irq_flags);
		अगर (nentries < ch->remote_nentries)
			ch->remote_nentries = nentries;
		spin_unlock_irqrestore(&ch->lock, irq_flags);
		वापस xpSuccess;
	पूर्ण

	वापस xpNoMemory;
पूर्ण

/*
 * Allocate msg_slots associated with the channel.
 */
अटल क्रमागत xp_retval
xpc_setup_msg_काष्ठाures_uv(काष्ठा xpc_channel *ch)
अणु
	अटल क्रमागत xp_retval ret;
	काष्ठा xpc_channel_uv *ch_uv = &ch->sn.uv;

	DBUG_ON(ch->flags & XPC_C_SETUP);

	ch_uv->cached_notअगरy_gru_mq_desc = kदो_स्मृति(माप(काष्ठा
						   gru_message_queue_desc),
						   GFP_KERNEL);
	अगर (ch_uv->cached_notअगरy_gru_mq_desc == शून्य)
		वापस xpNoMemory;

	ret = xpc_allocate_send_msg_slot_uv(ch);
	अगर (ret == xpSuccess) अणु

		ret = xpc_allocate_recv_msg_slot_uv(ch);
		अगर (ret != xpSuccess) अणु
			kमुक्त(ch_uv->send_msg_slots);
			xpc_init_fअगरo_uv(&ch_uv->msg_slot_मुक्त_list);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Free up msg_slots and clear other stuff that were setup क्रम the specअगरied
 * channel.
 */
अटल व्योम
xpc_tearकरोwn_msg_काष्ठाures_uv(काष्ठा xpc_channel *ch)
अणु
	काष्ठा xpc_channel_uv *ch_uv = &ch->sn.uv;

	lockdep_निश्चित_held(&ch->lock);

	kमुक्त(ch_uv->cached_notअगरy_gru_mq_desc);
	ch_uv->cached_notअगरy_gru_mq_desc = शून्य;

	अगर (ch->flags & XPC_C_SETUP) अणु
		xpc_init_fअगरo_uv(&ch_uv->msg_slot_मुक्त_list);
		kमुक्त(ch_uv->send_msg_slots);
		xpc_init_fअगरo_uv(&ch_uv->recv_msg_list);
		kमुक्त(ch_uv->recv_msg_slots);
	पूर्ण
पूर्ण

अटल व्योम
xpc_send_chctl_बंदrequest_uv(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags)
अणु
	काष्ठा xpc_activate_mq_msg_chctl_बंदrequest_uv msg;

	msg.ch_number = ch->number;
	msg.reason = ch->reason;
	xpc_send_activate_IRQ_ch_uv(ch, irq_flags, &msg, माप(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTL_CLOSEREQUEST_UV);
पूर्ण

अटल व्योम
xpc_send_chctl_बंदreply_uv(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags)
अणु
	काष्ठा xpc_activate_mq_msg_chctl_बंदreply_uv msg;

	msg.ch_number = ch->number;
	xpc_send_activate_IRQ_ch_uv(ch, irq_flags, &msg, माप(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTL_CLOSEREPLY_UV);
पूर्ण

अटल व्योम
xpc_send_chctl_खोलोrequest_uv(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags)
अणु
	काष्ठा xpc_activate_mq_msg_chctl_खोलोrequest_uv msg;

	msg.ch_number = ch->number;
	msg.entry_size = ch->entry_size;
	msg.local_nentries = ch->local_nentries;
	xpc_send_activate_IRQ_ch_uv(ch, irq_flags, &msg, माप(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREQUEST_UV);
पूर्ण

अटल व्योम
xpc_send_chctl_खोलोreply_uv(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags)
अणु
	काष्ठा xpc_activate_mq_msg_chctl_खोलोreply_uv msg;

	msg.ch_number = ch->number;
	msg.local_nentries = ch->local_nentries;
	msg.remote_nentries = ch->remote_nentries;
	msg.notअगरy_gru_mq_desc_gpa = uv_gpa(xpc_notअगरy_mq_uv->gru_mq_desc);
	xpc_send_activate_IRQ_ch_uv(ch, irq_flags, &msg, माप(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREPLY_UV);
पूर्ण

अटल व्योम
xpc_send_chctl_खोलोcomplete_uv(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags)
अणु
	काष्ठा xpc_activate_mq_msg_chctl_खोलोcomplete_uv msg;

	msg.ch_number = ch->number;
	xpc_send_activate_IRQ_ch_uv(ch, irq_flags, &msg, माप(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTL_OPENCOMPLETE_UV);
पूर्ण

अटल व्योम
xpc_send_chctl_local_msgrequest_uv(काष्ठा xpc_partition *part, पूर्णांक ch_number)
अणु
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&part->chctl_lock, irq_flags);
	part->chctl.flags[ch_number] |= XPC_CHCTL_MSGREQUEST;
	spin_unlock_irqrestore(&part->chctl_lock, irq_flags);

	xpc_wakeup_channel_mgr(part);
पूर्ण

अटल क्रमागत xp_retval
xpc_save_remote_msgqueue_pa_uv(काष्ठा xpc_channel *ch,
			       अचिन्हित दीर्घ gru_mq_desc_gpa)
अणु
	काष्ठा xpc_channel_uv *ch_uv = &ch->sn.uv;

	DBUG_ON(ch_uv->cached_notअगरy_gru_mq_desc == शून्य);
	वापस xpc_cache_remote_gru_mq_desc_uv(ch_uv->cached_notअगरy_gru_mq_desc,
					       gru_mq_desc_gpa);
पूर्ण

अटल व्योम
xpc_indicate_partition_engaged_uv(काष्ठा xpc_partition *part)
अणु
	काष्ठा xpc_activate_mq_msg_uv msg;

	xpc_send_activate_IRQ_part_uv(part, &msg, माप(msg),
				      XPC_ACTIVATE_MQ_MSG_MARK_ENGAGED_UV);
पूर्ण

अटल व्योम
xpc_indicate_partition_disengaged_uv(काष्ठा xpc_partition *part)
अणु
	काष्ठा xpc_activate_mq_msg_uv msg;

	xpc_send_activate_IRQ_part_uv(part, &msg, माप(msg),
				      XPC_ACTIVATE_MQ_MSG_MARK_DISENGAGED_UV);
पूर्ण

अटल व्योम
xpc_assume_partition_disengaged_uv(लघु partid)
अणु
	काष्ठा xpc_partition_uv *part_uv = &xpc_partitions[partid].sn.uv;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&part_uv->flags_lock, irq_flags);
	part_uv->flags &= ~XPC_P_ENGAGED_UV;
	spin_unlock_irqrestore(&part_uv->flags_lock, irq_flags);
पूर्ण

अटल पूर्णांक
xpc_partition_engaged_uv(लघु partid)
अणु
	वापस (xpc_partitions[partid].sn.uv.flags & XPC_P_ENGAGED_UV) != 0;
पूर्ण

अटल पूर्णांक
xpc_any_partition_engaged_uv(व्योम)
अणु
	काष्ठा xpc_partition_uv *part_uv;
	लघु partid;

	क्रम (partid = 0; partid < XP_MAX_NPARTITIONS_UV; partid++) अणु
		part_uv = &xpc_partitions[partid].sn.uv;
		अगर ((part_uv->flags & XPC_P_ENGAGED_UV) != 0)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत xp_retval
xpc_allocate_msg_slot_uv(काष्ठा xpc_channel *ch, u32 flags,
			 काष्ठा xpc_send_msg_slot_uv **address_of_msg_slot)
अणु
	क्रमागत xp_retval ret;
	काष्ठा xpc_send_msg_slot_uv *msg_slot;
	काष्ठा xpc_fअगरo_entry_uv *entry;

	जबतक (1) अणु
		entry = xpc_get_fअगरo_entry_uv(&ch->sn.uv.msg_slot_मुक्त_list);
		अगर (entry != शून्य)
			अवरोध;

		अगर (flags & XPC_NOWAIT)
			वापस xpNoWait;

		ret = xpc_allocate_msg_रुको(ch);
		अगर (ret != xpInterrupted && ret != xpTimeout)
			वापस ret;
	पूर्ण

	msg_slot = container_of(entry, काष्ठा xpc_send_msg_slot_uv, next);
	*address_of_msg_slot = msg_slot;
	वापस xpSuccess;
पूर्ण

अटल व्योम
xpc_मुक्त_msg_slot_uv(काष्ठा xpc_channel *ch,
		     काष्ठा xpc_send_msg_slot_uv *msg_slot)
अणु
	xpc_put_fअगरo_entry_uv(&ch->sn.uv.msg_slot_मुक्त_list, &msg_slot->next);

	/* wakeup anyone रुकोing क्रम a मुक्त msg slot */
	अगर (atomic_पढ़ो(&ch->n_on_msg_allocate_wq) > 0)
		wake_up(&ch->msg_allocate_wq);
पूर्ण

अटल व्योम
xpc_notअगरy_sender_uv(काष्ठा xpc_channel *ch,
		     काष्ठा xpc_send_msg_slot_uv *msg_slot,
		     क्रमागत xp_retval reason)
अणु
	xpc_notअगरy_func func = msg_slot->func;

	अगर (func != शून्य && cmpxchg(&msg_slot->func, func, शून्य) == func) अणु

		atomic_dec(&ch->n_to_notअगरy);

		dev_dbg(xpc_chan, "msg_slot->func() called, msg_slot=0x%p "
			"msg_slot_number=%d partid=%d channel=%d\n", msg_slot,
			msg_slot->msg_slot_number, ch->partid, ch->number);

		func(reason, ch->partid, ch->number, msg_slot->key);

		dev_dbg(xpc_chan, "msg_slot->func() returned, msg_slot=0x%p "
			"msg_slot_number=%d partid=%d channel=%d\n", msg_slot,
			msg_slot->msg_slot_number, ch->partid, ch->number);
	पूर्ण
पूर्ण

अटल व्योम
xpc_handle_notअगरy_mq_ack_uv(काष्ठा xpc_channel *ch,
			    काष्ठा xpc_notअगरy_mq_msg_uv *msg)
अणु
	काष्ठा xpc_send_msg_slot_uv *msg_slot;
	पूर्णांक entry = msg->hdr.msg_slot_number % ch->local_nentries;

	msg_slot = &ch->sn.uv.send_msg_slots[entry];

	BUG_ON(msg_slot->msg_slot_number != msg->hdr.msg_slot_number);
	msg_slot->msg_slot_number += ch->local_nentries;

	अगर (msg_slot->func != शून्य)
		xpc_notअगरy_sender_uv(ch, msg_slot, xpMsgDelivered);

	xpc_मुक्त_msg_slot_uv(ch, msg_slot);
पूर्ण

अटल व्योम
xpc_handle_notअगरy_mq_msg_uv(काष्ठा xpc_partition *part,
			    काष्ठा xpc_notअगरy_mq_msg_uv *msg)
अणु
	काष्ठा xpc_partition_uv *part_uv = &part->sn.uv;
	काष्ठा xpc_channel *ch;
	काष्ठा xpc_channel_uv *ch_uv;
	काष्ठा xpc_notअगरy_mq_msg_uv *msg_slot;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ch_number = msg->hdr.ch_number;

	अगर (unlikely(ch_number >= part->nchannels)) अणु
		dev_err(xpc_part, "xpc_handle_notify_IRQ_uv() received invalid "
			"channel number=0x%x in message from partid=%d\n",
			ch_number, XPC_PARTID(part));

		/* get hb checker to deactivate from the remote partition */
		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		अगर (part_uv->act_state_req == 0)
			xpc_activate_IRQ_rcvd++;
		part_uv->act_state_req = XPC_P_ASR_DEACTIVATE_UV;
		part_uv->reason = xpBadChannelNumber;
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		wake_up_पूर्णांकerruptible(&xpc_activate_IRQ_wq);
		वापस;
	पूर्ण

	ch = &part->channels[ch_number];
	xpc_msgqueue_ref(ch);

	अगर (!(ch->flags & XPC_C_CONNECTED)) अणु
		xpc_msgqueue_deref(ch);
		वापस;
	पूर्ण

	/* see अगर we're really dealing with an ACK क्रम a previously sent msg */
	अगर (msg->hdr.size == 0) अणु
		xpc_handle_notअगरy_mq_ack_uv(ch, msg);
		xpc_msgqueue_deref(ch);
		वापस;
	पूर्ण

	/* we're dealing with a normal message sent via the notअगरy_mq */
	ch_uv = &ch->sn.uv;

	msg_slot = ch_uv->recv_msg_slots +
	    (msg->hdr.msg_slot_number % ch->remote_nentries) * ch->entry_size;

	BUG_ON(msg_slot->hdr.size != 0);

	स_नकल(msg_slot, msg, msg->hdr.size);

	xpc_put_fअगरo_entry_uv(&ch_uv->recv_msg_list, &msg_slot->hdr.u.next);

	अगर (ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) अणु
		/*
		 * If there is an existing idle kthपढ़ो get it to deliver
		 * the payload, otherwise we'll have to get the channel mgr
		 * क्रम this partition to create a kthपढ़ो to करो the delivery.
		 */
		अगर (atomic_पढ़ो(&ch->kthपढ़ोs_idle) > 0)
			wake_up_nr(&ch->idle_wq, 1);
		अन्यथा
			xpc_send_chctl_local_msgrequest_uv(part, ch->number);
	पूर्ण
	xpc_msgqueue_deref(ch);
पूर्ण

अटल irqवापस_t
xpc_handle_notअगरy_IRQ_uv(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xpc_notअगरy_mq_msg_uv *msg;
	लघु partid;
	काष्ठा xpc_partition *part;

	जबतक ((msg = gru_get_next_message(xpc_notअगरy_mq_uv->gru_mq_desc)) !=
	       शून्य) अणु

		partid = msg->hdr.partid;
		अगर (partid < 0 || partid >= XP_MAX_NPARTITIONS_UV) अणु
			dev_err(xpc_part, "xpc_handle_notify_IRQ_uv() received "
				"invalid partid=0x%x in message\n", partid);
		पूर्ण अन्यथा अणु
			part = &xpc_partitions[partid];

			अगर (xpc_part_ref(part)) अणु
				xpc_handle_notअगरy_mq_msg_uv(part, msg);
				xpc_part_deref(part);
			पूर्ण
		पूर्ण

		gru_मुक्त_message(xpc_notअगरy_mq_uv->gru_mq_desc, msg);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
xpc_n_of_deliverable_payloads_uv(काष्ठा xpc_channel *ch)
अणु
	वापस xpc_n_of_fअगरo_entries_uv(&ch->sn.uv.recv_msg_list);
पूर्ण

अटल व्योम
xpc_process_msg_chctl_flags_uv(काष्ठा xpc_partition *part, पूर्णांक ch_number)
अणु
	काष्ठा xpc_channel *ch = &part->channels[ch_number];
	पूर्णांक ndeliverable_payloads;

	xpc_msgqueue_ref(ch);

	ndeliverable_payloads = xpc_n_of_deliverable_payloads_uv(ch);

	अगर (ndeliverable_payloads > 0 &&
	    (ch->flags & XPC_C_CONNECTED) &&
	    (ch->flags & XPC_C_CONNECTEDCALLOUT_MADE)) अणु

		xpc_activate_kthपढ़ोs(ch, ndeliverable_payloads);
	पूर्ण

	xpc_msgqueue_deref(ch);
पूर्ण

अटल क्रमागत xp_retval
xpc_send_payload_uv(काष्ठा xpc_channel *ch, u32 flags, व्योम *payload,
		    u16 payload_size, u8 notअगरy_type, xpc_notअगरy_func func,
		    व्योम *key)
अणु
	क्रमागत xp_retval ret = xpSuccess;
	काष्ठा xpc_send_msg_slot_uv *msg_slot = शून्य;
	काष्ठा xpc_notअगरy_mq_msg_uv *msg;
	u8 msg_buffer[XPC_NOTIFY_MSG_SIZE_UV];
	माप_प्रकार msg_size;

	DBUG_ON(notअगरy_type != XPC_N_CALL);

	msg_size = माप(काष्ठा xpc_notअगरy_mq_msghdr_uv) + payload_size;
	अगर (msg_size > ch->entry_size)
		वापस xpPayloadTooBig;

	xpc_msgqueue_ref(ch);

	अगर (ch->flags & XPC_C_DISCONNECTING) अणु
		ret = ch->reason;
		जाओ out_1;
	पूर्ण
	अगर (!(ch->flags & XPC_C_CONNECTED)) अणु
		ret = xpNotConnected;
		जाओ out_1;
	पूर्ण

	ret = xpc_allocate_msg_slot_uv(ch, flags, &msg_slot);
	अगर (ret != xpSuccess)
		जाओ out_1;

	अगर (func != शून्य) अणु
		atomic_inc(&ch->n_to_notअगरy);

		msg_slot->key = key;
		smp_wmb(); /* a non-शून्य func must hit memory after the key */
		msg_slot->func = func;

		अगर (ch->flags & XPC_C_DISCONNECTING) अणु
			ret = ch->reason;
			जाओ out_2;
		पूर्ण
	पूर्ण

	msg = (काष्ठा xpc_notअगरy_mq_msg_uv *)&msg_buffer;
	msg->hdr.partid = xp_partition_id;
	msg->hdr.ch_number = ch->number;
	msg->hdr.size = msg_size;
	msg->hdr.msg_slot_number = msg_slot->msg_slot_number;
	स_नकल(&msg->payload, payload, payload_size);

	ret = xpc_send_gru_msg(ch->sn.uv.cached_notअगरy_gru_mq_desc, msg,
			       msg_size);
	अगर (ret == xpSuccess)
		जाओ out_1;

	XPC_DEACTIVATE_PARTITION(&xpc_partitions[ch->partid], ret);
out_2:
	अगर (func != शून्य) अणु
		/*
		 * Try to शून्य the msg_slot's func field. If we fail, then
		 * xpc_notअगरy_senders_of_disconnect_uv() beat us to it, in which
		 * हाल we need to pretend we succeeded to send the message
		 * since the user will get a callout क्रम the disconnect error
		 * by xpc_notअगरy_senders_of_disconnect_uv(), and to also get an
		 * error वापसed here will confuse them. Additionally, since
		 * in this हाल the channel is being disconnected we करोn't need
		 * to put the the msg_slot back on the मुक्त list.
		 */
		अगर (cmpxchg(&msg_slot->func, func, शून्य) != func) अणु
			ret = xpSuccess;
			जाओ out_1;
		पूर्ण

		msg_slot->key = शून्य;
		atomic_dec(&ch->n_to_notअगरy);
	पूर्ण
	xpc_मुक्त_msg_slot_uv(ch, msg_slot);
out_1:
	xpc_msgqueue_deref(ch);
	वापस ret;
पूर्ण

/*
 * Tell the callers of xpc_send_notअगरy() that the status of their payloads
 * is unknown because the channel is now disconnecting.
 *
 * We करोn't worry about putting these msg_slots on the मुक्त list since the
 * msg_slots themselves are about to be kमुक्त'd.
 */
अटल व्योम
xpc_notअगरy_senders_of_disconnect_uv(काष्ठा xpc_channel *ch)
अणु
	काष्ठा xpc_send_msg_slot_uv *msg_slot;
	पूर्णांक entry;

	DBUG_ON(!(ch->flags & XPC_C_DISCONNECTING));

	क्रम (entry = 0; entry < ch->local_nentries; entry++) अणु

		अगर (atomic_पढ़ो(&ch->n_to_notअगरy) == 0)
			अवरोध;

		msg_slot = &ch->sn.uv.send_msg_slots[entry];
		अगर (msg_slot->func != शून्य)
			xpc_notअगरy_sender_uv(ch, msg_slot, ch->reason);
	पूर्ण
पूर्ण

/*
 * Get the next deliverable message's payload.
 */
अटल व्योम *
xpc_get_deliverable_payload_uv(काष्ठा xpc_channel *ch)
अणु
	काष्ठा xpc_fअगरo_entry_uv *entry;
	काष्ठा xpc_notअगरy_mq_msg_uv *msg;
	व्योम *payload = शून्य;

	अगर (!(ch->flags & XPC_C_DISCONNECTING)) अणु
		entry = xpc_get_fअगरo_entry_uv(&ch->sn.uv.recv_msg_list);
		अगर (entry != शून्य) अणु
			msg = container_of(entry, काष्ठा xpc_notअगरy_mq_msg_uv,
					   hdr.u.next);
			payload = &msg->payload;
		पूर्ण
	पूर्ण
	वापस payload;
पूर्ण

अटल व्योम
xpc_received_payload_uv(काष्ठा xpc_channel *ch, व्योम *payload)
अणु
	काष्ठा xpc_notअगरy_mq_msg_uv *msg;
	क्रमागत xp_retval ret;

	msg = container_of(payload, काष्ठा xpc_notअगरy_mq_msg_uv, payload);

	/* वापस an ACK to the sender of this message */

	msg->hdr.partid = xp_partition_id;
	msg->hdr.size = 0;	/* size of zero indicates this is an ACK */

	ret = xpc_send_gru_msg(ch->sn.uv.cached_notअगरy_gru_mq_desc, msg,
			       माप(काष्ठा xpc_notअगरy_mq_msghdr_uv));
	अगर (ret != xpSuccess)
		XPC_DEACTIVATE_PARTITION(&xpc_partitions[ch->partid], ret);
पूर्ण

अटल स्थिर काष्ठा xpc_arch_operations xpc_arch_ops_uv = अणु
	.setup_partitions = xpc_setup_partitions_uv,
	.tearकरोwn_partitions = xpc_tearकरोwn_partitions_uv,
	.process_activate_IRQ_rcvd = xpc_process_activate_IRQ_rcvd_uv,
	.get_partition_rsvd_page_pa = xpc_get_partition_rsvd_page_pa_uv,
	.setup_rsvd_page = xpc_setup_rsvd_page_uv,

	.allow_hb = xpc_allow_hb_uv,
	.disallow_hb = xpc_disallow_hb_uv,
	.disallow_all_hbs = xpc_disallow_all_hbs_uv,
	.increment_heartbeat = xpc_increment_heartbeat_uv,
	.offline_heartbeat = xpc_offline_heartbeat_uv,
	.online_heartbeat = xpc_online_heartbeat_uv,
	.heartbeat_init = xpc_heartbeat_init_uv,
	.heartbeat_निकास = xpc_heartbeat_निकास_uv,
	.get_remote_heartbeat = xpc_get_remote_heartbeat_uv,

	.request_partition_activation =
		xpc_request_partition_activation_uv,
	.request_partition_reactivation =
		xpc_request_partition_reactivation_uv,
	.request_partition_deactivation =
		xpc_request_partition_deactivation_uv,
	.cancel_partition_deactivation_request =
		xpc_cancel_partition_deactivation_request_uv,

	.setup_ch_काष्ठाures = xpc_setup_ch_काष्ठाures_uv,
	.tearकरोwn_ch_काष्ठाures = xpc_tearकरोwn_ch_काष्ठाures_uv,

	.make_first_contact = xpc_make_first_contact_uv,

	.get_chctl_all_flags = xpc_get_chctl_all_flags_uv,
	.send_chctl_बंदrequest = xpc_send_chctl_बंदrequest_uv,
	.send_chctl_बंदreply = xpc_send_chctl_बंदreply_uv,
	.send_chctl_खोलोrequest = xpc_send_chctl_खोलोrequest_uv,
	.send_chctl_खोलोreply = xpc_send_chctl_खोलोreply_uv,
	.send_chctl_खोलोcomplete = xpc_send_chctl_खोलोcomplete_uv,
	.process_msg_chctl_flags = xpc_process_msg_chctl_flags_uv,

	.save_remote_msgqueue_pa = xpc_save_remote_msgqueue_pa_uv,

	.setup_msg_काष्ठाures = xpc_setup_msg_काष्ठाures_uv,
	.tearकरोwn_msg_काष्ठाures = xpc_tearकरोwn_msg_काष्ठाures_uv,

	.indicate_partition_engaged = xpc_indicate_partition_engaged_uv,
	.indicate_partition_disengaged = xpc_indicate_partition_disengaged_uv,
	.assume_partition_disengaged = xpc_assume_partition_disengaged_uv,
	.partition_engaged = xpc_partition_engaged_uv,
	.any_partition_engaged = xpc_any_partition_engaged_uv,

	.n_of_deliverable_payloads = xpc_n_of_deliverable_payloads_uv,
	.send_payload = xpc_send_payload_uv,
	.get_deliverable_payload = xpc_get_deliverable_payload_uv,
	.received_payload = xpc_received_payload_uv,
	.notअगरy_senders_of_disconnect = xpc_notअगरy_senders_of_disconnect_uv,
पूर्ण;

अटल पूर्णांक
xpc_init_mq_node(पूर्णांक nid)
अणु
	पूर्णांक cpu;

	get_online_cpus();

	क्रम_each_cpu(cpu, cpumask_of_node(nid)) अणु
		xpc_activate_mq_uv =
			xpc_create_gru_mq_uv(XPC_ACTIVATE_MQ_SIZE_UV, nid,
					     XPC_ACTIVATE_IRQ_NAME,
					     xpc_handle_activate_IRQ_uv);
		अगर (!IS_ERR(xpc_activate_mq_uv))
			अवरोध;
	पूर्ण
	अगर (IS_ERR(xpc_activate_mq_uv)) अणु
		put_online_cpus();
		वापस PTR_ERR(xpc_activate_mq_uv);
	पूर्ण

	क्रम_each_cpu(cpu, cpumask_of_node(nid)) अणु
		xpc_notअगरy_mq_uv =
			xpc_create_gru_mq_uv(XPC_NOTIFY_MQ_SIZE_UV, nid,
					     XPC_NOTIFY_IRQ_NAME,
					     xpc_handle_notअगरy_IRQ_uv);
		अगर (!IS_ERR(xpc_notअगरy_mq_uv))
			अवरोध;
	पूर्ण
	अगर (IS_ERR(xpc_notअगरy_mq_uv)) अणु
		xpc_destroy_gru_mq_uv(xpc_activate_mq_uv);
		put_online_cpus();
		वापस PTR_ERR(xpc_notअगरy_mq_uv);
	पूर्ण

	put_online_cpus();
	वापस 0;
पूर्ण

पूर्णांक
xpc_init_uv(व्योम)
अणु
	पूर्णांक nid;
	पूर्णांक ret = 0;

	xpc_arch_ops = xpc_arch_ops_uv;

	अगर (माप(काष्ठा xpc_notअगरy_mq_msghdr_uv) > XPC_MSG_HDR_MAX_SIZE) अणु
		dev_err(xpc_part, "xpc_notify_mq_msghdr_uv is larger than %d\n",
			XPC_MSG_HDR_MAX_SIZE);
		वापस -E2BIG;
	पूर्ण

	अगर (xpc_mq_node < 0)
		क्रम_each_online_node(nid) अणु
			ret = xpc_init_mq_node(nid);

			अगर (!ret)
				अवरोध;
		पूर्ण
	अन्यथा
		ret = xpc_init_mq_node(xpc_mq_node);

	अगर (ret < 0)
		dev_err(xpc_part, "xpc_init_mq_node() returned error=%d\n",
			-ret);

	वापस ret;
पूर्ण

व्योम
xpc_निकास_uv(व्योम)
अणु
	xpc_destroy_gru_mq_uv(xpc_notअगरy_mq_uv);
	xpc_destroy_gru_mq_uv(xpc_activate_mq_uv);
पूर्ण

module_param(xpc_mq_node, पूर्णांक, 0);
MODULE_PARM_DESC(xpc_mq_node, "Node number on which to allocate message queues.");
