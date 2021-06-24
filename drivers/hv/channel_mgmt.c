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
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpu.h>
#समावेश <linux/hyperv.h>
#समावेश <यंत्र/mshyperv.h>

#समावेश "hyperv_vmbus.h"

अटल व्योम init_vp_index(काष्ठा vmbus_channel *channel);

स्थिर काष्ठा vmbus_device vmbus_devs[] = अणु
	/* IDE */
	अणु .dev_type = HV_IDE,
	  HV_IDE_GUID,
	  .perf_device = true,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* SCSI */
	अणु .dev_type = HV_SCSI,
	  HV_SCSI_GUID,
	  .perf_device = true,
	  .allowed_in_isolated = true,
	पूर्ण,

	/* Fibre Channel */
	अणु .dev_type = HV_FC,
	  HV_SYNTHFC_GUID,
	  .perf_device = true,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Synthetic NIC */
	अणु .dev_type = HV_NIC,
	  HV_NIC_GUID,
	  .perf_device = true,
	  .allowed_in_isolated = true,
	पूर्ण,

	/* Network Direct */
	अणु .dev_type = HV_ND,
	  HV_ND_GUID,
	  .perf_device = true,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* PCIE */
	अणु .dev_type = HV_PCIE,
	  HV_PCIE_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Synthetic Frame Buffer */
	अणु .dev_type = HV_FB,
	  HV_SYNTHVID_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Synthetic Keyboard */
	अणु .dev_type = HV_KBD,
	  HV_KBD_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Synthetic MOUSE */
	अणु .dev_type = HV_MOUSE,
	  HV_MOUSE_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* KVP */
	अणु .dev_type = HV_KVP,
	  HV_KVP_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Time Synch */
	अणु .dev_type = HV_TS,
	  HV_TS_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = true,
	पूर्ण,

	/* Heartbeat */
	अणु .dev_type = HV_HB,
	  HV_HEART_BEAT_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = true,
	पूर्ण,

	/* Shutकरोwn */
	अणु .dev_type = HV_SHUTDOWN,
	  HV_SHUTDOWN_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = true,
	पूर्ण,

	/* File copy */
	अणु .dev_type = HV_FCOPY,
	  HV_FCOPY_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Backup */
	अणु .dev_type = HV_BACKUP,
	  HV_VSS_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Dynamic Memory */
	अणु .dev_type = HV_DM,
	  HV_DM_GUID,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,

	/* Unknown GUID */
	अणु .dev_type = HV_UNKNOWN,
	  .perf_device = false,
	  .allowed_in_isolated = false,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	guid_t guid;
पूर्ण vmbus_unsupported_devs[] = अणु
	अणु HV_AVMA1_GUID पूर्ण,
	अणु HV_AVMA2_GUID पूर्ण,
	अणु HV_RDV_GUID	पूर्ण,
पूर्ण;

/*
 * The rescinded channel may be blocked रुकोing क्रम a response from the host;
 * take care of that.
 */
अटल व्योम vmbus_rescind_cleanup(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा vmbus_channel_msginfo *msginfo;
	अचिन्हित दीर्घ flags;


	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	channel->rescind = true;
	list_क्रम_each_entry(msginfo, &vmbus_connection.chn_msg_list,
				msglistentry) अणु

		अगर (msginfo->रुकोing_channel == channel) अणु
			complete(&msginfo->रुकोevent);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
पूर्ण

अटल bool is_unsupported_vmbus_devs(स्थिर guid_t *guid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vmbus_unsupported_devs); i++)
		अगर (guid_equal(guid, &vmbus_unsupported_devs[i].guid))
			वापस true;
	वापस false;
पूर्ण

अटल u16 hv_get_dev_type(स्थिर काष्ठा vmbus_channel *channel)
अणु
	स्थिर guid_t *guid = &channel->offermsg.offer.अगर_type;
	u16 i;

	अगर (is_hvsock_channel(channel) || is_unsupported_vmbus_devs(guid))
		वापस HV_UNKNOWN;

	क्रम (i = HV_IDE; i < HV_UNKNOWN; i++) अणु
		अगर (guid_equal(guid, &vmbus_devs[i].guid))
			वापस i;
	पूर्ण
	pr_info("Unknown GUID: %pUl\n", guid);
	वापस i;
पूर्ण

/**
 * vmbus_prep_negotiate_resp() - Create शेष response क्रम Negotiate message
 * @icmsghdrp: Poपूर्णांकer to msg header काष्ठाure
 * @buf: Raw buffer channel data
 * @buflen: Length of the raw buffer channel data.
 * @fw_version: The framework versions we can support.
 * @fw_vercnt: The size of @fw_version.
 * @srv_version: The service versions we can support.
 * @srv_vercnt: The size of @srv_version.
 * @nego_fw_version: The selected framework version.
 * @nego_srv_version: The selected service version.
 *
 * Note: Versions are given in decreasing order.
 *
 * Set up and fill in शेष negotiate response message.
 * Mainly used by Hyper-V drivers.
 */
bool vmbus_prep_negotiate_resp(काष्ठा icmsg_hdr *icmsghdrp, u8 *buf,
				u32 buflen, स्थिर पूर्णांक *fw_version, पूर्णांक fw_vercnt,
				स्थिर पूर्णांक *srv_version, पूर्णांक srv_vercnt,
				पूर्णांक *nego_fw_version, पूर्णांक *nego_srv_version)
अणु
	पूर्णांक icframe_major, icframe_minor;
	पूर्णांक icmsg_major, icmsg_minor;
	पूर्णांक fw_major, fw_minor;
	पूर्णांक srv_major, srv_minor;
	पूर्णांक i, j;
	bool found_match = false;
	काष्ठा icmsg_negotiate *negop;

	/* Check that there's enough space क्रम icframe_vercnt, icmsg_vercnt */
	अगर (buflen < ICMSG_HDR + दुरत्व(काष्ठा icmsg_negotiate, reserved)) अणु
		pr_err_ratelimited("Invalid icmsg negotiate\n");
		वापस false;
	पूर्ण

	icmsghdrp->icmsgsize = 0x10;
	negop = (काष्ठा icmsg_negotiate *)&buf[ICMSG_HDR];

	icframe_major = negop->icframe_vercnt;
	icframe_minor = 0;

	icmsg_major = negop->icmsg_vercnt;
	icmsg_minor = 0;

	/* Validate negop packet */
	अगर (icframe_major > IC_VERSION_NEGOTIATION_MAX_VER_COUNT ||
	    icmsg_major > IC_VERSION_NEGOTIATION_MAX_VER_COUNT ||
	    ICMSG_NEGOTIATE_PKT_SIZE(icframe_major, icmsg_major) > buflen) अणु
		pr_err_ratelimited("Invalid icmsg negotiate - icframe_major: %u, icmsg_major: %u\n",
				   icframe_major, icmsg_major);
		जाओ fw_error;
	पूर्ण

	/*
	 * Select the framework version number we will
	 * support.
	 */

	क्रम (i = 0; i < fw_vercnt; i++) अणु
		fw_major = (fw_version[i] >> 16);
		fw_minor = (fw_version[i] & 0xFFFF);

		क्रम (j = 0; j < negop->icframe_vercnt; j++) अणु
			अगर ((negop->icversion_data[j].major == fw_major) &&
			    (negop->icversion_data[j].minor == fw_minor)) अणु
				icframe_major = negop->icversion_data[j].major;
				icframe_minor = negop->icversion_data[j].minor;
				found_match = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found_match)
			अवरोध;
	पूर्ण

	अगर (!found_match)
		जाओ fw_error;

	found_match = false;

	क्रम (i = 0; i < srv_vercnt; i++) अणु
		srv_major = (srv_version[i] >> 16);
		srv_minor = (srv_version[i] & 0xFFFF);

		क्रम (j = negop->icframe_vercnt;
			(j < negop->icframe_vercnt + negop->icmsg_vercnt);
			j++) अणु

			अगर ((negop->icversion_data[j].major == srv_major) &&
				(negop->icversion_data[j].minor == srv_minor)) अणु

				icmsg_major = negop->icversion_data[j].major;
				icmsg_minor = negop->icversion_data[j].minor;
				found_match = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found_match)
			अवरोध;
	पूर्ण

	/*
	 * Respond with the framework and service
	 * version numbers we can support.
	 */

