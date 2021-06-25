<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (c) 2011, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *   K. Y. Srinivasan <kys@microsoft.com>
 */

#अगर_अघोषित _HYPERV_VMBUS_H
#घोषणा _HYPERV_VMBUS_H

#समावेश <linux/list.h>
#समावेश <यंत्र/sync_bitops.h>
#समावेश <यंत्र/hyperv-tlfs.h>
#समावेश <linux/atomic.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "hv_trace.h"

/*
 * Timeout क्रम services such as KVP and fcopy.
 */
#घोषणा HV_UTIL_TIMEOUT 30

/*
 * Timeout क्रम guest-host handshake क्रम services.
 */
#घोषणा HV_UTIL_NEGO_TIMEOUT 55


/* Definitions क्रम the monitored notअगरication facility */
जोड़ hv_monitor_trigger_group अणु
	u64 as_uपूर्णांक64;
	काष्ठा अणु
		u32 pending;
		u32 armed;
	पूर्ण;
पूर्ण;

काष्ठा hv_monitor_parameter अणु
	जोड़ hv_connection_id connectionid;
	u16 flagnumber;
	u16 rsvdz;
पूर्ण;

जोड़ hv_monitor_trigger_state अणु
	u32 asu32;

	काष्ठा अणु
		u32 group_enable:4;
		u32 rsvdz:28;
	पूर्ण;
पूर्ण;

/* काष्ठा hv_monitor_page Layout */
/* ------------------------------------------------------ */
/* | 0   | TriggerState (4 bytes) | Rsvd1 (4 bytes)     | */
/* | 8   | TriggerGroup[0]                              | */
/* | 10  | TriggerGroup[1]                              | */
/* | 18  | TriggerGroup[2]                              | */
/* | 20  | TriggerGroup[3]                              | */
/* | 28  | Rsvd2[0]                                     | */
/* | 30  | Rsvd2[1]                                     | */
/* | 38  | Rsvd2[2]                                     | */
/* | 40  | NextCheckTime[0][0]    | NextCheckTime[0][1] | */
/* | ...                                                | */
/* | 240 | Latency[0][0..3]                             | */
/* | 340 | Rsvz3[0]                                     | */
/* | 440 | Parameter[0][0]                              | */
/* | 448 | Parameter[0][1]                              | */
/* | ...                                                | */
/* | 840 | Rsvd4[0]                                     | */
/* ------------------------------------------------------ */
काष्ठा hv_monitor_page अणु
	जोड़ hv_monitor_trigger_state trigger_state;
	u32 rsvdz1;

	जोड़ hv_monitor_trigger_group trigger_group[4];
	u64 rsvdz2[3];

	s32 next_checkसमय[4][32];

	u16 latency[4][32];
	u64 rsvdz3[32];

	काष्ठा hv_monitor_parameter parameter[4][32];

	u8 rsvdz4[1984];
पूर्ण;

#घोषणा HV_HYPERCALL_PARAM_ALIGN	माप(u64)

/* Definition of the hv_post_message hypercall input काष्ठाure. */
काष्ठा hv_input_post_message अणु
	जोड़ hv_connection_id connectionid;
	u32 reserved;
	u32 message_type;
	u32 payload_size;
	u64 payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
पूर्ण;


क्रमागत अणु
	VMBUS_MESSAGE_CONNECTION_ID	= 1,
	VMBUS_MESSAGE_CONNECTION_ID_4	= 4,
	VMBUS_MESSAGE_PORT_ID		= 1,
	VMBUS_EVENT_CONNECTION_ID	= 2,
	VMBUS_EVENT_PORT_ID		= 2,
	VMBUS_MONITOR_CONNECTION_ID	= 3,
	VMBUS_MONITOR_PORT_ID		= 3,
	VMBUS_MESSAGE_SINT		= 2,
पूर्ण;

/*
 * Per cpu state क्रम channel handling
 */
काष्ठा hv_per_cpu_context अणु
	व्योम *synic_message_page;
	व्योम *synic_event_page;
	/*
	 * buffer to post messages to the host.
	 */
	व्योम *post_msg_page;

	/*
	 * Starting with win8, we can take channel पूर्णांकerrupts on any CPU;
	 * we will manage the tasklet that handles events messages on a per CPU
	 * basis.
	 */
	काष्ठा tasklet_काष्ठा msg_dpc;
पूर्ण;