fw_error:
	अगर (!found_match) अणु
		negop->icframe_vercnt = 0;
		negop->icmsg_vercnt = 0;
	पूर्ण अन्यथा अणु
		negop->icframe_vercnt = 1;
		negop->icmsg_vercnt = 1;
	पूर्ण

	अगर (nego_fw_version)
		*nego_fw_version = (icframe_major << 16) | icframe_minor;

	अगर (nego_srv_version)
		*nego_srv_version = (icmsg_major << 16) | icmsg_minor;

	negop->icversion_data[0].major = icframe_major;
	negop->icversion_data[0].minor = icframe_minor;
	negop->icversion_data[1].major = icmsg_major;
	negop->icversion_data[1].minor = icmsg_minor;
	वापस found_match;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_prep_negotiate_resp);

/*
 * alloc_channel - Allocate and initialize a vmbus channel object
 */
अटल काष्ठा vmbus_channel *alloc_channel(व्योम)
अणु
	काष्ठा vmbus_channel *channel;

	channel = kzalloc(माप(*channel), GFP_ATOMIC);
	अगर (!channel)
		वापस शून्य;

	spin_lock_init(&channel->sched_lock);
	init_completion(&channel->rescind_event);

	INIT_LIST_HEAD(&channel->sc_list);

	tasklet_init(&channel->callback_event,
		     vmbus_on_event, (अचिन्हित दीर्घ)channel);

	hv_ringbuffer_pre_init(channel);

	वापस channel;
पूर्ण

/*
 * मुक्त_channel - Release the resources used by the vmbus channel object
 */
अटल व्योम मुक्त_channel(काष्ठा vmbus_channel *channel)
अणु
	tasklet_समाप्त(&channel->callback_event);
	vmbus_हटाओ_channel_attr_group(channel);

	kobject_put(&channel->kobj);
पूर्ण

व्योम vmbus_channel_map_relid(काष्ठा vmbus_channel *channel)
अणु
	अगर (WARN_ON(channel->offermsg.child_relid >= MAX_CHANNEL_RELIDS))
		वापस;
	/*
	 * The mapping of the channel's relid is visible from the CPUs that
	 * execute vmbus_chan_sched() by the समय that vmbus_chan_sched() will
	 * execute:
	 *
	 *  (a) In the "normal (i.e., not resuming from hibernation)" path,
	 *      the full barrier in smp_store_mb() guarantees that the store
	 *      is propagated to all CPUs beक्रमe the add_channel_work work
	 *      is queued.  In turn, add_channel_work is queued beक्रमe the
	 *      channel's ring buffer is allocated/initialized and the
	 *      OPENCHANNEL message क्रम the channel is sent in vmbus_खोलो().
	 *      Hyper-V won't start sending the पूर्णांकerrupts क्रम the channel
	 *      beक्रमe the OPENCHANNEL message is acked.  The memory barrier
	 *      in vmbus_chan_sched() -> sync_test_and_clear_bit() ensures
	 *      that vmbus_chan_sched() must find the channel's relid in
	 *      recv_पूर्णांक_page beक्रमe retrieving the channel poपूर्णांकer from the
	 *      array of channels.
	 *
	 *  (b) In the "resuming from hibernation" path, the smp_store_mb()
	 *      guarantees that the store is propagated to all CPUs beक्रमe
	 *      the VMBus connection is marked as पढ़ोy क्रम the resume event
	 *      (cf. check_पढ़ोy_क्रम_resume_event()).  The पूर्णांकerrupt handler
	 *      of the VMBus driver and vmbus_chan_sched() can not run beक्रमe
	 *      vmbus_bus_resume() has completed execution (cf. resume_noirq).
	 */
	smp_store_mb(
		vmbus_connection.channels[channel->offermsg.child_relid],
		channel);
पूर्ण

व्योम vmbus_channel_unmap_relid(काष्ठा vmbus_channel *channel)
अणु
	अगर (WARN_ON(channel->offermsg.child_relid >= MAX_CHANNEL_RELIDS))
		वापस;
	WRITE_ONCE(
		vmbus_connection.channels[channel->offermsg.child_relid],
		शून्य);
पूर्ण

अटल व्योम vmbus_release_relid(u32 relid)
अणु
	काष्ठा vmbus_channel_relid_released msg;
	पूर्णांक ret;

	स_रखो(&msg, 0, माप(काष्ठा vmbus_channel_relid_released));
	msg.child_relid = relid;
	msg.header.msgtype = CHANNELMSG_RELID_RELEASED;
	ret = vmbus_post_msg(&msg, माप(काष्ठा vmbus_channel_relid_released),
			     true);

	trace_vmbus_release_relid(&msg, ret);
पूर्ण

व्योम hv_process_channel_removal(काष्ठा vmbus_channel *channel)
अणु
	lockdep_निश्चित_held(&vmbus_connection.channel_mutex);
	BUG_ON(!channel->rescind);

	/*
	 * hv_process_channel_removal() could find INVALID_RELID only क्रम
	 * hv_sock channels.  See the अंतरभूत comments in vmbus_onoffer().
	 */
	WARN_ON(channel->offermsg.child_relid == INVALID_RELID &&
		!is_hvsock_channel(channel));

	/*
	 * Upon suspend, an in-use hv_sock channel is हटाओd from the array of
	 * channels and the relid is invalidated.  After hibernation, when the
	 * user-space appplication destroys the channel, it's unnecessary and
	 * unsafe to हटाओ the channel from the array of channels.  See also
	 * the अंतरभूत comments beक्रमe the call of vmbus_release_relid() below.
	 */
	अगर (channel->offermsg.child_relid != INVALID_RELID)
		vmbus_channel_unmap_relid(channel);

	अगर (channel->primary_channel == शून्य)
		list_del(&channel->listentry);
	अन्यथा
		list_del(&channel->sc_list);

	/*
	 * If this is a "perf" channel, updates the hv_numa_map[] masks so that
	 * init_vp_index() can (re-)use the CPU.
	 */
	अगर (hv_is_perf_channel(channel))
		hv_clear_alloced_cpu(channel->target_cpu);

	/*
	 * Upon suspend, an in-use hv_sock channel is marked as "rescinded" and
	 * the relid is invalidated; after hibernation, when the user-space app
	 * destroys the channel, the relid is INVALID_RELID, and in this हाल
	 * it's unnecessary and unsafe to release the old relid, since the same
	 * relid can refer to a completely dअगरferent channel now.
	 */
	अगर (channel->offermsg.child_relid != INVALID_RELID)
		vmbus_release_relid(channel->offermsg.child_relid);

	मुक्त_channel(channel);
पूर्ण

व्योम vmbus_मुक्त_channels(व्योम)
अणु
	काष्ठा vmbus_channel *channel, *पंचांगp;

	list_क्रम_each_entry_safe(channel, पंचांगp, &vmbus_connection.chn_list,
		listentry) अणु
		/* hv_process_channel_removal() needs this */
		channel->rescind = true;

		vmbus_device_unरेजिस्टर(channel->device_obj);
	पूर्ण
पूर्ण

/* Note: the function can run concurrently क्रम primary/sub channels. */
अटल व्योम vmbus_add_channel_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vmbus_channel *newchannel =
		container_of(work, काष्ठा vmbus_channel, add_channel_work);
	काष्ठा vmbus_channel *primary_channel = newchannel->primary_channel;
	पूर्णांक ret;

	/*
	 * This state is used to indicate a successful खोलो
	 * so that when we करो बंद the channel normally, we
	 * can cleanup properly.
	 */
	newchannel->state = CHANNEL_OPEN_STATE;

	अगर (primary_channel != शून्य) अणु
		/* newchannel is a sub-channel. */
		काष्ठा hv_device *dev = primary_channel->device_obj;

		अगर (vmbus_add_channel_kobj(dev, newchannel))
			जाओ err_deq_chan;

		अगर (primary_channel->sc_creation_callback != शून्य)
			primary_channel->sc_creation_callback(newchannel);

		newchannel->probe_करोne = true;
		वापस;
	पूर्ण

	/*
	 * Start the process of binding the primary channel to the driver
	 */
	newchannel->device_obj = vmbus_device_create(
		&newchannel->offermsg.offer.अगर_type,
		&newchannel->offermsg.offer.अगर_instance,
		newchannel);
	अगर (!newchannel->device_obj)
		जाओ err_deq_chan;

	newchannel->device_obj->device_id = newchannel->device_id;
	/*
	 * Add the new device to the bus. This will kick off device-driver
	 * binding which eventually invokes the device driver's AddDevice()
	 * method.
	 */
	ret = vmbus_device_रेजिस्टर(newchannel->device_obj);

	अगर (ret != 0) अणु
		pr_err("unable to add child device object (relid %d)\n",
			newchannel->offermsg.child_relid);
		kमुक्त(newchannel->device_obj);
		जाओ err_deq_chan;
	पूर्ण

	newchannel->probe_करोne = true;
	वापस;

err_deq_chan:
	mutex_lock(&vmbus_connection.channel_mutex);

	/*
	 * We need to set the flag, otherwise
	 * vmbus_onoffer_rescind() can be blocked.
	 */
	newchannel->probe_करोne = true;

	अगर (primary_channel == शून्य)
		list_del(&newchannel->listentry);
	अन्यथा
		list_del(&newchannel->sc_list);

	/* vmbus_process_offer() has mapped the channel. */
	vmbus_channel_unmap_relid(newchannel);

	mutex_unlock(&vmbus_connection.channel_mutex);

	vmbus_release_relid(newchannel->offermsg.child_relid);

	मुक्त_channel(newchannel);
पूर्ण

/*
 * vmbus_process_offer - Process the offer by creating a channel/device
 * associated with this offer
 */
अटल व्योम vmbus_process_offer(काष्ठा vmbus_channel *newchannel)
अणु
	काष्ठा vmbus_channel *channel;
	काष्ठा workqueue_काष्ठा *wq;
	bool fnew = true;

	/*
	 * Synchronize vmbus_process_offer() and CPU hotplugging:
	 *
	 * CPU1				CPU2
	 *
	 * [vmbus_process_offer()]	[Hot removal of the CPU]
	 *
	 * CPU_READ_LOCK		CPUS_WRITE_LOCK
	 * LOAD cpu_online_mask		SEARCH chn_list
	 * STORE target_cpu		LOAD target_cpu
	 * INSERT chn_list		STORE cpu_online_mask
	 * CPUS_READ_UNLOCK		CPUS_WRITE_UNLOCK
	 *
	 * Forbids: CPU1's LOAD from *not* seing CPU2's STORE &&
	 *              CPU2's SEARCH from *not* seeing CPU1's INSERT
	 *
	 * Forbids: CPU2's SEARCH from seeing CPU1's INSERT &&
	 *              CPU2's LOAD from *not* seing CPU1's STORE
	 */
	cpus_पढ़ो_lock();

	/*
	 * Serializes the modअगरications of the chn_list list as well as
	 * the accesses to next_numa_node_id in init_vp_index().
	 */
	mutex_lock(&vmbus_connection.channel_mutex);

	init_vp_index(newchannel);

	/* Remember the channels that should be cleaned up upon suspend. */
	अगर (is_hvsock_channel(newchannel) || is_sub_channel(newchannel))
		atomic_inc(&vmbus_connection.nr_chan_बंद_on_suspend);

	/*
	 * Now that we have acquired the channel_mutex,
	 * we can release the potentially racing rescind thपढ़ो.
	 */
	atomic_dec(&vmbus_connection.offer_in_progress);

	list_क्रम_each_entry(channel, &vmbus_connection.chn_list, listentry) अणु
		अगर (guid_equal(&channel->offermsg.offer.अगर_type,
			       &newchannel->offermsg.offer.अगर_type) &&
		    guid_equal(&channel->offermsg.offer.अगर_instance,
			       &newchannel->offermsg.offer.अगर_instance)) अणु
			fnew = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fnew) अणु
		list_add_tail(&newchannel->listentry,
			      &vmbus_connection.chn_list);
	पूर्ण अन्यथा अणु
		/*
		 * Check to see अगर this is a valid sub-channel.
		 */
		अगर (newchannel->offermsg.offer.sub_channel_index == 0) अणु
			mutex_unlock(&vmbus_connection.channel_mutex);
			/*
			 * Don't call मुक्त_channel(), because newchannel->kobj
			 * is not initialized yet.
			 */
			kमुक्त(newchannel);
			WARN_ON_ONCE(1);
			वापस;
		पूर्ण
		/*
		 * Process the sub-channel.
		 */
		newchannel->primary_channel = channel;
		list_add_tail(&newchannel->sc_list, &channel->sc_list);
	पूर्ण

	vmbus_channel_map_relid(newchannel);

	mutex_unlock(&vmbus_connection.channel_mutex);
	cpus_पढ़ो_unlock();

	/*
	 * vmbus_process_offer() mustn't call channel->sc_creation_callback()
	 * directly क्रम sub-channels, because sc_creation_callback() ->
	 * vmbus_खोलो() may never get the host's response to the
	 * OPEN_CHANNEL message (the host may rescind a channel at any समय,
	 * e.g. in the हाल of hot removing a NIC), and vmbus_onoffer_rescind()
	 * may not wake up the vmbus_खोलो() as it's blocked due to a non-zero
	 * vmbus_connection.offer_in_progress, and finally we have a deadlock.
	 *
	 * The above is also true क्रम primary channels, अगर the related device
	 * drivers use sync probing mode by शेष.
	 *
	 * And, usually the handling of primary channels and sub-channels can
	 * depend on each other, so we should offload them to dअगरferent
	 * workqueues to aव्योम possible deadlock, e.g. in sync-probing mode,
	 * NIC1's netvsc_subchan_work() can race with NIC2's netvsc_probe() ->
	 * rtnl_lock(), and causes deadlock: the क्रमmer माला_लो the rtnl_lock
	 * and रुकोs क्रम all the sub-channels to appear, but the latter
	 * can't get the rtnl_lock and this blocks the handling of
	 * sub-channels.
	 */
	INIT_WORK(&newchannel->add_channel_work, vmbus_add_channel_work);
	wq = fnew ? vmbus_connection.handle_primary_chan_wq :
		    vmbus_connection.handle_sub_chan_wq;
	queue_work(wq, &newchannel->add_channel_work);