काष्ठा hv_context अणु
	/* We only support running on top of Hyper-V
	 * So at this poपूर्णांक this really can only contain the Hyper-V ID
	 */
	u64 guestid;

	काष्ठा hv_per_cpu_context __percpu *cpu_context;

	/*
	 * To manage allocations in a NUMA node.
	 * Array indexed by numa node ID.
	 */
	काष्ठा cpumask *hv_numa_map;
पूर्ण;

बाह्य काष्ठा hv_context hv_context;

/* Hv Interface */

बाह्य पूर्णांक hv_init(व्योम);

बाह्य पूर्णांक hv_post_message(जोड़ hv_connection_id connection_id,
			 क्रमागत hv_message_type message_type,
			 व्योम *payload, माप_प्रकार payload_size);

बाह्य पूर्णांक hv_synic_alloc(व्योम);

बाह्य व्योम hv_synic_मुक्त(व्योम);

बाह्य व्योम hv_synic_enable_regs(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक hv_synic_init(अचिन्हित पूर्णांक cpu);

बाह्य व्योम hv_synic_disable_regs(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक hv_synic_cleanup(अचिन्हित पूर्णांक cpu);

/* Interface */

व्योम hv_ringbuffer_pre_init(काष्ठा vmbus_channel *channel);

पूर्णांक hv_ringbuffer_init(काष्ठा hv_ring_buffer_info *ring_info,
		       काष्ठा page *pages, u32 pagecnt);

व्योम hv_ringbuffer_cleanup(काष्ठा hv_ring_buffer_info *ring_info);

पूर्णांक hv_ringbuffer_ग_लिखो(काष्ठा vmbus_channel *channel,
			स्थिर काष्ठा kvec *kv_list, u32 kv_count,
			u64 requestid);

पूर्णांक hv_ringbuffer_पढ़ो(काष्ठा vmbus_channel *channel,
		       व्योम *buffer, u32 buflen, u32 *buffer_actual_len,
		       u64 *requestid, bool raw);

/*
 * The Maximum number of channels (16384) is determined by the size of the
 * पूर्णांकerrupt page, which is HV_HYP_PAGE_SIZE. 1/2 of HV_HYP_PAGE_SIZE is to
 * send endpoपूर्णांक पूर्णांकerrupts, and the other is to receive endpoपूर्णांक पूर्णांकerrupts.
 */
#घोषणा MAX_NUM_CHANNELS	((HV_HYP_PAGE_SIZE >> 1) << 3)

/* The value here must be in multiple of 32 */
#घोषणा MAX_NUM_CHANNELS_SUPPORTED	256

#घोषणा MAX_CHANNEL_RELIDS					\
	max(MAX_NUM_CHANNELS_SUPPORTED, HV_EVENT_FLAGS_COUNT)

क्रमागत vmbus_connect_state अणु
	DISCONNECTED,
	CONNECTING,
	CONNECTED,
	DISCONNECTING
पूर्ण;

#घोषणा MAX_SIZE_CHANNEL_MESSAGE	HV_MESSAGE_PAYLOAD_BYTE_COUNT

/*
 * The CPU that Hyper-V will पूर्णांकerrupt क्रम VMBUS messages, such as
 * CHANNELMSG_OFFERCHANNEL and CHANNELMSG_RESCIND_CHANNELOFFER.
 */
#घोषणा VMBUS_CONNECT_CPU	0

काष्ठा vmbus_connection अणु
	u32 msg_conn_id;

	atomic_t offer_in_progress;

	क्रमागत vmbus_connect_state conn_state;

	atomic_t next_gpadl_handle;

	काष्ठा completion  unload_event;
	/*
	 * Represents channel पूर्णांकerrupts. Each bit position represents a
	 * channel.  When a channel sends an पूर्णांकerrupt via VMBUS, it finds its
	 * bit in the sendInterruptPage, set it and calls Hv to generate a port
	 * event. The other end receives the port event and parse the
	 * recvInterruptPage to see which bit is set
	 */
	व्योम *पूर्णांक_page;
	व्योम *send_पूर्णांक_page;
	व्योम *recv_पूर्णांक_page;

	/*
	 * 2 pages - 1st page क्रम parent->child notअगरication and 2nd
	 * is child->parent notअगरication
	 */
	काष्ठा hv_monitor_page *monitor_pages[2];
	काष्ठा list_head chn_msg_list;
	spinlock_t channelmsg_lock;

	/* List of channels */
	काष्ठा list_head chn_list;
	काष्ठा mutex channel_mutex;

	/* Array of channels */
	काष्ठा vmbus_channel **channels;

	/*
	 * An offer message is handled first on the work_queue, and then
	 * is further handled on handle_primary_chan_wq or
	 * handle_sub_chan_wq.
	 */
	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा workqueue_काष्ठा *handle_primary_chan_wq;
	काष्ठा workqueue_काष्ठा *handle_sub_chan_wq;

	/*
	 * The number of sub-channels and hv_sock channels that should be
	 * cleaned up upon suspend: sub-channels will be re-created upon
	 * resume, and hv_sock channels should not survive suspend.
	 */
	atomic_t nr_chan_बंद_on_suspend;
	/*
	 * vmbus_bus_suspend() रुकोs क्रम "nr_chan_close_on_suspend" to
	 * drop to zero.
	 */
	काष्ठा completion पढ़ोy_क्रम_suspend_event;

	/*
	 * The number of primary channels that should be "fixed up"
	 * upon resume: these channels are re-offered upon resume, and some
	 * fields of the channel offers (i.e. child_relid and connection_id)
	 * can change, so the old offermsg must be fixed up, beक्रमe the resume
	 * callbacks of the VSC drivers start to further touch the channels.
	 */
	atomic_t nr_chan_fixup_on_resume;
	/*
	 * vmbus_bus_resume() रुकोs क्रम "nr_chan_fixup_on_resume" to
	 * drop to zero.
	 */
	काष्ठा completion पढ़ोy_क्रम_resume_event;
पूर्ण;


काष्ठा vmbus_msginfo अणु
	/* Bookkeeping stuff */
	काष्ठा list_head msglist_entry;

	/* The message itself */
	अचिन्हित अक्षर msg[];
पूर्ण;


बाह्य काष्ठा vmbus_connection vmbus_connection;

पूर्णांक vmbus_negotiate_version(काष्ठा vmbus_channel_msginfo *msginfo, u32 version);

अटल अंतरभूत व्योम vmbus_send_पूर्णांकerrupt(u32 relid)
अणु
	sync_set_bit(relid, vmbus_connection.send_पूर्णांक_page);
पूर्ण

क्रमागत vmbus_message_handler_type अणु
	/* The related handler can sleep. */
	VMHT_BLOCKING = 0,

	/* The related handler must NOT sleep. */
	VMHT_NON_BLOCKING = 1,
पूर्ण;

काष्ठा vmbus_channel_message_table_entry अणु
	क्रमागत vmbus_channel_message_type message_type;
	क्रमागत vmbus_message_handler_type handler_type;
	व्योम (*message_handler)(काष्ठा vmbus_channel_message_header *msg);
	u32 min_payload_len;
पूर्ण;

बाह्य स्थिर काष्ठा vmbus_channel_message_table_entry
	channel_message_table[CHANNELMSG_COUNT];


/* General vmbus पूर्णांकerface */

काष्ठा hv_device *vmbus_device_create(स्थिर guid_t *type,
				      स्थिर guid_t *instance,
				      काष्ठा vmbus_channel *channel);

पूर्णांक vmbus_device_रेजिस्टर(काष्ठा hv_device *child_device_obj);
व्योम vmbus_device_unरेजिस्टर(काष्ठा hv_device *device_obj);
पूर्णांक vmbus_add_channel_kobj(काष्ठा hv_device *device_obj,
			   काष्ठा vmbus_channel *channel);

व्योम vmbus_हटाओ_channel_attr_group(काष्ठा vmbus_channel *channel);

व्योम vmbus_channel_map_relid(काष्ठा vmbus_channel *channel);
व्योम vmbus_channel_unmap_relid(काष्ठा vmbus_channel *channel);

काष्ठा vmbus_channel *relid2channel(u32 relid);

व्योम vmbus_मुक्त_channels(व्योम);

/* Connection पूर्णांकerface */

पूर्णांक vmbus_connect(व्योम);
व्योम vmbus_disconnect(व्योम);

पूर्णांक vmbus_post_msg(व्योम *buffer, माप_प्रकार buflen, bool can_sleep);

व्योम vmbus_on_event(अचिन्हित दीर्घ data);
व्योम vmbus_on_msg_dpc(अचिन्हित दीर्घ data);

पूर्णांक hv_kvp_init(काष्ठा hv_util_service *srv);
व्योम hv_kvp_deinit(व्योम);
पूर्णांक hv_kvp_pre_suspend(व्योम);
पूर्णांक hv_kvp_pre_resume(व्योम);
व्योम hv_kvp_onchannelcallback(व्योम *context);

पूर्णांक hv_vss_init(काष्ठा hv_util_service *srv);
व्योम hv_vss_deinit(व्योम);
पूर्णांक hv_vss_pre_suspend(व्योम);
पूर्णांक hv_vss_pre_resume(व्योम);
व्योम hv_vss_onchannelcallback(व्योम *context);

पूर्णांक hv_fcopy_init(काष्ठा hv_util_service *srv);
व्योम hv_fcopy_deinit(व्योम);
पूर्णांक hv_fcopy_pre_suspend(व्योम);
पूर्णांक hv_fcopy_pre_resume(व्योम);
व्योम hv_fcopy_onchannelcallback(व्योम *context);
व्योम vmbus_initiate_unload(bool crash);

अटल अंतरभूत व्योम hv_poll_channel(काष्ठा vmbus_channel *channel,
				   व्योम (*cb)(व्योम *))
अणु
	अगर (!channel)
		वापस;
	cb(channel);
पूर्ण

क्रमागत hvutil_device_state अणु
	HVUTIL_DEVICE_INIT = 0,  /* driver is loaded, रुकोing क्रम userspace */
	HVUTIL_READY,            /* userspace is रेजिस्टरed */
	HVUTIL_HOSTMSG_RECEIVED, /* message from the host was received */
	HVUTIL_USERSPACE_REQ,    /* request to userspace was sent */
	HVUTIL_USERSPACE_RECV,   /* reply from userspace was received */
	HVUTIL_DEVICE_DYING,     /* driver unload is in progress */
पूर्ण;

क्रमागत delay अणु
	INTERRUPT_DELAY = 0,
	MESSAGE_DELAY   = 1,
पूर्ण;

बाह्य स्थिर काष्ठा vmbus_device vmbus_devs[];

अटल अंतरभूत bool hv_is_perf_channel(काष्ठा vmbus_channel *channel)
अणु
	वापस vmbus_devs[channel->device_id].perf_device;
पूर्ण

अटल अंतरभूत bool hv_is_alloced_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा vmbus_channel *channel, *sc;

	lockdep_निश्चित_held(&vmbus_connection.channel_mutex);
	/*
	 * List additions/deletions as well as updates of the target CPUs are
	 * रक्षित by channel_mutex.
	 */
	list_क्रम_each_entry(channel, &vmbus_connection.chn_list, listentry) अणु
		अगर (!hv_is_perf_channel(channel))
			जारी;
		अगर (channel->target_cpu == cpu)
			वापस true;
		list_क्रम_each_entry(sc, &channel->sc_list, sc_list) अणु
			अगर (sc->target_cpu == cpu)
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम hv_set_alloced_cpu(अचिन्हित पूर्णांक cpu)
अणु
	cpumask_set_cpu(cpu, &hv_context.hv_numa_map[cpu_to_node(cpu)]);
पूर्ण

अटल अंतरभूत व्योम hv_clear_alloced_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (hv_is_alloced_cpu(cpu))
		वापस;
	cpumask_clear_cpu(cpu, &hv_context.hv_numa_map[cpu_to_node(cpu)]);
पूर्ण

अटल अंतरभूत व्योम hv_update_alloced_cpus(अचिन्हित पूर्णांक old_cpu,
					  अचिन्हित पूर्णांक new_cpu)
अणु
	hv_set_alloced_cpu(new_cpu);
	hv_clear_alloced_cpu(old_cpu);
पूर्ण

#अगर_घोषित CONFIG_HYPERV_TESTING

पूर्णांक hv_debug_add_dev_dir(काष्ठा hv_device *dev);
व्योम hv_debug_rm_dev_dir(काष्ठा hv_device *dev);
व्योम hv_debug_rm_all_dir(व्योम);
पूर्णांक hv_debug_init(व्योम);
व्योम hv_debug_delay_test(काष्ठा vmbus_channel *channel, क्रमागत delay delay_type);

#अन्यथा /* CONFIG_HYPERV_TESTING */

अटल अंतरभूत व्योम hv_debug_rm_dev_dir(काष्ठा hv_device *dev) अणुपूर्ण;
अटल अंतरभूत व्योम hv_debug_rm_all_dir(व्योम) अणुपूर्ण;
अटल अंतरभूत व्योम hv_debug_delay_test(काष्ठा vmbus_channel *channel,
				       क्रमागत delay delay_type) अणुपूर्ण;
अटल अंतरभूत पूर्णांक hv_debug_init(व्योम)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक hv_debug_add_dev_dir(काष्ठा hv_device *dev)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर /* CONFIG_HYPERV_TESTING */

#पूर्ण_अगर /* _HYPERV_VMBUS_H */