पूर्ण

/*
 * We use this state to अटलally distribute the channel पूर्णांकerrupt load.
 */
अटल पूर्णांक next_numa_node_id;

/*
 * Starting with Win8, we can अटलally distribute the incoming
 * channel पूर्णांकerrupt load by binding a channel to VCPU.
 *
 * For pre-win8 hosts or non-perक्रमmance critical channels we assign the
 * VMBUS_CONNECT_CPU.
 *
 * Starting with win8, perक्रमmance critical channels will be distributed
 * evenly among all the available NUMA nodes.  Once the node is asचिन्हित,
 * we will assign the CPU based on a simple round robin scheme.
 */
अटल व्योम init_vp_index(काष्ठा vmbus_channel *channel)
अणु
	bool perf_chn = hv_is_perf_channel(channel);
	cpumask_var_t available_mask;
	काष्ठा cpumask *alloced_mask;
	u32 target_cpu;
	पूर्णांक numa_node;

	अगर ((vmbus_proto_version == VERSION_WS2008) ||
	    (vmbus_proto_version == VERSION_WIN7) || (!perf_chn) ||
	    !alloc_cpumask_var(&available_mask, GFP_KERNEL)) अणु
		/*
		 * Prior to win8, all channel पूर्णांकerrupts are
		 * delivered on VMBUS_CONNECT_CPU.
		 * Also अगर the channel is not a perक्रमmance critical
		 * channel, bind it to VMBUS_CONNECT_CPU.
		 * In हाल alloc_cpumask_var() fails, bind it to
		 * VMBUS_CONNECT_CPU.
		 */
		channel->target_cpu = VMBUS_CONNECT_CPU;
		अगर (perf_chn)
			hv_set_alloced_cpu(VMBUS_CONNECT_CPU);
		वापस;
	पूर्ण

	जबतक (true) अणु
		numa_node = next_numa_node_id++;
		अगर (numa_node == nr_node_ids) अणु
			next_numa_node_id = 0;
			जारी;
		पूर्ण
		अगर (cpumask_empty(cpumask_of_node(numa_node)))
			जारी;
		अवरोध;
	पूर्ण
	alloced_mask = &hv_context.hv_numa_map[numa_node];

	अगर (cpumask_weight(alloced_mask) ==
	    cpumask_weight(cpumask_of_node(numa_node))) अणु
		/*
		 * We have cycled through all the CPUs in the node;
		 * reset the alloced map.
		 */
		cpumask_clear(alloced_mask);
	पूर्ण

	cpumask_xor(available_mask, alloced_mask, cpumask_of_node(numa_node));

	target_cpu = cpumask_first(available_mask);
	cpumask_set_cpu(target_cpu, alloced_mask);

	channel->target_cpu = target_cpu;

	मुक्त_cpumask_var(available_mask);
पूर्ण

#घोषणा UNLOAD_DELAY_UNIT_MS	10		/* 10 milliseconds */
#घोषणा UNLOAD_WAIT_MS		(100*1000)	/* 100 seconds */
#घोषणा UNLOAD_WAIT_LOOPS	(UNLOAD_WAIT_MS/UNLOAD_DELAY_UNIT_MS)
#घोषणा UNLOAD_MSG_MS		(5*1000)	/* Every 5 seconds */
#घोषणा UNLOAD_MSG_LOOPS	(UNLOAD_MSG_MS/UNLOAD_DELAY_UNIT_MS)

अटल व्योम vmbus_रुको_क्रम_unload(व्योम)
अणु
	पूर्णांक cpu;
	व्योम *page_addr;
	काष्ठा hv_message *msg;
	काष्ठा vmbus_channel_message_header *hdr;
	u32 message_type, i;

	/*
	 * CHANNELMSG_UNLOAD_RESPONSE is always delivered to the CPU which was
	 * used क्रम initial contact or to CPU0 depending on host version. When
	 * we're crashing on a different CPU let's hope that IRQ handler on
	 * the cpu which receives CHANNELMSG_UNLOAD_RESPONSE is still
	 * functional and vmbus_unload_response() will complete
	 * vmbus_connection.unload_event. If not, the last thing we can करो is
	 * पढ़ो message pages क्रम all CPUs directly.
	 *
	 * Wait up to 100 seconds since an Azure host must ग_लिखोback any dirty
	 * data in its disk cache beक्रमe the VMbus UNLOAD request will
	 * complete. This flushing has been empirically observed to take up
	 * to 50 seconds in हालs with a lot of dirty data, so allow additional
	 * leeway and क्रम inaccuracies in mdelay(). But eventually समय out so
	 * that the panic path can't get hung क्रमever in हाल the response
	 * message isn't seen.
	 */
	क्रम (i = 1; i <= UNLOAD_WAIT_LOOPS; i++) अणु
		अगर (completion_करोne(&vmbus_connection.unload_event))
			जाओ completed;

		क्रम_each_online_cpu(cpu) अणु
			काष्ठा hv_per_cpu_context *hv_cpu
				= per_cpu_ptr(hv_context.cpu_context, cpu);

			page_addr = hv_cpu->synic_message_page;
			msg = (काष्ठा hv_message *)page_addr
				+ VMBUS_MESSAGE_SINT;

			message_type = READ_ONCE(msg->header.message_type);
			अगर (message_type == HVMSG_NONE)
				जारी;

			hdr = (काष्ठा vmbus_channel_message_header *)
				msg->u.payload;

			अगर (hdr->msgtype == CHANNELMSG_UNLOAD_RESPONSE)
				complete(&vmbus_connection.unload_event);

			vmbus_संकेत_eom(msg, message_type);
		पूर्ण

		/*
		 * Give a notice periodically so someone watching the
		 * serial output won't think it is completely hung.
		 */
		अगर (!(i % UNLOAD_MSG_LOOPS))
			pr_notice("Waiting for VMBus UNLOAD to complete\n");

		mdelay(UNLOAD_DELAY_UNIT_MS);
	पूर्ण
	pr_err("Continuing even though VMBus UNLOAD did not complete\n");

completed:
	/*
	 * We're crashing and alपढ़ोy got the UNLOAD_RESPONSE, cleanup all
	 * maybe-pending messages on all CPUs to be able to receive new
	 * messages after we reconnect.
	 */
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा hv_per_cpu_context *hv_cpu
			= per_cpu_ptr(hv_context.cpu_context, cpu);

		page_addr = hv_cpu->synic_message_page;
		msg = (काष्ठा hv_message *)page_addr + VMBUS_MESSAGE_SINT;
		msg->header.message_type = HVMSG_NONE;
	पूर्ण
पूर्ण

/*
 * vmbus_unload_response - Handler क्रम the unload response.
 */
अटल व्योम vmbus_unload_response(काष्ठा vmbus_channel_message_header *hdr)
अणु
	/*
	 * This is a global event; just wakeup the रुकोing thपढ़ो.
	 * Once we successfully unload, we can cleanup the monitor state.
	 *
	 * NB.  A malicious or compromised Hyper-V could send a spurious
	 * message of type CHANNELMSG_UNLOAD_RESPONSE, and trigger a call
	 * of the complete() below.  Make sure that unload_event has been
	 * initialized by the समय this complete() is executed.
	 */
	complete(&vmbus_connection.unload_event);
पूर्ण

व्योम vmbus_initiate_unload(bool crash)
अणु
	काष्ठा vmbus_channel_message_header hdr;

	अगर (xchg(&vmbus_connection.conn_state, DISCONNECTED) == DISCONNECTED)
		वापस;

	/* Pre-Win2012R2 hosts करोn't support reconnect */
	अगर (vmbus_proto_version < VERSION_WIN8_1)
		वापस;

	reinit_completion(&vmbus_connection.unload_event);
	स_रखो(&hdr, 0, माप(काष्ठा vmbus_channel_message_header));
	hdr.msgtype = CHANNELMSG_UNLOAD;
	vmbus_post_msg(&hdr, माप(काष्ठा vmbus_channel_message_header),
		       !crash);

	/*
	 * vmbus_initiate_unload() is also called on crash and the crash can be
	 * happening in an पूर्णांकerrupt context, where scheduling is impossible.
	 */
	अगर (!crash)
		रुको_क्रम_completion(&vmbus_connection.unload_event);
	अन्यथा
		vmbus_रुको_क्रम_unload();
पूर्ण

अटल व्योम check_पढ़ोy_क्रम_resume_event(व्योम)
अणु
	/*
	 * If all the old primary channels have been fixed up, then it's safe
	 * to resume.
	 */
	अगर (atomic_dec_and_test(&vmbus_connection.nr_chan_fixup_on_resume))
		complete(&vmbus_connection.पढ़ोy_क्रम_resume_event);
पूर्ण

अटल व्योम vmbus_setup_channel_state(काष्ठा vmbus_channel *channel,
				      काष्ठा vmbus_channel_offer_channel *offer)
अणु
	/*
	 * Setup state क्रम संकेतling the host.
	 */
	channel->sig_event = VMBUS_EVENT_CONNECTION_ID;

	अगर (vmbus_proto_version != VERSION_WS2008) अणु
		channel->is_dedicated_पूर्णांकerrupt =
				(offer->is_dedicated_पूर्णांकerrupt != 0);
		channel->sig_event = offer->connection_id;
	पूर्ण

	स_नकल(&channel->offermsg, offer,
	       माप(काष्ठा vmbus_channel_offer_channel));
	channel->monitor_grp = (u8)offer->monitorid / 32;
	channel->monitor_bit = (u8)offer->monitorid % 32;
	channel->device_id = hv_get_dev_type(channel);
पूर्ण

/*
 * find_primary_channel_by_offer - Get the channel object given the new offer.
 * This is only used in the resume path of hibernation.
 */
अटल काष्ठा vmbus_channel *
find_primary_channel_by_offer(स्थिर काष्ठा vmbus_channel_offer_channel *offer)
अणु
	काष्ठा vmbus_channel *channel = शून्य, *iter;
	स्थिर guid_t *inst1, *inst2;

	/* Ignore sub-channel offers. */
	अगर (offer->offer.sub_channel_index != 0)
		वापस शून्य;

	mutex_lock(&vmbus_connection.channel_mutex);

	list_क्रम_each_entry(iter, &vmbus_connection.chn_list, listentry) अणु
		inst1 = &iter->offermsg.offer.अगर_instance;
		inst2 = &offer->offer.अगर_instance;

		अगर (guid_equal(inst1, inst2)) अणु
			channel = iter;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&vmbus_connection.channel_mutex);

	वापस channel;
पूर्ण

अटल bool vmbus_is_valid_device(स्थिर guid_t *guid)
अणु
	u16 i;

	अगर (!hv_is_isolation_supported())
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(vmbus_devs); i++) अणु
		अगर (guid_equal(guid, &vmbus_devs[i].guid))
			वापस vmbus_devs[i].allowed_in_isolated;
	पूर्ण
	वापस false;
पूर्ण

/*
 * vmbus_onoffer - Handler क्रम channel offers from vmbus in parent partition.
 *
 */
अटल व्योम vmbus_onoffer(काष्ठा vmbus_channel_message_header *hdr)
अणु
	काष्ठा vmbus_channel_offer_channel *offer;
	काष्ठा vmbus_channel *oldchannel, *newchannel;
	माप_प्रकार offer_sz;

	offer = (काष्ठा vmbus_channel_offer_channel *)hdr;

	trace_vmbus_onoffer(offer);

	अगर (!vmbus_is_valid_device(&offer->offer.अगर_type)) अणु
		pr_err_ratelimited("Invalid offer %d from the host supporting isolation\n",
				   offer->child_relid);
		atomic_dec(&vmbus_connection.offer_in_progress);
		वापस;
	पूर्ण

	oldchannel = find_primary_channel_by_offer(offer);

	अगर (oldchannel != शून्य) अणु
		/*
		 * We're resuming from hibernation: all the sub-channel and
		 * hv_sock channels we had beक्रमe the hibernation should have
		 * been cleaned up, and now we must be seeing a re-offered
		 * primary channel that we had beक्रमe the hibernation.
		 */

		/*
		 * अणु Initially: channel relid = INVALID_RELID,
		 *		channels[valid_relid] = शून्य पूर्ण
		 *
		 * CPU1					CPU2
		 *
		 * [vmbus_onoffer()]			[vmbus_device_release()]
		 *
		 * LOCK channel_mutex			LOCK channel_mutex
		 * STORE channel relid = valid_relid	LOAD r1 = channel relid
		 * MAP_RELID channel			अगर (r1 != INVALID_RELID)
		 * UNLOCK channel_mutex			  UNMAP_RELID channel
		 *					UNLOCK channel_mutex
		 *
		 * Forbids: r1 == valid_relid &&
		 *              channels[valid_relid] == channel
		 *
		 * Note.  r1 can be INVALID_RELID only क्रम an hv_sock channel.
		 * None of the hv_sock channels which were present beक्रमe the
		 * suspend are re-offered upon the resume.  See the WARN_ON()
		 * in hv_process_channel_removal().
		 */
		mutex_lock(&vmbus_connection.channel_mutex);

		atomic_dec(&vmbus_connection.offer_in_progress);

		WARN_ON(oldchannel->offermsg.child_relid != INVALID_RELID);
		/* Fix up the relid. */
		oldchannel->offermsg.child_relid = offer->child_relid;

		offer_sz = माप(*offer);
		अगर (स_भेद(offer, &oldchannel->offermsg, offer_sz) != 0) अणु
			/*
			 * This is not an error, since the host can also change
			 * the other field(s) of the offer, e.g. on WS RS5
			 * (Build 17763), the offer->connection_id of the
			 * Mellanox VF vmbus device can change when the host
			 * reoffers the device upon resume.
			 */
			pr_debug("vmbus offer changed: relid=%d\n",
				 offer->child_relid);

			prपूर्णांक_hex_dump_debug("Old vmbus offer: ",
					     DUMP_PREFIX_OFFSET, 16, 4,
					     &oldchannel->offermsg, offer_sz,
					     false);
			prपूर्णांक_hex_dump_debug("New vmbus offer: ",
					     DUMP_PREFIX_OFFSET, 16, 4,
					     offer, offer_sz, false);

			/* Fix up the old channel. */
			vmbus_setup_channel_state(oldchannel, offer);
		पूर्ण

		/* Add the channel back to the array of channels. */
		vmbus_channel_map_relid(oldchannel);
		check_पढ़ोy_क्रम_resume_event();

		mutex_unlock(&vmbus_connection.channel_mutex);
		वापस;
	पूर्ण

	/* Allocate the channel object and save this offer. */
	newchannel = alloc_channel();
	अगर (!newchannel) अणु
		vmbus_release_relid(offer->child_relid);
		atomic_dec(&vmbus_connection.offer_in_progress);
		pr_err("Unable to allocate channel object\n");
		वापस;
	पूर्ण

	vmbus_setup_channel_state(newchannel, offer);

	vmbus_process_offer(newchannel);
पूर्ण

अटल व्योम check_पढ़ोy_क्रम_suspend_event(व्योम)
अणु
	/*
	 * If all the sub-channels or hv_sock channels have been cleaned up,
	 * then it's safe to suspend.
	 */
	अगर (atomic_dec_and_test(&vmbus_connection.nr_chan_बंद_on_suspend))
		complete(&vmbus_connection.पढ़ोy_क्रम_suspend_event);
पूर्ण

/*
 * vmbus_onoffer_rescind - Rescind offer handler.
 *
 * We queue a work item to process this offer synchronously
 */
अटल व्योम vmbus_onoffer_rescind(काष्ठा vmbus_channel_message_header *hdr)
अणु
	काष्ठा vmbus_channel_rescind_offer *rescind;
	काष्ठा vmbus_channel *channel;
	काष्ठा device *dev;
	bool clean_up_chan_क्रम_suspend;

	rescind = (काष्ठा vmbus_channel_rescind_offer *)hdr;

	trace_vmbus_onoffer_rescind(rescind);

	/*
	 * The offer msg and the corresponding rescind msg
	 * from the host are guranteed to be ordered -
	 * offer comes in first and then the rescind.
	 * Since we process these events in work elements,
	 * and with preemption, we may end up processing
	 * the events out of order.  We rely on the synchronization
	 * provided by offer_in_progress and by channel_mutex क्रम
	 * ordering these events:
	 *
	 * अणु Initially: offer_in_progress = 1 पूर्ण
	 *
	 * CPU1				CPU2
	 *
	 * [vmbus_onoffer()]		[vmbus_onoffer_rescind()]
	 *
	 * LOCK channel_mutex		WAIT_ON offer_in_progress == 0
	 * DECREMENT offer_in_progress	LOCK channel_mutex
	 * STORE channels[]		LOAD channels[]
	 * UNLOCK channel_mutex		UNLOCK channel_mutex
	 *
	 * Forbids: CPU2's LOAD from *not* seeing CPU1's STORE
	 */

	जबतक (atomic_पढ़ो(&vmbus_connection.offer_in_progress) != 0) अणु
		/*
		 * We रुको here until any channel offer is currently
		 * being processed.
		 */
		msleep(1);
	पूर्ण

	mutex_lock(&vmbus_connection.channel_mutex);
	channel = relid2channel(rescind->child_relid);
	अगर (channel != शून्य) अणु
		/*
		 * Guarantee that no other instance of vmbus_onoffer_rescind()
		 * has got a reference to the channel object.  Synchronize on
		 * &vmbus_connection.channel_mutex.
		 */
		अगर (channel->rescind_ref) अणु
			mutex_unlock(&vmbus_connection.channel_mutex);
			वापस;
		पूर्ण
		channel->rescind_ref = true;
	पूर्ण
	mutex_unlock(&vmbus_connection.channel_mutex);

	अगर (channel == शून्य) अणु
		/*
		 * We failed in processing the offer message;
		 * we would have cleaned up the relid in that
		 * failure path.
		 */
		वापस;
	पूर्ण

	clean_up_chan_क्रम_suspend = is_hvsock_channel(channel) ||
				    is_sub_channel(channel);
	/*
	 * Beक्रमe setting channel->rescind in vmbus_rescind_cleanup(), we
	 * should make sure the channel callback is not running any more.
	 */
	vmbus_reset_channel_cb(channel);

	/*
	 * Now रुको क्रम offer handling to complete.
	 */
	vmbus_rescind_cleanup(channel);
	जबतक (READ_ONCE(channel->probe_करोne) == false) अणु
		/*
		 * We रुको here until any channel offer is currently
		 * being processed.
		 */
		msleep(1);
	पूर्ण

	/*
	 * At this poपूर्णांक, the rescind handling can proceed safely.
	 */

	अगर (channel->device_obj) अणु
		अगर (channel->chn_rescind_callback) अणु
			channel->chn_rescind_callback(channel);

			अगर (clean_up_chan_क्रम_suspend)
				check_पढ़ोy_क्रम_suspend_event();

			वापस;
		पूर्ण
		/*
		 * We will have to unरेजिस्टर this device from the
		 * driver core.
		 */
		dev = get_device(&channel->device_obj->device);
		अगर (dev) अणु
			vmbus_device_unरेजिस्टर(channel->device_obj);
			put_device(dev);
		पूर्ण
	पूर्ण अन्यथा अगर (channel->primary_channel != शून्य) अणु
		/*
		 * Sub-channel is being rescinded. Following is the channel
		 * बंद sequence when initiated from the driveri (refer to
		 * vmbus_बंद() क्रम details):
		 * 1. Close all sub-channels first
		 * 2. Then बंद the primary channel.
		 */
		mutex_lock(&vmbus_connection.channel_mutex);
		अगर (channel->state == CHANNEL_OPEN_STATE) अणु
			/*
			 * The channel is currently not खोलो;
			 * it is safe क्रम us to cleanup the channel.
			 */
			hv_process_channel_removal(channel);
		पूर्ण अन्यथा अणु
			complete(&channel->rescind_event);
		पूर्ण
		mutex_unlock(&vmbus_connection.channel_mutex);
	पूर्ण

	/* The "channel" may have been मुक्तd. Do not access it any दीर्घer. */

	अगर (clean_up_chan_क्रम_suspend)
		check_पढ़ोy_क्रम_suspend_event();
पूर्ण

व्योम vmbus_hvsock_device_unरेजिस्टर(काष्ठा vmbus_channel *channel)
अणु
	BUG_ON(!is_hvsock_channel(channel));

	/* We always get a rescind msg when a connection is बंदd. */
	जबतक (!READ_ONCE(channel->probe_करोne) || !READ_ONCE(channel->rescind))
		msleep(1);

	vmbus_device_unरेजिस्टर(channel->device_obj);
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_hvsock_device_unरेजिस्टर);


/*
 * vmbus_onoffers_delivered -
 * This is invoked when all offers have been delivered.
 *
 * Nothing to करो here.
 */
अटल व्योम vmbus_onoffers_delivered(
			काष्ठा vmbus_channel_message_header *hdr)
अणु
पूर्ण

/*
 * vmbus_onखोलो_result - Open result handler.
 *
 * This is invoked when we received a response to our channel खोलो request.
 * Find the matching request, copy the response and संकेत the requesting
 * thपढ़ो.
 */
अटल व्योम vmbus_onखोलो_result(काष्ठा vmbus_channel_message_header *hdr)
अणु
	काष्ठा vmbus_channel_खोलो_result *result;
	काष्ठा vmbus_channel_msginfo *msginfo;
	काष्ठा vmbus_channel_message_header *requestheader;
	काष्ठा vmbus_channel_खोलो_channel *खोलोmsg;
	अचिन्हित दीर्घ flags;

	result = (काष्ठा vmbus_channel_खोलो_result *)hdr;

	trace_vmbus_onखोलो_result(result);

	/*
	 * Find the खोलो msg, copy the result and संकेत/unblock the रुको event
	 */
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);

	list_क्रम_each_entry(msginfo, &vmbus_connection.chn_msg_list,
				msglistentry) अणु
		requestheader =
			(काष्ठा vmbus_channel_message_header *)msginfo->msg;

		अगर (requestheader->msgtype == CHANNELMSG_OPENCHANNEL) अणु
			खोलोmsg =
			(काष्ठा vmbus_channel_खोलो_channel *)msginfo->msg;
			अगर (खोलोmsg->child_relid == result->child_relid &&
			    खोलोmsg->खोलोid == result->खोलोid) अणु
				स_नकल(&msginfo->response.खोलो_result,
				       result,
				       माप(
					काष्ठा vmbus_channel_खोलो_result));
				complete(&msginfo->रुकोevent);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
पूर्ण

/*
 * vmbus_ongpadl_created - GPADL created handler.
 *
 * This is invoked when we received a response to our gpadl create request.
 * Find the matching request, copy the response and संकेत the requesting
 * thपढ़ो.
 */
अटल व्योम vmbus_ongpadl_created(काष्ठा vmbus_channel_message_header *hdr)
अणु
	काष्ठा vmbus_channel_gpadl_created *gpadlcreated;
	काष्ठा vmbus_channel_msginfo *msginfo;
	काष्ठा vmbus_channel_message_header *requestheader;
	काष्ठा vmbus_channel_gpadl_header *gpadlheader;
	अचिन्हित दीर्घ flags;

	gpadlcreated = (काष्ठा vmbus_channel_gpadl_created *)hdr;

	trace_vmbus_ongpadl_created(gpadlcreated);

	/*
	 * Find the establish msg, copy the result and संकेत/unblock the रुको
	 * event
	 */
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);

	list_क्रम_each_entry(msginfo, &vmbus_connection.chn_msg_list,
				msglistentry) अणु
		requestheader =
			(काष्ठा vmbus_channel_message_header *)msginfo->msg;

		अगर (requestheader->msgtype == CHANNELMSG_GPADL_HEADER) अणु
			gpadlheader =
			(काष्ठा vmbus_channel_gpadl_header *)requestheader;

			अगर ((gpadlcreated->child_relid ==
			     gpadlheader->child_relid) &&
			    (gpadlcreated->gpadl == gpadlheader->gpadl)) अणु
				स_नकल(&msginfo->response.gpadl_created,
				       gpadlcreated,
				       माप(
					काष्ठा vmbus_channel_gpadl_created));
				complete(&msginfo->रुकोevent);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
पूर्ण

/*
 * vmbus_onmodअगरychannel_response - Modअगरy Channel response handler.
 *
 * This is invoked when we received a response to our channel modअगरy request.
 * Find the matching request, copy the response and संकेत the requesting thपढ़ो.
 */
अटल व्योम vmbus_onmodअगरychannel_response(काष्ठा vmbus_channel_message_header *hdr)
अणु
	काष्ठा vmbus_channel_modअगरychannel_response *response;
	काष्ठा vmbus_channel_msginfo *msginfo;
	अचिन्हित दीर्घ flags;

	response = (काष्ठा vmbus_channel_modअगरychannel_response *)hdr;

	trace_vmbus_onmodअगरychannel_response(response);

	/*
	 * Find the modअगरy msg, copy the response and संकेत/unblock the रुको event.
	 */
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);

	list_क्रम_each_entry(msginfo, &vmbus_connection.chn_msg_list, msglistentry) अणु
		काष्ठा vmbus_channel_message_header *responseheader =
				(काष्ठा vmbus_channel_message_header *)msginfo->msg;

		अगर (responseheader->msgtype == CHANNELMSG_MODIFYCHANNEL) अणु
			काष्ठा vmbus_channel_modअगरychannel *modअगरymsg;

			modअगरymsg = (काष्ठा vmbus_channel_modअगरychannel *)msginfo->msg;
			अगर (modअगरymsg->child_relid == response->child_relid) अणु
				स_नकल(&msginfo->response.modअगरy_response, response,
				       माप(*response));
				complete(&msginfo->रुकोevent);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
पूर्ण

/*
 * vmbus_ongpadl_tornकरोwn - GPADL tornकरोwn handler.
 *
 * This is invoked when we received a response to our gpadl tearकरोwn request.
 * Find the matching request, copy the response and संकेत the requesting
 * thपढ़ो.
 */
अटल व्योम vmbus_ongpadl_tornकरोwn(
			काष्ठा vmbus_channel_message_header *hdr)
अणु
	काष्ठा vmbus_channel_gpadl_tornकरोwn *gpadl_tornकरोwn;
	काष्ठा vmbus_channel_msginfo *msginfo;
	काष्ठा vmbus_channel_message_header *requestheader;
	काष्ठा vmbus_channel_gpadl_tearकरोwn *gpadl_tearकरोwn;
	अचिन्हित दीर्घ flags;

	gpadl_tornकरोwn = (काष्ठा vmbus_channel_gpadl_tornकरोwn *)hdr;

	trace_vmbus_ongpadl_tornकरोwn(gpadl_tornकरोwn);

	/*
	 * Find the खोलो msg, copy the result and संकेत/unblock the रुको event
	 */
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);

	list_क्रम_each_entry(msginfo, &vmbus_connection.chn_msg_list,
				msglistentry) अणु
		requestheader =
			(काष्ठा vmbus_channel_message_header *)msginfo->msg;

		अगर (requestheader->msgtype == CHANNELMSG_GPADL_TEARDOWN) अणु
			gpadl_tearकरोwn =
			(काष्ठा vmbus_channel_gpadl_tearकरोwn *)requestheader;

			अगर (gpadl_tornकरोwn->gpadl == gpadl_tearकरोwn->gpadl) अणु
				स_नकल(&msginfo->response.gpadl_tornकरोwn,
				       gpadl_tornकरोwn,
				       माप(
					काष्ठा vmbus_channel_gpadl_tornकरोwn));
				complete(&msginfo->रुकोevent);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
पूर्ण

/*
 * vmbus_onversion_response - Version response handler
 *
 * This is invoked when we received a response to our initiate contact request.
 * Find the matching request, copy the response and संकेत the requesting
 * thपढ़ो.
 */
अटल व्योम vmbus_onversion_response(
		काष्ठा vmbus_channel_message_header *hdr)
अणु
	काष्ठा vmbus_channel_msginfo *msginfo;
	काष्ठा vmbus_channel_message_header *requestheader;
	काष्ठा vmbus_channel_version_response *version_response;
	अचिन्हित दीर्घ flags;

	version_response = (काष्ठा vmbus_channel_version_response *)hdr;

	trace_vmbus_onversion_response(version_response);

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);

	list_क्रम_each_entry(msginfo, &vmbus_connection.chn_msg_list,
				msglistentry) अणु
		requestheader =
			(काष्ठा vmbus_channel_message_header *)msginfo->msg;

		अगर (requestheader->msgtype ==
		    CHANNELMSG_INITIATE_CONTACT) अणु
			स_नकल(&msginfo->response.version_response,
			      version_response,
			      माप(काष्ठा vmbus_channel_version_response));
			complete(&msginfo->रुकोevent);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);
पूर्ण

/* Channel message dispatch table */
स्थिर काष्ठा vmbus_channel_message_table_entry
channel_message_table[CHANNELMSG_COUNT] = अणु
	अणु CHANNELMSG_INVALID,			0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_OFFERCHANNEL,		0, vmbus_onoffer,
		माप(काष्ठा vmbus_channel_offer_channel)पूर्ण,
	अणु CHANNELMSG_RESCIND_CHANNELOFFER,	0, vmbus_onoffer_rescind,
		माप(काष्ठा vmbus_channel_rescind_offer) पूर्ण,
	अणु CHANNELMSG_REQUESTOFFERS,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_ALLOFFERS_DELIVERED,	1, vmbus_onoffers_delivered, 0पूर्ण,
	अणु CHANNELMSG_OPENCHANNEL,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_OPENCHANNEL_RESULT,	1, vmbus_onखोलो_result,
		माप(काष्ठा vmbus_channel_खोलो_result)पूर्ण,
	अणु CHANNELMSG_CLOSECHANNEL,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_GPADL_HEADER,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_GPADL_BODY,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_GPADL_CREATED,		1, vmbus_ongpadl_created,
		माप(काष्ठा vmbus_channel_gpadl_created)पूर्ण,
	अणु CHANNELMSG_GPADL_TEARDOWN,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_GPADL_TORNDOWN,		1, vmbus_ongpadl_tornकरोwn,
		माप(काष्ठा vmbus_channel_gpadl_tornकरोwn) पूर्ण,
	अणु CHANNELMSG_RELID_RELEASED,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_INITIATE_CONTACT,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_VERSION_RESPONSE,		1, vmbus_onversion_response,
		माप(काष्ठा vmbus_channel_version_response)पूर्ण,
	अणु CHANNELMSG_UNLOAD,			0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_UNLOAD_RESPONSE,		1, vmbus_unload_response, 0पूर्ण,
	अणु CHANNELMSG_18,			0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_19,			0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_20,			0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_TL_CONNECT_REQUEST,	0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_MODIFYCHANNEL,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_TL_CONNECT_RESULT,		0, शून्य, 0पूर्ण,
	अणु CHANNELMSG_MODIFYCHANNEL_RESPONSE,	1, vmbus_onmodअगरychannel_response,
		माप(काष्ठा vmbus_channel_modअगरychannel_response)पूर्ण,
पूर्ण;

/*
 * vmbus_onmessage - Handler क्रम channel protocol messages.
 *
 * This is invoked in the vmbus worker thपढ़ो context.
 */
व्योम vmbus_onmessage(काष्ठा vmbus_channel_message_header *hdr)
अणु
	trace_vmbus_on_message(hdr);

	/*
	 * vmbus_on_msg_dpc() makes sure the hdr->msgtype here can not go
	 * out of bound and the message_handler poपूर्णांकer can not be शून्य.
	 */
	channel_message_table[hdr->msgtype].message_handler(hdr);
पूर्ण

/*
 * vmbus_request_offers - Send a request to get all our pending offers.
 */
पूर्णांक vmbus_request_offers(व्योम)
अणु
	काष्ठा vmbus_channel_message_header *msg;
	काष्ठा vmbus_channel_msginfo *msginfo;
	पूर्णांक ret;

	msginfo = kदो_स्मृति(माप(*msginfo) +
			  माप(काष्ठा vmbus_channel_message_header),
			  GFP_KERNEL);
	अगर (!msginfo)
		वापस -ENOMEM;

	msg = (काष्ठा vmbus_channel_message_header *)msginfo->msg;

	msg->msgtype = CHANNELMSG_REQUESTOFFERS;

	ret = vmbus_post_msg(msg, माप(काष्ठा vmbus_channel_message_header),
			     true);

	trace_vmbus_request_offers(ret);

	अगर (ret != 0) अणु
		pr_err("Unable to request offers - %d\n", ret);

		जाओ cleanup;
	पूर्ण

cleanup:
	kमुक्त(msginfo);

	वापस ret;
पूर्ण

अटल व्योम invoke_sc_cb(काष्ठा vmbus_channel *primary_channel)
अणु
	काष्ठा list_head *cur, *पंचांगp;
	काष्ठा vmbus_channel *cur_channel;

	अगर (primary_channel->sc_creation_callback == शून्य)
		वापस;

	list_क्रम_each_safe(cur, पंचांगp, &primary_channel->sc_list) अणु
		cur_channel = list_entry(cur, काष्ठा vmbus_channel, sc_list);

		primary_channel->sc_creation_callback(cur_channel);
	पूर्ण
पूर्ण

व्योम vmbus_set_sc_create_callback(काष्ठा vmbus_channel *primary_channel,
				व्योम (*sc_cr_cb)(काष्ठा vmbus_channel *new_sc))
अणु
	primary_channel->sc_creation_callback = sc_cr_cb;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_set_sc_create_callback);

bool vmbus_are_subchannels_present(काष्ठा vmbus_channel *primary)
अणु
	bool ret;

	ret = !list_empty(&primary->sc_list);

	अगर (ret) अणु
		/*
		 * Invoke the callback on sub-channel creation.
		 * This will present a unअगरorm पूर्णांकerface to the
		 * clients.
		 */
		invoke_sc_cb(primary);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_are_subchannels_present);

व्योम vmbus_set_chn_rescind_callback(काष्ठा vmbus_channel *channel,
		व्योम (*chn_rescind_cb)(काष्ठा vmbus_channel *))
अणु
	channel->chn_rescind_callback = chn_rescind_cb;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_set_chn_rescind_callback);
